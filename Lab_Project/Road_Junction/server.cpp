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

void Server::show_result ()
{
    cout<<endl<<endl;
    cout<<"Signals  = "<<signals_<<endl;
    cout<<"Departed = "<<totalDepartures_<<endl;
    cout<<"Wait     = "<<totalWait_<<endl;
    cout<<"Service  = "<<totalService_<<endl;
    cout<<endl<<endl;

    for(int i=0;i<totalDepartures_;i++)
    {
        //cout<<a[totalDepartures_]<<' ';
    }
}

void Server :: initialize ()
{
    status_ = 1;
    remaining_time = 300;
    agg_length = 0;


    signals_ = 1;
    totalDepartures_ = 0;
    totalWait_ = 0;
    totalService_ = 0;

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
	j_.activate(0);
	//t_.activate(2000);
}


void Server :: arrivalHandler ()
{
	//qProduct_ += queue_->length()*(Scheduler::now()-lastEventTime_);
	//lastEventTime_ = Scheduler::now();
	//lastArrivalTime_=Scheduler::now();

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

    if(Scheduler::now() < 10005)
    {
        a_.activate(100);
    }

    cout<<"Queue Length  "<<v[1].size()<<" "<<v[3].size()<<" "<<v[2].size()<<endl;
}

void Server :: junctionHandler ()
{

    if(v[status_].size()>0)
    {
        vehicles car = v[status_][0];

        int length_,speed_,arrival_,depart_;
        car.fetch_info(length_,speed_,arrival_);


        if( car.can_pass(remaining_time,agg_length) )
        {
            cout<<"YES "<<"     Car ID :"<<car.ret_id()<<"   Lane :"<<status_<<"    Time:  "<<Scheduler::now()<<" Type 1"<<endl;

            cout << status_ << " " << v[1].size() <<" "<< v[2].size() <<" "<< v[3].size() <<endl<<endl;
            int tm = agg_length/(int)speed_;
            d_.activate(0);
        }
    }


    status_ = 1+(status_++)%3;

    int x = 200;

    if(v[status_].size()>=30)       x += 100;

    remaining_time = x;
    agg_length = 0;
    signals_++;

    //cout<<x<<" "<<Scheduler::now()<<" "<<status_<<endl;
    //v[status_].erase(v[status_].begin(),v[status_].begin()+50);

    ofstream myfile;
    myfile.open("Junction Status.csv",ios::app);
    myfile << Scheduler::now() << "," << status_ << "," << x <<","<< v[1].size() <<","<< v[2].size() <<","<< v[3].size() <<"\n";
    myfile.close();

    if(Scheduler::now() < 10005)
        j_.activate(x);
}


void Server :: departureHandler ()
{

    if(v[status_].size()>0)
    {
        vehicles car = v[status_][0];

        int length_,speed_,arrival_,depart_,serve_,wait_;

        car.fetch_info(length_,speed_,arrival_);

        serve_ = (agg_length+Junction_length)/(double)speed_ ;
        car.departing_info(serve_);

        ofstream myfile;
    myfile.open("Wait.csv",ios::app);  //,std::ios::app
    myfile<< Scheduler::now() << "," << arrival_ <<endl;// "," << wait_<<endl;
    myfile.close();

        agg_length+=length_;
        wait_ = Scheduler::now() - arrival_;
        car.write_depart_csv(status_);
        totalDepartures_++;


        totalWait_ += wait_;
        totalService_ += serve_ ;

        v[status_].erase(v[status_].begin());

        if(v[status_].size()>0)
        {
            vehicles car1 = v[status_][0];

            if(car1.can_pass(remaining_time,agg_length))
            {
                cout<<"YES "<<"     Car ID :"<<car1.ret_id()<<"   Lane :"<<status_<<"    Time:  "<<Scheduler::now()<<" Type 2"<<endl;
                cout << status_ << " " << v[1].size() <<" "<< v[2].size() <<" "<< v[3].size() <<endl<<endl;;
                int tm = agg_length/(double)speed_;
                d_.activate(0);
            }
        }

    }

    else return;
}

void Server :: terminationHandler ()
{
   a_.cancel();
   d_.cancel();
   j_.cancel();
}
