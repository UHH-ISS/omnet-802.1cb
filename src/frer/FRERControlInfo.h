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

#ifndef FRER_FRERCONTROLINFO_H_
#define FRER_FRERCONTROLINFO_H_

#include "core4inet/base/CoRE4INET_Defs.h"
#include "inet/linklayer/common/MACAddress.h"

class FRERControlInfo : public cObject {
public:
    FRERControlInfo();
    virtual ~FRERControlInfo();

    inet::MACAddress addr;
    int port;

    void setAddress(inet::MACAddress a) {addr = a;};
    inet::MACAddress getAddress() {return addr;};

    void setPort(int p) {port = p;};
    int getPort() {return port;}
};

#endif /* FRER_FRERCONTROLINFO_H_ */
