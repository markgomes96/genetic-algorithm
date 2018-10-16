#include "includes.h"
#include "structs.h"
#include "Individual.h"

#ifndef POPULATION_H
#define POPULATION_H

class Population
{
	public:

	int popSize;				//variables
	vector<Individual> individuals;
	int fittest;

	Population();		//constructor
	
	void initializePopulation(int _popSize, int _geneSize, int _atomCount);		//functions
	int getFittest();
	int getSecondFittest();
	int getLeastFittestIndex();
};

#endif
