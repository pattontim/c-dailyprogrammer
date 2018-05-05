#ifndef POP_VIEW_H
#define POP_VIEW_H

#include <iostream>
using namespace std;

class Population;

class PopulationView {
    PopulationView(){
        aPop = new Population();
    }
    void printGeneration();
    Population & aPop;
    void start();
};
#endif
