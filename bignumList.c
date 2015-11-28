//
//  bignumList.c
//  Tp4
//
//  Created by fmonpelat on 11/25/15.
//  Copyright (c) 2015 ___FMONPELAT___. All rights reserved.
//

#include "bignumList.h"

/*
 typedef struct bignumNodo {
 
 unsigned short val;
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

*/

operation_status_t inicializarStructOperationList(operationList_vector_t * oper ){
    
    operationList_t **ppAux=NULL;
    operationList_t *pAux;
    oper->operacionesList=NULL;
    oper->operList_size=0;
    
    
    if ( !(ppAux=(operationList_t **)realloc(oper->operacionesList,( sizeof(operationList_t*)) ) )  )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    (oper->operacionesList)=ppAux;
    
    if (!(pAux=(operationList_t *)malloc(sizeof(operationList_t) )) ) {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    oper->operacionesList[0]=pAux;
    
    
    /* pido memoria para cada bignum_t */
    if( !(oper->operacionesList[0]->op1=(bignumList_t *)malloc( sizeof(bignumList_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper->operacionesList[0]->op2=(bignumList_t *)malloc( sizeof(bignumList_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    /* inicializamos la lista de digitos */
    oper->operacionesList[0]->op1->digits=NULL;
    oper->operacionesList[0]->op2->digits=NULL;
    oper->operacionesList[0]->op=NOOPERATION;
    oper->operList_size=0;
    
    
    return OK;
}


operation_status_t AddOperationList(operationList_vector_t *oper){
    
    operationList_t **ppAux=NULL;
    operationList_t *pAux;
    
    
    if ( !(ppAux=(operationList_t **)realloc(oper->operacionesList,(sizeof(operationList_t*) * (oper->operList_size+1) ) ) )  )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    (oper->operacionesList)=ppAux;
    
    if (!(pAux=(operationList_t *)malloc(sizeof(operationList_t) )) ) {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    oper->operacionesList[oper->operList_size]=pAux;
    
    
    /* pido memoria para cada bignum_t */
    if( !(oper->operacionesList[0]->op1=(bignumList_t *)malloc( sizeof(bignumList_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper->operacionesList[0]->op2=(bignumList_t *)malloc( sizeof(bignumList_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    
    /* inicializamos la lista de digitos */
    oper->operacionesList[oper->operList_size]->op1->digits=NULL;
    oper->operacionesList[oper->operList_size]->op2->digits=NULL;
    
    
    oper->operacionesList[oper->operList_size]->op=NOOPERATION;
    
    return OK;
}



operation_status_t cargarStructNumerosList(operationList_t **oper,size_t *size,size_t *pos,char *num1,char *num2, opt_t *operation,size_t precision,operation_status_t status)
{
    
    size_t size_num1=0;
    size_t size_num2=0;
    size_t i=0;
    
    size_num1=strlen(num1);
    size_num2=strlen(num2);
    
    /* corroboracion para no pasarnos del array */
    if ( (*pos)>(*size) ) return ERROR;
    
    
    /* hay que llamar a la funcion de insertarNodo
    
    if( !( oper[*pos]->op1->digits=(ushort *)malloc( sizeof(ushort)*(size_num1-1)) ) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper[*pos]->op2->digits=(ushort *)malloc(sizeof(ushort)*(size_num2-1))) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
     */
    
    if (num1[0]=='-') {
        oper[*pos]->op1->sign=NEGATIVE;
    }
    else if (num1[0]=='+') {
        oper[*pos]->op1->sign=POSITIVE;
    }
    else oper[*pos]->op1->sign=POSITIVE;
    
    if (num2[0]=='-') {
        oper[*pos]->op2->sign=NEGATIVE;
    }
    else if (num2[0]=='+') {
        oper[*pos]->op2->sign=POSITIVE;
    }
    else oper[*pos]->op2->sign=POSITIVE;
    
    
    /* Empezamos de 1 porque nos comemos el caracter de signo que se lo asignamos arriba */
    for (i=1; i<size_num1; i++)
    {
        insertarNodoLista(&(oper[*pos]->op1->digits), (ushort)(num1[i] - '0'), oper[*pos]->op1->digits);
        /* hay que llamar a insertar nodo
         oper[*pos]->op1->digits[i-1]=(ushort)(num1[i] - '0');
         */
    }
    for (i=1; i<size_num2; i++)
    {
        insertarNodoLista(&(oper[*pos]->op2->digits), (ushort)(num2[i] - '0'), oper[*pos]->op2->digits);
        /*
        oper[*pos]->op2->digits[i-1]=(ushort)(num2[i] - '0');
         */
    }
    
    /* Agregamos q digits para saber hasta donde debemos iterar */
    oper[*pos]->op1->q_digits=size_num1-1;
    oper[*pos]->op2->q_digits=size_num2-1;
    
    /* agregamos la operacion a efectuar */
    oper[*pos]->op=*operation;
    
    oper[*pos]->op1->inf=NEGATIVE;
    oper[*pos]->op2->inf=NEGATIVE;
    
    /* preguntamos si excedemos la precision */
    if (oper[*pos]->op1->q_digits>precision) {
        oper[*pos]->op1->inf=POSITIVE;
        return INF;
    }
    if (oper[*pos]->op2->q_digits>precision) {
        oper[*pos]->op2->inf=POSITIVE;
        return INF;
    }
    
    if(status==_EOF) return ERROR;
    
    return OK;
    
}



void insertarNodoLista(bignumNodo_t ** lista, ushort valor,bignumNodo_t *anterior){
    
    //bignumNodo_t * auxLista=NULL;
    
    if (!*lista) {
        (*lista)=(bignumNodo_t*)malloc( sizeof(bignumNodo_t) );
        (*lista)->val=valor;
        (*lista)->sig=NULL;
        (*lista)->ant=anterior;
        
    }
    else insertarNodoLista(&((*lista)->sig), valor,*lista/*Creo que este parámetro está mal, no va (*lista)->sig ??*/);
    
}



void imprimirLista(bignumNodo_t * lista){
    
    if ( lista == NULL ) {
        return;
    }
    if ( !(lista->sig) ) {
        printf("%hu\n",lista->val);
        return;
    }
    printf("%hu\n",lista->val);
    imprimirLista(lista->sig);
    
}

ushort valor_en_lista(bignumNodo_t *dig,int i)
{
    size_t j=0;
    bignumNodo_t *aux=NULL;
    for(aux=dig;aux->sig!=NULL;aux=aux->sig)
    {
	if(j==i) break;
	j++;
    }
    return aux->val;
}

ushort * suma_digito_a_digito_List (bignumNodo_t *dig1,bignumNodo_t *dig2, size_t cant1, size_t cant2, size_t *q_resultado)
{
    size_t carry=0;
    ushort *resultado=NULL;
    int dif=cant1-cant2;
    int i;

    if (!(resultado = (ushort*)malloc(sizeof(ushort)*(cant1+1))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    for(i=cant1-1;i>=0;i--)
    {
        if(i-dif<0)
        {
            resultado[i+1]=valor_en_lista(dig1,i)+carry;
            carry=0;
        }
        else
            resultado[i+1]=valor_en_lista(dig1,i)+valor_en_lista(dig2,i-dif)+carry;
        
        carry=0;

        if(resultado[i+1]>9)
        {
            
            resultado[i+1]=resultado[i+1]-10;
            carry++;
            
        }
    }
    resultado[0]=carry;
    *q_resultado=cant1+1;
    
    return resultado;
}

ushort * resta_digito_a_digito_List (bignumNodo_t *dig1, bignumNodo_t *dig2, size_t cant1, size_t cant2, size_t *q_resultado)
{
    ushort *resultado=NULL;
    int carry=0,dif;
    int i=0;
    
    dif=cant1-cant2;
    
    if (!(resultado = (ushort*)malloc(sizeof(ushort)*(cant1))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    for(i=cant1-1;i>=0;i--)
    {
        if (i-dif<0)
        {
	    resultado[i]=valor_en_lista(dig1,i)-carry;
            carry=0;
	}
        else if( (valor_en_lista(dig1,i) -carry )<(valor_en_lista(dig2,i-dif)))
        {
            resultado[i]=10+valor_en_lista(dig1,i)-carry-valor_en_lista(dig2,i-dif);
            if(carry==0) carry++;
        }
        else
        {
            resultado[i]=valor_en_lista(dig1,i)-carry-valor_en_lista(dig2,i-dif);
            carry=0;
        }
    }
    *q_resultado=cant1;
    return resultado;
}






void inserto_valor_en_lista(bignumNodo_t ** lista,ushort num, size_t i)
{
    size_t j=0; 
    bignumNodo_t *aux;
    for(aux=(*lista);aux->sig!=NULL;aux=aux->sig)
    {
	if (j==i) break;
	j++;

    }
    aux->val=num;
}
	
void freeLista(bignumNodo_t **lista)
{
    if(!((*lista)->sig))
	free(*lista);
    else freeLista(&((*lista)->sig));
}
    

bignumNodo_t * multiplico_List (bignumNodo_t *dig1,bignumNodo_t *dig2, size_t cant1, size_t cant2,size_t * q_resultado)
{
    bignumNodo_t ** res_matriz=NULL;
    int i,k,j,cont=0;
    int carry=0;
    bignumNodo_t * resAux=NULL;
    ushort * res=NULL;
    ushort num;
    if (!(  res_matriz = (bignumNodo_t**)malloc(sizeof(bignumNodo_t*)*(cant2))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    for(k=0;k<cant2;k++)
    {
        for(i=0;i<cant1+1+k;i++)
	{
		insertarNodoLista(&(res_matriz[k]),0,res_matriz[k]);
	}
    }
    
    k=0;
    while(k<cant2)
    {

        for(j=cant2-1;j>=0;j--)
        {
            carry=0;
            for(i=cant1-1;i>=0;i--)
            {
		num= ( valor_en_lista(dig2,j)*valor_en_lista(dig1,i) ) + carry;
		              
		if (num<=9) 
		{
			inserto_valor_en_lista(&(res_matriz[k]),num,i+1);		
			carry=0;
		}
		else                
		if (num>9)
                {
                    carry=findCarry(num);
                    inserto_valor_en_lista(&(res_matriz[k]),num-10*carry,i+1);
		
                }
            }
            inserto_valor_en_lista(&(res_matriz[k]),carry,0);
            k++;
        }
    }
    
    /* CREO LISTA resAux con cant1+cant2 ceros*/
    for(i=0;i<cant1+2*cant2;i++) /*Lleno resAux con ceros para poder hacer la suma*/
    {  
    	insertarNodoLista(&(resAux),0,resAux);
    }
    for(k=cant2-1;k>=0;k--)   /*Este es el procedimiento para que vaya sumando desde la ultima fila de la matriz, hacia arriba.*/
    {
        res=suma_digito_a_digito(resAux,res_matriz[k],cant1+cant2+cont,cant1+1+k,q_resultado);
        ++cont;

	/*Paso res a una lista*/
	for(i=0;i<cant1+cant2+cont;i++)
	{
	    num=res[i];
	    insertarNodoLista(&(resAux),num,resAux);
	}
 	
        free(res);
         
    }
    *q_resultado=cant1+cant2+cont;
    
    for(k=0;k<cant2;k++)
    {
	for(i=0;i<cant1+1+k;i++)
	{        
            freeLista(&(res_matriz[k]));
	}
    }
    free(res_matriz);
    
    return resAux;	/* Esta no devuelve un vector, devuelve una lista. Para imprimirla afuera hay q llamar a imprimirLista */
}


