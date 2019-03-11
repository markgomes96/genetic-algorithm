#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H

#include "Molecule.h"
#include "Individual.h"
#include "Population.h"

using namespace std;

//CONSTANTS
#define TEST_PROGRAM "obenergy -ff UFF"
#define POPULATION_SIZE 10

#define EXTINCTION_PERIOD 100
#define EXTINCTION_THRESHOLD 0.2

#define MIGRATION_PERIOD 100
#define MIGRATION_PERCENT 10.0

//GLOBALS
extern Molecule molecule;
extern Population population;
extern Individual fittest;
extern Individual secondFittest;
extern int generationCount;

#endif
