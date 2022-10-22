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
    Server :: itemArrived_ ++;
    Item* temp;
    temp = (Item*) malloc(sizeof(Item));
    temp -> id_ = Server :: itemArrived_;
    temp -> arrivalTime = Scheduler :: now();

    if(server1 -> status() == 0)
    {
        server1 -> serverArrivalHandler(temp);
    }
    else if(server2 -> status() == 0)
    {
        server2 -> serverArrivalHandler(temp);
    }
    else if(server1 -> queueLength() <= server2 -> queueLength())
    {
        server1 -> serverArrivalHandler(temp);
    }
    else
    {
        server2 -> serverArrivalHandler(temp);
    }
}

void Facility :: departureHandler(Server* server)
{
    server -> serverDepartureHandler();
    // jockeying
    if(server1 -> queueLength() - server2 -> queueLength() > 1)
    {
        // server 1 to server 2
        Server :: jockeying(server1, server2);
    }
    else if (server2 -> queueLength() - server1 -> queueLength() > 1)
    {
        // server 2 to server 1
        Server :: jockeying(server2, server1);
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

