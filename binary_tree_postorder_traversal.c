/**
 * Given a binary tree, return the postorder traversal of its nodes' values.
 *
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 *
 * Output: [3,2,1]
 * Follow up: Recursive solution is trivial, could you do it iteratively?
 *
 * 二叉树后序遍历,先来常规的递归解法.
 */
#define BUFFSIZE 1024
void
traversal(struct TreeNode *root, int **ans, int *returnSize) {
  if (!root)
    return;

  traversal(root->left, ans, returnSize);
  traversal(root->right, ans, returnSize);

  if (*returnSize % BUFFSIZE == 0)
    *ans = realloc(*ans, (*returnSize + BUFFSIZE) * sizeof(int));
  (*ans)[(*returnSize)++] = root->val;
}

int *
postorderTraversal(struct TreeNode *root, int *returnSize) {
  int *ans = NULL;

  *returnSize = 0;
  traversal(root, &ans, returnSize);

  return ans;
}


/**
 * follow up里面提到能否用循环解决,这里同样借助于螺纹二叉树(threaded binary tree),
 * 注意在遍历的时候恢复二叉树的结构.
 */
#define BUFFSIZE 1024

void
reverse(struct TreeNode *head, struct TreeNode *tail) {
  struct TreeNode *t, *node, *next;

  t = head;
  node = head->right;
  while (t != tail) {
    next = node->right;
    node->right = t;

    t = node;
    node = next;
  }
}

int *
postorderTraversal(struct TreeNode *root, int *returnSize) {
  struct TreeNode *prev, *curr, dummy;
  int *ans = NULL;

  *returnSize = 0;
  dummy.left = root;
  dummy.right = NULL;
  curr = &dummy;  /* dummy哑结点,为了保证右子树的最右节点能指向根节点. */
  while (curr) {
    if (curr->left) {
      prev = curr->left;
      while (prev->right && prev->right != curr)
        prev = prev->right;

      if (prev->right == NULL) {
        /* 第一次遍历该节点. */
        prev->right = curr;
        curr = curr->left;
      } else {
        /**
         * 第二次遍历该节点,打印输出并恢复二叉树的结构.
         * 注意到我们要求后序遍历,故在遍历时需要先反转这部分节点,
         * 或者借助于栈来实现.
         * 此时prev->right == curr,我们将curr->left作为头节点head,
         * 链表上的元素是节点的右孩子,prev作为链表尾节点,将这个单向链表就地反转.
         */
        reverse(curr->left, prev);

        /* 后续遍历. */
        struct TreeNode *node = prev;
        while (1) {
          if (*returnSize % BUFFSIZE == 0)
            ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
          ans[(*returnSize)++] = node->val;

          if (node == curr->left)
            break;
          node = node->right;
        }
        /* 恢复二叉树结构. */
        reverse(prev, curr->left);
        prev->right = NULL;
        curr = curr->right;
      }
    } else {
      curr = curr->right;
    }
  }

  return ans;
}


/**
 * 此题也可以借助栈来实现循环迭代求解.
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

struct TreeNode *
top(Stack *s) {
  return s->array[s->top];
}

bool
isEmpty(Stack *s) {
  return s->top == -1;
}


/**
 * 要实现后序遍历,也就是说在访问右子树之前需要先把该节点的左子树全部遍历一次,
 * 我们可以先将该节点入栈,先处理它的左子树,当左子树为空时,表明已经到达最左边
 * 的节点,此时开始处理栈中的元素.若栈顶元素的右孩子不为空,则将其右孩子入栈,
 * 这里需要注意,为了避免死循环,需要设置一个哨兵sentinel来标记当前已经访问过
 * 的子树.
 */
int *
postorderTraversal(struct TreeNode *root, int *returnSize) {
  Stack *s;
  struct TreeNode *node, *sentinel = NULL, *curr = root;
  int *ans = NULL;

  *returnSize = 0;
  s = createStack(BUFFSIZE);

  while (curr || !isEmpty(s)) {
    if (curr) {
      push(s, curr);
      curr = curr->left;
    } else {
      node = top(s);
      /**
       * 哨兵sentinel标记已经访问过的右子树的根节点.若节点的右子树已经全部
       * 遍历了,那么接着就该遍历这个节点.
       */
      if (node->right && node->right != sentinel) {
        /**
         * 这两行代码可以和外层的循环合并:
         * push(s, node->right);
         * curr = node->right->left;
         * 这与
         * curr = node->right;
         * 这行代码是等价的,因为接下来进入182行的if分支,会将curr节点入栈.
         */
        curr = node->right;
      } else {
        if (*returnSize % BUFFSIZE == 0)
          ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
        ans[(*returnSize)++] = node->val;

        sentinel = pop(s);
      }
    }
  }

  return ans;
}