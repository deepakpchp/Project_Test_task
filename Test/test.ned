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
simple Txc1
{
    gates:
        input in;
        output out;
}
//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Test1
{
    @display("bgb=485,384");
    submodules:
        S1: Txc1 {
            @display("color=green;p=57,173;b=100,100,rect,#CA3939;t=S1,,blue");
        }

        S2: Txc1 {

            @display("p=384,167;b=100,100,oval,#008000,,0;t=S2,,blue");
        }
    connections:
        S1.out --> {  datarate = 8Mbps;@display("ls=green"); } --> S2.in;
        S1.in <-- {  datarate = 8Mbps;@display("ls=red"); } <-- S2.out;
}
