/*
 * StreamIdentification.cpp
 *
 *  Created on: Apr 15, 2020
 *      Author: doganalp
 */

#include "StreamIdentification.h"

StreamIdentification::StreamIdentification() {
    // TODO Auto-generated constructor stub
}

StreamIdentification::~StreamIdentification() {
    // TODO Auto-generated destructor stub
}

L2Identifier StreamIdentification::getStreamIdentifier(EthernetFrameFRER* frame, int sid_function) {

    switch(sid_function) {
        case 0:
            return NullIdentifier(frame);
        case 1:
            return sourceAndVLAN(frame);
        case 2:
            return destinationAndVLAN(frame);
        default:
            return NullIdentifier(frame);
    }
}

L2Identifier StreamIdentification::NullIdentifier(EthernetFrameFRER* frame) {
    return destinationAndVLAN(frame);
}

L2Identifier StreamIdentification::sourceAndVLAN(EthernetFrameFRER* frame) {
    return L2Identifier(frame->getSrc(), frame->getVID());
}

L2Identifier StreamIdentification::destinationAndVLAN(EthernetFrameFRER* frame) {
    return L2Identifier(frame->getDest(), frame->getVID());
}
