//Program converts .xyz format to .zmt format
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

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

void convertXYZToZMT()
{
	string command = "newzmat -ixyz genalg.xyz -rebuildzmat -ozmat genalg.com" + string(fileName);		//convert string command to char array
	char char_command[command.length()+1];
	strcpy(char_command, command.c_str());

	getZMAT(executeCommand(char_command));
}

void getZMAT(string output)		//***start here - change to cut out zmat
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

	//return words.end()[-2];			//return 2nd to last string value

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

	cout << fileInfo[0] << endl << fileInfo[1] << endl << fileInfo[2] << endl;

	convertToXYZFile(fileInfo);

	convertXYZToZMT();
}
