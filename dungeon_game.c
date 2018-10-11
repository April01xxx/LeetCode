/**
 * The demons had captured the princess (P) and imprisoned her in the
 * bottom-right corner of a dungeon. The dungeon consists of M x N rooms
 * laid out in a 2D grid. Our valiant knight (K) was initially positioned
 * in the top-left room and must fight his way through the dungeon to
 * rescue the princess.
 *
 * The knight has an initial health point represented by a positive integer.
 * If at any point his health point drops to 0 or below, he dies immediately.
 *
 * Some of the rooms are guarded by demons, so the knight loses health
 * (negative integers) upon entering these rooms; other rooms are either
 * empty (0's) or contain magic orbs that increase the knight's health
 * (positive integers).
 *
 * In order to reach the princess as quickly as possible, the knight decides
 * to move only rightward or downward in each step.
 *
 * Write a function to determine the knight's minimum initial health so that
 * he is able to rescue the princess.
 *
 * For example, given the dungeon below, the initial health of the knight must
 * be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.
 *
 * +----+----+----+
 * | -2 | -3 |  3 |
 * +----+----+----+
 * | -5 | -10|  1 |
 * +----+----+----+
 * | 10 | 30 | -5 |
 * +----+----+----+
 *
 * Note:
 * The knight's health has no upper bound.
 * Any room can contain threats or power-ups, even the first room the knight
 * enters and the bottom-right room where the princess is imprisoned.
 *
 * 题目要求最小的血量使得骑士能够成功营救公主.需要注意的是血量为0时骑士立即死亡,所以
 * 为了保证成功营救,最后剩余的血量应大于等于1.由于初始时骑士血量为0,故初始时至少需要
 * 1点血量.
 * 令dp[i][j]表示第i行j列房间所需的血量.初始时:
 * dp[m-1][n-1] = dungeon[m-1][n-1] > 0 ? 1 : 1-dungeon[m-1][n-1];
 * 对于任意的(i,j)而言,dp[i][j]所需的最少血量与dp[i][j+1]和dp[i+1][j]有关.分两种情
 * 况计算:
 * 1. dp[i][j] = dp[i][j+1] - dungeon[i][j] > 0 ? dp[i][j+1] - dungeon[i][j]
 *                                              : 1.
 * 2. dp[i][j] = dp[i+1][j] - dungeon[i][j] > 0 ? dp[i+1][j] - dungeon[i][j]
 *                                              : 1.
 */
#define min(x, y) ((x) > (y) ? (y) : (x))
int
calculateMinimumHP(int **dungeon, int rows, int *cols) {
  int *dp;
  int i, j;

  dp = malloc(cols[0] * sizeof(int));

  for (i = rows - 1; i >= 0; --i) {
    for (j = cols[0] - 1; j >= 0; --j) {
      if (i == rows - 1) {
        if (j == cols[0] - 1) {
          dp[j] = dungeon[i][j] > 0 ? 1 : 1 - dungeon[i][j];
        } else {
          dp[j] = dp[j + 1] - dungeon[i][j] > 0 ? dp[j + 1] - dungeon[i][j] : 1;
        }
      } else {
        if (j == cols[0] - 1) {
          dp[j] = dp[j] - dungeon[i][j] > 0 ? dp[j] - dungeon[i][j] : 1;
        } else {
          int right = dp[j + 1] - dungeon[i][j] > 0
                      ? dp[j + 1] - dungeon[i][j]
                      : 1;
          int down = dp[j] - dungeon[i][j] > 0 ? dp[j] - dungeon[i][j] : 1;
          dp[j] = min(right, down);
        }
      }
    }
  }

  return dp[0];
}