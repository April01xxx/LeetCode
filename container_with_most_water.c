#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 求两条边,使得两条边和x轴形成的容器装水最多.
 * 暴力破解法: 找出所有的组合的面积.
 * 此方法超时.
 */

#define min(x, y) ((x) > (y) ? (y) : (x))

int
maxArea1(int *height, int heightSize) {
  size_t i, j;
  int area, max_area = 0;

  for (i = 0; i < heightSize; ++i) {
    for (j = i + 1; j < heightSize; ++j) {
      area = (j - i) * min(height[i], height[j]);
      if (area > max_area)
        max_area = area;
    }
  }
  return max_area;
}

/*
 * 稍加分析发现上面的暴力破解法中可能计算了很多不必计算的点.
 * 令S[i,j]表示数组a[0:n-1]中最大的面积,其中i,j表示数组元素的下标,0<=i<j<=n-1.
 * 显然对于所有的k(0<=k<i)都有a[k] < a[i],因为若a[k]>=a[i]则S[k,j] > S[i,j],这与
 * 假设矛盾;同理可以推出对于所有的j<m<=n-1都有a[m] < a[j].
 */
int
maxArea2(int *height, int heightSize) {
  int *start, *end;
  int i, j, m, n;
  int level;
  int max_area, area;

  if (heightSize < 2)
    return 0;
  else if (heightSize == 2)
    return min(height[0], height[1]);

  start = malloc(heightSize * sizeof(int));
  *start = 0;

  end = malloc(heightSize * sizeof(int));
  memset(end + 1, -1, heightSize - 1);
  *end = heightSize - 1;

  level = height[*start];
  m = 1;
  for (i = 1; i < heightSize; ++i) {
    if (height[i] > level) {
      start[m++] = i;
      level = height[i];
    }
  }

  level = height[*end];
  n = 1;
  for (i = heightSize - 2; i >= 0; --i) {
    if (height[i] > level) {
      end[n++] = i;
      level = height[i];
    }
  }

  max_area = area = 0;
  for (i = 0; i < m; ++i) {
    for (j = 0; j < n; ++j) {
      /* start[i]一定是小于等于end[j]的 */
      area = (end[j] - start[i]) * min(height[end[j]], height[start[i]]);
      printf("[%d, %d] [%d, %d] : %d\n", start[i], height[start[i]],
          end[j], height[end[j]], area);
      if (max_area < area)
        max_area = area;
    }
  }

  free(start);
  free(end);
  return max_area;
}

/*
 * 官方解答:
 * 注意到面积的大小由两条直线之间的距离和较短的直线决定.
 * 对于两条直线:i,j,其中0<=i<j<N,若a[i]<a[j],则面积area = (j-i)*a[i];
 * 在采用暴力破解法时,对于每一个i,会遍历所有的j,然而仔细观察发现,若出现某个a[j]
 * 大于a[i],则对于任意m<j的直线的计算是多余的,这是因为:
 * 1. 对于m<j, m-i < j-i;
 * 2. 面积由更短的直线决定,无论a[m]是大于等于a[i]还是小于a[i],其面积都必定小于
 * (j-i)*a[i];
 * 所以此时应该移动i,才有可能使得面积增大.
 */
int
maxArea(int *height, int heightSize) {
  int i, j;
  int area, maxarea;

  maxarea = 0;
  for (i = 0, j = heightSize - 1; i < j; ) {
    if (height[i] < height[j]) {
      area = (j - i) * height[i];
      ++i;
    } else {
      area = (j - i) * height[j];
      --j;
    }
    if (area > maxarea)
      maxarea = area;
  }

  return maxarea;
}

int
main()
{
  int a[] = {1, 2, 1, 3, 7, 9, 3, 2, 1, 7, 5};

  printf("%d\n", maxArea(a, 11));

  return 0;
}
