# The Self-Avoiding Walk Model in 2D and 3D 

The behaviour of random walks, loop erased random walks (LERWs) and self-avoiding walks (SAWs) were investigated for this final year theoretical physics bachelor project.

An n-step self-avoiding walk, $w$, on $\mathbb{Z}^d$, a hypercubic lattice, is defined as a sequence of points or sites $(w(0),w(1),w(2),...,w(n))$, where $w(i) = w(j)$ iff $i=j$.

The self avoidance of random walks was investigated first in 2D for the square and hexagonal lattice, following which, the n-D hypercubic lattice was studied. 

The difference between the LERW model and SAW model were looked at. Both generate a walk which is self-avoiding however both are slightly different models.

The efficiency of the Berretti-Sokal algorithm, the three move variant and the pivot algorithm were investigated. The Kennedy version of the pivot algorithm was also implemented.
A new algorithm was developed, acting as a combination of the 3 algorithms, named as the pivot-Berretti-Sokal algorithm.

The critical phenomena associated with weighting straight edges was studied. The effects of weighting curved edges was looked at as an approximate version of the self-attracting self-avoiding walk model.

Most files come with Python and C++ counterparts as an additional aim to look at the decreased run time of the C++ algorithms.

## 1. Examples of Input Data 
input_data contains 2 example data files:


 > example_1.csv
  - example data format for a self avoiding walk of length 500,000 steps

 > example_2.csv
  - example data format for mean square displacement data  


## 2. Random Walks

random_walks folder contains code used to study self avoidance of random walks: 

> 2D_random_walks.py/2D_random_walks.cpp 
- measures the percent of random walks which are self avoiding in 2D while varying length
- works for square and hexagonal lattice


> n_dim_random_walks.py/n_dim_random_walks.cpp
- measures the percent of random walks of fixed length which are self avoiding while varying dimension

</br>

loop_erased_random_walks folder corresponds to code used to generate and study LERWs:

> loop_erased_random_walks.py
* generates a loop erased random walk
  
> loop_erased_random_walks.cpp
* computes the mean square displacement used to calculate the length scaling coefficient


## 3. Self Avoiding Walk Generation 
A key concept looked at in this project was the generation of self avoiding walks. 

#### Berretti Sokal Algorithm
berretti_sokal_algorithm contains the code used to study the Berretti-Sokal algorithms. 
The Berretti-Sokal algorithm incorporates a fugacity term which determines the probability of moving forwards or removing an edge.

> berretti_sokal_algorithm.py
* Generates a SAW of a given length using either the two or three move Berretti-Sokal algorithm. 
* Includes a maximum number of iterations to account for possibility of crashing into itself.


> two_move_berretti_sokal.cpp
* Explores the effect of varying the fugacity (x), measuring the average length of the generated walks for different values of x.
* Save input should be set to 0 when varying the fugacity.


> three_move_berretti_sokal.cpp
* Generates a SAW using the three move Berretti-Sokal algorithm. Inputs are the same as the python version. 
* A csv file will be generated to store the walk produced by the algorithm. 
* The function also returns a vector containing the length of the walk at each iteration of the algorithm which can be looked at. 


> pivot_berretti_sokal_algorithm.cpp
* Generates a SAW of a given length, again inputting a maximum number of iterations, fugacity (x), dimension (d) and coordination number (z). 
* PBSAlgorithm function generates the walk as a vector of directions of each edge
* GenerateWalk function takes the direction vector and converts it into a set of coordinates
* SaveWalk stores the walk in a csv file for plotting

#### Pivot Algorithm
pivot_algorithm folder contains code used to perform the pivot algorithm: 

> pivot_algorithm.py
* generates a SAW in either 2D or 3D of length n 

inputs
* d : dimension
* n : length of SAW
* iterations : number of pivots to carry out


> pivot_algorithm_v1.cpp
* carries out the pivot algorithm using a direction vector 


> pivot_algorithm_v2.cpp
* carries out the pivot algorithm using matrix multiplication.
* This implementation also includes the Kennedy version of the pivot algorithm. 
* This code is used to look at the average number of points checked by both algorithms and generates a csv file to store the results.


> weighted_pivot_algorithm.cpp
* Explores the effect of weighting straight or curved edges in the self avoiding walk. 
* Setting the weighting to be positive favours straighter edges while negative corresponds to curves.
</br>
This weighting can be interpretted as the temperature, where negative weighting should be taken as an absolute value. 
Length of walk and dimension are set as constants. 



## 4. Critical Exponents
critical_exponents folder contains code used for generating data required to calculate the connective constant and the length scaling coefficient.
Also includes a Python file used to carry out linear regression in order to compute the two critical exponents. 


> connective_constant.cpp 
- performs exact enumeration using pivot algorithm for a particular n 
- values for particular n can be plotted for linear regression and a value as n $\to$ $\infty$ can be extrapolated


> length_scaling_coeff.cpp
- computes mean square displacement for a range of values of n 
- values stored to a csv file and linear regression can be performed on the logarithms to calculate the length scaling coefficient
- can also be carried out for different weightings 


> critical_exp_linear_regression.py
- performs linear regression on afformentioned data sets
- length scaling coefficient given as half of the slope of the line
- connective constant found by using equation of the line to find value of c_n as n goes to infinity


## 5. SAW Plotting
self_avoiding_walks_plotting contains code used to plot the walks generated by C++ algorithms 
Requires a csv file in the format of input_data_example_1
