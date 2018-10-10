/**
 * Implement an iterator over a binary search tree (BST). Your iterator will be
 * initialized with the root node of a BST. Calling next() will return the next
 * smallest number in the BST.
 *
 * Note: next() and hasNext() should run in average O(1) time and uses O(h)
 * memory, where h is the height of the tree.
 *
 * 要求实现一个二叉查找树迭代器,这个迭代器有两个方法:
 * 1. hasNext(): 是否存在下一个最小的元素.
 * 2. next(): 返回下一个最小的元素的值.
 * 这两个方法的时间复杂度都是O(1),空间复杂度是O(h),其中h为树的高度.
 * 如果空间复杂度没有限制,我们可以用一个数组来保存BST中序遍历的结果,迭代器内部用一个
 * 指针指向该数组的头部即可.
 */

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct BSTIterator {
  int *elem;
  int curr;
  int size;
};

#define BUFFSIZE 1024

void traversal(struct TreeNode *root, int **elem, int *size) {
  if (!root)
    return;

  traversal(root->left, elem, size);
  if (*size % BUFFSIZE == 0)
    *elem = realloc(*elem, (*size + BUFFSIZE) * sizeof(int));
  (*elem)[(*size)++] = root->val;
  traversal(root->right, elem, size);
}

struct BSTIterator *bstIteratorCreate(struct TreeNode *root) {
  struct BSTIterator *iter;

  iter = malloc(sizeof(struct BSTIterator));
  iter->elem = NULL;
  iter->size = 0;
  iter->curr = 0;

  traversal(root, &iter->elem, &iter->size);

  return iter;
}

/** @return whether we have a next smallest number */
bool bstIteratorHasNext(struct BSTIterator *iter) {
  return iter->curr < iter->size;
}

/** @return the next smallest number */
int bstIteratorNext(struct BSTIterator *iter) {
  return iter->elem[iter->curr++];
}

/** Deallocates memory previously allocated for the iterator */
void bstIteratorFree(struct BSTIterator *iter) {
  if (iter) {
    free(iter->elem);
    free(iter);
  }
}

/**
 * Your BSTIterator will be called like this:
 * struct BSTIterator *i = bstIteratorCreate(root);
 * while (bstIteratorHasNext(i)) printf("%d\n", bstIteratorNext(i));
 * bstIteratorFree(i);
 */

/**
 * 上述做法用了O(n)的空间来保存BST中的每个元素.
 * 其实这个问题本质上是对BST进行中序遍历,既然此题要求空间复杂度是O(h),那就只能
 * 存储指针,如果借助threaded binary tree的思路,我们要保存每个叶子节点的指针,对
 * 于一棵高度为h的二叉树而言,其叶子节点个数为2^(h-1),也不符合题目要求.
 *
 * 上面的解法在中序遍历时利用了递归,也就是借用了系统的栈,算法的空间复杂度是O(h).
 * 我们也可以用一个大小为h的栈来解决问题,初始时栈中的元素为BST的最左路径上的节点
 * 的指针,栈顶元素为BST中最小的元素.
 * 1. 若栈非空,则hashNext()为真.
 * 2. next()返回栈顶元素
 * 在每个元素出栈时,判断其右孩子是否为空,若非空则找到右子树中最小的元素.
 */
typedef struct {
  struct TreeNode **array;
  int size;
  int top;
} Stack;

Stack *
stackCreate(int size) {
  Stack *s;

  s = malloc(sizeof(Stack));
  s->top = -1;
  s->size = size;
  s->array = malloc(size * sizeof(struct TreeNode *));

  return s;
}

void
stackFree(Stack *s) {
  if (s) {
    free(s->array);
    free(s);
  }
}

bool
stackEmpty(Stack *s) {
  return s->top == -1;
}

void
stackPush(Stack *s, struct TreeNode *node) {
  if (s->top == s->size - 1) {
    s->size <<= 1;
    s->array = realloc(s->array, s->size * sizeof(struct TreeNode *));
  }

  s->array[++s->top] = node;
}

struct TreeNode *
stackPop(Stack *s) {
  return s->array[s->top--];
}

struct BSTIterator {
  Stack *s;
};

void
find_left(Stack *s, struct TreeNode *root) {
  while (root) {
    stackPush(s, root);
    root = root->left;
  }
}

struct BSTIterator *bstIteratorCreate(struct TreeNode *root) {
  struct BSTIterator *iter;
  struct TreeNode *node = root;
  int height = 0;

  iter = malloc(sizeof(struct BSTIterator));
  iter->s = stackCreate(1024);
  find_left(iter->s, root);

  return iter;
}

/** @return whether we have a next smallest number */
bool bstIteratorHasNext(struct BSTIterator *iter) {
  return !stackEmpty(iter->s);
}

/** @return the next smallest number */
int bstIteratorNext(struct BSTIterator *iter) {
  struct TreeNode *node;

  node = stackPop(iter->s);
  /**
   * next()方法调用了find_left寻找下一个最小元素,对于单次next()调用
   * 时间复杂度不是O(1),但从整体上来看,每个节点在遍历的过程中只会访问
   * 一次,故总体而言,平均时间复杂度是O(1).
   */
  find_left(iter->s, node->right);

  return node->val;
}

/** Deallocates memory previously allocated for the iterator */
void bstIteratorFree(struct BSTIterator *iter) {
  if (iter) {
    stackFree(iter->s);
    free(iter);
  }
}