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

typedef struct data
{
	string forceField;
	double bondDistance;
	double systemEnergy;

	data()
	{}

	data(string ff, double bd, double se)
	{
		forceField = ff;
		bondDistance = bd;
		systemEnergy = se;
	}
} data;

double createFile(data d);
double testFile(string fileInfo[], string ff);
string executeCommand(const char* cmd); 
string getEnergy(string output);

double plotstart = 0.5;
double plotend = 5.0;
double it = 0.05;
int ffc = 5;
string ffnames[5] = {"GAFF", "GHEMICAL", "MMFF94", "MMFF94s", "UFF"}; 

int main(int argc, char* argv[])
{
	int dc = ((plotend - plotstart) / it) + 1;
	data plots[ffc][dc];

	for(int i = 0; i < ffc; i++)		//declare the plot points
	{
		for(int j = 0; j < dc; j++)
		{
			plots[i][j] = data(ffnames[i], (plotstart + (it*j)), 0.0);
			cout << "( " << i << " , " << j << " ) : " << plots[i][j].forceField << " : " << plots[i][j].bondDistance << " : " << plots[i][j].systemEnergy << endl; 
		}
	}
	cout << "**********************" << endl << endl;	

	for(int i = 0; i < ffc; i++)		//test all the plot points
	{
		for(int j = 0; j < dc; j++)
		{
			plots[i][j].systemEnergy = createFile(plots[i][j]);	//store the system energy
			cout << "( " << i << " , " << j << " ) : " << plots[i][j].forceField << " : " << plots[i][j].bondDistance << " : " << plots[i][j].systemEnergy << endl; 
		}
		cout << endl;
	}

	//***create file with data form plot array
	//choose way to graph all that data -> gnuplot?
}

double createFile(data d)
{
	string fileInfo[4];
	string elementInfo;
	stringstream ss;

	for(int x = 0; x < 4; x++)		//sets up number of atoms at top of file
	{
		fileInfo[x].clear();
	}

	fileInfo[0] = "2";
	fileInfo[1] = "";
	
	ss << "O " << d.bondDistance << " 0.0000 0.0000";
	fileInfo[2] = ss.str();
	ss.str("");

	fileInfo[3] = "O 0.0000 0.0000 0.0000";

	return testFile(fileInfo, d.forceField);	//test individual to determine fitness
}

double testFile(string fileInfo[], string ff)
{
	string fileName = "o2.xyz";		//create file based on individual
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < 4; i++)
	{
		file << fileInfo[i] << endl;
	}
	file.close();
	
	stringstream ss;
	ss << "obenergy " << "-ff " << ff << " " << fileName;
	string command = ss.str();		//convert string command to char array
	ss.str("");
	char char_command[command.length()+1];
	strcpy(char_command, command.c_str());
	
	return stod(getEnergy(executeCommand(char_command)));
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

	cout << words.end()[-2] << endl;
	return words.end()[-2];			//return 2nd to last string value
}
