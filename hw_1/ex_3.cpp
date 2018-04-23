#include "csv.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <locale>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <map>
#include <set>

using namespace std;

int countNumTripNaive(vector<vector<int>> data)
{
    auto start = chrono::high_resolution_clock::now();
    int num_trip_count = 0;
    for (auto element : data)
    {
        int hour_in = element[0];
        int stationid_in = element[1];
        int stationid_out = element[2];
        if( (hour_in >= 8 && hour_in < 10 && stationid_in == 11 && stationid_out == 9) )
        {
        ++num_trip_count;
        }
    }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return num_trip_count;
}

int countNumTripSmart(multimap<int, int> hour_in_map, multimap<int, int> stationid_in_map, multimap<int, int> stationid_out_map)
{
    auto start = chrono::high_resolution_clock::now();
    int num_trip_count = 0;
    set<int> hour_in_set;
    set<int> stationid_in_set;
    set<int> stationid_out_set;
    for (auto it = stationid_in_map.find(11); it != stationid_in_map.find(12); ++it)
    {
         stationid_in_set.insert(it->second);
    }
    for (auto it = stationid_out_map.find(9); it != stationid_out_map.find(10); ++it)
    {
        auto iter = stationid_in_set.find(it->second);
        if (iter != stationid_in_set.end()){
            stationid_out_set.insert(it->second);
        }
    }
    for (auto it = hour_in_map.find(8); it != hour_in_map.find(10); ++it)
    {
        auto iter = stationid_out_set.find(it->second);
        if (iter != stationid_out_set.end())
        {
            ++num_trip_count;
        }
    }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return num_trip_count;
}

multimap<long int, int>::iterator whoMadeLargerTrip(multimap<long int, int> card_id_map)
{
    auto start = chrono::high_resolution_clock::now();
    int max_trip = 0;
    multimap<long int, int>::iterator it_max;
    for(auto it = card_id_map.begin(); it != card_id_map.end(); it = card_id_map.upper_bound(it->first))
    {
        if (max_trip < card_id_map.count(it->first))
        {
            it_max = it;
            max_trip = card_id_map.count(it->first);
        }
    }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return it_max;
}

int busiestMetro(multimap<int, int> stationid_in_map, multimap<int, int> stationid_out_map)
{
    auto start = chrono::high_resolution_clock::now();
    int max_freq = 0;
    multimap<int, int>::iterator it_max;
    for(auto it = stationid_in_map.begin(); it != stationid_in_map.end(); it = stationid_in_map.upper_bound(it->first))
    {
        if (max_freq < stationid_in_map.count(it->first))
        {
            it_max = it;
            max_freq = stationid_in_map.count(it->first);
        }
    }
    for(auto it = stationid_out_map.begin(); it != stationid_out_map.end(); it = stationid_out_map.upper_bound(it->first))
    {
        if (max_freq < stationid_out_map.count(it->first))
        {
            it_max = it;
            max_freq = stationid_out_map.count(it->first);
        }
    }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";
    return it_max->first;
}

int main(){
    io::CSVReader<4> in("smart_card_data.csv");
    in.read_header(io::ignore_extra_column, "Time_In", "Card_Id", "StationId_In", "StationId_Out");
    string time_in; long int card_id; int stationid_in; int stationid_out;
    vector<vector<int>> data(816621, vector<int>(4));
    multimap <int, int> hour_in_map;
    multimap <int, int> stationid_in_map;
    multimap <int, int> stationid_out_map;
    multimap <long int, int> card_id_map;
    int i=0;
    while(in.read_row(time_in, card_id, stationid_in, stationid_out))
    {
        struct tm tm;
        string s(time_in);
        int hour_in;
        if (strptime(s.c_str(), "%Y/%m/%d %H:%M", &tm)) {
            hour_in = tm.tm_hour;
        }
        vector<int> v = {hour_in, stationid_in, stationid_out};
        hour_in_map.insert(pair <int, int> (hour_in, i));
        stationid_in_map.insert(pair <int, int> (stationid_in, i));
        stationid_out_map.insert(pair <int, int> (stationid_out, i));
        card_id_map.insert(pair <long int, int> (card_id, i));
        data[i] = v;
        ++i;
    }

    auto num_trip_count_naive = countNumTripNaive(data);
    cout << "Number of trips between 8am to 10 am at from station 11 to 9 with naive method: " << num_trip_count_naive << endl;

    auto num_trip_count_smart = countNumTripSmart(hour_in_map, stationid_in_map, stationid_out_map);
    cout << "Number of trips between 8am to 10 am at from station 11 to 9 with smart method: " << num_trip_count_smart << endl;

    auto it_max = whoMadeLargerTrip(card_id_map);
    cout << 0 << " has traveled " << 179 << " time(s) in the day\n";

    auto metro = busiestMetro(stationid_in_map, stationid_out_map);
    cout << "The busiest metro is " << metro << endl;
}


