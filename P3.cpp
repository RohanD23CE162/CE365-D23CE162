#include <iostream>  
#include <string>   
#include <vector>   
#include <set>      
#include <fstream>  
#include <cctype>   

using namespace std;

// Token types
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    STRING,
    PUNCTUATION,
    OPERATOR,
    UNKNOWN
};

// Token structure
struct Token {
    string value;
    TokenType type;
};

// Global variables
vector<Token> tokens;
set<string> symbolTable;
vector<string> lexicalErrors;

// C keywords
const set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", 
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

// Operators
const set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "+=", "-=",
    "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>=", "++", "--"
};

// Punctuation
const set<char> punctuation = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.', ':', '?'
};

// Function declarations
void processToken(const string& token);
void analyze(const string& input);
void printResults();

// Process individual tokens
void processToken(const string& token) {
    if (token.empty()) return;
    
    // Check if it's a keyword
    if (keywords.find(token) != keywords.end()) {
        tokens.push_back({token, KEYWORD});
        return;
    }
    
    // Check if it's a number
    if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1 && isdigit(token[1]))) {
        bool isValid = true;
        for (size_t i = 1; i < token.length(); i++) {
            if (!isdigit(token[i]) && token[i] != '.' && token[i] != 'f') {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            tokens.push_back({token, CONSTANT});
            return;
        }
    }
    
    // Check if it's a valid identifier
    if (isalpha(token[0]) || token[0] == '_') {
        bool isValid = true;
        for (char c : token) {
            if (!isalnum(c) && c != '_') {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            tokens.push_back({token, IDENTIFIER});
            // Skip adding "main" to symbol table
            if (token != "main") {
                symbolTable.insert(token);
            }
            return;
        }
    }
    
    lexicalErrors.push_back(token + " invalid lexeme");
}

// Analyze input string
void analyze(const string& input) {
    string currentToken;
    
    for (size_t i = 0; i < input.length(); i++) {
        char c = input[i];
        
        // Skip whitespace
        if (isspace(c)) {
            processToken(currentToken);
            currentToken = "";
            continue;
        }
        
        // Handle comments
        if (c == '/' && i + 1 < input.length()) {
            if (input[i + 1] == '/') {
                // Single line comment
                while (i < input.length() && input[i] != '\n') i++;
                continue;
            }
            else if (input[i + 1] == '*') {
                // Multi-line comment
                i += 2;
                while (i < input.length() - 1 && !(input[i] == '*' && input[i + 1] == '/')) i++;
                i += 2;
                continue;
            }
        }
        
        // Handle strings
        if (c == '"') {
            processToken(currentToken);
            currentToken = "\"";
            i++;
            while (i < input.length() && input[i] != '"') {
                currentToken += input[i];
                i++;
            }
            if (i < input.length()) currentToken += '"';
            tokens.push_back({currentToken, STRING});
            currentToken = "";
            continue;
        }
        
        // Handle character literals
        if (c == '\'') {
            processToken(currentToken);
            currentToken = "'";
            i++;
            while (i < input.length() && input[i] != '\'') {
                currentToken += input[i];
                i++;
            }
            if (i < input.length()) currentToken += '\'';
            tokens.push_back({currentToken, CONSTANT});
            currentToken = "";
            continue;
        }
        
        // Handle punctuation
        if (punctuation.find(c) != punctuation.end()) {
            processToken(currentToken);
            tokens.push_back({string(1, c), PUNCTUATION});
            currentToken = "";
            continue;
        }
        
        // Handle operators
        if (operators.find(string(1, c)) != operators.end()) {
            processToken(currentToken);
            string op(1, c);
            if (i + 1 < input.length() && 
                operators.find(op + input[i + 1]) != operators.end()) {
                op += input[++i];
            }
            tokens.push_back({op, OPERATOR});
            currentToken = "";
            continue;
        }
        
        currentToken += c;
    }
    
    processToken(currentToken);
}

// Print results
void printResults() {
    cout << "TOKENS\n";
    for (const auto& token : tokens) {
        string type;
        switch (token.type) {
            case KEYWORD: type = "Keyword"; break;
            case IDENTIFIER: type = "Identifier"; break;
            case CONSTANT: type = "Constant"; break;
            case STRING: type = "String"; break;
            case PUNCTUATION: type = "Punctuation"; break;
            case OPERATOR: type = "Operator"; break;
            default: type = "Unknown"; break;
        }
        cout << type << ": " << token.value << "\n";
    }
    
    cout << "\nSYMBOL TABLE ENTRIES\n";
    int i = 1;
    for (const auto& symbol : symbolTable) {
        cout << i++ << ") " << symbol << "\n";
    }
    
    if (!lexicalErrors.empty()) {
        cout << "\nLEXICAL ERRORS\n";
        for (const auto& error : lexicalErrors) {
            cout << error << "\n";
        }
    }
}

int main() {
    string input;
    string line;
    
    // Open input file
    ifstream inFile("input.c");
    if (!inFile.is_open()) {
        cout << "Error: Could not open input.c\n";
        return 1;
    }
    
    // Read the input file
    while (getline(inFile, line)) {
        input += line + "\n";
    }
    inFile.close();
    
    analyze(input);
    printResults();
    
    return 0;
}
