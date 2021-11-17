/**
 * VUT IFJ Project 2021.
 *
 * @file ibuffer.c
 * 
 * @brief Implementation of instruction buffer
 * 
 * @author Vojtěch Eichler 
 * @author Václav Korvas
 * @author Tomáš Matuš
 * @author Adam Zvara
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ibuffer.h"

char *inst_create(size_t inst_size)
{
    char *inst = malloc(inst_size);
    if (inst == NULL) {
        return NULL;
    }
    memset(inst, 0, sizeof(*inst));

    return inst;
}

ibuffer_t *ibuffer_create(size_t buffer_size, size_t inst_size)
{
    ibuffer_t *buffer = malloc(sizeof(*buffer) + buffer_size*(sizeof(char *)));
    if (buffer == NULL) {
        return NULL;
    }

    buffer->inst_size = inst_size;
    buffer->size = buffer_size;
    buffer->length = 0;

    // allocate space for strings in flexible array member
    for (size_t i = 0; i < buffer->size; i++) {
        buffer->inst[i] = inst_create(buffer->inst_size);
        if (buffer->inst[i] == NULL) {
            return NULL;
        }
    }

    return buffer;
}

void ibuffer_clear(ibuffer_t *buffer)
{
    for (size_t i = 0; i < buffer->length; i++) {
        memset(buffer->inst[i], 0, sizeof(buffer->inst_size));
    }
    
    buffer->length = 0;
}

void ibuffer_print(ibuffer_t *buffer)
{
    for (size_t i = 0; i < buffer->length; i++) {
        printf("%s", buffer->inst[i]);
    }
}

void ibuffer_free(ibuffer_t *buffer)
{
    if (buffer == NULL) {
        return;
    }

    // free strings in buffer
    for (size_t i = 0; i < buffer->size; i++) {
        free(buffer->inst[i]);
    }

    buffer->length = 0;
    buffer->size = 0;

    free(buffer);
}