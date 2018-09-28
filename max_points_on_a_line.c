/**
 * Given n points on a 2D plane, find the maximum number of points that lie on
 * the same straight line.
 * Example 1:
 * Input: [[1,1],[2,2],[3,3]]
 * Output: 3
 * Explanation:
 * ^
 * |
 * |        o
 * |     o
 * |  o
 * +------------->
 * 0  1  2  3  4
 *
 * Example 2:
 * Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 * Output: 4
 * Explanation:
 * ^
 * |
 * |  o
 * |     o        o
 * |        o
 * |  o        o
 * +------------------->
 * 0  1  2  3  4  5  6
 *
 * 给定一组二维平面上的点坐标集,求落在同一条直线上的最多的点的个数.
 * 平面上两个点组成一条直线,若有n个点,最多有n*(n-1)/2条直线.对于
 * 每个点而言,最多有n-1条直线.若已知一个点,那么由斜率就能确定一条
 * 直线,在计算斜率时注意分母为0的情况,用弧度表示斜率arctanθ.
 * 对于每个点,我们维护一个过该点的所有直线的斜率的集合,在处理其它点
 * 时,计算斜率,若斜率已经存在则对应直线上的点加1.
 */

/**
 * struct Point {
 *   int x;
 *   int y;
 * };
 */

/**
 * 此题的关键是用一个hash表保存已经存在的直线.关于如何判断两直线是否
 * 共线,可以利用向量的叉乘,若叉积为0表示两向量共线.
 */
typedef enum {
  Empty = 0, Legitimate, Delete
} Status;

/* 直线的斜率,将其化简后得到. */
typedef struct Point Slope;

typedef struct {
  Status state;
  Slope slope;
  int count;
} HashEntry;

typedef struct {
  int capacity;
  HashEntry *array;
} HashTable;

HashTable *
hashCreate(int capacity) {
  HashTable *h;

  h = malloc(sizeof(HashTable));
  h->capacity = capacity << 1;
  h->array = malloc(h->capacity * sizeof(HashEntry));

  return h;
}

void
hashMakeEmpty(HashTable *h) {
  int i;
  HashEntry *ht = h->array;

  for (i = 0; i < h->capacity; ++i)
    ht[i].state = Empty;
}
/**
 * hash函数,用直线的斜率作为key.
 */
int
hash(HashTable *h, Slope *slope) {
  unsigned int hashval;   /* 兼容溢出的情况,定义为无符号整型. */

  hashval = labs(slope->x) * 31 + labs(slope->y);

  return hashval % h->capacity;
}

bool
sameSlope(Slope *a, Slope *b) {
  return a->x == b->x && a->y == b->y;
}

int
hashFind(HashTable *h, Slope *slope) {
  int hashval = hash(h, slope);
  HashEntry *ht = h->array;

  while (ht[hashval].state != Empty &&
         !sameSlope(&ht[hashval].slope, slope)) {
    ++hashval;
    if (hashval == h->capacity)
      hashval = 0;
  }

  return hashval;
}

int
hashInsert(HashTable *h, Slope *slope) {
  int hashval = hashFind(h, slope);
  HashEntry *ht = h->array;

  if (ht[hashval].state != Legitimate) {
    ht[hashval].slope.x = slope->x;
    ht[hashval].slope.y = slope->y;
    ht[hashval].count = 1;
    ht[hashval].state = Legitimate;
  } else {
    ht[hashval].count += 1;
  }

  return ht[hashval].count;
}

void
hashFree(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

#define max(x, y) ((x) > (y) ? (x) : (y))

/**
 * 求两个数的最大公约数.
 */
int
GCD(int M, int N) {
  int REM;

  while (N != 0) {
    REM = M % N;
    M = N;
    N = REM;
  }

  return M;
}

int
maxPoints(struct Point *points, int pointsSize) {
  int i, j, dup, count, ans = 0;
  HashTable *h;

  if (pointsSize <= 2)
    return pointsSize;

  h = hashCreate(pointsSize);
  for (i = 0; i < pointsSize; ++i) {
    hashMakeEmpty(h);
    dup = 1;
    count = 0;
    for (j = i + 1; j < pointsSize; ++j) {
      if (sameSlope(&points[i], &points[j])) {
        ++dup;
      } else {
        Slope slope;
        slope.x = points[j].x - points[i].x;
        slope.y = points[j].y - points[i].y;

        int gcd = GCD(slope.y, slope.x);
        slope.x /= gcd;
        slope.y /= gcd;

        int temp = hashInsert(h, &slope);
        count = max(count, temp);
      }
    }
    ans = max(ans, dup + count);
  }

  hashFree(h);
  return ans;
}