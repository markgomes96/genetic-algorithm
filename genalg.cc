#include "includes.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

#include "Molecule.h"
#include "Individual.h"
#include "Population.h"

void testPopulation()		//run individual's gene through tester program
{
	for(int i = 0; i < population.popSize; i++)
	{
		if(population.individuals[i].checkGeneChange())
		{
			testIndividual(i);
			population.individuals[i].updateGeneRecord();
		}
	}
}

void testIndividual(int ind)
{
	//convert genes to string, match with element, and write string to .xyz file
	string fileInfo[molecule.atomCount + 2];
	string elementInfo;
	stringstream ss;

	for(int x = 0; x < molecule.atomCount + 2; x++)		//sets up number of atoms at top of file
	{
		fileInfo[x].clear();
	}
	ss << molecule.atomCount;
	fileInfo[0] = ss.str();
	ss.str("");
	fileInfo[1] = "";
	
	int fractCount = 0;
	for(int j = 0; j < molecule.atoms.size(); j++)		//iterate through types of atoms
	{
		for(int k = 0; k < molecule.atoms[j].count; k++)	//iterate through count of type of atom
		{
			elementInfo = molecule.atoms[j].element + " " + geneToStringConverter(population.individuals[ind].genes, molecule.atomCount, fractCount);
			fileInfo[2+fractCount] = elementInfo;
			fractCount++;
		}
	}

	testGenes(fileInfo, ind);	//test individual to determine fitness
}

void testGenes(string fileInfo[], int ind)
{
	string fileName = "gentest.xyz";		//create file based on individual
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < (molecule.atomCount + 2); i++)
	{
		file << fileInfo[i] << endl;
	}
	file.close();
	
	string command = string(TEST_PROGRAM) + " " + string(fileName);		//convert string command to char array
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
	
	ss.str("");
	return words.end()[-2];			//return 2nd to last string value
}

void selection()					//selcted the two fittest individuals
{
	//Select the most fittest individual
	int fitIndex = population.getFittest();
	fittest.genes.reserve(molecule.geneSize);
	fittest.genes.resize(molecule.geneSize);
	for(int i = 0; i < population.individuals[0].geneLength; i++)
	{
		
		fittest.genes[i] = population.individuals[fitIndex].genes[i];
	}

	//Select the second most fittest individual
	fitIndex = population.getSecondFittest();
	secondFittest.genes.reserve(molecule.geneSize);
	secondFittest.genes.resize(molecule.geneSize);
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
	int fittestIndex = population.getFittest();
	int secondFittestIndex = population.getSecondFittest();
	testIndividual(fittestIndex);
	testIndividual(secondFittestIndex);

	//Get index of least fit individual
	int leastFittestIndex = population.getLeastFittestIndex();

	//Replace least fittest individual with 1st offspring
	for(int i = 0; i < population.individuals[leastFittestIndex].genes.size(); i++)
	{
		population.individuals[leastFittestIndex].genes[i] = fittest.genes[i];
	}

	//get index for second fit individual
	leastFittestIndex = population.getLeastFittestIndex();

	//Replace second fittest individual with 2nd offspring
	for(int i = 0; i < population.individuals[leastFittestIndex].genes.size(); i++)
	{
		population.individuals[leastFittestIndex].genes[i] = secondFittest.genes[i];
	}
}
