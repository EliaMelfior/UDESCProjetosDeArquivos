#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RelatoriosClimaticos.bin"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

/**
Eficácia 50
Organização/Legibilidade do código 10
Códigos-fontes foram entregues 20
Documentação 10
Lê/grava blocos de registros 50
Permite inserção 50
Permite consulta 50
Permite remoção 50
Base de dados 1Gb 10
Apresenta relatório de desempenho: tempo, no acessos a disco 20
Bônus: análise de performance com múltiplas bases de diferentes tamanhos (min = 4) 50
Punição por plágio -320
Punição por dia de atraso -100
Pontuação máxima 320

Nota Final

(*) não compareceu a apresentação = -15%
*/

/**
INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / 
INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / 
INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / INICIO DA LISTA (TESTE) / 
*/

typedef struct RelatorioClimatico
{ 
        char nomeLocal [50]; 
        struct tm dataColeta;
        int temperatura; 
    
}RelatorioClimatico; 

typedef struct info{
		struct RelatorioClimatico *relatorio;
		struct info *prev;
		struct info *next;
	}info;
	
	typedef struct{
		int tamanho;
		struct info *begin;
		struct info *end;
	} list;
	


int addInBegin (list *list, struct RelatorioClimatico *d){
	info *new = (info *) malloc(sizeof(info));
	if (new != NULL){
		new->relatorio = d;
		new->next = list->begin;
		new->prev = NULL;
		if (new->next != NULL){
			new->next->prev = new;
		}
		list->begin = new;
		list->tamanho++;
		return list->tamanho;
	}
	return 0;
}

int addInEnd (list *list, struct RelatorioClimatico *d){
	info *new = (info *) malloc(sizeof(info));
	if (new != NULL){
		new->relatorio = d;
		list->end = new;
		new->next = NULL;
		if (new->prev != NULL){
			new->prev->next = new;
		}
		list->end = new;
		list->tamanho++;
		return list->tamanho;
	}
	return 0;
}

/**
FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / 
FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / 
FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / 
*/

/** \ brief Dois ponteiros como variáveis globais, um para gravar e outro para ler arquivos */
FILE *fp1, *fp2;



/** \ struct
    Struct da previsão do tempo
    Dados necessarios:  nome do local, 
	                    data da coleta dos dados (dd/mm/aaaa),
					    hora da coleta dos dados(hh:mm:ss), 
						temperatura medida (C);
   Pelas variáveis usadas, cada registro possui 92 bytes de tamanho
   Uma base de 1GByte, utilizando as notacoes Giga,Mega e Kilo nas potências de 2, 
   1 GigaByte equivale a 1024 MegaBytes, que equivalem a 1024*1024 KiloBytes ou 1024*1024*1024 Bytes.
   
   Decidimos
   
   Através da ideia de blocagem, resolvemos gravar 512 KiloBytes de cada vez no disco, para criar a base de 1 GigaByte 
   512 KiloBytes são(512*1024) 524288 bytes, e a quantidade necessária de registros para gerar um "bloco" de 512 KiloBytes é de 5124288/92 
   ou: 55699 registros por bloco, arredondando por baixo para podermos ficar abaixo deste limite de 512 KiloBytes.
   
*/
/**
//partes de nomes para a função NameGen ## NAME GEN /NAME GEN /NAME GEN /NAME GEN /NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / ##############
//partes de nomes para a função NameGen ## NAME GEN /NAME GEN /NAME GEN /NAME GEN /NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / ##############
//partes de nomes para a função NameGen ## NAME GEN /NAME GEN /NAME GEN /NAME GEN /NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / NAME GEN / ##############
*/

char NamePrefix[][6] = {"join", "curi", "sao", "bom", "flori", "jara"};

char NameSuffix[][5] = {"wat", "rio", "lua", "sol", "marte"};


struct tm GeraData (){
	struct tm data;
	data.tm_mon = (rand() % 11 );
	data.tm_mday = 1 + (rand() % 30);
	data.tm_year = rand() % (2017 - 1980) + 1980;
	data.tm_sec = (rand() % 60 );
	data.tm_min = 1 + (rand() % 60);
	data.tm_hour = rand() % 23;
	return data;
}
/**
// GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / 
// GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / 
// GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / GERA NOME / 
*/

void NameGen(char* PlayerName)
{
	PlayerName[0]=0; //initialize the string to "" (zero length string).
	//add the prefix...
	strcat(PlayerName, NamePrefix[(int)(rand() % 5)]);
	//add the stem...
	fflush(stdin);
	strcat(PlayerName, NameSuffix[(int)(rand() % 4)]);
	//add the suffix...
	fflush(stdin);
	strcat(PlayerName, NamePrefix[(int)(rand() % 5)]);
	//Make the first letter capital...
	fflush(stdin);
	PlayerName[0]=toupper(PlayerName[0]);
	fflush(stdin);
	return;
}

void createBlock(FILE *fp5)
{
	RelatorioClimatico relatorio1;
	int size = sizeof(RelatorioClimatico);
	fseek(fp5, size, SEEK_END);
}

/** \ fn
    Ler o Arquivo 
*/

void readLastFile(FILE *fp5)
{
	RelatorioClimatico relatorio2;
	rewind(fp5);
	int size=sizeof(RelatorioClimatico);
	fseek(fp5, -size, SEEK_END);
	
	fread(&relatorio2, size, 1, fp5);
	
	printf("\n\n Um registro lido \n\n");
	fflush(stdin);
	printf("\n\n O local cuja previsao sera registrada %s ", relatorio2.nomeLocal);
	fflush(stdin);
	printf("\n\n A temperatura do local na hora da previsao %i ",relatorio2.temperatura);
	
	printf("\n\n O ano em que a previsao foi feita %i ", relatorio2.dataColeta.tm_year);
	
	printf("\n\n O mes em que a previsao foi feita %i ", relatorio2.dataColeta.tm_mon);
	
	printf("\n\n O dia do mes em que a previsao foi feita %i ", relatorio2.dataColeta.tm_mday);
	
	printf("\n\n A hora da coleta %i ", relatorio2.dataColeta.tm_hour);
	
	printf("\n\n Os minutos da coleta %i ", relatorio2.dataColeta.tm_min);

	printf("\n\n Os segundos da coleta %i ", relatorio2.dataColeta.tm_sec);
	
}

void testWriteRandom(FILE *fpp)
{
	struct timeval tm_ini, tm_fim;
	gettimeofday(&tm_ini, NULL);
	int x=0;

	struct tm dataColeta;
	int size = sizeof(RelatorioClimatico);
	RelatorioClimatico relatorioClimatico;
	
	while(x<55700)
	{
		fseek(fpp, size, SEEK_END);
		NameGen(relatorioClimatico.nomeLocal);
		fflush(stdin);
		relatorioClimatico.dataColeta = GeraData();
		fflush(stdin);
		relatorioClimatico.temperatura = rand() % 45;
		fflush(stdin);
		fwrite(&relatorioClimatico, size, 1, fpp);
		x++;
	}
	rewind(fpp);
	
	
    gettimeofday(&tm_fim, NULL);
    double diff_sec = difftime(tm_fim.tv_sec, tm_ini.tv_sec);
    double diff_milli = difftime(tm_fim.tv_usec, tm_ini.tv_usec)/1000000;

    printf("O tempo de execução foi %f segundos.\n", diff_sec+diff_milli);
	 
}


/** \ fn
    Funcao escrever no Arquivo
*/
void writeFile(FILE *fp5)
{
	RelatorioClimatico relatorio1;
	int size = sizeof(RelatorioClimatico);
	fseek(fp5, size, SEEK_END);
	
	printf("\n\n Funcao de inserir registros: \n\n");
	fflush(stdin);
	printf("\n\n Digite o local cuja previsao sera registrada: \n\n");
	scanf("%s", relatorio1.nomeLocal);
	fflush(stdin);
	printf("\n\n Digite a temperatura do local na hora da previsao: \n\n");
	scanf("%i",&relatorio1.temperatura);
	fflush(stdin);
	printf("\n\n Digite o ano em que a previsao foi feita: \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_year);
	fflush(stdin);
	printf("\n\n Digite o mes em que a previsao foi feita: \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_mon);
	fflush(stdin);
	printf("\n\n Digite o dia do mes em que a previsao foi feita: \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_mday);
	fflush(stdin);
	printf("\n\n Digite a hora da coleta: \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_hour);
	fflush(stdin);
	printf("\n\n Digite os minutos da coleta: \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_min);
	fflush(stdin);
	printf("\n\n Digite os segundos da coleta: \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_sec);
	fflush(stdin);
	
	 
	fwrite(&relatorio1, size , 1, fp5);
	rewind(fp5);
}


/** \ fn
Função para limpar a tela
*/

void clearScreen()
{
	printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ");
}


/** \ fn
Função que verifica se um valor está entre o intervalo delimitado por lower ou upper, 
só retorna verdade se o valor(val) for menor que o limite inferior(lower) ou se o valor(val) for maior que o limite superior(upper)*/
static int out_of_range ( int val, int lower, int upper )
{
  return val < lower || upper < val;
}


/** \ fn
Função menu que apresenta as opções do usuário */
static int menu (void)
{
  int option = 0;
   
  while ( out_of_range ( option, 1, 5 ) ) {
    printf ( "\n\n Sistema de Relatorios Climaticos - Digite a opcao desejada - \n" );
    printf ( "[1] Inserir registro no arquivo \n" );
    printf ( "[2] Apagar registro do arquivo \n" );
    printf ( "[3] Listar o ultimo registro \n" );
    printf ( "[4] Exibir na tela o tamanho do arquivo contendo os registros \n" );
    printf ( "[5] Sair\n\n" ); 
    fflush(stdin);	
    scanf ( "%d", &option );
     
    if ( out_of_range ( option, 1, 5 ) )
    {
      printf("Entrada invalida, por favor tente novamente.\n");
      fflush(stdin);
  	}
  }
   
  return option;
}

/** \ fn/
 Submenu de inserção */
static int insertMenu (void)
{
  int option = 0;
   
  while ( out_of_range ( option, 1, 3 ) ) {
    printf ( "\n\n Insercao de Registros - Digite a opcao desejada - \n" );
    printf ( "[1] Inserir registros por quantidade \n" );
    printf ( "[2] Inserir registros por tamanho total \n" );
    printf ( "[3] Sair \n" );
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


/** \ fn/
 Printa na tela o tamanho do arquivo em bytes */	
int fileSize(FILE *fp5)
{
	fseek(fp5, 0, SEEK_END);
	printf("O tamanho do arquivo eh de %ld em bytes, e contem %ld registros \n \n ",ftell(fp5), ftell(fp5)/92 );
}
/**
############## MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / 
############## MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / 
############## MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / 
*/

int main(void)
{
	srand(time(NULL));
	int intMenu=0;
	int intInsertMenu=0;
	long int sizeOfFile=0;
	long int numberOfRegistries=0;
	
	/** Abrindo os ponteiros para o Arquivo */
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
	    
	fp2 = fopen(FILENAME , "rb+");
	    if(fp2 == NULL)
	    {
	        fp2 = fopen(FILENAME , "wb+");
	        if(fp2 == NULL)
	        {
	            printf("error in opening file : \n");
	            return -1;
	        }
	    }
    
	/** Menu */
	while((intMenu = menu())!=5)
	{
		
		if(intMenu == 1)
		{
			clearScreen();
			fseek(fp1, 0, SEEK_END);
			printf ( " \n \n [1] Funcao de inserir registros, gostaria de inserir por: \n [1].[1]quantidade de registros?(Opcao 1) ou \n [1].[2] adicionar por tamanho?(Opcao 2) \n \n (O arquivo atual possui %ld bytes/ %ld kbytes / %ld megabytes e %ld registros) \n \n \n", ftell(fp1), ftell(fp1)/1024, (ftell(fp1)/1024)/1024, ftell(fp1)/184 );
			rewind(fp1);
			while((intInsertMenu = insertMenu())!=3)
			{
				if (intInsertMenu == 1)
				{
					printf ( "\n\n [1].[1] Inserir registros por quantidade \n\n" );
					printf ( "\n\n [1].[1] Quantos registros aleatorios gostaria de adicionar? \n\n ");
    				scanf ( "%ld", &numberOfRegistries );
    				testWriteRandom(fp1);
				}
				if (intInsertMenu == 2)
				{
				
					printf ( "\n\n [1].[2] Inserir registros por tamanho total \n\n" );
					printf ( "\n\n [1].[2] Quantos é o tamanho do arquivo que quer gerar?(em bytes) \n\n ");
   					scanf ( "%ld", &sizeOfFile );
    				testWriteRandom(fp1);
				}
			}
	   		
		}
		
		if(intMenu == 2)
		{
			clearScreen();
			printf ( "\n\n [2] Apagar todos os registros \n \n \n" );
			fp1 = fopen(FILENAME , "wb+");
			fclose(fp1);
		}
		
		if(intMenu == 3)
		{
			clearScreen();
			printf ( "\n \n [3] Listar o último registro \n \n" );
	        readLastFile(fp2);
		}
		
		if(intMenu == 4)
		{
			clearScreen();
			fileSize(fp1);
		}
		
		if(intMenu == 5)
		{
			printf ( "\n \n [5] Sair \n \n " );
		} 
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}

