/**
 * 哈希表(Hash Table)数组实现.
 * 开放定址散列,平方探测.
 * 调用者必须保证哈希表的大小至少是元素个数的两倍,
 * 否则find例程将会产生数组越界的错误.
 */

typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;
struct Node;
typedef struct Node *ElementType;

/* 哈希表元素的状态:
 * Legitimate - 被使用
 * Empty - 未被使用,初始化后的状态
 * Delete - 被删除
 */
enum KindOfEntry {
  Legitimate, Empty, Deleted
};

/**
 * 哈希表的元素是字符串和整数值的映射关系.
 */
struct Node {
  char *key;
  int val;
};

struct HashEntry {
  ElementType element;
  enum KindOfEntry info;
};

typedef struct HashEntry Cell;

struct HashTbl {
  int size;
  Cell *array;
};

/**
 * 求给定整数的下一个素数.
 */
typedef char bool;
#define true 1
#define false 0

static int
nextPrime(int n) {
  int i;
  bool notPrime;

  /* 如果n是偶数则加1变为奇数. */
  if ((n & 0x1) == 0)
    ++n;
  /* n的步长为2,因为本身是奇数,若加1则变为偶数肯定不是素数. */
  for (;; n += 2) {
    /* i的取值从3开始,因为不是偶数所以2不用测试.
     * 一个数不可能被比自己平方根大的数整除.
     * 一个奇数是不可能被偶数整除的,故i的步长也是2.
     */
    notPrime = false;
    for (i = 3; i * i <= n; i += 2) {
      if (n % i == 0) {
        notPrime = true;
        break;
      }
    }
    /* 循环结束时notPrime为假则表明找到了素数. */
    if (!notPrime)
      return n;
  }
}

/**
 * 初始化哈希表.
 */
HashTable
initHashTable(int size) {
  HashTable h;
  int i;

  h = malloc(sizeof(struct HashTbl));
  h->size = nextPrime(size);  /* 计算比size大的下一个素数. */
  h->array = malloc(sizeof(Cell) * h->size);

  for (i = 0; i < h->size; ++i) {
    h->array[i].element = malloc(sizeof(struct Node));
    h->array[i].info = Empty;
  }

  return h;
}

/**
 * 散列(Hash)函数.
 * 采用了<<数据结构与算法分析>>书中推荐的针对
 * 字符串的散列函数.
 */
Index
hash(char *key, int size) {
  unsigned int hashval = 0;
  int i = 0;

  /* 常用的字符串是26个英文字母加空格(27个字符),
   * 将每个字符乘以27就能得到唯一的映射,不过为了效率,
   * 我们乘以32(即左移5位),另外为了加速采用按位异或.
   */
  while (key[i] != 0)
    hashval = (hashval << 5) ^ key[i++];

  return hashval % size;
}

/**
 * 根据key查找元素.
 * 根据h->array[p].info的类型来判断元素是否存在.
 */
Position
find(char *key, HashTable h) {
  Position p;
  int collisionNum;   /* 冲突的次数,采用平方探测法. */

  collisionNum = 0;
  p = hash(key, h->size);
  /* 找到一个已被使用但是key不等,说明产生了冲突.
   * 本例程假设散列表的大小至少是元素个数的两倍,
   * 若不是,则下面代码会产生数组越界溢出.
   */
  while (h->array[p].info != Empty &&
         strcmp(h->array[p].element->key, key) != 0) {
    /* 平方探测法: i*i = (i-1)*(i-1) + 2i - 1. */
    p += 2 * ++collisionNum - 1;
    if (p >= h->size)
      p -= h->size; /* size必须是元素个数的两倍,否则此处会溢出. */
  }

  return p;
}


/**
 * 插入哈希表.
 * 若元素已经存在则累加其value值;
 * 若不存在则插入.
 */
struct HashEntry *
insert(char *key, HashTable h) {
  Position p;

  p = find(key, h);
  if (h->array[p].info != Legitimate) {
    h->array[p].info = Legitimate;
    h->array[p].element->key = key;
    h->array[p].element->val = 1;
  } else {
    ++h->array[p].element->val;
  }

  return &h->array[p];
}

/**
 * 清空哈希表.
 */
void
makeEmpty(HashTable h) {
  int i;

  for (i = 0; i < h->size; ++i)
    h->array[i].info = Empty;
}

/**
 * 销毁哈希表.
 */
void
disposeHashTable(HashTable h) {
  int i;
  if (h) {
    for (i = 0; i < h->size; ++i)
      free(h->array[i].element);
    free(h->array);
    free(h);
  }
}

/**
 * 根据字符串查找.
 */
struct HashEntry *
search(char *key, HashTable h) {
  return &h->array[find(key, h)];
}
