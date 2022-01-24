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

package ieee8021cb.simulations.custom_scenarios;

import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.visualizer.common.PacketDropVisualizer;

import ieee8021cb.nodes.TSNEndpoint;
import ieee8021cb.nodes.TSNBridge;

//
// Small sample network with three hosts and one switch that shows how to 
// configure the IEEE 802.1Q Model. Configuration in omnetpp.ini
// - 80ns Tick length
//
network frer_large
{
    parameters:
        @display("bgb=856.51495,406.36499,white");
    submodules:
        node1: TSNEndpoint {
            @display("p=199,168");
        }

        node2: TSNEndpoint {
            @display("p=620,130");
        }

        node3: TSNEndpoint {
            @display("p=620,200");
        }
        node4: TSNEndpoint {
            @display("p=360,296");
        }

        node5: TSNEndpoint {
            @display("p=366,40");
        }

        node6: TSNEndpoint {
            @display("p=444,40");
        }

        node7: TSNEndpoint {
            @display("p=529,79");
        }

        node8: TSNEndpoint {
            @display("p=529,258");
        }

        switch1: TSNBridge {
            parameters:
                @display("p=290,168");
            gates:
                ethg[4];
        }
        switch2: TSNBridge {
            parameters:
                @display("p=405,168");
            gates:
                ethg[3];
        }
        switch3: TSNBridge {
            parameters:
                @display("p=360,232");
            gates:
                ethg[3];
        }
        switch4: TSNBridge {
            parameters:
                @display("p=366,104");
            gates:
                ethg[3];
        }
        switch5: TSNBridge {
            parameters:
                @display("p=444,104");
            gates:
                ethg[3];
        }
        switch6: TSNBridge {
            parameters:
                @display("p=529,168");
            gates:
                ethg[6];
        }

    connections:
        switch1.ethg[0] <--> Eth1G {  length = 20m; } <--> switch2.ethg[0];
        switch1.ethg[1] <--> Eth1G {  length = 20m; } <--> switch3.ethg[0];
        switch1.ethg[2] <--> Eth1G {  length = 20m; } <--> switch4.ethg[0];
        switch1.ethg[3] <--> Eth100M {  length = 10m; } <--> node1.ethg;

        switch2.ethg[1] <--> Eth1G {  length = 20m; } <--> switch3.ethg[1];
        switch2.ethg[2] <--> Eth1G {  length = 20m; } <--> switch6.ethg[0];

        switch3.ethg[2] <--> Eth100M {  length = 10m; } <--> node4.ethg;

        switch4.ethg[1] <--> Eth1G {  length = 20m; } <--> switch5.ethg[0];
        switch4.ethg[2] <--> Eth100M {  length = 10m; } <--> node5.ethg;

        switch5.ethg[1] <--> Eth1G {  length = 20m; } <--> switch6.ethg[1];
        switch5.ethg[2] <--> Eth100M {  length = 10m; } <--> node6.ethg;

        switch6.ethg[2] <--> Eth100M {  length = 10m; } <--> node2.ethg;
        switch6.ethg[3] <--> Eth100M {  length = 10m; } <--> node3.ethg;
        switch6.ethg[4] <--> Eth100M {  length = 10m; } <--> node7.ethg;
        switch6.ethg[5] <--> Eth100M {  length = 10m; } <--> node8.ethg;
}
