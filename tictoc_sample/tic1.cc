/*
 * tic1.cc
 *
 *  Created on: Nov 23, 2017
 *      Author: Deepak Paramashivam
 */

#include <string.h>
#include <omnetpp.h>
#define PARAMETER1 2

using namespace omnetpp;
class Txc1: public cSimpleModule {
private:
    cMessage *event;  // to introduce delay in each packet
    cMessage *timeOut; // to indicate 20 seconds limit
    cMessage *tictocMsg; // variable to remember the message until we send it back
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
    if (strcmp("tic", getName()) == 0) {
        cPacket *msg = new cPacket("512Kb");
        msg->addByteLength(1024 * 512);
        send(msg, "out");
    }
}
void Txc1::handleMessage(cMessage *msg) {
    /*If 20s timer has expired then dont send any further messages*/
    if (msg == timeOut) {
        flag = false;
    }
    /*If msg type is event then it is self posted event to induce delay
     * Hence Send out the message*/
    else if (msg == event) {
        if (flag) {
            send(tictocMsg, "out"); // send out the message
            tictocMsg = nullptr;
        }
    }
    /*Its a new message hence save the message and start the timer*/
    else {

        tictocMsg = msg;
        /*If tick then indice 1s delay*/
        if (strcmp("tic", getName()) == 0) {
            scheduleAt(simTime() + 1.0, event);
        }
        /*this is toc hence induce, has a delay of X seconds, where X is
         * exponentially distributed with parameter 1 */
        else {
            scheduleAt(simTime() + exponential(PARAMETER1), event);
        }
    }
}

