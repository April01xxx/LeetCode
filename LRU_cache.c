/**
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put.
 *
 * get(key) - Get the value (will always be positive) of the key if the key
 *            exists in the cache, otherwise return -1.
 *
 * put(key, value) - Set or insert the value if the key is not already present.
 *                   When the cache reached its capacity, it should invalidate
 *                   the least recently used item before inserting a new item.
 *
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 *
 * LRU缓存.大意是要求设计并实现一个缓存,这个缓存拥有get,put两种操作,其中get指令
 * 能获取对应key的值,如果不存在则返回-1;put指令将对应的key-value存入缓存:若缓存
 * 中已经存在对应key则更新,若不存在对应key且缓存空间已满,则将最近最少使用(Least
 * Recently Used)的key-value覆盖.
 *
 * Follow up提出能不能使得两种操作的时间复杂度都是O(1).要做到这一点,那就需要用到
 * hash表,但还有另外一个问题,我们需要一个排名来表示最近最少使用的情况,当缓存满了后
 * 新插入一个值时能以O(1)时间复杂度的操作快速找到最近最少使用的记录.
 */
typedef enum {
  Empty = 0, Legitimate, Delete
} Status;

typedef struct {
  int state;
  int key;
  int value;
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

HashTable *
createHashTable(int maxsize) {
  HashTable *h;

  h = malloc(sizeof(HashTable));
  h->size = maxsize << 1;
  h->array = calloc(h->size, sizeof(HashEntry));

  return h;
}

int
find(HashTable *h, int key) {
  int old, idx;
  old = idx = labs(key) % h->size;
  HashEntry *ht = h->array;

  while (ht[idx].state != Empty &&
         ht[idx].key != key) {
    ++idx;
    if (idx == h->size)
      idx = 0;
    if (idx == old)
      break;
  }
  return idx;
}

void
insert(HashTable *h, int key, int value) {
  int idx = find(h, key);
  HashEntry *ht = h->array;

  ht[idx].state = Legitimate;
  ht[idx].key = key;
  ht[idx].value = value;
}

void
delete(HashTable *h, int key) {
  int idx = find(h, key);
  HashEntry *ht = h->array;

  if (ht[idx].state == Legitimate)
    ht[idx].state = Delete;
}

void
freeHashTable(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

/**
 * LRU结构.
 * 需要一个结构来维护最近最少使用的key的顺序,暂时没想到能用O(1)复杂度
 * 维护的数据结构,先用个数组替代吧:创建一个大小为capacity大小的数组,
 * 数组的最后一个元素表示最近最少使用的key,数组的第一个元素表示最近使
 * 用的key.
 */
typedef struct {
  HashTable *h;
  int *lru;
  int capacity;
  int size;
} LRUCache;

LRUCache *
lRUCacheCreate(int capacity) {
  LRUCache *cache;

  cache = malloc(sizeof(LRUCache));
  cache->size = 0;
  cache->capacity = capacity;
  cache->lru = malloc(capacity * sizeof(int));
  cache->h = createHashTable(capacity);

  return cache;
}

int
lRUCacheGet(LRUCache *obj, int key) {
  HashTable *h = obj->h;
  HashEntry *ht = h->array;
  int idx = find(h, key);

  if (ht[idx].state != Legitimate)
    return -1;
  else {
    int i, j;
    for (i = 0; i < obj->size; ++i) {
      if (obj->lru[i] == key)
        break;
    }
    for (j = i; j > 0; --j)
      obj->lru[j] = obj->lru[j - 1];
    obj->lru[0] = key;
    return ht[idx].value;
  }
}

void
lRUCachePut(LRUCache *obj, int key, int value) {
  HashTable *h = obj->h;
  HashEntry *ht = h->array;
  int i, j, idx;

  /**
   * 先判断新插入的key是否存在,如果已经存在则直接更新value;
   * 如果不存在,判断缓存是否满了,如果满了,则删除最近最少使用的key.
   */
  idx = find(h, key);
  if (ht[idx].state == Legitimate) {
    ht[idx].value = value;
    for (i = 0; i < obj->size; ++i) {
      if (obj->lru[i] == key)
        break;
    }
  } else if (obj->size < obj->capacity) {
    ht[idx].key = key;
    ht[idx].value = value;
    ht[idx].state = Legitimate;

    i = obj->size;
    ++obj->size;
  } else {
    delete(h, obj->lru[obj->capacity - 1]);
    insert(h, key, value);
    i = obj->capacity - 1;
  }

  for (j = i; j > 0; --j)
    obj->lru[j] = obj->lru[j - 1];
  obj->lru[0] = key;
}

void
lRUCacheFree(LRUCache *obj) {
  if (obj) {
    freeHashTable(obj->h);
    free(obj->lru);
    free(obj);
  }
}


/**
 * 上述方法能OJ,但效率不怎么理想,关键在于我们用一个数组维护最近最少使用
 * 的key的顺序,每次get或put操作后调整key的顺序的时间复杂度是O(n).那么
 * 有没有办法做到两种操作的时间复杂度都是O(1)呢?显然是有的,不然也不会这
 * 么出题了(- -).
 *
 * 上面我们已经能想到用hash表来维护key-value,加快查找的过程,但是对于优
 * 先级(最近最少使用可以看做一种优先级)的维护却采用了数组,这里我们可以改
 * 用链表来维护,那么接下来的问题是如何快速找到最近最少使用的key的节点?
 * 我们可以设计这样一个链表:
 * 1. 该链表有一个哑结点,其next指针指向链表的第一个元素;
 * 2. 该链表有一个尾指针,指向链表的最后一个元素;
 * 3. 该链表是双向链表;
 * 对于每个key所在的节点node,我们建立一个hash表保存key-node关系.于是有:
 * 1. put操作时,先查找对应的key是否已经存在,若存在则直接更新其value,并
 *    将节点移动到链表头;若不存在新建一个节点存储对应的key-value,并将其
 *    插入到链表头,若缓存已满,则将链表最后一个节点删除,hash表中对应的key
 *    也删除.
 * 2. get操作时,查找key在hash表中是否有记录,若没有则返回-1,否则返回对应
 *    的value.
 *
 * 下面的代码能通过OJ,但实际上对hash表的处理是有BUG的,在hashTableFind
 * 函数中查找对应key的位置时,若hash表已满,则会陷入死循环.
 */
typedef enum {
  Empty = 0, Legitimate, Delete
} Status;

struct DListNode {
  int key;
  int value;
  struct DListNode *prev;
  struct DListNode *next;
};

typedef struct {
  Status state;
  struct DListNode node;
} HashEntry;

typedef struct {
  int capacity;
  HashEntry *array;
} HashTable;

HashTable *
hashTableCreate(int capacity) {
  HashTable *h;
  int i;

  h = malloc(sizeof(HashTable));
  h->capacity = capacity << 1;
  h->array = malloc(h->capacity * sizeof(HashEntry));
  for (i = 0; i < h->capacity; ++i)
    h->array[i].state = Empty;

  return h;
}

int
hashTableFind(HashTable *h, int key) {
  int hash = labs(key) % h->capacity;
  HashEntry *ht = h->array;

  /**
   * 下面这段代码有BUG,对于本题来说,当元素个数超过缓存限制时
   * 会删除最近最少使用的元素,本例中删除采用的是懒惰删除(只是
   * 将状态置为Delete),所以会出现hash表满的情况.当hash表满了
   * 后下面这段代码会死循环.修正的方法是当发现全部遍历一次后未
   * 找到合适的位置则返回状态是被删除的第一个位置.
   */
  while (ht[hash].state != Empty &&
         ht[hash].node.key != key) {
    ++hash;
    if (hash == h->capacity)
      hash = 0;
    if (hash == labs(key) % h->capacity) {
      while (ht[hash].state != Delete) {
        ++hash;
        if (hash == h->capacity)
          hash = 0;
      }

      return hash;
    }
  }

  return hash;
}

void
hashTableInsert(HashTable *h, int key, int value) {
  int hash = hashTableFind(h, key);
  HashEntry *ht = h->array;

  if (ht[hash].state != Legitimate) {
    ht[hash].state = Legitimate;
    ht[hash].node.key = key;
    ht[hash].node.value = value;
  }
}

void
hashTableDelete(HashTable *h, int key) {
  int hash = hashTableFind(h, key);
  HashEntry *ht = h->array;

  if (ht[hash].state == Legitimate)
    ht[hash].state = Delete;
}

void
hashTableFree(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}


/**
 * LRU Cache结构.
 */
typedef struct {
  HashTable *h;
  struct DListNode head;
  struct DListNode tail;
  int capacity;
  int size;
} LRUCache;

LRUCache*
lRUCacheCreate(int capacity) {
  LRUCache *cache;

  cache = malloc(sizeof(LRUCache));
  cache->capacity = capacity;
  cache->size = 0;
  cache->h = hashTableCreate(capacity);
  cache->head.next = &cache->tail;
  cache->tail.prev = &cache->head;
  cache->head.prev = cache->tail.next = NULL;

  return cache;
}

void
listNodeRemove(struct DListNode *node) {
  struct DListNode *prev = node->prev;
  struct DListNode *next = node->next;

  prev->next = next;
  next->prev = prev;
}

void
listNodeInsert(struct DListNode *head, struct DListNode *node) {
  node->next = head->next;
  head->next->prev = node;
  head->next = node;
  node->prev = head;
}

int
lRUCacheGet(LRUCache* obj, int key) {
  HashTable *h = obj->h;
  HashEntry *ht = h->array;
  int hash = hashTableFind(h, key);

  if (ht[hash].state != Legitimate)
    return -1;
  else {
    /**
     * 该节点存在,调整该节点的优先级:
     * 1. 删除该节点;
     * 2. 将该节点插入head后面.
     */
    struct DListNode *node = &ht[hash].node;
    listNodeRemove(node);
    listNodeInsert(&obj->head, node);

    return node->value;
  }
}

void
lRUCachePut(LRUCache* obj, int key, int value) {
  HashTable *h = obj->h;
  HashEntry *ht = h->array;
  int hash = hashTableFind(h, key);
  struct DListNode *node;

  node = &ht[hash].node;
  if (ht[hash].state != Legitimate)  {
    node->key = key;
    node->value = value;

    hashTableInsert(h, key, value);  /* 插入hash表中. */
    listNodeInsert(&obj->head, node);   /* 插入优先级链表中. */
    ++obj->size;

    if (obj->size > obj->capacity) {
      /**
       * 1. 从hash表中删除最近最少使用的元素;
       * 2. 从链表中移除节点;
       */
      struct DListNode *t = obj->tail.prev;
      hashTableDelete(h, t->key);
      listNodeRemove(t);
      --obj->size;
    }
  } else {
    node->value = value;
    listNodeRemove(node);
    listNodeInsert(&obj->head, node);
  }
}

void
lRUCacheFree(LRUCache* obj) {
  struct DListNode *node, *next;

  if (obj) {
    hashTableFree(obj->h);
    free(obj);
  }
}