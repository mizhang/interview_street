#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <stdint.h>
#include <math.h>
#define MODULUS_BASE 1000007
using namespace std;



// Get the @parm factor_count, from calculating X factorial.
void get_factor_times (map<uint64_t,uint64_t> & factor_count, const uint64_t input) { 
	set<uint64_t> all_number; 
	for ( int i = 2; i <= input; i++ ) {
		all_number.insert(i);
        }
        uint64_t output=1 ;
	
	set<uint64_t>::iterator all_number_it = all_number.begin();
	while ( all_number_it != all_number.end()) {
	        uint64_t temp;
		temp = input;
		temp/= *all_number_it;
		for ( int j = 2; j <= temp; j++ ) {
			all_number.erase( j* ( *all_number_it));
		}
		uint64_t count;
		count = 0;	
		while ( temp > 0) {
			count += temp;
			temp /= *all_number_it;
		}
		count =(count *2 + 1) % MODULUS_BASE;
		map<uint64_t, uint64_t>::iterator factor_it;
		factor_it = factor_count.find(count);

		if ( factor_it != factor_count.end() ) 
			factor_it->second ++;
		else
		        factor_count.insert(make_pair (count, 1));

		all_number_it++;
	}		
	return ;
}


// Calculate the power and modulus for 1 count number.
uint64_t get_result (vector<uint64_t> & this_vector, const uint64_t base) {
	vector<uint64_t> this_template;
	uint64_t number = MODULUS_BASE;
	while( number > 0 ) {
		this_template.push_back( number % base) ;
		number /= base;
	}
	for ( int i = 0; i < this_template.size(); i ++ ) {
	   	this_template[i] = base-1 - this_template[i];
        }
	this_template[0] ++;

        int size_threshold = this_template.size();
	int highest_bit = this_vector.size()-1; 
	
	while (  highest_bit >= size_threshold) {
	        uint64_t highest_bit_value = this_vector[highest_bit];
		this_vector.pop_back();
		uint64_t carry_over;
		carry_over = 0;
		int this_bit = highest_bit - size_threshold;
		for ( int i = 0 ; i < size_threshold; i++, this_bit ++) {
			this_vector[this_bit] += carry_over
				+ highest_bit_value * this_template[i];
			carry_over = this_vector[this_bit]/base;
			this_vector[  this_bit] %= base; 
		}
		if ( carry_over > 0) this_vector.push_back(carry_over);
                highest_bit = this_vector.size() -1;
	}
    
	uint64_t result = 0;
	uint64_t base_number = 1;
	for ( int i = 0; i < this_vector.size(); i ++ ) {
		result += base_number * this_vector[i];
		base_number *= base;
	}
	return result;
} 
	
		

		

// Algorithm function to calculate output given input X. 	
uint64_t calculate_output( const map<uint64_t,
			uint64_t> & factor_count) { 
	uint64_t result = 1;
	for (map<uint64_t, uint64_t>::const_iterator it = factor_count.begin();
		it != factor_count.end(); it++ ) {
		vector<uint64_t> this_vector;
		switch ( it-> second) {
		case 2 : 
			result *= pow(it->first, it->second);
			result %= MODULUS_BASE;
			break;
		case 1:
			result *= it->first;
			result %= MODULUS_BASE;
			break;
		default: 
                    
		this_vector.clear();
		this_vector = vector<uint64_t>(it->second+1, 0);
		this_vector[it->second] = 1;
	              	
		result *= get_result ( this_vector, it->first);
                result %= MODULUS_BASE;
		break;
		}
	}
	return result;
	
}		


void print_map ( const map<uint64_t, uint64_t> & result ) {
	for ( map<uint64_t, uint64_t>::const_iterator it = 
		result.begin(); it != result.end(); it ++ ) {
		cout << it->first<< " ";
	}
	cout << endl;
	for ( map<uint64_t, uint64_t>::const_iterator it = 
		result.begin(); it != result.end(); it ++ ) {
		cout << it->second << " ";
	}
	cout << endl;
}	



int main () {
        // @ parameter input, the number x.
	uint64_t input;
	cin >> input; 

        // get_factor_times, factorize x factorial.
        // result is saved in @parameter factor_count.
        map<uint64_t, uint64_t>   factor_count;
	get_factor_times( factor_count, input);
//	print_map( factor_count);

        // calculate number from 29 based vector, @param result. 
	uint64_t output =  calculate_output( factor_count);

        // an second method used to confirm the results.
	// second_test( factor_count, input) ;
	cout << output  << endl;
       	
	
}
			
 
