//basic setup
//read data from a file
//write function for keyword
//write function for separator
//write function for identifier
//write function for operator
//write function for literal
//comments

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void tokenize(char s[]);
int isOperator(char s[]);

int comment=0, literal=0;

int isLiteral(char s[] ){
  int i=0;
  while(i<strlen(s) && isdigit(s[i])){
      i++;
  }
  if(i== strlen(s)) printf("Literal: %s \n",s);
  if(s[0] == '"' && s[strlen(s)-1] == '"'){
      printf("Literal: %s \n",s);
  }
               
  return 1;  
}

int isIdentifier(char s[]){
    char functions[3][10]={"main","printf","scanf"};
               
    for(int i=0;i<3;i++){
        if(strcmp(functions[i],s)==0)
            {   
                printf("Identifier: %s \n",s);
                return 1;
            }
    }
    

    int i=0;
    if(!isdigit(s[0]) && strlen(s)<32){
        while(i<strlen(s) &&(isalnum(s[i]) || s[i]=='_' )){
        i++;
        }
    

    if(i==strlen(s)) {
        printf("Identifier: %s \n",s);        
        return 1;}
    }
    if( isdigit(s[0])|| strlen(s)>32 || !(isalpha(s[0]))) 
        {   if(!isLiteral(s))
                printf("Invalid Identifier: %s \n",s);
            return 0;
        }
    return 0;
}

int isKeyword(char s[]){
    char keywords[32][10] = {"auto","break","case","char","const","continue","default",
                    "do","double","else","enum","extern","float","for","goto",
                        "if","int","long","register","return","short","signed",
                        "sizeof","static","struct","switch","typedef","union",
                        "unsigned","void","volatile","while"};
    for(int i=0;i<32;i++){
        if(strcmp(keywords[i],s)==0)
            return 1;
    }
    return 0;
}

    
void isComment(char s[]){

}

int isOperator(char s[]){
    int i=0;
     
     if(s[i]=='+' || s[i]=='-' || s[i] == '/' || s[i] == '*' || s[i] == '&' || s[i] == '%' || s[i] == '='){
           printf("Operator: %s \n",s);
           if(i+1 < strlen(s))
                return 1;
     }
    return 0;
}
char* substr(char s[],int start,int index){
    char * str = (char *)malloc(32*(sizeof(char)));
    
    int i=0;
    while(start<=index){
        str[i++] = s[start];
        start++;
    }
    return str;
}
int isSeparator(char s[]){
    int i=0;
    while(s[i]!='\0'){
        if(s[i]==';' || s[i]==',' || s[i] == '{' || s[i] == '}' || s[i] == '(' || s[i] == ')')
            {   
                
                if(i!=0)
                    {   char *s1 = substr(s,0,i-1);        
                        tokenize(s1);
                    }
                 printf("Separator: %c \n",s[i]);
               
                if(i!=strlen(s)-1){
                        char *s1 = substr(s,i+1,strlen(s)-1);
                        tokenize(s1);
                }
                return 1;
            }
            i++;
    }
    return 0;
}

void tokenize(char s[]){
   
    if(s[0]=='#') return;
    if(s[0]=='<' && s[strlen(s)-3]=='.') return;
    if(isKeyword(s)) printf("Keyword: %s \n",s);
    else if(isSeparator(s)) return;
    else if(isOperator(s)) return;
    else if(isIdentifier(s)) return;
    
}

int main()
{
   int num;char s[32];

   FILE *fptr;

   fptr = fopen("test.c","r");

   if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
   int flag=0;
    while(!feof(fptr))
    {   fscanf(fptr,"%s",s);
    
        if(strlen(s)>=2 && s[0]=='/' && s[1]=='*') {
            flag=1;
        }
        if(flag==0 && strlen(s)!=0) tokenize(s);
        if(flag==1 && strlen(s)>=2){
            int l = strlen(s);
            //printf("comment : %c %c\n",s[l-2],s[l-1]);
            printf("comment : %s  \n",s);
           
            if(s[l-2]=='*' && s[l-1]=='/') {
            flag=0;
        }
        }
		
    }
   fclose(fptr);

   return 0;
}

