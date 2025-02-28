#include<iostream>
#include<fstream>
#include <sstream>
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
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(const string& filename, vector<string>& names, vector<int>& scores, vector<char>& grades) {
    ifstream file(filename); 
    string line;
    
    if (!file) {
        cerr << "Error opening file." << endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string name;
        int score1, score2, score3;

        if (getline(ss, name, ':')) {
            size_t first = name.find_first_not_of(" \t");
            size_t last = name.find_last_not_of(" \t");
            name = name.substr(first, last - first + 1);
        }

        ss >> score1 >> score2 >> score3;

        int totalScore = score1 + score2 + score3;
        
        char grade = score2grade(totalScore);

        names.push_back(name);
        scores.push_back(totalScore);
        grades.push_back(grade);
    }

    file.close();
}

void getCommand(string &command, string &key){
    string input;
    cout << "Please input your command:" << endl;
    getline(cin, input);  

    input = toUpperStr(input);

    size_t spacePos = input.find(' ');

    if (spacePos != string::npos) {
        command = input.substr(0, spacePos); 
        key = input.substr(spacePos + 1);     
    } else {
        
        command = input;
        key = "";
    }
    
}

void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string key) {
    bool found = false;
    for (size_t i = 0; i < names.size(); i++) {
        if (toUpperStr(names[i]) == key) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            found = true;
        }
    }
    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found.\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key) {
    bool found = false;
    
    
    key = toUpperStr(key);

    
    cout << "---------------------------------" << endl;
    
    
    for (size_t i = 0; i < grades.size(); i++) {
        
        if (toUpperStr(string(1, grades[i])) == key) {
            found = true;
            
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }

    if (!found) {
        cout << "Cannot found." << endl;
    }

    cout << "---------------------------------" << endl;
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
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
