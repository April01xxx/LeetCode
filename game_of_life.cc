/**
 * According to the Wikipedia's article: "The Game of Life, also known simply
 * as Life, is a cellular automaton devised by the British mathematician John
 * Horton Conway in 1970."
 *
 * Given a board with m by n cells, each cell has an initial state live (1) or
 * dead (0). Each cell interacts with its eight neighbors (horizontal, vertical,
 * diagonal) using the following four rules (taken from the above Wikipedia
 * article):
 *
 * Any live cell with fewer than two live neighbors dies, as if caused by
 * under-population.
 * Any live cell with two or three live neighbors lives on to the next
 * generation.
 * Any live cell with more than three live neighbors dies, as if by
 * over-population..
 * Any dead cell with exactly three live neighbors becomes a live cell, as if
 * by reproduction.
 * Write a function to compute the next state (after one update) of the board
 * given its current state. The next state is created by applying the above
 * rules simultaneously to every cell in the current state, where births and
 * deaths occur simultaneously.
 *
 * Example:
 *
 * Input:
 * [
 *   [0,1,0],
 *   [0,0,1],
 *   [1,1,1],
 *   [0,0,0]
 * ]
 * Output:
 * [
 *   [0,0,0],
 *   [1,0,1],
 *   [0,1,1],
 *   [0,1,0]
 * ]
 * Follow up:
 *
 * Could you solve it in-place? Remember that the board needs to be updated at
 * the same time: You cannot update some cells first and then use their updated
 * values to update other cells.
 * In this question, we represent the board using a 2D array. In principle, the
 * board is infinite, which would cause problems when the active area encroaches
 * the border of the array. How would you address these problems?
 *
 * 生存游戏,有四条规则,依据当前元素是生(1)还是死(0),分别处理:
 * 1. 当前元素为生(1):
 *    a. 周围元素活着的小于2或者大于3,则死;
 *    b. 周围元素或者的只有2个或3个,则生;
 * 2. 当前元素为死(0):周围恰好有3个活着的元素则生.
 *
 * 必须同时更新,另外Follow up提到能否就地处理(不分配额外空间),答案是可以.
 * 此题的关键是针对每个元素,计算周围有多少个活着的元素,然后依据当前元素是生
 * 还是死,应用不同的法则.我们可以用正负数来表示当前元素是生还是死,绝对值表示
 * 当前元素周围有多少个生的元素.为了方便编程,用负数表示当前元素是死,正数表示
 * 当前元素是活,这样在判断周围元素时就可以用大于0来判断了.
 *
 * 有点图像处理里面卷积的意思.
 */
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int row = board.size(), col;

        if (row == 0)
            return;
        col = board[0].size();

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int count = liveCount(board, i, j);
                /* 这里要注意本身board[i][j]为生,但周围全是死的情况. */
                if (board[i][j] > 0)
                    board[i][j] = count > 0 ? count : board[i][j];
                else
                    board[i][j] = -count;
            }
        }

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                int count = board[i][j];
                if (count == -3 || count == 2 || count == 3)
                    board[i][j] = 1;
                else
                    board[i][j] = 0;
            }
        }
    }

    /* 计算当前位置周围有多少个活的. */
    inline int liveCount(vector<vector<int>>& board, int r, int c) {
        int count = 0;

        for (int i = r - 1; i <= r + 1; ++i) {
            for (int j = c - 1; j <= c + 1; ++j) {
                if (i == r && j == c)
                    continue;
                if (i >= 0 && i < board.size() && j >= 0 && j < board[0].size()
                    && board[i][j] > 0)
                    ++count;
            }
        }
        return count;
    }
};
