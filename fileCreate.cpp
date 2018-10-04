#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
void openFile(int myname[]);
int main (int argc, char ** argv) {
	int myname[5]; 
	return 0;
}
void openFile(int myname[])
{
	string filename;
	cout << "enter file";
	cin >> filename;
	cout << "now creating file " << " " << filename << "\n";
        ofstream myfile;
	myfile.open(filename + ".xyz");
	myfile << myname << filename;
	myfile.close(); 
}

