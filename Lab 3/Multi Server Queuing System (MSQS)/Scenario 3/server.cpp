#include "server.h"
#include "scheduler.h"
#include "server.h"
#include "facility.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

//int Server::totalCustomerServed_ = 0;
//double Server::timeLastEvent_ = 0.0;
//double Server::areaQueue_ = 0.0;
//double Server::totalQueueDelay_ = 0.0;
//double Server::totalSystemDelay_ = 0.0;

Server :: Server (int id, Facility* facility) : a_(this), d_(this), id_(id), facility_(facility)
{
	queue_ = new Queue ();
	itemArrived_ = 0;
}


double Server :: exponential(double mean) {

	double r = (double)rand()/RAND_MAX;

	double ex = -mean * log (r);

	return ex;
}

void Server :: initialize ()
{
    status_ = 0;
	itemArrived_ = 0;
	timeLastEvent_ = 0;

	areaQueue_ = 0;

	totalQueueDelay_ = 0.0;
	totalSystemDelay_ = 0.0;
	totalCustomerServed_ = 0;

	//double t = exponential (arrivalMean_);
	//trace_ << "interarrival time " << t << endl;
	//a_.activate (t);
}

//void Server :: createTraceFile ()
//{
//	trace_.open ("trace.out", ios::out);
//	if (!trace_) {
//		cout << "cannot open the trace file.\n";
//	}
//	trace_<< "trace file for the simulation" << endl;
//	trace_ << "format of the file" << endl;
//	trace_ << "<event> <time> <item id> <server status> <queue size>" << endl << endl;
//}

void Server :: jockeying (Server* from_, Server* to_)
{
    Item* jockeyingItem = from_ -> queue_ -> removeLast();
    to_ -> jockeyingHandler(jockeyingItem);
}

void Server :: triggerArrival ()
{
    double t = exponential(arrivalMean_);
    facility_->trace() << "\tinterarrival time = " << t << endl;
	a_.activate(t);
}

void Server :: facilityArrivalHandler ()
{
    facility_ -> arrivalHandler();
}

void Server :: serverArrivalHandler (Item* temp)
{

    updateStat();

    if(status () == 0)
    {
        facility_->trace() << "a\t" << id_ << "\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    	status() = 1;
    	facility_->trace() << "s\t" << id_ << "\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    	itemInService_ = temp;
    	queueDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
    	totalQueueDelay_ += queueDelay_;

    	double t = exponential (departureMean_);
    	facility_->trace() << "\tservice time = " << t << endl;
    	d_.activate(t);
    }
    else
    {
    	queue_ -> enque(temp);
    	facility_->trace() << "a\t" << id_ << "\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    }

    // If there 100 items, no more arrivals scheduled (simulation limit)
    if(temp-> id_ < 100)
    {
        triggerArrival();
    }
}

void Server :: jockeyingHandler (Item* temp)
{
    updateStat();

    if(status () == 0)
    {
        facility_->trace() << "j\t" << id_ << "\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    	status() = 1;
    	facility_->trace() << "s\t" << id_ << "\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    	itemInService_ = temp;
    	queueDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
    	totalQueueDelay_ += queueDelay_;

    	double t = exponential (departureMean_);
    	facility_->trace() << "\tservice time = " << t << endl;
    	d_.activate(t);
    }
    else
    {
    	queue_ -> enque(temp);
    	facility_->trace() << "j\t" << id_ << "\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    }
}

void Server :: facilityDepartureHandler ()
{
    facility_ -> departureHandler(this);
}

void
Server :: serverDepartureHandler ()
{

    if (queue_->length() > 0)
    {
		facility_->trace() << "d\t" << id_ << "\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
	}
	else
    {
		facility_->trace() << "d\t" << id_ << "\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << endl;
	}

	updateStat();

	totalCustomerServed_++;
	systemDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
	totalSystemDelay_ += systemDelay_;


	if(queue_->length() > 0)
    {
        itemInService_ = queue_->deque();

        // jockey handler

        facility_->trace() << "s\t" << id_ << "\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

        queueDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
        totalQueueDelay_ += queueDelay_;

		double t = exponential(departureMean_);
		facility_->trace() << "\tservice time = " << t << endl;
		d_.activate(t);
	}
	else
    {
		status() = 0;
		itemInService_ = 0;
	}
}

void Server :: updateStat()
{
	double durationSinceLastEvent;

	durationSinceLastEvent = Scheduler::now() - timeLastEvent_;
	timeLastEvent_ = Scheduler::now();

	areaQueue() += durationSinceLastEvent*(queue_->length());
}


void Server :: report()
{
	ofstream report_;
	string filename = "report" + to_string(id_) + ".csv";
	report_.open (filename, ios::app);
	if(!report_) {
		cout<<"cannot open report file.\n";
		return;
	}
//	report_<<"Report of the simulation"<<endl;
//	report_<<"Traffic intensity: "<<arrivalMean()/departureMean()<<endl;
//	report_<<"Average Queue Delay: "<<(totalQueueDelay()/totalCustomerServed())<<endl;
//	report_<<"Average Queue Length: "<<(areaQueue()/Scheduler::now())<<endl;
//	report_<<"Average System Delay: "<<(totalSystemDelay()/totalCustomerServed())<<endl;

    report_ << arrivalMean() << "," << arrivalMean()/departureMean() << "," << totalQueueDelay()/totalCustomerServed() << "," << (areaQueue()/Scheduler::now()) << "," << (totalSystemDelay()/totalCustomerServed()) << endl;
    report_.close();
}


//void
//Server :: arrivalHandler () {
//	qProduct_ += queue_->length()*(Scheduler::now()-lastEventTime_);
//	lastEventTime_ = Scheduler::now();
//	lastArrivalTime_=Scheduler::now();
//
//	Item* temp;
//
//	itemArrived_++;
//	temp = (Item*) malloc (sizeof(Item));
//	temp->id_ = itemArrived_;
//
//	if (status () == 0) {
//		// write to the trace file
//		status() = 1;
//		trace_ << "s\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
//		status() = 1;
//		itemInService_ = temp;
//
//		double t = exponential (departureMean_);
//		//trace_ << "\tservice time = " << t << endl;
//		d_.activate (t);
//	} else {
//		queue_->enque(temp);
//	}
//
//	if (temp->id_ < 100) {
//		double t = exponential (arrivalMean_);
//		//trace_ << "\tinterarrival time = " << t << endl;
//		a_.activate (t);
//	}
//
//	trace_ << "a\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
//}
//
//void
//Server :: departureHandler () {
//	qProduct_ += queue_->length()*(Scheduler::now()-lastEventTime_);
//	totalDelay_ += Scheduler::now()-lastArrivalTime_;
//	lastEventTime_ = Scheduler::now();
//
//	// write to the trace file
//	if (queue_->length() > 0) {
//		trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
//	} else {
//		trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << endl;
//	}
//
//	if (queue_->length() > 0) {
//		itemInService_ = queue_->deque ();
//
//		// write to the trace file
//		trace_ << "s\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
//
//		double t = exponential (departureMean_);
//		//trace_ << "\tservice time = " << t << endl;
//		d_.activate (t);
//	} else {
//		status () = 0;
//		itemInService_ = 0;
//	}
//}

