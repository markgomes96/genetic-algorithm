#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H

#include "Molecule.h"
#include "Individual.h"
#include "Population.h"

using namespace std;

//CONSTANTS
#define TEST_PROGRAM "obenergy"
#define POPULATION_SIZE 10

//GLOBALS
extern Molecule molecule;
extern Population population;
extern Individual fittest;
extern Individual secondFittest;
extern int generationCount;

#endif
