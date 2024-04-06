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

/*
Takes input variables 
* iterations : maximum number of iterations before the algorithm stops
* n : the desired length of the SAW
* x : fugacity term should be set between 0 and 1
* d : dimension of walk
* z : coordination number should be set to 2d

returns a vector of directions to be inputted into GenerateWalk() 
from there, coordinate set of GenerateWalk() can be inputted into SaveWalk()
*/

double Pneg(double x, double z)
{
    //Acceptance probability for negative move
    return min(1.0,2.0/(2.0+x*z));
}
double Pplus(double x, double z)
{
    //Acceptance probability for positive move
    return min(1.0,z*x/(2.0+x*z));
}

//Set P neutral to be the same as p negative, this way we can double the negative chance and then run a 50 50 to decide neutral or negative move
//Use pivot algorithm functions to check the SAW 


vector<vector<int>> GenerateWalk(const vector<int>& directions, int n, int d)
{

    vector<int> row(d, 0);
    vector<vector<int>> coordinates(n+1);
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
    for (int k=0; k<n; k++) 
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
        coordinates[k+1] = row;
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

int BerrettiSokalCheck(vector<int> directions,set<vector<int>> checker, int n,int d)
{
    
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
    vector<int> row(d, 0);
    checker.insert(row);

    for (int k=0; k<n; k++) 
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
        //As soon as set sees dupe break loop and return a saved set of coordinates
        checker.insert(row);
        if (checker.size()!=k+2)
        {
            //cout << "BAD\n";
            //If not a SAW return the saved set and a 1 to indicate we should return to old set of directions
            return 0;
        }
    }
    //cout << "\n";
    return 1;
}

int ReverseCheckBS(vector<int> directions,set<vector<int>> checker, int n,int d)
{
    if (n < 2*d-1)
    {
        return 1;
    }
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
    vector<int> row(d, 0);
    checker.insert(row);

    for (int k=n-1; k>-1; k--) 
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
        //As soon as set sees dupe break loop and return a saved set of coordinates
        checker.insert(row);
        if (checker.size()!=n-k+1)
        {
            //cout << "BAD\n";
            //If not a SAW return the saved set and a 1 to indicate we should return to old set of directions
            return 0;
        }
    }
    //cout << "\n";
    return 1;
}

int PivotCheckWalk(const vector<int>& directions, int pivotpoint, int pivotradius, int n, int d)
{
    if (n < 2*d-1)
    {
        return 1;
    }
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
    set<vector<int>> checker;
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
    
    for (int k=1; k<pivotradius+2; k++) 
    {
        if ((pivotpoint+k == (n)) || (pivotpoint-k == -1))
        {   
            //One side of the pivot radius has reached the end
            //need to proceed by increasing if PP closer to 0 or decrease if PP close to n
    
            if (pivotpoint > (n/2))
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
                for (int kk=k; kk<n-k;kk++)
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

int NewBSCheck(vector<int> directions,set<vector<int>> checker, int n, int d)
{
    //std::cout << "Length "<< n << "\n";
    if (n < 2*d-1)
    {
        return 1;
    }


    vector<int> front_row(d, 0);
    vector<int> back_row(d, 0);
    checker.insert(front_row);
    int limit;
    if (n%2==0)
    {
        limit = n/2;
    }
    else 
    {
        limit = floor(n/2) +1;
    }

    //Make First Move
    if(directions[floor(n/2)]==0)
        {
            front_row[1] = front_row[1] + 1;
        }    
    else if(directions[floor(n/2)]==1)
        {
            front_row[0] = front_row[0] + 1;
        } 
    else if(directions[floor(n/2)]==2)
        {
            front_row[1] = front_row[1] - 1;
        } 
    else if(directions[floor(n/2)]==3)
        {
            front_row[0] = front_row[0] - 1;
        } 
    else if(directions[floor(n/2)]==4)
        {
            front_row[2] = front_row[2] + 1;
        } 
    else if(directions[floor(n/2)]==5)
        {
            front_row[2] = front_row[2] - 1;
        }
    checker.insert(front_row);
    //std::cout << "HERE\n";
    for (int k=1; k<limit; k++) 
    {
        //Moving Neg Half
        //std::cout << "Front Row" << directions[floor(n/2)+k] << " Back Row" << directions[floor(n/2)-k] << "\n";
        if(directions[floor(n/2)-k]==0)
        {
            back_row[1] = back_row[1] - 1;
        }    
        else if(directions[floor(n/2)-k]==1)
        {
            back_row[0] = back_row[0] - 1;
        } 
        else if(directions[floor(n/2)-k]==2)
        {
            back_row[1] = back_row[1] + 1;
        } 
        else if(directions[floor(n/2)-k]==3)
        {
            back_row[0] = back_row[0] + 1;
        } 
        else if(directions[floor(n/2)-k]==4)
        {
            back_row[2] = back_row[2] - 1;
        } 
        else if(directions[floor(n/2)-k]==5)
        {
            back_row[2] = back_row[2] + 1;
        }
        //Moving Pos half
        if(directions[floor(n/2)+k]==0)
        {
            front_row[1] = front_row[1] + 1;
        }    
        else if(directions[floor(n/2)+k]==1)
        {
            front_row[0] = front_row[0] + 1;
        } 
        else if(directions[floor(n/2)+k]==2)
        {
            front_row[1] = front_row[1] - 1;
        } 
        else if(directions[floor(n/2)+k]==3)
        {
            front_row[0] = front_row[0] - 1;
        } 
        else if(directions[floor(n/2)+k]==4)
        {
            front_row[2] = front_row[2] + 1;
        } 
        else if(directions[floor(n/2)+k]==5)
        {
            front_row[2] = front_row[2] - 1;
        }
        
        
        //As soon as set sees dupe break loop and return a saved set of coordinates
        checker.insert(front_row);
        checker.insert(back_row);
        if (checker.size()!=2*k+2)
        {
            //cout << "BAD\n";
            //If not a SAW return the saved set and a 1 to indicate we should return to old set of directions
            return 0;
        }
    }
    if (n%2==0)
    {
        if(directions[0]==0)
        {
            back_row[1] = back_row[1] - 1;
        }    
        else if(directions[0]==1)
        {
            back_row[0] = back_row[0] - 1;
        } 
        else if(directions[0]==2)
        {
            back_row[1] = back_row[1] + 1;
        } 
        else if(directions[0]==3)
        {
            back_row[0] = back_row[0] + 1;
        } 
        else if(directions[0]==4)
        {
            back_row[2] = back_row[2] - 1;
        } 
        else if(directions[0]==5)
        {
            back_row[2] = back_row[2] + 1;
        }

    }
    checker.insert(back_row);
    if (checker.size() != n+1)
    {
        //cout << "BAD\n" ; 

        return 0;
    }

    //cout << "\n";
    return 1;
}

vector<int> PBSAlgorithm(double x, double z, int d, int n, int iterations)
{
    //Coordinate Vector which will be Returned
    
    int SAWCheck{0}, SAWCheck2{0},pivot_radius{0}, SAW_point_choice=0, side_choice{0}, rotation{0}, direction_temp_hold{0}, prev_dir{0}, negneut{0};
    vector<int> row(d);
    vector<int> temp_row(d);
    set<vector<int>> checker;
    checker.insert(row);
    vector<vector<int>> coordinates;
    coordinates.push_back(row);
    vector<int>  directions;
    directions.clear();
    vector<int>  directions_save;
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> directionPivot(1,2*d-1);
    uniform_int_distribution<int> pivot_side(1,2);   //Use for neg/nut
    uniform_int_distribution<int> directionBS(0,2*d-1);
    uniform_real_distribution<double> percent(0,1);
    //vector<int> length_per_step;
    int move {0};
    int step {0};
    double acc {0.0};
    double r {0.0};
    int removal {0};

    double index {0};
    
    int break_point=0;
    int length =0;

    //Method
    while (length < n)
    {
        //cout << length << "\n";
        break_point+=1;
        if (break_point == iterations)
        {
            break;
        }
        
        if (directions.size() == 0)
        {
            //std::cout << "At Origin \n";
            //At the origin so we make a positive move in any direction

            //Length = 1
            //Directions size = 1

            step = directionBS(generator);
            //std::cout << "Step in: "<< step <<" Directions \n";
            directions.push_back(step);
            if(step==0)
            {
                row[1] = row[1] + 1;
            }    
            else if(step==1)
            {
                row[0] = row[0] + 1;
            } 
            else if(step==2)
            {
                row[1] = row[1] - 1;
            } 
            else if(step==3)
            {
                row[0] = row[0] - 1;
            } 
            else if(step==4)
            {
                row[2] = row[2] + 1;
            } 
            else if(step==5)
            {
                row[2] = row[2] - 1;
            }
            coordinates.push_back(row);
            checker.insert(row);
            length = 1;
            //length_per_step.push_back(length);
            
        }
        else 
        {
            
            //If move is 1 > positive move to be made
            //If move = 2 > negative move
            acc = Pplus(x,z);
            if (acc < 1)
            {
                r = percent(generator);
                
                if (r > acc)
                {
                    //std::cout << "Failed \n";
                    move = 2;
                }
                else 
                {
                    move = 1;
                }
            }
            
            if (move == 1)
            {   
                //std::cout << "Positive \n";
                //Positive
                //understand previous direction and which way would result in it going back
                prev_dir = directions.back();

                if (prev_dir == 0)
                {
                    removal = 2;
                }
                else if (prev_dir == 1)
                {
                    removal = 3;
                }
                else if (prev_dir == 2)
                {
                    removal = 0;
                }
                else if (prev_dir == 3)
                {
                    removal = 1;
                }
                else if (prev_dir == 4)
                {
                    removal = 5;
                }
                else if (prev_dir == 5)
                {
                    removal = 4;
                }

                //Make new step avoiding the backwards move
                //Need to generate a random number which doesnt include the previous direction 
                //Creates a vector 1,2,3,4...
                std::vector<int> numbers(2*d);
                std::iota(std::begin(numbers), std::end(numbers), 1);
                //remove the prev_direction from this vector 
                // 1 > 0th ,, 2 > 1st ...
                //index = removal-1;
                numbers.erase(numbers.begin()+removal);
                //Shuffles the order
                std::shuffle(std::begin(numbers), std::end(numbers), std::mt19937{std::random_device{}()});
                //Then the last value can be taken as the random number .back()
                step = numbers.back()-1;    
                
                //Length and Directions + 1
                directions.push_back(step);
                length += 1;
                //Step made, now to see if the new step is a legal move
                temp_row = row;
                if(step==0)
                {
                    row[1] = row[1] + 1;
                }    
                else if(step==1)
                {
                    row[0] = row[0] + 1;
                } 
                else if(step==2)
                {
                    row[1] = row[1] - 1;
                } 
                else if(step==3)
                {
                    row[0] = row[0] - 1;
                } 
                else if(step==4)
                {
                    row[2] = row[2] + 1;
                } 
                else if(step==5)
                {
                    row[2] = row[2] - 1;
                }
                
                checker.insert(row);
                //if the set is not the same size as the set, this move is a duplicate and so must be voided
                //checker doesn't gain a new entry so we don't need to mess with it
                //reset the length, set the temp row to the old row and continue
                
                //SAWCheck2 = BerrettiSokalCheck(directions, checker, directions.size(), d);
                //SAWCheck = ReverseCheckBS(directions, checker, directions.size(), d);

                if (checker.size() != length+1)
                {

                    //Not self avoiding so remove last point
                    //length and directions -1
                    length -= 1;
                    directions.pop_back();
                    row = temp_row;
                    //length_per_step.push_back(length);
                    continue;
                }
                
                //else we are happy with the change
                coordinates.push_back(row);
                //length_per_step.push_back(length);
            }
            
            else if (move == 2)
            {
                negneut = pivot_side(generator);
                if (negneut == 1)
                {   
                    //Negative Move Chosen
                    //Directions and Length -1
                    directions.pop_back();
                    coordinates.pop_back();
                    length -= 1;
                    //Find the previous row in the set
                    auto find_in_set = checker.find(row);
                    // Checking is element present in set or not 
                    // And if present then Removing that element 
                    if (find_in_set != checker.end()) 
                        checker.erase(find_in_set);

                    row = coordinates.back();
                    //length_per_step.push_back(length);
                }
                
                else
                {
                    //cout << "PIVOT\n";
                    //Neutral Move - Pivot 
                    rotation = directionPivot(generator);
                    
                    side_choice = pivot_side(generator);
                    if (length == 1)
                    {
                        direction_temp_hold = directions[0];
                        direction_temp_hold += rotation;
                        directions[0] = direction_temp_hold%(2*d);
                        coordinates = GenerateWalk(directions,length,d);
                        checker.clear();
                        
                        for (int ii=0;ii<coordinates.size();ii++)
                        {
                            checker.insert(coordinates[ii]);
                        }
                        row = coordinates.back();
                        continue;
                    }
                    uniform_int_distribution<int> pivot_point(1,length-1);
                    SAW_point_choice = pivot_point(generator);
                    directions_save = directions;
                    //cout << SAW_point_choice << "SAWPChoice || Length" << length << "\n";
                    //cout << "Direction: " << directions[SAW_point_choice] << "\n";
                    
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
                        for (int j = SAW_point_choice; j<length;j++)
                        {
                            direction_temp_hold = directions[j];
                            direction_temp_hold += rotation;
                            directions[j] = direction_temp_hold%(2*d);
                        }
                    }
                    if (SAW_point_choice > length/2)
                    {
                        pivot_radius = n-SAW_point_choice;
                    }
                    else 
                    {
                        pivot_radius = SAW_point_choice;
                    }
        
                    SAWCheck = PivotCheckWalk(directions,SAW_point_choice,pivot_radius,directions.size(),d);
                    
                    if (SAWCheck==0)
                    {
                        directions = directions_save;
                        continue;
                    }

                    checker.clear();
                    row[0] =0; row[1] = 0;
                    coordinates[0] = row;
                    checker.insert(row);
                    for (int k=0; k<length; k++) 
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
                        coordinates[k+1] = row;
                        checker.insert(row);
                    }
                }
                
            }
            
        }
    }
    
    //std::cout << length << "\n";
    
    return directions;
}
void SaveWalk(vector<vector<int>> coordinates)
{
    ofstream file;

    //naming file to store results in  Big5000
    file.open("200kWalk.csv");
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
    

    double x{0.379};
    int d {2};
    double z{2*double(d)};
    vector<vector<int>> coords;
    vector<int> direction_vector;
    int desired_length{200000};

    vector<int> length_of_walks;
    int max_iters {50*desired_length};
    int counter = 0;
    int length_of_walk = 0;
    int big{100};
    //int length_of_walk2 = 0;
    
    direction_vector= PBSAlgorithm(x,z,d,desired_length,max_iters);
    coords=GenerateWalk(direction_vector,direction_vector.size(),d);
    SaveWalk(coords);
        
    /* 

    ofstream file;
    length_of_walks = MaximBSAlgorithm(x,z,d,max_iters,max_iters);
    file.open("LengthsPBS.csv");
    for (int kk=0;kk<length_of_walks.size();kk++)
    {
        file << kk << "," << length_of_walks[kk] << "\n";
    }
    file.close();
    
    
    for (int kkk=0;kkk<big;kkk++)

    {
        direction_vector= MaximBSAlgorithm(x,z,d,desired_length,max_iters);
        
        if (desired_length==direction_vector.size())
        {
            counter += 1;
        }
        
    }

    */
    return 0;
}
