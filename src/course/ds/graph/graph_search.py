'''
implemention of DFS and BFS
with Queue/Stack

Desc:
    BFS(Breadth First Search) is similar to the level traversal,
    it searches the nodes of the Lv.1, then Lv.2, then Lv.3 ...

    DFS(Depth First Search) searches the nodes until reach the deepest one

Algorithm:
    BFS:
        1. put root into queue
        2. dequeue to get current node 
        3. call procedure (for target-search task call your check func)
        4. put all the children of current node into queue
        5. repeat from 2, if the queue is empty-> Done

    DFS:
        1. put root into stack
        2. pop to get current node
        3. call procedure
        4. put one child which has not been examined into stack
        5. repeat from 2, if all the children has been examined, put parent node into
           stack, and then repeat from 2
        6. when stack is empty -> Done


'''
import general_graph as gg

def print_helper(x, args):
    print(x)

def BFS(graph, root, procedure=print_helper, args=None):
    queue = []
    history = []
    queue.append(root)
    history.append(root)

    while True:
        if len(queue) == 0:
            break
        cur_node = queue.pop(0)
        procedure(cur_node, args)
        related = graph.get_related_vertex(cur_node)
        
        for node in related:
            if node in history:
                continue
            queue.append(node)
            history.append(node)

    return history


def DFS(graph, root, procedure=print_helper, args=None):
    stack = []
    has_seen = set()
    history = []
    stack.append(root)
    has_seen.add(root)

    while True:
        if len(stack) == 0:
            break
        cur_node = stack.pop()
        procedure(cur_node, args)
        history.append(cur_node)
        related = graph.get_related_vertex(cur_node)
        
        for node in related:
            if node in has_seen:
                continue
            stack.append(node)
            has_seen.add(node)

    return history

if __name__ == '__main__':
    m = gg.MatrixGraph(5)
    m.add_double_edge(0,1)
    m.add_double_edge(0,2)
    m.add_double_edge(0,3)
    m.add_double_edge(3,4)
    m.add_double_edge(2,3)
    m.add_double_edge(1,4)
    m.print_graph()

    history = BFS(m, 0)
    print(history)

    m = gg.MatrixGraph(5)
    m.add_double_edge(0,1)
    m.add_double_edge(0,2)
    m.add_double_edge(0,3)
    m.add_double_edge(3,4)
    m.add_double_edge(2,3)
    m.add_double_edge(1,4)
    m.print_graph()

    history = DFS(m, 0)
    print(history)
