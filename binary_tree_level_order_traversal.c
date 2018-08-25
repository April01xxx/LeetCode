/**
 * Given a binary tree, return the level order traversal of its nodes' values.
 * (ie, from left to right, level by level).
 *
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 *     3
 *    / \
 *   9  20
 *     /  \
 *    15   7
 * return its level order traversal as:
 * [
 *   [3],
 *   [9,20],
 *   [15,7]
 * ]
 *
 * 层序遍历二叉树,将每一层的元素用一个数组表示.没啥好说的,利用队列即可.
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

void
reCreateQueue(Queue q) {
  q->capacity <<= 1;
  q->size = 0;
  q->rear = 0;
  q->front = 1;

  q->array = realloc(q->array, q->capacity * sizeof(struct TreeNode *));
}

#define BUFFSIZE 1024
int **
levelOrder(struct TreeNode *root, int **columnSizes, int *returnSize) {
  int **ans = NULL, *col = NULL, count, idx, size;
  Queue q;
  struct TreeNode *node;

  *returnSize = 0;

  q = createQueue(BUFFSIZE);
  enqueue(root, q);

  count = 1;
  idx = size = 0;
  while (!isEmpty(q)) {
    if (idx == count) {
      if (size == 0)
        break;
      col[(*returnSize)++] = size;
      idx = size = 0;
      count <<= 1;
    }

    node = dequeue(q);

    if (node) {

      if (*returnSize % BUFFSIZE == 0) {
        ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int *));
        col = realloc(col, (*returnSize + BUFFSIZE) * sizeof(int));
      }

      if (size == 0)
        ans[*returnSize] = malloc(count * sizeof(int));

      ans[*returnSize][size++] = node->val;

      enqueue(node->left, q);
      enqueue(node->right, q);
    } else {
      enqueue(NULL, q);
      enqueue(NULL, q);
    }

    ++idx;
  }

  *columnSizes = col;
  return ans;
}

/**
 * 上面的解法在树的高度比较高时,耗费内存会剧增.关键原因是利用了每层最多的元素
 * 个数来作为每层结束的标记.为了解决这个问题,在节点的孩子为空时,不能再将其入队
 * 了,这样我们就可以利用NULL指针来标记一层循环的结束.另外每层循环时用一个变量
 * 记录这一层有多少个子节点入队,便于下一层循环分配空间.
 */
#define BUFFSIZE 1024
int **
levelOrder(struct TreeNode *root, int **columnSizes, int *returnSize) {
  int **ans = NULL, *col = NULL, count, idx;
  Queue q;
  struct TreeNode *node;

  *returnSize = 0;
  if (root == NULL)
    return NULL;

  q = createQueue(BUFFSIZE);
  enqueue(root, q);

  count = 1;  /* 记录每层节点个数. */
  idx = 0;
  while (!isEmpty(q)) {
    node = dequeue(q);
    if (node == NULL) {
      /**
       * 如果node为空,表明是新的一层循环.
       */
      ++*returnSize;
      idx = 0;
    } else {
      if (*returnSize % BUFFSIZE == 0) {
        ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int *));
        col = realloc(col, (*returnSize + BUFFSIZE) * sizeof(int));
      }

      if (idx == 0) {
        enqueue(NULL, q); /* idx为0表明是新的一层循环,插入一个空节点表示下层循环的开始. */
        ans[*returnSize] = malloc(count * sizeof(int));
        col[*returnSize] = count;
        count = 0;
      }

      ans[*returnSize][idx++] = node->val;
      if (node->left) {
        ++count;
        enqueue(node->left, q);
      }
      if (node->right) {
        ++count;
        enqueue(node->right, q);
      }
    }
  }

  *columnSizes = col;
  return ans;
}
