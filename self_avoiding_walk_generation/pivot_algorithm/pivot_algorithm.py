# -*- coding: utf-8 -*-
"""
Pivot Algorithm 
"""

import numpy as np
import matplotlib.pyplot as plt
import random
import progressbar
import math
import time
from statsmodels.tsa.stattools import acf
from scipy.spatial.distance import cdist
#Save if need to reinstall
#pip install progressbar2 requests

def SAWChecker(coordinates, expected_length):
    
    coordinates_set = list(set(map(tuple,list(coordinates))))
    SAW = 0
    if len(coordinates_set) == expected_length:
        SAW = 1
    
    return SAW 

"""

Pivot Algorithm

1) Initialise a SAW of desired length (n)
    > (Usually just a straight line for simplicity)
2) Choose a point on the SAW
    > Choose point to break the SAW  ----- > --- --
    > Choose side of line --- or --
3) Carry out Rotation (Some symmetry operation)
    > Take the selected side, turn in random direction  

Inputs: 
n - length
d - either 2 or 3 dimensions
pivot_iterations - number of times we wish to attempt a pivot    
"""

def Pivot_algorithm(d,n,pivot_iterations):
    #z = 2*d
    #for now work with 2 and 3D 
   
    widgets = [
        ' [', progressbar.Timer(), '] ',
        progressbar.GranularBar(), ' ',
        progressbar.Percentage(),    
    ]
    #Initialise straight line in x dimension (1st Direction for dims higher than 2)
    coordinates = np.zeros([n,d], dtype=int)
    coordinates[:, 0] = np.arange(0, n)
    
    #print(coordinates)
    #Save an initial version of the coordinates to be used as a save for non self avoiding cases
    
    with progressbar.ProgressBar(max_value=pivot_iterations, widgets=widgets) as bar:
        
        for i in range(pivot_iterations):
            bar.update(i)
            #Random vertex to separate the SAW chooses random point 1 - n
            SAW_point_choice = random.randint(0,n-1)
            #chooses which side to act on
            side_choice = random.randint(1,2)
            #Save a copy of the coordinates in case it needs to be reset for an invalid move
            coordinates_save = coordinates.copy()
            #Use side choice to determine which side should be affected
            if side_choice == 1:
                keep_half = coordinates[0:SAW_point_choice+1]
                altered_half = coordinates[SAW_point_choice+1:]
            else:
                keep_half = coordinates[SAW_point_choice:]
                altered_half = coordinates[0:SAW_point_choice]
                    
            #Now want to rotate whats known as altered_half
            #Depending on dimension, we need to define various directions 
            if d == 2:
                #stores the 3 different directions for 2D
                rotation_matrices = np.array([[[0,1],[-1,0]],
                                              [[-1,0],[0,-1]],
                                              [[0,-1],[1,0]]])
                rotation_matrix = random.choice(rotation_matrices)
            if d == 3:
                #Rotation matrices more complex for 3D
                rotation_matrices = np.array([[[1,0,0],[0,0,-1],[0,1,0]],
                                              [[1,0,0],[0,-1,0],[0,0,-1]],
                                              [[1,0,0],[0,0,1],[0,-1,0]],
                                              [[0,0,1],[0,1,0],[-1,0,0]],
                                              [[-1,0,0],[0,1,0],[0,0,-1]],
                                              [[0,0,-1],[0,1,0],[-1,0,0]],
                                              [[0,-1,0],[1,0,0],[0,0,1]],
                                              [[-1,0,0],[0,-1,0],[0,0,1]],
                                              [[0,1,0],[-1,0,0],[0,0,1]]])
                rotation_matrix = random.choice(rotation_matrices)
                
            new_half = np.dot(altered_half-coordinates[SAW_point_choice], rotation_matrix.T).astype(int) + coordinates[SAW_point_choice]
            #new_half = altered_half.copy()
                
                
            
        
            #Apply the change
                
            if side_choice == 1:
                    coordinates = np.concatenate((keep_half, new_half), axis =0) 
            else:
                    coordinates = np.concatenate((new_half, keep_half),axis=0) 
            #Set checker version
            SAW = SAWChecker(coordinates, n)
            
            #Bring it back to origin
            coordinates = (coordinates - np.int_(np.mean(coordinates,axis=0)))
    

    #Plotting
    if d == 2:
            xs = [x[0] for x in coordinates]
            ys = [x[1] for x in coordinates]
            plt.plot(xs, ys, color = "purple")
            #plt.title("Pivot Algorithm, Steps: %i, Iterations: %i" %(n,pivot_iterations))
            resolution_value = 1200
            #plt.axis('equal')
            
            save_name = "PivotAlgorithmL" + str(n) + "Save.pdf"
            plt.savefig(save_name, format="pdf", dpi=resolution_value)
            plt.show()
        
    elif d == 3:
                
            xs = [x[0] for x in coordinates]
            ys = [x[1] for x in coordinates]
            zs = [x[2] for x in coordinates]
            
            
            ax = plt.figure().add_subplot(projection='3d')
            ax.plot(xs, ys, zs,color = "purple")
            #ax.set_title("Pivot Algorithm 3D, Steps: %i" %(n))
            resolution_value = 1200
            #ax.set_aspect('equal')

            save_name = "PivotAlgorithmL" + str(n) + "(2D).pdf"
            plt.savefig(save_name, format="pdf", dpi=resolution_value)
            plt.show()
            
    return coordinates
            
            
"""
d = 2
n = 1000
iterations = 20*n
coords = Pivot_algorithm(d,n,iterations)
"""

d = 2
n = 10000
iterations = 5*n
times_pivot = []
for i in range(1):
    start = time.time()
    
    coords = Pivot_algorithm(d, n, iterations)
    
    end = time.time()
    
    times_pivot.append(end-start)

#coords = Pivot_algorithm(d, n, iterations, 2)

print("")
avg_time = sum(times_pivot)/len(times_pivot)
print("Pivot Avg Time: ", avg_time)

