/*
 * test.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: Deepak Paramashivam
 */

#include <string.h>
#include <omnetpp.h>
#define PARAMETER1 1

using namespace omnetpp;
class Txc1: public cSimpleModule {
private:
    cMessage *event;  // to introduce delay in each packet
    cMessage *timeOut; // to indicate 20 seconds limit
    bool flag; //To indicate the timeout

protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc1);

void Txc1::initialize() {
    event = new cMessage("event"); //To induce time delay
    timeOut = new cMessage("timeOut"); //To stop after 20 sec
    flag = true; //To stop after 20 sec
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.
    // Am I Tic or Toc?
    scheduleAt(simTime() + 20.0, timeOut);

    /*Initially Tic will start sending the packet of length 512Kb*/
    if (strcmp("S1", getName()) == 0) {
        cPacket *msg = new cPacket("512Kb");
        msg->addByteLength(1024 * 512);
        send(msg, "out");
    }
}
void Txc1::handleMessage(cMessage *msg) {
    /*If 20s timer is expired then dont process the packets*/
    if(!flag)
    {
        return;
    }
    /*If timer expired event occures then set the flag to false which will prevent further processing of messages*/
    if (msg == timeOut) {
        flag = false;
    }
    /*If packet is received in S1 then send out with 1 sec delay*/
    if (strcmp("S1", getName()) == 0) {
        sendDelayed(msg, 1, "out");
    }
    /*If packet is received in S" then send out with exponential(PARAMETER1) sec delay*/
    else
    {
        sendDelayed(msg, exponential(PARAMETER1), "out");
    }

}




