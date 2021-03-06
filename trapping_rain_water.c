/**
 * Given n non-negative integers representing an elevation map where the
 * width of each bar is 1, compute how much water it is able to trap after
 * raining.
 *
 * 题目大意是给定n个竖立的挡板,每个挡板的宽度为1,求着n个挡板能装多少水(面积)?
 * 很显然能装多少水取决于较矮的那块挡板.大致思路是寻找局部极大值,计算两两之间
 * 的面积,从左到右一次,然后从右到左一次,两次之和即为解.
 * 需要注意:若从左到右的时候比较了相等的情况,从右到左就不能再比较相等,否则会出
 * 现重复累加的情况.
 */
int
trap(int *height, int heightSize) {
  int i, area, sum, max, maxi;

  if (heightSize <= 2)
    return 0;

  area = maxi = 0;
  sum = max = height[maxi];
  for (i = 1; i < heightSize; ++i) {
    if (height[i] < max)
      sum += height[i];
    else {
      area += max * (i - maxi) - sum;
      maxi = i;
      max = height[maxi];
      sum = height[i];
    }
  }

  maxi = heightSize - 1;
  sum = max = height[maxi];
  for (i = heightSize - 2; i >= 0; --i) {
    if (height[i] <= max)
      sum += height[i];
    else {
      area += max * (maxi - i) - sum;
      maxi = i;
      max = height[maxi];
      sum = height[i];
    }
  }

  return area;
}

/**
 * 仔细观察上面的解法,遍历了两趟来寻找局部极大值,实际上这个过程一趟遍历就可以
 * 完成,用两个指针分别指向数组头和数组尾部,哪边小则哪边前进,在前进的过程中更新
 * 面积.最终两个指针一定会在整个数组的最大值处相遇.
 */
int
trap(int *height, int heightSize) {
  int left, left_max, right, right_max;
  int area;

  left = 0, right = heightSize - 1;
  left_max = 0, right_max = 0;
  area = 0;
  while (left < right) {
    if (height[left] < height[right]) {
      /* 因为left_max初始化为0,故找到大于left_max的元素时应该更新left_max,
       * 而不是计算面积.
       */
      if (height[left] > left_max)
        left_max = height[left];
      else
        area += left_max - height[left];
      ++left;
    } else {
      if (height[right] > right_max)
        right_max = height[right];
      else
        area += right_max - height[right];
      --right;
    }
  }

  return area;
}
