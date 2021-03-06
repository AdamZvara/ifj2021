/**
 * VUT IFJ Project 2021.
 *
 * @file generator.h
 *
 * @brief Header file for generator.c
 *
 * @author Vojtěch Eichler
 * @author Václav Korvas
 * @author Tomáš Matuš
 * @author Adam Zvara
 */

#ifndef _GENERATOR_H
#define _GENERATOR_H


#include <stdio.h>
#include "scanner.h"
#include "ibuffer.h"
#include "symtable.h"
#include "parser_helper.h"
#include "expression.h"
#include "builtin.h"


extern local_symtab_t *local_tab;   // local symtable from parser
extern global_symtab_t *global_tab; // global symtable from parser
extern ibuffer_t *buffer;           // instruction buffer from parser
extern ibuffer_t *defvar_buffer;    // buffer for declaring variables
extern parser_helper_t *p_helper;   // get context of parser

void generate_name(ibuffer_t *buffer, string_t name);

void generate_start();
void generate_entry();
void generate_end();
void generate_exit();

void generate_div_by_zero();
void generate_write_nil();
void generate_nil_with_operator();

void generate_label(string_t label_name);
void generate_parameters(parser_helper_t *p_helper);
void generate_retvals();
void generate_function(parser_helper_t *p_helper);
void generate_function_end();
void generate_function_skip_jump(string_t name);
void generate_function_skip_label(string_t name);

void generate_identifier(ibuffer_t *buffer, string_t id_name);

void generate_call_prep(parser_helper_t *p_helper);
void generate_call_params(token_t *token, parser_helper_t *p_helper);
void generate_call(parser_helper_t *p_helper);
void generate_return_value(int ret_counter);

void generate_write(token_t *token);

void generate_expr_start();
void generate_expr_end();
void generate_push_compare(prec_table_term_t op);
void generate_push_operator(prec_table_term_t op);
void generate_push_operand(token_t *token);

void generate_assign(string_t name);
void generate_assign_function(parser_helper_t *p_helper);

void generate_else();
void generate_if_else();
void generate_if_end();

void generate_while_start();
void generate_while_skip();
void generate_while_end();

void generate_num_conversion(unsigned index);
void generate_int_to_num();

#endif // _GENERATOR_H
