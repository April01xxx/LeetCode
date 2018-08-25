/**
 * Given a binary tree, return the zigzag level order traversal of its nodes'
 * values. (ie, from left to right, then right to left for the next level and
 * alternate between).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its zigzag level order traversal as:
 * [
 *   [3],
 *   [20,9],
 *   [15,7]
 * ]
 *
 * 给定一棵二叉树,以之字形层序遍历其所有节点.在层序遍历的基础上有点小变化,
 * 偶数层是从右向左输出,奇数层从左向右输出.
 */
typedef struct Queue *Queue;

struct Queue {
  int capacity;
  int size;
  int front;
  int rear;
  struct TreeNode **array;
};

Queue
createQueue(int size) {
  Queue q;

  q = malloc(sizeof(struct Queue));
  q->capacity = size;
  q->size = 0;
  q->front = 1;
  q->rear = 0;
  q->array = malloc(size * sizeof(struct TreeNode *));

  return q;
}

void
disposeQueue(Queue q) {
  if (q) {
    free(q->array);
    free(q);
  }
}

bool
isEmpty(Queue q) {
  return q->size == 0;
}

bool
isFull(Queue q) {
  return q->capacity == q->size;
}

void
enqueue(struct TreeNode *node, Queue q) {
  /**
   * 循环队列满时重新分配空间不能简单的realloc,示意图如下:
   * |          | |     |
   *            r f
   * r指向队列尾,f指向队列头,此时队列满了,如果realloc,将会在
   * 原队列大小后面多出一段空间,导致整个队列中间一部分为空.
   * 所以下面这段代码是错误的:
   * if (isFull(q)) {
   *   q->capacity *= 2;
   *   q->array = realloc(q->array, q->capacity * sizeof(struct TreeNode *));
   * }
   */
  if (isFull(q)) {
    q->array = realloc(q->array, 2 * q->capacity * sizeof(struct TreeNode *));
    memcpy(q->array + q->capacity, q->array,
           (q->rear + 1) * sizeof(struct TreeNode *));
    q->rear += q->capacity;
    q->capacity <<= 1;
  }

  if (++q->rear == q->capacity)
    q->rear = 0;
  ++q->size;
  q->array[q->rear] = node;
}

struct TreeNode *
dequeue(Queue q) {
  struct TreeNode *node;

  --q->size;
  node = q->array[q->front++];

  if (q->front == q->capacity)
    q->front = 0;

  return node;
}

int
queueSize(Queue q) {
  return q->size;
}

#define BUFFSIZE 1024
int **
zigzagLevelOrder(struct TreeNode *root, int **columnSize, int *returnSize) {
  int **ans = NULL, *col = NULL, i, idx, size, depth;
  Queue q;
  struct TreeNode *node;

  *returnSize = 0;
  if (root == NULL)
    return NULL;

  q = createQueue(BUFFSIZE);
  enqueue(root, q);

  depth = 0;
  while (!isEmpty(q)) {
    size = queueSize(q);
    for (i = 0; i < size; ++i) {
      node = dequeue(q);
      if (depth % BUFFSIZE == 0) {
        ans = realloc(ans, (depth + BUFFSIZE) * sizeof(int *));
        col = realloc(col, (depth + BUFFSIZE) * sizeof(int));
      }
      if (i == 0) {
        ans[depth] = malloc(size * sizeof(int));
        col[depth] = size;
      }

      idx = depth & 0x1 ? size - 1 - i : i;
      ans[depth][idx] = node->val;

      if (node->left)
        enqueue(node->left, q);
      if (node->right)
        enqueue(node->right, q);
    }

    ++depth;
  }

  disposeQueue(q);
  *returnSize = depth;
  *columnSize = col;
  return ans;
}
