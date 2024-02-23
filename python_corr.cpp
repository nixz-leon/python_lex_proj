#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string keywords[7] = {"if","else","elif","for","while","return","def"};

inline int toint(char in){
    return in-'0';
}
inline char tochar(int in){
    return in+'0';
}

inline string condition_line(string input){
    int space_count=0;
    int indent_count = 0;
    for(int i =0; i< (int)input.size(); i++){
        if(input[i] == ' '){
            space_count++;
        }else{
            break;
        }
    }
    int temp = (int)(((float)space_count/4.f)+0.5f); 
    indent_count += temp;
    //now just need to need to add a char to represent level of indentation
    input = tochar(indent_count) + input.substr(space_count,input.length());
    return input;
}


inline bool check_print(string input){
    if(input.substr(1,6) == "print(" && (input[input.size()-2] == ')' || input.back() == ')')){
        return true;
    }
    return false;
}

inline string uncondition_line(string input){
    string temp = "";
    for(int i =0; i<toint(input[0]); i++){
        temp += "    ";
    }
    input = temp + input.substr(1,input.size());
    return input;
}

inline string check_keyword(string input){
    input = input.substr(1,input.size());
    string keyword = "";
    
    // first need to ident key word
    // if no key word then exit
    // if first char is the comment symbol, exit it doesn't matter
    // then check if key word is using proper syntax
    // if key word has proper syntax return key word identified

    return keyword;
}   


int main(){
    vector<string> lines;
    string filename = "test.py";
    string outfilename = "correct.txt";
    fstream file;
    file.open(filename);
    ofstream outfile;
    outfile.open(outfilename);
    int print_count = 0;


    string line ="";
    while(getline(file,line)){   
        if(line != ""){
            outfile << line << endl;
            lines.push_back(condition_line(line));   
        }
    }


    int indentation=0;
    int loop_count = 0;
    int curr_indent =0;
    int min_statement = 0;

    for(int i=0; i < (int)lines.size(); i++){
        cout << lines[i] << endl;
    }

    for(int i=0; i < (int)lines.size(); i++){
        print_count += (int)check_print(lines[i]);  
        if(lines[i][lines[i].size()-2] == ':'){
            //need to add indentation check here
            if(toint(lines[i][0]) != indentation){
                lines[i][0] = tochar(indentation);
            }
            indentation++;
            loop_count++;
            min_statement = 1;
            //here just need to check for char d at position 1; if so call the correct function function
            
        }else{
            //For logic diagram, refer to pdf posted in the discord
            curr_indent = toint(lines[i][0]);
            if(curr_indent!=indentation){
                if(min_statement == 0){//here i have min_statement = 0, which in this case is the inverse of min_statment = 1;
                    if(curr_indent <= indentation-loop_count){
                        if(lines[i-1][0] == lines[i+1][0]){
                            cout << lines[i+1] << endl;
                            cout << indentation << endl;
                            curr_indent = indentation;
                        }else{
                            indentation -= loop_count;
                            curr_indent = indentation;
                            loop_count = 0;
                        }
                        
                    }else if(curr_indent < indentation){
                        if(lines[i-1][0] == lines[i+1][0]){
                            cout << lines[i+1] << endl;
                            cout << indentation << endl;
                            curr_indent = indentation;
                        }else{
                            loop_count -= indentation-curr_indent;
                            indentation = curr_indent;
                        }
                    }else{
                        curr_indent = indentation;
                    }
                }else{
                    curr_indent = indentation;
                    min_statement = 0;
                }
            }else{
                min_statement = 0;
            }
            cout << indentation << endl;
            lines[i][0]= tochar(curr_indent);
        }
    }

    outfile << " " << endl;//adding seperation between the two files
    outfile << " " << endl;
    outfile << " " << endl;
    for(int i=0; i < (int)lines.size(); i++){
        outfile << uncondition_line(lines[i]) << endl;
    }
    outfile << endl << endl << endl;
    outfile << print_count << endl;
    
}



