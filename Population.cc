#include "includes.h"
#include "structs.h"
#include "Population.h"
#include "Individual.h"

#ifndef POPULATION_CC
#define POPULATION_CC


//Default constructor
Population :: Population()
{
	popSize = 10;
	int fittest = 0;
}

//Initialize population
void Population :: initializePopulation(int _popSize, int _geneSize, int _atomCount)
{
	popSize = _popSize;
	individuals.reserve(popSize);
	individuals.resize(popSize);

	for(int i = 0; i < popSize; i++)
	{
		individuals[i].setGeneLength(_geneSize, _atomCount);
		individuals[i].setValues();
	}
}

//Get the fittest individual
int Population :: getFittest() 
{
	int maxFit = INT_MIN;
	int maxFitIndex = 0;
	for (int i = 0; i < popSize; i++) 
	{
		if (maxFit <= individuals[i].fitness) 
		{
			maxFit = individuals[i].fitness;
			maxFitIndex = i;
		}
	}
	fittest = individuals[maxFitIndex].fitness;
	return maxFitIndex;
}

//Get the second most fittest individual
int Population :: getSecondFittest() 
{
	int maxFit1 = 0;
	int maxFit2 = 0;
	for (int i = 0; i < popSize; i++) 
	{
		if (individuals[i].fitness > individuals[maxFit1].fitness) 
	   	{
            		maxFit2 = maxFit1;
               		maxFit1 = i;
        	} 
	    	else if (individuals[i].fitness > individuals[maxFit2].fitness) 
	    	{
            		maxFit2 = i;
            	}
        }
        return maxFit2;
}

//Get index of least fittest individual
int Population :: getLeastFittestIndex() 
{
	int minFitVal = INT_MAX;
	int minFitIndex = 0;
	for (int i = 0; i < popSize; i++) 
	{
		if (minFitVal >= individuals[i].fitness) 
		{
			minFitVal = individuals[i].fitness;
			minFitIndex = i;
		}
	}
	return minFitIndex;
}

#endif
