#include "includes.h"

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
