#include "aplicacao.h"

typedef struct{
    char data_char;
    char data_int;
    char data_float;
} app_test_struct_t;

enum {
    APP_TYPE_CHAR,
    APP_TYPE_INT,
    APP_TYPE_FLOAT,
    APP_TYPE_TEST_STRUCT
} app_types;

int main(int argc, char **argv)
{
    pFila p_fila;

    /* Variables to write */
    char value_char = 'c';
    int value_int = 12;
    int value_float = 3.4;
    app_test_struct_t test_struct;
    test_struct.data_char = 'e';
    test_struct.data_int = 37;
    test_struct.data_float = 54.7;

    /* Variable to read */
    void * data_reception;
    int type_get;

    /* Creation test */
    printf("\n\nCreation test:\n");
    if(FAIL == init(&p_fila, 4, 0)) exit(1);
    printf("Creation OK.\n");

    /* Enqueue test */
    printf("\n\nEnqueue test:\n");
    if(FAIL == enqueue(p_fila, &value_char, APP_TYPE_CHAR, sizeof(char)))  exit(1);
    printf("value_char enqueued.\n");
    if(FAIL == enqueue(p_fila, &value_int, APP_TYPE_INT, sizeof(int)))  exit(1);
    printf("value_int enqueued.\n");
    if(FAIL == enqueue(p_fila, &value_float, APP_TYPE_FLOAT, sizeof(float)))  exit(1);
    printf("value_float enqueued.\n");
    if(FAIL == enqueue(p_fila, &test_struct, APP_TYPE_TEST_STRUCT, sizeof(app_test_struct_t)))  exit(1);
    printf("test_struct enqueued.\n");
    printf("Enqueue test OK.\n");

    /* Enqueue with queue full test */
    printf("\n\nEnqueue with queue full test:\n");
    if(SUCCESS == enqueue(p_fila, &value_char, APP_TYPE_CHAR, sizeof(char)))  exit(1);
    printf("Test OK -> Unable to enqueue as expected.\n");

    /* Dequeue test */
    printf("\n\nDequeue test:\n");

    if(FAIL == dequeue(p_fila, &data_reception, &type_get))  exit(1);
    printf("value_char dequeued.\n");
    if(type_get != APP_TYPE_CHAR) exit(1);
    if(*(char*)data_reception != value_char) exit(1);
    free(data_reception);
    printf("value_char correct value.\n");

    if(FAIL == dequeue(p_fila, &data_reception, &type_get))  exit(1);
    printf("value_int dequeued.\n");
    if(type_get != APP_TYPE_INT) exit(1);
    if(*(int*)data_reception != value_int) exit(1);
    free(data_reception);
    printf("value_int correct value.\n");

    if(FAIL == dequeue(p_fila, &data_reception, &type_get))  exit(1);
    printf("value_float dequeued.\n");
    if(type_get != APP_TYPE_FLOAT) exit(1);
    if(*(int*)data_reception != value_float) exit(1);
    free(data_reception);
    printf("value_float correct value.\n");

    if(FAIL == dequeue(p_fila, &data_reception, &type_get))  exit(1);
    printf("test_struct dequeued.\n");
    if(type_get != APP_TYPE_TEST_STRUCT) exit(1);
    app_test_struct_t * p_test_struct_get;
    p_test_struct_get = data_reception;
    if(p_test_struct_get->data_char  != test_struct.data_char ) exit(1);
    if(p_test_struct_get->data_int   != test_struct.data_int  ) exit(1);
    if(p_test_struct_get->data_float != test_struct.data_float) exit(1);
    free(data_reception);
    printf("test_struct correct value.\n");
    printf("Dequeue test OK.\n");

    /* Dequeue with queue empty test */
    printf("\n\nDequeue with queue empty test:\n");
    if(SUCCESS == dequeue(p_fila, &data_reception, &type_get))  exit(1);
    printf("Test OK -> Unable to dequeue as expected.\n");

    /* Destruction test */
    printf("\n\nDestruction test:\n");
    if(FAIL == destroy(&p_fila)) exit(1);
    printf("Destruction OK.\n");
}
