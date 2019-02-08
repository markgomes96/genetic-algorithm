#include "includes.h"
#include "structs.h"

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

class Individual
{
	public:

	int geneLength;			//variables
	int atomCount;
	vector<int> genes;
	vector<int> oldgenes;
	double fitness;

	Individual();			//constructor

	void setGeneLength(int _geneLength, int _atomCount);		//functions
	void setValues();
	void calcFitness(double systemEnergy);
	bool checkGeneChange();
	void updateGeneRecord();
};

#endif
