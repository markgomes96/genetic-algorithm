//Program converts .xyz format to .zmt format
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	/*
	ifstream testfile;			//read in test file to understand molecule structure
	ifstream xyzfile;			//read in .xyz file to convert

	if(argc == 3)
	{
		testfile.open(argv[1]);
		xyzfile.open(argv[2]);
	}
	else
	{
		cout << "Error - Invalid number of arguments entered" << endl;
		exit(1);
	}

	if(!testfile.is_open() || !xyzfile.is_open())		//checks if file is available
	{
		cout << "Error - Invalid File Name Entered" << endl;
		exit(1);
	}

	//create tree of atoms, have a start head to point to start node
	//fill 
	//

	vector<string> testfile;
	//string line;
	string word1, word2;
	atom temp = atom();
	while(testfile.peek() != EOF)			//iterate through entire file
	{
		getline(infile, word1, ' ');
		getline(infile, word2, '\n');
		temp.element = word1;
		temp.root = atoi(word2.c_str());
		atomCount += temp.count;
		atoms.push_back(temp);	
	}

	vector<string>::iterator it;
	for(it = input.begin(); it != input.end(); ++it)
	{
		cout << *it << endl;
	}
	*/
}
