/**
 * 最小堆数据结构的实现,此处底层数据存储用数组,由于堆的性质,
 * 对于第i个节点,其左儿子位于2i+1,右儿子位于2(i+1).
 */
typedef struct Heap *Heap;

struct Heap {
  int capacity;
  int size;
  int *array;
};

Heap
heapCreate(int maxsize) {
  Heap heap;

  heap = malloc(sizeof(struct Heap));
  heap->capacity = maxsize;
  heap->size = 0;
  heap->array = malloc(maxsize * sizeof(int));

  return heap;
}

/**
 * 堆的插入,因为堆的性质,在插入时先在最后插入元素,然后将
 * 此元素上滤.
 */
void
heapInsert(Heap h, int key) {
  int curr, parent;
  int *ht = h->array;

  curr = h->size++;

  while (curr > 0) {
    parent = (curr - 1) >> 1;
    /**
     * 最小堆,父节点大于子节点,子节点上滤.
     * 此时并不需要交换两个节点的值.只需要
     * 将父节点的值赋给子节点即可.最后循环
     * 结束后的curr位置即插入的位置.
     */
    if (ht[parent] > key) {
      ht[curr] = ht[parent];
      curr = parent;
    } else
      break;
  }
  ht[curr] = key;
}

/**
 * 寻找数组中的最大K个数,先构建一个K个元素的
 * 最小堆,剩下的元素逐个校验:
 * 1. 若小于等于堆顶的元素,则抛弃;
 * 2. 若大于堆顶元素则替换掉堆顶元素,并下滤找到合适的位置.
 */
void
pryDown(Heap h, int key) {
  int curr = 0, left = 1, right = 2;
  int *ht = h->array;

  if (key <= ht[curr])
    return;

  /**
   * 注意判断左右子节点是否超出堆的大小.
   */
  while ((left < h->capacity && key > ht[left])
         || (right < h->capacity && key > ht[right])) {
    if (right < h->capacity && ht[left] > ht[right]) {
      ht[curr] = ht[right];
      curr = right;
    } else {
      ht[curr] = ht[left];
      curr = left;
    }
    left = (curr << 1) + 1;
    right = (curr + 1) << 1;
  }
  ht[curr] = key;
}

int *
findTopN(int n, int *nums, int numsSize, int *returnSize) {
  Heap h;
  int *ans, i;

  ans = malloc(n * sizeof(int));
  *returnSize = n;

  h = heapCreate(n);
  for (i = 0; i < n - 1; ++i)
    heapInsert(h, nums[i]);
  while (i < numsSize)
    pryDown(h, nums[i++]);

  memcpy(ans, h->array, n * sizeof(int));

  return ans;
}