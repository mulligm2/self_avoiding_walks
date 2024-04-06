# -*- coding: utf-8 -*-
"""
C code 2D/3D SAW Plotting
2/3 Move Berretti-Sokal
Pivot Algorithm

"""


import csv
import matplotlib.pyplot as plt


#Set variable to point to experiment data csv file with walk coordinates  
input_data_file = "..\input_data\example_1.csv"
file = open(input_data_file, "r")
saw = list(csv.reader(file, delimiter=","))
file.close()


#print(square_data)
# Number of rows relates to number of column outputs
# Split data into separate lists for graphing
def threeD(data, n):
        
    x_values = ([float(row[0]) for row in data])
    y_values = ([float(row[1]) for row in data])
    z_values = ([float(row[2]) for row in data])

    ax = plt.figure().add_subplot(projection='3d')
    ax.plot(x_values, y_values, z_values,color = "purple")
    resolution_value = 1200
    save_name =  "temp_walk_name.pdf"
    #plt.savefig(save_name, format="pdf", dpi=resolution_value)
    plt.show()

def twoD(data, n):
        
    x_values = ([float(row[0]) for row in data])
    y_values = ([float(row[1]) for row in data])

    plt.plot(x_values, y_values, color = "purple")
    resolution_value = 1200
    save_name =  "temp_walk_name.pdf"
    #plt.savefig(save_name, format="pdf", dpi=resolution_value)
    plt.show()
    

twoD(saw, 50000)
#threeD(saw, 50000)
