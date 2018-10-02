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
		//atom temp = {NULL, 0};
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
		/*
		vector<atom>::iterator it;
		for(it = atoms.begin(); it != atoms.end(); ++it)
		{
			geneSize += (it -> count) * bitMultiplier;
		}
		*/
		geneSize = atomCount * bitMultiplier;
		cout << "gene size : " << geneSize << endl;
	}
};

//Classes
class Individual
{
	public:
	int fitness;
	int geneLength;
	vector<int> genes;  

	Individual()
	{
		fitness = 0;
		geneLength = 5;	
	}
	
	void setGeneLength(int _geneLength)
	{
		geneLength = _geneLength;
		//genes = new int[geneLength];
		cout << "geneLength" << geneLength << endl;
		genes.reserve(geneLength);
		genes.resize(geneLength);
	}
	
	void setValues()
	{
        	//Set genes randomly for each individual
		//int randInt;
		for (int i = 0; i < geneLength; i++) 
		{
	    		//randInt = rand() % 3;		//set percent chance for one
			//if( randInt == 0 )
			if(rand() % 2 == 1)
			{
	    			genes[i] = 1;
	 		}
	    		else
	    		{
	        		genes[i] = 0;
	    		}
        	}
		fitness = 0;
	}

	//***Change to accept run data and calcuate fitness based on lowest stored min energy
	void calcFitness(/*double potentialEnergy*/)
	{
		fitness = 0;
        	for(int i = 0; i < 5; i++)
        	{
		    	if(genes[i] == 1)
		    	{
        		        fitness = fitness + 1;
		    	}
        	}
	}
	///////////////////////////////////////////////////////
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
	void initializePopulation(int _popSize, int _geneSize)
	{
		popSize = _popSize;
		individuals.reserve(popSize);
		individuals.resize(popSize);

        	for(int i = 0; i < popSize; i++)
        	{
			individuals[i].setGeneLength(_geneSize);
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

	//Calculate fitness of each individual
	void calculateFitness() 
	{
		/*
		for (int i = 0; i < popSize; i++) 
		{
			individuals[i].calcFitness();
		}
		getFittest();
		*/
	}
};

//Functions
void testPopulation();
string geneToStringConverter(vector<int> genes, int atomCount, int fractNum);
void selection();
void crossover();
void mutation();
Individual getFittestOffspring();
void addFittestOffspring();

//Constants
int POPULATION_SIZE = 10;

//Global variables
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

	population.initializePopulation(POPULATION_SIZE, molecule.geneSize);		//initialize the population
	
	//print out all individuals
	for (int i = 0; i < population.popSize; i++) 
	{
		cout << "Individual : " << (i+1) << "	Genes : "; 
		for (int j = 0; j < molecule.geneSize; j++)
		{
			cout << population.individuals[i].genes[j];
		}
		cout << endl;
	}
	////////////////////////////

	testPopulation();			//test each individual in tester program

	/*
	population.calculateFitness();			//calculate fitness of each individual

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
	string elementInfo;
	int fractCount = 0;
	for(int i = 0; i < population.popSize; i++)		//iterate through individuals
	{
		cout << "Individual : " << (i+1) << "	Genes : "; 
		for (int z = 0; z < molecule.geneSize; z++)
		{
			cout << population.individuals[i].genes[z];
		}
		cout << endl;

		for(int j = 0; j < molecule.atoms.size(); j++)		//iterate through types of atoms
		{
			for(int k = 0; k < molecule.atoms[j].count; k++)	//iterate through count of type of atom
			{
				//cout << "individual : " << i << "	molecule : " << molecule.atoms[j].element << "	count: " << molecule.atoms[j].count << endl;
				elementInfo = molecule.atoms[j].element + " " + geneToStringConverter(population.individuals[i].genes, molecule.atomCount, fractCount);
				cout << elementInfo << endl;
				fractCount++;
			}
		}
		fractCount = 0;
	}
}

string geneToStringConverter(vector<int> genes, int atomCount, int fractNum)
{
	int atomSegCount = molecule.geneSize / atomCount;
	string atomSegStr;
	stringstream ss;
	int powBin;		//power of 2 to convert binary digit to decimal
	int binValue = 0;
	int decPos = 2;
	for(int i = (atomSegCount * fractNum); i < (atomSegCount * (fractNum+1)); i += (atomSegCount/3))	//interate through each dimension position (x,y,z)
	{
		if(genes[i] == 1)		//assign the sign bit
		{
			ss << "-";
		}

		for(int j = i+1; j < (i+((atomSegCount/3)-1)); j=j+4)		//iterate through each character
		{
			//cout << genes[j] << genes[j+1] << genes[j+2] << genes[j+3] << endl;
			for(int k = j; k < (j+4); k++)			//interate through 4 bits to get numerical value
			{
				powBin = 3 - ( k - j );
				//cout << "powBin : " << powBin << endl;
				if(genes[i] == 1)
				{
					//cout << "added value" << endl; 
					binValue += pow(2, powBin);
				}
				//cout << "binValue : " << binValue << endl;
			}
			/*
			if(binValue > 9)	//get digits between 0-9
			{
				binValue = 9;	
			}
			*/
			ss << binValue;		//add num character
			binValue = 0;
			if(j == (i + 1 + ((decPos-1)*4)))		//add decimal after two digits
			{
				ss << ".";
			}
		}
		ss << " ";		//add space between each dimension

		//ss << genes[i];
	}

	atomSegStr = ss.str();		//add full string with all dimensions
	ss.str("");
	
	return atomSegStr;
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

	//cout << "Cross over point : "  << crossOverPoint << endl;

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
	fittest.calcFitness();
	secondFittest.calcFitness();

	//Get index of least fit individual
	int leastFittestIndex = population.getLeastFittestIndex();

	//Replace least fittest individual from most fittest offspring
	population.individuals[leastFittestIndex] = getFittestOffspring();
}

