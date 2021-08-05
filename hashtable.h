#ifndef HASHTABLE
#define HASHTABLE

struct variable_s {
        char* variable_name;
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
variable_t*         ht_variable(char* variable_name, char* value, int type, int scope);
void                ht_set(hashtable_t* hashtable, char* key, char* value);
char*               ht_get(hashtable_t* hashtable, char* key);

#endif