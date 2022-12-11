# anhnp2, shayana3, pzl2
# Final Project
# [Video Presentation of Project]() link to be added

# Data

We use the data from the Stanford SNAP dataset (http://snap.stanford.edu/data/wiki-Vote.html) , a dataset on the network of all the Wikipedia voting data from the inception of Wikipedia till January 2008.

# Deliverables
* #### Code 
  * All the code is found in the root directory(https://github.com/PatanL/final-project-wiki-vote-groups/tree/main/)
* #### Proposal
  * [Project Proposal](https://github.com/PatanL/final-project-wiki-vote-groups/blob/main/documents/Proposal.md)

* #### Development
  * [Development Log](https://github.com/PatanL/final-project-wiki-vote-groups/blob/main/documents/log.md). 
  
* #### Contracts
  * [Team Contract](https://github.com/PatanL/final-project-wiki-vote-groups/blob/main/documents/Contract.md)

* #### Written Report
  * [Report]() link to be added
# Installation
Make sure you are running the program in Docker. If not, follow [This Guide](https://courses.engr.illinois.edu/cs225/sp2022/resources/own-machine/) to get started.

### Executable
In order to get the program running, run `make` and then `bin/exec` in the root directory.

We call all our functions to demonstrate functionality in the main.cpp file. This includes:
1. Build graph:
   - Input: data file
   - Output: Nothing, but the graph is built
2. Most Voted Node:
   - Input: the graph
   - Output: The most voted admin ID
3. Votes Away From Most Popular:
   - Input: the graph
   - Output: A vector of the number of admin ID corresponding to increasing depth from most popular admin (starting from 0)
4. Strongly Connected Component:
   - Input: the graph
   - Output: A vector of all strongly connected component in form of a vector of admin index

### Tests
To run the test cases, run `make test` then `bin/test` in the root directory.

We constructed several small to medium sized datasets in /data directory, which are used as test cases to evaluate if the output of our algorithms are as expected. We also tested for edge cases such as when the graph is not fully connected. Our tests focus on testing the functionality of graph construction, Kosaraju's Strongly Connected Component, Floyd-Warshall SSSP, and BFS Traversal.

