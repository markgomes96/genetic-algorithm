#include <iostream>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

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
    }
 
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
Population population;
Individual fittest;
Individual secondFittest;
int generationCount = 0;

int main(int argc, char* argv[])
{
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

	/*
	for(int p = 0; p < 10; p++)
	{
        cout << "Individual: " << p << " | ";
        for(int g = 0; g < 5; g++)
	    {
	        cout << population.individuals[p].genes[g] << " ";
        }   
        cout << endl;
	}
	*/
	
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

