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

package ieee8021cb.nodes;

import core4inet.linklayer.port.TSNPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.linklayer.beHandling.avb.relay.SRPRelay;
import core4inet.incoming.IEEE8021Qbv.IEEE8021QbvIncoming;

import inet.linklayer.contract.IMACAddressTable;
import inet.linklayer.contract.IMACRelayUnit;
import inet.common.lifecycle.NodeStatus;
import inet.networklayer.common.InterfaceTable;

import ieee8021cb.frer.StreamRecovery;
import ieee8021cb.frer.EnhancedStreamRecovery;
import ieee8021cb.frer.LatentErrorDetection;
import ieee8021cb.spb.SPB;
import ieee8021cb.routing.ISIS;
import ieee8021cb.frer.TSNRelay;
import ieee8021cb.spb.PathSelectionTable;
import ieee8021cb.spb.ExtendedMACTable;

module TSNBridge
{
    parameters:
        @display("bgb=,;i=block/switch");
        @networkNode;
        @labels(node,ethernet-node);
        // Optional: Number of Buffers with Incoming Module for TT and RC traffic 
        // (When not manually declared in own deriving .ned file)
        int numBuffer = default(0);
        // Forwardingdelay of the device hardware
        double hardware_delay @unit(s) = default(8us);
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        
        int streamIdentificationFunction = default(0); // NullIdentifier: 0, source and VLAN: 1, destination and VLAN: 2

    gates:
        // Physical ports of the switch
        inout ethg[] @loose @labels(EtherFrame-conn);

    types:
        channel ProcessingDelay extends ned.DelayChannel
        {
        }

    submodules:
        // Keeps track of the status of network node (up, down, etc.)
        status: NodeStatus {
            @display("p=100,50;is=n");
        }

        // Implementation of the forwarding part
        beswitch: TSNRelay {
            parameters:
                @display("p=100,327");
            gates:
                ifIn[sizeof(ethg)];
                ifOut[sizeof(ethg)];
        }

        //The mac table associated with the beswitch
        macTable: ExtendedMACTable  {
            @display("p=100,250");
        }

        // Holds interface names
        interfaceTable: InterfaceTable {
            @display("p=200,250");
        }

        // Physical ports of the switch
        phy[sizeof(ethg)]: TSNPHYPort {
            parameters:
                @display("p=100,450,row,100");
                //For the switch it is necessary to have promiscuous mode enabled
                promiscuous = true;
        }

        indvRec[sizeof(ethg)]: StreamRecovery {
            @display("p=176,393");
        }

        seqRec: EnhancedStreamRecovery {
            parameters:
                recoveryType = 1;
                streamRecoveryFunction = 0;
                sequenceWindowSize = 5;
                @display("p=261,327");
        }

        spb: SPB {
            @display("p=709,69");
        }
        routing: ISIS {
            @display("p=30,250");
        }
        // AVB critical traffic control
        avbCTC: IEEE8021QbvIncoming {
            parameters:
                @display("p=500,250");
                hardware_delay = hardware_delay;
        }

        // Sync module for synchronisation of the scheduler
        sync: <default("DummySync")> like ISync {
            parameters:
                @display("p=300,50");
        }

        // Scheduler for the device
        scheduler: <default("Scheduler")> like ITTEScheduler {
            parameters:
                @display("p=200,50");
        }

        // Buffers with Incoming Module for TT and RC traffic (optional)
        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=600,150");
        }

        // Stream Reservation Protocol table
        srpTable: SRPTable {
            @display("p=400,250");
        }

        // Stream Reservation Protocol implementation
        srpProtocol: SRProtocol {
            @display("p=300,250");
        }

		pst: PathSelectionTable {};
		
		led: LatentErrorDetection {};

    connections:
        for i=0..sizeof(ethg)-1 {
            phy[i].phys <--> ethg[i];
            phy[i].upperLayerIn <-- indvRec[i].lowerLayerOut;
            phy[i].upperLayerOut --> indvRec[i].lowerLayerIn;

            indvRec[i].upperLayerOut --> ProcessingDelay {  delay = (hardware_delay/2); } --> beswitch.ifIn[i];
            indvRec[i].upperLayerIn <-- ProcessingDelay {  delay = (hardware_delay/2); } <-- beswitch.ifOut[i];
        }

        srpProtocol.out --> beswitch.srpIn;
        srpProtocol.in <-- beswitch.srpOut;

        seqRec.upperLayerOut --> beswitch.seqRecIn;
        seqRec.lowerLayerIn <-- beswitch.seqRecOut;

        routing.relayIn <-- beswitch.routingOut;
        routing.relayOut --> beswitch.routingIn;
}
