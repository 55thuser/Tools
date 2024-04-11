#include <stdio.h>
#include <string.h>
#include <ctype.h>

void left(char word[]);
void right(char word[]);
void inc(char word[]);
void dec(char word[]);

int main(int argc, char *argv[]) {
   if(!(argc==3)){
      printf("Invalid number of arguments");
      return 0;
   }
   char word[20];
   char curCom;
   int numCom = strlen(argv[2]);
   char commands[99];
   strcpy(commands, argv[2]);
   //printf("!!!!!!!");
   FILE *fp = fopen(argv[1],"r");
   //printf("????????");
   if(fopen(argv[1],"r") == 0){
      printf("Could not open file '%s'", argv[1]);
      return 0;
   }

   else{
      fscanf(fp,"%s",word);
      while(!feof(fp)){
         //printf("%s", word);

         //printf("%c", curCom);

         for(int i = 0; i<numCom; i++){
            curCom = commands[i];
            if(curCom=='L'){
               left(word);
               //printf("!");
            }
            else if(curCom=='R'){
               right(word);
               //printf("r");
            }
            else if(curCom=='I'){
               inc(word);
            }
            else if(curCom=='D'){
               dec(word);
            }
            else{
               printf("You threw off my schwiftiness with schwifty '%c'!", curCom);
               return 0;
            }
         }
         printf("%s\n", word);
         fscanf(fp,"%s",word);
         //printf("%s\n", word);
      }
   }
    
   return 0;
}

void left(char word[]) {
   char temp = word[0];
   for(int i = 0; i<strlen(word)-1; i++){
      word[i] = word[i+1];
   }
   word[strlen(word)-1]= temp;
   //printf("%s\n", word);
}

void right(char word[]) {
   char temp = word[strlen(word)-1];
   for(int i = strlen(word)-1; i>0; i--){
      word[i] = word[i-1];
   }
   word[0] = temp;
   //printf("%s\n", word);
}

void inc(char word[]) {
   for(int i = 0; i<strlen(word); i++){
      if(word[i]=='z'){
         word[i]='a';
      }
      else if(word[i]=='Z'){
         word[i]='A';
      }
      else if(word[i]=='9'){
         word[i]='0';
      }
      else if((isdigit(word[i])==0)&&(isalpha(word[i])==0)){

      }
      else{
         word[i] = word[i]+1;
      }
   }
}

void dec(char word[]) {
   for(int i = 0; i<strlen(word); i++){
      if(word[i]=='a'){
         word[i]='z';
      }
      else if(word[i]=='A'){
         word[i]='Z';
      }
      else if(word[i]=='0'){
         word[i]='9';
      }
      else if((isdigit(word[i])==0)&&(isalpha(word[i])==0)){

      }
      else{
         word[i] = word[i]-1;
      }
   }
}
