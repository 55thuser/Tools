using namespace std;
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#define BUFSIZE 128
char* stringToCharPointer(string input){
    char* output = new char[input.length() +1];
    strcpy(output, input.c_str());
    return output;
}
void my_outputCAP(vector<string>& memory, string COM){
    char* popenInput = stringToCharPointer(COM);
    char buf[BUFSIZE] = {0};
    FILE *fp;

    if ((fp = popen(popenInput, "r")) == NULL) {
        cout<<"Error opening pipe!\n";
        return;
    }
    else{
        while (fgets(buf, BUFSIZE, fp) != NULL) {
            //system("echo hello");
            memory.push_back(buf);
            //printf("OUTPUT: %s", buf);
        }
    }
    if (pclose(fp)) {
        cout<<"Command not found or exited with error status\n";
        return;
    }
    return;


}
int main(){
    vector<string> output;
    my_outputCAP(output,"ls");
    for(int i = 0; i<output.size(); i++){
        cout<<output[i];
    }
}
