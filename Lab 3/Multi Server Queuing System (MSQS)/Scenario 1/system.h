#include "server.h"
#include <fstream>
using namespace std;

#ifndef system_h
#define system_h

class System
{
public:
    System(double arrivalMean, double serviceMean);
    void report();
    void initialize();
    void createTraceFile ();
    void arrivalHandler();
    void departureHandler(Server*);

    inline int queueLength() { return queue_ -> length(); }
    inline ofstream& trace() { return trace_; }

private:
    Server* server1;
    Server* server2;

    Queue* queue_;
    int itemArrived_;

    ofstream trace_;

};

#endif
