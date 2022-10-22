#include "system.h"

System::System(double arrivalMean, double serviceMean)
{
    server1 = new Server(1, this);
    server2 = new Server(2, this);
    queue_ = new Queue();

    createTraceFile();

    server1 -> arrivalMean() = arrivalMean;
    server1->departureMean() = serviceMean;
    server2 -> arrivalMean() = arrivalMean;
    server2->departureMean() = serviceMean;
}

void System::initialize()
{
    itemArrived_ = 0;

    server1 -> initialize();
    server2 -> initialize();
    server1 -> triggerArrival();
}

void System :: createTraceFile ()
{
	trace_.open ("trace.out", ios::out);
	if (!trace_) {
		cout << "cannot open the trace file.\n";
	}
	trace_<< "trace file for the simulation" << endl;
	trace_ << "format of the file" << endl;
	trace_ << "<event> <server id> <time> <item id> <server status> <queue size>" << endl << endl;
}

void System:: arrivalHandler()
{
    itemArrived_ ++;
    Item* temp;
    temp = (Item*) malloc(sizeof(Item));
    temp -> id_ = itemArrived_;
    temp -> arrivalTime = Scheduler :: now();


    if(server1 -> status () == 0) { // server is idle during arrival
    	server1 -> ServerArrivalHandler(temp);
    } else if(server2 -> status () == 0) {
        server2 -> ServerArrivalHandler(temp);
    }else {
    	queue_ -> enque(temp);
    	server1 -> triggerArrival();
    }
}

void System:: departureHandler(Server* server) {
    if(queueLength() > 0){
        Item* temp = queue_->deque();
        server -> ServerDepartureHandler(temp);
	} else {
		server -> ServerDepartureHandler(nullptr);
	}
}

void System::report()
{
    server1 -> report();
}

