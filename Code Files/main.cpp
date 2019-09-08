#include <iterator>
#include <sstream>
#include <iomanip>
#include "iostream"
#include "graph.h"
using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}
int main(int argc, char* argv[]){

    fstream infile(argv[2]);
    string line="";
    ofstream result;
    result.open(argv[3]);
    ofstream derivative;
    derivative.open(argv[4]);
    result << std::fixed;
    result << std::setprecision(30);
    derivative << std::fixed;
    derivative << std::setprecision(30);
    getline(infile,line);
    int count=0;
    Graph mg;
    mg.readGraph(argv[1]);
    if(mg.isCyclic()) {
        derivative << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
        result << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
        return 0;
    }
    while(getline(infile,line)){
        Graph g;
        g.readGraph(argv[1]);
        vector<string> words;

        split1(line,words);
        vector<double> vec;
        for (int j = 0; j < words.size(); ++j) {
            vec.push_back(stod(words[j]));
        }

        if(count==0){
            result<<g.outputname();
            derivative<<"d"+g.outputname()+"/d"+g.inputName()[0];

            for(int i=1;i<g.inputName().size();i++){
                derivative<<" d"+g.outputname()+"/d"+g.inputName()[i];
            }
            result<<endl;
            derivative<<endl;
        }
        count++;
        result<<g.forwardPass(vec)<<endl;
      vector<double> v=g.backwardPass();
      for(int i=0;i<v.size();i++)
            derivative<<v[i]<<" ";

        derivative<<endl;
    }
    return 0;
}
