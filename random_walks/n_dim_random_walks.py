
"""
n dimension Random Walk 
"""

import numpy as np
import time 
import matplotlib.pyplot as plt
import random

start = time.time()

"""

Attempt to generate a 3D random walk and check if it is an SAW

"""


def RandomWalk(n, d):
    
    """
    use n to determine length
    
    """
    coordinates = np.zeros([n,d])
    for i in range(1,n):
            
        
        step = random.randint(1,2*d)
  
        if step%2 == 0:
            index = int((step/2)-1)
          
            coordinates[i][index] = coordinates[i-1][index] - 1
            for j in range(d):
                if j != index:
                    coordinates[i][j] = coordinates[i-1][j]
            
        elif step%2 != 0:
            step += 1
            index = int((step/2)-1)
     
            coordinates[i][index] = coordinates[i-1][index] + 1
            for j in range(d):
                if j != index:
                    coordinates[i][j] = coordinates[i-1][j]
            
   
    
    coordinates_tuple = list(set(map(tuple,list(coordinates))))
    SAW = 0
    #print(coordinates)
    #print(dist)
    if n == len(coordinates_tuple):
     
        SAW = 1

    return SAW

SAW_count = {} 
end_point = 10001
d = 30
for j in range(2,51):
    #j = length of walk
    rwalk = 0
    for i in range(1,end_point):
        rwalk += RandomWalk(40, j)
    
    rwalk = rwalk/end_point *100    
    SAW_count[(j)] = rwalk
        
        
keys_SAW_percent = list(SAW_count.keys())
values_SAW_percent = list(SAW_count.values())        
label = (str(d) + " dimensional lattice")
title = ("Percent of Random Walk of Length n being an SAW in " + str(d) + "D")
plt.plot(keys_SAW_percent,values_SAW_percent, color = "purple",label=label)
plt.axhline(y = 0, color = 'r', linestyle = '--') 
plt.title(title)
plt.xlabel("Length (n)")
plt.ylabel("Percent (%)")
plt.legend(loc="upper right")
plt.show()        
        
   
        
        
end = time.time()
total_time = end - start 
print("Time taken: ", round(total_time, 2))