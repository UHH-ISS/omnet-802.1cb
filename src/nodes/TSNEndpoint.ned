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

import core4inet.applications.base.IApplication;
import core4inet.buffer.base.BGQueueBuffer;
import core4inet.linklayer.port.TSNPHYPort;
import core4inet.scheduler.ITTEScheduler;
import core4inet.synchronisation.base.ISync;
import core4inet.utilities.modules.CheckedBuffer;
import core4inet.linklayer.ethernet.base.BGEtherEncap;
import core4inet.services.avb.SRP.SRPTable;
import core4inet.services.avb.SRP.SRProtocol;
import core4inet.linklayer.ethernet.avb.SRPEtherEncap;
import core4inet.incoming.IEEE8021Qbv.IEEE8021QbvIncoming;

import inet.common.lifecycle.NodeStatus;
import inet.networklayer.common.InterfaceTable;

import ieee8021cb.frer.SequenceEncoder;
import ieee8021cb.routing.ISIS;
import ieee8021cb.spb.SPBEtherEncap;
import ieee8021cb.frer.StreamRecovery;

module TSNEndpoint
{
    parameters:
        @display("bgb=,;i=device/device");
        @networkNode;
        @labels(node,ethernet-node,frer-node);
        int numApps = default(0);
        int numBuffer = default(0);
        int numPorts = default(1);
        double hardware_delay @unit(s) = default(0us);
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        
        routing.macTableModule = "^.srpTable";
        routing.type = "host";
        
        int streamIdentificationFunction = default(0); // NullIdentifier: 0, source and VLAN: 1, destination and VLAN: 2

    gates:
        inout ethg @loose @labels(EtherFrame-conn);

    submodules:
        seqEnc: SequenceEncoder {
            @display("p=175,400");
        }

        status: NodeStatus {
            @display("p=100,50;is=n");
        }

        phy[numPorts]: TSNPHYPort {
            @display("p=100,450,c,50");
        }

        avbCTC: IEEE8021QbvIncoming {
            parameters:
                @display("p=500,250");
                hardware_delay = hardware_delay;
        }

        encap: SPBEtherEncap {
            @display("p=100,350");
        }

        sync: <default("DummySync")> like ISync {
            @display("p=300,50");
        }

        scheduler: <default("Scheduler")> like ITTEScheduler {
            @display("p=200,50");
        }

        app[numApps]: <> like IApplication {
            @display("p=400,50,row,100");
        }

        bgIn: BGQueueBuffer {
            @display("p=100,150");
        }

        bgOut: BGQueueBuffer {
            @display("p=200,150");
        }

        checkedBuffer[numBuffer]: CheckedBuffer {
            @display("p=600,150");
        }

        interfaceTable: InterfaceTable {
            @display("p=200,250");
        }

        srpTable: SRPTable {
            @display("p=400,250");
        }

        srpProtocol: SRProtocol {
            @display("p=300,250");
        }

        routing: ISIS {
            @display("p=300,350");
        }

       indvRec[numPorts]: StreamRecovery {
                @display("p=36,403");
            }

    connections allowunconnected:
        phy[0].phys <--> ethg;
        encap.lowerLayerOut --> seqEnc.seqEncIn;
        seqEnc.seqEncOut --> phy[0].upperLayerIn;
        phy[0].upperLayerOut --> indvRec[0].lowerLayerIn;
        indvRec[0].upperLayerOut --> encap.lowerLayerIn;

        encap.bgOut --> bgIn.in;
        bgOut.out --> encap.bgIn;

        srpProtocol.out --> encap.srpIn;
        srpProtocol.in <-- encap.srpOut;

        routing.relayOut --> encap.routingIn;
        routing.relayIn <-- encap.routingOut;
}
