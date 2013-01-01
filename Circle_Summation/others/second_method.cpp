#include <iostream>
#include <vector>
#define MODULUS_BASE 1000000007
using namespace std;



// Play one position.
void play_a_hand ( vector<int64_t> & current, const int i ) {
	int previous = i-1;
	int next = i+1;
	if (previous < 0 ) previous = current.size()-1;
	if ( next == current.size() )  next = 0;
	current[i] += current[previous] + current[next];
	current[i] %= MODULUS_BASE;
	return;
}

// Play the whole game.
void play_all ( vector<int64_t> current, const int rounds,
		const int position) {
	int vector_size = current.size();
	for ( int i = 0; i < rounds ; i++ ) {
		play_a_hand ( current, (i+position ) % vector_size );
	}
	for ( int i = 0; i < vector_size; i ++ ) {
		cout << current[i] << " ";
	}
	cout << endl;
	return;
} 



int main() {
	int test_case_number;
	cin >> test_case_number;
	int vector_size;
	int rounds;

	// Each loop is for one test case.
	for ( int i = 0; i < test_case_number; i ++ )  {
		cin >> vector_size >> rounds;
		vector<int64_t>    current;
		current.clear();

		// Initiate the starting numbers.
		for ( int j= 0; j < vector_size; j++ ) {
			int64_t this_number;
			cin >> this_number;
			current.push_back(this_number) ;
		}

		for ( int j= 0; j < vector_size; j++ ) {
			play_all ( current, rounds, j);
		}
		if ( i != test_case_number-1)  cout << endl;

	}

}



