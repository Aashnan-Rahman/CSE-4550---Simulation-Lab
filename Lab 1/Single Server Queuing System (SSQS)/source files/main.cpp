#include <bits/stdc++.h>
using namespace std;

#include "scheduler.h"
#include "server.h"

int main ()
{
	srand(time(0));

	Scheduler *sch = new Scheduler ();
	sch->initialize ();

	Server* s = new Server ();
	s->createTraceFile ();

	ofstream out("out.csv");
	out << "ArrivalMean" << ',' << "ServiceMean" << ','  << "Ratio" << ','  << "Avg Delay" << ',' << "Avg Queue Length" << ',' << "Total Runtime" << endl;

    s->arrivalMean () = 5.0;

	int i, j;
	for(i=0; i<99; i++)
	{
		s->departureMean () = s->arrivalMean()*i/100;

		double avgd=0, avgql=0, avgrt=0;

		for(j=0; j<30; j++)
		{
			sch->initialize ();
			s->initialize ();

			sch->run ();
			avgd=(avgd*i+s->avgDelay())/(i+1);
			avgql=(avgql*i+s->avgQLength())/(i+1);
			avgrt=(avgrt*i+Scheduler::now())/(i+1);
		}

		out << s->arrivalMean() << ',' << s->departureMean() << ','  << s->departureMean()/s->arrivalMean()<< ','  << avgd << ',' << avgql << ',' << avgrt << endl;
	}

	return 0;
}
