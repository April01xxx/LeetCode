/**
 * You are given an integer array nums and you have to return a new counts
 * array. The counts array has the property where counts[i] is the number
 * of smaller elements to the right of nums[i].
 *
 * Example:
 *
 * Input: [5,2,6,1]
 * Output: [2,1,1,0]
 * Explanation:
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 *
 * 给定一个整数数组nums,求每个元素nums[i]右边小于它的元素个数.
 * 最直观的做法是针对每个元素遍历数组.
 */
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int sz = nums.size();
        vector<int> counter(sz);

        for (int i = 0; i < sz - 1; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                if (nums[j] < nums[i])
                    ++counter[i];
            }
        }
        return counter;
    }
};

/**
 * 上述解法的时间复杂度是O(n^2),空间复杂度为O(1).虽然AC了,但效率低下.
 * 后来想了下,如果将原数组排序,但是排序的时候记录下来每个元素原来在数
 * 组中的位置,例如数组[5,2,6,1]排序后得到[1,2,5,6]每个元素对应的原始
 * 下标为[3,1,0,2].现在要找出在5(index=0)的右边有多少个小于它的元素,
 * 排序后5位于第2的位置,且前面元素的下标均大于5的下标0,故有2个元素.
 *
 * 我想到这里的时候就没有太好的思路,还是要遍历才能找到具体的个数.看了
 * 下讨论区,有大牛基于这个分析进一步深入,通过merge sort解决了.思路如
 * 下:
 * 1. 首先理解问题的本质,对元素nums[i]而言,右边小于nums[i]的元素个数
 *    实际上就是稳定排序算法中需要移动到nums[i]左边的元素个数.
 * 2. 这里用归并排序merge sort,每次归并分为两组left part和right part.
 * 3. 假定left part和right part都已经有序,显然right part中的所有元素
 *    都在left part中的右边.在归并的过程中,对于每个left part中的元素,
 *    统计right part中有多少个在他们前面.
 * 以数组[5,2,6,1]的归并排序为例说明:
 * left: [5,2]            right: [6,1]
 * left:[5] right: [2]    left:[6] right[1]
 * [5]和[2]进行归并,因为5>2,故元素5右边比它小的数加1.归并之后得到[2(0),5(1)].
 * [6]和[1]归并同理得到[1(0),6(1)].接下来对[2(0),5(1)]和[1(0),6(1)]进行归并.
 * 因为2>1,所以2的右边比它小的数加1,得到[1(0),2(1)],接着轮到元素5,此时发现右边
 * 已经有1个元素被归并(元素1),故5的右边比它小的数要加上此时右边已经归并的元素个数,
 * 得到[1(0),2(1),5(2)],最后剩下元素6.最终得到[1(0),2(1),5(2),6(1)].
 * 括号中的值即为所求的答案.
 *
 * 以上是基于归并排序,还有一种方式是根据bit位比较(由高到低),思路都是一样的:
 * https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76729/
 */
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> smaller(nums.size());
        vector<int> indices;

        for (int i = 0; i < nums.size(); ++i)
            indices.push_back(i);

        mergeSort(nums, indices, 0, nums.size() - 1, smaller);
        return smaller;
    }

private:
    void mergeSort(vector<int>& nums, vector<int>& indices, int left, int right,
                   vector<int>& smaller) {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSort(nums, indices, left, mid, smaller);
        mergeSort(nums, indices, mid + 1, right, smaller);

        /* 合并并更新smaller. */
        merge(nums, indices, left, right, smaller);
    }

    /**
     * 归并排序,并在合并的过程中统计每个元素右边有多少个元素移到了它的左边.
     * 需要注意的是,我们保存的是排序后的元素的下标,这样便于更新smaller. */
    void merge(vector<int>& nums, vector<int>& indices, int l, int r,
               vector<int>& smaller) {
        int i = l, m = l + (r - l) / 2, j = m + 1;
        int count = 0;          // 统计右半部分有多少个元素已经被归并.
        vector<int> tmp;        // 临时保存排序后的下标.

        // 合并两个有序的数组,i指向左半部分,j指向右半部分.
        while (i <= m || j <= r) {
            if ((j == r + 1) ||
                    (i <= m && nums[indices[i]] <= nums[indices[j]])) {
                // 左半部分当前元素小于等于右半部分当前元素,此时在右边比它小
                // 的元素个数就是右半部分中已经被归并的元素个数.
                tmp.push_back(indices[i]);
                smaller[indices[i]] += count;
                ++i;
            } else if (j <= r) {
                tmp.push_back(indices[j]);
                ++j;
                ++count;
            }
        }

        // 将排序结果覆盖indices.
        for (int k = l; k <= r; ++k)
            indices[k] = tmp[k - l];
    }
};


/**
 * 还一种做法是基于BST的.从右向左遍历数组,将对应元素插入到BST中,同时
 * 维护相关信息:
 * 1. 创建一棵空树tree.每个节点包含三个信息:val,count和dup.其中val表示该
 *    节点的值,count表示小于该节点的节点数(左子树节点数),dup表示等于该节点的个数.
 * 2. 从右向左遍历数组将每个元素插入到树中,插入时维护count和dup信息:
 *    a. 若插入元素nums[i]大于节点node->val,因为nums[i]肯定在node->val
 *       的左边,故沿右子树继续查找且累加(node->count+node->dup).
 *    b. 若插入元素nums[i]小于节点node->val,累加node->count,沿左子树查找.
 *    c. 若两者相等,累加node->dup.
 * https://leetcode.com/problems/count-of-smaller-numbers-after-self/discuss/76580/
 */
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> ans(nums.size());
        Node *root = nullptr;

        for (int i = nums.size() - 1; i >= 0; --i)
            insert(root, nums, i, 0, ans);
        return ans;
    }

private:
    struct Node {
        int val, count = 0, dup = 1;
        Node *left, *right;

        Node(int num) : val(num), left(NULL), right(NULL) {}
    };

    void insert(Node *&root, vector<int>& nums, int pos, int count,
                vector<int>& ans) {
        if (!root) {
            root = new Node(nums[pos]);
            ans[pos] = count;
        } else if (root->val == nums[pos]) {
            ++root->dup;
            ans[pos] = count + root->count;
        } else if (root->val < nums[pos]) {
            insert(root->right, nums, pos,
                   count + root->count + root->dup, ans);
        } else {
            ++root->count;
            insert(root->left, nums, pos, count, ans);
        }
    }
};

/**
 * 此题还有一种解法是利用线段树segment tree,思路如下:
 * 1. 扫描整个数组nums,得到数组中元素的范围[min,max],这个范围就是线段树
 *    的区间,创建一棵线段树tree表示落在该区间内的元素个数.
 * 2. 从右向左遍历数组nums,对每一个元素nums[i]在线段树tree中查找落在区间
 *    [min, nums[i]-1]范围内的元素个数count,因为我们是从右向左遍历,故
 *    count就是我们求的nums[i]右边比它小的元素的个数;
 * 3. 将nums[i]插入线段树tree中,插入时更新路径上每个节点区间包含的元素个数.
 * struct SegmentTreeNode {
 *     int left, right; // 区间范围边界
 *     int count;       // 落在该区间内的元素个数
 *     SegmentTreeNode *left, *right;   // 左右子树指针
 * };
 * 可以预见的是,若nums[i]数组非常稀疏:例如min = INT_MIN, max = INT_MAX,
 * 但是数组元素非常少,那将会浪费很多空间.此外也要注意溢出问题:nums[i]-1可能
 * 会溢出.
 */