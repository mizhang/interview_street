#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#define MODULUS_BASE 1000000007
using namespace std;


static map<int, int64_t> dictionary;

void print_vector ( const vector<int64_t> & this_vector) {
	for (int i = 0; i < this_vector.size(); i ++ ) 
		cout << this_vector[i] << " ";
	cout << endl;
	return;
}

void print_distance_dic () {
	cout << "distance map is  " << endl;
	for ( map<int, int64_t>::iterator it = dictionary.begin();
		it != dictionary.end(); it ++ ) {
		cout << it->first << " " << it->second << endl;
	}
	cout << endl;
}
void extend_series ( vector<int64_t> & series, const int start_position ) {
	for (int i = 0; i < start_position; i ++ ) {
		series.push_back( series[i]);
	}
	return;
}
void get_first_step (vector<int64_t> & series, const int start_position) {
	int count = series.size();
	series.at(start_position) += series.at((start_position + count + 1)%count);
	series.at(start_position) += series.at((start_position + count - 1)%count);
	series.at(start_position) %= MODULUS_BASE;
	extend_series ( series, start_position);
	for ( int position = start_position +1; position < series.size() -1 ; position ++ ) {
		series[position] += series[position + 1];
		series[position] %= MODULUS_BASE;
	}
  
        int i = -1 * count;	
	for ( ; i < 0 ; i ++ ) {
		dictionary.insert( make_pair(i,0));
	}
	dictionary.insert( make_pair(i++, 1));
        for ( i = 1; i < count-1; i ++) {
		dictionary.insert( make_pair(i,1));
	}
	
	dictionary.insert(make_pair(i++, 2));
	dictionary.insert(make_pair(i, 4));

 	return;
}



void get_possibilities( const int min_number, const int max_number, 
				const int count) {
	double new_min = min_number;
        double new_max = max_number;
	double difference =(double)( (count -1)) /2; 
		

	int new_min_int = floor ( min_number/2 - difference);
	new_min_int = max( new_min_int, 1);

	int new_max_int = ceil  ((double) max_number/2 + difference);
	new_max_int = min( new_max_int, max_number);

	if (dictionary.rbegin()->first < max_number) {
		get_possibilities ( new_min_int, new_max_int, count);
	}
        
	for ( int i = min_number; i <= max_number; i ++ ) {
		int64_t result = 0;
		// efficiency can be increased here;
		int min_j = floor((double)i/2 - difference);
		min_j = max( min_j, 1);
		int max_j = min_j + count -1;
		max_j = min ( max_j, i-1);
		result += dictionary[min_j] * dictionary[i-min_j];
		result %= MODULUS_BASE;
		for ( int j = min_j+1; j <= max_j ; j++)   		{
			result += dictionary[j] * dictionary[i-j] ;		
			result -= dictionary[j-1] *dictionary[i-j];
  			result %= MODULUS_BASE;
			if ( result < 0 )
				result += MODULUS_BASE;
	
		}
		if (max_j - min_j == count -1) {
			int64_t temp = dictionary[min_j] *dictionary[i-count+1-min_j];
			temp %= MODULUS_BASE;
			if ( result < temp ) 
				result += MODULUS_BASE;
			result -= temp; 
		}
		dictionary.insert( make_pair ( i, result));
	}
	//print_distance_dic();
	return;
}



void finish_steps_2 ( const vector<int64_t> & numbers, vector<int64_t>  & series, const int start_position,
		    const int step, const int count) {
	int position = 0;

	vector<int64_t> result(count,0);

	//print_vector(series);	
	for ( int i = 0; i < count; i ++ ) {
		for ( int j = 0; j < count; j ++ ) {
			result[j] += series[start_position +i] * 
					dictionary[ step - count +j -i ];
			result[j] %= MODULUS_BASE;
		}
	}
// 	print_vector( numbers);

	for ( int i = 0; i < count; i++ ) {
		//cout << result[ (count - start_position + i) % count] << " ";
	 	int index = (count  - step - start_position + i ) % count;	
		if ( index < 0 ) index += count;
		
		cout <<( result[index ] > 0 ? result[index] : numbers[i]) << " ";
	}
	cout << endl;
	return;
}

void calculate_output ( ) {
	int count, step;
	cin >> count >> step;
	vector<int64_t> numbers;
	for ( int i = 0; i < count; i ++ ) {
		int64_t temp;
		cin >> temp;
		numbers.push_back(temp);
	}

	dictionary.clear();
	vector<int64_t> series;
	int start_position = 0;
	for ( ; start_position < count; start_position ++ ) {
		series = numbers;
		get_first_step (series, start_position);
		get_possibilities ( max(step -count *2,1), step-1, count);
		finish_steps_2 ( numbers, series, start_position, step, count);
	}

			
}
		
int main () {
	int test_case_number;
	cin >> test_case_number;

	for ( int i = 0; i < test_case_number; i ++ ) {
		calculate_output();
		if ( i != test_case_number -1) {
			cout << endl;
		}
	}
//	print_distance_dic();
//	print_dictionary_map();
}


