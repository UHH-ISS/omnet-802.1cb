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
#include "TSNRelay.h"

#include "core4inet/base/avb/AVBDefs.h"
#include "inet/linklayer/configurator/Ieee8021dInterfaceData.h"

#include "FRERControlInfo.h"
#include "spb/ExtendedMACTable.h"
#include "FRERConfiguration_m.h"

Define_Module(TSNRelay);

TSNRelay::TSNRelay() {
    // TODO Auto-generated constructor stub
}

TSNRelay::~TSNRelay() {
    // TODO Auto-generated destructor stub
}

void TSNRelay::initialize(int stage) {
   spbModule = getModuleFromPar<SPB>(par("spbModule"), this);
   pstModule = getModuleFromPar<PathSelectionTable>(par("pstModule"), this);

   streamIdentificationFunction = this->getParentModule()->par("streamIdentificationFunction");
   splitFactor = par("splitFactor");

   isSourceBridge = par("isSourceBridge");
   expectedPacketCount = registerSignal("expectedPacketCount");

   SRPRelay::initialize(stage);
}

void TSNRelay::handleMessage(cMessage * msg) {

    if (!isOperational) {
        EV_ERROR << "Message '" << msg << "' arrived when module status is down, dropped it." << endl;
        delete msg;
        return;
    }

    if (msg && !msg->isSelfMessage()) {

        if (msg->arrivedOn("ifIn")) {

            inet::EthernetIIFrame *frame = check_and_cast<inet::EthernetIIFrame*>(msg);
            if (frame->getEtherType() == ISIS_ETHER_PACKET && frame->getDest() == ISIS_MULTICAST) {
                ISISPacket* isisPacket = dynamic_cast<ISISPacket *>(frame);

                // Explicit MAC learning via ISIS
                if(isisPacket->getType() == HELLO) {
                    updateMACTable(isisPacket, (isisPacket->getMeta()).getAddress());
                }
                send(frame, "routingOut");
            }
            else {
                if(frame->getEtherType() == FRER_ETHER_PACKET) {
                    L2Identifier key = StreamIdentification::getStreamIdentifier((EthernetFrameFRER *)frame, streamIdentificationFunction);

                    int port = frame->getArrivalGate()->getIndex();

                    FRERControlInfo *control_info = new FRERControlInfo();
                    control_info->setPort(port);
                    ExtendedMACTable *mt = (ExtendedMACTable*)(macTable);
                    control_info->setAddress(mt->getAddressByPort(port));

                    frame->setControlInfo(control_info);

                    PathVector paths = pstModule->getPathsForStream(key, frame->getDest());
                    // Don't know how to forward yet
                    if(this->isSourceBridge) {
                        emit(expectedPacketCount, splitFactor);
                    }

                    if (!paths.size()) {
                        paths = spbModule->findAllPathsForStream(key, frame->getDest());

                        if(!paths.size()) {
                            std::cout << "Cannot find any path for " << frame->getDest() << ", FRER frame discarded." << endl;
                            delete msg;
                            return;
                        }
                    } else {
                        FRERConfiguration *knot_config = new FRERConfiguration();
                        knot_config->setKnot(spbModule->findKnotForStream(key, frame->getDest()));
                        knot_config->setKey(key);
                        send(knot_config, "seqRecOut");
                    }

                    send(frame, "seqRecOut");
                } else {
                    int outGate = macTable->getPortForAddress(frame->getDest());

                    if (outGate == -1) {
                        Path path = spbModule->findShortestPath(frame->getDest());

                        if(path.size() > 1) {
                            MACAddress nextHopAddr = path[1].getAddress();
                            outGate = macTable->getPortForAddress(nextHopAddr);
                            macTable->updateTableWithAddress(outGate, frame->getDest());
                        }
                    }

                    if(outGate != -1) {
                        SRPRelay::handleMessage(msg);
                    } else {
                        std::cout << "Cannot find next hop, frame discarded." << endl;
                    }
                }
            }
        } else if(msg->arrivedOn("seqRecIn")) {
            inet::EthernetIIFrame *frame = check_and_cast<inet::EthernetIIFrame*>(msg);
            FRERControlInfo *control_info = (FRERControlInfo*)(frame->getControlInfo());
            frame->setEtherType(FRER_ETHER_PACKET);
            // TODO: Implement a separate StreamSplitting module to handle that
            L2Identifier key = StreamIdentification::getStreamIdentifier((EthernetFrameFRER *) frame, streamIdentificationFunction);

            vector<ISISEthernetNodeMeta> nextHops = spbModule->getNextHops(key, control_info->getAddress(), frame->getDest());

            for(unsigned int i = 0; i < nextHops.size() && i < splitFactor; i++) {
                MACAddress nextHopAddr = nextHops[i].getAddress();
                int port = macTable->getPortForAddress(nextHopAddr);

                if(port < 0) {
                    std::cout << "Disconnection of " << nextHopAddr << " breaks the paths" << endl;
                } else {
                    dispatch(frame->dup(), macTable->getPortForAddress(nextHopAddr));
                }
            }

            delete frame;
        } else if(msg->arrivedOn("routingIn")) {
            inet::EtherFrame *frame = check_and_cast<inet::EtherFrame *>(msg);
            if (frame->getDest() == ISIS_MULTICAST) {
                broadcast(frame);
            } else
                handleAndDispatchFrame(frame);
        } else
            SRPRelay::handleMessage(msg);
    }
    else
        throw cRuntimeError("This module doesn't handle self-messages!");
}

void TSNRelay::broadcast(inet::EtherFrame *frame) {

    EV_DETAIL << "Broadcast frame " << frame << endl;

    unsigned int arrivalGate = frame->getArrivalGate()->getIndex();

    for (unsigned int i = 0; i < portCount; i++) {
        // BUG: Arrival gate for self-generated packets defined as 0 and not sent to port 0.
        // To bypass that, this function overridden
        if (!arrivalGate || (i != arrivalGate && (!isStpAware || getPortInterfaceData(i)->isForwarding()))) {
            dispatch(frame->dup(), i);
        }
    }

    delete frame;
}

void TSNRelay::updateMACTable(cMessage* msg, MACAddress addr) {
    int outGate = macTable->getPortForAddress(addr);

    if (outGate == -1) {
        unsigned int arrivalGate = msg->getArrivalGate()->getIndex();
        macTable->updateTableWithAddress(arrivalGate, addr);
    }
}



