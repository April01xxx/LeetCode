/**
 * You are playing the following Nim Game with your friend: There is a heap of
 * stones on the table, each time one of you take turns to remove 1 to 3 stones.
 * The one who removes the last stone will be the winner. You will take the
 * first turn to remove the stones.
 *
 * Both of you are very clever and have optimal strategies for the game. Write
 * a function to determine whether you can win the game given the number of
 * stones in the heap.
 *
 * Example:
 *
 * Input: 4
 * Output: false
 * Explanation: If there are 4 stones in the heap, then you will never win the
 *              game; No matter 1, 2, or 3 stones you remove, the last stone
 *              will always be removed by your friend.
 *
 * 没啥太好的思路,穷举吧.穷举的时候发现有个条件:双方的选择每一步都是最优的.这种
 * 逻辑很难表达,仔细想了下,这实际上是有规律的:
 * stones: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
 * win   :   1 1 1 0 1 1 1 0 1 1  1  0  1  1  1  0  1  1  1  0
 * 仔细观察,可以通过自底向上的方法计算出不同数量的石头数时能否赢.假设当前石头数量
 * 是N,若在[N-3, N-1]区间内存在一个不能赢的点,那就一定能赢.
 * 上面这些都是逻辑分析,数学规律上来说,若N%4等于0,就肯定不能赢.
 */
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4;
    }
};