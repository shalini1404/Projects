# Influence Maximization in Graphs

In this project influence Maximization is implemented under Independent Cascade Model using Greedy Maximal Marginal Selection algorithm and further optimized it
keeping same spread.

-File greedy.cpp is the used to run greedy algorithm. To compile this code, do it with following command:
 g++ -std=c++11 greedy.cpp -o greedy

 To run this code, do it with following command:
 ./greedy k path_of_input_file_with_generated_graphs

 where k is the no. of seed nodes to be selected and path_of_input_file_with_generated_graphs is the path of files generated with diffrent probabilities. For eg,
 if 5000 graphs for prob=0.1 are generated in folder graphs with name g0, g2, g2 and so on, then path_of_input_file_with_generated_graphs will be:
 graphs/g

 -File optimized.cpp is the used to run optimized algorithm. To compile this code, do it with following command:
 g++ -std=c++11 optimized.cpp -o opt

 To run this code, do it with following command:
 ./opt k path_of_input_file_with_generated_graphs

 where k is the no. of seed nodes to be selected and path_of_input_file_with_generated_graphs is the path of files generated with diffrent probabilities. For eg,
 if 5000 graphs for prob=0.1 are generated in folder "graphs" with name "g0", "g2", "g2" and so on, then path_of_input_file_with_generated_graphs will be:
 graphs/g

-File pager.cpp is the used to run page rank algorithm. To compile this code, do it with following command:
 g++ -std=c++11 pager.cpp -o pg

 To run this code, do it with following command:
 ./pg k path_of_input_file_with_generated_graphs

 where k is the no. of seed nodes to be selected and path_of_input_file_with_generated_graphs is the path of files generated with diffrent probabilities. For eg,
 if 5000 graphs for prob=0.1 are generated in folder "graphs" with name "g0", "g2", "g2" and so on, then path_of_input_file_with_generated_graphs will be:
 graphs/g

 (table.h and table.cpp is included in pager.cpp)