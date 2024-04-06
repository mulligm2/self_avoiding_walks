# -*- coding: utf-8 -*-
"""
LERWs
"""
import numpy as np
import time 
import matplotlib.pyplot as plt
import random
import progressbar

def SAWChecker(coordinates, expected_length):
    
    coordinates_set = list(set(map(tuple,list(coordinates))))
    
    SAW = 0
    if len(coordinates_set) == expected_length:
        SAW = 1
    
    return SAW 


def LERW(n,d,limit):
    
    break_point = 0
    coordinates = []
    coordinates_NONSAW = []
    row = np.zeros(d)
    coordinates.append(list(row))
    length = 1
    while(length < n):
            
        if break_point < limit:
            break_point += 1
        else:
            #print(length)
            break
        
        length = len(coordinates)
        step = random.randint(1,2*d)
  
        if step%2 == 0:
            index = int((step/2)-1)
            #print(index)
            row[index] +=1
            
            
        elif step%2 != 0:
            step += 1
            index = int((step/2)-1)
            #print(index)
            row[index] -=1
        #print(row)
        coordinates.append(list(row))
        coordinates_NONSAW.append(list(row))
        
        
        length += 1
        if (SAWChecker(coordinates, length)) == 0:
            #print(coordinates)
            #print(row)
            coordinates.pop()
            for jj in range(1,length):
                #print(jj)
                #print(coordinates[-1])
            
                if coordinates[-1]!=list(row):
                    coordinates.pop()
                else: 
                    break
            
    
    if d == 1:
        #print(SAWChecker(coordinates, length))
        x_values1 = ([float(row[0]) for row in coordinates])
        y_values1 = ([float(row[1]) for row in coordinates])
        #print(SAWChecker(coordinates_NONSAW, length))
        x_values2 = ([float(row[0]) for row in coordinates_NONSAW])
        y_values2 = ([float(row[1]) for row in coordinates_NONSAW])
        
       
        plt.plot(x_values2,y_values2,color="r")
        plt.plot(x_values1,y_values1,color="b")
    
        #plt.title(title)
        resolution_value = 1000
        
        save_name = "LERW" + str(length) + ".pdf"
        plt.savefig(save_name, format="pdf", dpi=resolution_value)
        plt.show()  
        
    elif d == 3:
        
        xs = [x[0] for x in coordinates]
        ys = [x[1] for x in coordinates]
        zs = [x[2] for x in coordinates]
        xs1 = [x[0] for x in coordinates_NONSAW]
        ys1 = [x[1] for x in coordinates_NONSAW]
        zs1 = [x[2] for x in coordinates_NONSAW]
        
        ax = plt.figure().add_subplot(projection='3d')
        ax.plot(xs1, ys1, zs1,color = "r")
        ax.plot(xs, ys, zs,color = "b")
        resolution_value = 1200
        
        save_name = "TwoMoveBerretti-Sokal" + str(length) + ".pdf"
        #plt.savefig(save_name, format="pdf", dpi=resolution_value)
        
        plt.show()
    #print(break_point)
    print("LERW Length")
    LERW_Length = len(coordinates)
    print(LERW_Length)
    print("RW Length")
    RW_Length = len(coordinates_NONSAW)
    print(RW_Length)
    return LERW_Length, RW_Length
    


n = 10000
limit = 5e5
d=2
LERW_lens = []
RW_lens = []
length_LERW = 0
length_RW = 0
counter = 0
max_val = 10

x, y = LERW(n,d,limit)

"""
widgets = [
        ' [', progressbar.Timer(), '] ',
        progressbar.GranularBar(), ' ',
        progressbar.Percentage(),    
    ]
with progressbar.ProgressBar(max_value=max_val, widgets=widgets) as bar:
    
    for i in range(max_val):
        bar.update(i)
        limit = n**3
        counter = 0
        length_RW = 0
        while counter < 10:
            x, y = LERW(n,d,limit)
            if x == n:
                length_RW += y
                counter += 1
        
        length_RW = length_RW/counter 
        LERW_lens.append(n)
        RW_lens.append(length_RW)
        n += 300;

plt.plot(LERW_lens,RW_lens)
"""

