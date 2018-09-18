/**
 * There are N children standing in a line. Each child is assigned a rating
 * value. You are giving candies to these children subjected to the following
 * requirements:
 * 1. Each child must have at least one candy.
 * 2. Children with a higher rating get more candies than their neighbors.
 * What is the minimum candies you must give?
 * Example 1:
 * Input: [1,0,2]
 * Output: 5
 * Explanation: You can allocate to the first, second and third child with 2, 1,
 *             2 candies respectively.
 *
 * Example 2:
 * Input: [1,2,2]
 * Output: 4
 * Explanation: You can allocate to the first, second and third child with 1, 2,
 *              1 candies respectively. The third child gets 1 candy because it
 *              satisfies the above two conditions.
 *
 * 注意上述第二个例子,第三个孩子只用分一颗糖即可,因为条件2是说得分更高的孩子必须要
 * 比邻近的得分低的孩子的糖果多,而第二个孩子也是2分,因此第三个孩子的得分不比第二个
 * 孩子高.
 */
int
candy(int *ratings, int ratingsSize) {
  int count, i, *dp;

  dp = malloc(ratingsSize * sizeof(int));
  for (i = 0; i < ratingsSize; ++i)
    dp[i] = 1;

  for (i = 1; i < ratingsSize; ++i) {
    if (ratings[i] > ratings[i - 1])
      dp[i] = dp[i - 1] + 1;
  }

  for (i = ratingsSize - 2; i >= 0; --i) {
    if (ratings[i] > ratings[i + 1] && dp[i] <= dp[i + 1])
      dp[i] = dp[i + 1] + 1;
  }

  count = 0;
  for (i = 0; i < ratingsSize; ++i)
    count += dp[i];

  free(dp);
  return count;
}


/**
 * 上述方法采用两趟遍历,求得了最后所需的最小糖果数.
 * 仔细观察发现,逻辑还可以简化:
 * 若数组中元素严格单调则糖果数累加,考虑例子[2,1,0,2,8,5,9,3,5,6,7,5,6,5,5]:
 * 1. 初始时,count = 1;
 * 2. 下标为1时,ratings[1] < ratings[0],此时递减的元素是两个,故count += 2;
 * 3. 下标为2时,ratings[2] < ratings[1],此时递减的元素有三个,故count += 3;
 * 4. 下标为3时,ratings[3] > ratings[2],此时递增的元素有两个,故count += 2;
 * ...
 * 以此类推,最终得到count=29.
 *
 * 上面的方法还存在一个逻辑漏洞,我按照原先的思路写出来的代码有BUG,后来看了LeetCode
 * 上面的解答,在计算单调递减或者单调递增的时候,局部最大值是属于递增的一边还是递减的
 * 一边,需要依据是递增的元素多还是递减的元素多来判断,局部峰值取两者中的较大值.详细
 * 说明参见:
 * https://leetcode.com/problems/candy/solution/
 *
 * 1. 为了判断是递增的元素多还是递减的元素多,我们需要两个变量来记录;
 * 2. 为了判断当前是递增还是递减我们需要用一个变量来表示,同时也要记
 *    录之前是递增还是递减;
 */
#define max(x, y) ((x) > (y) ? (x) : (y))

int
candy(int *ratings, int ratingsSize) {
  int i, up, down, old_slope, new_slope, candy;

  if (ratingsSize <= 1)
    return ratingsSize;

  up = down = 0;  /* up, down记录递增和递减的元素个数. */
  old_slope = 0;  /* 记录之前是递增还是递减: 1-递增, -1-递减, 0-水平. */
  candy = 0;  /* 初始时0个糖果. */

  for (i = 1; i < ratingsSize; ++i) {
    /* 判断当前是递增还是递减. */
    new_slope = ratings[i] > ratings[i - 1]
                ? 1
                : ratings[i] < ratings[i - 1] ? -1 : 0;
    /**
     * 出现局部极值时计算所需的糖果数.
     * 1. 之前递增,现在水平;
     * 2. 之前递减,现在水平;
     * 3. 之前递减,现在递增;
     * 注意这里没有考虑之前递增现在递减的情况,因为这种情况下,局部极大值
     * 应该属于递增或者递减元素较多的一边,而现在递减,不知道后续是否继续
     * 递减,所以无从判断哪边的元素多.
     * 在第一种情况中,可能会出现,递增后递减,然后水平,此时局部极大值应该
     * 属于元素较多的那一边.
     */
    if ((old_slope > 0 && new_slope == 0) ||
        (old_slope < 0 && new_slope >= 0)) {
      candy += (1 + up) * up / 2 + (1 + down) * down / 2 + max(up, down);
      up = down = 0;
    }

    /* 下面在计数时极值点没有计算进去,所以上面计算candy时还要加上max(up,down). */
    if (new_slope > 0)
      ++up;
    else if (new_slope < 0)
      ++down;
    else
      ++candy;  /* 当前是水平的,则糖果数加1即可. */

    old_slope = new_slope;
  }

  /**
   * 循环结束后做特殊处理,防止最后一部分是单调,或者最后出现单调增后单调减的情况.
   * 由于在前面计算up,down时,极值点未计算进去,故两者中的较大值加上1得到的就是多
   * 的那边元素的个数.
   * 第104行和125行代码很有技巧性.
   */
  candy += (1 + up) * up / 2 + (1 + down) * down / 2 + max(up, down) + 1;

  return candy;
}

/**
 * 看了下讨论区,贴上一篇非常棒的代码:
 * https://leetcode.com/problems/candy/discuss/161652/
 * 总体思路与上面相似,不过我觉得更简洁:
 * 1. 用两个变量up,down分别记录递增和递减的个数;
 * 2. 如果之前递减当前递增,up=1,如果当前递增,up加1;
 * 3. 如果当前递减,down加1,当down大于up时,说明之前分的糖果少了,每多一个,糖果数
 *    就需要额外加1;
 * 4. 如果当前是水平的,糖果数加1;
 */
int
candy(int *ratings, int ratingsSize) {
  int candy, up, down, i;

  if (ratingsSize <= 1)
    return ratingsSize;

  candy = up = down = 1;
  for (i = 1; i < ratingsSize; ++i) {
    if (ratings[i] > ratings[i - 1]) {
      /* 之前是递减的现在递增了. */
      if (i > 1 && ratings[i - 1] < ratings[i - 2])
        up = 1;
      candy += ++up;
      down = 1;
    } else if (ratings[i] < ratings[i - 1]) {
      ++down;
      candy += down - 1;

      /* 递减的个数超过递增的了,之前的极大值给的糖果少了. */
      if (down > up)
        ++candy;
    } else {
      ++candy;
      up = down = 1;
    }
  }

  return candy;
}