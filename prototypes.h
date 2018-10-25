void testPopulation( void );	//genetester.cc
void testIndividual( int );
void testGenes( string[] , int );
string geneToStringConverter( vector<int> , int , int );
string executeCommand( const char * );
string getEnergy( string );
double* printMoleculeStructure( int );

void selection( void );		//genalg.cc
void crossover( void );
void mutation( void );
Individual getFittestOffspring( void );
void addFittestOffspring( void );

int main(int , char** );	//main.cc
