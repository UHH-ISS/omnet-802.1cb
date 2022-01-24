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

package ieee8021cb.frer;

import core4inet.linklayer.beHandling.avb.relay.SRPRelay;

module TSNRelay extends SRPRelay
{
    parameters:
        @class(TSNRelay);
        string spbModule = default("^.spb");
        string pstModule = default("^.pst");
        
       	// TODO: Move that parameter to StreamSplitting module
        int splitFactor = default(2);
      
        bool isSourceBridge = default(false);
        
       	@signal[expectedPacketCount](type="long");
        @statistic[expectedPacketCount](title="Expected number of duplicate packets"; source="expectedPacketCount"; record=vector,stats; interpolationmode=none);    
    gates:
        input routingIn;
        output routingOut;
        
        input seqRecIn;
        output seqRecOut;
}
