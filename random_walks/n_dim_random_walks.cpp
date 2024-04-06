#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <bits/stdc++.h>
#include <array>
#include <cmath>
#include <random>
using namespace std;


int Random_D_Dim_walk(int n, int d)
{   
    // Create n*d walk with only 0 entries
    double coordinates[n][d] = {0};
    int SAW {0};
    set<vector<double>> checker;
    vector<double> row(d);
    //append the (0,0,...) coordinate to the set 
    for (int i = 0; i<d; i++)
    {
        row[i] = round(coordinates[0][i]);
    }       
    checker.insert(row);
    //initialise random variable generator with the possible directions
    //1 - 2d options to choose from 2D -> 4 options, 3D -> 6 etc
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> distribution(1,2*d);

    int step = distribution(generator);
    int index {0};
    //Carry out random walk
    for (int k=1; k<n; k++) 
    {
        //reset row to be added to set
        vector<double> row(d);

        //If step is even produces a negative step in the step/2 direction
        //If step is odd, produce a positive step in the direction of (step+1)/2
        // eg step = 1 -> 0th index (1st direction eg x) and positive step so (1,0,0,...)

        if (step%2 == 0)
        {
            index = (step/2) -1;
            //make step
            coordinates[k][index] = coordinates[k-1][index] - 1;
            //append the change to the row vector
            row[index] = round(coordinates[k][index]);
            //must now scan through other indices and bring them up to the previous value
            for (int l = 0; l < d; l++)
            {
                if (l != index)
                {
                    coordinates[k][l] = coordinates[k-1][l];
                    //fill in row vector values
                    row[l] = round(coordinates[k][l]);
                }
            }

        }
        else if (step%2 !=0)
        {   
            step += 1;
            index = (step/2) -1;
            //make step
            coordinates[k][index] = coordinates[k-1][index] + 1;
            //append the change to the row vector
            row[index] = round(coordinates[k][index]);
            //must now scan through other indices and bring them up to the previous value
            for (int l = 0; l < d; l++)
            {
                if (l != index)
                {
                    coordinates[k][l] = coordinates[k-1][l];
                    //fill in row vector values
                    row[l] = round(coordinates[k][l]);
                }
                
            }

        }
        //add row vector to the set
        checker.insert(row);

        //set new random value for next step
        step = distribution(generator);
    } 
    //cout << checker.size() << "\n";
    if (checker.size() == n)
    {
        SAW = 1;
    }
    // if it is self avoiding the length of the set should be equal to total length
    return SAW;
}

int main()
{
    int no_of_iterations {50001};
    int dimension {101};
    double temp1 {0};
    int length{30};

    //Increase dimension and evaluate how many random walks of length (30) are self avoiding

    ofstream file;
    //naming file to store results in
    file.open("RandomWalkDimensionPercentsn30.csv");

    for (int i=2; i<dimension; i++) 
    {
        temp1 = 0;
        
          for (int j=1; j<no_of_iterations; j++) 
            {
                //adds a 1 to the tally if it is self avoiding
                temp1 += Random_D_Dim_walk(length,i);
            }  
            
        double percent {(temp1/no_of_iterations)*100};
        //append the set of values to the csv file to be plotted
        file << round(percent*1000)/1000 << "," << i << "\n";
    }
    file.close();
}