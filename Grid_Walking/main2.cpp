#include <iostream>
#include <vector>
#include <set>
#define MODULUS_BASE
using namespace std;






class Solver {
public:
	vector<int>  starts;
	vector<int>  right_over;
	vector<int>  in_dimension_steps;
	vector<int>  result;
	int          steps;
	multset<int>  total_sequence;

	Solver( const int dimensions, const int steps_input );
	solve ();
};



Solver::Solver ( const int dimensions, const int steps_input):
		steps( steps_input ) {
	for ( int i = 0; i < dimensions; i ++ ) {
		int temp;
		cin >> temp;
		starts.push_back( temp ) ;
	}

	for ( int i = 0; i < dimensions; i ++ ) {
		int temp;
		cin >> temp;
		temp ++;
		right_over.push_back( temp );
	        in_dimension_steps.push_back ( temp*2);	
	}
	result = 0;
}
	


void Solver::solve() {
	initialize_sequence();
	while ( !total_sequence.empty()) {
		pair<int, int> this_pair = get_pair ();
		result += calculate_pair( this_pair);
		result %= MODULUS_BASE;
	}
	cout << result << endl;
}

void Solver::initialize_sequence() {
}

pair<int, int>  Solver::get_pair() {
}


int64_t Solver::calculate_pair ( const pair<int, int> & this_pair) {
}




int main () {
	int test_case_number;
	cin >> test_case_number;

	for ( int i = 0; i < test_case_number; i ++ ) {
		int dimensions, steps_input;
		cin >> dimensions >> steps_input;
		Solver this_solver ( dimensions, steps_input);
	}
		
}	
