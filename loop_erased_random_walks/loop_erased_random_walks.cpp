#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <array>
#include <cmath>
#include <algorithm>
#include <random>
#include <numeric>
#include <valarray>
#include <vector>
#include <set>
#include <tuple>
using namespace std;


double eucl_dist(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]);
}
double eucl_dist3D(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]+final_pos[2]*final_pos[2]);
}


vector<vector<int>> LERW(int n, int d, int limit)
{
    //Generates a loop erased random walk

    //Vectors to save the walk 
    vector<vector<int>> coordinates;
    vector<int> row(d);
    set<vector<int>> checker;

    //Append origin to all stores
    coordinates.push_back(row);
    checker.insert(row);
    

    //Counters
    int length{1}, break_point{0}, index{0}, step;
    double e2e{0};
    //Initialise rng
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> direction(1,2*d);
    while (length < n)
    {
        
        if (break_point < limit)
        {
            break_point +=1;
        }
        else
        {
            break;
        }
        //Ensure length is set to the current LERW 
        length = coordinates.size();
        
        //Decide on step to take
        step = direction(generator);

        //Make step 
        if (step%2 == 0)
        {
            index = (step/2) -1;
            row[index] += 1;
        }
        else if (step%2 !=0)
        {   
            step += 1;
            index = (step/2) -1;
            row[index] -= 1;
        }
        //Append to checker
        checker.insert(row);

        //Add 1 to the length 
        length +=1;

        if (checker.size() != length)
        {
            checker.clear();
            //Loop created, need to destroy loop 
            for (int ii=1;ii<length;ii++)
            {
                if (coordinates.back() != row)
                {    
                    coordinates.pop_back();
                }
                else 
                {
                    //If the point has been found again then the loop has been removed, we now update the set 
                    for (int jj =0; jj<coordinates.size();jj++)
                    {
                        checker.insert(coordinates[jj]);
                    }
                    break;
                }
            }
        }
        else 
        {
            coordinates.push_back(row);
        }
    }
    cout << "Length: " << length << "\n";
    return coordinates;
}

void SaveWalk(vector<vector<int>> coordinates)
{
    //Used to save walk to a csv file for plotting 
    ofstream file;

    //naming file to store results in
    file.open("LERWTest.csv");
    for (int i = 0; i < coordinates.size(); i++) 
    { 
        for ( 
            auto it = coordinates[i].begin(); 
            it != coordinates[i].end(); it++) 
            file << *it << ","; 
        file << endl; 
    } 
    file.close();
}


int main()
{
    vector<vector<int>> LERW_Test;
    int n = 1000;
    int limit = n*n;
    int d = 2;
    double e2e{0};
    LERW_Test = LERW(n,d,limit);
    SaveWalk(LERW_Test);
    
    
    //Values for avg
    n = 100;
    int total{50};

    int step{10};

    int counter{0};
    int big_number{400};
    

    //Evaluating scaling coefficient of LERW by computing end to end distance 

    ofstream file;
    file.open("e2eLERW2D.csv");
    for (int ii=0;ii<total;ii++)

    {
        limit = n*n*n;
        e2e = 0;
        counter = 0;
        while (counter < big_number)
        {
            LERW_Test = LERW(n,d,limit); 
            if (LERW_Test.size() == n)
            {
                e2e += eucl_dist(LERW_Test.back())*eucl_dist(LERW_Test.back());
                counter += 1;
            }
                
        }
        e2e = e2e/counter;

        file << n << "," << e2e << "\n";
        n += step;
    }
    file.close();
    
    return 0;
}