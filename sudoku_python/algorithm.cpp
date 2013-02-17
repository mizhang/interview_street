/********    SUDOKU SOLVER    **********

             mi miya zhang    Dec 4, 2012   
	
	This program solves sudoku puzzle based 
on algorithm computing.  Its performance is 
maximized by minimizing try_and_error approach. 

	Three rules (that each row, column and 
sub_square has a non repeating set of numbers from 
1-9) are each designed as a class(Row, Column
and Square), all derived from base Unit class.  

	The Puzzle class is responsible for 
whole puzzle solving with the help of the three
rule classes, Row, Column, and Square. 

******************************************/

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <stdexcept>
using namespace std;

/** For each grid in 9*9 squares. */
class Position {
	public:
		int            row;
		int            column;
		int            square;
		int            position;
		set<int>       possibles;
		int            value;
		int            count;

		Position ()  {  position = -2; }

		Position (const int row, const int column, const int value):
			row(row), column(column), value(value){
				position = row*9 +column;
				square = row/3*3 + column/3;
			}

		Position* solve() {
			if (possibles.size() > 1) return NULL;
			this->assign(*possibles.begin() ); 
			return this;
		}

		int update_count () { count = possibles.size();}


		void initiate_possibles(set<int> & one, set<int> & two, set<int> & three) {
			set<int>::iterator it_1 = one.begin();
			set<int>::iterator it_2 = two.begin();
			set<int>::iterator it_3 = three.begin();
			while ( it_1 != one.end() 
					&& it_2 != two.end()
					&& it_3 != three.end() )
			{
				if (*it_1 < *it_2)
				{ it_1 ++;  }
				else if ( *it_1 > *it_2)
				{ it_2 ++;  }
				else if (*it_1 < *it_3)
				{ it_1 ++;  }
				else if (*it_1 > *it_3)
				{ it_3 ++;  }
				else {
					possibles.insert(*it_1++);
				}
			}
			update_count();
		}

		bool solved() { return value > 0;}

		Position*  assign (const int input_value) {
			if (possibles.find(input_value) == possibles.end()) {
				throw -1;
			}
			value = input_value;
			return this;
		}


		Position *  update_assigned(const int x) {
			set<int>::iterator it = possibles.find(x);
			if (it != possibles.end()) {
				possibles.erase(it);
				return this;
			}
			return NULL;
		}

		void print () {
			cout << endl;
			std::cout << row  <<  " " << column << " "
				<< square << " " << position << endl;
			std::cout << "value: " << value << endl;	
			cout << "possible size " << possibles.size() << endl; 
			for ( set<int>::iterator it = possibles.begin();
					it != possibles.end(); it++)	{	
				cout << *it << " " ; }
			cout << endl;
		}

		inline bool operator< ( const Position & two) const
		{
			return position < two.position;
		} 
};

struct compare_count {
	bool operator() (const Position * one, const Position * two)
	{
		if (one->count != two->count)
			return one->count < two->count;
		else   return one->position < two->position;
	}
};


class Digit {
	public:
		int               value;
		set<Position*>    positions_list;
		int               count;
		int               equal_row;
		int               equal_column;

		Digit(const int input_value) : value(input_value) {
			count = 0;
		}

		Digit(const int input_value, set<Position*> & input_positions_list)
			: value(input_value) {
				count = 0;
				for ( set<Position*>::iterator it = input_positions_list.begin(); 
						it != input_positions_list.end(); it++) {
					if ( (*it)->possibles.find(value) != (*it)->possibles.end())
						positions_list.insert(*it);
				}
				count = positions_list.size();
				equal_row = -1;
				equal_column = -1;
			}

		int  update_count() {
			count = positions_list.size();
			return count; 
		}

		Position* solve() {

			if ( count == 1) {
				return (*positions_list.begin())->assign(value);
			}  else return NULL;
		}

		bool get_equal () {
			if (count < 2) {
				return false;
			}

			if (get_equal_diff(1)) {
				equal_row = (*positions_list.begin())->row;
				return true; 
			}
			if (get_equal_diff(9)) {
				equal_column = (*positions_list.begin())->column;
				return true;
			}
			return false;
		}

		bool get_equal_diff( const int diff) {
			int pre = (*positions_list.begin())->position;
			for ( set<Position*>::iterator it = ++positions_list.begin();
					it != positions_list.end();it++ ) {
				int current = (*it)->position;
				if ( diff != current - pre );
				return false;
				current = pre;
			}
			return true;
		}

		void update_assigned(Position * assigned) {
			if ( value == assigned->value) {
				update_value_assigned();
				return;
			}
			set<Position*>::iterator it = positions_list.find(assigned);
			if ( it == positions_list.end()) return ;
			positions_list.erase(it);
			count--;
		}

		void update_value_assigned() {
			positions_list.clear();
			count = 0;
		}

		bool solved() { return count == 0;}

		void print() {
			cout << endl;
			cout << "digit value " << value << " digit count " << count << endl;
			print_positions();
		}

		void print_positions() {
			for (set<Position*>::iterator it = positions_list.begin();
					it != positions_list.end(); it++) {
				cout << (*it)->position << " " << endl;
			}
		}



}; 

struct compare_digit_count {

	inline bool operator() (const  Digit* one, const Digit * two) {
		if (one->count != two->count) 
			return one->count < two->count;
		else    return one->value < two->value;
	}
};


/** Base class for rule classes, Row, Column, and Square. */
class Unit {
	public:

		int                       index;
		vector<Digit>             digits;
		set<Digit*, compare_digit_count>          
			digits_list; 
		set<int>                  values_list;
		set<Position*>            positions_list;
		int                       count;

		Unit(const int i) : index(i){
			for ( int i =0; i<9; i++)
			{
				values_list.insert(i+1);
			}
		}     

		void add_position ( Position * const this_position) {
			positions_list.insert(this_position); }

		void erase_value ( const int this_value ) { 
			values_list.erase(this_value); } 

		void update_count () { count = positions_list.size(); }

		void initiate_digits() {
			for ( int i = 1; i < 10 ; i++) {
				if (values_list.find(i) == values_list.end())
					digits.push_back(Digit(i));
				else {
					digits.push_back(Digit(i, positions_list));
				}
			}	

			for ( int i=0; i<9; i++) {
				if (!digits[i].solved())	
					digits_list.insert(&digits[i]);	
			}
		}     

		set<Position*> update_assigned(const Position* assigned) {

			set<Position*> result;
			values_list.erase(assigned->value);
			positions_list.erase(const_cast<Position*>(assigned)); 
			result = update_positions_list(assigned);
			update_digits_list(assigned);
			update_count();
			return result;
		}

		void update_updated (const int value, Position * updated) {
			digits_list.erase(&digits[value-1]);
			digits[value-1].positions_list.erase(updated);
			digits[value-1].update_count();
			if( !digits[value-1].solved() ) {
				digits_list.insert(&digits[value-1]);}
		
		}
	

		void update_digits_list(const Position * assigned) {
			for (set<int>::iterator num_it = assigned->possibles.begin();
					num_it != assigned->possibles.end(); num_it++)                        {
				digits_list.erase(&digits[(*num_it)-1]);
				digits[(*num_it)-1].update_assigned(const_cast<Position*>(assigned));
				if (!digits[(*num_it)-1].solved())
					digits_list.insert(&digits[(*num_it)-1]);
			} 
		}


		set<Position*> update_positions_list(const Position * assigned){
			set<Position*>result;
			for (set<Position*>::iterator position_it = positions_list.begin();
					position_it != positions_list.end() ; position_it++) {
				Position * updated=NULL;
				updated = (*position_it)->update_assigned(assigned->value);
				if (updated){
					result.insert(updated);
				}
			}
			return result;
		}

		Position* solve() {
			Position * position_ptr= NULL;
			if (count == 1) {
				position_ptr = (*positions_list.begin())->solve(); 
			} 
			else if ((*digits_list.begin())->count == 1)  {
				position_ptr = (*digits_list.begin())->solve();
			}
			return position_ptr;
		}

		bool solved() {  return count == 0;}

		void print() {
			cout << endl;
			cout << "index: " << index << endl;
			cout << "values: " ;
			cout << values_list.size() << endl;
			print_values();	
			cout << "positions: " ;
			cout << positions_list.size() << endl;
			print_positions();
			cout << "digits: " <<endl;
			print_digits();
		}

		void print_values() {

			for (set<int>::iterator it = values_list.begin();	
					it != values_list.end(); it++) {
				cout << " " << *it << " ";
			}
			cout << endl;
		}

		void print_positions() {
			for (set<Position*>::iterator it = positions_list.begin();
					it != positions_list.end();	it++) {
				cout << " " << (*it)->position << " ";
			}
			cout << endl;
		}

		void print_digits() {
			cout << "digits_list size " << digits_list.size() << endl;

			for (set<Digit*>::iterator it = digits_list.begin();
					it != digits_list.end(); it++) {
				(*it)->print();
			}
		}


};

struct compare_unit_count {
	bool operator() ( const Unit* one, const Unit * two) {
		if (one->count != two->count) 
			return one->count < two->count;
		else 	return one->index < two->index;
	}
};


/** Rule class for each row */
class Row : public Unit {
	public:

		Row(vector<Position> & grid, const int row_number) 
			: Unit(row_number) {
			for ( int i =0; i < 9; i++)
			{ 
				int position = row_number * 9 + i;
				if (grid[position].value < 0) {	
					add_position(&grid[position]);
				 } else
				erase_value(grid[position].value);
			}
			update_count();
		}

};


/** Rule class for each column */
class Column : public Unit {
	public:

		Column(vector<Position> & grid, const int column_number) 
			:Unit(column_number) {
			index += 9; 
			for ( int i =0; i < 9; i++)
			{
				int position = i * 9 + column_number;
				if (grid[position].value < 0 ) 
					add_position(&grid[position]);
				else	erase_value(grid[position].value);
			}
			update_count();
		}
};


/** Rule class for each sub 3*3 square. */
class Square : public Unit {
	public:
		Square(vector<Position> & grid, const int square_index)  
			:Unit(square_index) {
			index  += 18;
			for ( int i =0; i < 9; i++) {
				int position = (i/3 + square_index/3*3 )*9 + square_index%3*3 + i%3;
				if (grid[position].value < 0 ) 
					add_position(&grid[position]);
				else erase_value(grid[position].value);
			}
			update_count();
		}
};



/** Class to store and solve the Sudoku puzzle.
  * task_list, stores all rule classes that the one closed to be solved are
	ordered earlier.
  * positions_task, stores all grid positions that haven't been solved.
	They are ordered that the one with fewer possible numbers to be filled 
	in, or the one closer to be solved, are put earlier in the container.
  */
 
class Puzzle {
	public:
		vector<Position >                  grid;

		vector<Unit>                       units;          
		set<Unit*, compare_unit_count>     task_list;

		set<Position*, compare_count>      positions_task;

		Puzzle() {}

		Puzzle (const vector<int> & input_grid) {
			initialization_puzzle(input_grid);
		}


		void initialization_puzzle(const vector<int> & input_grid) {
			for (int i = 0; i < 9; i++)
				for (int j= 0; j < 9; j++) { 
					int       value = input_grid[i*9+j];
					grid.push_back(Position(i,j,value));
				}

			for (int i=0; i<27; i++) {
				int indicator = i/9;
				switch (indicator) {
					case 0:	
						units.push_back(Row(grid, i%9));
						break;
					case 1:
						units.push_back(Column(grid,i%9));
						break;
					case 2:
						units.push_back(Square(grid,i%9));
						break;
					default:
						break;
				}
			} 

			for ( int i=0; i<27; i++) {
				if (!units[i].solved())
					task_list.insert(&units[i]);
			}

			finalize_grid();

			for ( int i = 0; i <27; i++) {
				units[i].initiate_digits();
			}


		}

		void finalize_grid() {

			for (int i = 0; i < 9; i++) 
				for (int j=0; j<9 ; j++) {
					int position;
					position = i*9+j;
					if (grid[position].value > 0 ) continue;
					grid[position].initiate_possibles(
							units[i].values_list,
							units[j+9].values_list,units[18+i/3*3+j/3].values_list);
				}

			for ( int i =0; i < 81; i++) {
				if (!grid[i].solved())
					positions_task.insert(&grid[i]);
			}
		} 

		void update_all_units(Position * position) {

			update_one_unit(position->row,position); 
			update_one_unit(9+position->column, position); 
			update_one_unit(18+position->square, position); 
			positions_task.erase(position);
			position->possibles.clear();
		}

		void update_one_unit(const int index, Position * position) {
			set<Position*> result;
			task_list.erase(&units[index]);
			result = units[index].update_assigned(position);
			resort_positions_task(result); 
			update_update_all_units(position->value, result);
			if ( !units[index].solved())
				task_list.insert(&units[index]);
		}

		void update_update_all_units(const int value, set<Position*> & result) {
			for (set<Position*>::iterator it = result.begin();
				it != result.end(); it ++ ) {
				units[(*it)->row].update_updated(value, *it);
				units[9+(*it)->column].update_updated(value, *it);
				units[18+(*it)->square].update_updated(value, *it);
			}
		} 


		void resort_positions_task(set<Position*> & updated) {

			if (updated.empty() ) return;
			for (set<Position*>::iterator it = updated.begin();
					it != updated.end(); it++) {
				positions_task.erase(*it);
				(*it)->update_count();
				positions_task.insert(*it);
			}
		}

	 	Position *  solve_position_list() {
			Position * position = NULL;
			while ( (*positions_task.begin())->count == 1) {
				position = (*positions_task.begin())->solve(); 
				update_all_units(position);
				if (positions_task.empty()) break;
			}
			return   position;
		}

		bool solve() {
			Position * result = &Position();

			while( result ) {
				while(result) {
					if (positions_task.empty()) break;
					result =  solve_position_list();
				}
				result = solve_task_list();
				if (positions_task.empty()) return true;
			}

			try_solve();	
			return task_list.empty();
		}

		void try_solve() {
			set<int> all_cases = (*positions_task.begin())->possibles;
			set<int>::iterator it = all_cases.begin();

			Puzzle try_puzzle;
			vector<int> input_value = get_value_list();
			try_puzzle.initialization_puzzle(input_value); 
			Position * first_position = *try_puzzle.positions_task.begin();

			while (it != all_cases.end()){
				try {
					first_position->assign(*it);
					try_puzzle.update_all_units(first_position);
					try_puzzle.solve();	
				}	
				catch(...) {
					it++; 
					try_puzzle.clear();
					try_puzzle.initialization_puzzle(input_value);
					continue;
				}
				break;
			}
			if ( it != all_cases.end()) {
				this->clear();
				this->initialization_puzzle(try_puzzle.get_value_list());
			} else { throw -1;} 
			return;
		}

		void clear() {
			grid.clear();
			units.clear();
			task_list.clear();
			positions_task.clear();
		}		


		vector<int> get_value_list() {
			vector<int> result;
			for ( int i =0; i < 81; i++) {
				int value = grid[i].value;
				if ( value > 0) 
					result.push_back(grid[i].value);
				else
					result.push_back(-1);
			}
			return result;
		}

		Position* solve_task_list() {
			Position * position = NULL;
			set<Unit*>::iterator it = task_list.begin();
			while ( it != task_list.end() && !position)
			{
				Unit* this_unit = *it;
				position = (*it)->solve();
				if ( position ) { 
					update_all_units(position); 
					it = task_list.begin();
					break;
				}
				it ++;
			}
			return    position; 
		}

		void print_puzzle () {
			print_grid_value();
		}

		void print_grid_value() {
			for (int i=0; i<91 ; i++) {
				cout.setf(ios::right);
				if ( grid[i].value > 0)
					cout << setw(3) << grid[i].value ;
				else cout << setw(3) << "  " ;
				if (i%9 == 8)  cout << endl;
			}
		}
		void print_grid_position() {
			for (set<Position*>::iterator  it = positions_task.begin();
					it != positions_task.end(); it++) {
				(*it)->print();
			}
		}

		void print_task_list() {
			for (set<Unit*>::iterator it = task_list.begin();
					it != task_list.end(); it++) {
				print_task_list((*it)->index);	
			}
			for ( int i = 0; i < 27; i++) {
				units[i].print(); 
			}
		}

		void print_task_list(const int index_num) {
			units[index_num].print();
		}



}; 



#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
using namespace boost::python;
 
BOOST_PYTHON_MODULE(algorithm)
{
    def("Puzzle", puzzle);
}
/*
int main(int argc, char ** argv)
{
	if ( argc <2 ) return -1;
	ifstream infile (argv[1], ifstream::in);
	vector<int>  input(81);
	for ( int i=0; i<81; i++) {
		infile >> input[i]; 
	}

	Puzzle my_puzzle(input);
	my_puzzle.solve();
	my_puzzle.print_grid_value();

	infile.close();
}
*/
