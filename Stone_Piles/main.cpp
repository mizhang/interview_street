#include <iostream>
#include <set>
#include <vector>
using namespace std;


void get_next_possibility ( const vector<int> & start_piles, vector<int> & stone_piles )  {
		

bool play_games (const vector<int> & stone_piles, map<vector<int>, bool > & dictionary) {
	set<vector<int> >::iterator strateg_it = dictionary.find(stone_piles);
	if ( strategy_it != dictionary.end() )  
		return strategy_it->second;

	vector<int> one_possibility = get_first_possibility ( stone_piles);
	while ( ! one_possibility.empty() ) {
		if ( play_game ( one_possibility, dictionary) == false ) {
			dictionary.insert( make_pair ( stone_piles, true));
			return true;
		}
		get_next_possibility( one_possibility ) ;
	}

	dictionary.insert( make_pair(stone_piles, false));
	return false;
}

		

int main () {
	vector<int> stones_piles;
	int number;
	while ( cin >> number) {
		stones_piles.push_back(number);
	}

	vector<vector<int> > possibilities;
	get_all_possibilities ( possibilities, stone_piles);

	
	
