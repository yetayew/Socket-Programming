#pseudo code for DFS
#-----------------------------------------------------------------------------------
#Breadth_First_Search( Graph, X ):
 #   Let Q be the queue
 #   Q.enqueue( X )     // Inserting source node X into the queue
 #   Mark X node as visited.

  #  While ( Q is not empty )
   #     Y = Q.dequeue( )     // Removing the front node from the queue

   # Process all the neighbors of Y, For all the neighbors Z of Y
   # If Z is not visited:
    #    Q. enqueue( Z )     // Stores Z in Q
     #   Mark Z as visited
#-----------------------------------------------------------------------------------

# Python3 Program to print BFS traversal
# from a given source vertex. BFS(int s)
# traverses vertices reachable from s.
 
from collections import defaultdict
 
 
# This class represents a directed graph
# using adjacency list representation
class Graph:
 
    # Constructor
    def __init__(self):
 
        # Default dictionary to store graph
        self.graph = defaultdict(list)
 
    # Function to add an edge to graph
    def addEdge(self, u, v):
        self.graph[u].append(v)
 
    # Function to print a BFS of graph
    def BFS(self, s):
 
        # Mark all the vertices as not visited
        visited = [False] * (max(self.graph) + 1)
 
        # Create a queue for BFS
        queue = []
 
        # Mark the source node as
        # visited and enqueue it
        queue.append(s)
        visited[s] = True
 
        while queue:
 
            # Dequeue a vertex from
            # queue and print it
            s = queue.pop(0)
            print(s, end=" ")
 
            # Get all adjacent vertices of the
            # dequeued vertex s. If a adjacent
            # has not been visited, then mark it
            # visited and enqueue it
            for i in self.graph[s]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
 
 
# Driver code
if __name__ == '__main__':
 
    g = Graph()
    g.addEdge(0, 1)
    g.addEdge(0, 2)
    g.addEdge(1, 2)
    g.addEdge(2, 0)
    g.addEdge(2, 3)
    g.addEdge(3, 3)
 
    print("Following is Breadth First Traversal"
          " (starting from vertex 2)")
    g.BFS(2)
 
