//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <algorithm>
#include "inet/common/ModuleAccess.h"

#include "SPB_m.h"
#include "SPB.h"

using namespace inet;

using std::vector;
using std::string;

Define_Module(SPB);

SPB::SPB() {
    // TODO Auto-generated constructor stub
}

SPB::~SPB() {
    // TODO Auto-generated destructor stub
}

void SPB::initialize(int stage)
{
    if (stage == inet::INITSTAGE_LOCAL) {
        isisModule = getModuleFromPar<ISIS>(par("routingModule"), this);
        pstModule = getModuleFromPar<PathSelectionTable>(par("pstModule"), this);

        scheduleAt(simTime() + par("timeInjectPaths"), new parseTimer("PATH_PARSE"));
        scheduleAt(simTime() + 2, new remapTimer("SPB_UPDATE"));
    }
}

void SPB::handleMessage(cMessage *msg) {

    if(msg->isSelfMessage()) {
        SPBTimer* timer = dynamic_cast<SPBTimer *>(msg);

        if(timer->getType() == REMAP) {
            scheduleAt(simTime() + 2, new remapTimer("SPB_UPDATE"));
            updateMap();
        } else if(timer->getType() == PATH_PARSE) {
            string paths = par("paths");
            if(paths.size() > 1) {
                parsePaths(paths);
            }
        }
        delete msg;
    }
}

void SPB::updateMap() {

    ISISDatabase isis_db = isisModule->getDatabase();
    ISISEthernetNodeMeta meta = isisModule->getMetaInfo();

    // Routing only between the bridges in the SAME ISID group
    isidGroup = vector<ISISEthernetNodeMeta>();

    // Detect bridges in an ISID group
    for (auto it = isis_db.cbegin(); it != isis_db.cend(); it++) {
        ISISEthernetNodeMeta it_meta = it->first;
        if(it_meta.getISID() == meta.getISID()) {
            isidGroup.push_back(it_meta);
        }
    }

    isidMap = BridgeMap(isidGroup.size());

    for(int i = 0; i < isidGroup.size(); i++) {
        isidMap[i] = vector<int>(isidGroup.size());
        vector<ISISEthernetNodeMeta> it_neighbors = isis_db[isidGroup[i]];
        for(int j = 0; j < it_neighbors.size(); j++) {
            if(it_neighbors[j].getType() > HOST && it_neighbors[j].getISID() == meta.getISID() ) {
                for(int k = 0; k < isidGroup.size(); k++) {
                    if(it_neighbors[j] == isidGroup[k]) {
                        isidMap[i][k] = 1;
                    }
                }
            }
        }
    }
}

int SPB::findKnotForStream(L2Identifier key, MACAddress destAddr) {

    int knot = 0;

    int id = isisModule->getID();

    PathVector paths = pstModule->getPathsForStream(key, destAddr);

    for(unsigned int i = 0; i < paths.size(); i++) {
        Path path = paths[i];
        for(unsigned int j = 0; j < path.size(); j++) {
            if(path[j].getID() == id)
                knot++;
        }
    }

    return knot;
 }

PathVector SPB::findAllPathsForStream(L2Identifier key, MACAddress destAddr) {

    // Finds all paths but enables only the shortest one
    PathVector paths = findAllPaths(destAddr);
    pstModule->updateTable(key, destAddr, paths);

    return paths;
}

Path SPB::findShortestPath(MACAddress destAddr) {

    Path path;
    PathVector paths = findAllPaths(destAddr);

    if(paths.size()) {
        path = paths[0];
    }

    return path;
}

PathVector SPB::findAllPaths(MACAddress destAddr) {

    // Mark all the vertices as not visited
    updateMap();
    ISISDatabase db = isisModule->getDatabase();

    unsigned int size = isidGroup.size();
    int path[size];
    bool visited[size];  // sptSet[i] will true if vertex i is included in shortest path or shortest distance from src to i is finalized

    PathIDVector pathsID;
    PathVector paths;

    MACAddress destBridgeAddr;
    int destBridgeIndex = -1;
    int selfBridgeIndex = -1;

    int index = 0; // to be given to utilization function

    for (auto it = db.cbegin(); it != db.cend(); it++) {

        ISISEthernetNodeMeta it_meta = it->first;
        vector<ISISEthernetNodeMeta> it_neighbors = it->second;

        // If destination is already a bridge
        if(it_meta.getAddress() == destAddr) {
            destBridgeAddr = destAddr;
            break;
        }

        // If destination connected to it_meta bridge
        for(unsigned int i = 0; i < it_neighbors.size(); i++) {
            if(it_neighbors[i].getAddress() == destAddr) {
                destBridgeAddr = it_meta.getAddress();
                break;
            }
        }

        // Found
        if(destBridgeAddr != MACAddress::UNSPECIFIED_ADDRESS)
            break;
    }

    if(destBridgeAddr == MACAddress::UNSPECIFIED_ADDRESS) {
        std::cout << "Cannot find the bridge that destination connected to." << endl;
        return paths;
    }

    for (unsigned int i = 0; i < size; i++) {
        path[i] = -1;
        visited[i] = false;

        MACAddress it_bridgeAddress = isidGroup[i].getAddress();

        if(it_bridgeAddress == destBridgeAddr)
            destBridgeIndex = i;

        if(it_bridgeAddress == isisModule->getAddress())
            selfBridgeIndex = i;
    }

    if(destBridgeIndex < 0) {
        std::cout << "Bridge not indexed, ISID may be different." << endl;
        return paths;
    }

    findAllPathsUtil(selfBridgeIndex, destBridgeIndex, visited, path, index, pathsID);

    for(int i = 0; i < pathsID.size(); i++) {
        Path path;
        for(int j = 0; j < pathsID[i].size(); j++)
            path.push_back(isidGroup[pathsID[i][j]]);
        paths.push_back(path);
    }

    std::sort(paths.begin(), paths.end(), [](const Path & a, const Path & b){ return a.size() < b.size(); });

    return paths;
}

void SPB::findAllPathsUtil(int srcIndex, int destIndex, bool visited[], int path[], int &index, vector<vector<int>> &paths)
{
    // Mark the current node and store it in path
    visited[srcIndex] = true;
    path[index++] = srcIndex;

    // If current vertex is same as destination, then print path
    if (srcIndex == destIndex) {
        vector<int> route;
        for (int i = 0; i < index; i++)
            route.push_back(path[i]);
        paths.push_back(route);
    } else {
        // Recur for all the vertices adjacent to current vertex
        for(unsigned int i = 0; i < isidMap[srcIndex].size(); i++) {
            if(!visited[i] && isidMap[srcIndex][i])
                findAllPathsUtil(i, destIndex, visited, path, index, paths);
        }
    }

    // Remove current vertex from path[] and mark it as unvisited
    index--;
    visited[srcIndex] = false;
}

vector<ISISEthernetNodeMeta> SPB::getNextHops(L2Identifier stream, MACAddress prevHop, MACAddress destAddr) {

    ISISDatabase db = isisModule->getDatabase();
    PathVector paths = pstModule->getPathsForStream(stream, destAddr);
    vector<ISISEthernetNodeMeta> nextHops;

    // TODO: Check VLAN IDs

    bool is_trunk = false;

    if(paths.size()) {
        for(unsigned int j = 0; j < paths.size(); j++) {

            Path path = paths[j];

            if(path.back().getAddress() == isisModule->getAddress()) {
                ISISEthernetNodeMeta meta = isisModule->isDirectEndpoint(destAddr);
                if(meta.getType() == HOST) {
                    nextHops.clear();
                    nextHops.push_back(meta);
                    return nextHops;
                }
            } else {
                // it assumes that a bridge cannot be edge and trunk at the same time for different paths
                // it holds if paths are loop-free

                for(unsigned int i = 0; i < path.size(); i++) {

                    if(path[i].getAddress() == isisModule->getAddress()) {
                        if(i != 0) {
                            if(path[i-1].getAddress() == prevHop) {
                                nextHops.push_back(path[i+1]);
                                is_trunk = true;
                            }
                        } else {
                            nextHops.push_back(path[i+1]);
                        }
                    }
                }
            }
        }
    } else {
        std::cout << "No path can be found for " << destAddr << endl;
    }
    // remove duplicates
    std::sort(nextHops.begin(), nextHops.end());
    nextHops.erase(std::unique(nextHops.begin(), nextHops.end()), nextHops.end());

    // as paths are ordered by size, front gets the shortest path
    if(is_trunk && nextHops.size() > 1) {
        ISISEthernetNodeMeta shortest_meta = nextHops.front();
        nextHops.clear();
        nextHops.push_back(shortest_meta);
    }

    return nextHops;
}

void SPB::printMap() {

    std::cout << "ISID Map for: " << isisModule->getAddress() << endl;

    for(unsigned int i = 0; i < isidGroup.size(); i++) {
        std::cout << isidGroup[i].getAddress() << " " ;
    }
    std::cout << endl;

    for(unsigned int i = 0; i < isidGroup.size(); i++) {
        for(unsigned int j = 0; j < isidGroup.size(); j++) {
            std::cout << isidMap[i][j] << " " ;
        }
        std::cout << endl;
    }
}

void SPB::parsePaths(string paths) {
    // hostID1:bridgeID1,bridgeID2,..:hostID2:vlan1;hostID3:bridgeID3,bridgeID2,..:hostID4:vlan2;...

    ISISDatabase db = isisModule->getDatabase();

    std::stringstream ss(paths);
    string path;
    L2Identifier key;

    int streamIdentificationFunction = this->getParentModule()->par("streamIdentificationFunction");

    while(std::getline(ss, path,';')) {

        MACAddress srcAddr, destAddr;
        Path p;
        // Serialize a single entry
        std::stringstream iter_ss(path);
        string str_src, str_dest, str_relays, str_vlan;
        for(int i = 0; i < 4; i++) {
            switch(i) {
                case 0:
                    std::getline(iter_ss, str_src,':');
                    break;
                case 1:
                    std::getline(iter_ss, str_relays,':');
                    break;
                case 2:
                    std::getline(iter_ss, str_dest,':');
                    break;
                case 3:
                    std::getline(iter_ss, str_vlan,':');
                    break;
            }
        }

        // Convert IDs to integers
        int srcID = std::stoi(str_src);
        int destID = std::stoi(str_dest);
        int vlan = std::stoi(str_vlan);

        // Serialize path to bridge IDs
        vector<int> relayIDVector;
        std::stringstream iter_ssp(str_relays);
        string str_relayID;
        while(std::getline(iter_ssp, str_relayID, ',')) {
            int relayID = std::stoi(str_relayID);
            relayIDVector.push_back(relayID);
        }

        for (auto it = db.cbegin(); it != db.cend(); it++) {

            ISISEthernetNodeMeta it_meta = it->first;
            vector<ISISEthernetNodeMeta> it_neighbors = it->second;

            for(unsigned int i = 0; i < it_neighbors.size(); i++) {
                if(it_neighbors[i].getID() == srcID && it_neighbors[i].getType() == HOST)
                    srcAddr = it_neighbors[i].getAddress();

                if(it_neighbors[i].getID() == destID && it_neighbors[i].getType() == HOST)
                    destAddr = it_neighbors[i].getAddress();
            }
        }

        for(unsigned int i = 0; i < relayIDVector.size(); i++) {
            for (auto it = db.cbegin(); it != db.cend(); it++) {
                ISISEthernetNodeMeta it_meta = it->first;
                if(it_meta.getID() == relayIDVector[i] && it_meta.getType() > HOST)
                    p.push_back(it_meta);
            }
        }

        switch(streamIdentificationFunction) {
            case 0:
                key = L2Identifier(destAddr, vlan);
            case 1:
                key = L2Identifier(srcAddr, vlan);
            case 2:
                key = L2Identifier(destAddr, vlan);
            default:
                key = L2Identifier(destAddr, vlan);
        }
        pstModule->updateTable(key, destAddr, p);
    }
}


