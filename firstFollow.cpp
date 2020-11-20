#include<bits/stdc++.h>
using namespace std;

string startSymbol;
int lookahead=0;
int error =0;
stack<string> nextNonTerminal;
set<string> visited;
void findFirst(string production,vector<string>& productions,set<string> first){
    string nonTerminal = "";
    if(production[1]=='_')
        nonTerminal= production.substr(0,2);
    else
        nonTerminal = production[0];
    cout<<nonTerminal<<endl;

}
int main(){
    set<string> first;
    set<string> follow;
    cout<<"Expecting to input without spaces";
    int noOfProductions;
    cout<<"\n Number of Productions in the Grammar:";
    cin>>noOfProductions;
    vector<string> productions;
    cout<<"\n Productions: \n";
    int count=0;
    for(int i=0;i<noOfProductions+1;i++){
        string x;    
        getline(cin,x);
        productions.push_back(x);
        if(count ==1){
            startSymbol = productions[i][0] ;
            
        }
        count++;
    }
    eliminateLeftRecursion(productions);
    for(auto x: productions){
        first.clear();
        findFirst(x,productions,first);
       // cout<<x<<endl;
    }

    
     
}
    

/*E–>E+T|T
T–>T*F|F
F–>(E)|id


        if(flag==1)
            cout<<"}";*/