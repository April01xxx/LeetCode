/**
* Return an array of arrays of size *returnSize.
* The sizes of the arrays are returned as *columnSizes array.
* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
*/

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

// Memory layout:
// 32 -> 4 4 4 4 4 4 => 24
// 64 -> 8 4 4 4 4 8 => 32
typedef struct _HashEntry HashEntry;
struct _HashEntry {
  HashEntry * next;
  u32 key[3];
  u32 pos;
  char ** arr;
};

#define ENTRY_DEF_ARR_SIZE 4

HashEntry * NewHashEntry(char * str, u32 key1, u32 key2, u32 key3) {
  char ** arr = malloc(ENTRY_DEF_ARR_SIZE * sizeof(char *));
  HashEntry * entry = malloc(sizeof(HashEntry));
  *arr = str;
  entry->next = NULL;
  entry->key[0] = key1;
  entry->key[1] = key2;
  entry->key[2] = key3;
  entry->pos = 1;
  entry->arr = arr;
  return entry;
}

static HashEntry * hashMap[256][4];

#define IS_POW_2(x) (((x) & ((x) - 1)) == 0)

void InsertIntoHashMap(char * str) {
  u32 key[4];
  unsigned char * s = str;
  HashEntry * entry;
  unsigned char c, d;

  // Calculate the hash.
  key[0] = 0; key[1] = 0; key[2] = 0; key[3] = 0;
  while (*s != 0) {
    c = *s++ - 'a';
    key[c >> 3] += 1 << ((c & 7) << 2);
  }
  // Compress the hash.
  key[1] |= (key[3] & 0xF0) << 2;
  key[2] |= key[2] << 30;
  key[2] = (key[3] & 0x0F) | (key[2] & ~0x0F);
  // Calculate the short hash.
  key[3] = (key[0] ^ (key[1] << 1)) ^ (key[2] << 2);
  key[3] ^= key[3] >> 16;
  key[3] ^= key[3] >>  8;
  c = (void *)s - (void *)str;
  d = c & 3;
  c ^= key[3];
  // Insert string into the hash map.
  entry = hashMap[c][d];
  if (entry == NULL) {
    hashMap[c][d] = NewHashEntry(str, key[0], key[1], key[2]);
  } else {
    while (entry->next != NULL && (
             entry->key[0] != key[0] || entry->key[1] != key[1] ||
             entry->key[2] != key[2]
           )) {
      entry = entry->next;
    }
    if (entry->next == NULL && (
          entry->key[0] != key[0] || entry->key[1] != key[1] ||
          entry->key[2] != key[2]
        )) {
      entry->next = NewHashEntry(str, key[0], key[1], key[2]);
    } else {
      if (entry->pos >= ENTRY_DEF_ARR_SIZE && IS_POW_2(entry->pos)) {
        entry->arr = realloc(
                       entry->arr,
                       (entry->pos << 1) * sizeof(char *)
                     );
      }
      entry->arr[entry->pos++] = str;
    }
  }
}

int CompString(const void * l, const void * r) {
  char const * a = *(char const **)l;
  char const * b = *(char const **)r;

  while (*a != 0 && *a == *b) {
    ++a; ++b;
  }
  if (*b == 0) {
    return 0;
  } else {
    return *a > *b ? 1 : -1;
  }
}

int CountGroupAndSort() {
  int i, j, count = 0;
  HashEntry * entry;

  for (i = 0; i < 256; ++i) {
    for (j = 0; j < 4; ++j) {
      entry = hashMap[i][j];
      while (entry != NULL) {
        ++count;
        qsort(entry->arr, entry->pos, sizeof(char *), CompString);
        entry = entry->next;
      }
    }
  }

  return count;
}

void TraverseAndFreeHashMap(char *** groups, int * groupsSize, int len) {
  int i, j, count = 0;
  HashEntry * entry, * next;

  for (i = 0; i < 256; ++i) {
    for (j = 0; j < 4; ++j) {
      if (count == len) {
        return;
      }
      entry = hashMap[i][j];
      if (entry != NULL) {
        hashMap[i][j] = NULL;
      }
      while (entry != NULL) {
        next = entry->next;
        groups[count] = entry->arr;
        groupsSize[count] = entry->pos;
        ++count;
        free(entry);
        entry = next;
      }
    }
  }
}

char***
groupAnagrams(char** strs, int strsSize, int** columnSizes, int* returnSize) {
  int i, count, * groupsSize;
  char *** groups;

  if (strsSize == 0) {
    columnSizes = NULL;
    returnSize = 0;
    return NULL;
  }
  // Insert all strings.
  for (i = 0; i < strsSize; ++i) {
    InsertIntoHashMap(strs[i]);
  }
  // Count groups and sort them.
  count = CountGroupAndSort();
  // Generate output.
  groupsSize = malloc(count * sizeof(int));
  groups = malloc(count * sizeof(char **));
  TraverseAndFreeHashMap(groups, groupsSize, count);
  *columnSizes = groupsSize;
  *returnSize = count;
  return groups;
}