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
    (*pp_fila)->queue_size = tam_fila;
    (*pp_fila)->begin = 0;
    (*pp_fila)->end = 0;

    return SUCCESS;
}


/*************************/
/* Destruction operation */
/*************************/
int destroy(ppFila pp_fila){
    for(int element_idx = 0; element_idx<(*pp_fila)->queue_size; element_idx++){
        free((*pp_fila)->element_list[element_idx].data); /*Free data of each element*/    
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

    int element_count = pilha_element_count(p_fila);

    if(element_count == p_fila->queue_size) return FAIL; /* Queue full */

    p_fila->element_list[p_fila->end].data = malloc(tam_dado);

    if(NULL == p_fila->element_list[p_fila->end].data) return FAIL; /* Unable to allocate memory for entry */

    memcpy(p_fila->element_list[p_fila->end].data, p_dado, tam_dado);

    p_fila->element_list[p_fila->end].data_size = tam_dado;
    p_fila->element_list[p_fila->end].data_type = tipo_dado;
    
    p_fila->end++;
    if(p_fila->end > p_fila->queue_size) p_fila->end = 0; /* Wrap around circle queue */

    return SUCCESS;
}

/*-------------------------------------------------------------------------*/
int dequeue(pFila p_fila, void ** pp_dado, int * p_tipo_dado){
    if(p_fila == NULL) return FAIL;

    printf("\nDequeue:\n");
    printf("p_fila->begin: %d\n", p_fila->begin);
    printf("p_fila->end: %d\n", p_fila->end);

    int element_count = pilha_element_count(p_fila);

    if(element_count == 0) return FAIL; /* Empty Queue */

    *pp_dado = malloc(p_fila->element_list[p_fila->begin].data_size);

    if(NULL == *pp_dado) return FAIL; /* Unable to allocate memory for return */

    memcpy(*pp_dado, p_fila->element_list[p_fila->begin].data, p_fila->element_list[p_fila->begin].data_size);

    *p_tipo_dado = p_fila->element_list[p_fila->begin].data_type;
    free(p_fila->element_list[p_fila->begin].data); /* Free element memory */

    p_fila->begin++;
    if(p_fila->begin > p_fila->queue_size) p_fila->begin = 0; /* Wrap around circle queue */

    printf("p_fila->begin: %d\n", p_fila->begin);
    printf("p_fila->end: %d\n", p_fila->end);
    printf("\n");

    return SUCCESS;
}


/***************************/
/* Internal handlers       */
/***************************/

int pilha_element_count(pFila p_fila){

    if(p_fila->end >= p_fila->begin){
        return p_fila->end - p_fila->begin;
    }
    else{
        return 1 + p_fila->end + (p_fila->queue_size - p_fila->begin);
    }
}

