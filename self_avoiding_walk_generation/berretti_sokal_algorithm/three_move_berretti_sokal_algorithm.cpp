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


double Pplus(double x, double z)
{
    //Acceptance probability for positive move
    return min(1.0,x*(z-1.0));
}

double Pneg(double x, double z)
{
    //Acceptance probability for negative move
    return min(1.0,1.0/(x*(z-1.0)));
}

vector<int> ThreeMoveBerrettiSokal(double x, double z, double d, int n, int desired_length)
{
    vector<int> row(d);
    vector<int> temp_row(d);
    vector<int> length_per_step;
    //make coordinates vector the length of n and cut off where necessary at the end
    //maximum length of coordinates is n 

    vector<vector<int>> coordinates;
    //need a temp coords vector for neutral moves in case we need to go back 
    vector<vector<int>> temp_coordinates;
    coordinates.push_back(row);
    temp_coordinates = coordinates;
    set<vector<int>> checker;

    //update the length and append set at the same time
    //if values are the same, new coord is valid 
    int length {1};
    checker.insert(row);

    //initialise a vector to store all directions and store the current SAW checker set
    //Make it of length n, this is the maximum length that could be needed
    
    vector<int> prev_directions;
    vector<int> temp_prev_directions;
    
    int prev_dir;
    
    //Random number generator for getting the direction 
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> direction(1,2*d);
    uniform_int_distribution<int> percent(1,100);

    

    //second random number generator to determine which move to make
    uniform_int_distribution<int> atmosphere_choice(1,2);
    uniform_int_distribution<int> neutral_fifty(1,2);
    int move {0};
    int step {0};
    double acc {0};
    double r {0};
    int random_number, removal;
    double index {0};
    //int neutral_check{0};
    int neutral{0};
    
    bool zeros = std::all_of(row.begin(), row.end(), [](int i) { return i==0; });

    while (length < desired_length)
    {
        break_point+=1;
        if (break_point == n)
        {
            break;
        }
        std::cout << "\n";
        std::cout << "For Loop \n";
        //std::cout << "Neutral Check" << neutral_check << "\n";
        //First move is positive move unbounded to any direction
        //std::cout << "\n";
        //std::cout <<"Before Move Row: "<< row[0] << " " << row[1] << "\n"; 

        zeros = std::all_of(row.begin(), row.end(), [](int j) { return j==0; });
        if (zeros == true)
        {
            std::cout << "At Origin \n";
            //check to see if the move should be accepted
            acc = Pplus(x,z);
            if (acc < 1)
            {
                acc = acc*100;
                r = percent(generator);
                
                if (r > acc)
                {
                    //std::cout << "Failed \n";
                    length_per_step.push_back(length);
                    continue;
                }
            }
            
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
            temp_coordinates = coordinates;
            temp_prev_directions = prev_directions;
            length_per_step.push_back(length);
        }

        else 
        {
            //If move is 1 > positive move to be made
            //If move = 2 > negative move
            move = atmosphere_choice(generator);
            //cout << move << "\n";
            //neutral_check = 0;
            //While loop always active
            //Want to break it when a valid move has been made
            //Want to continue if the neutral move failed
            while(1)
            {
                
                std::cout << "While Loop \n";
                //std::cout << "Neutral Check" << neutral_check << "\n";

                if (move == 1)
                {   
                    std::cout << "Positive Atmosphere \n";

                    neutral = neutral_fifty(generator);

                    if (neutral == 1)
                    {
                        std::cout << "Neutral \n";
                        
                        //set temp storage of our current values
                        temp_coordinates = coordinates;
                        temp_prev_directions = prev_directions;
                        temp_row = row;

                        //Step 1: Remove previous step
                        temp_coordinates.pop_back();
                
                        //set step to be the final value of directions
                        step = temp_prev_directions.back();
                    
                        //remove this value from prev directions 
                        temp_prev_directions.pop_back();

                        //Take the length back by 1
                        length -= 1;

                        //If the neutral move fails, simply plug the removed row back in
                        //Find the previous row in the set
                        auto find_in_set = checker.find(temp_row);
                        // Checking is element present in set or not 
                        // And if present then Removing that element 
                        if (find_in_set != checker.end()) 
                            checker.erase(find_in_set);


                        if (step%2 == 0)
                        {
                            index = (step/2) -1;
                            //go back step
                            temp_row[index] = temp_row[index] + 1;
                        }
                        else if (step%2 !=0)
                        {   
                            step += 1;
                            index = (step/2) -1;
                            //revert step
                            temp_row[index] = temp_row[index] - 1; 
                            step -= 1;   
                        }

                        

                        //Now we have step (future move) and prev_dir (past move) these must be taken from our possible options
                        //also want to account for the potential of starting at origin
                        //Finding removal direction (past)
                        if (temp_prev_directions.size() > 0)
                        {
                            prev_dir = temp_prev_directions.back();

                            if (prev_dir%2 == 0)
                            {
                                removal = prev_dir - 1;
                            }
                            else if (prev_dir%2 != 0)
                            {
                                removal = prev_dir + 1;
                            }  
                            //We now want to make a random move without going back to the way we went, or back on itself
                            //Need to generate a random number which doesnt include the previous direction 
                            //Creates a vector 1,2,3,4...
                            std::vector<int> numbers(2*d);
                            std::iota(std::begin(numbers), std::end(numbers), 1);
                            //remove the prev_direction from this vector 
                            //remove future move from the vector
                            // 1 > 0th ,, 2 > 1st ...
                            index = removal-1;
                            numbers.erase(numbers.begin()+index);
                            index = step - 1;
                            numbers.erase(numbers.begin()+index);
                            //Shuffles the order
                            std::shuffle(std::begin(numbers), std::end(numbers), std::mt19937{std::random_device{}()});
                            //Then the last value can be taken as the random number .back()
                            step = numbers.back();    
                            //add our new step to our temp storage of directions
                            temp_prev_directions.push_back(step);
                        }
                        else 
                        {
                            //We are now at origin so we don't want to block any past moves as there are none

                            //Creates a vector 1,2,3,4...
                            std::vector<int> numbers(2*d);
                            std::iota(std::begin(numbers), std::end(numbers), 1);
                            
                            //remove future move from the vector
                            // 1 > 0th ,, 2 > 1st ...
                            index = step - 1;
                            numbers.erase(numbers.begin()+index);

                            //Shuffles the order
                            std::shuffle(std::begin(numbers), std::end(numbers), std::mt19937{std::random_device{}()});
                            //Then the last value can be taken as the random number .back()
                            step = numbers.back();    
                            //add our new step to our temp storage of directions
                            temp_prev_directions.push_back(step);
                        }
                        

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
                        //However unlike positive move, a move has already been taken from the neutral move so this row must be added
                        //To be reset:
                        //  Add row back to set
                        //  Set temp_row to row
                        //  Set move = 2 to switch to negative mode

                        

                        if (checker.size() != length)
                        {
                            checker.insert(row);
                            temp_coordinates = coordinates;
                            temp_prev_directions = prev_directions;
                            temp_row = row;
                            move = 2;
                            continue;
                            //std::cout << "Neutral not a SAW \n";
                            
                        }

                        //If the new move leads to a valid SAW 
                        //Update all old coordinates and directions based on the new changes
                        coordinates = temp_coordinates;
                        prev_directions = temp_prev_directions;
                        row = temp_row;
                        length_per_step.push_back(length);
                        //neutral_check = 1;
                        break;
                        
                    }
                    //Positive
                    //check to see if the move should be accepted
                    else if (neutral == 2)
                    {
                        std::cout << "Positive Move\n";
                        acc = Pplus(x,z);
                        if (acc < 1)
                        {
                            r = percent(generator);
                            acc = acc*100;
                            if (r > acc)
                            {
                                //std::cout << "Failed \n";
                                //neutral_check = 1;
                                length_per_step.push_back(length);
                                break;
                            }
                        }

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
                            //neutral_check = 1;
                            break;
                        }

                        //else we are happy with the change and can add it to our coordinates
                        row = temp_row;
                        coordinates.push_back(row);
                        length_per_step.push_back(length);
                        //neutral_check = 1;
                        break;
                    }
                }
                else if (move == 2)
                {
                    std::cout << "Negative Atmosphere \n";
                    neutral = neutral_fifty(generator);

                    if (neutral == 1)
                    {
                        //Neutral move
                        std::cout << "Neutral Move\n";
                        //set temp storage of our current values
                        temp_coordinates = coordinates;
                        temp_prev_directions = prev_directions;
                        temp_row = row;

                        //Step 1: Remove previous step
                        temp_coordinates.pop_back();
                
                        //set step to be the final value of directions
                        step = temp_prev_directions.back();
                    
                        //remove this value from prev directions 
                        temp_prev_directions.pop_back();
                        length -= 1;

                        //If the neutral move fails, simply plug the removed row back in
                        //Find the previous row in the set
                        auto find_in_set = checker.find(temp_row);
                        // Checking is element present in set or not 
                        // And if present then Removing that element 
                        if (find_in_set != checker.end()) 
                            checker.erase(find_in_set);


                        if (step%2 == 0)
                        {
                            index = (step/2) -1;
                            //go back step
                            temp_row[index] = temp_row[index] + 1;
                        }
                        else if (step%2 !=0)
                        {   
                            step += 1;
                            index = (step/2) -1;
                            //revert step
                            temp_row[index] = temp_row[index] - 1; 
                            step -= 1;   
                        }

                        

                        //Now we have step (future move) and prev_dir (past move) these must be taken from our possible options
                        //also want to account for the potential of starting at origin
                        //Finding removal direction (past)
                        if (temp_prev_directions.size() > 1)
                        {
                            prev_dir = temp_prev_directions.back();

                            if (prev_dir%2 == 0)
                            {
                                removal = prev_dir - 1;
                            }
                            else if (prev_dir%2 != 0)
                            {
                                removal = prev_dir + 1;
                            }  
                            //We now want to make a random move without going back to the way we went, or back on itself
                            //Need to generate a random number which doesnt include the previous direction 
                            //Creates a vector 1,2,3,4...
                            std::vector<int> numbers(2*d);
                            std::iota(std::begin(numbers), std::end(numbers), 1);
                            //remove the prev_direction from this vector 
                            //remove future move from the vector
                            // 1 > 0th ,, 2 > 1st ...
                            index = removal-1;
                            numbers.erase(numbers.begin()+index);
                            index = step - 1;
                            numbers.erase(numbers.begin()+index);
                            //Shuffles the order
                            std::shuffle(std::begin(numbers), std::end(numbers), std::mt19937{std::random_device{}()});
                            //Then the last value can be taken as the random number .back()
                            step = numbers.back();    
                            //add our new step to our temp storage of directions
                            temp_prev_directions.push_back(step);
                        }
                        else 
                        {
                            //We are now at origin so we don't want to block any past moves as there are none

                            //Creates a vector 1,2,3,4...
                            std::vector<int> numbers(2*d);
                            std::iota(std::begin(numbers), std::end(numbers), 1);
                            
                            //remove future move from the vector
                            // 1 > 0th ,, 2 > 1st ...
                            index = step - 1;
                            numbers.erase(numbers.begin()+index);

                            //Shuffles the order
                            std::shuffle(std::begin(numbers), std::end(numbers), std::mt19937{std::random_device{}()});
                            //Then the last value can be taken as the random number .back()
                            step = numbers.back();    
                            //add our new step to our temp storage of directions
                            temp_prev_directions.push_back(step);
                        }

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
                        //However unlike positive move, a move has already been taken from the neutral move so this row must be added
                        //To be reset:
                        //  Add row back to set
                        //  Set temp_row to row
                        //  Set move = 1 to switch to positive mode

                        //Length doesn't need to be changed as it went back and then forward
                        //Temp_coordinates is only used in neutral moves and it is reset at the beginning
                        //Same for temp directions

                        if (checker.size() != length)
                        {
                            checker.insert(row);
                            temp_coordinates = coordinates;
                            temp_prev_directions = prev_directions;
                            temp_row = row;
                            move = 1;
                            continue;
                            //std::cout << "Neutral not a SAW \n";
                            
                        }

                        //If the new move leads to a valid SAW 
                        //Update all old coordinates and directions based on the new changes
                        coordinates = temp_coordinates;
                        prev_directions = temp_prev_directions;
                        row = temp_row;
                        length_per_step.push_back(length);
                        //neutral_check = 1;
                        break;  
                    }
                    else if (neutral == 2)
                    {
                        std::cout << "Negative Move\n";
                        //Negative Move
                        //check to see if the move should be accepted
                        acc = Pneg(x,z);
                        if (acc < 1)
                        {
                            r = percent(generator);
                            acc = acc*100;
                            if (r > acc)
                            {
                                //std::cout << "Failed \n";
                                //neutral_check = 1;
                                length_per_step.push_back(length);
                                break;
                            }
                        }
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
                        //neutral_check = 1;
                        length_per_step.push_back(length);
                        break;
                    }
                }
                    
            }
            //neutral_check = 0;
             
        }
        
        //std::cout <<"After Move Row: "<< row[0] << " " << row[1] << "\n"; 
        

    }
    //std::cout << "Done \n";

    ofstream file;

    //naming file to store results in
    file.open("ThreeStepBSSAW2D.csv");
    for (int i = 0; i < length; i++) 
    { 
        for ( 
            auto it = coordinates[i].begin(); 
            it != coordinates[i].end(); it++) 
            file << *it << ","; 
        file << endl; 
    } 
    return length_per_step;   
}

int main()
{   
    double x{0.39};
    double d{2};
    double z{2*d};
    int n {5*n};
    int desired_length {1000};
    vector<int> length_of_walks;
    ofstream file;
    length_of_walks = ThreeMoveBerrettiSokal(x,z,d,n,desired_length);
}