#include "includes.h"
#include "structs.h"
#include "Molecule.h"

#ifndef MOLECULE_CC
#define MOLECULE_CC


Molecule :: Molecule()
{
	atomCount = 0;
	geneSize = 0;
	dimensions = 3;
	percision = 4;
	bitMultiplier = ( dimensions * ( 1 + ( (2 + percision) * 4 ) ) );	//1-sign bit, 2-whole nums, percision-decimals, 4-bits/char
}

void Molecule :: buildMolecule(string filename)		//reads in the molecule data from file
{
	ifstream infile;
	infile.open(filename.c_str());

	if(!infile.is_open())		//checks if file is available
	{
		cout << "Error - Invalid File Name Entered" << endl;
		exit(1);
	}

	string word1, word2;
	atom temp = atom();
	while(infile.peek() != EOF)			//iterate through entire file
	{
		getline(infile, word1, ' ');
		getline(infile, word2, '\n');
		temp.element = word1;
		temp.count = atoi(word2.c_str());
		atomCount += temp.count;
		atoms.push_back(temp);			//store molecule info
	}
	
	//display inputed molecule info
	cout << "-atom list-" << endl;
	vector<atom>::iterator it;
	for(it = atoms.begin(); it != atoms.end(); ++it)
	{
		cout << it -> element << " : " << it -> count << endl;
	}
}

void Molecule :: calculateGeneSize()		//uses total atom count to calc gene size
{
	geneSize = atomCount * bitMultiplier;
}

#endif
