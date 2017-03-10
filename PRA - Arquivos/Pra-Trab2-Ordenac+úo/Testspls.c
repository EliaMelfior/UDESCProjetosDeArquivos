#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RelatoriosClimaticos.bin"
#define STACKFILENAME1 "Stack1.txt"
#define STACKFILENAME2 "Stack2.txt"
#define STACKFILENAME3 "Stack3.txt"
#define STACKFILENAME4 "Stack4.txt"
#define STACKFILENAME5 "Stack5.txt"
#define STACKFILENAME6 "Stack6.txt"
#define STACKFILENAME7 "Stack7.txt"
#define STACKFILENAME8 "Stack8.txt"


#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "stack.c" /*implementação de pilha/stack*/


typedef struct RelatorioClimatico
{ 
        char nomeLocal [50]; 
        struct tm dataColeta;
        int temperatura; 
    
}RelatorioClimatico; 

typedef struct indexArray
{
	int path;
	int dados;
}indexArray;

long int determineNumberOfRegistries(long int fileSizeVariable2)
{
	long int fileSizeInBytes;
	long int numberOfRegistries;
	
	fileSizeInBytes=(fileSizeVariable2*1024)*1024; //De megabytes para bytes
	
	numberOfRegistries=fileSizeInBytes/sizeof(RelatorioClimatico); //Da quantidade de bytes para a quantidade de registros
	
	return(numberOfRegistries);
}

FILE *fp1, *fp2;

/* Função que compara pela temperatura, necessária para o quicksort
 *
 */
 
int cmpByTemperature (const void *p, const void *q)
{
   int temp1 = ((indexArray*)p)->dados;
   int temp2 = ((indexArray*)q)->dados;
   return temp2 - temp1;
}

/* Função que lê o arquivo, ordena e empilha valores
 * primeiro argumento é o ponteiro para o arquivo em modo de leitura
 * segundo argumento é o tamanho da pilha em Megabytes
 * terceiro argumento é a pilha
 * offset é o distanciamento ao ler o arquivo para percorrê-lo corretamente
 * RETORNA O número de elementos da pilha
 */
 
int returnOrderedStack(FILE *fppp, int SizeOfStack, stackT *stackP, long int offset)
{
	long int numberOfRegistries = determineNumberOfRegistries(SizeOfStack);
	int x,relatorioSize;
	int address;
	RelatorioClimatico *buffer = (RelatorioClimatico*)malloc((numberOfRegistries) * sizeof (RelatorioClimatico));
	indexArray *index = (indexArray*)malloc((numberOfRegistries) * sizeof (indexArray));
	offset = numberOfRegistries*offset;
	
	fseek(fppp , offset * sizeof(RelatorioClimatico) , SEEK_SET);
	fread(buffer, sizeof(RelatorioClimatico), numberOfRegistries, fppp);
	offset = offset/numberOfRegistries;
	
	StackInit(stackP, numberOfRegistries);
	relatorioSize = sizeof(RelatorioClimatico);
	for(x=0;x<numberOfRegistries;x++)
	{
		index[x].dados=buffer[x].temperatura;
		index[x].path=relatorioSize*x;
	}
	
	qsort(index, numberOfRegistries, sizeof(indexArray), cmpByTemperature);
	
	for(x=0;x<numberOfRegistries;x++)
	{
		StackPush(stackP,index[x].dados, index[x].path);
	}
	free(buffer);
	return(numberOfRegistries);
}

void generateIndexWithOrderedStack(FILE *fppp, stackT *stackP, int numberOfElements, char *SSTACKFILENAME)
{
	 /* Abertura do ponteiro de escrita das pilhas ordenadas em modo texto
	 *
	 */
	char *name = SSTACKFILENAME;
	
	fppp = fopen(name , "w+");
	    if(fppp == NULL)
		{
			fppp = fopen(name , "w+");
	        if(fppp == NULL)
	        {
	        	printf("%s \n", name);
	            printf("error in opening file : \n");
	        }
	    }
	    
	fseek(fppp , 0 , SEEK_SET);
	while (!StackIsEmpty(stackP))
	{
		stackElementT x = StackPop(stackP);
	    fprintf(fppp, "%i %i \n", x.temperatura, x.bytesMoved);
	}
}

static int out_of_range ( int val, int lower, int upper )
{
  return val < lower || upper < val;
}

void clearScreen()
{
	printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ");
}

static int menu (void)
{
  int option = 0;
   
  while ( out_of_range ( option, 1, 3 ) ) {
    printf ( "\n\t Sistema de Relatorios Climaticos - Digite a opcao desejada - \n" );
    printf ( "[1] Gerar arquivos de índice \n" );
    printf ( "[2] Limpar tela \n" );
    printf ( "[3] Sair\n\n" ); 
    fflush(stdin);	
    scanf ( "%d", &option );
     
    if ( out_of_range ( option, 1, 3) )
    {
      printf("Entrada invalida, por favor tente novamente.\n");
      fflush(stdin);
  	}
  }
   
  return option;
}

void fileSize(FILE *fp5)
{
	fseek(fp5, 0, SEEK_END);
	printf("O tamanho do arquivo eh de %li em bytes, %li em Mbytes, e contem %li registros \n \n ",ftell(fp5), ((ftell(fp5))/1024)/1024,  ftell(fp5)/sizeof(RelatorioClimatico) );
	printf("Tamanho de cada registro: %li", sizeof(RelatorioClimatico));
}

int main(void)
{	
	/* Abertura do ponteiro de leitura sobre o arquivo principal com muitas informações
	 *
	 */
	int intMenu=0;
	int x, numberOfStackElements;
	fp1 = fopen(FILENAME , "rb+");
	    if(fp1 == NULL)
	    {
	        fp1 = fopen(FILENAME , "wb+");
	        if(fp1 == NULL)
	        {
	            printf("error in opening file : \n");
	            return -1;
	        }
	    }
	    
	stackT stack1;
	
	
	
	
		while((intMenu = menu())!=3)
		{
			if(intMenu == 1)
			{
				numberOfStackElements = returnOrderedStack(fp1, 100, &stack1, 0);
				generateIndexWithOrderedStack(fp2, &stack1, numberOfStackElements, STACKFILENAME1);
				StackDestroy(&stack1);	
			}
			
			if(intMenu == 2)
			{
				clearScreen();
				fileSize(fp1);
			}
			
			if(intMenu == 3)
			{
				printf ( "\n \n [5] Sair \n \n " );
			}
		}
	/*
	printf("\nPopped characters are: \n ");
	while (!StackIsEmpty(&stack1))
	{
		x = x+1;
	    printf("%i \n", StackPop(&stack1));
	}
	printf("%i",x);
	*/
	    
}
