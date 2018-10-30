#include "includes.h"
#include "structs.h"
#include "globals.h"
#include "prototypes.h"

#include "Molecule.h"
#include "Individual.h"
#include "Population.h"

/*
*Allow mating of top 10% with each other randomly
*Store offspring in global vector
*Replace last 10% with offspring 
*/

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
	testIndividual(leastFittestIndex);

	//get index for second fit individual
	leastFittestIndex = population.getLeastFittestIndex();

	//Replace second fittest individual with 2nd offspring
	for(int i = 0; i < population.individuals[leastFittestIndex].genes.size(); i++)
	{
		population.individuals[leastFittestIndex].genes[i] = secondFittest.genes[i];
	}
}
