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

#include "StreamRecovery.h"
#include "inet/common/ModuleAccess.h"

Define_Module(StreamRecovery);

StreamRecovery::StreamRecovery() {
    // TODO Auto-generated constructor stub

}

StreamRecovery::~StreamRecovery() {
    // TODO Auto-generated destructor stub
}

void StreamRecovery::initialize() {

    streamRecoveryFunction = par("streamRecoveryFunction");
    streamIdentificationFunction = this->getParentModule()->par("streamIdentificationFunction");
    sequenceWindowSize = par("sequenceWindowSize");
    recoveryType = par("recoveryType");

    if(recoveryType == 1) // stream recovery
        ledModule = getModuleFromPar<LatentErrorDetection>(par("ledModule"), this);
}

void StreamRecovery::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("lowerLayerIn"))
    {
        EthernetIIFrame* frame = check_and_cast<EthernetIIFrame*>(msg);
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
        } else {
            send(msg, "upperLayerOut");
        }
    } else if(msg && msg->arrivedOn("upperLayerIn")) {
        // Forward packets coming from upper layers directly
        EthernetIIFrame* frame = check_and_cast<EthernetIIFrame*>(msg);
        send(msg, "lowerLayerOut");
    }
}

void StreamRecovery::handleFrameFRER(EthernetFrameFRER *frame) {

    L2Identifier key = StreamIdentification::getStreamIdentifier(frame, streamIdentificationFunction);

    bool isAccepted = true;

    int sequenceNumber = frame->getSequenceNumber();
    //std::cout << "Sequence number: " << sequenceNumber << endl;

    if(ledModule)
        ledModule->updateStreamSequence(key, sequenceNumber);

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

        if(streamIdentificationFunction == 1)
            streamVectorTable[key] = std::vector<int> (2 * sequenceWindowSize + 1, 0);
    }

    if(isAccepted) {
        streamMaxSeqTable[key] = sequenceNumber;
        send(frame, "upperLayerOut");
    } else {
        std::cout << "Discarded" << endl;
        delete frame;
    }
}

bool StreamRecovery::matchRecovery(L2Identifier key, int seq) {

    int streamMaxSeq = streamMaxSeqTable[key];
    return streamMaxSeq < seq;
}

bool StreamRecovery::vectorRecovery(L2Identifier key, int seq) {

    int streamMaxSeq = streamMaxSeqTable[key];
    std::vector<int> streamVector = streamVectorTable[key];
    // TODO: Implement its logic here
    return true;
}






