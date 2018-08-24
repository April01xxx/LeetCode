/**
 * Given a binary tree, return the inorder traversal of its nodes' values.
 *
 * Example:
 * Input: [1,null,2,3]
 *    1
 *     \
 *      2
 *     /
 *    3
 * Output: [1,3,2]
 *
 * 给定一颗二叉树,输出其中序遍历的结果.二叉树的基本操作,对其左右子树分别递归即可.
 * PS: LeetCode的Custom Testcase做的非常棒,这题你自定义测试案例时会同时以二叉
 *     树的形式显示在上方.
 */
#define BUFFSIZE 1024

void
traversal(struct TreeNode *t, int **ans, int *size) {
  if (t == NULL)
    return;

  traversal(t->left, ans, size);
  if (*size % BUFFSIZE == 0)
    *ans = (int *)realloc(*ans, (*size + BUFFSIZE) * sizeof(int));
  (*ans)[(*size)++] = t->val;
  traversal(t->right, ans, size);
}

int *
inorderTraversal(struct TreeNode *root, int *returnSize) {
  int *ans = NULL;

  *returnSize = 0;
  traversal(root, &ans, returnSize);

  return ans;
}

/**
 * 上述解法利用递归,是非常清晰简明的方法.还有一种非常棒的O(1)空间复杂度的方法,
 * 需要借助一种称为threaded binary tree的数据结构,中文译为螺纹树.这里我们要
 * 中序遍历二叉树,也就是左孩子->父节点->右孩子这样的顺序.构造螺纹树,我们将原本
 * 树中左孩子为空的节点的左孩子指向它的前驱节点(中序遍历结果中在该节点前面的那个),
 * 右孩子为空的节点的右孩子指向它的后继节点(中序遍历结果中在该节点后面的那个).
 * 举例说明如下:
 *                             2
 *                            / \
 *                           1   4
 *                              /
 *                             3
 * 上面一棵BST,节点1的左孩子为空,将其指向中序遍历的前驱节点,1的前驱是空.1的右
 * 孩子为空,将其指向中序遍历的后继节点,也就是2,故1->left=null,1->right=2.
 * 同理3->left=2,3-right=4;4->right=null.
 * 看到这里有人可能会担心这种方法会修改树的结构,大可不必.借助螺纹树,虽然遍历
 * 整个树只需要O(1)空间复杂度,但每个节点会被访问两次,在第一次访问时我们修改
 * 节点的空指针,第二次访问时可以将其修复,这样完成遍历后树的结构保持不变.
 * 剩下的问题就是如何构造螺纹树了.根据上面的分析,对于每个节点,我们需要知道它
 * 的前驱和后继节点.对于中序遍历来说有如下结论:
 * 1. 前驱节点是当前节点左子树的最右节点;
 * 2. 后继节点是当前节点右子树的最左节点;
 */
#define BUFFSIZE 1024
int *
inorderTraversal(struct TreeNode *root, int *returnSize) {
  int *ans = NULL;
  struct TreeNode *prev, *curr;

  *returnSize = 0;

  curr = root;
  while (curr) {
    if (curr->left) {
      /**
       * 当前节点左节点非空,接下来要找到其前驱:左子树的最右节点.
       * 上面提到如果右孩子为空,会将其指向后继节点,这里在寻找的
       * 过程中要判断该节点是否已经处理过了.
       */
      prev = curr->left;
      while (prev->right && prev->right != curr)
        prev = prev->right;

      if (prev->right) {
        /**
         * prev->right不为空,那说明它已经指向它的后继节点,进入
         * 这个分支表明是第二次访问该节点,此时应将其右孩子置为空.
         * 同时也说明curr节点前的所有节点已经访问过了,接下来应该
         * 访问curr的右子树了.
         */
        prev->right = NULL;

        if (*returnSize % BUFFSIZE == 0)
          ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
        ans[(*returnSize)++] = curr->val;

        curr = curr->right;
      } else {
        /**
         * 第一次访问该节点,将右孩子指向后继节点.
         */
        prev->right = curr;

        curr = curr->left;
      }
    } else {
      /**
       * 左孩子为空,将其左孩子指向前驱节点.但我们这里只是为了中序遍历,只需要
       * 处理后继节点就可以了:找到左子树的最左节点,然后跟随后继节点即可.
       */
      if (*returnSize % BUFFSIZE == 0)
        ans = realloc(ans, (*returnSize + BUFFSIZE) * sizeof(int));
      ans[(*returnSize)++] = curr->val;

      curr = curr->right;
    }
  }

  return ans;
}