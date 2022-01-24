 /*
 * EthernetNodeMeta.h
 *
 *  Created on: Jun 29, 2019
 *      Author: doganalp
 */

#ifndef NODE_EthernetNodeMeta_H_
#define NODE_EthernetNodeMeta_H_

#include "inet/linklayer/common/MACAddress.h"

using namespace inet;
using std::string;
using std::to_string;

enum NodeType {
    HOST = 0,
    CORE_BRIDGE,
    EDGE_BRIDGE,
    NONE
};

class EthernetNodeMeta {

    public:
        EthernetNodeMeta() {id = -1; vid = -1; cost = 0; type = NONE; };
        EthernetNodeMeta(MACAddress addr) {id = -1; vid = -1; cost = 0; type = HOST; this->addr = addr;};
        EthernetNodeMeta(MACAddress addr, int vid) {id = -1; vid = vid; cost = 0; type = HOST; this->addr = addr;};
        EthernetNodeMeta(const EthernetNodeMeta &enm) { *this = enm; };

        string str() const { return to_string(vid) + to_string(type) + addr.str(); }

        void operator=(const EthernetNodeMeta &enm ) {
            vid = enm.vid;
            cost = enm.cost;
            type = enm.type;
            addr = enm.addr;
            id = enm.id;
         };

        bool operator<(const EthernetNodeMeta &enm ) const {
            return id < enm.id;
         };

        bool operator==(const EthernetNodeMeta &enm ) const {
            return addr == enm.addr && vid == enm.vid && id == enm.id;
         };

        bool operator!=(const EthernetNodeMeta &enm ) const {
            return addr != enm.addr || vid != enm.vid || id != enm.id;
         };

        int getVID() {
            return vid;
        };

        void setVID(int v) {
            vid = v;
        };

        int getID() {
            return id;
        };

        void setID(int i) {
            id = i;
        };

        int getCost() {
            return cost;
        };

        void setCost(int c) {
            cost = c;
        };

        NodeType getType() {
            return type;
        };

        void setType(NodeType t) {
            type = t;
        };

        MACAddress getAddress() {
            return addr;
        };

        void setAddress(MACAddress a) {
            addr = a;
        };

    protected:
        int id; // unique ID
        int vid;    // VLAN ID
        double cost;
        NodeType type;
        MACAddress addr;
};


#endif /* NODE_EthernetNodeMeta_H_ */
