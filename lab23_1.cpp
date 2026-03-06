#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(size_t i = 0; i < x.size(); i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename.c_str());
    string textline;
    while(getline(file, textline)){
        size_t colon_idx = textline.find(':');
        if(colon_idx != string::npos){
            names.push_back(textline.substr(0, colon_idx));
            
            string nums = textline.substr(colon_idx + 1);
            int s1 = 0, s2 = 0, s3 = 0;
            
            size_t p1 = nums.find_first_not_of(" ");
            size_t p2 = nums.find_first_of(" ", p1);
            s1 = atoi(nums.substr(p1, p2 == string::npos ? string::npos : p2 - p1).c_str());
            
            p1 = nums.find_first_not_of(" ", p2);
            p2 = nums.find_first_of(" ", p1);
            s2 = atoi(nums.substr(p1, p2 == string::npos ? string::npos : p2 - p1).c_str());
            
            p1 = nums.find_first_not_of(" ", p2);
            s3 = atoi(nums.substr(p1).c_str());
            
            int total = s1 + s2 + s3;
            scores.push_back(total);
            grades.push_back(score2grade(total));
        }
    }
    file.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cout << endl;
    cin >> command;
    string temp;
    getline(cin, temp);
    
    size_t start = temp.find_first_not_of(" \t\r\n");
    if(start != string::npos){
        size_t end = temp.find_last_not_of(" \t\r\n");
        key = temp.substr(start, end - start + 1);
    } else {
        key = "";
    }
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    bool found = false;
    for(size_t i = 0; i < names.size(); i++){
        if(key.length() > 0 && grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);

    do{
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);

    return 0;
}