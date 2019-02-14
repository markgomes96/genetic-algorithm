//Program converts .xyz format to .zmt format

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
#include <algorithm>

using namespace std;

void convertToXYZFile(string fileInfo[]);
void convertXYZToCOM();
void convertCOMToZMT(string output);
string executeCommand(const char* cmd);

void testConvert();		//***move into convertCOMToZMT

void convertToXYZFile(string fileInfo[])	//convert string array to xyz file
{
	string fileName = "genalg.xyz";		//create file based on individual
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < 3; i++)
	{
		file << fileInfo[i] << endl;
	}
	file.close();
}

void testConvert()
{
	ifstream fileIn;
	string fileName1 = "benzene.com";
	fileIn.open(fileName1);
	vector<string> zmatInfo;
	string buffer;

	for(int i = 0; i < 6; i++)		//iterate to correct start in .com file
	{
		getline(fileIn, buffer, '\n');
	}
	
	cout << "****************" << endl;

	buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());

	while(strcmp(buffer.c_str(), "Variables:") != 0 && fileIn.good())	//retrieve zmat with variables
	{
		replace( buffer.begin(), buffer.end(), ',', ' ');
		zmatInfo.push_back(buffer);

		getline(fileIn, buffer, '\n');
		buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
	}
	zmatInfo.push_back("");

	getline(fileIn, buffer, '\n');
	while(strcmp(buffer.c_str(), "") != 0 && fileIn.good())			//retrieve variables values
	{
		buffer.erase(remove(buffer.begin(), buffer.end(), ' '), buffer.end());
		replace( buffer.begin(), buffer.end(), '=', ' ');
		zmatInfo.push_back(buffer);
		getline(fileIn, buffer, '\n');
	}

	fileIn.close();

	string fileName2 = "benzene.zmt";		//create file based on individual
	ofstream fileOut;
	fileOut.open(fileName2);
	for(int i = 0; i < zmatInfo.size(); i++)
	{
		fileOut << zmatInfo[i].c_str() << endl;
		cout << zmatInfo[i].c_str() << endl;
	}
	fileOut.close();
}

void convertXYZToCOM()
{
	string command = "newzmat -ixyz genalg.xyz -rebuildzmat -ozmat genalg.com";		//convert string command to char array
	char char_command[command.length()+1];
	strcpy(char_command, command.c_str());

	convertCOMToZMT(executeCommand(char_command));
}

void convertCOMToZMT(string output)		//***start here - change to cut out zmat
{
	string buf;                 	//have a buffer string
	stringstream ss(output);       	//insert the string into a stream

	//add to string vector -> convert to file
	vector<string> zmatInfo;

	while (ss >> buf)				//store words in buffer to vector
	{
		zmatInfo.push_back(buf);
	}
	ss.str("");

	string fileName = "genalg.zmt";		//create file based on individual
	ofstream file;
	file.open(fileName);
	for(int i = 0; i < zmatInfo.size(); i++)
	{
		file << zmatInfo[i] << endl;
	}
	file.close();
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

int main(int argc, char* argv[])
{
	/*
	ifstream xyzfile;			//read in .xyz file to convert

	if(argc == 2)
	{
		xyzfile.open(argv[1]);
	}
	else
	{
		cout << "Error - Invalid number of arguments entered" << endl;
		exit(1);
	}

	if(!xyzfile.is_open())		//checks if file is available
	{
		cout << "Error - Invalid File Name Entered" << endl;
		exit(1);
	}

	string fileInfo[3];
	getline(xyzfile, fileInfo[0], '\n');
	getline(xyzfile, fileInfo[1], '\n');
	getline(xyzfile, fileInfo[2], '\n');
	xyzfile.close();

	cout << fileInfo[0] << endl << fileInfo[1] << endl << fileInfo[2] << endl;

	convertToXYZFile(fileInfo);
	*/

	testConvert();

	//convertXYZToCOM();
}
