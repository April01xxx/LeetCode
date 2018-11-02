/**
 * A city's skyline is the outer contour of the silhouette formed by all the
 * buildings in that city when viewed from a distance. Now suppose you are
 * given the locations and height of all the buildings as shown on a cityscape
 * photo (Figure A), write a program to output the skyline formed by these
 * buildings collectively (Figure B).
 *
 * Buildings  Skyline Contour
 * The geometric information of each building is represented by a triplet of
 * integers [Li, Ri, Hi], where Li and Ri are the x coordinates of the left
 * and right edge of the ith building, respectively, and Hi is its height.
 * It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0.
 * You may assume all buildings are perfect rectangles grounded on an absolutely
 * flat surface at height 0.
 *
 * For instance, the dimensions of all buildings in Figure A are recorded as:
 * [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ] .
 *
 * The output is a list of "key points" (red dots in Figure B) in the format of
 * [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key
 * point is the left endpoint of a horizontal line segment. Note that the last
 * key point, where the rightmost building ends, is merely used to mark the
 * termination of the skyline, and always has zero height. Also, the ground in
 * between any two adjacent buildings should be considered part of the skyline
 * contour.
 *
 * For instance, the skyline in Figure B should be represented as:[ [2 10],
 * [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].
 *
 * Notes:
 *
 * The number of buildings in any input list is guaranteed to be in the range
 * [0, 10000].
 * The input list is already sorted in ascending order by the left x position Li.
 * The output list must be sorted by the x position.
 * There must be no consecutive horizontal lines of equal height in the output
 * skyline. For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not
 * acceptable; the three lines of height 5 should be merged into one in the
 * final output as such: [...[2 3], [4 5], [12 7], ...]
 *
 * 一个输入确定一个矩形,要判断后面的矩形是否会被前面的覆盖.
 * 想了半天没啥太好的思路,突然注意到题目说水平方向上的范围最多是10000.那就用
 * 笨办法吧,开一个10000大小的数组height,对输入的buildings的进行遍历:
 * 1. 在遍历过程中记录下来所有buildings的最左、最右边界;
 * 2. 对每一个buildings,判断其高度是否大于指定位置的height数组中的高度,若大于,
 *    则更新height数组中的值;
 * 3. 遍历height数组,即可得到输出.
 */

class Solution {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> ans;
    vector<int> height(10000);
    int left = INT_MAX, right = 0;

    if (buildings.size() == 0)
      return ans;

    for (int i = 0; i < buildings.size(); ++i) {
      if (buildings[i][0] < left)
        left = buildings[i][0];
      if (buildings[i][1] > right)
        right = buildings[i][1];

      for (int j = buildings[i][0]; j <= buildings[i][1]; ++j) {
        if (buildings[i][2] > height[j])
          height[j] = buildings[i][2];
      }
    }

    for (int i = left; i <= right; ++i) {
      if (i == 0) {
        ans.push_back({i, height[i]});
      } else if (height[i] < height[i - 1]) {
        ans.push_back({i - 1, height[i]});
      } else if (height[i] > height[i - 1]) {
        ans.push_back({i, height[i]});
      }
    }
    ans.push_back({right, 0});
    return ans;
  }
};


/**
 * 好吧,LeetCode上测试案例里面有[[1,2,1],[2147483646,2147483647,2147483647]]
 * 这种情况,这样height数组的大小不够.自己想了半天,总觉得要考虑的情况太多,条理不够
 * 清晰,思维混乱.看了LeetCode讨论区的解说和答案,总算是豁然开朗.这里贴一篇图文并茂
 * 的问题说明:
 * https://briangordon.github.io/2014/08/the-skyline-problem.html
 * 或者参见YouTube上的视频解说:
 * https://www.youtube.com/watch?v=GSBLe8cKu0s
 * 这里也记录下我的理解:
 * 1. 仔细观察不难发现,只有矩形的边界点才是需要关注的点,我们不妨称之为critical
 *    points,那接下来我们要做的事情就是确定每个关键点处的最大高度.
 * 2. 很直观的思路是针对每个关键点,我们遍历所有矩形,找出包含这个关键点的最大矩形
 *    高度即可.若有n个矩形,那就有2n个关键点,需要2n*2n次运算即可得到最终的结果.
 * 3. 在第二步中,我们实际上只需要获取该关键点处的最大矩形高度,其余的都不关心,如果
 *    用最大堆这种数据结构,我们只需要logn的复杂度即可每个点处的最大值,那整个算法
 *    的复杂度就变为nlogn.
 * 4. 此外题目要求最终的输出是按照x轴上的坐标升序排列的,故我们可以对所有关键点进行
 *    排序,但在排序的时候有几点要注意:
 *    a. 排序时要综合考虑关键点的x坐标和高度;
 *    b. 考虑这样一组输入数据[1,3,2], [1,4,4], [5,7,3], [6,7,2],最终的输出结果
 *       应该是[1,4],[4,0],[5,3],[7,0].每个矩形有两个关键点,我们称左边的点为start,
 *       右边的点为end.start排序规则: x坐标小的排前面,若x相同,高度大的排前面;end
 *       排序规则:x坐标小的排前面,若x相同,高度小的排前面;
 *    c. 这里解释下步骤b中的排序原理.对于每个关键点p,我们要维护包含了该关键点的所有
 *       矩形高度的一个最大堆h.每遇到一个新的矩形,我们将这个新矩形的高加入这个堆,若
 *       堆的最大值发生变化,说明这个点就是最终答案中的一个元素.每离开一个矩形,我们要
 *       将这个矩形的最大高度从最大堆中移除,此时若高度大的排在前面,移除之后发现最大堆
 *       中的最大值发生变化,认为这个点是一个输出,然后实际并非如此.
 * 下面以[1,3,2], [1,4,4], [5,7,3], [6,7,2]这组输入作为例子来说明:
 * 1. 列出所有的关键点,每个关键点是由x坐标和高度组成的一个pair,另外为了区分是矩形的
 *    起始点还是结束点,可以在每个pair中加入一个标志位,但还有另外一种非常富有技巧性
 *    的编程方法,我们用高度的负值表示起始点,高度的正值表示结束点,这样利用C++的sort
 *    方法排序后,恰好高度大的排在前面(高度越大,负值越小):[1,-2],[3,2],[1,-4],[4,4],
 *    [5,-3],[7,3],[6,-2],[7,2];
 * 2. 按照上述说明规则排序后结果如下:[1,-4],[1,-2],[3,2],[4,4],[5,-3],[6,-2],
 *    [7,2],[7,3];
 * 3. 令最大堆中的初始最大高度为0,遇到第一个点[1,-4],将其加入最大堆中,最大高度变为4,
 *    所以[1,4]是一个输出;接着遇到点[1,-2],将其加入最大堆,最大堆的最大高度没变化,故
 *    这个点无需考虑;接着判断点[3,2],因为这个点的高度为正,说明这是一个矩形的结束点,
 *    此时我们要将高度为2的矩形从最大堆中移除,移除后最大堆的最大高度还是4,所以这个点
 *    也不是最终的输出;接着判断点[4,4],与点[3,2]的情况类似,但是移除[4,4]后最大堆的
 *    最大高度变为0,故[4,0]是最终输出中的一个元素.重复这一过程直到遍历完所有的点即可.
 */
class Solution {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> ans;
    vector<pair<int, int>> critical_points;

    /**
     * 保存所有的critical points并按规则排序,这里利用将起始点的高度记录为
     * 负数,结束点的高度记录为正数的方法,可以减少一个标志位来标识点的起始或
     * 结束.
     */
    for (auto &b : buildings) {
      critical_points.push_back(make_pair(b[0], -b[2]));
      critical_points.push_back(make_pair(b[1], b[2]));
    }

    /**
     * 排序,起始点升序排列,若起始点相同,高度大的排在前面;结束点升序排列,
     * 若结束点相同,高度小的排在前面.
     */
    sort(critical_points.begin(), critical_points.end());

    /* 之前的最大高度和当前最大高度. */
    int prev_height = 0, curr_height;
    /**
     * 矩形的高度的最大堆,这里用了multiset结构而非priority_queue.
     * 因为multiset中的数据本身是有序的,插入删除的时间复杂度都是logn,
     * 而且rbegin()方法可以很方便的获取当前最大值.为了避免后续解引用
     * rbegin()方法出现异常,这里先插入一个0元素表示默认最大高度.
     */
    multiset<int> heights {0};
    for (auto &c : critical_points) {
      if (c.second > 0) {
        /**
         * 结束点,将对应的高度从堆中移除.注意这里不能直接用erase方法,
         * 因为erase方法会将所有等于c.second的值移除.而我们只能移除
         * 一个,故先用find方法找到一个即可.
         */
        heights.erase(heights.find(c.second));
      } else {
        /* 起始点,将新的高度入堆. */
        heights.insert(-c.second);
      }
      curr_height = *heights.rbegin();
      if (prev_height != curr_height) {
        prev_height = curr_height;
        ans.push_back(make_pair(c.first, prev_height));
      }
    }
    return ans;
  }
};