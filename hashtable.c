/*
 * taken from: https://gist.github.com/tonious/1377667/d9e4f51f05992f79455756836c9371942d0f0cee
 */

#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

// Create a new hashtable.
hashtable_t *ht_create(int size) 
{
    hashtable_t *hashtable = NULL;
    int i;

    if (size < 1) return NULL;

    // Allocate the table itself.
    if ((hashtable = malloc(sizeof(hashtable_t))) == NULL) 
        return NULL;
    
    // Allocate pointers to the head nodes.
    if ((hashtable->table = malloc(sizeof(variable_t*) * size)) == NULL) 
        return NULL;

    for (i = 0; i < size; i++)
        hashtable->table[i] == NULL;

    hashtable->size = size;

    return hashtable;
}

// Hash a string for a particular hash table.
int ht_hash(hashtable_t* hashtable, char* variable_name) 
{
    unsigned long int hashval;
    int i = 0;

    // Convert our string to an integer
    while (hashval < ULONG_MAX && i < strlen(variable_name)) 
    {
        hashval = hashval << 8;
        hashval += variable_name[ i ];
        i++;
    }

    return hashval % hashtable->size;
}

// Create a variable
variable_t* ht_variable(char* variable_name, char* value, int type, int scope)
{
    variable_t* new_variable;

    if ((new_variable = malloc(sizeof(variable_t))) == NULL)
        return NULL;

    if ((new_variable->variable_name = strdup(variable_name)) == NULL)
        return NULL;

    if ((new_variable->value = strdup(value)) == NULL ) 
        return NULL;

    new_variable->next = NULL;

    return new_variable;
}

// Insert a variable into a hash table. 
void ht_set(hashtable_t *hashtable, char* variable_name, char* value, int type, int scope)
{
    int bin = 0;
    variable_t* new_variable = NULL;
    variable_t* next = NULL;
    variable_t* last = NULL;

    bin = ht_hash( hashtable, variable_name );

    next = hashtable->table[ bin ];

    while( next != NULL && next->variable_name != NULL && strcmp( variable_name, next->variable_name ) > 0 ) {
        last = next;
        next = next->next;
    }

    // There's already a pair.  Let's replace that string.
    if( next != NULL && next->variable_name != NULL && strcmp( variable_name, next->variable_name ) == 0 ) {

        free( next->value );
        next->value = strdup( value );
        next->type = type;
        next->scope = scope;

        // Nope, could't find it.  Time to grow a pair.
    } 
    else 
    {
        new_variable = ht_variable( variable_name, value, type, scope);

        // We're at the start of the linked list in this bin.
        if( next == hashtable->table[ bin ] ) {
            new_variable->next = next;
            hashtable->table[ bin ] = new_variable;

        // We're at the end of the linked list in this bin.
        } else if ( next == NULL ) {
            last->next = new_variable;

        // We're in the middle of the list.
        } else  {
            new_variable->next = next;
            last->next = new_variable;
        }
    }
}

// Retrieve a variable_name-value pair from a hash table.
char* ht_get(hashtable_t *hashtable, char* variable_name) 
{
    int bin = 0;
    variable_t* pair;

    bin = ht_hash(hashtable, variable_name);

    // Step through the bin, looking for our value.
    pair = hashtable->table[bin];
    while (pair != NULL && pair->variable_name != NULL && strcmp(variable_name, pair->variable_name ) > 0) 
    {
        pair = pair->next;
    }

    // Did we actually find anything?
    if (pair == NULL || pair->variable_name == NULL || strcmp(variable_name, pair->variable_name) != 0)
            return NULL;
    else 
        return pair->value;   
}

/*
 * Priority should be given to scope = `scope`; scope = 0 (a.k.a. global) should be checked if first fails!
 */
int ht_variable_check_declared_in_scope(hashtable_t* hashtable, char* variable_name, int scope)
{
    return 0;
}

void ht_variable_delete_all_in_scope(hashtable_t* hashtable, int scope)
{
    for (int i = 0; i < hashtable->size; i++)
    {
        variable_t* previous = NULL;
        for (variable_t* cur = hashtable->table[i]; cur != NULL; cur = cur->next)
        {
            /* found variable of the specific scope; must remove and free() */
            if (cur->scope == scope)
            {
                /* if previous is not the first node, attach to it the next of cur */
                if (previous)
                    previous->next = cur->next;
                free(cur);
            }
            else
                previous = cur;
        }
    }
}

void ht_destroy(hashtable_t* hashtable)
{

}

int main( char *argc, char *argv ) {

    hashtable_t *hashtable = ht_create( 65536 );

    ht_set( hashtable, "variable_name1", "inky", 0, 0 );
    ht_set( hashtable, "variable_name2", "pinky", 0, 0 );
    ht_set( hashtable, "variable_name3", "blinky", 0, 0 );
    ht_set( hashtable, "variable_name4", "floyd", 0, 0 );

    printf( "%s\n", ht_get( hashtable, "variable_name1" ) );
    printf( "%s\n", ht_get( hashtable, "variable_name2" ) );
    printf( "%s\n", ht_get( hashtable, "variable_name3" ) );
    printf( "%s\n", ht_get( hashtable, "variable_name4" ) );

    return 0;
}