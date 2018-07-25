/**
 * Given a set of candidate numbers (candidates) (without duplicates) and a
 * target number (target), find all unique combinations in candidates where
 * the candidate numbers sums to target.
 * The same repeated number may be chosen from candidates unlimited number
 * of times.
 * Note:
 *   1. All numbers (including target) will be positive integers.
 *   2. The solution set must not contain duplicate combinations.
 *
 * Example:
 * Input: candidates = [2,3,5], target = 8,
 * A solution set is:
 * [
 *   [2,2,2,2],
 *   [2,3,3],
 *   [3,5]
 * ]
 *
 * 大致思路是先将数组排序,然后开始递归查找,以上面的例子来说明:
 * 1. 先固定一个值2,要在数组中查找6,此时递归;
 * 2. 发现6比数组最小的元素大,再次固定2,接着要在数组中查找4;
 * 3. 重复2的步骤,固定2,要在数组中查找2;
 * 4. 恰好等于数组最小的元素,成功找到,添加到结果集中,递归返回;
 * 5. 上层函数接着固定3(4>3),得出要在数组中查找1,递归;
 * 6. 发现1比最小的元素小,返回失败;
 * 7. 接着发现下一个元素5比4要大,此层递归也返回.
 * 8. 上上层递归固定3,得出要在数组中查找3,开始递归
 * 9. ...
 * 如此这般最后得到示例中的结果集.
 */

int **
combinationSum(int *candidates, int candidatesSize, int target,
    int **columnSize, int *returnSize) {
}
