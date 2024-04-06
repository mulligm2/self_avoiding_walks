#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <bits/stdc++.h>
#include <array>
#include <cmath>
#include <random>
using namespace std;

int RandomWalk(int n)
{
    //input 
    //  n: desired length of the random walk 


    double coordinates[n][2];
    coordinates[0][0] = 0;
    coordinates[0][1] = 0;
    set<set<double>> checker;
    set<double>row;
    row.insert(coordinates[0][0]);
    row.insert(coordinates[0][1]);
        
    checker.insert(row);

    //initialise random seed
    
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> distribution(1,4);
    int step = distribution(generator);
    for (int k=1; k<n; k++)    
    {
        //generate a random number 1 to 4 which will determine direction of walk 
        //int step = (rand()%4)+ 1; 
        
        
        //cout << step << "\n";
        set<double>row;

        if (step == 1)
        {
            coordinates[k][0] = coordinates[k - 1][0];
            coordinates[k][1] = coordinates[k - 1][1] + 1;
        }
                
        else if (step == 2)
        {
            coordinates[k][0] = coordinates[k - 1][0] + 1;
            coordinates[k][1] = coordinates[k - 1][1];
        }
        else if (step == 3)
        {
            coordinates[k][0] = coordinates[k - 1][0];
            coordinates[k][1] = coordinates[k - 1][1] - 1;
        }
                
        else if (step == 4)
        {
            coordinates[k][0] = coordinates[k - 1][0] - 1;
            coordinates[k][1] = coordinates[k - 1][1];            
        }

        row.insert(coordinates[k][0]);
        row.insert(coordinates[k][1]);
        
        checker.insert(row);


        step = distribution(generator);
    }
    int SAW {0};
    if (checker.size() == n)
    {
        SAW = 1;
        //cout << "SAW" << "\n";
    }
    
    return SAW;
}

int RandomHexWalk(int n)
{
    //input 
    //  n: desired length of the random walk
    
    double coordinates[n][2];

    coordinates[0][0] = 0;
    coordinates[0][1] = 0;
    set<set<double>> checker;
    set<double>row;
    row.insert(coordinates[0][0]);
    row.insert(coordinates[0][1]);
        
    checker.insert(row);

    //int starting_direction = (rand()%2)+1;
    default_random_engine generator1(random_device{}());
    uniform_int_distribution<int> distribution1(1,2);
    int starting_direction = distribution1(generator1);


    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> distribution(1,3);
    double x = 1/2;
    double y = sqrt(3)/2;
    int step = distribution(generator);
    //initialise random seed
    for (int k=1; k<n; k++) 
    {
        set<double>row; 
        if (starting_direction == 1)    
        {
            //generate a random number 1 to 3 which will determine direction of walk 

            if (step == 1)
            {
                coordinates[k][0] = coordinates[k-1][0]-x;
                coordinates[k][1] = coordinates[k-1][1]+y;
            }
                
            else if (step == 2)
            {
                coordinates[k][0] = coordinates[k-1][0]+1;
                coordinates[k][1] = coordinates[k-1][1];
            }
            else if (step == 3)
            {
                coordinates[k][0] = coordinates[k-1][0]-x;
                coordinates[k][1] = coordinates[k-1][1]-y;
            }

            starting_direction = 2;
        }
        else if (starting_direction == 2)
        {
           
            //generate a random number 1 to 3 which will determine direction of walk 
            int step = distribution(generator);

            if (step == 1)
            {
                coordinates[k][0] = coordinates[k-1][0]+x;
                coordinates[k][1] = coordinates[k-1][1]+y;
            }
                
            else if (step == 2)
            {
                coordinates[k][0] = coordinates[k-1][0]-1;
                coordinates[k][1] = coordinates[k-1][1];
            }
            else if (step == 3)
            {
                coordinates[k][0] = coordinates[k-1][0]+x;
                coordinates[k][1] = coordinates[k-1][1]-y;
            }
            starting_direction = 1;
        }
       

        row.insert(coordinates[k][0]);
        row.insert(coordinates[k][1]);
        
        checker.insert(row);
        step = distribution(generator); 
    }
    int SAW {0};
    if (checker.size() == n)
    {
        SAW = 1;
        //cout << "SAW" << "\n";
    }
    
    return SAW;
}

int main()
{
    
    int no_of_iterations {20001};
    int length {31};
    double temp1 {0};
    double temp2 {0};
    double percent,percent2;
    
    ofstream file;
    //naming file to store results in
    file.open("RandomWalkPercents.csv");
    
    for (int i=1; i<length; i++) 
    {
        temp1 = 0;
        
        temp2 = 0;
        
          for (int j=1; j<no_of_iterations; j++) 
            {
                //adds a 1 to the tally if it is self avoiding
                temp1 += RandomWalk(i); //Counter for square lattice walks
                temp2 += RandomHexWalk(i); // Counter for hexagonal lattice walks
            }  
            
        percent = (temp1/no_of_iterations)*100;
        percent2 = (temp2/no_of_iterations)*100;

        //append the set of values to the csv file to be plotted
        file << round(percent*1000)/1000 << "," << round(percent2*1000)/1000 << "," << i << "\n";
    }
    file.close();
    
}