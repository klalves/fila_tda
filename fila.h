/*************************************************************
 * Generic queue model developed in the context
 * of the PAA Discipline
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAIL
#define FAIL 1
#endif

typedef struct fila_t *pFila, **ppFila;


/**********************/
/* Creation operation */
/**********************/
int init(ppFila pp_fila, int tam_fila, int tam_max_item);


/*************************/
/* Destruction operation */
/*************************/
int destroy(ppFila pp_fila);


/*********************/
/* Access operations */
/*********************/


/***************************/
/* Manipulation operations */
/***************************/
int enqueue(pFila p_fila, void * p_dado, int tipo_dado, int tam_dado);
int dequeue(pFila p_fila, void ** pp_dado, int * p_tipo_dado);

