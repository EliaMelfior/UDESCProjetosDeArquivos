#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RelatoriosClimaticos.bin"
#define NUMERODEBLOCOS 2271282
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

typedef struct node
{
        RelatorioClimatico *relatorio;
        struct node *ant;
        struct node *prox;
}node;

typedef struct list {
        int tamanho;
        node *inicio;
        node *fim;
}list;

list* createList(){
	list *list1 = (list *) malloc (sizeof(list));
	if(list1 != NULL){
		list1->inicio = NULL;
		list1->fim = NULL;
		list1->tamanho = 0;
	}
	return list1;
}
//rnew = relatorio novo

int adicionaNoInicio (list *list, RelatorioClimatico *relatorio){
	node *rnew = (node *) malloc (sizeof(node));
	RelatorioClimatico *relatorioTemp = (RelatorioClimatico *) malloc(sizeof(RelatorioClimatico));
	if(relatorioTemp!=NULL){
		*relatorioTemp = *relatorio;
	}
	if(rnew!=NULL){
		rnew->relatorio = relatorioTemp;
		rnew->prox = list->inicio;
		rnew->ant = NULL;
		if(rnew->prox != NULL){
			rnew->prox->ant = rnew;
		}
		list->inicio = rnew;
		if(list->fim == NULL){
			list->fim = rnew;
		}
		list->tamanho++;
		return list->tamanho;
	}
	return 0;
}

int adicionaNoFim (list *list, RelatorioClimatico *relatorio){
	if(list->tamanho == 0){
		//printf("\n sai do fim e adiciona no inicio porque a lista esta vazia");
		return adicionaNoInicio(list, relatorio);;
	}
	RelatorioClimatico *relatorioTemp = (RelatorioClimatico *) malloc(sizeof(RelatorioClimatico));
	if(relatorioTemp!=NULL){
		*relatorioTemp = *relatorio;
	}
	node *rnew = (node *) malloc (sizeof(node));
	if(rnew!=NULL){
		rnew->relatorio = relatorioTemp;
		//printf(" adiciona no fim: %s", rnew->relatorio->nomeLocal);
		rnew->ant = list->fim;
		rnew->prox = NULL;
		if(rnew->ant != NULL){
			rnew->ant->prox = rnew;
		}
		list->fim = rnew;
		//printf("imprimindo o fim da lista: %s", list->fim->relatorio->nomeLocal);
		list->tamanho++;
		return list->tamanho;
	}
	return 0;
}
/**
int adicionaNoInicio (list *list, RelatorioClimatico *relatorio){
	node *rnew = (node *) malloc (sizeof(node));
	if(rnew!=NULL){
		rnew->relatorio = relatorio;
		rnew->prox = list->inicio;
		rnew->ant = NULL;
		if(rnew->prox != NULL){
			rnew->prox->ant = rnew;
		}
		list->inicio = rnew;
		list->tamanho++;
		return list->tamanho;
	}
	return 0;
}


int adicionaNoFim (list *list, RelatorioClimatico *relatorio){
	if(list->tamanho == 0){
		printf("\n sai do fim e adiciona no inicio porque a lista esta vazia");
		adicionaNoInicio(list, relatorio);
		return 0;
	}
	node *rnew = (node *) malloc (sizeof(node));
	if(rnew!=NULL){
		rnew->relatorio = relatorio;
		rnew->ant = list->fim;
		rnew->prox = NULL;
		if(rnew->ant != NULL){
			rnew->ant->prox = rnew;
		}
		list->fim = rnew;
		list->tamanho++;
		return list->tamanho;
	}
	return 0;
}	
*/

//imprime a lista do inicio ao fim
/**
void printList(list *lista){ 
	info *relatorioTemp = (info *)malloc(sizeof(info));
    if (lista->begin == NULL)
    {
        printf("\n A lista esta vazia!");
        return;
    }
    relatorioTemp = lista->begin;
    
    while (relatorioTemp != NULL)
    {
        printf("\n %s", relatorioTemp->relatorio->nomeLocal);
        relatorioTemp = relatorioTemp->next;
    }
}
*/




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

/** \ fn/
 Printa na tela o tamanho do arquivo em bytes */	
void fileSize(FILE *fp5)
{
	fseek(fp5, 0, SEEK_END);
	printf("O tamanho do arquivo eh de %li em bytes, %li em Mbytes, e contem %li registros \n \n ",ftell(fp5), ((ftell(fp5))/1024)/1024,  ftell(fp5)/92 );
	printf("Tamanho de cada registro: %li", sizeof(RelatorioClimatico));
}

/** \ fn
    Ler o Arquivo 
*/



void readLastFile(FILE *fp5)
{

	RelatorioClimatico relatorio2;
	rewind(fp5);
	int i=0;
	int size=sizeof(RelatorioClimatico);
	list *listLeitura = createList();
	int tamanhoLista = 0;
	
	fseek(fp5, size, SEEK_SET);
	for(i=1; i<=NUMERODEBLOCOS; i++){
		RelatorioClimatico *relatorioTESTE = (RelatorioClimatico*) malloc(sizeof(RelatorioClimatico));
		fread(relatorioTESTE, size, 1, fp5);
		tamanhoLista = adicionaNoFim(listLeitura , relatorioTESTE);

	}
	
printf("tamanho da lista: %i", tamanhoLista);
}

/** \ fn
	funcao escrever registros aleatorios por tamanho ###########################################################################################
*/
long int determineNumberOfRegistries(long int fileSizeVariable2)
{
	long int fileSizeInBytes;
	long int numberOfRegistries;
	
	fileSizeInBytes=(fileSizeVariable2*1024)*1024; //De megabytes para bytes
	
	numberOfRegistries=fileSizeInBytes/sizeof(RelatorioClimatico); //Da quantidade de bytes para a quantidade de registros
	
	return(numberOfRegistries);
}

void createFileByRegistryAmmount(FILE *fpp, long int numberOfRegistries)  //Opção 2
{
    struct timeval tm_ini, tm_fim;
    gettimeofday(&tm_ini, NULL);
    
    long int y=0;
    struct tm dataColeta;
    
    int size = sizeof(RelatorioClimatico);
    RelatorioClimatico *relatorioClimatico = (RelatorioClimatico*)malloc((numberOfRegistries) * sizeof (RelatorioClimatico));;

    rewind(fpp);
    while(y<numberOfRegistries)
    {
        NameGen(relatorioClimatico[y].nomeLocal);
        fflush(stdin);
        relatorioClimatico[y].dataColeta = GeraData();
        fflush(stdin);
        relatorioClimatico[y].temperatura = rand() % 45;
        fflush(stdin);
        y++;
    }
    fseek(fpp, size, SEEK_END);
    fwrite(relatorioClimatico, size*numberOfRegistries, 1, fpp);


    gettimeofday(&tm_fim, NULL);
    double diff_sec = difftime(tm_fim.tv_sec, tm_ini.tv_sec);
    double diff_milli = difftime(tm_fim.tv_usec, tm_ini.tv_usec)/1000000;
	
    printf("Os relatorios foram gerados em %f segundos, e o arquivo agora possui %li bytes, %li Mbytes \n", diff_sec+diff_milli, ftell(fpp), ((ftell(fpp))/1024)/1024);
    rewind(fpp);

}


/** \ fn
    Funcao escrever no Arquivo
*/
void writeFile(FILE *fp5)
{
	
	RelatorioClimatico *relatorio1 = (RelatorioClimatico*) malloc (sizeof(RelatorioClimatico));
	
	int size = sizeof(RelatorioClimatico);
	fseek(fp5, size, SEEK_END);
	
	printf("\n\n Funcao de inserir registros: \n\n");
	fflush(stdin);
	printf("\n\n Digite o local cuja previsao sera registrada: \n\n");
	scanf("%s", relatorio1->nomeLocal);
	fflush(stdin);
	printf("\n\n Digite a temperatura do local na hora da previsao: \n\n");
	scanf("%i",&relatorio1->temperatura);
	fflush(stdin);
	printf("\n\n Digite o ano em que a previsao foi feita: \n\n");
	scanf("%i",&relatorio1->dataColeta.tm_year);
	fflush(stdin);
	printf("\n\n Digite o mes em que a previsao foi feita: \n\n");
	scanf("%i",&relatorio1->dataColeta.tm_mon);
	fflush(stdin);
	printf("\n\n Digite o dia do mes em que a previsao foi feita: \n\n");
	scanf("%i",&relatorio1->dataColeta.tm_mday);
	fflush(stdin);
	printf("\n\n Digite a hora da coleta: \n\n");
	scanf("%i",&relatorio1->dataColeta.tm_hour);
	fflush(stdin);
	printf("\n\n Digite os minutos da coleta: \n\n");
	scanf("%i",&relatorio1->dataColeta.tm_min);
	fflush(stdin);
	printf("\n\n Digite os segundos da coleta: \n\n");
	scanf("%i",&relatorio1->dataColeta.tm_sec);
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
    printf ( "[2] Apagar todos os registros / Limpar o arquivo \n" );
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
   
  while ( out_of_range ( option, 1, 4 ) ) 
  {
    printf ( "\n\n Insercao de Registros - Digite a opcao desejada - \n" );
    printf ( "[1] Inserir registros por quantidade \n" );
    printf ( "[2] Inserir registros por tamanho total \n" );
    printf ( "[3] Inserir registros manualmente \n" );
    printf ( "[4] Sair \n" );
    fflush(stdin);	
    scanf ( "%d", &option );
     
    if ( out_of_range ( option, 1, 4) )
    {
      printf("Entrada invalida, por favor tente novamente.\n");
      fflush(stdin);
  	}
  }
   
  return option;
}



/**
############## MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / 
############## MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / 
############## MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / MAIN / 
*/

int main(void)
{
	
	
	
	int intMenu=0;
	int intInsertMenu=0;
	long int fileSizeVariable=0;
	long int numberOfRegistries=0;
	srand(time(NULL));
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
			printf ( " \n \n [1] Funcao de inserir registros, gostaria de inserir por: \n [1].[1]quantidade de registros?(Opcao 1),  \n [1].[2] adicionar por tamanho?(Opcao 2)  ou \n [1].[3] adicionar um registro manualmente?(Opcao 3) []\n \n (O arquivo atual possui %li bytes/ %li kbytes / %li megabytes e %li registros) \n \n \n", ftell(fp1), ftell(fp1)/1024, (ftell(fp1)/1024)/1024, ftell(fp1)/184 );
			rewind(fp1);
			while((intInsertMenu = insertMenu())!=4)
			{
				if (intInsertMenu == 1)
				{
					printf ( "\n\n [1].[1] Inserir registros por quantidade \n\n" );
					printf ( "\n\n [1].[1] Quantos registros aleatorios gostaria de adicionar? \n\n ");
    				scanf ( "%li", &numberOfRegistries );
    				printf( " \n \n Adicionando %li Registros ao arquivo \n \n", numberOfRegistries);
    				createFileByRegistryAmmount(fp1, numberOfRegistries);
				}
				if (intInsertMenu == 2)
				{
				
					printf ( "\n\n [1].[2] Inserir registros por tamanho total \n\n" );
					printf ( "\n\n [1].[2] Qual e o tamanho do arquivo, contendo registros aleatorios, que voce quer gerar?(em MegaBytes) \n\n ");
   					scanf ( "%li", &fileSizeVariable );
    				printf( " \n \n Criando registros para adicionar %li MegaBytes ao arquivo \n \n", fileSizeVariable);
    				numberOfRegistries = determineNumberOfRegistries(fileSizeVariable);
   					createFileByRegistryAmmount(fp1, numberOfRegistries);
				}
				if (intInsertMenu == 3)
				{
				
					printf ( "\n\n [1].[3] Inserir registro manualmente \n\n" );
    				printf( " \n \n Adicionar registro manualmente \n \n");
    				writeFile(fp1);
				}
			}
	   		
		}
		
		if(intMenu == 2)
		{
			clearScreen();
			printf ( "\n\n [2] Apagar todos os registros \n \n \n" );
			fp1 = fopen(FILENAME , "wb+");
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

