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

#include "../routing/ISISDefs.h"
#include "inet/linklayer/common/MACAddress.h"

#include "routing/ISIS_m.h"
#include "SPBEtherEncap.h"

Define_Module(SPBEtherEncap);


SPBEtherEncap::SPBEtherEncap() {
    // TODO Auto-generated constructor stub
}

SPBEtherEncap::~SPBEtherEncap() {
    // TODO Auto-generated destructor stub
}

void SPBEtherEncap::handleMessage(cMessage *msg)
{
    if (msg && msg->arrivedOn("lowerLayerIn")) {
        inet::EtherFrame * frame = check_and_cast<inet::EtherFrame*>(msg);
        if (frame->getDest() == ISIS_MULTICAST) {
            // Ignore ISIS announcements
            delete msg;
        } else {
            SRPEtherEncap::handleMessage(msg);
        }
    } else {
        if(msg->arrivedOn("routingIn")) {
            // IS-IS packets are already extended EthernetFrames. No more processing required
           send(msg, "lowerLayerOut");
        } else {
            SRPEtherEncap::handleMessage(msg);
        }
    }
}
