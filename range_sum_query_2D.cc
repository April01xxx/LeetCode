/**
 * Given a 2D matrix matrix, find the sum of the elements inside the rectangle
 * defined by its upper left corner (row1, col1) and lower right corner (row2,
 * col2).
 *
 * Example:
 * Given matrix = [
 *   [3, 0, 1, 4, 2],
 *   [5, 6, 3, 2, 1],
 *   [1, 2, 0, 1, 5],
 *   [4, 1, 0, 1, 7],
 *   [1, 0, 3, 0, 5]
 * ]
 *
 * sumRegion(2, 1, 4, 3) -> 8
 * sumRegion(1, 1, 2, 2) -> 11
 * sumRegion(1, 2, 2, 4) -> 12
 * Note:
 * You may assume that the matrix does not change.
 * There are many calls to sumRegion function.
 * You may assume that row1 ≤ row2 and col1 ≤ col2.
 *
 * 这题是前一道题range sum query的升级版,思路应该还是用空间换时间.
 * 用sum[i][j]表示所有row<i且col<j的元素的和.于是有:
 * sum[i][j] = sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+matrix[i-1][j-1].
 * sumRegion(row1,col1,row2,col2) = sum[row2+1][col2+1]-sum[row2+1][col1]
 *                                  -sum[row1][col2+1]+sum[row1][col1].
 * 为了编程方便,sum数组多一行一列.
 */
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> matrix) {
        int row, col;

        if (matrix.empty())
            return;

        row = matrix.size();
        col = matrix[0].size();
        sum.push_back(vector<int>(col + 1));
        for (int i = 1; i <= row; ++i) {
            vector<int> rowsum(col + 1);
            for (int j = 1; j <= col; ++j) {
                rowsum[j] = rowsum[j - 1] + sum[i - 1][j] - sum[i - 1][j - 1]
                            + matrix[i - 1][j - 1];
            }
            sum.push_back(rowsum);
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1]
               - sum[row1][col2 + 1] + sum[row1][col1];
    }

private:
    vector<vector<int>> sum;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */