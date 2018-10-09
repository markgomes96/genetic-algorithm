#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <memory>
#include <stdexcept>
#include <bits/stdc++.h> 

using namespace std;

struct atom
{
	string element;
	int count;
};

//Molecule -> Chromesome Convertion
class Molecule
{
	public:
	vector<atom> atoms;
	int atomCount;
	int geneSize;
	int dimensions;
	int percision;
	int bitMultiplier;

	Molecule()
	{
		atomCount = 0;
		geneSize = 0;
		dimensions = 3;
		percision = 4;
		bitMultiplier = ( dimensions * ( 1 + ( (2 + percision) * 4 ) ) );	//1-sign bit, 2-whole nums, percision-decimals, 4-bits/char
	}

	void buildMolecule(string filename)		//reads in the molecule data from file
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

	void calculateGeneSize()		//uses total atom count to calc gene size
	{
		geneSize = atomCount * bitMultiplier;
	}
};

//Classes
class Individual
{
	public:
	int geneLength;
	int atomCount;
	vector<int> genes;
	double fitness;

	Individual()
	{
		geneLength = 5;
		atomCount = 0;
		fitness = 0.0;	
	}
	
	void setGeneLength(int _geneLength, int _atomCount)
	{
		geneLength = _geneLength;
		genes.reserve(geneLength);
		genes.resize(geneLength);
		atomCount = _atomCount;
	}
	
	void setValues()
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
			
		fitness = 0.0;
	}

	//calculate fitness based on inputed system energy
	void calcFitness(double systemEnergy)
	{
		if(systemEnergy != 0)		//higher negative energies -> increased fitness
		{
			fitness = (-1) * systemEnergy;
		}
		else		//if it's zero then no interaction -> very unfit
		{
			fitness = -1000.0;
		}
	}
};

class Population
{
	public:
	int popSize;
	vector<Individual> individuals;
	int fittest;

	//Default constructor
	Population()
	{
		popSize = 10;
		int fittest = 0;
	}

	//Initialize population
	void initializePopulation(int _popSize, int _geneSize, int _atomCount)
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
	int getFittest() 
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
	int getSecondFittest() 
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
	int getLeastFittestIndex() 
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
};

//FUNCTIONS
void testPopulation();
void testIndividual(string fileInfo[], int ind);
string geneToStringConverter(vector<int> genes, int atomCount, int fractNum);
string executeCommand(const char* cmd);
string getEnergy(string output);
void selection();
void crossover();
void mutation();
Individual getFittestOffspring();
void addFittestOffspring();

//CONSTANTS
string TEST_PROGRAM = "obenergy";
int POPULATION_SIZE = 100;

//GLOBALS
Molecule molecule;
Population population;
Individual fittest;
Individual secondFittest;
int generationCount = 0;

int main(int argc, char* argv[])
{
	molecule.buildMolecule(argv[1]);	//store molecule information
	molecule.calculateGeneSize();

	srand((unsigned)time(0));

	population.initializePopulation(POPULATION_SIZE, molecule.geneSize, molecule.atomCount);		//initialize the population

	testPopulation();			//execute each individual in test program to calcuate fitness

	for(int i = 0; i < population.popSize; i++)
	{
		cout << "Ind : " << i << " 		Fitness : " << population.individuals[i].fitness << endl;
	}
	
	/*
	cout << "Generation: " << generationCount << " Fittest: " << population.fittest << endl;
    
	while (population.fittest < 5) 			//while population gets an individual with maximum fitness
	{
		generationCount = generationCount + 1;

		selection();				//do selection
		
		crossover();				//do crossover

		if (rand() % 7 < 5) 			//do mutation under a random probability
		{
			mutation();
		}

		addFittestOffspring();			//add fittest offspring to population

		population.calculateFitness();		//calculate new fitness value
	
		cout << "Generation: " << generationCount << " Fittest: " << population.fittest << endl;
	}

	cout << "\nSolution found in generation " << generationCount << endl;
	cout << "Fitness: " << population.fittest << endl;
	cout << "Genes: " << endl;

	int fitIndex = population.getFittest();
	for (int i = 0; i < 5; i++) 
	{
		cout << population.individuals[fitIndex].genes[i];
	}

	cout << endl;
	*/
}

void testPopulation()		//run individual's gene through tester program
{
	//convert genes to string, match with element, and write string to .xyz file
	string fileInfo[molecule.atomCount + 2];
	string elementInfo;
	stringstream ss;

	int fractCount = 0;
	for(int i = 0; i < population.popSize; i++)		//iterate through individuals
	{
		for(int x = 0; x < molecule.atomCount + 2; x++)		//sets up number of atoms at top of file
		{
			fileInfo[x].clear();
		}
		ss << molecule.atomCount;
		fileInfo[0] = ss.str();
		ss.str("");
		fileInfo[1] = "";

		for(int j = 0; j < molecule.atoms.size(); j++)		//iterate through types of atoms
		{
			for(int k = 0; k < molecule.atoms[j].count; k++)	//iterate through count of type of atom
			{
				elementInfo = molecule.atoms[j].element + " " + geneToStringConverter(population.individuals[i].genes, molecule.atomCount, fractCount);
				fileInfo[2+fractCount] = elementInfo;
				fractCount++;
			}
		}
		fractCount = 0;

		testIndividual(fileInfo, i);	//test individual to determine fitness
	}
}

void testIndividual(string fileInfo[], int ind)
{
	string fileName = "gentest.xyz";		//create file based on individual
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < (molecule.atomCount + 2); i++)
	{
		file << fileInfo[i] << endl;
	}
	file.close();
	
	string command = TEST_PROGRAM + " " + fileName;		//convert string command to char array
	char char_command[command.length()+1];
	strcpy(char_command, command.c_str());
	
	double systemEnergy = stod(getEnergy(executeCommand(char_command)));

	population.individuals[ind].calcFitness(systemEnergy);			//execute individual file and calc fitness with energy
}

string geneToStringConverter(vector<int> genes, int atomCount, int fractNum)
{
	int atomSegCount = molecule.geneSize / atomCount;
	string atomSegStr;
	stringstream ss;
	int powBin;					//power of 2 to convert binary digit to decimal
	int decimalValue = 0;		//decimal value of 4 bits
	int decPos = 2;
	for(int i = (atomSegCount * fractNum); i < (atomSegCount * (fractNum+1)); i += (atomSegCount/3))	//interates dimensions (x,y,z) for specified atom
	{
		if(genes[i] == 1)		//assign the sign bit
		{
			ss << "-";
		}

		for(int j = i+1; j < (i+((atomSegCount/3)-1)); j=j+4)		//iterate through each character 4 bits at time
		{
			for(int k = j; k < (j+4); k++)			//interate through 4 bits to get numerical value
			{
				powBin = 3 - ( k - j );

				if(genes[k] == 1)
				{ 
					decimalValue += pow(2, powBin);
				}
			}

			ss << decimalValue;			//add num character
			decimalValue = 0;

			if(j == (i + 1 + ((decPos-1)*4)))		//add decimal after two digits
			{
				ss << ".";
			}
		}
		ss << " ";				//add space between each dimension
	}

	atomSegStr = ss.str();		//add full string with all dimensions
	ss.str("");
	
	return atomSegStr;
}

string executeCommand(const char* cmd) 			//execute command and retrieve the output
{
	array<char, 128> buffer;
	string result;
	shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

	if (!pipe) throw runtime_error("popen() failed!");

	while (!feof(pipe.get())) 
	{
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
		{
			result += buffer.data();
		}
	}
	return result;
}

string getEnergy(string output)
{
	string buf;                 	//have a buffer string
	stringstream ss(output);       	//insert the string into a stream

	vector<string> words; 			//create vector to hold our words

	while (ss >> buf)				//store words in buffer to vector
	{
		words.push_back(buf);
	}

	return words.end()[-2];			//return 2nd to last string value
}

void selection()					//selcted the two fittest individuals
{
	//Select the most fittest individual
	int fitIndex = population.getFittest();
	for(int i = 0; i < population.individuals[0].geneLength; i++)
	{
		fittest.genes[i] = population.individuals[fitIndex].genes[i];
	}

	//Select the second most fittest individual
	fitIndex = population.getSecondFittest();
	for(int i = 0; i < population.individuals[0].geneLength; i++)
	{
		secondFittest.genes[i] = population.individuals[fitIndex].genes[i];
	}
}

void crossover()				//selects two random segments of genes from fit individuals
{
	//Select a random crossover point
	int crossOverPoint = (rand() % population.individuals[0].geneLength);

	//Swap values among parents
	for (int i = 0; i < crossOverPoint; i++) 
	{
		int temp = fittest.genes[i];
		fittest.genes[i] = secondFittest.genes[i];
		secondFittest.genes[i] = temp;
	}
}

void mutation()					//randomly changes gene value in fit individuals
{
	//Select a random mutation
	int mutationPoint = (rand() % population.individuals[0].geneLength);

	//Flip values at the mutation point
	if (fittest.genes[mutationPoint] == 0) 
	{
		fittest.genes[mutationPoint] = 1;
	} 
	else 
	{
		fittest.genes[mutationPoint] = 0;
	}

	mutationPoint = (rand() % population.individuals[0].geneLength);

	if (secondFittest.genes[mutationPoint] == 0) 
	{
		secondFittest.genes[mutationPoint] = 1;
	} 
	else 
	{
		secondFittest.genes[mutationPoint] = 0;
	}
}

Individual getFittestOffspring()		//get fittest offspring
{
	if (fittest.fitness > secondFittest.fitness) 
	{
		return fittest;
	}
	return secondFittest;
}

void addFittestOffspring()			//replace least fittest individual from most fittest offspring
{
	//Update fitness values of offspring
	//fittest.calcFitness();
	//secondFittest.calcFitness();

	//Get index of least fit individual
	int leastFittestIndex = population.getLeastFittestIndex();

	//Replace least fittest individual from most fittest offspring
	population.individuals[leastFittestIndex] = getFittestOffspring();
}

