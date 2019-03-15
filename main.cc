#include "includes.h"
#include "structs.h"
#include "globals.h"
#include "globals.cc"
#include "prototypes.h"

#include "Molecule.h"
#include "Individual.h"
#include "Population.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Please input file to define molecule composition" << endl;
		exit(1);
	}

	molecule.buildMolecule(argv[1]);	//store molecule information
	molecule.calculateGeneSize();

	srand((unsigned)time(0));
	
	population.initializePopulation(POPULATION_SIZE, molecule.geneSize, molecule.atomCount);		//initialize the population

	testPopulation();			//execute each individual in test program to calcuate fitness
	population.sortFittest();
	population.getFittest();	//move getFittest method over to sortFittest?

	for(int i = 0; i < population.popSize; i++)
	{
		cout << "Ind : " << i << " 		Fitness : " << setprecision(8) << population.individuals[i].fitness << endl;
	}
	
	cout << "Generation: " << generationCount << " Fittest: " << setprecision(8) << population.fittest << endl;
	
	int fitIndex = 0;
	int leastFitIndex = 0;
	int loopcount = 0;
	bool extinctionFlag = true;

	while(loopcount < 1000)    //(population.fittest < 0.2512) 		//while population gets an individual with maximum fitness
	{
		generationCount = generationCount + 1;

		selection();				//do selection
		
		crossover();				//do crossover

		if (rand() % 7 < 5) 			//do mutation under a random probability
			mutation();

		addFittestOffspring();			//add fittest offspring to population
	
		testPopulation();			//calculate new fitness values

		population.sortFittest();		//sort population by fittess		

		loopcount++;
		fitIndex = population.getFittest();

		if(population.fittest > EXTINCTION_THRESHOLD)
			extinctionFlag = false;

		if(extinctionFlag)					//handles extinction events
		{
			if(generationCount % EXTINCTION_PERIOD == 0)
			{
				cout << endl << "***EXTINCTION***" << endl;
				population.displacePopulation(90.0);		//mabye only kill off most not all of population?
			}
		}
		
		if(generationCount % MIGRATION_PERIOD == 0)		//handles migration events
		{
			cout << endl << "***MIGRATION***" << endl;
			population.displacePopulation(10.0);
		}

		cout << "Generation: " << generationCount << " Fittest: " << setprecision(8) << population.fittest << endl;	//print generation info
	}

	cout << "\nSolution found in generation " << generationCount << endl;		//diplay fitness and fitest invidiual
	cout << "Fitness: " << setprecision(8) << population.fittest << endl;
	cout << "Genes: " << endl;

	fitIndex = population.getFittest();
	for (int i = 0; i < molecule.geneSize; i++) 
	{
		cout << population.individuals[fitIndex].genes[i];
	}
	cout << endl;
	
	//printMoleculeStructure(fitIndex);

	cout << "\n \n MINIMUM ENERGY OF SYSTEM : " << setprecision(8) << -(population.fittest) << endl;
	cout << endl;

	system("rm genalg.xyz");		// remove utility files
	system("rm genalg.com");
}

void printPopulation()
{
		for(int i = 0; i < population.popSize; i++)
			cout << "Ind : " << i << " 		Fitness : " << setprecision(8) << population.individuals[i].fitness << endl;
		cout << "***********************************************" << endl;
}
