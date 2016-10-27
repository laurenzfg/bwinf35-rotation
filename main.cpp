#include <iostream>
#include <time.h>
#include <string>
#include "rahmen.h"
using namespace std;

int main(int argc, char *argv[])
{
    std::string dateiname;
    std::cout<<"Dateiname: ";
    std::cin>>dateiname;
    
		double tstart=clock();
	
		rahmen(dateiname.c_str());

    std::cout<<"Laufzeit: "<<(clock()-tstart)/CLOCKS_PER_SEC<<"s\n";
    return 0;
}
