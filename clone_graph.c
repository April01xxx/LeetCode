/**
 * Given the head of a graph, return a deep copy (clone) of the graph. Each node
 * in the graph contains a label (int) and a list (List[UndirectedGraphNode])
 * of its neighbors. There is an edge between the given node and each of the
 * nodes in its neighbors.
 *
 * OJ's undirected graph serialization (so you can understand error output):
 * Nodes are labeled uniquely.
 *
 * We use # as a separator for each node, and , as a separator for node label
 * and each neighbor of the node.
 *
 * As an example, consider the serialized graph {0,1,2#1,2#2,2}.
 *
 * The graph has a total of three nodes, and therefore contains three parts as
 * separated by #.
 *
 * First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
 * Second node is labeled as 1. Connect node 1 to node 2.
 * Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming
 * a self-cycle.
 *
 * Visually, the graph looks like the following:
 *
 *        1
 *       / \
 *      /   \
 *     0 --- 2
 *          / \
 *          \_/
 * Note: The information about the tree serialization is only meant so that you
 * can understand error output if you get a wrong answer. You don't need to
 * understand the serialization to solve the problem.
 *
 * 深度拷贝一个图.
 * 既然是深度拷贝(clone)那就要自己分配空间了,但在递归的过程中注意已经存在的节点不能
 * 再次分配空间,所以需要一个集合保存已经分配了空间的节点.
 */

/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
  map<int, UndirectedGraphNode *> exists;
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    UndirectedGraphNode *graph;

    if (node == NULL)
      return NULL;

    graph = new UndirectedGraphNode(node->label);
    exists[graph->label] = graph;
    for (int i = 0; i < node->neighbors.size(); ++i) {
      if (exists.count(node->neighbors[i]->label))
        graph->neighbors.push_back(exists[node->neighbors[i]->label]);
      else
        graph->neighbors.push_back(cloneGraph(node->neighbors[i]));
    }

    return graph;
  }
};

/**
 * 上面是偷懒用C++实现,下面还是用C再实现一次吧.
 * 用一个全局的hash表保存那些已经分配了空间的节点,在递归时判断当前处理的节点是否
 * 已经分配了空间即可.
 */
/**
 * #define NEIGHBORS_MAX_SIZE 100
 * struct UndirectedGraphNode {
 *     int label;
 *     struct UndirectedGraphNode *neighbors[NEIGHBORS_MAX_SIZE];
 *     int neighborsCount;
 * };
 */
typedef struct UndirectedGraphNode Graph;
#define MAX_SIZE 1024

typedef struct {
  int key;  /* lable */
  Graph *value;
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

HashTable *
createHashTable(int maxsize) {
  HashTable *h;

  h = malloc(sizeof(HashTable));
  h->size = maxsize << 1;
  h->array = calloc(h->size, sizeof(HashEntry));

  return h;
}

int
find(HashTable *h, int key) {
  int hashval = labs(key) % h->size;
  HashEntry *ht = h->array;

  while (ht[hashval].value) {
    if (ht[hashval].key == key)
      return hashval;
    else {
      ++hashval;
      if (hashval == h->size)
        hashval = 0;
    }
  }

  return hashval;
}

void
insert(HashTable *h, int key, Graph *node) {
  int hashval;

  hashval = find(h, key);
  h->array[hashval].key = key;
  h->array[hashval].value = node;
}

void
freeHashTable(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

Graph *
helper(Graph *g, HashTable *h) {
  Graph *node;
  int i, pos;

  if (!g)
    return NULL;

  node = malloc(sizeof(Graph));
  node->label = g->label;
  node->neighborsCount = g->neighborsCount;
  insert(h, node->label, node);
  for (i = 0; i < g->neighborsCount; ++i) {
    pos = find(h, g->neighbors[i]->label);
    if (h->array[pos].value)
      node->neighbors[i] = h->array[pos].value;
    else
      node->neighbors[i] = helper(g->neighbors[i], h);
  }

  return node;
}

Graph *cloneGraph(Graph *graph) {
  HashTable *h;

  h = createHashTable(MAX_SIZE);

  return helper(graph, h);
}