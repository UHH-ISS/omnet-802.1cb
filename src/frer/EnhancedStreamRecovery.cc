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
#define FRER_ETHER_PACKET 0xf1c1

#include "EnhancedStreamRecovery.h"
#include "FRERConfiguration_m.h"
#include "FRERConfiguration_m.h"
#include "../utils/L2Identifier.h"

Define_Module(EnhancedStreamRecovery);

EnhancedStreamRecovery::EnhancedStreamRecovery() {
    // TODO Auto-generated constructor stub

}

EnhancedStreamRecovery::~EnhancedStreamRecovery() {
    // TODO Auto-generated destructor stub
}

void EnhancedStreamRecovery::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("lowerLayerIn"))
    {
        if(EthernetIIFrame* frame = dynamic_cast<EthernetIIFrame*>(msg)) {
            // Check if the frame has R-TAG
            if(frame->getEtherType() == FRER_ETHER_PACKET) {
                EthernetFrameFRER* frame = check_and_cast<EthernetFrameFRER*>(msg);

                switch(recoveryType) {
                    case 0:
                        break;
                    case 1:
                        frame->setEtherType(0x8100);
                        break;
                }

                handleFrameFRER(frame);
            }
        } else if (FRERConfiguration* config = dynamic_cast<FRERConfiguration*>(msg)) {
            L2Identifier key = config->getKey();
            maxKnotTable[key] = config->getKnot();
        }
        else {
            send(msg, "upperLayerOut");
        }
    } else if(msg && msg->arrivedOn("upperLayerIn")) {
        // Forward packets coming from upper layers directly
        EthernetIIFrame* frame = check_and_cast<EthernetIIFrame*>(msg);
        send(msg, "lowerLayerOut");
    }
}

void EnhancedStreamRecovery::handleFrameFRER(EthernetFrameFRER *frame) {

    L2Identifier key = StreamIdentification::getStreamIdentifier(frame, streamIdentificationFunction);

    bool isAccepted = true;

    int sequenceNumber = frame->getSequenceNumber();
    //std::cout << "Sequence number: " << sequenceNumber << endl;

    if(ledModule) {
        ledModule->updateStreamSequence(key, sequenceNumber);
    }

    if(streamMaxSeqTable.find(key) != streamMaxSeqTable.end()) {
        switch(streamIdentificationFunction) {
            case 0:
                isAccepted = matchRecovery(key, sequenceNumber);
                break;
            case 1:
                isAccepted = vectorRecovery(key, sequenceNumber);
                break;
        }
    } else {
        // Prepare values for the new stream
        streamMaxSeqTable[key] = sequenceNumber;

        if(maxKnotTable.find(key) == maxKnotTable.end()) {
            maxKnotTable[key] = 0;
        }

        currentKnotTable[key] =  maxKnotTable[key];

        if(streamIdentificationFunction == 1)
            streamVectorTable[key] = std::vector<int> (2 * sequenceWindowSize + 1, 0);
    }

    // give one more chance
    if(!isAccepted && currentKnotTable[key] > 0) {
        currentKnotTable[key]--;
        isAccepted = true;
    }

    if(isAccepted) {
        streamMaxSeqTable[key] = sequenceNumber;
        send(frame, "upperLayerOut");
    } else {
        std::cout << "Discarded" << endl;
        delete frame;
    }
}
