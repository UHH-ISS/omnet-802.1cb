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

#include "ExtendedMACTable.h"

ExtendedMACTable::ExtendedMACTable() {
    // TODO Auto-generated constructor stub
}

Define_Module(ExtendedMACTable);

ExtendedMACTable::~ExtendedMACTable() {
    // TODO Auto-generated destructor stub
}

inet::MACAddress ExtendedMACTable::getAddressByPort(int port) {

    inet::MACAddressTable::AddressTable at = *addressTable;

    inet::MACAddress addr;

    for(auto it = at.begin(); it != at.end(); it++) {
        if((it->second).portno == port)
            addr = it->first;
    }

    return addr;
}
