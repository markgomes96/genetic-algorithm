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

