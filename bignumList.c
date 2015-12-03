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
    if( !(oper->operacionesList[oper->operList_size]->op1=(bignumList_t *)malloc( sizeof(bignumList_t) )) )
    {
        fprintf(stderr, "no memory \n");
        return NOMEM;
    }
    if( !(oper->operacionesList[oper->operList_size]->op2=(bignumList_t *)malloc( sizeof(bignumList_t) )) )
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

void printArrayShort(ushort *str,size_t size,sign_t sign,size_t precision){
    
    size_t i=0;
    int flag_print=0;

    
    if (sign==NEGATIVE) printf("-");
    
    for (i=0; i<size ; i++)
    {
        if( (str[i]!=0) || (flag_print) )
        {
            if(i!=precision)
            {
                printf("%d",str[i]);
                flag_print=1;
            }
            else
            {
                printf("\nOverflow\n");
                break;
            }
            fflush(stdout);
        }
    }
    if (!flag_print)
    {
        printf("0");
    }
    printf("\n");
}

void imprimirLista(bignumNodo_t * lista){
    
    if ( lista == NULL ) {
        return;
    }
    if ( !(lista->sig) ) {
        printf("%hu",lista->val);
        return;
    }
    printf("%hu",lista->val);
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

void sumaLista( operationList_vector_t *oper, size_t *size)
{
    size_t i;
    ushort aux=0;

    if(oper->operacionesList[*size]->op1->sign==NEGATIVE && oper->operacionesList[*size]->op2->sign==POSITIVE)
    {
        
        if( oper->operacionesList[*size]->op1->q_digits > oper->operacionesList[*size]->op2->q_digits )
        {
            oper->operacionesList[*size]->rst=resta_digito_a_digito_List(oper->operacionesList[*size]->op1->digits,
                                                                oper->operacionesList[*size]->op2->digits,
                                                                oper->operacionesList[*size]->op1->q_digits,
                                                                oper->operacionesList[*size]->op2->q_digits,
                                                                &(oper->operacionesList[*size]->q_rst));
            oper->operacionesList[*size]->sign_rst=NEGATIVE;
            return;
        }
        else if(oper->operacionesList[*size]->op1->q_digits == oper->operacionesList[*size]->op2->q_digits)
        {
            for (i=0; i<oper->operacionesList[*size]->op1->q_digits; i++)
            {
                if ( valor_en_lista(oper->operacionesList[*size]->op1->digits,i)<valor_en_lista(oper->operacionesList[*size]->op2->digits,i) )
                {
                    oper->operacionesList[*size]->rst=resta_digito_a_digito_List(oper->operacionesList[*size]->op2->digits,
                                                                        oper->operacionesList[*size]->op1->digits,
                                                                        oper->operacionesList[*size]->op2->q_digits,
                                                                        oper->operacionesList[*size]->op1->q_digits,
                                                                        &(oper->operacionesList[*size]->q_rst));
                    oper->operacionesList[*size]->sign_rst=POSITIVE;
                    return;
                }
                if (valor_en_lista(oper->operacionesList[*size]->op1->digits,i)>valor_en_lista(oper->operacionesList[*size]->op2->digits,i) )
                {
                    oper->operacionesList[*size]->rst=resta_digito_a_digito_List(oper->operacionesList[*size]->op1->digits,
                                                                        oper->operacionesList[*size]->op2->digits,
                                                                        oper->operacionesList[*size]->op1->q_digits,
                                                                        oper->operacionesList[*size]->op2->q_digits,
                                                                        &(oper->operacionesList[*size]->q_rst));
                    for (i=0; i<oper->operacionesList[*size]->q_rst; i++)
                    {
                        aux+=oper->operacionesList[*size]->rst[i];
                    }
                    if (!aux) oper->operacionesList[*size]->sign_rst=POSITIVE;
                    else oper->operacionesList[*size]->sign_rst=NEGATIVE;
                    return;

                }
            }
        }
        
            
    }
    
    
    if ( oper->operacionesList[*size]->op1->q_digits < oper->operacionesList[*size]->op2->q_digits )
    {
        if(oper->operacionesList[*size]->op1->sign==NEGATIVE && oper->operacionesList[*size]->op2->sign==POSITIVE)
        {
            oper->operacionesList[*size]->rst=resta_digito_a_digito_List(oper->operacionesList[*size]->op2->digits,
                                                                oper->operacionesList[*size]->op1->digits,
                                                                oper->operacionesList[*size]->op2->q_digits,
                                                                oper->operacionesList[*size]->op1->q_digits,
                                                                &(oper->operacionesList[*size]->q_rst));
            oper->operacionesList[*size]->sign_rst=POSITIVE;
        }
        else
        {
            oper->operacionesList[*size]->rst=suma_digito_a_digito_List(
                                                               oper->operacionesList[*size]->op2->digits,
                                                               oper->operacionesList[*size]->op1->digits,
                                                               oper->operacionesList[*size]->op2->q_digits,
                                                               oper->operacionesList[*size]->op1->q_digits,
                                                               &(oper->operacionesList[*size]->q_rst) );
            if (oper->operacionesList[*size]->op1->sign == NEGATIVE && oper->operacionesList[*size]->op2->sign == NEGATIVE)
            {
                oper->operacionesList[*size]->sign_rst=NEGATIVE;
            }
            else oper->operacionesList[*size]->sign_rst=POSITIVE;
        }
    }
    else
    {
        oper->operacionesList[*size]->rst=suma_digito_a_digito_List(
                                                           oper->operacionesList[*size]->op1->digits,
                                                           oper->operacionesList[*size]->op2->digits,
                                                           oper->operacionesList[*size]->op1->q_digits,
                                                           oper->operacionesList[*size]->op2->q_digits,
                                                           &(oper->operacionesList[*size]->q_rst) );
        
        
        if (oper->operacionesList[*size]->op1->sign == NEGATIVE && oper->operacionesList[*size]->op2->sign == NEGATIVE)
        {
            oper->operacionesList[*size]->sign_rst=NEGATIVE;
        }
        else oper->operacionesList[*size]->sign_rst=POSITIVE;
    }
    
    
    
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

void restaLista ( operationList_vector_t *oper, size_t *pos)
{
    size_t i;
    
    
    if (oper->operacionesList[*pos]->op1->sign == NEGATIVE && oper->operacionesList[*pos]->op2->sign == NEGATIVE)
    {
        if ( oper->operacionesList[*pos]->op1->q_digits < oper->operacionesList[*pos]->op2->q_digits )
        {
            oper->operacionesList[*pos]->rst=suma_digito_a_digito_List(oper->operacionesList[*pos]->op2->digits, oper->operacionesList[*pos]->op1->digits, oper->operacionesList[*pos]->op2->q_digits, oper->operacionesList[*pos]->op1->q_digits, &(oper->operacionesList[*pos]->q_rst) );
        }
        else
        {
            oper->operacionesList[*pos]->rst=suma_digito_a_digito_List(oper->operacionesList[*pos]->op1->digits, oper->operacionesList[*pos]->op2->digits, oper->operacionesList[*pos]->op1->q_digits, oper->operacionesList[*pos]->op2->q_digits, &(oper->operacionesList[*pos]->q_rst) );
        }
        oper->operacionesList[*pos]->sign_rst=NEGATIVE;
        return;
    }
    
    if ( (oper->operacionesList[*pos]->op1->q_digits) > (oper->operacionesList[*pos]->op2->q_digits) )
    {
        oper->operacionesList[*pos]->rst = resta_digito_a_digito_List(oper->operacionesList[*pos]->op1->digits,oper->operacionesList[*pos]->op2->digits,oper->operacionesList[*pos]->op1->q_digits,oper->operacionesList[*pos]->op2->q_digits,&(oper->operacionesList[*pos]->q_rst));
        oper->operacionesList[*pos]->sign_rst=POSITIVE;
    }
    else if((oper->operacionesList[*pos]->op1->q_digits)<(oper->operacionesList[*pos]->op2->q_digits))
    {
        oper->operacionesList[*pos]->rst=resta_digito_a_digito_List(oper->operacionesList[*pos]->op2->digits,oper->operacionesList[*pos]->op1->digits,oper->operacionesList[*pos]->op2->q_digits,oper->operacionesList[*pos]->op1->q_digits,&(oper->operacionesList[*pos]->q_rst));
        oper->operacionesList[*pos]->sign_rst=NEGATIVE;
    }
    
    else
    {
        for (i=0; i<oper->operacionesList[*pos]->op1->q_digits; i++)
        {
            if ( valor_en_lista(oper->operacionesList[*pos]->op1->digits,i)<valor_en_lista(oper->operacionesList[*pos]->op2->digits,i) )
            {
                oper->operacionesList[*pos]->rst=resta_digito_a_digito_List(oper->operacionesList[*pos]->op2->digits,oper->operacionesList[*pos]->op1->digits,oper->operacionesList[*pos]->op2->q_digits,oper->operacionesList[*pos]->op1->q_digits,&(oper->operacionesList[*pos]->q_rst));

                oper->operacionesList[*pos]->sign_rst=NEGATIVE;
                return;
            }
            if ( valor_en_lista(oper->operacionesList[*pos]->op1->digits,i)>valor_en_lista(oper->operacionesList[*pos]->op2->digits,i))
            {
                oper->operacionesList[*pos]->rst=resta_digito_a_digito_List(oper->operacionesList[*pos]->op1->digits,oper->operacionesList[*pos]->op2->digits,oper->operacionesList[*pos]->op1->q_digits,oper->operacionesList[*pos]->op2->q_digits,&(oper->operacionesList[*pos]->q_rst));
                
                oper->operacionesList[*pos]->sign_rst=POSITIVE;
                return;
                
            }
        }

    }
    
    
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
    bignumNodo_t *aux=NULL;
    if(*lista)
    {
        aux=(*lista)->sig;
        free(*lista);
        (*lista)=NULL;
        freeLista(&aux);
    }
}

void multiplicarLista(operationList_vector_t *oper, size_t *size)
{
    oper->operacionesList[*size]->rst = multiplico_List(oper->operacionesList[*size]->op1->digits,
                                               oper->operacionesList[*size]->op2->digits,
                                               oper->operacionesList[*size]->op1->q_digits,
                                               oper->operacionesList[*size]->op2->q_digits,
                                               &(oper->operacionesList[*size]->q_rst));
   
    if (oper->operacionesList[*size]->op1->sign==NEGATIVE && oper->operacionesList[*size]->op2->sign==NEGATIVE)
    {
        oper->operacionesList[*size]->sign_rst=POSITIVE;
    }
    else if(oper->operacionesList[*size]->op1->sign==NEGATIVE && oper->operacionesList[*size]->op2->sign==POSITIVE)
    {
        oper->operacionesList[*size]->sign_rst=NEGATIVE;
    }
    else if(oper->operacionesList[*size]->op1->sign==POSITIVE && oper->operacionesList[*size]->op2->sign==NEGATIVE)
    {
        oper->operacionesList[*size]->sign_rst=NEGATIVE;
    }
    else    oper->operacionesList[*size]->sign_rst=POSITIVE;
    
  
  
}
ushort * multiplico_List (bignumNodo_t *dig1,bignumNodo_t *dig2, size_t cant1, size_t cant2,size_t * q_resultado)
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
   /* inserto_valor_en_lista(&(res_matriz[0]),8,0);
    inserto_valor_en_lista(&(res_matriz[0]),8,1);
    imprimirLista(res_matriz[0]);
    freeLista(&(res_matriz[0]));
    //freeLista(&(res_matriz[0]));
    imprimirLista(res_matriz[0]);   
    */k=0;
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
	
    
	//imprimirLista(res_matriz[0]);
    for(k=cant2-1;k>=0;k--)   /*Este es el procedimiento para que vaya sumando desde la ultima fila de la matriz, hacia arriba.*/
    {	
	//printf("FAFAFFAFAFAFAFAF\n");        
	res=suma_digito_a_digito_List(resAux,res_matriz[k],cant1+cant2+cont,cant1+1+k,q_resultado);
        ++cont;
	
	/*Paso res a una lista*/
	for(i=0;i<cant1+cant2+cont;i++)
	{
	   
	    inserto_valor_en_lista(&(resAux),res[i],i);
	}
 	
        free(res);
         
    }
    *q_resultado=cant1+cant2+cont;
    
    for(k=0;k<cant2;k++)
    {
	freeLista(&(res_matriz[k]));
    }
    free(res_matriz);
    /*Paso resAux a un vector de ushort*/
    res=(ushort*)malloc(sizeof(ushort)*(cant1+cant2+cont));
    for(i=0;i<cant1+cant2+cont;i++)
    {
	res[i]=valor_en_lista(resAux,i);
    }
    freeLista(&resAux);
    return res;	/* Esta no devuelve un vector, devuelve una lista. Para imprimirla afuera hay q llamar a imprimirLista */
}

/*


operation_status_t GrabarOperaciones(operationList_vector_t * operaciones){
    
    FILE * fpOperaciones;
    bignumNodo_t *aux;
    size_t i=0;
    char NombreArchivo[MAX_CHAR];
    strcpy(NombreArchivo, "partidosjugados.dat");
    
    
    fpOperaciones = fopen(NombreArchivo, "wb");
    
    if (!fpOperaciones) {
        fprintf(stderr, "Error, no se pudo abrir %s\n", NombreArchivo);
        return ERROR;
    }
    
    //debemos guardar los siguientes datos:
    // por cada elemnto del vector de operaciones guardaremos (operationList_t):
    
    // bignumList_t *op1;
    // bignumList_t *op2;
    // opt_t op;
    // ushort *rst;
    // size_t q_rst;
    // sign_t sign_rst;
    // sign_t inf_rst;
    // result_state_t st;
    
    // bignumNodo_t *digits;
    // size_t q_digits;
    // sign_t sign ;
    // sign_t inf;

    for (i=0; i<operaciones->operList_size; i++)
    {
        
        fwrite(operaciones->operacionesList[i]->op, sizeof(opt_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->q_rst, sizeof(size_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->rst, sizeof(ushort), operaciones->operacionesList[i]->q_rst, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->sign_rst, sizeof(sign_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->inf_rst, sizeof(sign_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->st, sizeof(result_state_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->op1->inf, sizeof(sign_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->op1->sign, sizeof(sign_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->op1->q_digits, sizeof(size_t), 1, fpOperaciones);
        aux=operaciones->operacionesList[i]->op1->digits;
        while (aux)
        {
            fwrite(aux->val, sizeof(ushort), 1, fpOperaciones);
            aux=aux->sig;
        }
        fwrite(operaciones->operacionesList[i]->op2->inf, sizeof(sign_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->op2->sign, sizeof(sign_t), 1, fpOperaciones);
        fwrite(operaciones->operacionesList[i]->op2->q_digits, sizeof(size_t), 1, fpOperaciones);
        aux=operaciones->operacionesList[i]->op2->digits;
        while (aux)
        {
            fwrite(aux->val, sizeof(ushort), 1, fpOperaciones);
            aux=aux->sig;
        }
    }
    fflush(fpOperaciones);
    fclose(fpOperaciones);
    
    return OK;
    
}


operation_status_t leerPartidosJugados(operationList_vector_t * operaciones){
    
    FILE * fpOperaciones;
    char NombreArchivo[MAX_CHAR];
    strcpy(NombreArchivo, "partidosjugados.dat");
    
    
    
    
    
    fpOperaciones= fopen(NombreArchivo, "rb");
    
    if (!fpOperaciones) {
        fprintf(stderr, "Error, no se pudo abrir %s\n", NombreArchivo);
        fprintf(stderr, "Si es la primera vez que corre el programa ejecute devuelta por favor\n");
        return TRUE;
    }
    
    while (fread(buffer, sizeof(int), 1, fpPartidosJugados)) {
        /*printf("%d ", buffer[0]);
        fread(buffer + 1, sizeof(int), 1, fpPartidosJugados);
        /*printf("%d ", buffer[1]);
        fread(buffer + 2, sizeof(int), 1, fpPartidosJugados);
        /*printf("%d \n", buffer[2]);
        
        if (BuscarPartidoPorId(*listaPartidos, buffer[ID]) == NULL) {
            fprintf(stderr, "Error, archivo binario malformado.\n");
            return TRUE;
        }
        
    }
    return FALSE;
    
}

*/

