//Program converts .xyz format to .zmt format
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

typedef struct vect3d		//stores data for a 3D vector used for calcualtions
{
	float x;
	float y;
	float z;

	vect3d()
	{}

	vect3d(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
} vect3d;

typedef struct atom
{
	string element;
	atom root;		//connected atom  //***modify this
	vect3d position;
}

int main(int argc, char* argv[])
{
	vector<atom> atoms;

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
}

vect3d vectDistance(vect3d v1, vect3d v2)
{

}
