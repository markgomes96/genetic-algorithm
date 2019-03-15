void testPopulation( void );		//genetester.cc
void testIndividual( int );
void testGenes( int );
string geneToStringConverter( vector<int> , int , int );
string executeCommand( const char * );
string getEnergy( string );
void convertToXYZFile( string[] , int );
void convertXYZToCOM( string );
void convertCOMToZMT( string );

void selection( void );				//genalg.cc
void crossover( void );
void mutation( void );
Individual getFittestOffspring( void );
void addFittestOffspring( void );

int main(int , char** );			//main.cc
void printPopulation( void );
