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
//relatório exigido

typedef struct RelatorioClimatico
{ 
        char nomeLocal [50]; 
        struct tm dataColeta;
        int temperatura; 
    
}RelatorioClimatico; 

//nó da lista que contém um relatório
typedef struct node
{
        RelatorioClimatico *relatorio;
        struct node *ant;
        struct node *prox;
}node;
//lista para ler o arquivo e consultar
typedef struct list {
        int tamanho;
        node *inicio;
        node *fim;
}list;
//cria a lista
list* createList(){
	list *list1 = (list *) malloc (sizeof(list));
	if(list1 != NULL){
		list1->inicio = NULL;
		list1->fim = NULL;
		list1->tamanho = 0;
	}
	return list1;
}
/**GERAR O ARQUIVO EM BLOCOS DE DEFINE MB
 * RESOLVER BUG DO REGISTRO
 * GRAVAR UMA LISTA NO ARQUIVO
 * CONSULTA POR CIDADE, TEMPERATURA E DATA.
 * 
 * 
 * 
 * 
 * 
*/
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

//teste imprimir lista
void printList(list *list){
	node *nodePonteiro = list->inicio;
	int i=0;
	for(i=0; i<NUMERODEBLOCOS; i++){
	printf("\n Nome do local: %s",nodePonteiro->relatorio->nomeLocal);
	printf("\n\n A temperatura do local na hora da previsao: %i ",nodePonteiro->relatorio->temperatura);
	
	printf("\n\n O ano em que a previsao foi feita: %i ", nodePonteiro->relatorio->dataColeta.tm_year);
	
	printf("\n\n O mes em que a previsao foi feita: %i ", nodePonteiro->relatorio->dataColeta.tm_mon);
	
	printf("\n\n O dia do mes em que a previsao foi feita: %i ", nodePonteiro->relatorio->dataColeta.tm_mday);
	
	printf("\n\n A hora da coleta: %i ", nodePonteiro->relatorio->dataColeta.tm_hour);
	
	printf("\n\n Os minutos da coleta: %i ", nodePonteiro->relatorio->dataColeta.tm_min);

	printf("\n\n Os segundos da coleta: %i ", nodePonteiro->relatorio->dataColeta.tm_sec);
	nodePonteiro = nodePonteiro->prox;
	}
}


/**
FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / 
FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / 
FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / FIM DA LISTA (TESTE) / 
*/



/** READ FILE TO LIST / READ FILE TO LIST / READ FILE TO LIST / READ FILE TO LIST / READ FILE TO LIST / READ FILE TO LIST / READ FILE TO LIST / 
*/
void readFileToList (FILE *fp5){
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
	printList(listLeitura);
}

/*void readFileToListByParam (FILE *fp5, int prop, char* value){
	rewind(fp5);
	int i;
	int size=sizeof(RelatorioClimatico);
	list *listLeitura = createList();
	int tamanhoLista = 0;
	fseek(fp5, 0, SEEK_SET);
	long int fileSize = ftell(fp5);
	long int numberOfRegistries = fileSize/NUMERODEBLOCOS;
	printf("%li", numberOfRegistries);
	for(i=1; i<=NUMERODEBLOCOS; i++){
		//printf("ENTROU NO FOR");
		//RelatorioClimatico *relatorioTESTE = (RelatorioClimatico*) malloc((sizeof(RelatorioClimatico) * numberOfRegistries));
		//fread(relatorioTESTE, size, numberOfRegistries, fp5);
		int y = 0;
		while(y<numberOfRegistries)
	    {
	    	printf("ENTROU NO WHILE");
			RelatorioClimatico *relatorioTESTE = (RelatorioClimatico*) malloc(sizeof(RelatorioClimatico));
			fread(relatorioTESTE, size, 1, fp5);
			printf("\n teste 2, imprimir apos teste 1");
			char dataRelatorio[10];
			dataRelatorio[0]=0;
	        switch (prop)
			{
				case 1:
					if(strcmp(relatorioTESTE[y].nomeLocal, value) == 0)
						tamanhoLista = adicionaNoFim(listLeitura , relatorioTESTE);
						printf("\n teste, mesmo nome de cidade");
				break;
				case 2:
					if(strcmp(relatorioTESTE[y].temperatura, value) == 0)
						tamanhoLista = adicionaNoFim(listLeitura , relatorioTESTE);
				break;
				case 3:
					strcat(dataRelatorio, relatorioTESTE[y].dataColeta.tm_mday);
					strcat(dataRelatorio, "/");
					strcat(dataRelatorio, relatorioTESTE[y].dataColeta.tm_mon);
					strcat(dataRelatorio, "/");
					strcat(dataRelatorio, relatorioTESTE[y].dataColeta.tm_year);
					if(strcmp(dataRelatorio, value) == 0)
						tamanhoLista = adicionaNoFim(listLeitura , relatorioTESTE);
				break;
			}
	        y++;
	    }
		
		//tamanhoLista = adicionaNoFim(listLeitura , relatorioTESTE);
	}
	printf("tamanho da lista: %i", tamanhoLista);
	printList(listLeitura);
}
*/
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


void writeToFileByBlocks(FILE *fppp, long int blockSize, long int sizeInMb)
{
	long int fileSizeInBytes, blockSizeInBytes;
	int numberOfBlocksNeeded,  counter, totalRest;
 	
	fileSizeInBytes=(sizeInMb*1024)*1024; //De megabytes para bytes
	blockSizeInBytes=(blockSize*1024)*1024;
	
	numberOfBlocksNeeded = fileSizeInBytes/blockSizeInBytes;
	

    
	for(counter=0;counter<numberOfBlocksNeeded; counter++)
	{
	
		createFileByRegistryAmmount(fppp, (blockSizeInBytes/sizeof(RelatorioClimatico)));
	}

 
	
	totalRest = fileSizeInBytes % blockSizeInBytes;
	totalRest = totalRest + (blockSizeInBytes % sizeof(RelatorioClimatico));
	totalRest = totalRest/sizeof(RelatorioClimatico);
	//resto dos blocos

	createFileByRegistryAmmount(fppp, totalRest);
}

/** \ brief Dois ponteiros como variáveis globais, um para gravar e outro para ler arquivos */
FILE *fp1, *fp2;


/** \ fn/
 Printa na tela o tamanho do arquivo em bytes */	
void fileSize(FILE *fp5)
{
	fseek(fp5, 0, SEEK_END);
	printf("O tamanho do arquivo eh de %li em bytes, %li em Mbytes, e contem %li registros \n \n ",ftell(fp5), ((ftell(fp5))/1024)/1024,  ftell(fp5)/sizeof(RelatorioClimatico) );
	printf("Tamanho de cada registro: %li", sizeof(RelatorioClimatico));
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
   
  while ( out_of_range ( option, 1, 6 ) ) {
    printf ( "\n\t Sistema de Relatorios Climaticos - Digite a opcao desejada - \n" );
    printf ( "[1] Gerar arquivo texto com os registros ordenados \n" );
    printf ( "[2] Limpar tela \n" );
    printf ( "[3] Exibir na tela o tamanho do arquivo contendo os registros \n" );
    printf ( "[4] Ordenar registros por temperatura \n" );
    printf ( "[5] Listar registros ordenados \n" );
    printf ( "[6] Sair\n\n" ); 
    fflush(stdin);	
    scanf ( "%d", &option );
     
    if ( out_of_range ( option, 1, 6) )
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
	int intConsultaMenu=0;
	long int fileSizeVariable=0;
	long int numberOfRegistries=0;
	long int BlockSize=0;
	char paramConsulta[50];
	paramConsulta[0]=0;
	srand(time(NULL));
	
	/** Abrindo os ponteiros para o Arquivo, fp1 para escrita e fp2 para leitura*/
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
    
	/** Menu 
	printf ( "\n\t Sistema de Relatorios Climaticos - Digite a opcao desejada - \n" );
    printf ( "[1] Gerar arquivo texto com os registros ordenados \n" );
    printf ( "[2] Limpar tela \n" );
    printf ( "[3] Exibir na tela o tamanho do arquivo contendo os registros \n" );
    printf ( "[4] Ordenar registros por temperatura \n" );
    printf ( "[5] Sair\n\n" );
	*/
	
	while((intMenu = menu())!=6)
	{
		
		if(intMenu == 1)
		{
			clearScreen();
			fseek(fp1, 0, SEEK_END);
			printf ( " \n \n [1] Gerar arquivo texto com os registros ordenados (O arquivo atual possui %li bytes/ %li kbytes / %li megabytes e %li registros) \n \n \n", ftell(fp1), ftell(fp1)/1024, (ftell(fp1)/1024)/1024, ftell(fp1)/184 );
		}
		
		if(intMenu == 2)
		{
			clearScreen();
			fileSize(fp1);
		}
		
		if(intMenu == 3)
		{
			fileSize(fp1);
		}
		
		if(intMenu == 4)
		{
			//Função de Ordenação
		}
		
		if(intMenu == 5)
		{
		
			printf ( "\n \n [5] Sair \n \n " );
		}

	fclose(fp1);
	fclose(fp2);
	return 0;
}

