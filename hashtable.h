#ifndef HASHTABLE
#define HASHTABLE

struct variable_s {
        char* variable_name;
        char* value;
        int type;
        int scope;
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
void                ht_destroy(hashtable_t* hashtable);

variable_t*         ht_variable(char* variable_name, char* value, int type, int scope);

void                ht_set(hashtable_t* hashtable, char* variable_name, char* value, int type, int scope);
char*               ht_get(hashtable_t* hashtable, char* variable_name);

int                 ht_hash(hashtable_t* hashtable, char* variable_name);

int                 ht_variable_check_declared_in_scope(hashtable_t* hashtable, char* variable_name, int scope);
void                ht_variable_delete_all_in_scope(hashtable_t* hashtable, int scope);

void                ht_print(hashtable_t* hashtable);

#endif