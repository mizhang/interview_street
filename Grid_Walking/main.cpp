#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#define BASE_DIGIT 10
#define MODULUS_BASE 1000000007 
using namespace std;

// Print out all elements in a vector, for debugging.
void print_vector ( const vector<int64_t> & result) {
	cout << " vector is " ;
	for ( int i = 0; i < result.size(); i ++ ) {
		cout << result[i] << " ";
	}
	cout << endl;
 	cout << endl;
	return;
}

// Print out all elements in a set, for debugging.
void print_set( const set<int64_t> & result) {
	cout << " set is " ;
	for ( set<int64_t>::const_iterator it = result.begin();
		it != result.end(); it++ ) {
		cout << *it << " ";
	}
	cout << endl;
	cout << endl;
}

// Defactorize input @param number, and save the result in @param result, according to
// previously calculated @param primer_set.
void get_factorised_map ( const set<int64_t> & primer_set, map<int64_t, int64_t> & result,
			  const int64_t number) {
	result.clear();
	int N = number;
	for ( set<int64_t>::const_iterator it = primer_set.begin();
		it != primer_set.end(); it++ ) {
		while ( N % (*it) == 0 ) {
			N /= *it;
			map<int64_t, int64_t>::iterator result_it;
			result_it = result.find( *it);
			if ( result_it != result.end() )  result_it->second ++;
			else result.insert( make_pair(*it, 1));
		}
		if ( N== 1) break;
	}
	
	if ( N > 1 )  cerr << __LINE__ << " : algorithm error . " <<  endl;
	return;
}
			
// Change from int as 10 based number to a custom based (@param BASE_DIGIT) 
// number @param result. 
void  vector_convert ( const int number, vector<int64_t> & result) {
	int N = number;
 	result.clear();
	while ( N> 0 ) {
		result.push_back ( N % BASE_DIGIT );
		N /= BASE_DIGIT;
	}
	return;
}

// 
void  clean_digit( vector<int64_t> & result) {
	if (result.size() == 0) return;
	int carry_over = 0;
	for ( int i = 0; i < result.size() ; i++ ) {
		result[i] += carry_over;
		carry_over = result[i]/BASE_DIGIT;
		result[i] %= BASE_DIGIT;
	}

	while ( carry_over > 0 ) {
		result.push_back( carry_over % BASE_DIGIT);
		carry_over /=  BASE_DIGIT;
	}

	while ( *result.rbegin() == 0 ) {
		result.erase( result.begin()+result.size()-1 );
	}
	
	return;
}
			 
	
// Do times operation on input @param second_number, the reuslt is saved
// as in the vector based factorised map, @param result.
void vector_times ( const set<int64_t> & primer_set, map<int64_t, int64_t> & result, const int second_number ) {
	map<int64_t, int64_t> second;
	get_factorised_map (primer_set, second, second_number);
        map<int64_t, int64_t>::const_iterator second_it = second.begin();
        while ( second_it != second.end() ) {	
		map<int64_t, int64_t>::iterator result_it;
		result_it = result.find( second_it->first ); 
		if ( result_it != result.end() )  
		  	result_it->second += second_it->second;
		else 
			result.insert( *second_it); 
		second_it++;
	}
        return;
}

// Do deviding operation on @param second_number, result is saved in the factorised
// map of @param result.
void vector_devide( const set<int64_t> & primer_set, map<int64_t, int64_t> & result, const int second_number) {
	map<int64_t, int64_t> second;
	get_factorised_map (primer_set, second, second_number);
	map<int64_t, int64_t>::const_iterator second_it = second.begin();
        while ( second_it != second.end() ) {	
		map<int64_t, int64_t>::iterator result_it;
		result_it = result.find( second_it->first ); 
		if ( result_it != result.end() )    	result_it->second -= second_it->second;
		else  				result.insert( make_pair( second_it->first, 0-second_it->second)); 
		second_it++;
	}
        return;
}


// calculate all primers within range of input number (@param number).	
void get_primer_set ( set<int64_t> & result, const int64_t number) {
	result.clear();
	result.insert(2);
	for ( int i = 3; i <= number; i += 2) {
		bool mark;
		mark = false;
		for (set<int64_t>::iterator it = result.begin();
		     it != result.end(); it ++ ) {
		 	if ( i % *it == 0 ) {
			 	mark = true;
				break;	
			}
		}
		if ( mark == false)  result.insert(i);
	}
	return;
}

				
			
// Get the total number from factorised map of @param primer_map, and
// do modulus of 1,000,000,007
int64_t get_total_modulus ( const map<int64_t, int64_t> & primer_map) {
	int64_t result = 1;
	map<int64_t, int64_t> this_map = primer_map;

	while ( this_map.size() > 0 ) {
		result *= this_map.begin()->first;
	        if ((--this_map.begin()->second) == 0 ) {
			this_map.erase ( this_map.begin() );
		}
		result %= MODULUS_BASE;
	}
        return result;
}

// Clear the map when the count is zero.
void clear_map ( map<int64_t, int64_t> & result) {
	if (result.empty() ) return;

	map<int64_t, int64_t>::iterator it = result.begin();

	while ( it != result.end() ) {
	
		if ( it->second == 0) 	{
			int temp;
			temp = it->first;
			result.erase(it);
			it = result.lower_bound ( temp);
		} else  it ++ ;
	}
	return;
}
	

			 
// Calculate combinatorial of pick M from N.	
int64_t  pick_M_from_N ( const set<int64_t> & primer_set, const int N, const int M) {
	map<int64_t, int64_t> temp_result;
	int M_calculated = min ( M, N-M);
	if ( M_calculated < 0 ) return 0;
	if ( M_calculated == 0 ) return 1;
   
	for ( int64_t  i = 1; i <= M_calculated; i ++ ) {
		vector_devide (primer_set,temp_result, i);
		vector_times ( primer_set,temp_result, N-i+1);
	}
	clear_map ( temp_result);
        int64_t result = get_total_modulus (temp_result);
	return result;
}

// Calculate total number of possibilities of X steps, moduluated by 1,000,000,007.
int64_t calculate_total ( const int steps) {
	int devider = steps / 30;
	int remainder = steps % 30;
	int64_t base =(int64_t) pow(2,30) % MODULUS_BASE;
	int64_t result =1;
	for ( int i = 0; i < devider; i++) {
		result *= base;
		result %= MODULUS_BASE;
	}
		
	result *= (int64_t)pow(2, remainder) % MODULUS_BASE ;
	result %= MODULUS_BASE;
	return result;
}


// Main algorithm.
int64_t calculate_for_one_side( const int steps, const int start_position, const int edge_position) {

	set<int64_t> primers;
	get_primer_set ( primers, steps);/// name may not be correct.
	int64_t result = 0;
	int64_t fall_off = edge_position - start_position + 1;
	if (steps- fall_off < 0 ) return 0;
	int64_t fall_off_start = fall_off + max((int64_t)0, steps - fall_off) %2;
        
	if ( fall_off_start  == fall_off ) 	{
		result += pick_M_from_N (primers, steps, (steps-fall_off_start)/2 );
        } else { 
		  result += pick_M_from_N (primers, steps, (steps-fall_off_start)/2) *2;
        }
	for ( int i = fall_off_start+2; i <= steps; i += 2) {
		result += pick_M_from_N (primers, steps, (steps-i)/2) *2;
	}
        result %= MODULUS_BASE;
	return result;

	// test cases.
}	

int64_t calculate_output( const int steps, const int start_position, 
		           const int edge_position) {
	int64_t total_step = calculate_total(steps);
	int64_t increase_step = edge_position + 1;
	int64_t sign = -1;
	int64_t right_side_length = edge_position;
        int64_t left_side_length = 2* start_position - 1;

	int64_t result_right_side = calculate_for_one_side( steps, start_position, right_side_length );
	int64_t result_left_side = calculate_for_one_side( steps, start_position, left_side_length);

        while ( result_right_side > 0 || result_left_side > 0 ) {
		total_step += sign * result_right_side;
		total_step += sign * result_left_side;
		while ( total_step < 0 ) {
			total_step += MODULUS_BASE;
		}
		sign *= -1;
		right_side_length += increase_step;
		left_side_length += increase_step;

		result_right_side = calculate_for_one_side(steps, start_position, right_side_length);
		
		result_left_side = calculate_for_one_side(steps, start_position, left_side_length);
	}
	
	total_step %= MODULUS_BASE;

	return total_step; 
}


void run_test_cases ( const int test_case_number) {
	for (int i = 0; i < test_case_number; i ++ ) {
        int steps, start_position, edge_position;
        int temp;
	cin >> temp >> steps >> start_position >> edge_position;

	int64_t output= calculate_output ( steps, start_position, edge_position);

        cout << output << endl;
        }
 	return;
}
		
        
int main () 
{
	int test_case_number;
	cin >> test_case_number;

        run_test_cases ( test_case_number);

	// Test Section Starts.
	/// test for vector change.
	vector<int64_t> result;
	vector_convert(10, result);
	
	vector<int64_t> expected_result;
	expected_result.push_back(0);
	expected_result.push_back(1);

	if ( result != expected_result) 
		cerr << __LINE__ << ": test case failed. " << endl;
	
	vector_convert(1234567, result);
	expected_result.clear();
	expected_result.push_back(7);
	expected_result.push_back(6);
	expected_result.push_back(5);
	expected_result.push_back(4);
	expected_result.push_back(3);
	expected_result.push_back(2);
	expected_result.push_back(1);
	
	if ( result != expected_result) 
		cerr << __LINE__ << ": test case failed. " << endl;

        /// test for clean_digit;
	for ( int i = 0; i < expected_result.size(); i++ ) {
		expected_result[i] = 100;
	}
	clean_digit ( expected_result ) ;

	vector<int64_t> expected_result_2( 9,0);
	for ( int i =2 ; i < 9; i++)  expected_result_2[i] = 1;
	
	if ( expected_result_2 != expected_result) 
		cerr << __LINE__ << ": test case failed. " << endl;

        /// test for pick_N_from_M.
	set<int64_t> primer_set;
	get_primer_set( primer_set, 5);
	int result_1 = pick_M_from_N ( primer_set, 5,2);
	if ( result_1 != 5*4/2 ) 
		cerr << __LINE__ << ": test case failed. " << endl;

	result_1 = pick_M_from_N ( primer_set, 5, 3) ;
	if ( result_1 != 5*4/2 ) 
		cerr << __LINE__ << ": test case failed. " << endl;

	primer_set.clear();
	get_primer_set( primer_set, 6);
	result_1 = pick_M_from_N ( primer_set, 6, 3) ;
	if ( result_1 != 6*5*4/3/2 ) 
		cerr << __LINE__ << ": test case failed. " << endl;
	
	primer_set.clear();
	get_primer_set( primer_set, 7);
	result_1 = pick_M_from_N ( primer_set, 7, 3) ;
	if ( result_1 != 7*6*5/3/2 ) 
		cerr << __LINE__ << ": test case failed. " << endl;

	primer_set.clear();
	get_primer_set( primer_set, 7);
	result_1 = pick_M_from_N ( primer_set, 7, 4) ;
	if ( result_1 != 7*6*5/3/2 ) 
		cerr << __LINE__ << ": test case failed. " << endl;

	int64_t result_2 = calculate_total (31);	
        if ( result_2 != 147483634 ) 
		cerr << __LINE__ << ": test case failed. " << endl;
	result_2 = calculate_total (33);	
        if ( result_2 != 589934536) 
		cerr << __LINE__ << ": test case failed. " << endl;

	result_1 = calculate_for_one_side(1, 1, 2);
	result_2 = calculate_for_one_side(1, 1, 1);

}
