#include <bits/stdc++.h>
#include <ctime>

#include "vehicles.h"
#include "scheduler.h"
#include "server.h"

using namespace std;

int main()
{
    srand(time(0));
    ofstream result;
    result.open("Result Analysis.csv");  //,std::ios::app
    result<<"No , Total Signals, Total Departures , Total Waiting Time , Total Service Time , Avg Departures , Avg Waiting Time , Avg Service Time ,  Avg Queue Length \n";
    result.close();

    int signals__ = 0,totalDeps__ = 0,totalWait__ = 0,totalServ__ = 0,qLen__ = 0 ;

    for(int i=1;i<=20;i++)
    {
        Scheduler * sch = new Scheduler();
        Server* s = new Server();

        sch->initialize();
        s->initialize();
        sch->run();
        s->show_result(i);

    }


    return 0;
}
