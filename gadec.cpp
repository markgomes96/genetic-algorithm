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
	vector<atom> molecule;
	int geneLength = 0;

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
			molecule.push_back(temp);			//store molecule info
		}
	
		//display inputed molecule info
		vector<atom>::iterator it;
		for(it = molecule.begin(); it != molecule.end(); ++it)
		{
			cout << it -> element << " : " << it -> count << endl;
		}
		//
	}

	void calculateGenes()		//uses total atom count to calc gene length
	{
		
	}
};

//Classes
class Individual
{
    public:
    int fitness = 0;
    int geneLength = 5;
    int genes[5];
    int randInt;
    int fitCap = 0;    

    void setValues()
    {
		/*
        //Set genes randomly for each individual
		for (int i = 0; i < geneLength; i++) 
		{
	    	randInt = rand() % 3;
	    	if( randInt == 0 && fitCap < 4)
	    	{
	    		genes[i] = 1;
				fitCap++;
	    	}
	    	else
	    	{
	        	genes[i] = 0;
	    	}
        }
		fitness = 0;
		*/

		//Set genes randomly only for positons

    }
 
	//***Change to accept run data and calcuate fitness based on lowest stored min energy
    void calcFitness()
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
};

class Population
{
    public:
    int popSize = 10;
    Individual individuals[10];
    int fittest = 0;

    //Initialize population
    void initializePopulation(int size)
    {
        for(int i = 0; i < popSize; i++)
        {
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
        for (int i = 0; i < popSize; i++) 
        {
            individuals[i].calcFitness();
        }
        getFittest();
    }
};

//Functions
void selection();
void crossover();
void mutation();
Individual getFittestOffspring();
void addFittestOffspring();

//Global variables
Molecule molecule;
Population population;
Individual fittest;
Individual secondFittest;
int generationCount = 0;

int main(int argc, char* argv[])
{
	molecule.buildMolecule(argv[1]);

	/*
    srand((unsigned)time(0));

    //Initialize population
    population.initializePopulation(10);

    //Calculate fitness of each individual
    population.calculateFitness();

    cout << "Generation: " << generationCount << " Fittest: " << population.fittest << endl;
    
    //While population gets an individual with maximum fitness
    while (population.fittest < 5) 
    {
        generationCount = generationCount + 1;

        //Do selection
        selection();

        //Do crossover
        crossover();

        //Do mutation under a random probability
        if (rand() % 7 < 5) 
        {
            mutation();
        }

        //Add fittest offspring to population
        addFittestOffspring();

        //Calculate new fitness value
        population.calculateFitness();
	
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


//Selection
void selection()
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

//Crossover
void crossover()
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

//Mutation
void mutation()
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

//Get fittest offspring
Individual getFittestOffspring()
{
    if (fittest.fitness > secondFittest.fitness) 
    {
        return fittest;
    }
    return secondFittest;
}

//Replace least fittest individual from most fittest offspring
void addFittestOffspring()
{
    //Update fitness values of offspring
    fittest.calcFitness();
    secondFittest.calcFitness();

    //Get index of least fit individual
    int leastFittestIndex = population.getLeastFittestIndex();

    //Replace least fittest individual from most fittest offspring
    population.individuals[leastFittestIndex] = getFittestOffspring();
}

