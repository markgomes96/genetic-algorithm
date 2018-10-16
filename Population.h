#include "includes.h"

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
