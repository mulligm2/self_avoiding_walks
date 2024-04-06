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
V2 of pivot algorithm in C++ 

both methods use matrix multiplication

PivotAlgorithmHash() performs pivot algorithm using hash table to check self avoidance
PivotAlgorithmKennedy() checks self avoidance using method outlined by Tom Kennedy

*/

//n number of vertices (n-1 edges)

const int d = 2;

vector<vector<int>> MatMul(const vector<vector<int>>& coordinates, const vector<vector<int>>& rot_matrix,vector<vector<int>> resulting_vector, vector <int> row)
{
    
    for(int i=0; i<resulting_vector.size();i++)
    {   
        row[0]=0;row[1]=0;

        //Second loops through dimension
        for(int j=0;j<resulting_vector[0].size();j++)
        {
            
            for(int k=0;k<resulting_vector[0].size();k++)
            {
                row[j] += coordinates[i][k] * rot_matrix[k][j];
            }
        }
        resulting_vector[i] = row;
    }
    return resulting_vector;
}

vector<vector<int>> AddVectors(vector<vector<int>> coordinates, const vector<int>& row)
{
    
    for (int ii=0;ii<coordinates.size();ii++)
    {
        coordinates[ii][0] += row[0];
        coordinates[ii][1] += row[1];
    }

    return coordinates;
}

vector<vector<int>> SubtractVectors(vector<vector<int>> coordinates, const vector<int>& row)
{
    
    for (int ii=0;ii<coordinates.size();ii++)
    {
        coordinates[ii][0] -= row[0];
        coordinates[ii][1] -= row[1];
    }

    return coordinates;
}

double eucl_dist(const vector<int>& final_pos, const vector<int>& first_pos)
{
    return sqrt((final_pos[0]-first_pos[0])*(final_pos[0]-first_pos[0])+(final_pos[1]-first_pos[1])*(final_pos[1]-first_pos[1]));
}

vector<int> PivotAlgorithmHash(int n, int iterations)
{
    vector<vector<int>> coordinates(n);
    vector<vector<int>> front_coords(n);
    vector<vector<int>> back_coords(n);
    vector<int>  directions(n,0);
    vector<int>  directionsfront(n,0);
    vector<int>  directionsback(n,0);
    vector<int>  directions_save(n,0);
    int SAWCheck;
    set<vector<int>> checker;
    //Set up random direction, 2*d-1 possible directions
    vector<int> row(d, 0);
    vector<int> reset_row(d, 0);

    //Add a counter to measure checks done per iteration 
    int iteration_checks{0};
    vector <int> checks_per_iteration(iterations);

    //List of Directions
    //Starting off, all 0s all up 
    //int pivot_radius;
    int SAW_point_choice, side_choice, rotation,direction_temp_hold;
    //Pivot Algorithm
    // 1) Random number for pivot point (1/n)
    // 2) Random number for pivot side (1/2)
    // 3) Random number for direction (1/2d)  
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> direction(1,2*d-1);
    uniform_int_distribution<int> pivot_side(1,2);
    uniform_int_distribution<int> pivot_point(1,n-1);
    vector<vector<int>> rot_mat;
    vector<vector<int>> rot_mat1;
    vector<vector<int>> rot_mat2;
    vector<vector<int>> rot_mat3;
    vector<vector<int>> pivot_point_vector;
    //Set up coord vector to be rod in x dim
    for (int kk=0;kk<n;kk++)
    {
        row[1] = kk;
        coordinates[kk] = row;
    }
    
    if(d == 2)
    {
        vector<int> r1(2); r1[0] = 0; r1[1] = -1;
        vector<int> r2(2); r2[0] = 1; r2[1] = 0;
        rot_mat1.push_back(r1);rot_mat1.push_back(r2); //90 degrees

        r1[0] = -1; r1[1] = 0;
        r2[0] = 0; r2[1] = -1;
        rot_mat2.push_back(r1);rot_mat2.push_back(r2); //180 degrees

        r1[0] = 0; r1[1] = 1;
        r2[0] = -1; r2[1] = 0;
        rot_mat3.push_back(r1);rot_mat3.push_back(r2); //270 degrees
    }

    
    for (int ii=0;ii<iterations;ii++)
    {
        //Iteration checks to 0
        iteration_checks = 0;
        //Make point choice
        SAW_point_choice = pivot_point(generator);
        //Make side choice
        side_choice = pivot_side(generator);
        //Make rotation choice (1,2,3 for 2D & 1-5 for 3D)
        rotation = direction(generator);
        SAWCheck = 0;
        //cout << "Pivot Point " << SAW_point_choice << "\n";
        //cout << "Rotation " << rotation << "\n";
        //cout << "Side " << side_choice << "\n";
        //Reset Halves
        front_coords = coordinates;
        back_coords = coordinates;

        //Front 
        front_coords.resize(SAW_point_choice);

        //Back
        reverse(back_coords.begin(),back_coords.end());
        back_coords.resize(n-SAW_point_choice);
        reverse(back_coords.begin(),back_coords.end());
        //cout << "Front "<<front_coords.size() <<"\n";
        //cout << "Back "<<back_coords.size() << "\n";
        //Set rotation matrix 
        if (rotation = 1)
        {
            rot_mat = rot_mat1;
        }
        else if (rotation = 2)
        {
            rot_mat = rot_mat2;
        }
        else if (rotation = 3)
        {
            rot_mat = rot_mat3;
        }
        
        //pivot_point_vector[0] = coordinates[SAW_point_choice];
        
        if (side_choice==1)
        {   
            front_coords = SubtractVectors(front_coords,coordinates[SAW_point_choice]);
            front_coords = MatMul(front_coords,rot_mat,front_coords,row);
            front_coords = AddVectors(front_coords,coordinates[SAW_point_choice]);
        }
        else
        {
            back_coords = SubtractVectors(back_coords,coordinates[SAW_point_choice]);
            back_coords = MatMul(back_coords,rot_mat,back_coords,row);
            back_coords = AddVectors(back_coords,coordinates[SAW_point_choice]);
        }
             
        //Concatenate
        front_coords.insert( front_coords.end(), back_coords.begin(), back_coords.end() );

        //Check SAW Validity
        
        checker.clear();
        for (int ii=0;ii<front_coords.size();ii++)
        {
            checker.insert(front_coords[ii]);
            iteration_checks += 1;
            if (checker.size() != ii+1)
            {
                front_coords = coordinates;

                SAWCheck = 1;
                break;
            }
        }
        checks_per_iteration[ii] = iteration_checks;
        if (SAWCheck == 0)
        {
           coordinates = front_coords; 
        }
        
    }
    return checks_per_iteration;
}

vector<int> PivotAlgorithmKennedy(int n, int iterations)
{
    vector<vector<int>> coordinates(n);
    vector<vector<int>> front_coords(n);
    vector<vector<int>> back_coords(n);
    vector<int>  directions(n,0);
    vector<int>  directionsfront(n,0);
    vector<int>  directionsback(n,0);
    vector<int>  directions_save(n,0);
    int SAWCheck;
    set<vector<int>> checker;
    //Set up random direction, 2*d-1 possible directions
    vector<int> row(d, 0);
    vector<int> reset_row(d, 0);
    //cout<< coordinates.size() << "\n";
    //List of Directions
    //Starting off, all 0s all up 
    //int pivot_radius;
    int SAW_point_choice, side_choice, rotation,direction_temp_hold;
    //Pivot Algorithm
    // 1) Random number for pivot point (1/n)
    // 2) Random number for pivot side (1/2)
    // 3) Random number for direction (1/2d)  
    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> direction(1,2*d-1);
    uniform_int_distribution<int> pivot_side(1,2);
    uniform_int_distribution<int> pivot_point(2,n-2);
    vector<vector<int>> rot_mat;
    vector<vector<int>> rot_mat1;
    vector<vector<int>> rot_mat2;
    vector<vector<int>> rot_mat3;
    vector<vector<int>> pivot_point_vector;

    //Add a counter to measure checks done per iteration 
    int iteration_checks{0};
    vector <int> checks_per_iteration(iterations);
    //Set up coord vector to be rod in x dim
    for (int kk=0;kk<n;kk++)
    {
        row[1] = kk;
        coordinates[kk] = row;
    }
    
    if(d == 2)
    {
        vector<int> r1(2); r1[0] = 0; r1[1] = -1;
        vector<int> r2(2); r2[0] = 1; r2[1] = 0;
        rot_mat1.push_back(r1);rot_mat1.push_back(r2); //90 degrees

        r1[0] = -1; r1[1] = 0;
        r2[0] = 0; r2[1] = -1;
        rot_mat2.push_back(r1);rot_mat2.push_back(r2); //180 degrees

        r1[0] = 0; r1[1] = 1;
        r2[0] = -1; r2[1] = 0;
        rot_mat3.push_back(r1);rot_mat3.push_back(r2); //270 degrees
    }
    
    //Kennedy Stuff
    int i_or_j{0}, m{1},step{1},j,i,counter{0};
    double dist;
    
    for (int ii=0;ii<iterations;ii++)
    {
        //Iteration checks to 0
        iteration_checks = 0;

        //Make point choice
        SAW_point_choice = pivot_point(generator);
        //Make side choice
        side_choice = pivot_side(generator);
        //Make rotation choice (1,2,3 for 2D & 1-5 for 3D)
        rotation = direction(generator);
        SAWCheck = 0;
        //cout << "Pivot Point " << SAW_point_choice << "\n";
        //cout << "Rotation " << rotation << "\n";
        //cout << "Side " << side_choice << "\n";
        //Reset Halves
        front_coords = coordinates;
        back_coords = coordinates;

        //Front 
        front_coords.resize(SAW_point_choice);

        //Back
        reverse(back_coords.begin(),back_coords.end());
        back_coords.resize(n-SAW_point_choice);
        reverse(back_coords.begin(),back_coords.end());
        //cout << "Front "<<front_coords.size() <<"\n";
        //cout << "Back "<<back_coords.size() << "\n";
        //Set rotation matrix 
        if (rotation = 1)
        {
            rot_mat = rot_mat1;
        }
        else if (rotation = 2)
        {
            rot_mat = rot_mat2;
        }
        else if (rotation = 3)
        {
            rot_mat = rot_mat3;
        }
        
        //pivot_point_vector[0] = coordinates[SAW_point_choice];
        
        if (side_choice==1)
        {   
            front_coords = SubtractVectors(front_coords,coordinates[SAW_point_choice]);
            front_coords = MatMul(front_coords,rot_mat,front_coords,row);
            front_coords = AddVectors(front_coords,coordinates[SAW_point_choice]);
        }
        else
        {
            back_coords = SubtractVectors(back_coords,coordinates[SAW_point_choice]);
            back_coords = MatMul(back_coords,rot_mat,back_coords,row);
            back_coords = AddVectors(back_coords,coordinates[SAW_point_choice]);
        }
             
        //Concatenate
        front_coords.insert( front_coords.end(), back_coords.begin(), back_coords.end() );

        //Check SAW Validity
        i_or_j = 1;
                
        j = SAW_point_choice -2;
        i = SAW_point_choice +2;
        counter = 0;

        while (true) 
            {
                iteration_checks += 1;
                m=n;
                //std::cout << "i: " << i << " j: " << j << "\n";
                if (i_or_j == 1) //comparing j to [SPC -- i]
                {
                    //Check row j against l to i 
                    for (int ii=SAW_point_choice+1;ii<i;ii++)
                    {
                        dist = eucl_dist(front_coords[j+1], front_coords[ii]);
                        //cout << dist << "\n";
                        if (dist == 0)
                        {
                            //std::cout << dist << "\n";
                            SAWCheck = 1;
                            break;
                        }
                        if (m>dist)
                        {
                            m=int(floor(dist));
                        }
                    }
                    j -= m;
                    if (j<-1)
                    {
                        j = -1;
                        if (i==n)
                        {
                            counter +=1;//std::cout << "Count " <<counter << "\n";
                        }
                    }
                    i_or_j = 2;
                }
                else  //comparing i to [j -- SPC]
                {
                    for (int ii=SAW_point_choice-1;ii>j;ii--)
                    {
                        dist = eucl_dist(front_coords[i-1], front_coords[ii]);
                        //cout << dist << "\n";
                        if (dist == 0)
                        {
                            //std::cout << dist << "\n";
                            SAWCheck = 1;
                            break;
                        }
                        if (m>dist)
                        {
                            m=int(floor(dist));
                        }
                    }
                    i += m;
                    if (i>n)
                    {
                        i = n;
                        if (j == -1)
                        {
                            counter += 1;//std::cout << "Count " <<counter << "\n";
                        }
                    }
                    i_or_j = 1;
                }
                checks_per_iteration[ii] = iteration_checks;
                if (SAWCheck==1)
                {
                    break;
                }
                if (counter >= 2)
                {
                    break;
                }
            }   
        if (SAWCheck == 0)
        {
           coordinates = front_coords; 
        }
    
    }
    
    return checks_per_iteration;
}
void PrintCoords(vector<vector<int>> coords)
{
    //Printing Coordinates Before Change
    for (int i = 0; i < coords.size(); i++) 
    { 
        for ( 
            auto it = coords[i].begin(); 
            it != coords[i].end(); it++) 
            cout << *it << ","; 
        cout << endl; 
    } 
    cout << "\n";
}

void SaveWalk(vector<vector<int>> coordinates)
{
    ofstream file;
    //naming file to store results in
    file.open("PivotSAWTest.csv");
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
    int n = 10;

    int iters = 5*n;
    int summation{0};
    int big{30};
    double std{0};
    double average{0.0};

    vector<vector<int>> coords(n);
    vector<int> iteration_vector(iters);
    ofstream file;
    //naming file to store results in
    //coords = PivotAlgorithmKennedy(n,iters);

    file.open("StepCounter4.csv");
    for (int jj=0;jj<big;jj++)
    {

        n = n + 10*jj;
        iters = 5*n;
        summation = 0;
        iteration_vector = PivotAlgorithmHash(n,iters);
        
        
        for (int ii=0;ii<iteration_vector.size();ii++)
        {
            summation += iteration_vector[ii];
        }
        average = double(summation)/double(iters);
        //need standard dev 
        summation = 0;
        for (int ii=0;ii<iteration_vector.size();ii++)
        {
            summation += ((double(iteration_vector[ii]) - average)*(double(iteration_vector[ii]) - average));
        }
        std = sqrt(double(summation)/double(iters));

        file << n << "," << average << "," << std <<  "\n";
    }
    file.close();

/*
    for (int kkk=0;kkk<big;kkk++)
    {
        coords = PivotAlgorithmKennedy(n,iters);
        //coords = PivotAlgorithmHash(n,iters);
    }
*/
    return 0;
}
