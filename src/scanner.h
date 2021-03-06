/**
 * VUT IFJ Project 2021.
 *
 * @file scanner.h
 *
 * @brief Definition of scanner
 *
 * @author Vojtěch Eichler 
 * @author Václav Korvas
 * @author Tomáš Matuš
 * @author Adam Zvara
 */

#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "str.h"

typedef enum {
	TOK_ID,				// Identifier
	TOK_KEYWORD,		        // Keyword
	TOK_EOF,			// EOF
	TOK_NOTHING,	

	TOK_EQ,				// Equal (==)
	TOK_NEQ,			// Not equal (~=)
	TOK_LES,			// Less than (<)
	TOK_LES_EQ,			// Less and equal (<=)
	TOK_GR,				// Greater than (>)
	TOK_GR_EQ,			// Greater and equal (>=)
	TOK_ASSIGN, 		        // ASSIGN (=)

	TOK_LEN,			// Length (#)
	TOK_PLUS,			// +
	TOK_MINUS,			// -
	TOK_MUL,			// *
	TOK_DIV,			// Divide two numbers (/) 
	TOK_INT_DIV,		        // Divide two int numbers (//)
	TOK_CONCAT,			// Concatenation (..)
	
	TOK_RBRACKET, 		        // )
	TOK_LBRACKET, 		        // (
	
	TOK_COMMA, 			// ,
	TOK_COLON, 			// :
	TOK_INT,
	TOK_DECIMAL,
	TOK_STRING,

} token_type_t;

typedef enum {
	KW_DO,
	KW_ELSE,
	KW_END,
	KW_FUNCTION,
	KW_GLOBAL,
	KW_IF,
	KW_INTEGER,
	KW_LOCAL,
	KW_NIL,
	KW_NUMBER,
	KW_REQUIRE,
	KW_RETURN,
	KW_STRING,
	KW_THEN,
	KW_WHILE,

} keyword_t;

typedef union {
	string_t s;
	double decimal;
	int number;
	keyword_t keyword;
} token_attribute_t;

typedef struct {
	token_attribute_t attribute;
	token_type_t type;
} token_t;

/**
 * @brief Main scanner function, scans stdin and sends further corresponding token
 *
 * @param token Pointer to token, where all important info is stored
 *
 * @return SUCCESS (0) if successful, else one of error return codes from error.h
 */

int get_token(token_t* token);

#endif //_SCANNER_H_
