#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cmath>

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}


// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
        nums.push_back(idCount);
        vars[idCount]->isFirst=true;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp,0);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);
    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){
    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);
    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fId = getFunction(fnc);
    int inpId1 = getVariable(inp1);
    int inpId2 = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId1]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);
    vars[inpId1]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addAssignment(string lvalue, string rvalue) {
    addUnaryFunction("identity",rvalue,lvalue);
}

void Graph::readGraph(string fileName){
    fstream infile(fileName);
    string line = "";
    while(getline(infile, line)) {
        vector<string> words;

        split1(line, words);

        if(words[0].compare("input")==0){
            int temp=getVariable(words[1]);
            inputNodes.push_back(temp);
            vars[temp]->isFirst=true;
        }
        else if(words[0].compare("output")==0){
            outputNode=getVariable(words[1]);
        }
        else{
            if(words.size() == 5)
                addBinaryFunction(words[2],words[3],words[4],words[0]);

            else if(words.size()==4)
                addUnaryFunction(words[2], words[3], words[0]);

            else
                addAssignment(words[0],words[2]);
        }

    }
}

bool Graph::isCyclic(){

    queue<Variable> que;
    for(int i=0;i<inputNodes.size();i++)
        que.push(*vars[inputNodes[i]]);

    for(int i=0;i<nums.size();i++)
        que.push(*vars[nums[i]]);

    while(!que.empty()){
        Variable curr=que.front();
        que.pop();
        if(vars[curr.id]->visit)
            return true;

        vars[curr.id]->visit=true;
        for(int i=0;i< vars[curr.id]->to.size();i++){
            int temp = vars[curr.id]->to[i]->id;
            if(!fncs[temp]->isCycle){
                que.push(*fncs[temp]->output);
            }
            else
                fncs[temp]->isCycle=false;
        }

    }

    return false;
}

double Graph::forwardPass(vector<double> inputValues){
    for(int i=0;i<inputValues.size();i++){
        vars[inputNodes[i]]->value = inputValues[i];
    }

    queue<Variable> que;
    for(int i=0;i<inputNodes.size();i++)
        que.push(*vars[inputNodes[i]]);

    for(int i=0;i<nums.size();i++)
        que.push(*vars[nums[i]]);

    while(!que.empty()){
        Variable curr=que.front();
        que.pop();
        for(int i=0;i< vars[curr.id]->to.size();i++){
            int temp = vars[curr.id]->to[i]->id;
            if(!fncs[temp]->isDouble){
                fncs[temp]->doForward();
                que.push(*fncs[temp]->output);
            }
            else
            fncs[temp]->isDouble=false;
        }
    }
    return vars[outputNode]->value;
}

vector<double> Graph::backwardPass(){

    vars[outputNode]->derivative=1;
    queue<int> que;
    que.push(outputNode);

    while(!que.empty()){
        int temp=que.front();
        que.pop();
        if(!vars[temp]->isFirst){
            int temp2=vars[temp]->from->id;
            fncs[temp2]->doBackward();
            for(int i=0;i<fncs[temp2]->inputs.size();i++){
                int temp3= fncs[temp2]->inputs[i]->id;
                vars[temp3]->numTo--;
                if(vars[temp3]->numTo==0)
                    que.push(temp3);
            }
        }
    }

    vector<double>vec;
    for(int i=0;i<inputNodes.size();i++){
        vec.push_back(vars[inputNodes[i]]->derivative);
    }

    return vec;
};

string Graph::outputname() {
    return vars[outputNode]->name;
}

vector<string> Graph::inputName() {
    vector<string> names;
    for(int i=0;i<inputNodes.size();i++)
        names.push_back(vars[inputNodes[i]]->name);

    return names;
}

 //Graph::~Graph() {

//}