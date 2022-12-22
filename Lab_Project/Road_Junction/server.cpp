#include "server.h"
#include "scheduler.h"
#include "event.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


Server :: Server () : a_(this), d_(this), j_(this), t_(this)
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
    myfile<<"Serial No , Queue No , Type , Length , Speed , Arrival , Depart, Service , Wait \n";
    myfile.close();
}

void Server::manage_junction_csv()
{
    ofstream myfile;
    myfile.open("Junction Status.csv");  //,std::ios::app
    myfile<<"Time , Junction , Duration , Queue 1 , Queue 2 , Queue 3 \n";
    myfile.close();
}

void Server::create_depart_csv()
{
    ofstream myfile;
    myfile.open("Departure Tracker.csv");  //,std::ios::app
    //myfile<<"Serial no , Time , Queue , Status \n";
    myfile<<"Turn, Serial No , Queue No , Type , Length , Speed , Arrival , Depart, Service , Wait \n";

    myfile.close();
}


void Server :: initialize ()
{
    status_ = 1;
    remaining_time = 300;
    agg_length = 0;


	itemArrived_ = 0;
	qProduct_ = 0;
	totalDelay_ = 0;
	lastEventTime_ = 0;

	vhc_cnt = 0;
	vhc_cnt_q1 = 0;
    vhc_cnt_q2 = 0;
	vhc_cnt_q3 = 0;

	create_vehic_csv();
	manage_junction_csv();
	create_depart_csv();

	//double t = exponential (arrivalMean_);
	//trace_ << "interarrival time " << t << endl;
	a_.activate(0);
	j_.activate(1);
	//t_.activate(2000);
}


void Server :: arrivalHandler ()
{
	//qProduct_ += queue_->length()*(Scheduler::now()-lastEventTime_);
	lastEventTime_ = Scheduler::now();
	lastArrivalTime_=Scheduler::now();

	Item* temp;

	itemArrived_++;

	temp = (Item*) malloc (sizeof(Item));
	temp->id_ = itemArrived_;


    int x = rand_g(add);

    // q1
    for(int i=0;i<=vehic+x;i++)
    {

        vehicles v1;
        v1.create_vehicles(vhc_cnt,1);

        v[1].push_back(v1);

        //v1.show_vehicles();
        v1.write_vehic_csv();
        //cout<<Scheduler::clock_<<" "<<Scheduler::now()<<endl;

        vhc_cnt++;
        vhc_cnt_q1++;
    }

    x = rand_g(add);

    // q2
    for(int i=0;i<=vehic+x;i++)
    {

        vehicles v1;
        v1.create_vehicles(vhc_cnt,2);

        v[2].push_back(v1);

        //v1.show_vehicles();
        //cout<<Scheduler::clock_<<" "<<Scheduler::now()<<endl;
        v1.write_vehic_csv();

        vhc_cnt++;
        vhc_cnt_q2++;
    }

    x = rand_g(add);

    // q3
    for(int i=0;i<=vehic+x;i++)
    {

        vehicles v1;
        v1.create_vehicles(vhc_cnt,3);

        v[3].push_back(v1);

        //v1.show_vehicles();
        //cout<<Scheduler::clock_<<" "<<Scheduler::now()<<endl;
        v1.write_vehic_csv();

        vhc_cnt++;
        vhc_cnt_q3++;
    }

    if(Scheduler::now() < 3005)
    {
        //a_.activate(200);
    }

    cout<<"Queue Length  "<<v[1].size()<<" "<<v[3].size()<<" "<<v[2].size()<<endl;
}

void Server :: junctionHandler ()
{

    if(v[status_].size()>0)
    {
        vehicles car = v[status_][0];

        int length_,speed_,arrival_,depart_;
        car.fetch_info(length_,speed_,arrival_,depart_);

        if( car.can_pass(remaining_time,agg_length) )
        {
            cout<<"YES "<<"     Car ID :"<<car.ret_id()<<"   Lane :"<<status_<<"    Time:  "<<Scheduler::now()<<" Type 2"<<endl;

            cout << status_ << " " << v[1].size() <<" "<< v[2].size() <<" "<< v[3].size() <<endl<<endl;
            int tm = agg_length/(int)speed_;
            d_.activate(Scheduler::now());
        }
    }


    status_ = 1+(status_++)%3;

    int x = 300;

    if(v[status_].size()>=50)       x += 100;

    remaining_time = x;
    agg_length = 100;

    //cout<<x<<" "<<Scheduler::now()<<" "<<status_<<endl;
    //v[status_].erase(v[status_].begin(),v[status_].begin()+50);

    ofstream myfile;
    myfile.open("Junction Status.csv",ios::app);
    myfile << Scheduler::now() << "," << status_ << "," << x <<","<< v[1].size() <<","<< v[2].size() <<","<< v[3].size() <<"\n";
    myfile.close();

    if(Scheduler::now() < 3005)
        j_.activate(x);
}


void Server :: departureHandler ()
{
    vehicles car = v[status_][0];

    int length_,speed_,arrival_,depart_;
    car.fetch_info(length_,speed_,arrival_,depart_);

    car.departing_info(Scheduler::now(), (agg_length+Junction_length)/(double)speed_);

    agg_length+=length_;
    car.write_depart_csv(status_);
    v[status_].erase(v[status_].begin());

    if(v[status_].size()>0)
    {
        vehicles car = v[status_][0];

        if( car.can_pass(remaining_time,agg_length))
        {
            cout<<"YES "<<"     Car ID :"<<car.ret_id()<<"   Lane :"<<status_<<"    Time:  "<<Scheduler::now()<<" Type 2"<<endl;
            cout << status_ << " " << v[1].size() <<" "<< v[2].size() <<" "<< v[3].size() <<endl<<endl;;
            int tm = agg_length/(double)speed_;
            d_.activate(Scheduler::now());
        }
    }


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
}

void Server :: terminationHandler ()
{
   a_.cancel();
   d_.cancel();
   j_.cancel();
}
