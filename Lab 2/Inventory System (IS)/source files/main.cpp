#include <bits/stdc++.h>
using namespace std;

#include "scheduler.h"
#include "server.h"

int main()
{
    srand(time(0));

    ofstream out("out.csv");
	out << "Average Ordering Cost" << ','  << "Average Holding Cost" << ',' << "Average Shortage Cost" << ',' << "Average Cost" << endl;

	cout << "Average Ordering Cost" << " "  << "Average Holding Cost" << " " << "Average Shortage Cost" << ' ' << "Average Cost" << endl;
	//out.close();

    for(int i=1; i<=30; i++)
    {
        Scheduler *sch = new Scheduler ();
        Server *s = new Server ();

        sch->initialize ();
        s->initialize();

        sch->run();

        //cout << s->avgOrderingCost << ','  << s->avgHoldingCost << ',' << s->avgShortageCost << ',' << s->avgCost << endl;
    }

    return 0;
}
