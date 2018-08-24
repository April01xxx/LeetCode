/**
 * Two elements of a binary search tree (BST) are swapped by mistake.
 * Recover the tree without changing its structure.
 *
 * Example 1:
 * Input: [1,3,null,null,2]
 *
 *    1
 *   /
 *  3
 *   \
 *    2
 *
 * Output: [3,1,null,null,2]
 *
 *    3
 *   /
 *  1
 *   \
 *    2
 *
 * Follow up:
 * - A solution using O(n) space is pretty straight forward.
 * - Could you devise a constant space solution?
 *
 * 二叉查找树中有两个节点被错误交换,找到这两个节点并将其恢复正确.
 * 根据follow up里面的提示,先来straight forward方法吧,用一个数组保存二叉查找树
 * 中序遍历的结果,然后遍历数组找到里面错位的元素.
 */
#define BUFFSIZE 1024
void
traversal(struct TreeNode *root, struct TreeNode ***nodes, int *size) {
  if (root == NULL)
    return;

  traversal(root->left, nodes, size);
  if (*size % BUFFSIZE == 0)
    *nodes = realloc(*nodes, (*size + BUFFSIZE) * sizeof(struct TreeNode *));
  (*nodes)[(*size)++] = root;
  traversal(root->right, nodes, size);
}

void
recoverTree(struct TreeNode *root) {
  struct TreeNode **nodes = NULL;
  int i, j, size = 0;

  traversal(root, &nodes, &size);

  i = 0;
  while (i < size - 1 && nodes[i]->val < nodes[i + 1]->val)
    ++i;
  j = size - 1;
  while (j > 0 && nodes[j]->val > nodes[j - 1]->val)
    --j;

  if (nodes) {
    int temp = nodes[i]->val;
    nodes[i]->val = nodes[j]->val;
    nodes[j]->val = temp;
  }
}


/**
 * 题意表明只有两个节点的元素被错误交换,故只要找到这两个节点并将其存储的值交换即可.
 * 我们用一个指针指向第一个不满足二叉查找树性质的节点,当遇到第二个这样的节点时,交换
 * 两节点存储的值即可.
 */
void
traversal(struct TreeNode *node, struct TreeNode **prev,
          struct TreeNode **first, struct TreeNode **second) {
  if (node == NULL)
    return;
  /* 中序遍历寻找被错误交换的节点. */
  traversal(node->left, prev, first, second);

  /**
   * 当前节点值比前面节点的值小,说明前面的节点是被错误交换的节点.
   * 题目假设只有一对节点被错误交换,此处用两个指针分别指向这两个节点.
   */
  if (*prev && node->val <= (*prev)->val) {
    if (*first == NULL)
      *first = *prev;
    /**
     * second指向当前节点,因为可能当前节点就是那个被错误交换的节点.
     * 在遍历的过程中如果再次遇到不满足中序遍历结果的节点,则更新second.
     */
    *second = node;
  }

  /* 中序遍历,当前节点变为右子树的prev. */
  *prev = node;
  traversal(node->right, prev, first, second);
}

void
recoverTree(struct TreeNode *root) {
  struct TreeNode *prev = NULL, *first = NULL, *second = NULL;

  traversal(root, &prev, &first, &second);

  if (first && second) {
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
  }
}

/**
 * 以上两种解法的空间复杂度都是O(n),第二种解法是利用了函数调用自带的栈.要想实现O(1)
 * 的解法,必须找到一种不需要递归或者额外空间就能遍历整个树的方法.要实现这个目的,需要
 * 借助一种称为threaded binary tree(中文普遍译为螺纹树)的数据结构.详细资料可以自行
 * Google.基本思路还是中序遍历BST,在遍历过程中发现错误节点则将其记录下来.关于如何利
 * 用螺纹树中序遍历,可以查看另一道题binary tree inorder traversal的解法.这里有点小
 * 区别:我们需要同时记录前驱和后继节点.
 */
void
recoverTree(struct TreeNode *root) {
  struct TreeNode *prev = NULL, *curr;   /* for threaded binary tree. */
  struct TreeNode *first = NULL, *second = NULL, *p = NULL;

  curr = root;
  while (curr) {
    if (curr->left) {
      prev = curr->left;
      while (prev->right && prev->right != curr)
        prev = prev->right;

      if (prev->right) {
        prev->right = NULL;
        if (curr->val <= p->val) {
          if (first == NULL)
            first = p;
          second = curr;
        }

        p = curr;  /* 接下来向右遍历,当前节点变为前驱. */
        curr = curr->right;
      } else {
        prev->right = curr;
        curr = curr->left;
      }
    } else {
      if (p && curr->val <= p->val) {
        if (first == NULL)
          first = p;
        second = curr;
      }
      p = curr;  /* 接下来向右遍历,当前节点变为前驱. */
      curr = curr->right;
    }
  }

  if (first && second) {
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
  }
}

/**
 * 写在最后,因为题目说只有一对节点被错误交换,上述所有解法在找到第二个错误
 * 节点时就可以返回了,但这里有些地方需要注意:
 * 1. 对于递归的解法,需要再用一个额外变量来表示是否找到第二个错误节点,这样
 *    可以提前返回.
 * 2. 对于利用threaded binary tree的方法,由于在遍历的过程中修改了树的结构,
 *    必须完整遍历后才能恢复,无法提前结束循环.
 */
void
traversal(struct TreeNode *node, struct TreeNode **prev,
          struct TreeNode **first, struct TreeNode **second, 
          struct TreeNode **last) {
  if (node == NULL || *last)  /* 利用last提前结束递归. */
    return;
  /* 中序遍历寻找被错误交换的节点. */
  traversal(node->left, prev, first, second, last);

  /**
   * 当前节点值比前面节点的值小,说明前面的节点是被错误交换的节点.
   * 题目假设只有一对节点被错误交换,此处用两个指针分别指向这两个节点.
   */
  if (*prev && node->val <= (*prev)->val) {
    if (*first == NULL) {
      *first = *prev;
      *second = node;
    } else {
      *last = node;
      return;
    }
  }

  /* 中序遍历,当前节点变为右子树的prev. */
  *prev = node;
  traversal(node->right, prev, first, second, last);
}

void
recoverTree(struct TreeNode *root) {
  struct TreeNode *prev = NULL, *first = NULL, *second = NULL, *last = NULL;

  traversal(root, &prev, &first, &second, &last);

  if (first) {
    last = last ? last : second;
    int temp = first->val;
    first->val = last->val;
    last->val = temp;
  }
}
