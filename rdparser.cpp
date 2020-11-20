#include<bits/stdc++.h>
using namespace std;

string startSymbol;
int lookahead=0;
int error =0;
stack<string> nextNonTerminal;
set<string> visited;
void eliminateLeftRecursion( vector<string>& productions){
    string non_terminal,alpha,beta;
    for(int i=0;i<productions.size();i++){
        //cout<<productions[i][5]<<endl;
        if(productions[i].size()==0)
            continue;
        if(productions[i][0] == productions[i][5]){
            non_terminal = productions[i][0];
            alpha ="";
            int j;
            for(j=6;j<productions[i].size()&&productions[i][j]!='|';j++){
                alpha += productions[i][j];
            }
            beta = "";
            j++;
            for(j;j<productions[i].size();j++){
                beta += productions[i][j];
            }
            string new_production = non_terminal+"->"+beta+non_terminal+"_";
            productions.insert(productions.begin()+i,new_production);
            new_production = non_terminal+"_"+"->"+alpha+non_terminal+"_"+"|"+"e";
            productions.insert(productions.begin()+i+1,new_production);
            productions.erase(productions.begin()+i+2);
            
            i+=1;
        }

    }
}


int find(string nonterminal,vector<string> productions){
    int size = nonterminal.size();
    for(int i=0;i<productions.size();i++){
       if((size==1 && productions[i].substr(0, 1)==nonterminal && productions[i][1]!='_') || (size==2 && productions[i].substr(0,2)==nonterminal)){
           
           //cout << productions[i] ;
           return i;
       }
    }
    return 0;
}

void NonTerminal(string nonTerminal,vector<string> productions){
    
    int index = find(nonTerminal,productions);
    string production = productions[index];
    if(visited.find(nonTerminal)!=visited.end()){
        nextNonTerminal.pop();
        if(!nextNonTerminal.empty())
            NonTerminal(nextNonTerminal.top(),productions);
        return;
    }
        
    visited.insert(nonTerminal);
    cout<<endl<<"void "<<nonTerminal<<"(){"<<endl;
    nextNonTerminal.pop();
    int i=0;int flag=0;
    while(i<production.size()&& production[i]!='>'){
        i++;
    }
    i++;
    for(i;i<production.size();i++){
        if(i+1<production.size() && production[i+1]=='_'){
            nextNonTerminal.push(production.substr(i,2));
            cout<<"\t"<<production.substr(i,2)<<"();"<<endl;
            i++;
            continue;
        }
        if( isupper(production[i])){
            nextNonTerminal.push(production.substr(i,1));
            cout<<"\t"<<production.substr(i,1)<<"();"<<endl;
            continue;
        }
        if(i+1<production.size() && production.substr(i,2)=="|e"){
            cout<<"}"<<endl;
            cout<<"else {" <<endl;
            cout<<"return ;"<<endl;
            cout<<"}"<<endl;
            flag=0;
            break;
        }
        if(production[i]=='|'){
            cout<<"return;"<<endl;
            cout<<"}";
            flag=0;
            continue;
        };
        cout<<"\t if(l=='"<<production[i]<<"'){" <<endl;
        cout<<"\t\t match('"<<production[i]<<"');"<<endl;
        flag =1;
    }
    if(flag==1)
        cout<<"}"<<endl;
    if(nonTerminal==startSymbol){
        cout<<"if (l == '$')"; 
        cout<<"\t cout<<\"Parsing Successful\""<<endl;
    }
    cout<<"}";
    cout<<endl;
    
    if(!nextNonTerminal.empty()){
        NonTerminal(nextNonTerminal.top(),productions);
    }
}



int main(){
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
        cout<<x<<endl;
    }
    
    cout<<"\n Recursive Descent Parser is:";
    nextNonTerminal.push(startSymbol);
    NonTerminal(startSymbol,productions); 
    
    cout<<"match(char t) \n";
    cout<<"{\n"; 
    cout<<"\t if (l == t) { \n";
    cout<<"\t \t   l = getchar(); \n"; 
    cout<<"\t \t}\n"; 
    cout<<"]\t else";
    cout<<"cout<<\"Error\";";
    cout<<"}";
   
}
    

/*E–>E+T|T
T–>T*F|F
F–>(E)|id


        if(flag==1)
            cout<<"}";*/