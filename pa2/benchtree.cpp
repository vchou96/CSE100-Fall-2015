#include "BST.hpp"
#include "RST.hpp"
#include "countint.hpp"
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;



int main(int argc, char** argv) {

    cout << "# Benchmarking average number of comparisons for successful find" << endl;

    int bstbool=0;
    int rstbool=0;
    int setbool=0;
    int shuffled=0;
    int N=0;
    int run=0;
    int num = 1;

    srand(time(0));

 
    for (int i=1; i<argc; i++){
      std::string arg(argv[i]);
      if(!arg.compare("bst")){
        bstbool=1;  
        cout << "# Data structure: bst" << endl;
      }
      if(!arg.compare("rst")){
        rstbool=1;  
        cout << "# Data structure: rst" << endl;
      }
      if(!arg.compare("set")){
        setbool=1; 
        cout << "# Data structure: set" << endl; 
      }
      if(!arg.compare("sorted")){
        cout << "# Data: sorted" << endl;         
      }
      if(!arg.compare("shuffled")){
        shuffled=1;  
        cout << "# Data: shuffled" << endl;                 
      }     
      if(i==3){
        N=atoi(argv[i]);
        cout << "# N is powers of 2, minus 1, from 1 to " << argv[i] << endl;                 
      }
      if(i==4){
        run=atoi(argv[i]);
        cout << "# Averaging over " << argv[i] << " runs for each N" << endl;
      }
    }
    
    //cout << "#" << endl;
    //cout << "# N" << '\t' << "avgcomps" << '\t' << "stdev" << endl;
    std::vector<countint> v;  
     
    while(num<=N){
      double stdev = 0;
      double squared=0;
      double avgcomps=0;   
      for(int j=0; j<run; j++){
        v.clear();
        for (int i=0; i<num; ++i){
          v.push_back(i);
        }
        BST<countint> bst;
        RST<countint> rst;
        set<countint> sset;
        
        if(shuffled){
          std::random_shuffle(v.begin(),v.end());
        }
   
        vector<countint>::iterator vit = v.begin();
        vector<countint>::iterator ven = v.end();

        for(vit = v.begin(); vit != ven; ++vit) {
          if(setbool){
            sset.insert(*vit);
          }
          if(bstbool){
            bst.insert(*vit);
          }
          if(rstbool){
            rst.insert(*vit);
          }
        }

        countint::clearcount();
        for(vit = v.begin(); vit != ven; ++vit) {
          if(setbool){
            sset.find(*vit);
          }
          if(bstbool){
            bst.find(*vit);
          }
          if(rstbool){
            rst.find(*vit);
          }
        }
        avgcomps = countint::getcount()/(double)num;
        stdev = stdev + avgcomps;
        squared= squared + (avgcomps * avgcomps);
      }
      avgcomps= stdev/run;
      squared= squared/run;
      stdev= sqrt(squared - (avgcomps * avgcomps));
      if(stdev!=stdev){
        stdev=0;
      }
      cout<< num << "\t" << avgcomps << "\t" << stdev << endl;
      num=(num*2)+1;
    } 
    return 0;
}
