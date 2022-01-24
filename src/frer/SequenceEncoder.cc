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

#include "SequenceEncoder.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "core4inet/linklayer/ethernet/base/EtherFrameWithQTag_m.h"

#include <time.h>
#include <random>

#define FRER_ETHER_PACKET 0xf1c1
#define VLAN_TAGGED_PACKET 0x8100

using namespace inet;

Define_Module(SequenceEncoder);

SequenceEncoder::SequenceEncoder() {
    // TODO Auto-generated constructor stub
}

SequenceEncoder::~SequenceEncoder() {
    // TODO Auto-generated destructor stub
}

void SequenceEncoder::initialize() {
    srand(time(0));
    streamIdentificationFunction = this->getParentModule()->par("streamIdentificationFunction");
}

void SequenceEncoder::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("seqEncIn"))
    {
        EthernetIIFrame* frame = check_and_cast<EthernetIIFrame*>(msg);

        // Check if the frame has VLAN tag
        if(frame->getEtherType() == VLAN_TAGGED_PACKET) {

            EthernetIIFrameWithQTag* qframe = check_and_cast<EthernetIIFrameWithQTag*>(msg);
            EthernetFrameFRER *fframe = new EthernetFrameFRER;

            int sequenceNumber = getSequenceNumber(fframe);

            fframe->setSequenceNumber(sequenceNumber);
            fframe->setDest(qframe->getDest());
            fframe->setSrc(qframe->getSrc());
            //fframe->setEtherType(qframe->getEtherType());
            fframe->setEtherType(FRER_ETHER_PACKET);
            fframe->encapsulate(qframe->decapsulate());
            fframe->setDe(qframe->getDe());
            fframe->setPcp(qframe->getPcp());
            fframe->setVID(qframe->getVID());
            fframe->setByteLength(qframe->getByteLength() + 4);

            delete msg;
            send(fframe, "seqEncOut");
        }
        else {
            send(msg, "seqEncOut");
        }
    }
}

int SequenceEncoder::getSequenceNumber(EthernetFrameFRER *frame) {

    L2Identifier key = StreamIdentification::getStreamIdentifier(frame, streamIdentificationFunction);

    auto it = streamSequenceTable.find(key);

    if(it != streamSequenceTable.end()) {
        // Increment if an existing stream
        int prob = rand() % 100;

        // Send duplicate sometimes
        //if(prob < 30) {
        //    return it->second;
        //}

        return ++it->second;
    } else {
        // Random sequence generation
        // TODO: ensure it is not used before
        streamSequenceTable[key] = rand();
        return streamSequenceTable[key];
    }
}









