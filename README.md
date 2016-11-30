Project 05: Path Finding
========================

This [project] implements a [Dijkstra's Algorithm] to perform rudimentary path
finding on a 2D tile-based map.

[project]:              https://www3.nd.edu/~pbui/teaching/cse.30331.fa16/project05.html
[Dijkstra's Algorithm]: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm


Input
-----

    TILES_N
    TILE_NAME_0	TILE_COST_0
    ...
    TILE_NAME_N-1	TILE_COST_N-1

    MAP_ROWS MAP_COLUMNS
    TILE_0_0    ...
    ...

    TRAVELER_START_ROW TRAVELER_START_COL
    TRAVELER_END_ROW   TRAVELER_END_COL

Output
------

    Cost
    [(ROW_0, COL_0), ...]

Measure
--------

| N             | Elapsed Time  | Memory Usage   |
|---------------|---------------|----------------|
| 10            | 0.002998      | 1.171875       |
| 20            | 0.008997      | 1.226562       |
| 50            | 0.057990      | 1.617188       |
| 100           | 0.260960      | 3.003906       |
| 200           | 1.164822      | 8.539062       |
| 500           | 8.534702      | 47.234375      |
| 1000          | 38.400162     | 185.359375     |
|---------------|---------------|----------------|

Output File Differences
-----------------------

Test 1: 
    Given output:           Our output: 
        63                      63
        3 3                     3 3
        4 3                     4 3
        5 3                     5 3
        5 4                     5 4 
        5 5                     6 4 ** Different
        6 5                     6 5
        6 6                     6 6
        6 7                     6 7
        6 8                     6 8
        7 8                     7 8
        8 8                     8 8
        8 9                     8 9
        9 9                     9 9
        10 9                    10 9
        11 9                    11 9
        11 10                   12 9 ** Diferent 
        12 10                   12 10
        12 11                   12 11
        13 11                   13 11
        13 12                   13 12
        13 13                   13 13
        14 13                   14 13
        15 13                   15 13
        16 13                   16 13 
        17 13                   17 13
        17 14                   17 14
        17 15                   17 15
        17 16                   17 16
        17 17                   17 17
        17 18                   17 18

    Original: (5,5) , (11, 10)
    Alternative: (6,4) , (12, 9)
    
    Original: 5,5 = g = 1
              11,10 = m = 7 
                        = 8
    Alternative: 6,4 = g  = 1 
                 12,9 = m = 7 
                          = 8 
    While different tiles are chosen their total cost remains the same showing there is more than one shortest path with a total cost of 63. 

Test 2: 
    Given output:           Our output: 
        17                      17
        0 0                     0 0
        0 1                     1 0 **different
        1 1                     2 0 **different
        2 1                     2 1
        2 2                     2 2
        2 3                     2 3
        3 3                     3 3

    Original: (0,1) , (1,1)
    Alternative: (1,0) , (2,0)

    Original: 0,1 = g = 1
              1,1 = r = 5
                      = 6
    Alternative: 1,0 = f = 3
                 2,0 = f = 3
                         = 6
    While different tiles are chosen the total cost still adds up to 6.  The total costs of the full paths are also equal at 17 showing there is more than one valid shortest path.                 
        
              
        
Questions
----------

* How did you represent the map as a graph?

We represented the map by using a vector of vectors and then used a distance map and a previous map to keep track of shortest distances and the nodes that these distances came from. We also had a map created initially to store the cost of leaving each lettered node.

* What is complexity of your implementation of Dijkstra's Algorithm?

We used a set, 3 maps, a priority queue, and a vector of vector. For space complexity, the graph takes up O(N^2) because the vector of vectors is NxN data. This is the greatest space taken up of any of the data structures, which is why the memory usage increases so drastically with large N's. The maps and priority queue has space complexity of O(N). For time complexity, in worst case, it is O(N^2) for the nested for loops, but it rarely has to check all of these nodes (only when N <= 3. Then checking the priority queue for the nodes not in the marked set would take in worst case O(N) time. Therefore, our time complexity is slightly better than space complexity, but still increases with greater N.

* How well does your implementation scale?

As stated above, as N increases, both time and memorage increase with time scaling slightly better than memory usage does.

* Group member contributions:

We all worked together on every part, woo!
