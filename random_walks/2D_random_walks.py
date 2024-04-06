# -*- coding: utf-8 -*-
"""
Created on Fri Sep 29 21:10:16 2023

@author: maxim
"""

import numpy as np
import time 
import matplotlib.pyplot as plt
import random

start = time.time()

"""

Step 1: Generate a random walk and access whether it is a SAW or not

    > (To do) determine what fraction of random walks for different n are and graph it
    > observed that as n increases, less SAW are generated
    > Why?
    > (To do) determine average length of random walk as n -> inf
    > should see that it is sqrt(n)
    > if the random walk is of length n, and on average it goes sqrt(n) from start
      then it takes up a grid of sqrt(n)*sqrt(n) (= n).
      This implies it will almost always overlap at some point

Step 2: Experiment with a hexagonal lattice

    > (To do) generate a random walk on a hexagonal lattice as opposed to a normal one
    > directions are now limited to 3 however need to take angles into account
    
    
    
        0   0          0   0
                
     0         0    0         0
                
        0   0          0   0
        
    > How many situations are there? 2
    > 1) Options: Up + left, right, down + left
    > 2) Options: Up + right, left, down + right 
    > Both scenarios lead to each other (1>2>1>2...)
    
    > Implementation 
    > 1st choice must be completely random
    > n = 1 > random choice between 1 or 2 > random selection of 3 moves from whichever case it chooses
    > n = 2 > has to follow the path chosen by n=1 > random selection of 3 moves 
    
"""

def DistanceCalc(x_start, x_end, y_start, y_end):
    return np.sqrt((x_end-x_start)**2+(y_end-y_start)**2)


def RandomWalk(n, title):
    
    """
    use n to determine length
    
    """
    coordinates = np.zeros([n,2])
    
    for i in range(1,n):
            
            step = random.randint(1,4)
            
            
            if step == 1:
                coordinates[i][0] = coordinates[i-1][0]
                coordinates[i][1] = coordinates[i-1][1] + 1
                
            elif step == 2:
                coordinates[i][0] = coordinates[i-1][0] + 1
                coordinates[i][1] = coordinates[i-1][1]
                
            elif step == 3:
                coordinates[i][0] = coordinates[i-1][0]
                coordinates[i][1] = coordinates[i-1][1] - 1
            
            elif step == 4:
                coordinates[i][0] = coordinates[i-1][0] - 1
                coordinates[i][1] = coordinates[i-1][1]
            
      
            """
            plt.plot(horizontal_steps,vertical_steps)
            plt.xlim(-np.sqrt(n)-10,np.sqrt(n)+10)
            plt.ylim(-np.sqrt(n)-10,np.sqrt(n)+10)
            plt.title(title)
            plt.show()
            """
    
   
    
    coordinates_tuple = list(set(map(tuple,list(coordinates))))
    #print("Length:", n)
    #print("Iteration:", title)
    SAW = 0
 
    #print(dist)
    if n == len(coordinates_tuple):
        #print("SAW")
        #title = str(title) + " SAW"
        SAW = 1
        """
        plt.plot(horizontal_steps,vertical_steps)
        plt.xlim(-np.sqrt(n)-10,np.sqrt(n)+10)
        plt.ylim(-np.sqrt(n)-10,np.sqrt(n)+10)
        plt.title(title)
        plt.show()
        """
    #else:
        #print("Not a SAW")
    
    
    return SAW
    
    
    

def RandomHexWalk(n,title):
   
    coordinates = np.zeros([n,2])
    #starting direction will choose either path 1 or 2 randomly
    starting_direction = random.randint(1,2)
    #print(starting_direction)
    x = 1/2
    y = np.sqrt(3)/2
    for i in range(1,n):
        if starting_direction == 1:
            
            step = random.randint(1,3)
            
            
            if step == 1: #up + left
                coordinates[i][0] = coordinates[i-1][0] - x
                coordinates[i][1] = coordinates[i-1][1] + y
                
            elif step == 2: #right
                coordinates[i][0] = coordinates[i-1][0] + 1
                coordinates[i][1] = coordinates[i-1][1]
                
            elif step == 3: #down + left
                coordinates[i][0] = coordinates[i-1][0] - x
                coordinates[i][1] = coordinates[i-1][1] - y
            
            starting_direction = 2
            
        elif starting_direction == 2:
            
            step = random.randint(1,3)
            
            if step == 1: #up + right
                coordinates[i][0] = coordinates[i-1][0] + x
                coordinates[i][1] = coordinates[i-1][1] + y
                
            elif step == 2: #left
                coordinates[i][0] = coordinates[i-1][0] - 1
                coordinates[i][1] = coordinates[i-1][1]
                
            elif step == 3: #down + right
                coordinates[i][0] = coordinates[i-1][0] + x
                coordinates[i][1] = coordinates[i-1][1] - y
            
            starting_direction = 1
        """
        plt.plot(horizontal_steps,vertical_steps)
        plt.xlim(-np.sqrt(n)-10,np.sqrt(n)+10)
        plt.ylim(-np.sqrt(n)-10,np.sqrt(n)+10)
        plt.title(title)
        plt.show()
        """
    coordinates_tuple = list(set(map(tuple,list(coordinates))))
    
    #print("Length:", n)
    #print("Iteration:", title)
    SAW = 0
  
    #print(dist)
    if n == len(coordinates_tuple):
        #print("SAW")
        #title = str(title) + " SAW"
        SAW = 1
        
         
        
    #else:
        #print("Not a SAW")
    """
    plt.plot(horizontal_steps,vertical_steps)
    plt.xlim(-np.sqrt(n)-10,np.sqrt(n)+10)
    plt.ylim(-np.sqrt(n)-10,np.sqrt(n)+10)
    plt.title(title)
    plt.show() 
    """
    return SAW    
    
    

    
SAW_count = {} 
SAW_hex_count = {}  
end_point = 20001
for j in range(1,31):
    #print("Walk length: ", j)
    temprwalk = 0
    temprhexwalk = 0

    
    for i in range(1,end_point):
        #Temp stores number of SAWs
        #distance stores the distance of each SAW
 
        temprwalk += RandomWalk(j, i)
        temprhexwalk += RandomHexWalk(j, i)     

    
    #Getting avg distance of all random walks
    #Counting SAWs for each length
    
    temprwalk = temprwalk/end_point *100
    SAW_count[(j)] = temprwalk
     
    temprhexwalk = temprhexwalk/end_point *100
    SAW_hex_count[(j)] = temprhexwalk


keys_SAW_percent = list(SAW_count.keys())
values_SAW_percent = list(SAW_count.values())
keys_SAW_percent_hex = list(SAW_hex_count.keys())
values_SAW_percent_hex = list(SAW_hex_count.values())

plt.plot(keys_SAW_percent,values_SAW_percent, color = "red",label="2D Square Lattice")
plt.plot(keys_SAW_percent_hex,values_SAW_percent_hex, color = "blue",label="2D Hexagonal Lattice")
#plt.title("Percent of Random Walk of Length n being an SAW (Python)")
plt.xlabel("Length (n)")
plt.ylabel("Percent (%)")
plt.legend(fontsize="11", loc="upper right")
resolution_value = 1000
save_name = "RWalkSuccessRate2DPython.pdf"
plt.savefig(save_name, format="pdf", dpi=resolution_value)
plt.show()


end = time.time()
total_time = end - start 
print("Time taken: ", round(total_time, 2))
    