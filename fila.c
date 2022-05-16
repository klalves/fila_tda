/*************************************************************
 * Generic queue model developed in the context
 * of the PAA Discipline
 *************************************************************/

#include "fila_privado.h"

/********************************/
/* Internal Handlers Prototypes */
/********************************/
int pilha_element_count(pFila p_fila);


/**********************/
/* Creation operation */
/**********************/
int init(ppFila pp_fila, int tam_fila, int tam_max_item){
    /* Memory allocation */
    (*pp_fila) = (pFila)malloc(sizeof(fila_t));
    if( (*pp_fila) == NULL) return FAIL;

    (*pp_fila)->element_list = malloc(tam_fila * sizeof(fila_element_t));
    (*pp_fila)->queue_max_size = tam_fila;
    (*pp_fila)->queue_size = 0;
    (*pp_fila)->begin = 0;

    return SUCCESS;
}


/*************************/
/* Destruction operation */
/*************************/
int destroy(ppFila pp_fila){
    for(int element_idx = 0; element_idx<(*pp_fila)->queue_max_size; element_idx++){
        if(NULL != (*pp_fila)->element_list[element_idx].data){
            free((*pp_fila)->element_list[element_idx].data); /*Free data of each element*/
        }
    }
    free((*pp_fila)->element_list); /*Free element list*/
    free(*pp_fila);
    return SUCCESS;
}


/*********************/
/* Access operations */
/*********************/


/***************************/
/* Manipulation operations */
/***************************/

/*-------------------------------------------------------------------------*/
int enqueue(pFila p_fila, void * p_dado, int tipo_dado, int tam_dado){
    if(p_fila == NULL) return FAIL;

    if(p_fila->queue_size == p_fila->queue_max_size) return FAIL; /* Queue full */

    int end = p_fila->begin + p_fila->queue_size;
    if(end >= p_fila->queue_max_size){ /*Wrap around if necessary*/
        end -= p_fila->queue_max_size;
    }

    p_fila->element_list[end].data = malloc(tam_dado);

    if(NULL == p_fila->element_list[end].data) return FAIL; /* Unable to allocate memory for entry */

    memcpy(p_fila->element_list[end].data, p_dado, tam_dado);

    p_fila->element_list[end].data_size = tam_dado;
    p_fila->element_list[end].data_type = tipo_dado;
    
    p_fila->queue_size++;

    return SUCCESS;
}

/*-------------------------------------------------------------------------*/
int dequeue(pFila p_fila, void ** pp_dado, int * p_tipo_dado){
    if(p_fila == NULL) return FAIL;

    if(p_fila->queue_size == 0) return FAIL; /* Empty Queue */

    *pp_dado = malloc(p_fila->element_list[p_fila->begin].data_size);

    if(NULL == *pp_dado) return FAIL; /* Unable to allocate memory for return */

    memcpy(*pp_dado, p_fila->element_list[p_fila->begin].data, p_fila->element_list[p_fila->begin].data_size);

    *p_tipo_dado = p_fila->element_list[p_fila->begin].data_type;
    free(p_fila->element_list[p_fila->begin].data); /* Free element memory */
    p_fila->element_list[p_fila->begin].data = NULL;

    p_fila->begin++;
    if(p_fila->begin >= p_fila->queue_max_size) p_fila->begin = 0; /* Wrap around circle queue */

    p_fila->queue_size--;

    return SUCCESS;
}


/************************/
/*  Internal handlers  */
/***********************/