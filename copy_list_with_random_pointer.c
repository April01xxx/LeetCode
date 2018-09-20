/**
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null. Return a deep
 * copy of the list.
 *
 * 给定一个单向链表,返回其深度拷贝,其中链表的每个节点中存在一个指针指向一个随机的
 * 节点.大致思路还是用一个Map保存新旧节点的映射,在遍历链表的过程中,若随机指针指向
 * 非空节点,则:
 *    在Map中以旧节点为key,查找是否存在,若存在则表明该节点已经分配空间,该key对应
 *    的value就是新分配的节点,若不存在,则新分配空间,并将其存入Map中.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  Status state;
  int key;
  int value;
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

typedef HashTable *Map;

Map
createMap(int maxsize) {
  Map m;
  int i;

  m = malloc(sizeof(HashTable));
  m->size = maxsize << 1;
  m->array = malloc(m->size * sizeof(HashEntry));
  for (i = 0; i < m->size; ++i)
    m->array[i].state = Empty;

  return m;
}

void
freeMap(Map m) {
  if (m) {
    free(m->array);
    free(m);
  }
}

int find(Map m, int key) {
  int hashval = key % m->size;
  HashEntry *ht = m->array;

  while (ht[hashval].state != Empty &&
         ht[hashval].key != key) {
    ++hashval;
    if (hashval == m->size)
      hashval = 0;
  }

  return hashval;
}

void
insert(Map m, int key, int value) {
  int hashval = find(m, key);
  HashEntry *ht = m->array;

  if (ht[hashval].state == Empty) {
    ht[hashval].state = Legitimate;
    ht[hashval].key = key;
    ht[hashval].value = value;
  }
}

/**
 * struct RandomListNode {
 *   int label;
 *   struct RandomListNode *next;
 *   struct RandomListNode *random;
 * };
 */
typedef struct RandomListNode List;

List *
deepCopy(List *head, Map m) {
  List *node;
  int idx;
  HashEntry *ht = m->array;

  if (head == NULL)
    return NULL;

  /* 判断该节点是否已经存在,以地址作为key */
  idx = find(m, (int)head);
  if (ht[idx].state == Empty) {
    node = malloc(sizeof(List));
    insert(m, (int)head, (int)node);
    node->label = head->label;
    node->next = deepCopy(head->next, m);
    node->random = deepCopy(head->random, m);
  } else {
    node = (List *)ht[idx].value;
  }

  return node;
}

List *
copyRandomList(List *head) {
  Map m;

  m = createMap(10240);
  return deepCopy(head, m);
}