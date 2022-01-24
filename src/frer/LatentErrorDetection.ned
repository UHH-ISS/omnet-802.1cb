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

module LatentErrorDetection {
    
    parameters:
        @class(LatentErrorDetection);
        
     	@signal[receivedDuplicates](type="long");
     	//@signal[expectedPacketCount](type="long");
        @statistic[receivedDuplicates](title="Number of received duplicate packets (including the original one)"; source="receivedDuplicates"; record=vector,stats; interpolationmode=none);
        //@statistic[expectedPacketCount](title="Expected number of duplicate packets"; source="expectedPacketCount"; record=vector,stats; interpolationmode=none);

        int splitFactor = default(2);
        int sequenceWindowSize = default(5);
    
    // TODO: It should be connected to some gates to send ErrorDetectionFRER packets
}