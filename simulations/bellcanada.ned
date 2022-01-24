package ieee8021cb.simulations;

import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth1G;
import inet.visualizer.common.PacketDropVisualizer;

import ieee8021cb.nodes.TSNEndpoint;
import ieee8021cb.nodes.TSNBridge;

import inet.common.scenario.ScenarioManager; 

network bellcanada
{
    parameters:
        @display("bgb=1000.0,500.0,white");

    submodules:
        scenarioManager: ScenarioManager;
        
        node1: TSNEndpoint;
        node2: TSNEndpoint;
        node3: TSNEndpoint;
        node4: TSNEndpoint;
        node5: TSNEndpoint;
        node6: TSNEndpoint;
        node7: TSNEndpoint;
        node8: TSNEndpoint;
        node9: TSNEndpoint;
        node10: TSNEndpoint;
        node11: TSNEndpoint {
            @display("p=741.70496,412.895");
        }
        node12: TSNEndpoint;
        node13: TSNEndpoint;
        node14: TSNEndpoint;
        node15: TSNEndpoint;
        node16: TSNEndpoint;
        node17: TSNEndpoint;
        node18: TSNEndpoint;
        node19: TSNEndpoint {
            @display("p=848.38,469.37");
        }
        node20: TSNEndpoint {
            @display("p=647.57996,453.055");
        }
        node21: TSNEndpoint;
        node22: TSNEndpoint;
        node23: TSNEndpoint;
        node24: TSNEndpoint;
        node25: TSNEndpoint;
        node26: TSNEndpoint;
        node27: TSNEndpoint;
        node28: TSNEndpoint;
        node29: TSNEndpoint;
        node30: TSNEndpoint;
        node31: TSNEndpoint;
        node32: TSNEndpoint;
        node33: TSNEndpoint;
        node34: TSNEndpoint;
        node35: TSNEndpoint;
        node36: TSNEndpoint;
        node37: TSNEndpoint;
        node38: TSNEndpoint;
        node39: TSNEndpoint;
        node40: TSNEndpoint;
        node41: TSNEndpoint;
        node42: TSNEndpoint;
        node43: TSNEndpoint;
        node44: TSNEndpoint;
        node45: TSNEndpoint;
        node46: TSNEndpoint;
        node47: TSNEndpoint;
        node48: TSNEndpoint;

        switch1: TSNBridge {
            gates:
                ethg[2];
        }
        switch2: TSNBridge {
            gates:
                ethg[3];
        }
        switch3: TSNBridge {
            gates:
                ethg[7];
        }
        switch4: TSNBridge {
            @display("p=107.93,105.42");
            gates:
                ethg[2];
        }
        switch5: TSNBridge {
            gates:
                ethg[5];
        }
        switch6: TSNBridge {
            gates:
                ethg[3];
        }
        switch7: TSNBridge {
            gates:
                ethg[3];
        }
        switch8: TSNBridge {
            gates:
                ethg[3];
        }
        switch9: TSNBridge {
            gates:
                ethg[5];
        }
        switch10: TSNBridge {
            gates:
                ethg[2];
        }
        switch11: TSNBridge {
            @display("p=865.94995,441.75998");
            gates:
                ethg[2];
        }
        switch12: TSNBridge {
            @display("p=119.225,328.81");
            gates:
                ethg[3];
        }
        switch13: TSNBridge {
            @display("p=753,328.81");
            gates:
                ethg[4];
        }
        switch14: TSNBridge {
            @display("p=312.495,320.025");
            gates:
                ethg[3];
        }
        switch15: TSNBridge {
            @display("p=638.795,320.025");
            gates:
                ethg[5];
        }
        switch16: TSNBridge {
            @display("p=97.89,266.06");
            gates:
                ethg[3];
        }
        switch17: TSNBridge {
            @display("p=322.535,469.37");
            gates:
                ethg[6];
        }
        switch18: TSNBridge {
            gates:
                ethg[3];
        }
        switch19: TSNBridge {
            @display("p=412.895,453.055");
            gates:
                ethg[3];
        }
        switch20: TSNBridge {
            @display("p=638.795,400.345");
            gates:
                ethg[3];
        }
        switch21: TSNBridge {
            @display("p=204.56499,328.81");
            gates:
                ethg[4];
        }
        switch22: TSNBridge {
            @display("p=254.765,469.37");
            gates:
                ethg[5];
        }
        switch23: TSNBridge {
            @display("p=48.945,328.81");
            gates:
                ethg[4];
        }
        switch24: TSNBridge {
            @display("p=254.765,303.71");
            gates:
                ethg[3];
        }
        switch25: TSNBridge {
            gates:
                ethg[3];
        }
        switch26: TSNBridge {
            @display("p=161.89499,469.37");
            gates:
                ethg[5];
        }
        switch27: TSNBridge {
            gates:
                ethg[2];
        }
        switch28: TSNBridge {
            gates:
                ethg[6];
        }
        switch29: TSNBridge {
            @display("p=613.695,229.665");
            gates:
                ethg[3];
        }
        switch30: TSNBridge {
            gates:
                ethg[5];
        }
        switch31: TSNBridge {
            gates:
                ethg[4];
        }
        switch32: TSNBridge {
            gates:
                ethg[6];
        }
        switch33: TSNBridge {
            gates:
                ethg[2];
        }
        switch34: TSNBridge {
            gates:
                ethg[6];
        }
        switch35: TSNBridge {
            gates:
                ethg[4];
        }
        switch36: TSNBridge {
            gates:
                ethg[4];
        }
        switch37: TSNBridge {
            gates:
                ethg[4];
        }
        switch38: TSNBridge {
            gates:
                ethg[3];
        }
        switch39: TSNBridge {
            gates:
                ethg[3];
        }
        switch40: TSNBridge {
            gates:
                ethg[3];
        }
        switch41: TSNBridge {
            gates:
                ethg[4];
        }
        switch42: TSNBridge {
            gates:
                ethg[3];
        }
        switch43: TSNBridge {
            @display("p=431.72,183.23");
            gates:
                ethg[3];
        }
        switch44: TSNBridge {
            gates:
                ethg[3];
        }
        switch45: TSNBridge {
            gates:
                ethg[3];
        }
        switch46: TSNBridge {
            gates:
                ethg[5];
        }
        switch47: TSNBridge {
            gates:
                ethg[3];
        }
        switch48: TSNBridge {
            gates:
                ethg[3];
        }

    connections:
        switch1.ethg[0] <--> Eth1G {  length = 30m; } <--> switch3.ethg[0];
        switch2.ethg[0] <--> Eth1G {  length = 30m; } <--> switch3.ethg[1];
        switch2.ethg[1] <--> Eth1G {  length = 30m; } <--> switch7.ethg[0];
        switch3.ethg[2] <--> Eth1G {  length = 30m; } <--> switch4.ethg[0];
        switch3.ethg[3] <--> Eth1G {  length = 30m; } <--> switch5.ethg[0];
        switch3.ethg[4] <--> Eth1G {  length = 30m; } <--> switch40.ethg[0];
        switch3.ethg[5] <--> Eth1G {  length = 30m; } <--> switch47.ethg[0];
        switch5.ethg[1] <--> Eth1G {  length = 30m; } <--> switch6.ethg[0];
        switch5.ethg[2] <--> Eth1G {  length = 30m; } <--> switch8.ethg[0];
        switch5.ethg[3] <--> Eth1G {  length = 30m; } <--> switch34.ethg[0];
        switch6.ethg[1] <--> Eth1G {  length = 30m; } <--> switch9.ethg[0];
        switch7.ethg[1] <--> Eth1G {  length = 30m; } <--> switch8.ethg[1];
        switch9.ethg[1] <--> Eth1G {  length = 30m; } <--> switch10.ethg[0];
        switch9.ethg[2] <--> Eth1G {  length = 30m; } <--> switch28.ethg[0];
        switch9.ethg[3] <--> Eth1G {  length = 30m; } <--> switch34.ethg[1];
        switch11.ethg[0] <--> Eth1G {  length = 30m; } <--> switch20.ethg[0];
        switch12.ethg[0] <--> Eth1G {  length = 30m; } <--> switch22.ethg[0];
        switch12.ethg[1] <--> Eth1G {  length = 30m; } <--> switch26.ethg[0];
        switch13.ethg[0] <--> Eth1G {  length = 30m; } <--> switch15.ethg[0];
        switch13.ethg[1] <--> Eth1G {  length = 30m; } <--> switch29.ethg[0];
        switch13.ethg[2] <--> Eth1G {  length = 30m; } <--> switch41.ethg[0];
        switch14.ethg[0] <--> Eth1G {  length = 30m; } <--> switch15.ethg[1];
        switch14.ethg[1] <--> Eth1G {  length = 30m; } <--> switch30.ethg[0];
        switch15.ethg[2] <--> Eth1G {  length = 30m; } <--> switch16.ethg[0];
        switch15.ethg[3] <--> Eth1G {  length = 30m; } <--> switch17.ethg[0];
        switch16.ethg[1] <--> Eth1G {  length = 30m; } <--> switch17.ethg[1];
        switch17.ethg[2] <--> Eth1G {  length = 30m; } <--> switch18.ethg[0];
        switch17.ethg[3] <--> Eth1G {  length = 30m; } <--> switch22.ethg[1];
        switch17.ethg[4] <--> Eth1G {  length = 30m; } <--> switch24.ethg[0];
        switch18.ethg[1] <--> Eth1G {  length = 30m; } <--> switch19.ethg[0];
        switch19.ethg[1] <--> Eth1G {  length = 30m; } <--> switch20.ethg[1];
        switch21.ethg[0] <--> Eth1G {  length = 30m; } <--> switch22.ethg[2];
        switch21.ethg[1] <--> Eth1G {  length = 30m; } <--> switch23.ethg[0];
        switch21.ethg[2] <--> Eth1G {  length = 30m; } <--> switch24.ethg[1];
        switch22.ethg[3] <--> Eth1G {  length = 30m; } <--> switch26.ethg[1];
        switch23.ethg[1] <--> Eth1G {  length = 30m; } <--> switch25.ethg[0];
        switch23.ethg[2] <--> Eth1G {  length = 30m; } <--> switch26.ethg[2];
        switch25.ethg[1] <--> Eth1G {  length = 30m; } <--> switch26.ethg[3];
        switch27.ethg[0] <--> Eth1G {  length = 30m; } <--> switch28.ethg[1];
        switch28.ethg[2] <--> Eth1G {  length = 30m; } <--> switch34.ethg[2];
        switch28.ethg[3] <--> Eth1G {  length = 30m; } <--> switch39.ethg[0];
        switch28.ethg[4] <--> Eth1G {  length = 30m; } <--> switch40.ethg[1];
        switch29.ethg[1] <--> Eth1G {  length = 30m; } <--> switch30.ethg[1];
        switch30.ethg[2] <--> Eth1G {  length = 30m; } <--> switch35.ethg[0];
        switch30.ethg[3] <--> Eth1G {  length = 30m; } <--> switch44.ethg[0];
        switch31.ethg[0] <--> Eth1G {  length = 30m; } <--> switch32.ethg[0];
        switch31.ethg[1] <--> Eth1G {  length = 30m; } <--> switch33.ethg[0];
        switch31.ethg[2] <--> Eth1G {  length = 30m; } <--> switch34.ethg[3];
        switch32.ethg[1] <--> Eth1G {  length = 30m; } <--> switch34.ethg[4];
        switch32.ethg[2] <--> Eth1G {  length = 30m; } <--> switch36.ethg[0];
        switch32.ethg[3] <--> Eth1G {  length = 30m; } <--> switch37.ethg[0];
        switch32.ethg[4] <--> Eth1G {  length = 30m; } <--> switch38.ethg[0];
        switch35.ethg[1] <--> Eth1G {  length = 30m; } <--> switch43.ethg[0];
        switch35.ethg[2] <--> Eth1G {  length = 30m; } <--> switch46.ethg[0];
        switch36.ethg[1] <--> Eth1G {  length = 30m; } <--> switch37.ethg[1];
        switch36.ethg[2] <--> Eth1G {  length = 30m; } <--> switch41.ethg[1];
        switch37.ethg[2] <--> Eth1G {  length = 30m; } <--> switch38.ethg[1];
        switch39.ethg[1] <--> Eth1G {  length = 30m; } <--> switch48.ethg[0];
        switch41.ethg[2] <--> Eth1G {  length = 30m; } <--> switch42.ethg[0];
        switch42.ethg[1] <--> Eth1G {  length = 30m; } <--> switch43.ethg[1];
        switch44.ethg[1] <--> Eth1G {  length = 30m; } <--> switch45.ethg[0];
        switch45.ethg[1] <--> Eth1G {  length = 30m; } <--> switch46.ethg[1];
        switch46.ethg[2] <--> Eth1G {  length = 30m; } <--> switch47.ethg[1];
        switch46.ethg[3] <--> Eth1G {  length = 30m; } <--> switch48.ethg[1];

        switch1.ethg[1] <--> Eth100M {  length = 10m; } <--> node1.ethg;
        switch2.ethg[2] <--> Eth100M {  length = 10m; } <--> node2.ethg;
        switch3.ethg[6] <--> Eth100M {  length = 10m; } <--> node3.ethg;
        switch4.ethg[1] <--> Eth100M {  length = 10m; } <--> node4.ethg;
        switch5.ethg[4] <--> Eth100M {  length = 10m; } <--> node5.ethg;
        switch6.ethg[2] <--> Eth100M {  length = 10m; } <--> node6.ethg;
        switch7.ethg[2] <--> Eth100M {  length = 10m; } <--> node7.ethg;
        switch8.ethg[2] <--> Eth100M {  length = 10m; } <--> node8.ethg;
        switch9.ethg[4] <--> Eth100M {  length = 10m; } <--> node9.ethg;
        switch10.ethg[1] <--> Eth100M {  length = 10m; } <--> node10.ethg;
        switch11.ethg[1] <--> Eth100M {  length = 10m; } <--> node11.ethg;
        switch12.ethg[2] <--> Eth100M {  length = 10m; } <--> node12.ethg;
        switch13.ethg[3] <--> Eth100M {  length = 10m; } <--> node13.ethg;
        switch14.ethg[2] <--> Eth100M {  length = 10m; } <--> node14.ethg;
        switch15.ethg[4] <--> Eth100M {  length = 10m; } <--> node15.ethg;
        switch16.ethg[2] <--> Eth100M {  length = 10m; } <--> node16.ethg;
        switch17.ethg[5] <--> Eth100M {  length = 10m; } <--> node17.ethg;
        switch18.ethg[2] <--> Eth100M {  length = 10m; } <--> node18.ethg;
        switch19.ethg[2] <--> Eth100M {  length = 10m; } <--> node19.ethg;
        switch20.ethg[2] <--> Eth100M {  length = 10m; } <--> node20.ethg;
        switch21.ethg[3] <--> Eth100M {  length = 10m; } <--> node21.ethg;
        switch22.ethg[4] <--> Eth100M {  length = 10m; } <--> node22.ethg;
        switch23.ethg[3] <--> Eth100M {  length = 10m; } <--> node23.ethg;
        switch24.ethg[2] <--> Eth100M {  length = 10m; } <--> node24.ethg;
        switch25.ethg[2] <--> Eth100M {  length = 10m; } <--> node25.ethg;
        switch26.ethg[4] <--> Eth100M {  length = 10m; } <--> node26.ethg;
        switch27.ethg[1] <--> Eth100M {  length = 10m; } <--> node27.ethg;
        switch28.ethg[5] <--> Eth100M {  length = 10m; } <--> node28.ethg;
        switch29.ethg[2] <--> Eth100M {  length = 10m; } <--> node29.ethg;
        switch30.ethg[4] <--> Eth100M {  length = 10m; } <--> node30.ethg;
        switch31.ethg[3] <--> Eth100M {  length = 10m; } <--> node31.ethg;
        switch32.ethg[5] <--> Eth100M {  length = 10m; } <--> node32.ethg;
        switch33.ethg[1] <--> Eth100M {  length = 10m; } <--> node33.ethg;
        switch34.ethg[5] <--> Eth100M {  length = 10m; } <--> node34.ethg;
        switch35.ethg[3] <--> Eth100M {  length = 10m; } <--> node35.ethg;
        switch36.ethg[3] <--> Eth100M {  length = 10m; } <--> node36.ethg;
        switch37.ethg[3] <--> Eth100M {  length = 10m; } <--> node37.ethg;
        switch38.ethg[2] <--> Eth100M {  length = 10m; } <--> node38.ethg;
        switch39.ethg[2] <--> Eth100M {  length = 10m; } <--> node39.ethg;
        switch40.ethg[2] <--> Eth100M {  length = 10m; } <--> node40.ethg;
        switch41.ethg[3] <--> Eth100M {  length = 10m; } <--> node41.ethg;
        switch42.ethg[2] <--> Eth100M {  length = 10m; } <--> node42.ethg;
        switch43.ethg[2] <--> Eth100M {  length = 10m; } <--> node43.ethg;
        switch44.ethg[2] <--> Eth100M {  length = 10m; } <--> node44.ethg;
        switch45.ethg[2] <--> Eth100M {  length = 10m; } <--> node45.ethg;
        switch46.ethg[4] <--> Eth100M {  length = 10m; } <--> node46.ethg;
        switch47.ethg[2] <--> Eth100M {  length = 10m; } <--> node47.ethg;
        switch48.ethg[2] <--> Eth100M {  length = 10m; } <--> node48.ethg;

}
