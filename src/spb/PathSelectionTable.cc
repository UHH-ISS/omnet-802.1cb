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

#include "PathSelectionTable.h"

PathSelectionTable::PathSelectionTable() {
    // TODO Auto-generated constructor stub
}

Define_Module(PathSelectionTable);

PathSelectionTable::~PathSelectionTable() {
    // TODO Auto-generated destructor stub
}

void PathSelectionTable::initialize(int stage) {
    timeout = par("timeout");
}

PathVector PathSelectionTable::getPathsForStream(L2Identifier key, MACAddress destAddr) {

    PathVector pv;
    PathSelectionKey psk = PathSelectionKey(key, destAddr);

    if(pathTable.find(psk) != pathTable.end()) {
        PathIndicatorVector piv = pathTable[psk];
        for(unsigned int i = 0; i < piv.size(); i++) {
            if(piv[i].isEnabled(timeout)) {
                pv.push_back(piv[i].getPath());
            }
        }
    }

    return pv;
}

void PathSelectionTable::updateTable(L2Identifier key, MACAddress destAddr, PathVector paths) {
    PathSelectionKey psk = PathSelectionKey(key, destAddr);

    PathIndicatorVector piv;

    for(unsigned int i = 0; i < paths.size(); i++) {
        // Enable only the shortest path
        PathIndicator pi = PathIndicator(paths[i], i == 0);
        piv.push_back(pi);
    }

    pathTable[psk] = piv;
}

void PathSelectionTable::updateTable(L2Identifier key, MACAddress destAddr, Path path) {

    bool isExist = false;

    PathSelectionKey psk = PathSelectionKey(key, destAddr);

    if(pathTable.find(psk) != pathTable.end()) {
        for(unsigned int i = 0; i < pathTable[psk].size(); i++) {
            if(pathTable[psk][i].getPath() == path) {
                pathTable[psk][i].updateStamp();
                isExist = true;
            }
        }
    } else {
        pathTable[psk] = PathIndicatorVector();
    }

    if(!isExist) {
        PathIndicator pi = PathIndicator(path, true);
        pathTable[psk].push_back(pi);
    }
}

void PathSelectionTable::deleteFromTable(L2Identifier key, MACAddress destAddr, Path path) {

    PathSelectionKey psk = PathSelectionKey(key, destAddr);

    for(unsigned int i = 0; i < pathTable[psk].size(); i++) {
        if(pathTable[psk][i].getPath() == path) {
            pathTable[psk].erase(pathTable[psk].begin() + i);
            break;
        }
    }
}

void PathSelectionTable::deleteFromTable(L2Identifier key, MACAddress destAddr) {
    PathSelectionKey psk = PathSelectionKey(key, destAddr);
    pathTable.erase(psk);
}

void PathSelectionTable::printPath(Path path) {
    for(unsigned int i = 0; i < path.size(); i++)
        std::cout << path[i].getID() << " ";
    std::cout << endl;
}

void PathSelectionTable::printTable() {

    std::cout << "Path Selection Table of " ;
    std::cout << this->getFullPath() << endl;

    for (auto it = pathTable.cbegin(); it != pathTable.cend(); it++) {
        PathSelectionKey it_meta = it->first;
        PathIndicatorVector it_paths = it->second;
        std::cout << "To " << it_meta.addr << ", there are " << it_paths.size() << " paths." << endl;
        std::cout << "Those paths are: " << endl;

        for(unsigned int i = 0; i < it_paths.size(); i++) {
            std::cout << "Activation: " << it_paths[i].isEnabled(timeout) << endl;
            printPath(it_paths[i].getPath());
        }
    }
}
