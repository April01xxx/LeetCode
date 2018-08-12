/**
 * Given a string S and a string T, find the minimum window in S which will
 * contain all the characters in T in complexity O(n).
 * Example:
 *  Input: S = "ADOBECODEBANC", T = "ABC"
 *  Output: "BANC"
 *
 * Note:
 * - If there is no such window in S that covers all characters in T, return
 *   the empty string "".
 * - If there is such window, you are guaranteed that there will always be
 *   only one unique minimum window in S.
 *
 * 求包含字符串T的最小的子串.
 *    0                   1
 *    0 1 2 3 4 5 6 7 8 9 0 1 2
 * S: A D O B E C O D E B A N C
 * 在字符串S中寻找子串"ABC",当i=5时第一次找到包含T的子串.此时的子串为"ADOBEC".
 * 继续遍历剩下的字符,当i=9时,遇到一个字符'B'属于T,此时判断是否可能存在下一个
 * 比已经找到的子串更短的子串.这个子串的起始下标start=5,此时S[5,9]包含字符'B',
 * 'C',该子串的长度为5,还剩余一个字符'A'未找到,故最起码能找到一个与原子串同长
 * 度的子串.下一个字符恰好为'A'此时找到第二个子串包含"ABC",长度也为6.此时若S[10]
 * 不等于A,则start应该移动到i=9处(这一步属于剪枝优化).当i=12时,S[i]='C',此时从
 * start开始往后找到'C'第一次出现的地方j=5,接着从j开始往后寻找下一个出现的字符,
 * 故新的start=9.此时子串的长度为4,小于6,故最短的子串为"BANC".
 *
 * 剩下还有问题是如何判断子串S[i,j]是否包含字符串T,假设只有26个字母,那可以用
 * 一个数组来记录每个字符出现的次数.
 * 整个思路如下:
 * 1. 用数组letters[26]字符串T中每个字符出现的次数.
 * 2. 遍历字符串S,若字符S[i]在T中出现,则记录其在字符串S中出现的次数到target[26].
 *    同时用一个队列维护已经匹配到的字符集合.每次匹配到一个字符则将其入队.入队
 *    后检查队首元素出现的次数是否大于该字符在T中出现的次数,如果是的话,则将其出
 *    队,同时将其出现的次数target减一.
 * 3. 用变量check记录匹配到的字符的和,若check == sum,表明成功匹配,记下此时子串
 *    的长度.
 */
struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;

struct QueueRecord {
  int capacity;   /* 队列的容量. */
  int size;       /* 队列当前元素个数. */
  int front;      /* 队首指针. */
  int rear;       /* 队尾指针. */
  ElementType *array;
};


/**
 * 创建队列并初始化.
 */
Queue
createQueue(int size) {
  Queue q;

  q = malloc(sizeof(struct QueueRecord));
  q->array = malloc(size * sizeof(ElementType));
  q->capacity = size;
  q->size = 0;
  q->front = 1;   /* 注意初始化rear = front - 1. */
  q->rear = 0;

  return q;
}

/**
 * 销毁队列.
 */
void
disposeQueue(Queue q) {
  if (q) {
    free(q->array);
    free(q);
  }
}

/**
 * 判断队列是否为空.
 */
int
isEmpty(Queue q) {
  return q->size == 0;
}

/**
 * 判断队列是否满了.
 */
int
isFull(Queue q) {
  return q->size == q->capacity;
}

/**
 * 入队操作.
 * 调用者自行保证队列不满.
 */
void
enqueue(ElementType x, Queue q) {
  /* 循环队列,注意回绕. */
  if (++q->rear == q->capacity)
    q->rear = 0;
  q->array[q->rear] = x;
  ++q->size;
}

/**
 * 出队操作.
 * 调用者自行保证队列非空.
 */
ElementType
dequeue(Queue q) {
  /* 因为初始化时front为1.若栈的大小
   * 只有1(几乎不可能),则需要特殊处理.
   */
  if (q->front == q->capacity)
    q->front = 0;
  --q->size;
  return q->array[q->front++];
}

ElementType
top(Queue q) {
  return q->array[q->front];
}

char *
minWindow(char *s, char *t) {
  int start, len, min_start, min_len, i;
  int letters[256] = {0}, target[256] = {0};
  int check, sum;
  char *ans;
  Queue q;

  ans = (char *)malloc((1 + strlen(s)) * sizeof(char));
  *ans = 0;
  if (strlen(t) > strlen(s) || strlen(t) == 0)
    return ans;

  sum = 0;
  for (i = 0; t[i] != 0; ++i) {
    letters[t[i] - 'A'] += 1;
    sum += t[i];
  }

  q = createQueue(strlen(s));
  check = 0;
  min_start = 0;
  min_len = strlen(s);
  for (i = 0; s[i] != 0; ++i) {
    if (letters[s[i] - 'A'] > 0) {
      ++target[s[i] - 'A'];
      enqueue(i, q);
      if (target[s[i] - 'A'] <= letters[s[i] - 'A'])
        check += s[i];

      /**
       * 检查队首的元素出现的次数是否大于其在T中出现的次数,如果是的话,将窗口向右
       * 滑动,同时将队首元素出队.
       */
      start = top(q);
      /**
       * 这里不加上s[start] - 'A' >= 0的条件在LeetCode上会报错.
       * 然而在队列非空的情况下,s[start] - 'A'是肯定大于等于0的.
       * 有点奇怪...
       */
      while (!isEmpty(q) && s[start] - 'A' >= 0 &&
             target[s[start] - 'A'] > letters[s[start] - 'A']) {
        --target[s[start] - 'A'];
        dequeue(q);
        start = top(q);
      }

      if (check == sum) {
        /* 成功找到一个包含字符串T的子串. */
        len = i - start + 1;
        if (len < min_len) {
          min_start = start;
          min_len = len;
        }
      }
    }
  }

  disposeQueue(q);
  if (check == sum) {
    memcpy(ans, s + min_start, min_len);
    ans[min_len] = 0;
  }
  return ans;
}

/**
 * 仔细思考之后发现,上述代码的逻辑还不够简洁.
 * 1. 在没有找到完全包含字符串T的子串之前,没必要滑动窗口;
 * 2. 在滑动窗口时判断当前窗口是否完全包含字符串T,如果是,则窗口的左边界
 *    向右滑动,一次前进一个字符,这样就不用单独维护一个已匹配字符的队列.
 * 3. 没必要用两个数组来记录匹配信息,只用一个就可以了,正数表示待匹配,
 *    负数表示超出匹配次数.
 */
char *
minWindow(char *s, char *t) {
  int start, i, min_start, min_len, match;
  int dict[256] = {0};
  char *ans;

  ans = (char *)malloc((1 + strlen(s)) * sizeof(char));
  *ans = 0;

  if (strlen(s) < strlen(t) || strlen(t) == 0)
    return ans;

  match = 0;
  for (i = 0; t[i] != 0; ++i) {
    dict[t[i]] += 1;
    ++match;
  }

  min_start = -1;
  start = 0;
  min_len = 1 + strlen(s);
  for (i = 0; s[i] != 0; ++i) {
    if (dict[s[i]] > 0)
      --match;

    /**
     * 找到一个在T中的字符则将其待匹配次数减1,若匹配次数超过T中出现的次数,
     * 则会扣减为负数.没有在T中出现的字符也会扣减为负数,在后续将左边界向右
     * 移动时,判断dict[s[start]]的待匹配次数大于0则不能再向右移动左边界.
     */
    --dict[s[i]];

    /**
     * 若成功找到包含字符串T的子串,此时需要将左边界向右移动来找到最短的子串.
     */
    while (match == 0) {
      if (i - start + 1 < min_len) {
        min_start = start;
        min_len = i - start + 1;
      }
      /* 尝试将左边界向右移动. */
      if (++dict[s[start++]] > 0)
        ++match;
    }
  }

  if (min_start != -1) {
    memcpy(ans, s + min_start, min_len);
    ans[min_len] = 0;
  }
  return ans;
}
