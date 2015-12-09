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


#define MAX_CHAR_FILE 5000
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
void insertarNodoLista(bignumNodo_t ** , ushort ,bignumNodo_t *);
operation_status_t cargarStructNumerosList(operationList_t **,size_t *,size_t *,char *,char *, opt_t *,size_t ,operation_status_t status);
operation_status_t AddOperationList(operationList_vector_t *);
operation_status_t inicializarStructOperationList(operationList_vector_t * );
void imprimirLista(bignumNodo_t * );
void sumaLista( operationList_vector_t *, size_t *);
ushort * suma_digito_a_digito_List (bignumNodo_t *,bignumNodo_t *, size_t , size_t , size_t *);
void restaLista(operationList_vector_t *, size_t *);
ushort * resta_digito_a_digito_List (bignumNodo_t *, bignumNodo_t *, size_t , size_t , size_t *);
void multiplicarLista( operationList_vector_t *, size_t *);
ushort * multiplico_List (bignumNodo_t *,bignumNodo_t *, size_t , size_t ,size_t *);
void freeLista(bignumNodo_t **);
void inserto_valor_en_lista(bignumNodo_t **,ushort , size_t);
ushort valor_en_lista(bignumNodo_t *,int );
void printArrayShort(ushort *,size_t ,sign_t ,size_t );
operation_status_t GrabarOperaciones(operationList_vector_t *);
operation_status_t leerOperaciones(operationList_vector_t *);

#endif /* defined(__Tp4__bignumList__) */
