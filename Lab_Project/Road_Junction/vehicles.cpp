#include "vehicles.h"
#include "scheduler.h"

int cnt = 0;

vehicles::vehicles()
{
    //ctor
}

int vehicles::rand_g(int n)
{
    return (rand())%n;
}

int vehicles::vehicle_sl()
{
    int temp = cnt;
    cnt++;

    return temp;
}

void vehicles::create_vehicles(int no,int q)
{
    int n = rand_g(3);
    serial_no = no;
    queue_no  = q;

    depart_t = 0;
    waiting_t = 0;
    service_t = 0;
    arrival_t = Scheduler::now();


    if(n == 0)
    {
        type = "small";
        length = 7 + rand_g(3);
        speed =  40 + rand_g(15);
    }

    else if(n == 1)
    {
        type = "medium";
        length = 10 + rand_g(3);
        speed =  25 + rand_g(10);
    }

    else
    {
        type = "large";
        length = 20 + rand_g(2);
        speed =  10 + rand_g(5);
    }

}

void vehicles::write_vehic_csv()
{
    ofstream myfile;
    myfile.open("Vehicle List.csv",ios::app);
    myfile << serial_no << "," << queue_no << "," << type <<","<< length <<","<< speed <<","<< arrival_t <<","<< depart_t << "," << service_t << "," <<waiting_t <<"\n";
    myfile.close();
}

void vehicles::write_depart_csv(int turn_)
{
    ofstream myfile;
    myfile.open("Departure Tracker.csv",ios::app);
    myfile << turn_ << "," << serial_no << "," << queue_no << "," << type <<","<< length <<","<< speed <<","<< arrival_t <<","<< depart_t << "," << service_t << "," <<waiting_t <<"\n";
    myfile.close();
}

void vehicles::show_vehicles()
{
    cout<<"Serial No :  "<<serial_no<<endl;
    cout<<"Queue No  :  "<<queue_no<<endl;
    cout<<"Type      :  "<<type<<endl;
    cout<<"Length    :  "<<length<<endl;
    cout<<"Speed     :  "<<speed<<endl;
    cout<<"Arrival   :  "<<arrival_t<<endl;
    cout<<"Depart    :  "<<depart_t<<endl;
    cout<<"Wait      :  "<<waiting_t<<endl;
    //write_vehic_csv();
    cout<<endl;
}

void vehicles::departing_info(int departing,int servicingTime)
{
    depart_t = departing;
    service_t = servicingTime;
    waiting_t = (Scheduler::now()) - departing;
}

int vehicles::can_pass(int remain, int length_to_be_covered)
{
    if(length + length_to_be_covered <= remain*speed ) return 1;
    else return 0;
}

void vehicles::fetch_info(int length_, int speed_, int arrival_, int depart_)
{
    length_  = length;
    speed_   = speed;
    arrival_ = arrival_t;
    depart_  = depart_t;
}

