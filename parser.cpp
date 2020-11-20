#include<stdio.h>
#include<stdlib.h>

int main(){
    char str[20][20];
    int noOfProductions;
    int alpha,beta;
    char non_terminal;
    scanf("%d",&noOfProductions);
    for(int i=0;i<noOfProductions;i++)
    {
        scanf("%s",str[i]);     
    }
    int last=noOfProductions;
    int index=3;
    for(int i=0;i<noOfProductions;i++){
        non_terminal=str[i][0];  
         if(non_terminal==str[i][index]) {  
                alpha=index+1;  
                while(str[i][index]!=0 && str[i][index]!='|')  
                      index++;  
                if(str[i][index]!=0) {  
                    beta=index+1;  
                
                str[last][0] = non_terminal;
                str[last][1] = '-';
                str[last][2] = '>';
                int subIndex = 2;
                 while (str[i][beta]!=0)
                {
                     str[last][subIndex++] = str[i][beta];
                } 
                 str[last][subIndex++] = non_terminal;
                  str[last][subIndex++] ='`';
                last++;
                str[last][0] = non_terminal;
                str[last][1] = '`';
                str[last][2] = '-';
                str[last][3] = '-';
                subIndex = 3;
                while(str[i][alpha++]!='|' || str[i][alpha++]!=0){
                    str[last][++subIndex]=str[i][alpha++];
                }
                str[last][++subIndex] = non_terminal;
                str[last][++subIndex] = '`';
                str[last][++subIndex] = '|';
                str[last][++subIndex] = non_terminal;

                
                
                 }  

        }


        for(int i=0;i<last;i++){
            printf("%s\n",str[i]);
        }
    }

}
/*
3
E->E+T|T
T->T*F|F
F->(E)|id
*/
