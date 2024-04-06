#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <bits/stdc++.h>
#include <array>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;

/*
Takes input variables 
* n : maximum number of iterations before the algorithm stops
* desired_length : the desired length of the SAW
* x : fugacity term should be set between 0 and 1
* d : dimension of walk
* z : coordination number should be set to 2d
* save : 1 to store the walk, 0 to avoid this step

*/



double eucl_dist(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]);
}
double eucl_dist3D(vector<int> final_pos)
{
    return sqrt(final_pos[0]*final_pos[0]+final_pos[1]*final_pos[1]+final_pos[2]*final_pos[2]);
}
double Pplus(double x, double z)
{
    //Acceptance probability for positive move
    return min(1.0,z*x/(1.0+x*z));
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
double localField(int direction_minus_1,int direction_current)
{
    //Local Field will return number of curves at the point
    return 1 - 2*double(delta_func(direction_current,direction_minus_1));
}
double Pneg(double x, double z)
{
    //Acceptance probability for negative move
    return min(1.0,1.0/(1.0+x*z));
}

void SaveWalk(vector<vector<int>> coordinates)
{
    ofstream file;

    //naming file to store results in
    file.open("TwoStepBSSAW2DWeighted.csv");
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

vector<double> TwoMoveBerrettiSokal(double x, double z, double d, int n, int desired_length,  int save)
{
    /*
    x fugacity 
    z = 2*d
    d dimension 
    n max number of iterations 
    desired_length required length of walk 
    save 1/0, save the walk to csv file/not
    */


    vector<int> row(d);
    vector<int> temp_row(d);
    
    //make coordinates vector the length of n and cut off where necessary at the end
    //maximum length of coordinates is n 
    double dS;
    vector<vector<int>> coordinates;
    coordinates.push_back(row);
    set<vector<int>> checker;

    //update the length and append set at the same time
    //if values are the same, new coord is valid 
    int length {1};
    double e2e{0};
    checker.insert(row);

    //initialise a vector to store all directions and store the current SAW checker set
    //Make it of length n, this is the maximum length that could be needed
    
    vector<int> prev_directions;
    int prev_dir;
    
    //Random number generator for getting the direction 
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> direction(1,2*d);
    uniform_real_distribution<double> percent(0,1);

    

    //second random number generator to determine which move to make
    //uniform_int_distribution<int> atmosphere_choice(1,2);
    vector <int> length_per_step;
    int move {0};
    int step {0};
    double acc {0};
    double r {0};
    int random_number, removal;
    double index {0};
    bool zeros = std::all_of(row.begin(), row.end(), [](int i) { return i==0; });
    int break_point{0};
    while (length < desired_length)
    {
        break_point+=1;
        if (break_point == n)
        {
            break;
        }
        //First move is positive move unbounded to any direction
        //std::cout << "\n";
        //std::cout <<"Before Move Row: "<< row[0] << " " << row[1] << "\n"; 

        zeros = std::all_of(row.begin(), row.end(), [](int i) { return i==0; });
        if (zeros == true)
        {
            //std::cout << "At Origin \n";
            //check to see if the move should be accepted
            
            
            step = direction(generator);
            //std::cout << "Step in: "<< step <<" Directions \n";
            prev_directions.push_back(step);    
            if (step%2 == 0)
            {
                index = (step/2) -1;
                //make step
                row[index] = row[index] - 1;
                temp_row[index] = temp_row[index] - 1;
            }
            else if (step%2 !=0)
            {   
                step += 1;
                index = (step/2) -1;
                //make step
                row[index] = row[index] + 1;
                temp_row[index] = temp_row[index] + 1;
            }
            coordinates.push_back(row);
            checker.insert(row);
            length += 1;
            length_per_step.push_back(length);
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
            //move = atmosphere_choice(generator);
            //cout << move << "\n";
            if (move == 1)
            {   
                //std::cout << "Positive \n";
                //Positive
                //check to see if the move should be accepted
               
                //understand previous direction and which way would result in it going back
                prev_dir = prev_directions.back();

                if (prev_dir%2 == 0)
                {
                    removal = prev_dir - 1;
                }
                else if (prev_dir%2 != 0)
                {
                    removal = prev_dir + 1;
                }

                //Make new step avoiding the backwards move
                random_number = direction(generator); 

                //Need to generate a random number which doesnt include the previous direction 
                //Creates a vector 1,2,3,4...
                std::vector<int> numbers(2*d);
                std::iota(std::begin(numbers), std::end(numbers), 1);
                //remove the prev_direction from this vector 
                // 1 > 0th ,, 2 > 1st ...
                index = removal-1;
                numbers.erase(numbers.begin()+index);
                //Shuffles the order
                std::shuffle(std::begin(numbers), std::end(numbers), std::mt19937{std::random_device{}()});
                //Then the last value can be taken as the random number .back()
                step = numbers.back();    
                
                prev_directions.push_back(step);


                //std::cout << "Step in: "<< step <<" Directions \n";
                
            

                if (step%2 == 0)
                {
                    index = (step/2) -1;
                    //make step
                    temp_row[index] = temp_row[index] - 1;
                }
                else if (step%2 !=0)
                {   
                    step += 1;
                    index = (step/2) -1;
                    //make step
                    temp_row[index] = temp_row[index] + 1;
                }

                //Step made, now to see if the new step is a legal move
                checker.insert(temp_row);
                length += 1;

                //if the set is not the same size as the set, this move is a duplicate and so must be voided
                //checker doesn't gain a new entry so we don't need to mess with it
                //reset the length, set the temp row to the old row and continue

                if (checker.size() != length)
                {
                    length -= 1;
                    temp_row = row;
                    prev_directions.pop_back();
                    length_per_step.push_back(length);
                    continue;
                }

                //else we are happy with the change and can add it to our coordinates
                row = temp_row;
                coordinates.push_back(row);
                length_per_step.push_back(length);

            }
            else if (move == 2)
            {
                //std::cout << "Negative \n";
                //Negative
                //check to see if the move should be accepted
                //We want to remove the previous step
                //remove the entry from coordinates
                coordinates.pop_back();
                
                //set step to be the final value of directions
                step = prev_directions.back();
                //std::cout << "Step in: "<< step <<" Directions \n";
                //remove this value from prev directions 
                prev_directions.pop_back();
                length -= 1;

                //Find the previous row in the set
                auto find_in_set = checker.find(row);
                // Checking is element present in set or not 
                // And if present then Removing that element 
                if (find_in_set != checker.end()) 
                    checker.erase(find_in_set);


                if (step%2 == 0)
                {
                    index = (step/2) -1;
                    //go back step
                    row[index] = row[index] + 1;
                }
                else if (step%2 !=0)
                {   
                    step += 1;
                    index = (step/2) -1;
                    //revert step
                    row[index] = row[index] - 1;
                    
                }
                temp_row = row;
                length_per_step.push_back(length);
            } 
        }
        
        //std::cout <<"After Move Row: "<< row[0] << " " << row[1] << "\n"; 
    

    }
    if (save == 1)
    {
        SaveWalk(coordinates);
    }
    //std::cout << "Done \n";
    vector<double> results(2);
    results[0] = double(length);
    
    if (d==2)
    {
        e2e = eucl_dist(coordinates[length-1]);
    }
    else if (d==3)
    {
        e2e = eucl_dist3D(coordinates[length-1]);
    }
    
    results[1] = e2e;
    return results;
}


int main()
{   
    double x{0};
    double d{2};
    double z{2*d};
    
    vector<double> things;
    
    double success_count {0};

    double length {0};
    double e2e {0};
    ofstream file;
    double weights{0};
    int desired_length{10000};
    int n {10000};
    int no_of_points{110},total{100};
    vector<int> lengths(total);
    double summation{0};
    double avg;
    double std;
    things = TwoMoveBerrettiSokal(x,z,d,n,desired_length,1); 

    file.open("e2eFugacities2D.csv");
    for (int ii=0;ii<no_of_points;ii++)
    {
        
        summation = 0;
        for (int jj=0;jj<total;jj++)
        {
            things = TwoMoveBerrettiSokal(x,z,d,n,desired_length,0);
            summation += things[0];
            lengths[jj] = things[0];
        }
        avg = double(summation)/double(total);
        summation = 0;
        for (int jj=0;jj<lengths.size();jj++)
        {
            summation += ((double(lengths[jj]) - avg)*(double(lengths[jj]) - avg));
        }
        std = sqrt(double(summation)/double(total));

        file << x << "," << avg << "," << std <<  "\n";
        x = x+0.005;
    }
    file.close();

    
   return 0;
}