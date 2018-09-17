/**
 * There are N gas stations along a circular route, where the amount of gas
 * at station i is gas[i]. You have a car with an unlimited gas tank and it
 * costs cost[i] of gas to travel from station i to its next station (i+1).
 * You begin the journey with an empty tank at one of the gas stations.
 *
 * Return the starting gas station's index if you can travel around the circuit
 * once in the clockwise direction, otherwise return -1.
 *
 * Note:
 * - If there exists a solution, it is guaranteed to be unique.
 * - Both input arrays are non-empty and have the same length.
 * - Each element in the input arrays is a non-negative integer.
 *
 * 加油站问题,题目要求从环上的某点出发,能否绕环一圈.也就是说沿途加油,保证绕一圈时
 * 油箱中剩余的油大于等于0.
 * 1. 若存在解,则gas数组总和大于等于cost数组总和;
 * 2. 起点: 从某一点开始到最后,gas数组中的和大于等于cost数组中的和.
 */
int
canCompleteCircuit(int *gas, int gasSize, int *cost, int costSize) {
  int i, start, sum, sub_sum;

  i = sum = sub_sum = 0;
  start = -1;
  for (i = 0; i < gasSize; ++i) {
    sub_sum += gas[i] - cost[i];
    sum += gas[i] - cost[i];
    if (start == -1 && sub_sum >= 0)
      start = i;
    else if (sub_sum < 0) {
      sub_sum = 0;
      start = -1;
    }
  }

  if (sum < 0)
    return -1;
  else
    return start;
}