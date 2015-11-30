//
//  bignumList.h
//  Tp4
//
//  Created by fmonpelat on 11/25/15.
//  Copyright (c) 2015 ___FMONPELAT___. All rights reserved.
//

#ifndef __Tp4__bignumList__
#define __Tp4__bignumList__

#include <stdio.h>
#include "bignum.h"

typedef unsigned short ushort;

typedef struct bignumNodo {
    
    ushort val;
    struct bignumNodo *sig;
    struct bignumNodo *ant;
    
} bignumNodo_t;


typedef struct bignumLis {
    
    bignumNodo_t *digits;
    size_t q_digits;
    sign_t sign ;
    sign_t inf;
    
} bignumList_t;

typedef struct operationList {
    
    bignumList_t *op1;
    bignumList_t *op2;
    opt_t op;
    ushort *rst;
    size_t q_rst;
    sign_t sign_rst;
    sign_t inf_rst;
    result_state_t st;
    
} operationList_t;

typedef struct operationList_vector  {
    
    operationList_t **operacionesList;
    size_t operList_size;
    
} operationList_vector_t;


/*############ FUNCIONES ###################*/
void insertarNodoLista(bignumNodo_t ** lista, ushort valor,bignumNodo_t *anterior);
operation_status_t cargarStructNumerosList(operationList_t **oper,size_t *size,size_t *pos,char *num1,char *num2, opt_t *operation,size_t precision,operation_status_t status);
operation_status_t AddOperationList(operationList_vector_t *oper);
operation_status_t inicializarStructOperationList(operationList_vector_t * oper );
void imprimirLista(bignumNodo_t * lista);
void sumaLista( operationList_vector_t *oper, size_t *size);
ushort * suma_digito_a_digito_List (bignumNodo_t *dig1,bignumNodo_t *dig2, size_t cant1, size_t cant2, size_t *q_resultado);
void restaLista(operationList_vector_t *oper, size_t *size);
ushort * resta_digito_a_digito_List (bignumNodo_t *dig1, bignumNodo_t *dig2, size_t cant1, size_t cant2, size_t *q_resultado);
void multiplicarLista( operationList_vector_t *oper, size_t *size);
ushort * multiplico_List (bignumNodo_t *dig1,bignumNodo_t *dig2, size_t cant1, size_t cant2,size_t * q_resultado);

void freeLista(bignumNodo_t **lista);
void inserto_valor_en_lista(bignumNodo_t ** lista,ushort num, size_t i);
ushort valor_en_lista(bignumNodo_t *dig,int i);
void printArrayShort(ushort *,size_t ,sign_t ,size_t );




#endif /* defined(__Tp4__bignumList__) */
