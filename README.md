traveling-salesman
==================

##Traveling Salesman Problem C++ Implementation##

###Usage###
Input files must be have one city per line identified by a unique number, followed by the Euclidean coordinates. Here is an example:

```
0 200 800
1 3600 2300
2 3100 3300
3 4700 5750
4 5400 5750
5 5608 7103
6 4493 7102
7 3600 6950
```
Output will be to mysolution.txt. The first line is the total distance traveled, followed by the order of visits:
```
18877
0
1
2
3
4
5
6
7
```
Compile the program with ```make``` then run it with the command ```./tsp [input_file]```

###Problem Description###
The traveling salesman problem was first formulated in 1930 [1]. The goal of the problem is, given a
list of cities and their locations, to find the shortest possible path that passes through each city exactly
once and ends at the starting city. There are two primary forms of the problem. One is the graph-based
version, where the cities are given within the framework of a weighted graph that dictates the
connections between cities so that the problem must be solved with constraints on the order that cities
can be visited in. This form is most closely analogous to the real-world problem of driving from city to
city, where cities are connected by highways in a specific way. The other form of the TSP is the
Euclidean version, where cities are given as coordinates on a two-dimensional plane and the salesman
can move freely from one city to any other. In this form of the problem, distances between cities are
calculated using the Euclidean distance formula. For this project, we tackle the Euclidean version of the
problem.

###Algorithm###
Algorithms for optimization of the TSP usually are either based on thoughtful construction of a new
tour, improvement upon an existing tour, or a combination of both.

Construction algorithms aim to construct a short tour from the beginning. There are variations upon
this: one approach is to construct a short tour in the first try by finding a good order of cities as it runs.
Another approach is to construct many tours either randomly or based on some logic and use the one
with the shortest total distance, throwing out all the others. One example of this is the brute force
construction algorithm which generates every possible tour by finding all permutations of cities and
saves the shortest one. This method will find the optimal tour, but has an extremely poor running time
of O((n-1)!). Improvement algorithms take an existing tour, which could be a random construction or
an optimized construction, and repeatedly perform operations that aim to reduce the total tour distance.
The approach I used to solve the problem was a combination of a simple construction algorithm, the
nearest neighbor heuristic, and an improvement algorithm using a local search heuristic called 2-opt.

####Nearest Neighbor [2]####
The principle behind this algorithm is simple. It constructs a tour by starting with a list of all the cities
and their coordinates. The starting city is chosen arbitrarily and moved to a list of cities representing
the solution. Then, out of the remaining cities, the city nearest in distance to the starting city is moved
to the solution list. This is repeated, using the most recently added city in the solution list as the starting
city, until all cities have been moved to the solution. The tour order will be the order of the cities in the
solution list, and the final move will be to the start of the list.

*This algorithm can be summarized by the following steps:*
1. Create a set of all cities (U) and an ordered set of cities representing a tour (V).
1. Choose arbitrary starting city from V, remove from V and add to U.
2. Select the city in V closest to the latest city added to U, remove from V and add to U.
3. Repeat step 2 until no cities remain in V.

####2-opt neighbor search [2, 3]####
After generating a tour with the nearest neighbor algorithm, I perform a series of exchanges to improve
upon the original tour. To use the 2-opt heuristic, the first step is to generate an initial tour. My originalapproach was to run the nearest neighbor algorithm repeatedly to find the starting point that resulted in
the best initial tour, but I found that the best starting tour didn't always result in the best improved tour
after running the 2-opt. Instead, for relatively small test cases I resorted to running the entire
optimization, including the 2-opt, with each possible start point and choosing the best one. This
becomes impractical above a certain number of cities, but it ran to completion on my computer for all
of the test cases except test-input-8.

The basis of the 2-opt algorithm is to swap the endpoints of two edges of a tour and see if the resulting
tour has a lower distance. For example, in a tour with cities ~A-B~C-D~, where ~ represents an
arbitrary number of intermediate cities, a 2-opt exchange between edge AB and edge CD would result
in the tour ~A-C~B-D~, with the cities between C and B being in reverse order compared to the
original tour. In its naïve form, the algorithm iterates through each city on the tour, performing a 2-opt
exchange between each of the other edges and retains the change only if it reduced the total tour
distance. This unoptimized version of the algorithm runs through every 2-opt exchange, resulting in
fairly poor runtime.

To improve on the runtime of the naïve 2-opt algorithm, there is a comparison that exploits the triangle
inequality to determine if a swap will reduce distance [3]. This is the method I used to improve the
speed of my algorithm. Using the same notation as above, the comparison is that dist(A, C) must be
less than dist(B, D) for an exchange to be distance-reducing. Using this comparison, I reduced the
number of exchanges needed to achieve the same result. My algorithm stops once the distance stops
improving, indicating a locally optimal tour.

There is another method which can further improve the efficiency of the 2-opt algorithm. This method
is to build a neighbor list for each city, sorted by increasing distance of the neighbors from the original
city. Using this strategy, the algorithm requires even fewer iterations. I made an attempt to use this
method and implemented all the code that generates sorted neighbor lists for each city, but I haven't
been able to get it to work in practice.

For all of my solutions, I used the nearest neighbor with a normal 2-opt, running through all possible
starting points when practical (I didn't have time to try every starting point for test instance 8 [2048 cities]). After
seeing the small size of the first test input, I also wrote code implementing the brute force algorithm to
make sure I had the optimal value, but the 2-opt algorithm had already found it. The other test cases
were too large for the the brute force algorithm to find a solution in reasonable time, even with as few
as 19 cities.

###Sources###
[1] http://en.wikipedia.org/wiki/Travelling_salesman_problem
[2] http://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html
[3] http://www2.research.att.com/~dsj/papers/TSPchapter.pdf
