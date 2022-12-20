#include "server.h"
#include "scheduler.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


Server :: Server () : a_(this), d_(this)
{
	queue_ = new Queue ();
}

double Server :: exponential(double mean)
{

	double r = (double)rand()/RAND_MAX;

	double ex = -mean * log (r);

	return ex;
}

int Server::rand_g(int n)
{
    return (rand())%n;
}

void Server::create_vehic_csv()
{
    ofstream myfile;
    myfile.open("Vehicle List.csv");  //,std::ios::app
    myfile<<"Serial No , Queue No , Type , Length , Speed , Arrival , Depart, Wait \n";
    myfile.close();
}


void Server :: initialize ()
{
	status_ = 0;

	itemArrived_ = 0;
	qProduct_ = 0;
	totalDelay_ = 0;
	lastEventTime_ = 0;

	vhc_cnt = 0;
	vhc_cnt_q1 = 0;
    vhc_cnt_q2 = 0;
	vhc_cnt_q3 = 0;

	create_vehic_csv();

	//double t = exponential (arrivalMean_);
	//trace_ << "interarrival time " << t << endl;
	a_.activate(0);
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

void
Server :: arrivalHandler ()
{
	//qProduct_ += queue_->length()*(Scheduler::now()-lastEventTime_);
	lastEventTime_ = Scheduler::now();
	lastArrivalTime_=Scheduler::now();

	Item* temp;

	itemArrived_++;

	temp = (Item*) malloc (sizeof(Item));
	temp->id_ = itemArrived_;


    int x = rand_g(10);

    // q1
    for(int i=0;i<=15+x;i++)
    {

        vehicles v1;
        v1.create_vehicles(vhc_cnt,1);

        v[1].push_back(v1);

        v1.show_vehicles();
        v1.write_vehic_csv();

        vhc_cnt++;
        vhc_cnt_q1++;
    }

    x = rand_g(10);

    // q2
    for(int i=0;i<=15+x;i++)
    {

        vehicles v1;
        v1.create_vehicles(vhc_cnt,2);

        v[2].push_back(v1);

        v1.show_vehicles();
        v1.write_vehic_csv();

        vhc_cnt++;
        vhc_cnt_q2++;
    }

    x = rand_g(10);

    // q3
    for(int i=0;i<=15+x;i++)
    {

        vehicles v1;
        v1.create_vehicles(vhc_cnt,3);

        v[3].push_back(v1);

        v1.show_vehicles();
        v1.write_vehic_csv();

        vhc_cnt++;
        vhc_cnt_q3++;
    }

    if(Scheduler::now() < 1005)
    {
        //a_.activate(lastEventTime_ + 200);
        a_.activate(Scheduler::now() + 200);
    }

    //cout<<v[1].size()<<" "<<v[3].size()<<" "<<v[2].size()<<endl;
}

void
Server :: departureHandler () {
	qProduct_ += queue_->length()*(Scheduler::now()-lastEventTime_);
	totalDelay_ += Scheduler::now()-lastArrivalTime_;
	lastEventTime_ = Scheduler::now();

	// write to the trace file
	if (queue_->length() > 0) {
		trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
	} else {
		trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << endl;
	}

	if (queue_->length() > 0) {
		itemInService_ = queue_->deque ();

		// write to the trace file
		trace_ << "s\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

		double t = exponential (departureMean_);
		//trace_ << "\tservice time = " << t << endl;
		d_.activate (t);
	} else {
		status () = 0;
		itemInService_ = 0;
	}
}

