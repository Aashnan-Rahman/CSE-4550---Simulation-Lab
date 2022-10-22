#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

#include "scheduler.h"
#include "facility.h"

int Server::itemArrived_;

int main ()
{

    for(int i=0;i<=5;i++)
    {
        srand(time(0));
        ofstream report_;

        Scheduler *sch = new Scheduler();
        sch -> initialize();

        Facility* fac = new Facility(5.0 + i, 10.0);
        fac -> initialize();

        sch->run();

        fac -> report();
    }

	return 0;
}
