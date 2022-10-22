//#include "facility.h"
#include "server.h"

Facility::Facility(double arrivalMean, double serviceMean)
{
    Server :: itemArrived_ = 0;
    server1 = new Server(1, this);
    server2 = new Server(2, this);

    server1 -> arrivalMean() = arrivalMean;
    server1->departureMean() = serviceMean;
    server2 -> arrivalMean() = arrivalMean;
    server2->departureMean() = serviceMean;
}

void Facility::initialize()
{
    createTraceFile();

    server1 -> initialize();
    server2 -> initialize();
    server1 -> triggerArrival();
}

void Facility:: arrivalHandler()
{
    if(server1 -> queueLength() < server2 -> queueLength()) {
        server1 -> serverArrivalHandler();
    } else {
        server2 -> serverArrivalHandler();
    }
}

void Facility :: createTraceFile () {
	trace_.open ("trace.out", ios::out);
	if (!trace_) {
		cout << "cannot open the trace file.\n";
	}
	trace_<< "trace file for the simulation" << endl;
	trace_ << "format of the file" << endl;
	trace_ << "<event> <server id> <time> <item id> <server status> <queue size>" << endl << endl;
}

void Facility::report()
{
    server1 -> report();
    server2 -> report();
}

