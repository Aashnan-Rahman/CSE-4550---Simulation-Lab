#include <bits/stdc++.h>
#include <ctime>

#include "vehicles.h"
#include "scheduler.h"
#include "server.h"
//int vhc_cnt=0;
using namespace std;

int main()
{
    //clock_t t1 = clock();
    cout << "Hello world!" << endl;

//    for(int i=0;i<5;i++)
//    {
//        vehicles v1;
//        v1.create_vehicles();
//        v1.show_vehicles();
//        cout<<endl;
//    }

    Scheduler * sch = new Scheduler();
    Server* s = new Server();

    sch->initialize();
    s->initialize();
    sch->run();

    //s->show_total_cnt ();

    return 0;
}
