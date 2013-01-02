#include<map>
#include<iostream>
#include<vector>
using namespace std;


int calculate ( const int i , map<int,int> & map_score, map<int, vector<int> > & map_tree)
{
      if ( map_score[i] >= 0) return map_score[i];
      if ( map_tree[i].size() == 0) { map_score[i] = 0; return 0;}
      map_score[i] = map_tree[i].size(); 

      for ( vector<int>::iterator it2 = map_tree[i].begin(); it2 != map_tree[i].end(); it2++)
      {
            map_score[i] += calculate(*it2, map_score, map_tree); 
      }
      return map_score[i];

}







int main()
{
      int remove_step = 0;

      int node_num, vertice_num;
      cin >> node_num >> vertice_num;
      node_num++;

      map<int, vector<int> > map_tree;

      for ( int i = 0; i < node_num; i++)
      {
           map_tree[i] = vector<int>();
      }

      for (int j = 0; j < vertice_num; j++)
      {
           int first_node, second_node;
           cin >> first_node >> second_node;

           map_tree[second_node].push_back(first_node);
       }
       map<int, int>  map_score;
       for ( int i =0; i <node_num; i++)
       {
           map_score[i] = -1;
       }   

       for ( int i = 1; i < node_num; i++) 
       {
           int this_number;
           this_number = calculate ( i, map_score, map_tree); 
           if ( this_number %2 == 1) remove_step ++;
         
       }  
       remove_step--;
       cout << remove_step << endl; 
}

