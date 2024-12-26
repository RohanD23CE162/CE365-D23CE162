// CPP code for DFA
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    // Get the number of input symbols
    int no_symbols;
    cout << "Number of input symbols : ";
    cin >> no_symbols;

    // Read the input symbols
    char input_symbols[no_symbols];
    cout << "Input symbols : ";
    for (int i = 0; i < no_symbols; i++)
    {
        cin >> input_symbols[i];
    }

    // Get the number of states in the DFA
    int no_states;
    cout << "Enter number of states : ";
    cin >> no_states;

    // Define the initial state of the DFA
    int initial_state;
    cout << "Initial state : ";
    cin >> initial_state;

    // Get the number of accepting states
    int no_accepting_states;
    cout << "Number of accepting states : ";
    cin >> no_accepting_states;

    // Read the list of accepting states
    vector<int> accepting_states(no_accepting_states);
    cout << "Accepting states : ";
    for (int i = 0; i < no_accepting_states; i++)
    {
        cin >> accepting_states[i];
    }

    // Create the transition table
    int transition_table[no_states][no_symbols];
    cout << "Transition table : " << endl;
    for (int i = 0; i < no_states; i++)
    {
        for (int j = 0; j < no_symbols; j++)
        {
            cout << i + 1 << " to " << input_symbols[j] << " -> ";
            cin >> transition_table[i][j];
        }
    }

    // Get the input string to be tested
    string input_string;
    cout << "Input string : ";
    cin >> input_string;

    // Start processing the input string from the initial state
    int current_state = initial_state;

    for (int i = 0; i < input_string.size(); i++)
    {
        char current_symbol = input_string[i];

        // Find the index of the current symbol in the input symbols
        int symbol_index = -1;
        for (int j = 0; j < no_symbols; j++)
        {
            if (input_symbols[j] == current_symbol)
            {
                symbol_index = j;
                break;
            }
        }

        // Transition to the next state based on the current symbol
        current_state = transition_table[current_state - 1][symbol_index];
    }

    // Check if the final state is an accepting state
    bool is_accepted = false;
    for (int i = 0; i < no_accepting_states; i++)
    {
        if (current_state == accepting_states[i])
        {
            is_accepted = true;
            break;
        }
    }

    // Output the result of the string validation
    if (is_accepted)
    {
        cout << "Valid string" << endl;
    }
    else
    {
        cout << "Not Valid string" << endl;
    }
}
