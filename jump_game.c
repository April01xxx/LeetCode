/**
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.Each element in the array represents your maximum
 * jump length at that position. Determine if you are able to reach the last
 * index.
 *
 * Example 1:
 *  Input: [2,3,1,1,4]
 *  Output: true
 *
 * Example 2:
 *  Input: [3,2,1,0,4]
 *  Output: false
 *
 * 此题与Jump Game II很像,不过那道题是求从数组头到数组尾的最少跳数,这道题则是
 * 要判断能否从数组头调到数组尾.如果那道题的Greedy Algorithm理解了的话,这道题
 * 很容易解决.
 */
bool
canJump(int *nums, int numsSize) {
  int i, left, right, distance;

  left = right = distance = 0;
  while (distance < numsSize - 1) {
    for (i = left; i <= right; ++i) {
      if (i + nums[i] > distance)
        distance = i + nums[i];
    }
    /**
     * 在[left,right]范围内的所有元素能移动的最远距离不超过distance,
     * 则说明不能从数组头移动到尾部.
     */
    if (distance <= right)
      return false;

    left = right + 1;
    right = distance;
  }
  return true;
}




