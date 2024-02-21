#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

inline string condition_line(string input){
    int space_count=0;
    int indent_count = 0;
    for(int i =0; i< input.size(); i++){
        if(input[i] == ' '){
            space_count++;
        }
    }
    int temp = (int)(((float)space_count/4.f)+0.5f); // this method is suggesting that x+3 spaces is an error for n+1 tab not that it is meant to be n-3 tabs
    indent_count += temp;
    //now just need to need to add a char to represent level of indentation
    input = to_string(indent_count) + input.substr(space_count,input.length()-2);
    return input;
}


int main(){
    string filename;
    ios file(filename);
    string line;
}



