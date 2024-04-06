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

//n number of vertices (n-1 edges)
const int n = 5;

const int d = 2;

vector<vector<int>> GenerateWalk(vector<int> directions, vector<vector<int>> coordinates)
{

    vector<int> row(d, 0);

    coordinates[0] = row;
    /*
    Directions List 
    0 Up +y
    1 Right +x
    2 Down -y
    3 Left -x
    4 +z
    5 -z 
    */
    //set<vector<int>> SAW;
    //SAW.insert(row);
    for (int k=1; k<n; k++) 
    {
        if(directions[k]==0)
        {
            row[1] = row[1] + 1;
        }    
        else if(directions[k]==1)
        {
            row[0] = row[0] + 1;
        } 
        else if(directions[k]==2)
        {
            row[1] = row[1] - 1;
        } 
        else if(directions[k]==3)
        {
            row[0] = row[0] - 1;
        } 
        else if(directions[k]==4)
        {
            row[2] = row[2] + 1;
        } 
        else if(directions[k]==5)
        {
            row[2] = row[2] - 1;
        }
        coordinates[k] = row;
        //SAW.insert(row);
    }
/*
    if (SAW.size() == n)
    {
        cout << "YAY\n";
    }
*/
    return coordinates;
}

int GenerateWalkEfficientKennedyInspired(vector<int> directions,set<vector<int>> checker, int pivotpoint, int pivotradius)
{
    //cout << "Pivot\n";
     /*
    Directions List 
    0 Up +y
    1 Right +x
    2 Down -y
    3 Left -x
    4 +z
    5 -z 
    */
    //set<vector<int>> checker;
    //cout << "Pivot Point" << pivotpoint << " " << "Pivot Radius" << pivotradius << "\n";
    vector<int> row(d, 0);
    vector<int> back_row(d, 0);
    
    checker.insert(row);
    if(directions[pivotpoint]==0)
        {
            row[1] = row[1] + 1;
        }    
    else if(directions[pivotpoint]==1)
        {
            row[0] = row[0] + 1;
        } 
    else if(directions[pivotpoint]==2)
        {
            row[1] = row[1] - 1;
        } 
    else if(directions[pivotpoint]==3)
        {
            row[0] = row[0] - 1;
        } 
    else if(directions[pivotpoint]==4)
        {
            row[2] = row[2] + 1;
        } 
    else if(directions[pivotpoint]==5)
        {
            row[2] = row[2] - 1;
        }

    checker.insert(row);
    //cout << row[0] << " " << row[1] << "\n";
    //cout << back_row[0] << " " << back_row[1] << "\n\n";
    
    for (int k=1; k<pivotradius+5; k++) 
    {
        if ((pivotpoint+k == (n)) || (pivotpoint-k == -1))
        {   
            //One side of the pivot radius has reached the end
            //need to proceed by increasing if PP closer to 0 or decrease if PP close to n
    
            if (pivotpoint >= n/2)
            {
                for (int kk=k; kk<n-k+1;kk++)
                {
                    if(directions[pivotpoint-kk]==0)
                    {
                        back_row[1] = back_row[1] - 1;
                    }    
                    else if(directions[pivotpoint-kk]==1)
                    {
                        back_row[0] = back_row[0] - 1;
                    } 
                    else if(directions[pivotpoint-kk]==2)
                    {
                        back_row[1] = back_row[1] + 1;
                    } 
                    else if(directions[pivotpoint-kk]==3)
                    {
                        back_row[0] = back_row[0] + 1;
                    } 
                    else if(directions[pivotpoint-kk]==4)
                    {
                        back_row[2] = back_row[2] - 1;
                    } 
                    else if(directions[pivotpoint-kk]==5)
                    {
                        back_row[2] = back_row[2] + 1;
                    }   
                    checker.insert(back_row);
                    
                    //cout << back_row[0] << " " << back_row[1] << "\n\n";
                    if (checker.size()!=kk+(2*k)-k+1)
                    {
                        //cout << "BAD\n";
                        //If not a SAW return the saved set and a 1 to indicate we should return to old set of directions
                        return 0;
                    }
                }
                break;
            }
            else 
            {
                for (int kk=k; kk<n-k+1;kk++)
                {
                    if(directions[pivotpoint+kk]==0)
                    {
                        row[1] = row[1] + 1;
                    }    
                    else if(directions[pivotpoint+kk]==1)
                    {
                        row[0] = row[0] + 1;
                    } 
                    else if(directions[pivotpoint+kk]==2)
                    {
                        row[1] = row[1] - 1;
                    } 
                    else if(directions[pivotpoint+kk]==3)
                    {
                        row[0] = row[0] - 1;
                    } 
                    else if(directions[pivotpoint+kk]==4)
                    {
                        row[2] = row[2] + 1;
                    } 
                    else if(directions[pivotpoint+kk]==5)
                    {
                        row[2] = row[2] - 1;
                    }
                    checker.insert(row);
                    //cout << row[0] << " " << row[1] << "\n\n";
                    
                    if (checker.size()!=kk+(2*k)-k+1)
                    {
                        //cout << "BAD\n";
                        //If not a SAW return the saved set and a 1 to indicate we should return to old set of directions
                        return 0;
                    }
                }

                break;
            }
            
        }
        //Send row forward 1

            if(directions[pivotpoint+k]==0)
            {
                row[1] = row[1] + 1;
            }    
            else if(directions[pivotpoint+k]==1)
            {
                row[0] = row[0] + 1;
            } 
            else if(directions[pivotpoint+k]==2)
            {
                row[1] = row[1] - 1;
            } 
            else if(directions[pivotpoint+k]==3)
            {
                row[0] = row[0] - 1;
            } 
            else if(directions[pivotpoint+k]==4)
            {
                row[2] = row[2] + 1;
            } 
            else if(directions[pivotpoint+k]==5)
            {
                row[2] = row[2] - 1;
            }
            checker.insert(row);  

        
        //Move 2nd coord vector back a space

            if(directions[pivotpoint-k]==0)
            {
                back_row[1] = back_row[1] - 1;
            }    
            else if(directions[pivotpoint-k]==1)
            {
                back_row[0] = back_row[0] - 1;
            } 
            else if(directions[pivotpoint-k]==2)
            {
                back_row[1] = back_row[1] + 1;
            } 
            else if(directions[pivotpoint-k]==3)
            {
                back_row[0] = back_row[0] + 1;
            } 
            else if(directions[pivotpoint-k]==4)
            {
                back_row[2] = back_row[2] - 1;
            } 
            else if(directions[pivotpoint-k]==5)
            {
                back_row[2] = back_row[2] + 1;
            }   
            checker.insert(back_row);
        
        
        //cout << row[0] << " " << row[1] << "\n";
        //cout << back_row[0] << " " << back_row[1] << "\n\n";
        
        //As soon as set sees dupe break loop and return a saved set of coordinates
     
        
        if (checker.size()!=2*k+2)
        {
            //cout << "BAD\n";
            //If not a SAW return the saved set and a 1 to indicate we should return to old set of directions
            return 0;
        }

    }
    
    
    //cout << "\n";
    return 1;
}

int PivotAlgorithm(int no_iterations, int runs)
{
    ofstream file;
    int counter;
    //Coordinates Array
    set<vector<int>> uniques;
    int SAWCheck,SAWCheck2;
    set<vector<int>> checker;
    //Set up random direction, 2*d-1 possible directions
    

    //List of Directions
    //Starting off, all 0s all up 
    int pivot_radius;
    vector<int>  directions(n,0);
    vector<int>  directions_reset(n,0);
    uniques.insert(directions);
    vector<int>  directions_save(n,0);
    int SAW_point_choice, side_choice, rotation, direction_temp_hold;
    //Pivot Algorithm
    // 1) Random number for pivot point (1/n)
    // 2) Random number for pivot side (1/2)
    // 3) Random number for direction (1/2d)  
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> direction(1,2*d-1);
    uniform_int_distribution<int> pivot_side(1,2);
    uniform_int_distribution<int> pivot_point(0,n-1);
    
    // Based on the random number add direction to the directions list and do x%2*d
    for (int kkk=0; kkk<runs; kkk++)
    {
    directions = directions_reset;
  
    for (int i = 0; i<no_iterations;i++)
    {
        checker.clear();
        //Make point choice
        SAW_point_choice = pivot_point(generator);
        
        //Make side choice
        side_choice = pivot_side(generator);
        //Make rotation choice 
        rotation = direction(generator);
        //Save old set of directions
        directions_save = directions;
        if (side_choice == 1)
        {
            for (int j = 0; j<SAW_point_choice;j++)
            {
                direction_temp_hold = directions[j];
                direction_temp_hold += rotation;
                directions[j] = direction_temp_hold%(2*d);
            }
        }
        else if (side_choice == 2)
        {
            for (int j = SAW_point_choice; j<n;j++)
            {
                direction_temp_hold = directions[j];
                direction_temp_hold += rotation;
                directions[j] = direction_temp_hold%(2*d);
            }
        }
        if (SAW_point_choice > n/2)
        {
            pivot_radius = n-SAW_point_choice;
        }
        else 
        {
            pivot_radius = SAW_point_choice;
        }
        //Old Method
        //SAWCheck = GenerateWalkEfficient(directions,coordinates,checker,row, reset_row);
        //New Method
        SAWCheck2 = GenerateWalkEfficientKennedyInspired(directions,checker,SAW_point_choice,pivot_radius);
       
        if (SAWCheck2==0)
        {
            directions = directions_save;
        }
        else 
        {
            uniques.insert(directions);
        }   
        
    }
    }
    counter = uniques.size();
    
    return counter;
}

int main()
{
    double connective_constant;
    int counter;
    int iterations{int(1e5)};
    int runs{100};


    counter=PivotAlgorithm(iterations,runs);
    //counter+=PivotAlgorithm(iterations);

    connective_constant = pow(double(counter),(1.0/n));
    cout << connective_constant << "\n";
    cout << counter;
    return 0;
}