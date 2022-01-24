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

#ifndef FRER_STREAMRECOVERY_H_
#define FRER_STREAMRECOVERY_H_

#include "core4inet/base/CoRE4INET_Defs.h"
#include "FREREtherFrame_m.h"
#include "StreamIdentification.h"
#include "LatentErrorDetection.h"

class StreamRecovery : public cSimpleModule {
public:
    StreamRecovery();
    virtual ~StreamRecovery();

protected:

    bool matchRecovery(L2Identifier, int);
    bool vectorRecovery(L2Identifier, int);
    void handleMessage(cMessage *msg) override;
    void initialize() override;

    void handleFrameFRER(EthernetFrameFRER *frame);

    int sequenceWindowSize;
    int streamRecoveryFunction;
    int streamIdentificationFunction;
    int recoveryType;

    std::map<L2Identifier, std::vector<int>> streamVectorTable;
    std::map<L2Identifier, int> streamMaxSeqTable;



    LatentErrorDetection* ledModule = nullptr;
};

#endif /* FRER_STREAMRECOVERY_H_ */
