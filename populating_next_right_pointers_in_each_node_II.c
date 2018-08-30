/**
 * Given a binary tree
 * struct TreeLinkNode {
 *   TreeLinkNode *left;
 *   TreeLinkNode *right;
 *   TreeLinkNode *next;
 * }
 * Populate each next pointer to point to its next right node. If there is no
 * next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 *
 * Note:
 * - You may only use constant extra space.
 * - Recursive approach is fine, implicit stack space does not count as extra
 *   space for this problem.
 *
 * Example:
 * Given the following binary tree,
 *
 *      1
 *    /  \
 *   2    3
 *  / \    \
 * 4   5    7
 * After calling your function, the tree should look like:
 *
 *      1 -> NULL
 *    /  \
 *   2 -> 3 -> NULL
 *  / \    \
 * 4-> 5 -> 7 -> NULL
 *
 * 这题相比上一题难度增加,因为二叉树不再是完全二叉树,在给next节点赋值时,要做额外
 * 判断.
 */
void
connect(struct TreeLinkNode *root) {
  struct TreeLinkNode *node;

  if (root == NULL)
    return;

  if (root->left) {
    if (root->right) {
      root->left->next = root->right;
    } else {
      /* 当前节点的右孩子为NULL,向右遍历找到第一个不为空的节点. */
      node = root->next;
      while (root->left->next == NULL && node) {
        if (node->left)
          root->left->next = node->left;
        else if (node->right)
          root->left->next = node->right;

        node = node->next;
      }
    }
  }

  if (root->right) {
    node = root->next;
    while (root->right->next == NULL && node) {
      if (node->left)
        root->right->next = node->left;
      else if (node->right)
        root->right->next = node->right;

      node = node->next;
    }
  }

  /**
   * 右孩子如果存在,则左孩子的next指向右孩子,否则next要指向右边
   * 第一个非空节点,故此处要先处理右孩子的next指针.顺序不能颠倒.
   */
  connect(root->right);
  connect(root->left);
}


/**
 * 循环迭代实现.
 */
void
connect(struct TreeLinkNode *root) {
  struct TreeLinkNode *node, *head = NULL, *next;

  node = root;
  while (node) {
    if (head == NULL) {
      if (node->left)
        head = node->left;
      else
        head = node->right;
    }

    if (node->left) {
      if (node->right)
        node->left->next = node->right;
      else {
        next = node->next;
        while (node->left->next == NULL && next) {
          if (next->left)
            node->left->next = next->left;
          else if (next->right)
            node->left->next = next->right;

          next = next->next;
        }
      }
    }

    if (node->right) {
      next = node->next;
      while (node->right->next == NULL && next) {
        if (next->left)
          node->right->next = next->left;
        else if (next->right)
          node->right->next = next->right;

        next = next->next;
      }
    }

    if (node->next == NULL) {
      node = head;
      head = NULL;
    } else
      node = node->next;
  }
}


/**
 * 上面的实现还存在优化的空间,不过总体思路还是一样的,层序遍历的方式来
 * 处理所有节点.
 */
void
connect(struct TreeLinkNode *root) {
  struct TreeLinkNode head, *tail;

  head.next = NULL;
  tail = &head;
  while (root) {
    if (root->left) {
      tail->next = root->left;
      tail = tail->next;
    }

    if (root->right) {
      tail->next = root->right;
      tail = tail->next;
    }

    if (root->next == NULL) {
      root = head.next;
      head.next = NULL;   /* 必须置为NULL,否则最后一层死循环. */
      tail = &head;
    } else {
      root = root->next;
    }
  }
}


/**
 * 递归的修改方法同上,逐层处理.
 */
void
connect(struct TreeLinkNode *root) {
  struct TreeLinkNode *next = NULL, *node;

  if (root == NULL)
    return;

  /**
   * 找到这一层右孩子后面第一个非空节点.
   */
  node = root->next;
  while (next == NULL && node) {
    if (node->left)
      next = node->left;
    else if (node->right)
      next = node->right;

    node = node->next;
  }

  if (root->right) {
    root->right->next = next;
    next = root->right;
  }
  if (root->left)
    root->left->next = next;

  connect(root->right);
  connect(root->left);
}