#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "bignum.h"
#include "simplecalc.h"
#include "bignumList.h"


/* Defines para supercalc */
#define MAX_STR 10
#define VALID_ARGUMENTS 2 /* argumentos de entrada por parametro 1-> nombre del programa 2-> modo del programa (simplecalc o supercalc)*/
#define DEFAULT_PRECISION 1000
#define INPUT_MODE_SIMPLECALC "simpleCalc"
#define INPUT_MODE_SUPERCALC "superCalc"

/* typedef de supercalc */
typedef enum{ SIMPLECALC, SUPERCALC} calcMode_t;



/*##### PROTOTIPOS #####*/

void paso_linea_a_struct( char *, operation_t **, int );
char * GetLines( void );
operation_status_t parseLines( char ** ,char ** , char **, opt_t * );
char * searchEnter(char * );
char * prependChar(const char * , char );
operation_status_t ValidateArguments(int ,char **,size_t *,calcMode_t * ,char **,char **);
void testLista(operationList_vector_t * oper_vect);


/*######################################################################################*/



int main(int argc,char *argv[])
{
    calcMode_t calcmode=SIMPLECALC; /* por default hacemos que sea simpleCalc */
    /* simpleCalc */
    int opt;
    char * output=NULL;
    
    /* superCalc */
    operationList_vector_t operaciones_vect;
    char *num1=NULL;
    char *num2=NULL;
    char *input=NULL;
    operation_status_t statusLine=OK;
    size_t precision=DEFAULT_PRECISION;
    operation_status_t status_cargado=ERROR;
    size_t i=0;

    
    if (argc<VALID_ARGUMENTS)
    {
        fprintf(stderr, "Modo invalido de invocacion\n");
        fprintf(stderr, "Se debe de invocar como $%s <mode> -p <precision>\n",argv[0]);
        fprintf(stderr, "<mode> : modo de la calculadora %s o %s\n",INPUT_MODE_SIMPLECALC,INPUT_MODE_SUPERCALC);
        fprintf(stderr, "<precision> : precision del calculo antes de truncar ( Default: %d )\n",DEFAULT_PRECISION);
        return EXIT_FAILURE;
    }
    
    ValidateArguments(argc,argv,&precision,&calcmode,&output,&input);
    
    if ( calcmode==SUPERCALC )
    {
        
         /*testLista(&operaciones_vect);*/
        
        inicializarStructOperationList(&operaciones_vect);
        
        status_cargado=leerOperaciones(&operaciones_vect);
        if (status_cargado!=ERROR)
        {
            
            while (statusLine!=_EOF)
            {
                
                input=GetLines();
                if(operaciones_vect.operList_size!=0) AddOperationList(&operaciones_vect);
                
                statusLine=parseLines(&input, &num1, &num2, &(operaciones_vect.operacionesList[operaciones_vect.operList_size]->op) );
                
                status_cargado=cargarStructNumerosList(operaciones_vect.operacionesList,
                                                    &(operaciones_vect.operList_size),
                                                    &(operaciones_vect.operList_size),
                                                    num1,
                                                    num2,
                                                    &(operaciones_vect.operacionesList[operaciones_vect.operList_size]->op),
                                                    precision,
                                                    statusLine
                                                       );
                
                    switch (operaciones_vect.operacionesList[operaciones_vect.operList_size]->op)
                    {
                        case SUMA:
                                    sumaLista(&operaciones_vect, &(operaciones_vect.operList_size) );
                                    printArrayShort(operaciones_vect.operacionesList[operaciones_vect.operList_size]->rst, operaciones_vect.operacionesList[operaciones_vect.operList_size]->q_rst,operaciones_vect.operacionesList[operaciones_vect.operList_size]->sign_rst,precision);
                                    break;
                        case RESTA:
                                    restaLista(&operaciones_vect, &(operaciones_vect.operList_size) );
                                    printArrayShort(operaciones_vect.operacionesList[operaciones_vect.operList_size]->rst, operaciones_vect.operacionesList[operaciones_vect.operList_size]->q_rst,operaciones_vect.operacionesList[operaciones_vect.operList_size]->sign_rst,precision);
                                    break;
                        case MULT:
                                    multiplicarLista(&operaciones_vect, &(operaciones_vect.operList_size));
                                    printArrayShort(operaciones_vect.operacionesList[operaciones_vect.operList_size]->rst, operaciones_vect.operacionesList[operaciones_vect.operList_size]->q_rst,operaciones_vect.operacionesList[operaciones_vect.operList_size]->sign_rst,precision);
                                    break;
                        case NOOPERATION:
                                    sumaLista(&operaciones_vect, &(operaciones_vect.operList_size) );
                                    break;
                        default:
                            fprintf(stderr, "no se pudo efectuar ninguna operacion\n");
                            break;
                    }
                    
                    operaciones_vect.operList_size++;
                    free(input);
                    free(num1);
                    free(num2);
                    input=NULL;
                    num1=NULL;
                    num2=NULL;
                }
            if(status_cargado==INF)
            {
                printf("Inf\n");
            }
            GrabarOperaciones(&operaciones_vect);
        
            /*liberamos memoria*/
           
            free(input);
            free(num1);
            free(num2);
            input=NULL;
            num1=NULL;
            num2=NULL;

        }
    
        
        for (i=0; i<operaciones_vect.operList_size; i++)
        {
            freeLista( &(operaciones_vect.operacionesList[i]->op1->digits));
            operaciones_vect.operacionesList[i]->op1->digits=NULL;
            freeLista( &(operaciones_vect.operacionesList[i]->op2->digits));
            operaciones_vect.operacionesList[i]->op2->digits=NULL;
            free( operaciones_vect.operacionesList[i]->op1);
            operaciones_vect.operacionesList[i]->op1=NULL;
            free( operaciones_vect.operacionesList[i]->op2);
            operaciones_vect.operacionesList[i]->op2=NULL;
            free( operaciones_vect.operacionesList[i]->rst);
            operaciones_vect.operacionesList[i]->rst=NULL;
        }
        
        for (i=0; i<operaciones_vect.operList_size; i++)
        {
            free(operaciones_vect.operacionesList[i]);
            operaciones_vect.operacionesList[i]=NULL;
        }
        free(operaciones_vect.operacionesList);
        operaciones_vect.operacionesList=NULL;
    
        
    }
    else if( calcmode==SIMPLECALC )
    {
        
        /* modo calculadora simple */
        printf(MENU);
        scanf("%d",&opt);
        opcion(opt,output);
        return 0;

    }
    
    return 0;
}







/*###############################*/
/*####### funciones #############*/
void testLista(operationList_vector_t * oper_vect)
{
    size_t precision=DEFAULT_PRECISION;
    /* Los numeros van con su signo para ser tomados y cargados correctamente en cargarStructNumeros */
    char num1[]="+111";  
    char num2[]="+111";
		
    opt_t operation=SUMA;
    operation_status_t status=OK;
    
    inicializarStructOperationList(oper_vect);
    leerOperaciones(oper_vect);
    
    cargarStructNumerosList(&(oper_vect->operacionesList[oper_vect->operList_size]),
                            &(oper_vect->operList_size),
                            &(oper_vect->operList_size),
                            num1,
                            num2,
                            &operation,
                            precision,
                            status);
    
    printf("primera lista:\n");
    imprimirLista(oper_vect->operacionesList[oper_vect->operList_size]->op1->digits);
    putchar('\n');
    printf("segunda lista:\n");
    imprimirLista(oper_vect->operacionesList[oper_vect->operList_size]->op2->digits);
    putchar('\n');
    oper_vect->operacionesList[oper_vect->operList_size]->rst=
			multiplico_List (oper_vect->operacionesList[oper_vect->operList_size]->op1->digits,
			oper_vect->operacionesList[oper_vect->operList_size]->op2->digits,
			oper_vect->operacionesList[oper_vect->operList_size]->op1->q_digits,
			oper_vect->operacionesList[oper_vect->operList_size]->op2->q_digits,
			&(oper_vect->operacionesList[oper_vect->operList_size]->q_rst));
    printf("Res:\n");
    printArrayShort(oper_vect->operacionesList[oper_vect->operList_size]->rst,oper_vect->operacionesList[oper_vect->operList_size]->q_rst,POSITIVE,DEFAULT_PRECISION);
    
    GrabarOperaciones(oper_vect);
    

}


operation_status_t ValidateArguments(int argc,char **argv,size_t *precision,calcMode_t *mode, char ** output,char **input)
{
    
    size_t i=0;
    
    
    for (i=1; i<argc; i++)
    {
        if ( !(strcmp(argv[i],INPUT_MODE_SIMPLECALC)) )
        {
            *mode=SIMPLECALC;
            break;
        }
        else if( !(strcmp(argv[i],INPUT_MODE_SUPERCALC)) )
        {
            *mode=SUPERCALC;
            break;
        }

    }
    for (i=1; i<argc; i++)
    {
        if (!(strcmp(argv[i],"-p")))
        {
            *precision=atoi(argv[i+1]);
            if (!*precision) *precision=DEFAULT_PRECISION;
        }
        if (!(strcmp(argv[i],"-output")))
        {
            *output=argv[i+1];
        }
        if (!(strcmp(argv[i],"-input")))
        {
            *input=argv[i+1];
        }

        
    }
    
    return OK;
    
}





char * GetLines( void )
{
    

    char lines[MAX_STR];
    char *totalLines=NULL;
    char *aux=NULL;
    /* como pedimos memoria esta hardcodeado de a init chop chars por llamada */
    size_t used_size = 0;
    size_t alloc_size = 0, init_chop = MAX_STR, chop_size = MAX_STR*2;
    size_t counterMemoryCallouts=0;

    
    /* pedimos memoria por primera vez antes de reallocar si es que necesitamos memoria.
     */
    if (!(totalLines = (char*)calloc(init_chop,sizeof(char))))
    {
        fprintf(stderr, "Error, could not find memory\n");
        return NULL;
    }
    
    
    alloc_size = init_chop;
    
    
    while ( !(searchEnter( lines )) )
    {
        fgets(lines, MAX_STR, stdin);
        
        
        /* nos preguntamos si necesitamos memoria ... pedimos de a chops o de a pedazos
         */
        if (used_size == alloc_size)
        {
            
            if (!(aux = (char*)realloc(totalLines, sizeof(char)*(alloc_size + chop_size))))
            {
                fprintf(stderr, "Error, could not find memory\n");
                free(totalLines);
                totalLines = NULL;
                return NULL;
            }
            totalLines = aux;
            alloc_size += chop_size; /* incremento en suma o escalonada */
            counterMemoryCallouts++;
            /* debugging alloc size callouts
            printf("counter:%lu alloc:%lu chop_size:%lu\n",counterMemoryCallouts,alloc_size,chop_size);*/
             
        }
        /* concatenamos line con totallines para obtener el string final */
        strcat(totalLines, lines);
        /* incrementamos en MAX_STR el used size asi si nos falta obtener del stdin pedimos memoria */
        used_size=used_size+MAX_STR;
        /* debug totallines printf("%s\n",totalLines); */
    }
    /* quitamos el \n y hacemos null terminated string */
    totalLines[strlen(totalLines)-1]='\0';
    
    return totalLines;
    
}

operation_status_t parseLines( char **totalLines,char **line1, char **line2,opt_t *operation)
{
    
    char *ptr;
    char *ptr2;
    size_t i; /*contador para parsear con strtok*/
    
    
    if ( strcmp(*totalLines,"#calculate") )
    {
        /* Aca calculo como separar las cadenas de caracteres en line1 y line2 */
        
            if (*totalLines[0]=='*')
            {
                return ERROR;
            }
            else if ( *totalLines[0]=='+')
            {
                
                /* que pasa si no hay un - o un + en el medio? */
                for (i=1; i<strlen(*totalLines); i++)
                {
                    if ( !(isdigit((*totalLines)[i])) )
                    {
                        
                        if ((*totalLines)[i]=='-')
                        {
                            ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                            *line1=prependChar(ptr,'#');
                            *line2=prependChar(ptr2, '-');
                            *operation=RESTA;
                            return OK;
                        }
                        
                        if ((*totalLines)[i]=='+')
                        {
                            ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                            /**(searchEnter(ptr2))='\0';*/
                            *line1=prependChar(ptr,'#');
                            *line2=prependChar(ptr2,'+');
                            *operation=SUMA;
                            return OK;
                        }
                    }
                }
                ptr=NULL; /* si llegamos hasta aca es porque no se ingreso una operacion */
            }
            else if (*totalLines[0]=='-' ) {
                
                /* que pasa si no hay un - o un + en el medio? */
                for (i=1; i<strlen(*totalLines); i++)
                {
                    if ( !(isdigit((*totalLines)[i])) )
                    {
                        
                        if ((*totalLines)[i]=='-')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                            ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                            ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                            *line1=prependChar(ptr, '-');
                            *line2=prependChar(ptr2, '+');
                            *operation=SUMA;
                            return OK;
                            }
                            else
                            {
                                ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr, '-');
                                *line2=prependChar(ptr2, '-');
                                *operation=RESTA;
                                return OK;
                            }
                                
                        }
                        
                        if ((*totalLines)[i]=='+')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                /**line1=prependChar(ptr, '-');
                                *line2=prependChar(ptr2, '-');*/
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2,'#');
                                *operation=SUMA;
                                return OK;
                            }
                            else
                            {
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;
                            }
                        }
                        if ((*totalLines)[i]=='*')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"*"); /* este es nuestro primer numero */
                                /*line1=prependChar(ptr, '-');
                                *line2=prependChar(ptr2, '-');*/
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2,'#');
                                *operation=MULT;
                                return OK;
                            }
                            else
                            {
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"*"); /* este es nuestro primer numero */
                                /**line1=prependChar(ptr, '-');*/
                                *line1=prependChar(ptr,'#');
                                *line2=prependChar(ptr2, '+');
                                *operation=MULT;
                                return OK;
                            }
                        }
                    }
                }
                ptr=NULL; /* Si llegamos hasta aca es porque no se ingreso una operacion */
            }
            else
            {
                for (i=1; i<strlen(*totalLines); i++)
                {
                    if ( !(isdigit((*totalLines)[i])) )
                    {
                        if ((*totalLines)[i]=='-')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001--222 */
                                ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;
                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001-222 */
                                ptr=strtok(*totalLines,"-"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=RESTA;
                                return OK;

                            }
                        }
                        
                        if ((*totalLines)[i]=='+')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001+-222 */
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                *operation=RESTA;
                                return OK;
                            }
                            else if((*totalLines)[i+1]=='+')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001++222 */
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;

                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001+222 */
                                ptr=strtok(*totalLines,"+"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=SUMA;
                                return OK;
                            }
                        }
                        
                        if ((*totalLines)[i]=='*')
                        {
                            if ((*totalLines)[i+1]=='-')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001*-222 */
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"-"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'-');
                                *operation=MULT;
                                return OK;
                            }
                            else if((*totalLines)[i+1]=='+')
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 001*+222 */
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"+"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=MULT;
                                return OK;
                                
                            }
                            else
                            {
                                /* si llegamos hasta aca quiere decir que se ingreso algo como 10*3 */
                                ptr=strtok(*totalLines,"*"); /* con esto nos saltemaos el primer caracter */
                                ptr2=strtok(NULL,"*"); /* este es nuestro primer numero */
                                *line1=prependChar(ptr,'+');
                                *line2=prependChar(ptr2,'+');
                                *operation=MULT;
                                return OK;
                            }
                        }
                    }
                }
                ptr=NULL; /* Si llegamos hasta aca es porque no se ingreso una operacion */
            }

        if (!ptr) return _EOF;
    }
    else
    {
        *line1=prependChar("00",'+');
        *line2=prependChar("00",'+');
        *operation=NOOPERATION;
        return _EOF;
    }
    
    return OK;
}


char * searchEnter(char *str ){
    size_t i;
    for (i=0; i<strlen(str)+1; i++) {
        if (str[i]=='\n') {
            return str+i;
        }
    }
    return NULL;
}

char * prependChar(const char * str, char c)
{
    char * string = (char *)calloc( strlen(str)+2,sizeof(char) ); /* añadimos 2 posiciones una para el caracter y otra para el \0 */
    if(c!='#')
    {
        string[0] = c;
        strcpy(string + 1, str);
    }
    else
    {
        strcpy(string, str);
    }
    return string;
}








