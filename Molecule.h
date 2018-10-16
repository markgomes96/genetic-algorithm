#include "includes.h"

class Molecule
{
	public:
	
	vector<atom> atoms;	//variables
	int atomCount;
	int geneSize;
	int dimensions;
	int percision;
	int bitMultiplier;

	Molecule();					//constructor

	void buildMolecule(string filename);		//functions
	void calculateGeneSize();
	
	private:	
};
