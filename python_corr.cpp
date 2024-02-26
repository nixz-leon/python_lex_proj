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
    input.erase(0,space_count);
    input = tochar(indent_count) + input; 
    while(isspace(input.back())){//removing white spaces from each string
        input.erase(input.size()-1);
    }
    return input;
}

inline bool check_print(string input){
    if(input.substr(1,6) == "print(" && input.back() == ')'){return true;}
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
    int g =0;
    while(getline(file,line)){   
        if(line != ""){
            outfile << line << endl;
            lines.push_back(condition_line(line));
            print_count += (int)check_print(lines[g]);   
            g++;
        }
    }
    int loop_count = 0;
    int n1;int n2 = toint(lines[0][0]);int n3 = toint(lines[1][0]);
    char e1; char e2= lines[0][lines[0].size()-1];char e3= lines[1][lines[1].size()-1];


    for(int i =0; i < (int)lines.size()-2; i++){
        n1 = n2; n2 = n3; // indent count, n1, n2, n3, since we iterate only line line at a time, 
        n3 = toint(lines[i+2][0]);
        e1 = e2; e2 = e3; // these are ending char, makes the rest of the code more readable
        e3 = lines[i+2].back();
        if(e1 == ':'){
            loop_count++;
            if((n1+1)!=n2){n2 = n1+1;}
            if(n2<n3){n3=n2;};
        }
        else if((e2==e1) & (e1 == ':')){n2 = n1+1;n3 = n2+1;}
        else if ((e2==e3) & (e2 == ':')){n2 = n1; n3 = n2+1;}
        else if (e2 == ':'){if(n1!=n3){n3=n1;}}
        else{
            cout << "con 4" << endl;
            if(n1==n3){n2=n3;}
            else if((n1==n2) & (n2>n3)){loop_count = n2-n3;}
            else if((n1==n2) & (n2<n3)){n3=n2;}
            else if((n2==n3) & (n1>n2)){loop_count=n2;}
            else if((n2==n3) & (n1<n2)){n2=n1;n3=n1;}
        }
        lines[i][0] = tochar(n1);
        lines[i+1][0] = tochar(n2);
        lines[i+2][0] = tochar(n3);
        cout << endl << endl;
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



