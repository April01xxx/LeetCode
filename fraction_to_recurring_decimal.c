/**
 * Given two integers representing the numerator and denominator of a fraction,
 * return the fraction in string format. If the fractional part is repeating,
 * enclose the repeating part in parentheses.
 *
 * Example 1:
 * Input: numerator = 1, denominator = 2
 * Output: "0.5"
 *
 * Example 2:
 * Input: numerator = 2, denominator = 1
 * Output: "2"
 *
 * Example 3:
 * Input: numerator = 2, denominator = 3
 * Output: "0.(6)"
 *
 * 用字符串表示两个整数的除法结果,如果结果是无限循环小数,用括号将无限循环的部分括起来.
 * 首先可以肯定,两个整数的除法结果要么是有限小数,要么是无限循环小数.那么首先要判断结果
 * 属于哪一种.这可以利用欧几里得定理求最大公约数将分数化简,然后判断分母是否包含因子2或
 * 5.若包含,那么结果是有限小数,否则结果是无限循环小数.
 * 若结果是无限循环小数,那么接下来要判断循环多少位?一种做法是判断余数是否重复出现.例如
 * 2/7 = 0.(285714).每次除法将余数记录下来,若某次相除后余数重复出现,那说明开始循环.
 * 另外,循环节的最大长度一定比分母小1.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  Status state;
  long key;
  long quotient; /* 记录商. */
  int value;  /* 记录字符串位置下标. */
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

HashTable *
hashCreate(int size) {
  HashTable *h;
  int i;

  h = malloc(sizeof(HashTable));
  h->size = size << 1;
  h->array = malloc(h->size * sizeof(HashEntry));
  for (i = 0; i < h->size; ++i)
    h->array[i].state = Empty;

  return h;
}

void
hashFree(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

int
hashFind(HashTable *h, long key) {
  unsigned int hashval = labs(key) % h->size;
  HashEntry *ht = h->array;

  while (ht[hashval].state != Empty &&
         ht[hashval].key != key) {
    ++hashval;
    if (hashval == h->size)
      hashval = 0;
  }

  return hashval;
}

int
hashInsert(HashTable *h, long key, long q, int len) {
  unsigned int idx = hashFind(h, key);
  HashEntry *ht = h->array;

  if (ht[idx].state == Legitimate)
    return ht[idx].value;
  else {
    ht[idx].state = Legitimate;
    ht[idx].key = key;
    ht[idx].value = len;
    ht[idx].quotient = q;
    return -1;
  }
}

#define BUFFSIZE 2048
char *
fractionToDecimal(int numerator, int denominator) {
  HashTable *h;
  char *ans, *decimal, integer[12] = {0}; /* integer记录整数部分的值. */
  int sign, len = 0, begin = -1;  /* len记录小数部分的长度,begin记录循环节起始位置. */
  long q, r, d;

  if (denominator == 0) {
    ans = malloc(4);
    strcpy(ans, "NaN");
    return ans;
  }

  if (numerator > 0)
    sign = 1;
  else if (numerator < 0)
    sign = -1;
  else
    sign = 0;

  if (denominator > 0)
    sign *= 1;
  else
    sign *= -1;

  d = labs(denominator);
  r = labs(numerator);
  q = r / d;
  r = r % d;
  sprintf(integer, "%s%ld", sign >= 0 ? "" : "-", q);

  h = hashCreate(BUFFSIZE);
  q = 0;

  decimal = calloc(BUFFSIZE, sizeof(char));
  while (r != 0) {
    if ((begin = hashInsert(h, r, q, len)) >= 0)
      break;

    r *= 10;
    q = r / d;
    r %= d;

    decimal[len++] = q + '0';
  }

  ans = calloc(BUFFSIZE, sizeof(char));
  if (begin == 0)
    sprintf(ans, "%s.(%s)", integer, decimal);
  else if (begin > 0) {
    int ch = decimal[begin];
    decimal[begin] = 0;
    sprintf(ans, "%s.%s(%c%s)", integer, decimal, ch, decimal + begin + 1);
  } else {
    if (len != 0)
      sprintf(ans, "%s.%s", integer, decimal);
    else
      sprintf(ans, "%s", integer);
  }

  hashFree(h);
  return ans;
}