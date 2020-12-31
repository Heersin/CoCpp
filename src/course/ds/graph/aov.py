'''
Topologic Sorting

Desc:
    There are prequisite courses before u take a High-level course, 
    topologic sorting can help us to ensure a sequence to learn these
    courses step by step

Algorithm:
    1. chose a node whose indegree is 0
    2. record it and delete it
    3. repeat from 1 until the graph is empty or
        there are none indegree-0 node (that means its not a DAG, contains loop)
'''

import general_graph as gg
import copy as cp

def get_all_indegree_zeros(graph):
    v_list = graph.get_vertexs()
    result = []
    for v in v_list:
        if graph.get_indegree(v, mode=0) == 0:
            result.append(v)
    return result

def topo_sorting(graph):
    g = cp.deepcopy(graph)
    result = []

    while True:
        v_list = get_all_indegree_zeros(g)
        if len(v_list) == 0:
            break
        result.append(v_list[0])
        g.del_vertex(v_list[0], mode=0)

    remain_nodes = g.get_vertexs()
    if len(remain_nodes) == 0:
        return result
    else:
        print("Not A DAG, loop may exsits among : ")
        print(remain_nodes)
        return None



if __name__ == '__main__':
    graph = gg.MatrixGraph(5)
    graph.add_edge(0,1)
    graph.add_edge(0,3)
    graph.add_edge(1,3)
    graph.add_edge(1,2)
    graph.add_edge(3,2)
    graph.add_edge(3,4)
    graph.add_edge(2,4)

    x = get_all_indegree_zeros(graph)
    print(x)
    topo = topo_sorting(graph)
    print(topo)
    graph.print_graph()


    graph = gg.ListGraph(5)
    graph.add_edge(0,1)
    graph.add_edge(0,3)
    graph.add_edge(1,3)
    graph.add_edge(1,2)
    graph.add_edge(3,2)
    graph.add_edge(3,4)
    graph.add_edge(2,4)

    x = get_all_indegree_zeros(graph)
    print(x)
    topo = topo_sorting(graph)
    print(topo)
    print(graph)
