# KMBSteinerTree
This program aproximates the optimal Steiner Tree using the KMB heuristic in witch we compute the the metric clousure of the given conected graph, induced by the terminals. Then, compute the Minumum Span Tree (MST) for the metric clousure show the path between each terminal.

## Aproximation Ratio
For the provided instances the solution is, in average, 26% distant from the optimal solution. But, in the genaral case the cost of the solution given by this method has a 2 - 2 / t factor of distance from the optiaml solution.

## Output format 
Prints the Cost: | Three ...

## Build
`make`

## Test
`make test` runs some special cases such as disconected graphs and graphs that has all vertices as terminals

## Run
`make run`

## References
https://www.researchgate.net/publication/305636225_An_Effective_Construction_Algorithm_for_the_Steiner_Tree_Problem_Based_on_Edge_Betweenness

https://en.wikipedia.org/wiki/Steiner_tree_problem
