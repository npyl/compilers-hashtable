#ifndef HASHTABLE
#define HASHTABLE

struct variable_s {
        char* key;
        char* value;
        struct variable_s* next;
};

typedef struct variable_s variable_t;

struct hashtable_s {
        int size;
        variable_t** table;
};

typedef struct hashtable_s hashtable_t;

//
// Functions
//

hashtable_t*        ht_create(int size);
int                 ht_hash(hashtable_t* hashtable, char* key);
variable_t*         ht_newpair(char* key, char *value);
void                ht_set(hashtable_t* hashtable, char* key, char* value);
char*               ht_get(hashtable_t* hashtable, char* key);

#endif