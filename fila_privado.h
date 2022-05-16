/*************************************************************
 * Generic queue model developed in the context
 * of the PAA Discipline
 *************************************************************/

#include "fila.h"

typedef struct fila_element_t{
    void * data; /* Pointer to data storage */
    int data_size;
    int data_type;
}fila_element_t;

typedef struct fila_t{
    fila_element_t * element_list;
    int queue_max_size;
    int queue_size;
    int begin;
}fila_t;

