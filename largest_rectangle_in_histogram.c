/**
 * Given n non-negative integers representing the histogram's bar height 
 * where the width of each bar is 1, find the area of largest rectangle 
 * in the histogram.
 *
 * Example:
 * Input: [2,1,5,6,2,3]
 * Output: 10
 *
 * 求直方图上最大的矩形面积.和之前那道container with most water有点类似.那道题
 * 只需要考虑两边的边界,而这道题要求矩形边界内的所有元素的值都大于等于两边中的最小值.
 * 令left,right分别指向数组的左右边界,显然此时的面积为:
 * area = (right - left + 1) * min(heights[left, right]);
 * 其中min(heights[left, right])表示从left到right区间范围内的最小值.
 * 令dp[i][j]表示heights[i, j]范围的最大矩形面积,那么显然有以下关系:
 * min(heights[left, right]) = dp[i][j] / (j - i + 1).
 * 所以dp[i][j+1] = min(min(heights[left, right]), heights[j+1]) * (j - i + 2).
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
int
largestRectangleArea(int *heights, int heightsSize) {
  int **dp, i, j, ans;

  dp = (int *)malloc(heightsSize * sizeof(int *));
  for (i = 0; i < heightsSize; ++i)
    dp[i] = (int *)calloc(heightsSize, sizeof(int));

  ans = 0;
  for (i = 0; i < heights; ++i) {
    for (j = i; j < heightsSize; ++j) {
      if (j == i) {
        dp[i][j] = heights[i];
      } else {
        dp[i][j] = min(heights[j], dp[i][j - 1] / (j - i)) * (j - i + 1);
      }
      if (dp[i][j] > ans)
        ans = dp[i][j];
    }
  }

  for (i = 0; i < heightsSize; ++i)
    free(dp[i]);
  free(dp);

  return ans;
}

/**
 * 以上方法在LeetCode上Memory Limit Exceeded.意思很明显,这样做是对的,但还存在
 * 更好的做法.仔细观察上面的状态转移方程,发现只需要常量空间来记录一个区间的最小值.
 * brute force,算法的复杂度为O(n^2).
 */
int
largestRectangleArea(int *heights, int heightsSize) {
  int i, j, min, area, max_area;

  max_area = 0;
  for (i = 0; i < heightsSize; ++i) {
    min = heights[i];
    for (j = i; j < heightsSize; ++j) {
      if (heights[j] < min)
        min = heights[j];
      area = min * (j - i + 1);
      if (area > max_area)
        max_area = area;
    }
  }
  return max_area;
}

/**
 * 仔细观察发现对于每个元素heights[i],它所能形成的最大矩形的面积是:
 * (R - L + 1) * heights[i],其中R是数组中最右边的大于等于heights[i]的下标,
 * L是数组最左边的大于等于heights[i]的下标,这样对于每个i都要遍历一次整个数组,
 * 整个算法的时间复杂度是O(N^2).
 */
int
largestRectangleArea(int *heights, int heightsSize) {
  int i, l, r, max_area, area;

  max_area = 0;
  for (i = 0; i < heightsSize; ++i) {
    for (l = i - 1; l >= 0 && heights[l] >= heights[i]; --l)
      ;
    for (r = i + 1; r < heightsSize && heights[r] >= heights[i]; ++r)
      ;
    area = heights[i] * (r - l - 1);
    if (area > max_area)
      max_area = area;
  }
  return max_area;
}

/**
 * 上面的解法主要耗时是在计算左右边界上,那有没有方法能快速计算呢?还是通过例子来说明.
 * 考虑数组[2,1,5,6,2,3],用两个数组left[n]和right[n]分别保存每个元素点的左右边界.
 *                         -1 0 1 2 3 4 5 6
 *                            2 1 5 6 2 3
 * 1. i=0时,heights[0]=2,此时left[0]=-1,right[0]=1.
 * 2. i=1时,heights[1]=1,此时left[1]=-1,right[1]=6.
 * 3. i=2时,heights[2]=5,此时left[2]=1,right[2]=4.
 * 4. i=3时,heights[3]=6,此时left[3]=2,right[3]=4.
 * 5. i=4时,heights[4]=2,此时left[4]=1,right[4]=6.
 * 6. i=5时,heights[5]=3,此时left[5]=4,right[5]=6.
 * 以i=4,heights[i]=2为例来说明,此时要计算其左边界,目前他的左边是6,6是大于2的,所以
 * 此时继续查找6的左边界,发现6的左边界是5,而5也大于2,故继续查找5的左边界,找到其左边
 * 界是1,而1小于2,故2的左边界是1,此时l=1.查找右边界也同理.简单来说就是利用之前已经
 * 计算过的值来加速查找的过程.
 */
int
largestRectangleArea(int *heights, int heightsSize) {
  int *left, *right, i, max_area, area, l, r;

  left = (int *)malloc(heightsSize * sizeof(int));
  left[0] = -1;
  right = (int *)malloc(heightsSize * sizeof(int));
  right[heightsSize - 1] = heightsSize;

  /* 计算每个元素的左边界. */
  for (i = 1; i < heightsSize; ++i) {
    l = i - 1;
    while (l >= 0 && heights[l] >= heights[i])
      l = left[l];
    left[i] = l;
  }

  /* 计算右边界. */
  for (i = heightsSize - 2; i >= 0; --i) {
    r = i + 1;
    while (r < heightsSize && heights[r] >= heights[i])
      r = right[r];
    right[i] = r;
  }

  /* 遍历数组计算最大矩形面积. */
  max_area = 0;
  for (i = 0; i < heightsSize; ++i) {
    area = heights[i] * (right[i] - left[i] - 1);
    if (area > max_area)
      max_area = area;
  }

  free(left);
  free(right);
  return max_area;
}

/**
 * 还有一种解法也很巧妙,是利用栈来处理.观察整个数组,不难发现,若数组元素都是单调
 * 递增或者单调递减(简单来说就是有序的)情况下,问题很简单:如果是单调递增的,那最大
 * 的面积就是头部元素的值乘以元素个数.单调递减的情况类似.
 */