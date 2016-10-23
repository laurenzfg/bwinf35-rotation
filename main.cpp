#include <iostream>
#include <time.h>
#include <string>
#include "rahmen.h"
using namespace std;

int main(int argc, char *argv[])
{
    double t0,t1;
    std::string dateiname;
    std::cout<<"Dateiname: ";
    std::cin>>dateiname;
    t0=clock();
    rahmen(dateiname.c_str());
    t1=clock();
    std::cout<<"Laufzeit: "<<(t1-t0)/CLOCKS_PER_SEC<<"s\n";
    return 0;
}
