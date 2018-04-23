// Exercice 3 (Turing Machine)


#include <iostream>
#include <string>

using namespace std;

struct State{
    int q_current;
    char red;
    int q_next;
    char to_write;
    char direction;
};

string TuringMachine(string n_binary){
    State rules[9] = {{0, '0', 0, '0', 'R'},
        {0, '1', 0, '1', 'R'},
        {0, '-', 2, '-', 'L'},
        {1, '0', 1, '0', 'L'},
        {1, '1', 1, '1', 'L'},
        {1, 'X', 3, 'X', 'L'},
        {2, '0', 1, '1', 'L'},
        {2, '1', 2, '0', 'L'},
        {2, 'X', 3, '1', 'L'}};

    char n_binary_new[5];
    int q_current = 0;
    int index = 4;
    char red = n_binary[index];
    cout << red << endl;
    while(q_current < 3){
        State state_ok;
        for(auto state:rules){
            if((state.q_current == q_current) && (state.red == red)){
                state_ok = state;
            }
        }
        q_current = state_ok.q_next;
        n_binary_new[index] = state_ok.to_write;
        cout << n_binary_new[index] << endl;
        cout << q_current << endl;
        char l = 'L';
        char r = 'R';
        if(state_ok.direction == l){
        index--;
        }
        if(state_ok.direction == r){
        index++;
        }
        red = n_binary[index];
    }
    return n_binary_new;
};

int main(){

    string n_binary = "X101-";
    string n_binary_new = TuringMachine(n_binary);
    cout << "X101 + 1 = " << n_binary_new << endl;

    n_binary = "X111-";
    n_binary_new = TuringMachine(n_binary);
    cout << "X111 + 1 = " << n_binary_new << endl;

    return 0;
}
