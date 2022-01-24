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

simple StreamRecovery {
    
    parameters:
        @class(StreamRecovery);
        
        int recoveryType = default(0); // IndividualRecovery: 0, SequenceRecovery: 1
        int streamRecoveryFunction = default(0); // MatchRecoveryFunction: 0, VectorRecoveryFunction: 1
        int sequenceWindowSize = default(5);
        
        string ledModule = default("^.led");
        
    gates:  
        input upperLayerIn @loose;
        output upperLayerOut @loose;
        
        input lowerLayerIn @loose;
        output lowerLayerOut @loose;
}