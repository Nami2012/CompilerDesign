#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct node{
    int state;
    node* next;
};

class DFA{
    private:
        int noOfAlphabets;
        vector<char> alphabets;
        int noOfStates;
        int noOfFinalStates;
        set<int> finalStates;
        int noOfTransitions;
        vector<vector<node*>> transitions;
        vector<vector<int>> table;
        vector<set<int>> minimised_states;
        vector<vector<node*>> minimised_transitions;
        set<int> minimizedFinalStates;

    public:
        void setAlphabets(){
            cout<<"\n No Of Alphabets: ";
            cin>>noOfAlphabets;
            cout<<"\n Enter alphabets: ";
            for(int i=0;i<noOfAlphabets;i++){
                char ch;
                cin>>ch; 
                alphabets.push_back(ch);
            }
            cout<<"\n alphabets are ";
            for(int i=0;i<noOfAlphabets;i++)
                cout<<alphabets[i];
        }

        void setStates(){
            cout<<"\n No Of States: ";
            cin>>noOfStates;

            cout<<"\n No Of Final States: ";
            cin>>noOfFinalStates;
            cout<<"\n Enter Final States: ";
            for(int i=0;i<noOfFinalStates;i++){
                int x;
                cin>>x;
                finalStates.insert(x);
            }

        }
        int findAlpha(char c){
            for(int i=0;i<noOfAlphabets;i++){
                if(alphabets[i]==c)
                    return i;
            }
            return -1;
        }
        void insertTransitions(){
            
            cout<<"\n No Of Transitions:";
            cin>>noOfTransitions;
            transitions.resize(noOfStates);
            cout<<"\n Enter Transitions in the form : Start alphabet next \n ";
            for (int i = 0; i < noOfStates; ++i){
                    transitions[i].resize(noOfAlphabets);
                    for(int j=0;j<noOfAlphabets;j++){
                        transitions[i][j]=NULL;
                    }
            }
                   
            for(int i=0;i<noOfTransitions;i++){
                int start,next;char alphabet;
                cin>>start>>alphabet>>next;
                int j;
                struct node *temp;
                j=findAlpha(alphabet);
                if(j==-1)
                {
                    cout<<"error\n";
                    exit(0);
                }
                temp=(struct node *)malloc(sizeof(struct node));
                temp->state=next;
                temp->next=transitions[start][j];
                transitions[start][j]=temp;
            }
                        
        }

        void generateTable(){

           //keep in mind to consider only those i <j;
            table.assign(noOfStates, {} );
           for (int i = 0; i < noOfStates; ++i){
                    table[i].assign(noOfStates,0);
            }

        }
        void initialMarkTable(){
            //keep in mind to consider only those i <j;
           for (int i = 0; i < noOfStates; ++i){
                for(int j=0;j<i;j++){
                        if((finalStates.find(i)!=finalStates.end() 
                            && finalStates.find(j)== finalStates.end())||
                            (finalStates.find(j)!=finalStates.end() 
                            && finalStates.find(i)== finalStates.end()))
                            {
                                table[i][j]=1;
                            }

                    }
            }

            
            }
        

        void completeMarkTable(){
           int flag =0;
           while(flag == 0){
               flag =1;
            for(int j=0;j<noOfAlphabets;j++){
               for (int i = 0; i < noOfStates; ++i){
                    for(int k=0;k<i;k++){
                       if(table[i][k]==1) continue;
                       int rowState = transitions[i][j]!=NULL? transitions[i][j]->state:-1;
                       int columnState = transitions[k][j]!=NULL? transitions[k][j]->state:-1; 
                       if(rowState == -1 || columnState ==-1){
                           continue;
                       }
                       if(table[rowState][columnState]==1){
                           if(table[i][k]==0){
                               flag = 0;
                               table[i][k]=1;
                           }
                       }

                    }
                }
            }
           }

           for (int i = 0; i < noOfStates; ++i){
                for(int j=0;j<i;j++){
                               cout<<table[i][j];

                            }
                    cout<<endl;
                    }
        }
        void insertIntoExistingState(int a,int b){
            for(int i = 0;i<minimised_states.size();i++){
                if(minimised_states[i].count(a)!=0||minimised_states[i].count(b)!=0){
                    minimised_states[i].insert({a,b});
                }
            }
        }
        void minimisedStates(){
            //find non marked columns;
            vector<int> visited(noOfStates,0);

            for (int i = 0; i < noOfStates; ++i){
                for(int j=0;j<i;j++){
                        if(table[i][j]==0){
                            if(visited[i]!=0 || visited[j]!=0){
                                insertIntoExistingState(i,j);
                                visited[i]=1;
                                visited[j]=1;
                            }
                            else{
                                minimised_states.push_back({i,j});
                                visited[i]=1;
                                visited[j]=1;
                            }
                        }

                }
            }
            for(int i=0;i<visited.size();i++){
                if(visited[i]!=1){
                    minimised_states.push_back({i});
                }
            }
            for(int i=0;i<minimised_states.size();i++){
                for(auto x:minimised_states[i]){
                    cout<<x;
                }
                cout<<endl;
            }
        }
        void setMinimizedFinalStates(){
            for(int i = 0;i<minimised_states.size();i++){
                for(auto x:minimised_states[i] ){
                    if(finalStates.count(x)!=0){
                        minimizedFinalStates.insert(i);        
                    }
                }
            }
        }

        int findIndex(int next){
            for(int i = 0;i<minimised_states.size();i++){
                if(minimised_states[i].count(next)!=0){
                    return i;
                }
            }
            return -1;
        }

        void minimisedTransitions(){
             int size= minimised_states.size();
             minimised_transitions.assign(size,{});
             for (int i = 0; i < size; ++i){
                    minimised_transitions[i].assign(noOfAlphabets,NULL);
            }
            struct node *temp;
                
            for(int i=0;i<size;i++){
                for(int j=0;j<noOfAlphabets;j++){
                    for(auto state:minimised_states[i]){
                        
                        int next = transitions[state][j]->state;
                    
                        int k = findIndex(next);
                        cout<<state<<" "<<i<<endl;
                        temp=(struct node *)malloc(sizeof(struct node));
                        temp->state=k;
                        temp->next=minimised_transitions[i][j];
                        minimised_transitions[i][j]=temp;
                    }
                    
                }
            }
        }

        void printMinimizedDfa(){
            cout<<"\n Minimized DFA: \n";
            for(int i=0;i<minimised_states.size();i++){
                
                for(int j=0;j<noOfAlphabets;j++){

                    if(minimised_transitions[i][j]!=NULL){
                        cout<<"{ ";
                        for(auto state: minimised_states[i]){
                            cout<<state<<", ";
                        }
                        cout<<"}   ";
                        cout<<alphabets[j]<<"    ";
                        int next = minimised_transitions[i][j]->state;
                        cout<<"{ ";
                        for(auto state: minimised_states[next]){
                            cout<<state<<", ";
                        }
                        cout<<"}   ";
                    }
                    cout<<endl;
                }
                
            }
            cout<<"\n Final States :";
            for(auto x: minimizedFinalStates){
                cout<<"{ ";
                for(auto y:minimised_states[x])
                    cout<<y<<" ,";
                cout<<"}";
            }
        }

        void minimizeDfa(){
            generateTable();
            initialMarkTable();
            completeMarkTable();
            minimisedStates();
            setMinimizedFinalStates();
            minimisedTransitions();
            printMinimizedDfa();
        }
        //generate table;
        //figure row element of final state and column not eleement of for all table row<col
        //set flag;
        
        DFA(){
            setAlphabets();
            setStates();
            insertTransitions();
            minimizeDfa();
        }

};


int main(){

    DFA dfa;

}

/*
2
0 1
6
3
2 3 4
12

0 0 1
0 1 2
1 0 0
1 1 3
2 0 4
2 1 5
3 0 4
3 1 5
4 0 4
4 1 5
5 0 5
5 1 5


*/