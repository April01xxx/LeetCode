/**
 * Given a binary tree, return the preorder traversal of its nodes' values.
 *
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 *
 * Output: [1,2,3]
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 *
 * 二叉树先序遍历,常规解法就是递归咯.
 */
#define BUFFSIZE 1024

void
traversal(struct TreeNode *root, int **ans, int *returnSize) {
  if (!root)
    return;

  if (*returnSize % BUFFSIZE == 0)
    *ans = realloc(*ans, (*returnSize + BUFFSIZE) * sizeof(int));
  (*ans)[(*returnSize)++] = root->val;
  traversal(root->left, ans, returnSize);
  traversal(root->right, ans, returnSize);
}

int *
preorderTraversal(struct TreeNode *root, int *returnSize) {
  int *ans = NULL;

  *returnSize = 0;
  traversal(root, &ans, returnSize);

  return ans;
}


/**
 * follow up里面提到能不能用循环来实现,之前中序遍历的时候介绍过一种辅助数据结构:
 * 螺纹二叉树(threaded binary tree).此题也可以构造这种辅助树来求解.
 */
#define BUFFSIZE 1024

int *
preorderTraversal(struct TreeNode *root, int *returnSize) {
  struct TreeNode *prev, *curr;
  int *ans = NULL;

  curr = root;
  *returnSize = 0;
  while (curr) {
    if (*returnSize % BUFFSIZE == 0)
      ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
    ans[(*returnSize)++] = curr->val;

    if (curr->left) {
      prev = curr->left;
      while (prev->right)
        prev = prev->right;

      prev->right = curr->right;
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  return ans;
}


/**
 * 上述方法在LeetCode上会报错:Runtime Error,代码逻辑是没问题的,但是在遍历的过程
 * 中上述代码会破坏原有二叉树的结构,猜测可能是LeetCode在验证答案时用到了原先树的
 * 结构导致.既然这样,那在遍历的时候设置一个哨兵,用于恢复原来树的结构.
 */
#define BUFFSIZE 1024
int *
preorderTraversal(struct TreeNode *root, int *returnSize) {
  struct TreeNode *prev, *curr;
  int *ans = NULL;

  curr = root;
  *returnSize = 0;
  while (curr) {
    if (curr->left) {
      prev = curr->left;
      /* curr节点就是哨兵. */
      while (prev->right && prev->right != curr)
        prev = prev->right;

      if (prev->right == NULL) {
        /* prev->right指向NULL,说明是第一次遍历. */
        if (*returnSize % BUFFSIZE == 0)
          ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
        ans[(*returnSize)++] = curr->val;

        prev->right = curr;
        curr = curr->left;
      } else {
        /* prev->right不是NULL,恢复二叉树的结构. */
        prev->right = NULL;
        curr = curr->right;
      }
    } else {
      if (*returnSize % BUFFSIZE == 0)
        ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
      ans[(*returnSize)++] = curr->val;

      curr = curr->right;
    }
  }

  return ans;
}


/**
 * 另外这题也可以借助栈来实现循环遍历:每次循环时,将当前节点的右孩子先入栈,接着是
 * 左孩子入栈.
 */
#define BUFFSIZE 1024
typedef struct {
  int top;
  int size;
  struct TreeNode **array;
} Stack;

Stack *
createStack(int maxsize) {
  Stack *s;

  s = malloc(sizeof(Stack));
  s->top = -1;
  s->size = maxsize;
  s->array = malloc(maxsize * sizeof(struct TreeNode *));

  return s;
}

void
push(Stack *s, struct TreeNode *node) {
  if (s->top == s->size - 1) {
    s->size <<= 1;
    s->array = realloc(s->array, s->size * sizeof(struct TreeNode *));
  }

  s->array[++s->top] = node;
}

struct TreeNode *
pop(Stack *s) {
  return s->array[s->top--];
}

bool
isEmpty(Stack *s) {
  return s->top == -1;
}

int *
preorderTraversal(struct TreeNode *root, int *returnSize) {
  Stack *s;
  int *ans;
  struct TreeNode *node;

  *returnSize = 0;
  if (!root)
    return NULL;

  s = createStack(BUFFSIZE);
  ans = malloc(BUFFSIZE * sizeof(int));
  ans[(*returnSize)++] = root->val;

  if (root->right)
    push(s, root->right);
  if (root->left)
    push(s, root->left);

  while (!isEmpty(s)) {
    node = pop(s);

    if (*returnSize % BUFFSIZE == 0)
      ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
    ans[(*returnSize)++] = node->val;

    if (node->right)
      push(s, node->right);
    if (node->left)
      push(s, node->left);
  }

  return ans;
}