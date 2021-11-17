/**
 * VUT IFJ Project 2021.
 *
 * @file symtable.h
 *
 * @brief Definition of symtable and stack used for syntactic analysis
 *
 * @author Vojtěch Eichler 
 * @author Václav Korvas
 * @author Tomáš Matuš
 * @author Adam Zvara
 */

/* Implementation of hash table was taken from Language C course,
 * original implementation was made by Vojtech Eichler (xeichl01) */

#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

#define GLOBAL_SYM_SIZE 20
#define LOCAL_SYM_SIZE	20

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "str.h"

// Identificator types
typedef enum type_t {
	STR_T,
	INT_T,
	NUM_T,
	NIL_T
} type_t;

/**
 * @brief Information about identificators
 */
struct local_data {
	string_t name;
	type_t type;
	bool init;
};

/**
 * @brief Information about local symtable for single function
 */
typedef struct local_symtab {
	string_t key;
	unsigned int depth;				// Level of depth (if, while ...)
	unsigned int size;				// Amount of stored variables
	unsigned int alloc_size;		// Size of allocated space for variables
	struct local_symtab *next;		// Pointer to next local TS (creating linked list)
	struct local_data *data[];		// Variables inside function
} local_symtab_t;

/**
 * @brief Information about function
 */
struct global_item {
	bool defined;
	string_t key;				// Name of function
	string_t retvals;			// Function return values in string format
	string_t params;			// Parameters of function in string format
	struct global_item *next;
	//TODO: maybe add names of parameters with their types?
};

/**
 * @brief Global symtable containing list of declared functions
 */
typedef struct global_symtab {
	unsigned int size;
	struct global_item *func[];
} global_symtab_t; 

/**
 * @brief Create index to hashtable from string
 * @param key Key in string format
 * @return Index to hashtable based on key
 */
int hash_function(string_t key);

/**
 * @brief Create global symtable with initialized values
 * @return Initialized global symtable
 */
global_symtab_t *global_create();

/**
 * @brief Find function in global symtable 
 * @param gs Pointer to global symtable
 * @param key Function name
 * @return Pointer to found function or NULL
 */
struct global_item *global_find(global_symtab_t *gs, string_t key);

/**
 * @brief Insert new function to gs, if no function with same key is found
 * @param gs Pointer to global symtable
 * @param key Function name
 * @return Pointer to found/created function
 */
struct global_item *global_add(global_symtab_t *gs, string_t key);

// dont need these functions as they are just str_add_char()
// global_add_param = str_add_char(global_item, first char of param);
// global_add_retval = str_add_char(global_item, first char of retvals);

/**
 * @brief Create local symtable 
 * @param key Name of function
 * @return Pointer to newly created local symtable
 */
local_symtab_t *local_create(string_t key);

/**
 * @brief Create new depth of last function in local symtable
 * @param previous Pointer to local symtable
 * @return 0 if successful, otherwise ERROR_INTERNAL TODO: maybe change
 */
int local_new_depth(local_symtab_t **previous);

/**
 * @brief Add new variable into local symtable
 * @param name Name of new variable
 * @return Pointer to new variable
 */
struct local_data *local_add(local_symtab_t *act, string_t name);

#endif
