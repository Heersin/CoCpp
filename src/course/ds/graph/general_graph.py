'''
Implemention of diffrent Graph

- Neighbor Matrix Implemention
- Neighbor LinkList
'''

import numpy as np

# neighbor matrix
class MatrixGraph():
    def __init__(self, num_of_vertex):
        self.matrix = np.array([[0] * num_of_vertex] * num_of_vertex)
        self.name_dict = {}
        self.name_list = [0] * num_of_vertex

        for i in range(num_of_vertex):
            self.name_dict['v' + str(i)] = i
            self.name_list[i] = 'v' + str(i)

        self.num = num_of_vertex

    def add_vertex(self, name=None):
        m = self.matrix
        n = self.num
        if name is None:
            name = 'v' + n

        # add name to current known list
        self.name_dict[name] = n
        self.name_list.append(name)

        # add col and row
        m = np.insert(m, n, 0, axis=1)
        m = np.insert(m, n, 0, axis=0)
        self.matrix = m
        self.num += 1

    def del_vertex(self, name, mode=1):
        if mode == 0:
            v_index = self.name_dict[name]
            v_name = name
        else:
            v_index = name
            v_name = self.name_list[name]
        
        m = self.matrix
        m = np.delete(m, v_index, 0)
        m = np.delete(m, v_index, 1)
        self.matrix = m

        del self.name_dict[v_name]
        self.name_list.remove(v_name)

        # fix name_dict
        for index in range(len(self.name_list)):
            name = self.name_list[index]
            self.name_dict[name] = index

        self.num -= 1

    def _set_edge(self, start, end, value, mode=1):
        if mode == 0:
            start_index = self.name_dict[start]
            end_index = self.name_dict[end]
        else:
            start_index = start
            end_index = end

        self.matrix[start_index][end_index] = value


    # mode 0 means find by name
    def add_edge(self, start, end, value=1, mode=1):
        self._set_edge(start, end, value, mode)

    def add_double_edge(self, start, end, value=1, mode=1):
        self._set_edge(start, end, value, mode)
        self._set_edge(end, start, value, mode)

    def del_edge(self, start, end, mode=1):
        self._set_edge(start, end, 0, mode)

    def del_double_edge(self, start, end, mode=1):
        self._set_edge(start, end, 0, mode)
        self._set_edge(end, start, 0, mode)

    def get_related_vertex(self, vertex, mode=1):
        neighbor = self.matrix[vertex]
        related = []
        for v in range(self.num):
            if neighbor[v] == 1:
                related.append(v)
        return related

    def get_indegree(self, vertex, mode=1):
        if mode == 0:
            vertex = self.name_dict[vertex]

        m = self.matrix
        vlist = m[:, vertex]

        count = 0
        for v in vlist:
            if v != 0:
                count +=1

        return count

    def get_edge_value(self, start, end, mode=1):
        if mode == 0:
            start = name_dict[start]
            end = name_dict[end]
        return self.matrix[start][end]

    def get_vertexs(self):
        result = []
        for v in self.name_list:
            result.append(v)
        return result
        
    def print_graph(self):
        print("Verdicts:\n {}".format(self.name_dict))
        print("Graph:\n {}".format(self.matrix))

# neighbor list
# neighbot list do not support valued map
class ListGraph():
    def __init__(self, num_of_vertex):
        self.graph = {}
        self.name_dict = {}
        self.name_list = [0] * num_of_vertex

        for i in range(num_of_vertex):
            self.name_dict['v' + str(i)] = i
            self.graph[i] = []
            self.name_list[i] = 'v' + str(i)

        self.num = num_of_vertex

    def add_vertex(self, name=None):
        m = self.graph
        n = self.num
        if name is None:
            name = 'v' + n

        # add name to current known list
        self.name_dict[name] = n
        self.name_list.append(name)

        # add to graph
        self.graph[n] = []

        # fix num of vertex
        self.num += 1

    def del_vertex(self, name, mode=1):
        g = self.graph
        if mode == 0:
            v_index = self.name_dict[name]
            v_name = name
        else:
            v_index = name
            v_name = self.name_list[name]

        # clear edges of vertex v
        del g[v_index]
        for vi in g:
            l = g[vi]
            if name in l:
                l.remove(v_name)

        del self.name_dict[v_name]
        self.name_list.remove(v_name)

        # fix name_dict
        # for index in range(len(self.name_list)):
        #    name = self.name_list[index]
        #    self.name_dict[name] = index

        self.num -= 1

    # mode 0 means find by name
    def _translate(self, start, end, mode=1):
        if mode == 0:
            start_index = self.name_dict[start]
            end_index = self.name_dict[end]
        else:
            start_index = start
            end_index = end

        return start_index, end_index

    def add_edge(self, start, end, mode=1):
        start_index, end_index = self._translate(start, end, mode)
        self.graph[start_index].append(end_index)

    def add_double_edge(self, start, end, mode=1):
        start_index, end_index = self._translate(start, end, mode)
        self.graph[start_index].append(end_index)
        self.graph[end_index].append(start_index)

    def del_edge(self, start, end, mode=1):
        start_index, end_index = self._translate(start, end, mode)
        neighbor_list = self.graph[start_index]
        neighbor_list.remove(end_index)

    def del_double_edge(self, start, end, mode=1):
        del_edge(start, end, mode)
        del_edge(end, start, mode)

    def get_related_vertex(self, vertex):
        # return a list contains related vertexs
        return self.graph[vertex]

    def get_indegree(self, vertex, mode=1):
        if mode == 0:
            vertex = self.name_dict[vertex]

        g = self.graph
        count = 0

        for vi in g:
            vlist = g[vi]
            if vertex in vlist:
                count += 1

        return count

    def get_vertexs(self):
        result = []
        for v in self.name_list:
            result.append(v)
        return result

    def print_graph(self):
        print("Verdicts:\n {}".format(self.name_dict))
        print("Graph:\n {}".format(self.graph))



if __name__ == '__main__':
    g = MatrixGraph(3)
    g.add_edge(0,1)
    g.add_edge(0,2)
    g.add_edge(2,1)
    g.add_vertex('test')
    print(g.get_related_vertex(0))
    print("in degree is " + str(g.get_indegree(1)))

    g.print_graph()
    g.del_edge(0,2)
    g.del_vertex(2)
    g.print_graph()
    print("Vertexs: ")
    print(g.get_vertexs())

    g = ListGraph(3)
    g.add_edge(0,1)
    g.add_edge(0,2)
    g.add_edge(2,1)
    g.add_vertex('test')
    print(g.get_related_vertex(0))
    print("in degree is " + str(g.get_indegree(1)))

    g.print_graph()
    g.del_edge(0,2)
    g.del_vertex(2)
    g.print_graph()
    print("Vertexs: ")
    print(g.get_vertexs())


