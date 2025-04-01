// LL1Validator.cpp
#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

const int MAX = 20;
string productions[MAX] = {
    "S->ABC", "S->D",
    "A->a", "A->e",
    "B->b", "B->e",
    "C->(S)", "C->c",
    "D->AC"
};
int numProductions = 9;

map<char, string> first;
map<char, string> follow;
map<char, map<char, string>> parsing_table;
char terminals[] = {'a', 'b', '(', ')', 'c', '$'};
int numTerminals = 6;
char nonTerminals[] = {'S', 'A', 'B', 'C', 'D'};
int numNonTerminals = 5;

void readSets() {
    string line;
    while(getline(cin, line)) {
        stringstream ss(line);
        string type;
        char nt;
        string set;

        ss >> type >> nt;
        getline(ss, set);
        set = set.substr(1); // Remove leading space

        if(type == "FIRST") first[nt] = set;
        else if(type == "FOLLOW") follow[nt] = set;
    }
}

bool makeTable() {
    for(int i = 0; i < numNonTerminals; i++) {
        char nt = nonTerminals[i];
        parsing_table[nt] = map<char, string>();
        for(int j = 0; j < numTerminals; j++) {
            parsing_table[nt][terminals[j]] = "";
        }
    }

    for(int i = 0; i < numProductions; i++) {
        char nt = productions[i][0];
        string rhs = productions[i].substr(3);

        if(rhs == "e") {
            string followSet = follow[nt];
            for(int j = 0; j < followSet.length(); j++) {
                if(parsing_table[nt][followSet[j]] != "") {
                    cout << "Conflict! Not LL(1)" << endl;
                    return false;
                }
                parsing_table[nt][followSet[j]] = "e";
            }
        }
        else {
            char firstChar = rhs[0];
            string firstSet = isupper(firstChar) ? first[firstChar] : string(1, firstChar);
            for(int j = 0; j < firstSet.length(); j++) {
                if(firstSet[j] != 'e') {
                    if(parsing_table[nt][firstSet[j]] != "") {
                        cout << "Conflict! Not LL(1)" << endl;
                        return false;
                    }
                    parsing_table[nt][firstSet[j]] = rhs;
                }
            }
        }
    }
    return true;
}

void showTable() {
    cout << "\nParsing Table:\n   ";
    for(int i = 0; i < numTerminals; i++) cout << terminals[i] << "   ";
    cout << endl;

    for(int i = 0; i < numNonTerminals; i++) {
        char nt = nonTerminals[i];
        cout << nt << "  ";
        for(int j = 0; j < numTerminals; j++) {
            string entry = parsing_table[nt][terminals[j]];
            if(entry == "") cout << "-   ";
            else if(entry == "e") cout << "^   ";
            else cout << entry << "  ";
        }
        cout << endl;
    }
}

bool checkString(string input) {
    string stack = "$S";
    input += "$";
    int pos = 0;

    while(stack.length() > 0) {
        char top = stack.back();
        stack.pop_back();

        if(top == input[pos]) pos++;
        else if(isupper(top)) {
            if(parsing_table[top].find(input[pos]) == parsing_table[top].end() ||
               parsing_table[top][input[pos]] == "") return false;
            string prod = parsing_table[top][input[pos]];
            if(prod != "e") {
                for(int i = prod.length() - 1; i >= 0; i--) stack += prod[i];
            }
        }
        else return false;
    }
    return pos == input.length();
}

int main() {
    cout << "Reading FIRST and FOLLOW sets..." << endl;
    readSets();

    cout << "Making parsing table..." << endl;
    bool isLL1 = makeTable();

    if(isLL1) {
        cout << "Grammar is LL(1)" << endl;
        showTable();

        string test;
        cout << "\nEnter a string to check: ";
        cin >> test;

        if(checkString(test)) cout << "Valid string" << endl;
        else cout << "Invalid string" << endl;
    }
    else {
        cout << "Grammar is not LL(1)" << endl;
    }
    return 0;
}
