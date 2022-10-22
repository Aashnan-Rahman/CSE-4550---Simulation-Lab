#include "server.h"
#include "scheduler.h"
#include "facility.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

int Server::totalCustomerServed_ = 0;
double Server::timeLastEvent_ = 0.0;
double Server::areaQueue_ = 0.0;
double Server::totalQueueDelay_ = 0.0;
double Server::totalSystemDelay_ = 0.0;

Server :: Server (int id, Facility* facility) : a_(this), d_(this), id_(id), facility_(facility)
{
	queue_ = new Queue ();
}


double Server :: exponential(double mean) {

	double r = (double)rand()/RAND_MAX;

	double ex = -mean * log (r);

	return ex;
}

void Server :: initialize ()
{
	status_ = 0;
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

void Server :: triggerArrival ()
{
    double t = exponential(arrivalMean_);
    facility_->trace() << "\tinterarrival time = " << t << endl;
	a_.activate(t);
}

void Server :: serverArrivalHandler (Item* item)
{
    facility_->trace() << "a\t" << id_ << "\t" << Scheduler::now () << "\t" << item->id_ << "\t" << status_ << "\t" << facility_->queueLength() << endl;
    updateStat();


    status() = 1;
    facility_->trace() << "s\t" << id_ << "\t" << Scheduler::now () << "\t" << item->id_ << "\t" << status_ << "\t" << facility_->queueLength() << endl;
    itemInService_ = item;
    queueDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
    totalQueueDelay_ += queueDelay_;

    double t = exponential (departureMean_);
    facility_->trace() << "\tservice time = " << t << endl;
    d_.activate(t);


    // If there 100 items, no more arrivals scheduled (simulation limit)
    if(item-> id_ < 100) {
        triggerArrival();
    }
}

void Server :: serverDepartureHandler (Item* item)
{
	updateStat();

	totalCustomerServed_++;
	systemDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
	totalSystemDelay_ += systemDelay_;


	if(item){
        facility_->trace() << "d\t" << id_ << "\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << facility_->queueLength() << endl;

        itemInService_ = item;

        facility_->trace() << "s\t" << id_ << "\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << facility_->queueLength() << endl;

        queueDelay_ = Scheduler::now() - itemInService_ -> arrivalTime;
        totalQueueDelay_ += queueDelay_;

		double t = exponential(departureMean_);
		facility_->trace() << "\tservice time = " << t << endl;
		d_.activate(t);
	} else {
	    status() = 0;
	    facility_->trace() << "d\t" << id_ << "\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << facility_->queueLength() << endl;
		itemInService_ = 0;
	}
}

void Server :: facilityArrivalHandler ()
{
    facility_ -> arrivalHandler();
}

void Server:: facilityDepartureHandler ()
{
    facility_ -> departureHandler(this);
}


void Server :: updateStat()
{
	double durationSinceLastEvent;

	durationSinceLastEvent = Scheduler::now() - timeLastEvent_;
	timeLastEvent_ = Scheduler::now();

	areaQueue() += durationSinceLastEvent*(facility_->queueLength());
}

void Server :: report()
{
	ofstream report_;
	string filename = "report.csv";
	report_.open (filename, std::ios_base::app);
	if(!report_) {
		cout<<"cannot open report file.\n";
		return;
	}

//	report_<<"Report of the simulation"<<endl;
//	report_<<"Traffic intensity: "<< arrivalMean()/departureMean() <<endl;
//	report_<<"Average Queue Delay: "<<(totalQueueDelay()/totalCustomerServed())<<endl;
//	report_<<"Average Queue Length: "<<(areaQueue()/Scheduler::now())<<endl;
//	report_<<"Average System Delay: "<<(totalSystemDelay()/totalCustomerServed())<<endl;
//
//	report_<<" "<<endl<<endl;
//
//	report_<<"Total Queue Delay = "<< totalQueueDelay() <<endl;
//	report_<<"Total Customer Served = "<< totalCustomerServed() <<endl<<endl;
//
//	report_<<"Area Queue = "<< areaQueue() <<endl;
//	report_<<"Now Time = "<< Scheduler::now() <<endl<<endl;
//
//	report_<<"Total Delay = "<< totalSystemDelay() <<endl;
//	report_<<"Total Customer Served = "<< totalCustomerServed() <<endl<<endl;

    report_ << arrivalMean() << "," << arrivalMean()/departureMean() << "," << totalQueueDelay()/totalCustomerServed() << "," << (areaQueue()/Scheduler::now()) << "," << (totalSystemDelay()/totalCustomerServed()) << endl;
    report_.close();
}


