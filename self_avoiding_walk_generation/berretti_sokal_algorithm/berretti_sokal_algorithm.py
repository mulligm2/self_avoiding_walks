
"""
Berretti-Sokal algorithm
for d-dim lattice

Takes input variables 
* n : maximum number of iterations before the algorithm stops
* desired_length : the desired length of the SAW
* x : fugacity term should be set between 0 and 1
* d : dimension of walk
* z : coordination number should be set to 2d

TwoMoveBerrettiSokal employs 2 move method while ThreeMoveBerrettiSokal employs 3 move method
"""

import numpy as np
import matplotlib.pyplot as plt
import time
import random
from statsmodels.tsa.stattools import acf

import progressbar


def Pplus(x,z):
    return min(1,z*x/(1+x*z))

def Pminus(x,z):
    return min(1,1/(1+x*z))

def SAWChecker(coordinates, expected_length):
    
    coordinates_set = list(set(map(tuple,list(coordinates))))
    SAW = 0
    if len(coordinates_set) == expected_length:
        SAW = 1
    
    return SAW 

def distance_calc(x1,x2,y1,y2,dim):
    if dim == 2:
        return np.sqrt((x2)**2+(y2)**2)
  
    
    

def neutral(x,z, save_all_directions, prev_directions_list, row, coordinates, length, next_atmosphere):
    #print("Neutral")

    #save old values in case the new walk isn't self avoiding
    
    old_prev_directions_list = prev_directions_list.copy()
    old_row = row.copy()
    old_coordinates = coordinates.copy()
    

    #print(coordinates)
    temp_row = row.copy()
    new_direction = prev_directions_list[-1] #Where it went 
    if len(prev_directions_list) > 2:
        old_direction = prev_directions_list[-2] #Where it came from
        
    
    step = new_direction
    #print(prev_directions_list)
    prev_directions_list.pop()
        
    if step%2 == 0:
        index = int((step/2)-1)
        temp_row[index] = row[index] + 1 
    elif step%2 != 0: 
        step += 1
        index = int((step/2)-1)
        temp_row[index] = row[index] - 1
                
    #print(coordinates)
    coordinates.pop()
    length -= 1
    directions = save_all_directions.copy()       
    if len(prev_directions_list) > 1:
        if old_direction%2 == 0:
             removal = old_direction - 1
  
        elif old_direction%2 != 0:
             removal = old_direction + 1
             
       
        directions.remove(removal)
        directions.remove(new_direction)
    else:
        directions.remove(new_direction)
    step = int(random.choice(directions))
     
    prev_directions_list.append(step)
    
    #Walk in the direction of step
    if step%2 == 0:
             index = int((step/2)-1)
             temp_row[index] = row[index] - 1
            
    elif step%2 != 0:
             step += 1
             index = int((step/2)-1)
             temp_row[index] = row[index] + 1
                
    #Append the change to a copy of coordinate list 
    coordinate_copy = coordinates.copy()
    coordinate_copy.append(list(temp_row))
    length += 1
                
    is_saw = SAWChecker(coordinate_copy, length)
    
    if is_saw == 1:
   
        row = temp_row.copy()
        coordinates.append(list(temp_row))
   
        return prev_directions_list, row, coordinates, length 
    
    elif is_saw == 0:
        if next_atmosphere == 1:
  
            return PositiveStep(x, z, save_all_directions, old_prev_directions_list, old_row, old_coordinates, length)
        elif next_atmosphere == 2:
       
            return NegativeStep(x, z, save_all_directions, old_prev_directions_list, old_row, old_coordinates, length)

def PositiveStep(x,z, save_all_directions, prev_directions_list, row, coordinates, length):
     #print("Positive Step")
     
     positive_fifty_fifty = random.randint(1,2)
     
     
     if positive_fifty_fifty == 1:
         return neutral(x,z, save_all_directions, prev_directions_list, row, coordinates, length,2)
     
     temp_row = row.copy()
     prev_direction = prev_directions_list[-1]
     acc = Pplus(x, z)
     if acc < 1:
         #generate random number [0,1)
         r = np.random.rand()
         if r > acc:
             # Reject the move
             #print("failed")
             return prev_directions_list, row, coordinates, length
     #Accept the move 
                
     #Reset all available directions
     directions = save_all_directions.copy()
                
     if prev_direction%2 == 0:
             removal = prev_direction - 1
  
     elif prev_direction%2 != 0:
             removal = prev_direction + 1
                
     directions.remove(removal)
     step = int(random.choice(directions))
     
     prev_direction = step #save previous step
     prev_directions_list.append(step)
                
     #Walk in the direction of step
                
     if step%2 == 0:
             index = int((step/2)-1)
             temp_row[index] = row[index] - 1
            
     elif step%2 != 0:
             step += 1
             index = int((step/2)-1)
             temp_row[index] = row[index] + 1
            

     #Append the change to a copy of coordinate list 
     coordinate_copy = coordinates.copy()
     coordinate_copy.append(list(temp_row))
     length += 1
                
     is_saw = SAWChecker(coordinate_copy, length)
     
     if is_saw == 0:
             #print("Not SAW")       
             #step back and decrease length
             length -= 1
             prev_directions_list.pop()
             temp_row = row.copy()
             return prev_directions_list, row, coordinates, length
     #print(coordinate_copy) 
              
     #set the row to be the proposed move and continue
     row = temp_row.copy()
     coordinates.append(list(row))
     
     
     return prev_directions_list, row, coordinates, length
                
    
def NegativeStep(x,z, save_all_directions, prev_directions_list, row, coordinates, length):
    #print("Negative Step")
    
    
    negative_fifty_fifty = random.randint(1,2)
    
    if negative_fifty_fifty == 1:
         return neutral(x,z, save_all_directions, prev_directions_list, row, coordinates, length, 1)
    
    acc = Pminus(x, z)
    if acc < 1:
        r = np.random.rand()
        if r > acc:
        # Reject the move
            #print("failed")
            return prev_directions_list, row, coordinates, length
                    
    #Accept the move 
    #return back to previous coords
    step = prev_directions_list[-1]
    prev_directions_list.pop()
        
    if step%2 == 0:
        index = int((step/2)-1)
        row[index] = row[index] + 1    
    elif step%2 != 0: 
        step += 1
        index = int((step/2)-1)
        row[index] = row[index] - 1
                
    coordinates.pop()
    length -= 1
   
    return prev_directions_list, row, coordinates, length


def TwoMoveBerrettiSokal(x,z,d,n,desired_length):
    """
    2 Move Berretti Sokal algorithm:
        1) choose move
        2) Positive > take a step in any of the z-1 directions with probability
           P+, if it generates a valid SAW keep, if not discard 
        3) Negative > remove previous edge with probability P- 
    
    Need to account for SAW validity
    Need to reject the move if it violates SAW rule
    """
    coordinates = []
    row = np.zeros(d, dtype = int)
    temp_row = np.zeros(d, dtype = int)
    prev_direction = 0
    directions = []
    prev_directions_list = []
    
    length = 1
    
    for j in range(1,z+1):
        directions.append(j)
        
    
    save_all_directions = directions.copy()
    coordinates.append(list(row))
    iterations = 0
    
    
    while length != desired_length:
            
            if iterations == n:
                break
            else:
                iterations += 1
                
            if np.count_nonzero(row) == 0:
                #print("Case 1")
            
                #If at origin, need to perform a positive step
                
                step = random.randint(1,z)
            
                #save previous step
                prev_direction = step
                prev_directions_list.append(step)
                
                #make move 
                if step%2 == 0:
                    index = int((step/2)-1)
                    row[index] = row[index] - 1

            
                elif step%2 != 0:
                    step += 1
                    index = int((step/2)-1)
     
                    row[index] = row[index] + 1
            
                coordinates.append(list(row))
                length += 1 
                temp_row = row.copy()
                #print(row)
    
            else:
            
                #otherwise we allow it to make either a positive or negative move
                acc = Pplus(x, z)
                    
                if acc < 1:
                    #generate random number [0,1)
                    r = np.random.rand()
                    if r > acc:
                        move_choice = 2
                    else:
                        move_choice = 1
                
                
                    
                if move_choice == 1:
                
                        
                        #Reset all available directions
                    directions = save_all_directions.copy()
                        
                        #Next remove the previous direction
                        #prev_direction = prev_directions_list[-1]
                        
                    if prev_direction%2 == 0:
                        removal = prev_direction - 1
                            
                    elif prev_direction%2 != 0:
                        removal = prev_direction + 1
                
                    directions.remove(removal)
                    step = int(random.choice(directions))
                    #print(step)
                    #save previous step
                    prev_direction = step
                    prev_directions_list.append(step)
                    
                    #Walk in the direction of step
                
                    if step%2 == 0:
                        index = int((step/2)-1)
                        temp_row[index] = row[index] - 1
                        
                    elif step%2 != 0:
                        step += 1
                        index = int((step/2)-1)
                        temp_row[index] = row[index] + 1
                
                #Append the change to a copy of coordinate list 
                    coordinate_copy = coordinates.copy()
                    coordinate_copy.append(list(temp_row))
                    length += 1
                    
                    is_saw = SAWChecker(coordinate_copy, length)
                    #print(coordinates)
                    #print(len(coordinates))
                    #print(length)
                    
                    #print(is_saw)
                    #if it is not a SAW 
                    if is_saw == 0:
                    
                    #step back and decrease length
                        length -= 1
                        prev_directions_list.pop()
                        prev_direction = prev_directions_list[-1]
                        temp_row = row.copy()
                        continue
                
                #set the row to be the proposed move and continue
                    row = temp_row.copy()
                    coordinates.append(list(temp_row))
                             
                            
                elif move_choice == 2:
                    
                    #return back to previous coords
                    step = prev_directions_list[-1]
                    prev_directions_list.pop()
                    if prev_directions_list != []:
                        prev_direction = prev_directions_list[-1]
                
                    if step%2 == 0:
                        index = int((step/2)-1)
                        row[index] = row[index] + 1

            
                    elif step%2 != 0:
                        step += 1
                        index = int((step/2)-1)
                        row[index] = row[index] - 1
                
                    coordinates.pop()
                    length -= 1
                    temp_row = row.copy()
                #print(row)
        #print(prev_directions_list)  
  
    #print(coordinates)
    if d == 2:
        xs = [x[0] for x in coordinates]
        ys = [x[1] for x in coordinates]
        
        title = "Two Move Berretti-Sokal " + str(length) + "-step, x: " + str(x)
        plt.plot(xs, ys, color = "purple")
        #plt.title(title)
        resolution_value = 1200
        
        save_name = "TwoMoveBerretti-Sokal" + str(length) + ".pdf"
        #plt.savefig(save_name, format="pdf", dpi=resolution_value)
        plt.show()  
        
    elif d == 3:
        
        xs = [x[0] for x in coordinates]
        ys = [x[1] for x in coordinates]
        zs = [x[2] for x in coordinates]
   
        
        ax = plt.figure().add_subplot(projection='3d')
        ax.plot(xs, ys, zs,color = "purple")

        title = "Two Move Length: " + str(length) 
        ax.set_title(title)
        plt.show()
        
    #print(length)
    return length, np.array(coordinates)

def ThreeMoveBerrettiSokal(x,z,d,n,desired_length):
    
    
    coordinates = []
    row = np.zeros(d, dtype = int)
    directions = []
    prev_directions_list = []
    prev_directions_list.append(0)
    length = 1
    
    for j in range(1,z+1):
        directions.append(j)
        
    
    save_all_directions = directions.copy()
    coordinates.append(list(row))
    iterations = 0
    while length != desired_length:
        
        if iterations == n:
            break
        else:
            iterations += 1
 
        if np.count_nonzero(row) == 0:
            #print("Case 1")
            
            #If at origin, need to perform a positive step
            acc = Pplus(x, z)
            if acc < 1:
                r = np.random.rand()
                if r > acc:
                    # Reject the move
                    #print("failed")
                    continue
            #Accept the move 
            step = random.randint(1,z)
            
            #save previous step
            prev_directions_list.append(step)
            
            #make move 
            if step%2 == 0:
                index = int((step/2)-1)
                row[index] = row[index] - 1

            elif step%2 != 0:
                step += 1
                index = int((step/2)-1)
     
                row[index] = row[index] + 1
            
            coordinates.append(list(row))
            length += 1 
            
            #print(row)
            
        else:
            """
            Three Move Algorithm 
            Choose Positive or Negative
            Choose P/N or Neutral
            
            Flow chart:
                
                                             Positive
                            Positive 50 50 / 
                                           \          /  positive 50 50 ...
            Initial 50 50                    Neutral  
                                           /          \  negative 50 50 ...  
                            Negative 50 50 \
                                             Negative
            
            """
            initial_fifty_fifty = random.randint(1,2)
            
            if initial_fifty_fifty == 1:
                #positive move
                prev_directions_list, row, coordinates, length = PositiveStep(x, z, save_all_directions, prev_directions_list, row, coordinates, length)
          
            
            elif initial_fifty_fifty == 2:
                #negative move
                prev_directions_list, row, coordinates, length = NegativeStep(x, z, save_all_directions, prev_directions_list, row, coordinates, length)
           
    #Want to calculate distance away from the origin
    distances_from_origin = []
    if (d == 1):
        for i in range(len(coordinates)):
            distance = distance_calc(0, coordinates[i][0], 0, coordinates[i][1], 0,0,0,0,d)
            distances_from_origin.append(distance)
    
    if (d == 3):
        for i in range(len(coordinates)):
            distance = distance_calc(0, coordinates[i][0], 0, coordinates[i][1], 0,coordinates[i][2],0,0,d)
            distances_from_origin.append(distance)
    
    if (d == 4):
        for i in range(len(coordinates)):
            distance = distance_calc(0, coordinates[i][0], 0, coordinates[i][1], 0,coordinates[i][2],0,coordinates[i][3],d)
            distances_from_origin.append(distance)
    
    
    #print(coordinates)
    if d == 2:
        xs = [x[0] for x in coordinates]
        ys = [x[1] for x in coordinates]
        
        title = "Two Move Berretti-Sokal " + str(length) + "-step, x: " + str(x)
        plt.plot(xs, ys, color = "purple")
        #plt.title(title)
        resolution_value = 1200
        
        save_name = "ThreeMoveBerretti-Sokal" + str(length) + ".pdf"
        #plt.savefig(save_name, format="pdf", dpi=resolution_value)
        plt.show()  
        
    elif d == 3:
        
        xs = [x[0] for x in coordinates]
        ys = [x[1] for x in coordinates]
        zs = [x[2] for x in coordinates]
   
        
        ax = plt.figure().add_subplot(projection='3d')
        ax.plot(xs, ys, zs,color = "purple")

        title = "Two Move Length: " + str(length) 
        ax.set_title(title)
        plt.show()
        
    #print(length)
    return length, np.array(coordinates)

x = 0.37905
d = 2   
z = 2*d
#Setting limit to a high value
#To be used if a SAW of unspecified length is desired and the longest possible is 
limit = 30000
n = 1000 
max_iter = 50*n


length, coordinates_two_move = TwoMoveBerrettiSokal(x, z, d, max_iter, n)
 

