#include "includes.h"
#include "globals.h"
#include "prototypes.h"

#include "Molecule.h"
#include "Individual.h"
#include "Population.h"

int main(int argc, char* argv[])
{
	molecule.buildMolecule(argv[1]);	//store molecule information
	molecule.calculateGeneSize();

	srand((unsigned)time(0));

	population.initializePopulation(POPULATION_SIZE, molecule.geneSize, molecule.atomCount);		//initialize the population

	testPopulation();			//execute each individual in test program to calcuate fitness
	population.getFittest();

	/*
	for(int i = 0; i < population.popSize; i++)
	{
		cout << "Ind : " << i << " 		Fitness : " << population.individuals[i].fitness << endl;
	}
	*/

	cout << "Generation: " << generationCount << " Fittest: " << population.fittest << endl;
	
	int loopcount = 0;    
	while (loopcount < 10)		//population.fittest < 5) 		//while population gets an individual with maximum fitness
	{
		generationCount = generationCount + 1;

		selection();				//do selection
		
		crossover();				//do crossover

		if (rand() % 7 < 5) 			//do mutation under a random probability
		{
			mutation();
		}

		addFittestOffspring();			//add fittest offspring to population

		testPopulation();				//calculate new fitness values
		population.getFittest();

		cout << "Generation: " << generationCount << " Fittest: " << population.fittest << endl;
		
		loopcount++;
	}

	cout << "\nSolution found in generation " << generationCount << endl;
	cout << "Fitness: " << population.fittest << endl;
	cout << "Genes: " << endl;

	int fitIndex = population.getFittest();
	for (int i = 0; i < molecule.geneSize; i++) 
	{
		cout << population.individuals[fitIndex].genes[i];
	}

	cout << "\n \n MINIMUM ENERGY OF SYSTEM : " << -(population.fittest) << endl;
	cout << endl;
}
