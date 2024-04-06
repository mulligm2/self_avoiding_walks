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

const int d = 3;

double eucl_dist(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]);
}
double eucl_dist3D(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]+final_pos[2]*final_pos[2]);
}
double eucl_dist4D(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]+final_pos[2]*final_pos[2]+final_pos[3]*final_pos[3]);
}
int delta_func(int xy, int xpyp)
{
    if (xy==xpyp)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int localField(int direction_minus_1,int direction_current,int direction_plus_1)
{
    //Local Field will return number of curves at the point
    return 2 - delta_func(direction_current,direction_minus_1) - delta_func(direction_current,direction_plus_1);
}
vector<vector<int>> GenerateWalk(vector<int> directions, vector<vector<int>> coordinates, int n)
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
        else if(directions[k]==6)
        {
            row[3] = row[3] + 1;
        } 
        else if(directions[k]==7)
        {
            row[3] = row[3] - 1;
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

int GenerateWalkEfficientKennedyInspired(vector<int> directions, vector<vector<int>> coordinates,set<vector<int>> checker, int pivotpoint, int pivotradius, int n)
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
    else if(directions[pivotpoint]==6)
        {
            row[3] = row[3] + 1;
        } 
    else if(directions[pivotpoint]==7)
        {
            row[3] = row[3] - 1;
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
                    else if(directions[pivotpoint]==6)
                    {
                        back_row[3] = back_row[3] - 1;
                    } 
                    else if(directions[pivotpoint]==7)
                    {
                        back_row[3] = back_row[3] + 1;
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
                    else if(directions[pivotpoint]==6)
                    {
                        row[3] = row[3] + 1;
                    } 
                    else if(directions[pivotpoint]==7)
                    {
                        row[3] = row[3] - 1;
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
            else if(directions[pivotpoint]==6)
            {
                row[3] = row[3] + 1;
            } 
            else if(directions[pivotpoint]==7)
            {
                row[3] = row[3] - 1;
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
            else if(directions[pivotpoint]==6)
            {
                back_row[3] = back_row[3] - 1;
            } 
            else if(directions[pivotpoint]==7)
            {
                back_row[3] = back_row[3] + 1;
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

double PivotAlgorithm(int no_iterations, int n, int SAWs, double weighting)
{
    ofstream file;
    //Coordinates Array
    vector<vector<int>> coordinates (n);
    int SAWCheck,SAWCheck2;
    set<vector<int>> checker;
    //Set up random direction, 2*d-1 possible directions
    vector<int> row(d, 0);
    vector<int> reset_row(d, 0);
    double e2e {0};
    int dS;
    double r,acc;
    //List of Directions
    //Starting off, all 0s all up 
    int pivot_radius;
    int counter{0};
    vector<int>  directions(n,0);
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
    uniform_real_distribution<double> percent(0.0,1.0);
    // Based on the random number add direction to the directions list and do x%2*d
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
       
        SAWCheck2 = GenerateWalkEfficientKennedyInspired(directions,coordinates,checker,SAW_point_choice,pivot_radius,n);
        //SAWCheck2 = 1;
        
        if (SAWCheck2==0)
        {
            directions = directions_save;
        }
        
    }
    
    while (counter < SAWs)
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
        if ((SAW_point_choice != 0) && (SAW_point_choice != n-1)) 
        {
            dS = localField(directions[SAW_point_choice-1],directions[SAW_point_choice],directions[SAW_point_choice+1]) - localField(directions_save[SAW_point_choice-1],directions_save[SAW_point_choice],directions_save[SAW_point_choice+1]); 
        }
        else if (SAW_point_choice == 0)
        {
            dS = localField(directions[SAW_point_choice],directions[SAW_point_choice],directions[SAW_point_choice+1]) - localField(directions_save[SAW_point_choice],directions_save[SAW_point_choice],directions_save[SAW_point_choice+1]);
        }
        else if (SAW_point_choice == n-1)
        {
            dS = localField(directions[SAW_point_choice-1],directions[SAW_point_choice],directions[SAW_point_choice]) - localField(directions_save[SAW_point_choice-1],directions_save[SAW_point_choice],directions_save[SAW_point_choice]);
        }
        //Calc accuracy
        acc = exp(-dS*weighting);
        
        if (acc < 1)
        {
            r = percent(generator);
            if (r > acc)
            {
                //reject change
                directions = directions_save;
                continue;
            }
        }
        SAWCheck2 = GenerateWalkEfficientKennedyInspired(directions,coordinates,checker,SAW_point_choice,pivot_radius,n);
        //SAWCheck2=1;
        
        if (SAWCheck2==0)
        {
            directions = directions_save;
        }
        else 
        {
            coordinates = GenerateWalk(directions,coordinates,n);
            if (d==2)
            {
                e2e += eucl_dist(coordinates[n-1])*eucl_dist(coordinates[n-1]);
            }
            else if (d==3)
            {
                e2e += eucl_dist3D(coordinates[n-1])*eucl_dist3D(coordinates[n-1]);
            }
            else if (d==4)
            {
                e2e += eucl_dist4D(coordinates[n-1])*eucl_dist4D(coordinates[n-1]);
            }
            
            counter += 1;
        }
    }

    e2e = e2e/counter;

    return e2e;
}

void SaveWalk(vector<vector<int>> coordinates)
{
    ofstream file;

    //naming file to store results in
    file.open("WeightedSAW.csv");
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
    int n{20};
    int iterations{5*n};
    double e2e{0.0};

    double weight{-13};

    int total{45};

    int step{2};

    int big_number{20000};

    //Make 2 for loops, first for length changing, 2nd for iterations  


    ofstream file;
    file.open("e2eWeightedCurvy13.csv");
    
    //Generate Initial SAW 

    for (int ii=0;ii<total;ii++)
    {
        iterations = 5*n;
        
        e2e = PivotAlgorithm(iterations,n,big_number,weight);  

        file << n << "," << e2e << "\n";
        n += step;
    }
    file.close();
}
