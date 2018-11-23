/**
 * Given an integer array nums, find the sum of the elements between indices i
 * and j (i ≤ j), inclusive.
 *
 * The update(i, val) function modifies nums by updating the element at index i
 * to val.
 *
 * Example:
 *
 * Given nums = [1, 3, 5]
 *
 * sumRange(0, 2) -> 9
 * update(1, 2)
 * sumRange(0, 2) -> 8
 *
 * Note:
 * The array is only modifiable by the update function.
 * You may assume the number of calls to update and sumRange function is
 * distributed evenly.
 *
 * 这题是上一题的变种,之前那道题,数组是不可变的,故可以事先将区间的和记录下来.
 * 现在数组是可变的,若采用事先记录的方式,那每次调用update时要同步修改.此外为
 * 了知道应该改动的值,需要将原先的对应下标处的元素值记下来.
 */
class NumArray {
public:
    NumArray(vector<int> nums) : copy(nums), sum(nums.size() + 1) {
        for (int i = 1; i <= nums.size(); ++i)
            sum[i] = sum[i - 1] + nums[i - 1];
    }

    void update(int i, int val) {
        int diff = val - copy[i];
        copy[i] = val;
        for (int j = i + 1; j < sum.size(); ++j)
            sum[j] += diff;
    }

    int sumRange(int i, int j) {
        return sum[j + 1] - sum[i];
    }

private:
    vector<int> sum;
    vector<int> copy;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */

/**
 * 上述做法虽然能解决问题,但基本上是暴力破解了,有没有办法像sumRange一样,输入
 * 一个区间能以O(1)的时间复杂度返回这个区间调整的差值呢?自己想了半天没想到好
 * 的数据结构来表达这种信息,看了下这题的tag,发现是segment tree,顿时恍然.
 * 以输入为[0,9,5,7,3]为例可以构造一棵segment tree如下:
 *                           24(0:4)
 *                      /              \
 *                   14(0:2)        10(3:4)
 *                    /   \           /   \
 *                 9(0:1) 5(2:2)   7(3:3) 3(4:3)
 *                 /    \
 *               0(0:0) 9(1:1)
 * 当区间的首尾坐标相等时表示这个节点是一个叶子节点.
 * 为了满足题目的要求,segment tree的每个节点数据结构如下:
 * struct segmentTreeNode {
 *     int sum;     // 表示子树的和
 *     int lo;      // 区间左边界
 *     int hi;      // 区间右边界
 *     struct segmentTreeNode *left;    // 左孩子
 *     struct segmentTreeNode *right;   // 右孩子
 * };
 *
 * 创建segment tree的伪代码如下:
 * def segmentTreeCreate(array, lo, hi):
 *     segmentTreeNode *node = new SegmentTreeNode
 *
 *     node->lo = lo
 *     node->hi = hi
 *     if (lo == hi)
 *         node->sum = array[lo]
 *         return node
 *     mid = lo + (hi - lo) / 2
 *     node->left = segmentTreeCreate(array, lo, mid)
 *     node->right = segmentTreeCreate(array, mid+1, hi)
 *     node->sum = node->left->sum + node->right->sum;
 *     return node;
 *
 * 接下来实现segment tree的range查询:
 * def sumRange(root, i, j):
 *     if (i == root->lo && j == root->hi)
 *         return root->sum
 *
 *     mid = root->lo + (root->hi - root->lo) / 2
 *     if (j <= mid)
 *         return sumRange(root->left, i, j);
 *     else if (i > mid)
 *         return sumRange(root->right, i, j);
 *     else
 *         return sumRange(root->left, i, mid)
 *                 + sumRange(root->right, mid + 1, j);
 *
 * 修改update的方法如下:
 * def update(root, i, val):
 *     if (root->lo == i && root->hi == i)
 *         root->sum = val
 *         return
 *     mid = root->lo + (root->hi - root->lo) / 2
 *     if (i <= mid)
 *         update(root->left, i, val)
 *     else
 *         update(root->right, i, val)
 *     root->sum = root->left->sum + root->right->sum
 */
typedef struct NumArray {
    int sum;
    int lo;
    int hi;
    struct NumArray *left, *right;
} NumArray;

NumArray *segmentTreeCreate(int *a, int lo, int hi) {
    NumArray *root = malloc(sizeof(*root));

    root->lo = lo;
    root->hi = hi;
    root->left = root->right = NULL;
    if (lo == hi) {
        root->sum = a[lo];
        return root;
    }
    int mid = lo + (hi - lo) / 2;
    root->left = segmentTreeCreate(a, lo, mid);
    root->right = segmentTreeCreate(a, mid + 1, hi);
    root->sum = root->left->sum + root->right->sum;
    return root;
}

NumArray* numArrayCreate(int* nums, int numsSize) {
    if (numsSize <= 0)
        return NULL;
    return segmentTreeCreate(nums, 0, numsSize - 1);
}

void numArrayUpdate(NumArray* obj, int i, int val) {
    int mid;

    if (obj->lo == i && obj->hi == i) {
        obj->sum = val;
        return;
    }
    mid = obj->lo + (obj->hi - obj->lo) / 2;
    if (i > mid)
        numArrayUpdate(obj->right, i, val);
    else
        numArrayUpdate(obj->left, i, val);
    obj->sum = obj->left->sum + obj->right->sum;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    int mid;

    if (obj->lo == i && obj->hi == j)
        return obj->sum;

    mid = obj->lo + (obj->hi - obj->lo) / 2;
    if (j <= mid)
        return numArraySumRange(obj->left, i, j);
    else if (i > mid)
        return numArraySumRange(obj->right, i, j);
    else
        return numArraySumRange(obj->left, i, mid)
               + numArraySumRange(obj->right, mid + 1, j);
}

void numArrayFree(NumArray* obj) {
    if (obj) {
        numArrayFree(obj->left);
        numArrayFree(obj->right);
        free(obj);
    }
}