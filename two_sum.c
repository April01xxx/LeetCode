/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    int key;
    int value;
} HashNode;

typedef HashNode *HashTable;

typedef struct {
    HashTable *hash_table;
    int size;
} HashMap;

HashMap *
hash_init(int size) {
    HashMap *map = malloc(sizeof(HashMap));
    map->size = size;
    map->hash_table = calloc(size, sizeof(HashTable));
    
    return map;
}

void
hash_free(HashMap *map) {
    HashTable *ht = map->hash_table;
    HashNode *node;
    int i;
    
    for (i = 0; i < map->size; ++i) {
        if ((node = ht[i]))
            free(node);
    }
    free(ht);
    free(map);
}

void
hash_set(HashMap *map, int key, int value) {
    int h = abs(key) % map->size;
    HashTable *ht = map->hash_table;
    HashNode *node;
    
    while (ht[h]) {
        if (h < map->size - 1)
            ++h;
        else
            h = 0;
    }
    node = malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    ht[h] = node;
}

HashNode *
hash_get(HashMap *map, int key) {
    int h = abs(key) % map->size;
    HashTable *ht = map->hash_table;
    HashNode *node;
    
    while ((node = ht[h])) {
        if (node->key != key) {
            if (h < map->size)
                ++h;
            else
                h = 0;
        } else
            return node;
    }
    return NULL;
}

int* twoSum(int* nums, int numsSize, int target) {
    int *result;
    HashMap *map;
    HashNode *node;
    int i;
    int rest;
    
    if ((result = malloc(2 * sizeof(int))) == NULL)
        return NULL;
    map = hash_init(2 * numsSize);
    
    for (i = 0; i < numsSize; ++i) {
        rest = target - nums[i];
        if ((node = hash_get(map, rest))) {
            result[0] = node->value;
            result[1] = i;
            hash_free(map);
            return result;
        } else
            hash_set(map, nums[i], i);
    }
    hash_free(map);
    return NULL;
}