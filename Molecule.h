#include "includes.h"
#include "structs.h"

#ifndef MOLECULE_H
#define MOLECULE_H

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

#endif
