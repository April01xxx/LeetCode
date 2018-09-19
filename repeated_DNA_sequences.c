/**
 * All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T,
 * for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to
 * identify repeated sequences within the DNA.
 * Write a function to find all the 10-letter-long sequences (substrings) that
 * occur more than once in a DNA molecule.
 *
 * Example:
 * Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
 * Output: ["AAAAACCCCC", "CCCCCAAAAA"]
 * 重复的DNA序列.给定一个字符串s表示一段DNA序列,找出其中长度为10个字符的重复出现的
 * 所有子串.先尝试用hash表来解决,遍历字符串,每10个字符组成一个子串,将其记录到hash
 * 表中.
 */
typedef enum {
  Empty, Legitimate, Delete
} Status;

typedef struct {
  Status state;
  int count;
  char key[11];
} HashEntry;

typedef struct {
  int size;
  HashEntry *array;
} HashTable;

HashTable *
createHashTable(int maxsize) {
  HashTable *h;
  int i;

  h = malloc(sizeof(HashTable));
  h->size = maxsize << 1;
  h->array = malloc(h->size * sizeof(HashEntry));
  for (i = 0; i < h->size; ++i)
    h->array[i].state = Empty;

  return h;
}

int
hash(HashTable *h, char *key) {
  int i, hashval = 0;

  for (i = 0; key[i] != 0; ++i)
    hashval = (hashval << 2) ^ key[i];

  return hashval % h->size;
}

int
find(HashTable *h, char *key) {
  int hashval = hash(h, key);
  HashEntry *ht = h->array;

  while (ht[hashval].state != Empty &&
         strcmp(ht[hashval].key, key) != 0) {
    ++hashval;
    if (hashval == h->size)
      hashval = 0;
  }

  return hashval;
}

void
insert(HashTable *h, char *key) {
  int hashval = find(h, key);
  HashEntry *ht = h->array;

  if (ht[hashval].state == Empty) {
    ht[hashval].state = Legitimate;
    strcpy(ht[hashval].key, key);
    ht[hashval].count = 1;
  } else {
    ht[hashval].count += 1;
  }
}

void
freeHashTable(HashTable *h) {
  if (h) {
    free(h->array);
    free(h);
  }
}

void
findRepeated(HashTable *h, char **ans, int *size) {
  int i;
  HashEntry *ht = h->array;

  for (i = 0; i < h->size; ++i) {
    if (ht[i].state == Legitimate && ht[i].count > 1) {
      ans[*size] = malloc(11 * sizeof(char));
      memcpy(ans[*size], ht[i].key, 11);
      ++*size;
    }
  }
}

char **
findRepeatedDnaSequences(char *s, int *returnSize) {
  HashTable *h;
  int i, len;
  char temp[11];
  char **ans;

  len = strlen(s);
  ans = malloc(len * sizeof(char *));
  h = createHashTable(len);

  *returnSize = 0;
  for (i = 0; i <= len - 10; ++i) {
    memcpy(temp, s + i, 10);
    temp[10] = 0;

    insert(h, temp);
  }

  findRepeated(h, ans, returnSize);

  freeHashTable(h);

  return ans;
}