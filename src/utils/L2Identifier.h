/*
 * L2Identifier.h
 *
 *  Created on: Jun 2, 2020
 *      Author: doganalp
 */

#ifndef UTILS_L2IDENTIFIER_H_
#define UTILS_L2IDENTIFIER_H_

#include "inet/linklayer/common/MACAddress.h"

using inet::MACAddress;

// Can be used for various stream identification methods
struct L2Identifier {
    MACAddress addr;
    int vid;

    L2Identifier(MACAddress a, int v) {addr = a; vid = v;}
    L2Identifier() {}
    friend bool operator<(const L2Identifier& l, const L2Identifier& r)
    {
        return l.addr < r.addr;
    }
    bool operator==(const L2Identifier &l2id ) const {
        return addr == l2id.addr && vid == l2id.vid;
     };

    bool operator!=(const L2Identifier &l2id ) const {
        return addr != l2id.addr || vid != l2id.vid;
     };

    void operator=(const L2Identifier &l2id ) {
        vid = l2id.vid;
        addr = l2id.addr;
     };

};

struct L3Identifier {

};

// Currenlty not used
namespace std
{
    template<> struct hash<L2Identifier>
    {
        std::size_t operator()(L2Identifier &mid)
        {
            std::size_t h1 = std::hash<std::string>{}(mid.addr.str());
            std::size_t h2 = std::hash<int>{}(mid.vid);
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
}
#endif /* UTILS_L2IDENTIFIER_H_ */
