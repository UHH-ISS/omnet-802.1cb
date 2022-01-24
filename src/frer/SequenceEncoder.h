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

#ifndef FRER_SEQUENCEENCODER_H_
#define FRER_SEQUENCEENCODER_H_

#include "StreamIdentification.h"
#include "core4inet/base/CoRE4INET_Defs.h"
#include "FREREtherFrame_m.h"

class SequenceEncoder : public cSimpleModule {

public:
    SequenceEncoder();
    virtual ~SequenceEncoder();

protected:
    void handleMessage(cMessage *msg) override;
    void initialize() override;

    int getSequenceNumber(EthernetFrameFRER*);

    int streamIdentificationFunction;
    std::map<L2Identifier, int> streamSequenceTable;
    //std::map<std::size_t, int> streamSequenceTable;
};

#endif /* FRER_SEQUENCEENCODER_H_ */
