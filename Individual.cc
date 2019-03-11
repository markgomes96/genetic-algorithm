#include "includes.h"
#include "structs.h"
#include "Individual.h"

#ifndef INDIVIDUAL_CC
#define INDIVIDUAL_CC


Individual :: Individual()
{
	geneLength = 5;
	atomCount = 0;
	fitness = 0.0;	
}

void Individual :: setGeneLength(int _geneLength, int _atomCount)
{
	geneLength = _geneLength;
	genes.reserve(geneLength);
	genes.resize(geneLength);
	oldgenes.reserve(geneLength);
	oldgenes.resize(geneLength);
	atomCount = _atomCount;
}

void Individual :: setValues()
{
	//Set genes randomly for each individual
	int randInt;
	for (int i = 0; i < geneLength; i += ((geneLength / atomCount) / 3)) 		//iterate through every dimension for every atom
	{
    	randInt = rand() % 2;		//set sign bit 0-1
		if(randInt == 1)
		{
    		genes[i] = 1;
 		}
    	else
    	{
        	genes[i] = 0;
    	}

		for(int j = i + 1; j < i + (((geneLength / atomCount) / 3) - 1); j = j + 4)		//iterate through every decimal digit
		{
			int bitNum = 4;				//number of bits per digit
			int binArray[bitNum];
			for(int x = 0; x < bitNum; x++)		//clear bitNum array
			{
				binArray[x] = 0;
			}

			randInt = rand() % 10;		//random number 0-9

			int randIntPerm = randInt;			//remove later

			int count = 0;
			while(randInt > 0)			//convert decimal digit to binary
			{
				binArray[count] = randInt % 2;
				randInt = randInt / 2;
				count++;
			}

			int index = 0;
			for(int k = bitNum - 1; k >= 0; k--)		//array in reverse is binary conversion
			{
				index = (bitNum-1) - k;
				genes[j + index] = binArray[k];
			}
		}
	}
	
	for (int i = 0; i < genes.size(); i++)
	{ 
		oldgenes[i] = 0; 	
	}		
	fitness = -1000.0;
}

//calculate fitness based on inputed system energy
void Individual :: calcFitness(double systemEnergy)
{	
	if(systemEnergy != 0)		//higher negative energies -> increased fitness
	{
		fitness = -1 * systemEnergy;		//mabye flip sign or not?
	}
	else		//if it's zero then no interaction -> very unfit
	{
		fitness = -1000.0;
	}
}

//checks if the genes where changed
bool Individual :: checkGeneChange()
{
	bool changed = false;
	
	for(int i = 0; i < genes.size(); i++)
	{
		if(genes[i] != oldgenes[i])
		{
			changed = true;
		}
	}
	
	return changed;
}

void Individual :: updateGeneRecord()
{
	for (int i = 0; i < genes.size(); i++)
	{ 
		oldgenes[i] = genes[i];	
	}	
}

#endif
