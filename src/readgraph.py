import networkx as nx

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

def read_graph():
    G = nx.Graph()
    graph_adjacency_list = { }
    for line in open("/Users/dongyu/Desktop/College/cs225/final-project-wiki-vote-groups/adjacency_list.txt"):
        line = line.strip(" ").split(" ")
        G.add_node(line[0])
        for i in range(1, len(line)):
            G.add_edge(line[0], line[i])
        

    return G

G = read_graph()
nx.draw_networkx(G, arrows = True, with_labels = True, node_size = 10, node_color = "c", edge_color = "k", font_size = 1)

plt.axis('off')
plt.draw()
plt.savefig("graph.pdf")