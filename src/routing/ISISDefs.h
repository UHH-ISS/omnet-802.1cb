/*
 * ISISDefs.h
 *
 *  Created on: May 27, 2020
 *      Author: doganalp
 */

#ifndef ROUTING_ISISDEFS_H_
#define ROUTING_ISISDEFS_H_

#define ISIS_ETHER_PACKET 0x88cc

#include "utils/EthernetNodeMeta.h"

class ISISEthernetNodeMeta : public EthernetNodeMeta {

    public:
        ISISEthernetNodeMeta() { id = -1; isid = -1; vid = -1; cost = 0; type = NONE; };
        ISISEthernetNodeMeta(MACAddress addr) { id = -1; isid = -1; vid = -1; cost = 0; type = HOST; this->addr = addr;};
        ISISEthernetNodeMeta(MACAddress addr, int vid) {id = -1; isid = -1; vid = vid; cost = 0; type = HOST; this->addr = addr;};
        ISISEthernetNodeMeta(const ISISEthernetNodeMeta &ienm) { *this = ienm; };

        string str() const { return to_string(isid) + to_string(vid) + to_string(type) + addr.str(); }

        void operator=(const ISISEthernetNodeMeta &ienm ) {
            isid = ienm.isid;
            vid = ienm.vid;
            cost = ienm.cost;
            type = ienm.type;
            addr = ienm.addr;
            id = ienm.id;
         };

        int getISID() {
            return isid;
        };

        void setISID(int i) {
            isid = i;
        };

    protected:
        int isid;
};

typedef std::map<ISISEthernetNodeMeta, std::vector<ISISEthernetNodeMeta>> ISISDatabase;

const MACAddress ISIS_MULTICAST = inet::MACAddress("01:80:C2:00:00:03");

#endif /* ROUTING_ISISDEFS_H_ */
