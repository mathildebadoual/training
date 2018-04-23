#include <iostream>
#include <vector>
#include <time.h>
#include <map>
#include "csv.h"
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <locale>


using namespace std;

char change_name_reference(char& name, multimap<char, char> states_map){
    char new_name = states_map.find(name)->second;
    name = new_name;
    return name;
}

char change_name_value(char name, multimap<char, char> states_map){
    char new_name = states_map.find(name)->second;
    name = new_name;
    return name;
}


int main() {

    /*
    io::CSVReader<2> in1("states.csv");
    in1.read_header(io::ignore_extra_column, "State", "Abbreviation");
    char state_name; char state_abbr;
    multimap <char, char> states_map;
    int i=0;
    while(in1.read_row(state_name, state_abbr)){
        states_map.insert(pair <char, char> (state_abbr, state_name));
        ++i;
    }
    */


    io::CSVReader<1> in2("Parking_Violations_Issued_-_Fiscal_Year_2018.csv");
    in2.read_header(io::ignore_extra_column, "Registration State");
    char registration_state;
    char registration_state_list[8643263];
    int j=0;
    while(in2.read_row(registration_state)){
        cout << j <<endl;
        registration_state_list[j] = registration_state;
        ++j;
    }

    /*
    clock_t tStart = clock();

    printf("Start of reference call");
    tStart = clock();
    int k=0;
    for (auto name : registration_state_list){
        registration_state_list[i] = change_name_reference(name, states_map);
        ++k;
    }
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    printf("Start of value call");

    tStart = clock();
    int l=0;
    for (auto name : registration_state_list){
        registration_state_list[i] = change_name_value(name, states_map);
        ++l;
    }
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);*/

    return 0;
}
