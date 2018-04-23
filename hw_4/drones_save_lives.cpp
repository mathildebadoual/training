// Exercice 1 (Drones save lifes)

//There are 22 hospitals that must be served (distance in distances.csv). Several blood
//distribution centers will be built on top of these hospitals. The range of our
//medical drone is 3.5 miles. The distribution center will be able to serve a certain
//hospital if it is within this range. Your task is to design the location of the
//distribution centers such that all 22 hospitals can be served and the number of
//distribution centers is minimized.

#include <iostream>
#include "csv.h"
#include <iomanip>
#include <math.h>
#include <vector>
#include <tuple>
#include <iterator>
#include <algorithm>


using namespace std;

// Question 1:

tuple<vector<vector<int>>, vector<int>> PrepareSetCoverProblem(int size, long double latitudes[22], long double longitudes[22]){
    vector<int> univers;
    vector<vector<int>> set_cover;
    for (int i = 0; i < size; ++i){
        univers.push_back(i);
        vector<int> set = {i};
        for (int j = 0; j < size; ++j){
            long double distance = sqrt(pow((latitudes[i] - latitudes[j])*69, 2) + pow((longitudes[i] - longitudes[j])*53, 2));
            if (distance <= 3.5){
                set.push_back(j);
            }
        }
        for (int x:set){
            cout << x << " ";
        }
        cout << "\n";
        set_cover.push_back(set);
    }
    return {set_cover, univers};
}

// Question 2:

int MinimumSetCover(vector<int> univers, vector<vector<int>> set_cover){
    int blood_centers;
    vector<int> hospitals_covered;
    int num_hosp_cover = 0;
    int max_size = 1;
    while (num_hosp_cover < 22){
        int index;
        int i = 0;
        vector<int> best_set;
        for (auto set:set_cover){
            int size = sizeof(set);
            if (max_size < size){
                max_size = size;
                index = i;
                best_set = set;
            }
            ++i;
        }
        for (int hospital:best_set){
            if (find(hospitals_covered.begin(), hospitals_covered.end(), hospital) != hospitals_covered.end()){
                hospitals_covered.push_back(hospital);
                ++num_hosp_cover;
            }
        }
        ++blood_centers;
        set_cover.erase(set_cover.begin() + index);
    }
    return blood_centers;
}


int main(){
    const int size=22;
    io::CSVReader<2> in("distances.csv");
    in.read_header(io::ignore_extra_column, "long", "lat");
    long double longitude; long double latitude;
    long double latitudes[size];
    long double longitudes[size];
    int i = 0;
    while (in.read_row(longitude, latitude)){
        latitudes[i] = latitude;
        longitudes[i] = longitude;
        ++i;
        cout << latitude << longitude << endl;
    }
    tuple<vector<vector<int>>, vector<int>> sets =  PrepareSetCoverProblem(size, latitudes, longitudes);
    vector<int> univers = get<1>(sets);
    vector<vector<int>> set_cover = get<0>(sets);
    auto blood_center = MinimumSetCover(univers, set_cover);
    cout << blood_center << endl;
    return 0;
}
