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

#ifndef ROUTING_ISIS_H_
#define ROUTING_ISIS_H_

#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/MACAddress.h"
#include "inet/common/INETDefs.h"

#include "ISIS_m.h"
#include "ISISDefs.h"

using namespace inet;
using std::string;

class ISIS : public cSimpleModule
{
    public:
        ISIS();
        virtual ~ISIS();

        NodeType type = HOST;

        ISISEthernetNodeMeta getMetaInfo() {
            return meta;
        }

        ISISDatabase getDatabase() {
            return db;
        }

        MACAddress getAddress() {
            return meta.getAddress();
        }

        int getISID() {
            return meta.getISID();
        }

        int getID() {
            return meta.getID();
        }

        ISISEthernetNodeMeta isDirectEndpoint(MACAddress);

    protected:
        ISISDatabase db;
        ISISEthernetNodeMeta meta;

        static int hostID;
        static int bridgeID;

        double updatePeriod;
        double dbAnnouncePeriod;

        virtual void initialize(int) override;
        virtual int numInitStages() const { return 5; };
        void handleMessage(cMessage *msg) override;

        void sendHello();
        void sendDbAnnounce(MACAddress destAddress = ISIS_MULTICAST);

        void handleHello(const ISISPacket*);
        void handleDbAnnounce(const ISISPacket*);

        string serializeDatabase();
        string getDbSignature();
};

#endif /* ROUTING_ISIS_H_ */
