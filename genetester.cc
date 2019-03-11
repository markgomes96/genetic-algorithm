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
	int fileSize = molecule.atomCount /*+ 2*/;
	string fileInfo[fileSize];
	string elementInfo;
	stringstream ss;

	for(int x = 0; x < molecule.atomCount /*+ 2*/; x++)		//clear out fileInfo
	{
		fileInfo[x].clear();
	}
	/*
	ss << molecule.atomCount;
	fileInfo[0] = ss.str();		// write atom count
	ss.str("");
	fileInfo[1] = "";
	*/	

	int fractCount = 0;
	for(int j = 0; j < molecule.atoms.size(); j++)		//iterate through types of atoms
	{
		for(int k = 0; k < molecule.atoms[j].count; k++)	//iterate through count of type of atom
		{
			elementInfo = molecule.atoms[j].element + " " + geneToStringConverter(population.individuals[ind].genes, molecule.atomCount, fractCount);
			fileInfo[/*2+*/fractCount] = elementInfo;
			fractCount++;
		}
	}

	//*** Convert .xyz format to .zmt format
	convertToXYZFile(fileInfo, fileSize);
	string testFile = "snifr.zmt";				// test file accessed by traject3d
	convertXYZToCOM(testFile);
	//***

	testGenes(ind);				//test individual to determine fitness
}

void testGenes(int ind)
{	
	stringstream ss;
	ss << "traject3d";
	string command = ss.str();		//convert string command to char array
	ss.str("");
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

string getEnergy(string output)		//retrieve energy value from buffer string
{
	string buf;                 	//have a buffer string
	stringstream ss(output);       	//insert the string into a stream

	vector<string> words; 			//create vector to hold our words

	while (ss >> buf)				//store words in buffer to vector
	{
		words.push_back(buf);
	}
	ss.str("");

	cout << "energy : " << words[1] << endl;

	return words[1];			//return 2nd to last string value
}

void convertToXYZFile(string fileInfo[], int fileSize)	//convert string array to xyz file
{
	string fileName = "genalg.xyz";		//create file based on individual
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < fileSize; i++)
	{
		file << fileInfo[i] << endl;
	}
	file.close();
}

void convertXYZToCOM(string testFile)
{
	string command = "newzmat -ixyz genalg.xyz -rebuildzmat -ozmat genalg.com";		//convert string command to char array
	char char_command[command.length()+1];
	strcpy(char_command, command.c_str());

	system(char_command);

	convertCOMToZMT(testFile);
}

void convertCOMToZMT(string testFile)
{
	ifstream comFile;
	string comFileName = "genalg.com";
	comFile.open(comFileName);
	vector<string> zmatInfo;
	string buffer;

	for(int i = 0; i < 6; i++)		//iterate to correct start in .com file
	{
		getline(comFile, buffer, '\n');
	}

	buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());

	while(strcmp(buffer.c_str(), "Variables:") != 0 && comFile.good())	//retrieve zmat with variables
	{
		replace( buffer.begin(), buffer.end(), ',', ' ');
		zmatInfo.push_back(buffer);

		getline(comFile, buffer, '\n');
		buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
	}
	zmatInfo.push_back("");

	getline(comFile, buffer, '\n');
	while(strcmp(buffer.c_str(), "") != 0 && comFile.good())			//retrieve variables values
	{
		buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
		replace( buffer.begin(), buffer.end(), '=', ' ');
		zmatInfo.push_back(buffer);
		getline(comFile, buffer, '\n');
	}

	comFile.close();

	string zmtFileName = testFile;		// input zmt info to test file modified by traject3d
	ofstream zmtFile;
	zmtFile.open(zmtFileName);
	for(int i = 0; i < zmatInfo.size(); i++)
	{
		zmtFile << zmatInfo[i].c_str() << endl;
	}
	zmtFile.close();
}
