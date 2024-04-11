#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
int main(){
    char input[100];
    //bool END = false;
    printf("Enter a token to identify, EOF to stop: ");
    scanf("%s", input);
    while(!feof(stdin)){
        bool negative = false;
        bool binary = false;
        bool GUID = false;
        bool DUB = false;
        bool num = true;
        //printf("Enter a token to identify, EOF to stop: ");
        //scanf("%s", input);
        for(int i = 0; i<strlen(input); i++){
           // printf("!");
            if(input[0]=='-'){
                negative = true;
                //printf("NEG");
            }
            if(input[i]=='.' && isdigit(input[i+1]) && isdigit(input[i-1])){
                DUB = true;
                //printf("DUB");
            }
            if(input[0]=='0' && input[1]=='b' && input[2] != ' '){
                binary = true;
            }
            if(input[8]=='-' && input[13]=='-' && input[18]=='-' && input[23]=='-' ){
                GUID =true;
            }
            if(!isdigit(input[i]) && input[0]!= '-'){
                num = false;
            }

        }
        if(GUID){
            printf("The token is a GUID\n");
            //GUID = false;
        }
        else if(binary){
            printf("The token is a binary number\n");
        }
        else if(DUB){
            if(negative){
                printf("The token is a negative floating-point number\n");
            }
            else{
                printf("The token is a positive floating-point number\n");
            }
        }
        else if(num){
            if(negative){
                printf("The token is a negative integer\n");
            }
            else{
                printf("The token is a positive integer\n");
            }
        }
        else{
            printf("The token cannot be identified\n");
        }
        
        for(int i = 0; i<100; i++){
            input[i] = ' ';
        }
        printf("Enter a token to identify, EOF to stop: ");
        scanf("%s", input);
        if(feof(stdin)){
            return 0;
        }
    }
    return 0;
}