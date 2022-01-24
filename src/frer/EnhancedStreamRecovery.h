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

#ifndef FRER_ENHANCEDSTREAMRECOVERY_H_
#define FRER_ENHANCEDSTREAMRECOVERY_H_

#include "StreamRecovery.h"

class EnhancedStreamRecovery : public StreamRecovery {
public:
    EnhancedStreamRecovery();
    virtual ~EnhancedStreamRecovery();

protected:

    std::map<L2Identifier, int> maxKnotTable;
    std::map<L2Identifier, int> currentKnotTable;

    void handleMessage(cMessage *msg);
    void handleFrameFRER(EthernetFrameFRER *frame);
};

#endif /* FRER_ENHANCEDSTREAMRECOVERY_H_ */
