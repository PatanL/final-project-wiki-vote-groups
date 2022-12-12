import networkx as nx

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

def read_graph():
    graph_adjacency_list = { }
    for line in open("/Users/dongyu/Desktop/College/cs225/final-project-wiki-vote-groups/adjacency_list.txt"):
        line = line.rstrip()
        line = map(int, line.split(" "))
        graph_adjacency_list.update({ list(line)[0]: { e: 1 for e in list(line)[1:] } })

    return graph_adjacency_list

graph_data = read_graph()
G = nx.Graph(graph_data)
nx.draw_networkx(G, with_labels = True, node_color = "c", edge_color = "k", fontsize= 2)

plt.axis('off')
plt.draw()
plt.savefig("graph.pdf")