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

#ifndef IEEE8021AQ_SPB_H_
#define IEEE8021AQ_SPB_H_

#include "../routing/ISIS.h"
#include "inet/linklayer/common/MACAddress.h"
#include "inet/linklayer/configurator/Ieee8021dInterfaceData.h"
#include "inet/linklayer/ethernet/switch/IMACAddressTable.h"
#include "inet/networklayer/common/InterfaceTable.h"
#include "inet/common/lifecycle/OperationalBase.h"

#include "PathSelectionTable.h"

using namespace inet;
using std::vector;

typedef vector<vector<int>> BridgeMap;
typedef vector<vector<int>> PathIDVector;

class SPB : public cSimpleModule {
    public:
        SPB();
        virtual ~SPB();

        ISIS *isisModule = nullptr;
        PathSelectionTable *pstModule = nullptr;

        BridgeMap isidMap;
        vector<ISISEthernetNodeMeta> isidGroup;

        void updateMap();
        void printMap();
        Path findShortestPath(MACAddress destAddr);
        PathVector findAllPaths(MACAddress destAddr);
        PathVector findAllPathsForStream(L2Identifier key, MACAddress);
        void findAllPathsUtil(int srcIndex, int destIndex, bool visited[], int path[], int &index, PathIDVector &paths);
        vector<ISISEthernetNodeMeta> getNextHops(L2Identifier key, MACAddress prevHop, MACAddress destAddr);
        void parsePaths(std::string);
        int findKnotForStream(L2Identifier key, MACAddress destAddr);

    protected:
        void initialize(int) override;
        void handleMessage(cMessage *msg) override;
        virtual int numInitStages() const { return 6; };

};


#endif /* IEEE8021AQ_SPB_H_ */
