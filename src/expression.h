/**
 * VUT IFJ Project 2021.
 *
 * @file expression.h
 *
 * @brief header file for expression.c
 *
 * @author Vojtěch Eichler
 * @author Václav Korvas
 * @author Tomáš Matuš
 * @author Adam Zvara
 */

#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "scanner.h"
#include "symtable.h"
#include "error.h"
#include "parser.h"
#include "str.h"

#define TABLE_SIZE 9
// return values
#define EC_FUNC 98
#define T_INT 100
#define T_NUM 101
#define T_STR 102
#define T_NIL 103
#define T_NONE 104

#define FREE_STRING_TOKEN(token) \
    do { \
        if (token->type == TOK_STRING || token->type == TOK_ID) \
            str_free(&token->attribute.s); \
    } while(0);

#define GET_NEW_TOKEN(token, ret) \
    do {             \
        FREE_STRING_TOKEN(token)    \
        ret = get_token(token); \
        if (ret) {     \
            return ret; \
        }    \
    } while(0);

#define EXIT_ON_ERROR(ret) \
    do { \
        free(new_token); \
        stack_dispose(&stack_prec); \
        *return_token = NULL; \
        return ret; \
    } while(0);



typedef enum
{
    // #
    STR_LEN, // 0

    // * / '//'
    MUL, // 1
    DIV, // 2
    DIV_INT, // 3

    // + -
    PLUS, // 4
    MINUS, // 5

    // ..
    CONCAT, // 6

    // = ~= < <= > >=
    EQ, // 7
    NOT_EQ, // 8
    LESS, // 9
    LESS_EQ, // 10
    GREAT, // 11
    GREAT_EQ, // 12

    // (
    LEFT_BR, // 13

    // )
    RIGHT_BR, // 14

    // id
    ID, // 15
    INT, // 16
    NUM, // 17
    STR, // 18
    NIL, // 19

    // $
    DOLLAR, // 20

    // <
    HANDLE, // 21

    NON_TERM // 22
} prec_table_term_t;

typedef enum
{
    I_STR_LEN,
    I_MUL_DIV,
    I_PLUS_MINUS,
    I_CONCAT,
    I_RELATION,
    I_LEFT_BR,
    I_RIGHT_BR,
    I_ID,
    I_DOLLAR
} prec_table_index_t;

/**
 * @brief Converts token to expression type symbol
 *
 * @param token current token
 *
 * @return type symbol
 */
int token_to_symbol(token_t *token);

/**
 * @brief Converts symbol to index in precedence table
 *
 * @param symbol symbol
 *
 * @return index in precedence table
 */
prec_table_index_t symbol_to_index(int symbol);

/**
 * @brief Function to perform reduction following set rules
 *
 * @param stack Initialized stack
 *
 * @return Syntax error or success
 */
int reduce(stack_t *stack);

/**
 * @brief Function to perform semantic checks
 *
 * @param token current token
 * @param stack Initialized stack
 * @param type type of expression
 *
 * @return Semantic error or success
 */
int check_semantic(token_t *token, stack_t *stack, int *type);

void push_operand(token_t *token, int *type);

/**
 * @brief performs syntactic and semantic analysis on expression
 *
 * @param return_token last read token
 *
 * @return Expression data type on success
 * @return ERROR_SYNTAX, ERROR_SEMANTIC, ERROR_SEMANTIC_TYPE, ERROR_NIL on failure
 * @return EC_FUNC when function ID is read
 */
int expression(token_t **return_token);

#endif // _EXPRESSION_H_
