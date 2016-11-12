#ifndef RAHMEN_H
#define RAHMEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <iomanip>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <iterator>


class rahmen
{
public:
    rahmen(const char *eingabedatei);

private:
    unsigned int dateigroese;
    char * datei;
    unsigned int seitenlaenge;
		char ** buffer_feld;	

 		void loese(char **f);
    
		void allocate_feld(char **&f);
    void kopiere_feld(char **&quelle, char **&ziel);
    void zeige_feld(char **f);
    void rotieren_links(char **&f);
    void rotieren_rechts(char **&f);
    void gravitation(char**&f);
    bool ist_loesung(char **f);
    void zeige_loesung(char **f, std::string l);
		
		char * berechne_hash(char **&f);
		bool vergleiche_hashs(const char * h1,const char *h2);

};

#endif // RAHMEN_H
