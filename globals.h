#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H

using namespace std;

//CONSTANTS
#define TEST_PROGRAM "obenergy";
#define POPULATION_SIZE 10;

//GLOBALS
extern Molecule molecule;
extern Population population;
extern Individual fittest;
extern Individual secondFittest;
extern int generationCount = 0;

#endif
