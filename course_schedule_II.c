/**
 * There are a total of n courses you have to take, labeled from 0 to n-1.
 * Some courses may have prerequisites, for example to take course 0 you have
 * to first take course 1, which is expressed as a pair: [0,1]. Given the total
 * number of courses and a list of prerequisite pairs, return the ordering of
 * courses you should take to finish all courses. There may be multiple correct
 * orders, you just need to return one of them. If it is impossible to finish
 * all courses, return an empty array.
 *
 * Example 1:
 * Input: 2, [[1,0]]
 * Output: [0,1]
 * Explanation: There are a total of 2 courses to take. To take course 1 you
 *              should have finished course 0. So the correct course order is
 *              [0,1] .
 *
 * Example 2:
 * Input: 4, [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,1,2,3] or [0,2,1,3]
 * Explanation: There are a total of 4 courses to take. To take course 3 you
 *              should have finished both courses 1 and 2. Both courses 1 and 2
 *              should be taken after you finished course 0. So one correct
 *              course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].
 *
 * Note:
 * - The input prerequisites is a graph represented by a list of edges, not
 *   adjacency matrices. Read more about how a graph is represented.
 * - You may assume that there are no duplicate edges in the input prerequisites.
 *
 * 前一道题course schedule是问能不能修完所有的课程,这道题是在能修完的前提下给出一个
 * 顺序.
 * 没啥好说的,拓扑(Topological Sort)排序问题.
 * 1. 用一个数组indegree记录每门课程的入度;
 * 2. 每次随机挑选一个入度为0的课程,将将与之相邻的课程的入度减1;
 * 3. 重复步骤2直到所有课程遍历完毕或者找不到入度为0的课程.
 *
 * 为了提高算法效率,用一个队列保存入度为0的课程,若某门课程的入度减少为0,则将其入队.
 * 另外由于课程的关系是用一系列边表示的,将其转换为邻接表更容易处理.
 */
typedef struct Queue *Queue;

struct Queue {
  int capacity;
  int size;
  int front;
  int rear;
  int *array;
};

Queue
queueCreate(int maxsize) {
  Queue q;

  q = malloc(sizeof(struct Queue));
  q->capacity = maxsize;
  q->size = 0;
  q->front = 0;
  q->rear = 1;
  q->array = malloc(maxsize * sizeof(int));

  return q;
}

bool
isEmpty(Queue q) {
  return q->size == 0;
}

void
enqueue(Queue q, int x) {
  if (++q->front == q->capacity)
    q->front = 0;
  q->array[q->front] = x;
  ++q->size;
}

int
dequeue(Queue q) {
  int x;

  x = q->array[q->rear++];
  --q->size;
  if (q->rear == q->capacity)
    q->rear = 0;

  return x;
}

void
queueFree(Queue q) {
  if (q) {
    free(q->array);
    free(q);
  }
}


int *
findOrder(int n, int **pre, int rows, int *cols, int *returnSize) {
  int i, j, *ans;
  int *indegree, **outdegree;
  Queue q;

  indegree = calloc(n, sizeof(int));
  outdegree = malloc(n * sizeof(int *));
  /* 共n门课程,每门课程最多n-1个后续课程. 故分配n个空间,第0位表示大小. */
  for (i = 0; i < n; ++i) {
    outdegree[i] = malloc(n * sizeof(int));
    outdegree[i][0] = 0;
  }

  /* 创建邻接表. */
  for (i = 0; i < rows; ++i) {
    ++indegree[pre[i][0]];
    outdegree[pre[i][1]][++outdegree[pre[i][1]][0]] = pre[i][0];
  }

  q = queueCreate(n);
  for (i = 0; i < n; ++i) {
    if (indegree[i] == 0)
      enqueue(q, i);
  }


  *returnSize = 0;
  ans = malloc(n * sizeof(int));

  while (!isEmpty(q)) {
    int idx = dequeue(q);
    ans[(*returnSize)++] = idx;

    for (j = 1; j <= outdegree[idx][0]; ++j) {
      if (--indegree[outdegree[idx][j]] == 0)
        enqueue(q, outdegree[idx][j]);
    }
  }

  if (*returnSize < n)
    *returnSize = 0;
  return ans;
}


/**
 * 上述方法采用的是数组,用链表的话,一来可以避免空间的浪费,二来在入度
 * 减少为0时可以将课程从图中删除,避免不必要的遍历.
 * 从LeetCode上的测试结果来说比上述数组的方法快很多.
 */
struct Course {
  int no;         /* 课程编号. */
  int indegree;   /* 入度. */
  struct Course *next;  /* 出度. */
};

int *
findOrder(int n, int **pre, int rows, int *cols, int *returnSize) {
  int i, *ans;
  struct Course *graph;
  Queue q;

  graph = malloc(n * sizeof(struct Course));
  for (i = 0; i < n; ++i) {
    graph[i].no = i;
    graph[i].indegree = 0;
    graph[i].next = NULL;
  }

  /* 初始化图. */
  for (i = 0; i < rows; ++i) {
    int prev = pre[i][1];
    int next = pre[i][0];

    ++graph[next].indegree;
    struct Course *temp = malloc(sizeof(struct Course));
    temp->no = next;
    temp->next = graph[prev].next;
    graph[prev].next = temp;
  }

  q = queueCreate(n);
  for (i = 0; i < n; ++i) {
    if (graph[i].indegree == 0)
      enqueue(q, i);
  }

  ans = malloc(n * sizeof(int));
  while (!isEmpty(q)) {
    int idx = dequeue(q);
    ans[(*returnSize)++] = idx;

    struct Course *node = graph[idx].next;
    struct Course *t = &graph[idx];
    while (node) {
      if (--graph[node->no].indegree == 0) {
        enqueue(q, node->no);
        t->next = node->next;
        free(node);
        node = t->next;
      } else {
        t = node;
        node = node->next;
      }
    }
  }

  if (*returnSize < n)
    *returnSize = 0;

  return ans;
}