#include <iostream>
#include <fstream>
using namespace std;

int main ( ) {
 	ifstream correct_file("correctresult.txt");	
	ifstream test_file ("testresult.txt");
	int i = 0;
	while ( correct_file.good() ) {
		i++;
		if ( !test_file.good() ) 
			cout << __LINE__ << " error " << endl;
	
		string correct_line, test_line;
		getline ( correct_file, correct_line);
		getline ( test_file, test_line);
		
		if ( correct_line != test_line) 
			cout << __LINE__  << " " << i << " ";
	}
}

		


