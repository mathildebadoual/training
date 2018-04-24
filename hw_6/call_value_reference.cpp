#include <iostream>
#include <vector>
#include <time.h>
#include <map>
#include "csv.h"
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <locale>
#include <string>

#define CSV_IO_NO_THREAD

using namespace std;

string change_name_reference(string& name, multimap<string, string> states_map){
    return states_map.find(name)->second;
}

string change_name_value(string name, multimap<string, string> states_map){
    return states_map.find(name)->second;
}


int main() {

    io::CSVReader<2> in1("states.csv");
    in1.read_header(io::ignore_extra_column, "state", "abbreviation");
    string state_name; string state_abbr;
    multimap <string, string> states_map;
    int i=0;
    while(in1.read_row(state_name, state_abbr)){
        states_map.insert(pair <string, string> (state_abbr, state_name));
        ++i;
    }

    clock_t tStart = clock();
    bool row_readable;


    printf("Start of reference call");
    tStart = clock();

    io::CSVReader<1> in2("Parking_Violations_Issued_-_Fiscal_Year_2018.csv");
    in2.read_header(io::ignore_extra_column, "Registration State");
    string registration_state1;
    int j=0;
    while(j < 8643265){
        try {
            row_readable = in2.read_row(registration_state1);
            change_name_reference(registration_state1, states_map);
            j++;
        } catch(io::error::too_many_columns e1) {
            j++;
        }
    }

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    printf("Start of value call");

    tStart = clock();

    io::CSVReader<1> in3("Parking_Violations_Issued_-_Fiscal_Year_2018.csv");
    in3.read_header(io::ignore_extra_column, "Registration State");
    string registration_state2;
    int k=0;
    while(k < 8643265){
        try {
            row_readable = in3.read_row(registration_state2);
            change_name_value(registration_state2, states_map);
            k++;
        } catch(io::error::too_many_columns e1) {
            k++;
        }
    }
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}
