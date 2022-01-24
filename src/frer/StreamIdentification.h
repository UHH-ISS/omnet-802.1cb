/*
 * StreamIdentification.h
 *
 *  Created on: Apr 15, 2020
 *      Author: doganalp
 */

#include "utils/L2Identifier.h"
#include "inet/linklayer/common/MACAddress.h"
#include "FREREtherFrame_m.h"

using namespace inet;

#ifndef FRER_STREAMIDENTIFICATION_H_
#define FRER_STREAMIDENTIFICATION_H_

class StreamIdentification {
    public:
        StreamIdentification();
        virtual ~StreamIdentification();

        static L2Identifier NullIdentifier(EthernetFrameFRER*);
        static L2Identifier sourceAndVLAN(EthernetFrameFRER*);
        static L2Identifier destinationAndVLAN(EthernetFrameFRER*);
        static L2Identifier getStreamIdentifier(EthernetFrameFRER*, int);
};

#endif /* FRER_STREAMIDENTIFICATION_H_ */
