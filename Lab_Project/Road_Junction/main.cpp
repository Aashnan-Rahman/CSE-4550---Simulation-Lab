#include <bits/stdc++.h>
#include <ctime>

#include "vehicles.h"
#include "scheduler.h"
#include "server.h"
//int vhc_cnt=0;
using namespace std;

int main()
{
    srand(time(0));
    cout << "Hello world!" << endl;

    Scheduler * sch = new Scheduler();
    Server* s = new Server();

    sch->initialize();
    s->initialize();
    sch->run();
    s->show_result();

    return 0;
}
