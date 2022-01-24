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

#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/ethernet/switch/MACAddressTable.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"


#include <functional>
#include <algorithm>

#include "ISIS.h"

#include "spb/SPB.h"

using namespace inet;
using std::map;
using std::vector;

int ISIS::hostID = 1;
int ISIS::bridgeID = 1;

ISIS::ISIS() {
    // TODO Auto-generated constructor stub
}

Define_Module(ISIS);

ISIS::~ISIS() {
    // TODO Auto-generated destructor stub
}

void ISIS::initialize(int stage) {

    if (stage == inet::INITSTAGE_LOCAL) {

        if(!strcmp(this->par("type"), "switch")) type = EDGE_BRIDGE;

        if(type > HOST) {
            // Enable that explicitly periodic database announcement scheme
            dbAnnouncePeriod = par("dbAnnouncePeriod");
            scheduleAt(simTime() + dbAnnouncePeriod, new dbAnnounceTimer("ISIS_DB_ANNOUNCE_TIMER"));
        }

        updatePeriod = par("updatePeriod");
        scheduleAt(simTime() + updatePeriod, new updateTimer("ISIS_UPDATE_TIMER"));

    } else if (stage == INITSTAGE_LINK_LAYER) {

        IInterfaceTable* ifTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        MACAddress addr;
        for (int i = 0; i < ifTable->getNumInterfaces(); i++) {
                InterfaceEntry *current = ifTable->getInterface(i);
                if (!current->isLoopback()) {
                    addr = current->getMacAddress();
                }
        }

        int id = -1;

        if(type > HOST) {
            id = (ISIS::bridgeID)++;
            meta = ISISEthernetNodeMeta(MACAddress::generateAutoAddress());
            meta.setISID(this->par("isid"));
        } else {
            id = (ISIS::hostID)++;
            meta = ISISEthernetNodeMeta(addr);
        }
        meta.setType(type);
        meta.setID(id);
        db[meta] = vector<ISISEthernetNodeMeta>();
    }
}

void ISIS::handleMessage(cMessage *msg) {

    if(msg->isSelfMessage()) {
        ISISTimer* isisPacket = dynamic_cast<ISISTimer *>(msg);
        if(isisPacket->getType() == UPDATE) {
            scheduleAt(simTime() + updatePeriod, new updateTimer("ISIS_UPDATE"));
            sendHello();
        } else if(isisPacket->getType() == DB_ANNOUNCE) {
            scheduleAt(simTime() + dbAnnouncePeriod, new dbAnnounceTimer("ISIS_DB_ANNOUNCE_TIMER"));
            sendDbAnnounce();
        }
    } else {
        ISISPacket* isisPacket = dynamic_cast<ISISPacket *>(msg);

        if(isisPacket->getType() == HELLO)
            handleHello(isisPacket);
         else if(isisPacket->getType() == DB_ANNOUNCE)
            handleDbAnnounce(isisPacket);
    }

    delete msg;
}

void ISIS::sendHello() {
    helloPacket* hello = new helloPacket();
    hello->setMeta(meta);
    hello->setSrc(meta.getAddress());
    hello->setDest(ISIS_MULTICAST);
    send(hello, "relayOut");
}

void ISIS::handleHello(const ISISPacket* packet) {
    ISISEthernetNodeMeta received_meta(packet->getMeta());

    if(std::find(db[meta].begin(), db[meta].end(), received_meta) == db[meta].end()) {
        //std::cout << "Bridge with ISID " <<  meta.getAddress() << " (" << meta.getISID() << ") " <<
        //        "received an ISIS_HELLO from " << received_meta.getAddress() << " (" << received_meta.getISID() << ") " << endl;
        db[meta].push_back(received_meta);
    }
}

ISISEthernetNodeMeta ISIS::isDirectEndpoint(MACAddress destAddress) {

    for(unsigned int i = 0; i < db[meta].size(); i++) {
        ISISEthernetNodeMeta it_meta = db[meta][i];
        if(it_meta.getCost() < 2 && it_meta.getType() == HOST && it_meta.getAddress() == destAddress)
            return it_meta;
    }
    return ISISEthernetNodeMeta();
}

void ISIS::sendDbAnnounce(MACAddress destAddress) {
    dbAnnouncePacket* announce = new dbAnnouncePacket();
    announce->setDatabase(db);
    announce->setMeta(meta);
    announce->setDbSignature(getDbSignature().c_str());
    announce->setSrc(meta.getAddress());
    announce->setDest(destAddress);
    send(announce, "relayOut");
}

void ISIS::handleDbAnnounce(const ISISPacket* packet) {

    dbAnnouncePacket* announce = (dbAnnouncePacket*)packet;
    ISISDatabase received_db = announce->getDatabase();
    ISISEthernetNodeMeta received_meta = announce->getMeta();

    // Check time-stamp to overwrite current database if necessary
    std::string currentSignature = getDbSignature();

    if(std::find(db[meta].begin(), db[meta].end(), received_meta) == db[meta].end()) {
        received_meta.setCost(received_meta.getCost() + 1);
        db[meta].push_back(received_meta);
    }

    ISISEthernetNodeMeta it_meta;

    for (auto it = received_db.cbegin(); it != received_db.cend(); it++) {
        it_meta = it->first;
        ISISEthernetNodeMeta stored_meta = db.find(it_meta)->first;
        if(it_meta != meta && (db.find(it_meta) == db.end() || it_meta.getCost() < stored_meta.getCost())) {
            it_meta.setCost(it_meta.getCost() + 1);
            db[it_meta] = it->second;
        }
    }

    std::string newSignature = getDbSignature();

    if(currentSignature != newSignature) {
        //std::cout << "Database updated" << endl;
    }

    if(announce->getDbSignature() != newSignature) {
        //std::cout << "Different database signatures" << endl;
    }
}

std::string ISIS::serializeDatabase() {

    std::string output = "";
    for (auto it = db.cbegin(); it != db.cend(); it++) {
        output += (it->first).str();
        for(int i = 0; i < (it->second).size(); i++)
            output += (it->second)[i].str();
    }

    return output;
}

std::string ISIS::getDbSignature() {

    std::hash<std::string> hsh;
    std::string sign = serializeDatabase();
    return std::to_string(hsh(sign));
}


