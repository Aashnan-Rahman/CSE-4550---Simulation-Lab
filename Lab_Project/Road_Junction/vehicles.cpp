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
    myfile << serial_no << "," << queue_no << "," << type <<","<< length <<","<< speed <<","<< arrival_t <<","<< depart_t << "," << waiting_t <<"\n";
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


