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
network frer_small
{
    parameters:
        @display("bgb=556.51495,206.36499,white");
    submodules:
        node1: TSNEndpoint {
            @display("p=39,70");
        }

        node2: TSNEndpoint {
            @display("p=398,38");
        }

        node3: TSNEndpoint {
            @display("p=398,102");
        }
        node4: TSNEndpoint {
            @display("p=200.405,172.09499");
        }

        switch1: TSNBridge {
            parameters:
                @display("p=147,70");
            gates:
                ethg[3];
        }
        switch2: TSNBridge {
            parameters:
                @display("p=245,70");
            gates:
                ethg[4];
        }
        switch3: TSNBridge {
            parameters:
                @display("p=200.405,119.94499");
            gates:
                ethg[3];
        }
        
    connections:
        node1.ethg <--> Eth100M {  length = 20m; } <--> switch1.ethg[0];
        switch1.ethg[1] <--> Eth1G {  length = 10m; } <--> switch2.ethg[0];
        node2.ethg <--> Eth100M {  length = 10m; } <--> switch2.ethg[1];
        node3.ethg <--> Eth100M {  length = 5m; } <--> switch2.ethg[2];

        switch1.ethg[2] <--> Eth1G {  length = 10m; } <--> switch3.ethg[0];
        switch2.ethg[3] <--> Eth1G {  length = 10m; } <--> switch3.ethg[1];
        node4.ethg <--> Eth100M {  length = 10m; } <--> switch3.ethg[2];
}
