/**
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, is it
 * possible for you to finish all courses?
 *
 * Example 1:
 * Input: 2, [[1,0]]
 * Output: true
 * Explanation: There are a total of 2 courses to take.
 *              To take course 1 you should have finished course 0. So it is
 *              possible.
 *
 * Example 2:
 * Input: 2, [[1,0],[0,1]]
 * Output: false
 * Explanation: There are a total of 2 courses to take.
 *              To take course 1 you should have finished course 0, and to
 *              take course 0 you should also have finished course 1. So it is
 *              impossible.
 *
 * Note:
 * - The input prerequisites is a graph represented by a list of edges, not
 *   adjacency matrices. Read more about how a graph is represented.
 * - You may assume that there are no duplicate edges in the input
 *   prerequisites.
 *
 * 总共有n门课程要进修,有些课程必须有预修课程,必须先修完预修才能修习该课程.
 * 要求判断能否修完所有课程.
 *
 * 比较直观的想法是判断预修课程的关系是否形成一个环,如果有环那就说明不可能修完所有
 * 课程.
 * 话说当时看<<数据结构与算法分析>>时图那一章看的懵懵懂懂,这题虽然知道怎么做,但是
 * 算法写不出来.回去复习.
 *
 * 对于一个有向图而言,如果能对其进行拓扑排序,那么说明该图是无圈的,否则就是有圈的.
 * 我们用一个大小为n的数组保存每个顶点(课程)的入度(在此题中入度表示该课程的预修课
 * 程).所谓拓扑排序就是选择任意一个入度为0的顶点,将相连的边从图中删除并将对应顶点
 * 的入度减少.
 *
 * 为了提高拓扑排序的速度,我们可以将入度为0的顶点放入一个队列中,若队列非空则从队列
 * 中取出队首元素,并将与之相邻的顶点的入度减1,若某个顶点的入度减少为0,则将其入队.
 */
typedef struct {
  int capacity;
  int size;
  int front;
  int rear;
  int *array;
} Queue;

Queue *
queueCreate(int maxsize) {
  Queue *q;

  q = malloc(sizeof(Queue));
  q->capacity = maxsize;
  q->size = 0;
  q->array = malloc(maxsize * sizeof(int));
  q->front = 0;
  q->rear = 1;

  return q;
}

bool
isEmpty(Queue *q) {
  return q->size == 0;
}

bool
isFull(Queue *q) {
  return q->size == q->capacity;
}

void
enqueue(Queue *q, int vertex) {
  if (++q->front == q->capacity)
    q->front = 0;
  q->array[q->front] = vertex;
  ++q->size;
}

int
dequeue(Queue *q) {
  int vertex = q->array[q->rear++];
  --q->size;
  if (q->rear == q->capacity)
    q->rear = 0;

  return vertex;
}

bool
topSort(int **prerequisites, int rows, int cols, int *indegree,
        int numCourses) {
  Queue *q;
  int i, count = 0;

  q = queueCreate(numCourses);

  /* 将入度为0的顶点入队. */
  for (i = 0; i < numCourses; ++i) {
    if (indegree[i] == 0)
      enqueue(q, i);
  }

  while (!isEmpty(q)) {
    int vertex = dequeue(q);
    ++count;  /* count统计已经排序的顶点. */

    /* 将与之相邻的顶点入度减1. */
    for (i = 0; i < rows; ++i) {
      if (prerequisites[i][1] == vertex) {
        if (--indegree[prerequisites[i][0]] == 0)
          enqueue(q, prerequisites[i][0]);
      }
    }
  }

  if (count != numCourses)
    return false;
  else
    return true;
}

bool
canFinish(int numCourses, int **prerequisites, int rows, int cols) {
  int *indegree;
  int i;

  indegree = calloc(numCourses, sizeof(int));

  /* 统计每个顶点的入度. */
  for (i = 0; i < rows; ++i)
    ++indegree[prerequisites[i][0]];

  return topSort(prerequisites, rows, cols, indegree, numCourses);
}


/**
 * 关于拓扑排序的更多介绍可以参见维基百科:
 * https://en.wikipedia.org/wiki/Topological_sorting
 * 上述方法称为Kahn's algorithm,也可以借助于DFS来实现topological sorting.
 * 大致思路如下:
 * 用一个大小为n的数组标记已经访问过的节点,对于未访问过的节点,设置一个临时标记,
 * 继续范围与之相邻的节点,若在访问途中遇到有临时标记的节点则表示图有圈,否则继续.
 * 访问完成后将初始节点置为设置永久标记.
 * 下面的代码用1表示永久标记,-1表示临时标记.
 */
bool
dfs(int vertex, int *vertices, int numCourses, int **prerequisites, int rows,
    int cols) {
  int i;

  if (vertices[vertex] == 1)
    return true;
  else if (vertices[vertex] == -1)
    return false;

  vertices[vertex] = -1;
  for (i = 0; i < rows; ++i) {
    if (prerequisites[i][1] == vertex)
      if (!dfs(prerequisites[i][0], vertices, numCourses, prerequisites,
               rows, cols))
        return false;
  }
  vertices[vertex] = 1;

  return true;
}

bool
canFinish(int numCourses, int **prerequisites, int rows, int cols) {
  int *vertices;
  int i;

  vertices = calloc(numCourses, sizeof(int));

  for (i = 0; i < numCourses; ++i) {
    if (vertices[i] == 1)
      continue;
    if (!dfs(i, vertices, numCourses, prerequisites, rows, cols))
      return false;
  }

  return true;
}


/**
 * 上述方法在查找邻接点时每次都遍历prerequisites,这是因为题目给定的输入结构是
 * 边的集合,我们可以将其转换为邻接表来表示.为简便起见用一个二维矩阵表示邻接表.
 */
int **
graphInit(int numCourses, int **prerequisites, int rows, int cols,
          int **colsSize) {
  int **graph;
  int i, j;

  graph = malloc(numCourses * sizeof(int *));
  *colsSize = calloc(numCourses, sizeof(int));

  /* 总共numCourses个节点,故最多有numCourses个邻接点. */
  for (i = 0; i < numCourses; ++i)
    graph[i] = malloc(numCourses * sizeof(int));

  for (i = 0; i < rows; ++i) {
    int vertex = prerequisites[i][1];
    graph[vertex][(*colsSize)[vertex]++] = prerequisites[i][0];
  }

  return graph;
}

bool
dfs(int vertex, int *vertices, int numCourses, int **graph, int *colsSize) {
  int i;

  if (vertices[vertex] == 1)
    return true;
  else if (vertices[vertex] == -1)
    return false;

  vertices[vertex] = -1;
  for (i = 0; i < colsSize[vertex]; ++i) {
    if (!dfs(graph[vertex][i], vertices, numCourses, graph, colsSize))
      return false;
  }
  vertices[vertex] = 1;

  return true;
}

bool
canFinish(int numCourses, int **prerequisites, int rows, int cols) {
  int *vertices;
  int i;
  int **graph, *colsSize;

  vertices = calloc(numCourses, sizeof(int));

  graph = graphInit(numCourses, prerequisites, rows, cols, &colsSize);

  for (i = 0; i < numCourses; ++i) {
    if (vertices[i] == 1)
      continue;
    if (!dfs(i, vertices, numCourses, graph, colsSize))
      return false;
  }

  return true;
}