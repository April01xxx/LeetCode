/**
 * Given a binary tree, check whether it is a mirror of itself (ie, symmetric
 * around its center).
 * For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
 *
 *     1
 *    / \
 *   2   2
 *  / \ / \
 * 3  4 4  3
 * But the following [1,2,2,null,3,null,3] is not:
 *     1
 *    / \
 *   2   2
 *    \   \
 *    3    3
 * Note:
 * Bonus points if you could solve it both recursively and iteratively.
 * 给定一棵二叉树,判断是否关于根节点对称.
 * 先来递归解法吧,判断是否关于根节点对称,那就是判断其左右子树是否对称.
 */
bool
symmetric(struct TreeNode *left, struct TreeNode *right) {
  if (left == NULL)
    return right == NULL;
  else if (right == NULL)
    return left == NULL;

  if (left->val != right->val)
    return false;

  if (!symmetric(left->left, right->right))
    return false;
  return symmetric(left->right, right->left);
}

bool
isSymmetric(struct TreeNode *root) {
  if (root == NULL)
    return true;

  return symmetric(root->left, root->right);
}

/**
 * 迭代的写法自己想的是利用层序遍历得到每一层的结果,然后从两头开始比较每个
 * 元素是否相等.后来看了下讨论区,发现不用这么复杂.核心思想还是利用队列进行
 * 层序遍历,但是在遍历时,并不是按顺序从左到右存放元素,而是将左孩子的右孙子
 * 和右孩子的左孙子放在一起,每次出队两个元素,比较其是否相等.
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
  if (isFull(q)) {
    q->capacity *= 2;
    q->array = realloc(q->array, q->capacity * sizeof(struct TreeNode *));
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

bool
isSymmetric(struct TreeNode *root) {
  Queue q;
  struct TreeNode *t1, *t2;

  if (root == NULL)
    return true;

  q = createQueue(1024);
  enqueue(root->left, q);
  enqueue(root->right, q);

  while (!isEmpty(q)) {
    t1 = dequeue(q);
    t2 = dequeue(q);

    if (t1 == NULL && t2 == NULL)
      continue;
    if (t1 == NULL || t2 == NULL || t1->val != t2->val) {
      disposeQueue(q);
      return false;
    }

    /**
     * 入队时将要比较的两个元素放在一起.
     */
    enqueue(t1->left, q);
    enqueue(t2->right, q);
    enqueue(t1->right, q);
    enqueue(t2->left, q);
  }

  disposeQueue(q);
  return true;
}
