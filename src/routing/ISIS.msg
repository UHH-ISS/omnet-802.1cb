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

cplusplus {{
#include "ISISDefs.h"
#include "inet/linklayer/ethernet/EtherFrame.h"
}}

class noncobject ISISEthernetNodeMeta;
class noncobject ISISDatabase;
class EthernetIIFrame;

enum ISISMsgType {
	UPDATE = 0;
	HELLO = 1;
	HELLO_RESP = 2;
	DB_ANNOUNCE = 3;
}

packet ISISTimer {
    int type @enum(ISISMsgType);
}

packet updateTimer extends ISISTimer {
	type = ISISMsgType::UPDATE;
}

packet dbAnnounceTimer extends ISISTimer {
	type = ISISMsgType::DB_ANNOUNCE;
}

packet ISISPacket extends EthernetIIFrame {
	int type @enum(ISISMsgType);
	etherType = 0x88cc;
	ISISEthernetNodeMeta meta;
} 

packet helloPacket extends ISISPacket {
	type = ISISMsgType::HELLO;
}

packet helloRespPacket extends ISISPacket {
	type = ISISMsgType::HELLO_RESP;
}

packet dbAnnouncePacket extends ISISPacket {
	type = ISISMsgType::DB_ANNOUNCE;
	string dbSignature;
	ISISDatabase database;
}



