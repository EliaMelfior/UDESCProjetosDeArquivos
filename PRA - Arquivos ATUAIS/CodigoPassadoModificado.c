#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RegistrosDoAluno.bin"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

/** \ brief Dois ponteiros como variáveis globais, um para gravar e outro para ler arquivos */
FILE *fp1, *fp2;

/** \ struct
    Struct do aluno
    Dados necessarios:  nome do aluno, 
	                    materia,
					    notas, 
						faltas,
						media,
						situa��o
*/

typedef struct aluno{
        char nome[30];
        char materia[30];
        float notas[20];
        int faltas;
        float media;
        char situacao[10];
    	int quantidadeDeNotas;
}Aluno;



/** \ fn/
 Printa na tela o tamanho do arquivo em bytes */	
void fileSize(FILE *fp5)
{
	fseek(fp5, 0, SEEK_END);
	printf("O tamanho do arquivo eh de %li em bytes, e %li em Mbytes",ftell(fp5), ((ftell(fp5))/1024)/1024);
}

/** \ fn
 Ler o �ltimo registro de aluno adicionado
*/
void readLastFile(FILE *fp5)
{
	Aluno aluno2;
	rewind(fp5);
	int size=sizeof(Aluno);
	fseek(fp5, -size, SEEK_END);
	
	fread(&aluno2, size, 1, fp5);
	
	printf("\n\n Um registro lido \n\n");
	fflush(stdin);
	printf("\n\n O nome do aluno : %s ", aluno2.nome);
	fflush(stdin);
	printf("\n\n Este aluno possuia %i faltas", i, aluno2.faltas);
	
	printf("\n\n A materia deste relat�rio �: %s ", aluno2.materia);
	fflush(stdin);
	
	printf("\n\n As %i notas do aluno s�o : ", aluno2.quantidadeDeNotas);
	for(int i=0; i<aluno2.quantidadeDeNotas, i++) {
		printf("\n\n As %ia nota do aluno � : %i", i, aluno2.notas[i]);
	}
	
	printf("\n\n O aluno est� : %s", aluno2.situacao);
	
	fflush(stdin);
}

void NameGen(char* NomeDoAluno)
{
	char *name[100] = {"Stuart","Van","Odis","Chas","Santo","Bradley","Hank","Conrad","Randal","Salvatore","Jackie","Johnie","Brady","Merlin","Hilton","Neal",
                         "Beau","Herschel","Milton","Deshawn","Dick","Caleb","Tim","Otis","Dillonv","Dominick","Clayton","Neville","Brock","Byron","Earle","Errol",
                         "Armand","Drew","Demarcus","Mervin","Duncan","Alton","Valentine","Charles","Evan","Clement","Lucien","Wayne","Wayne","Curtis","Eli,Carey",
                         "Ezra","Florencio","Adolfo","Leia","Laquita","Arlette","Rosamaria","Delois","Melva","Blythe","Gricelda","Sheri","Carolee","Christeen",
                         "Rosetta","Erminia","Lesli","Alene","Mahalia","Janeen","Domonique","Berna","Ferne","Latrisha","Mindy","Denese","Porsche","Lore","Elissa",
                         "Lajuana","Willette","Ngan","Marvella","Jolie","Adriene","Gwenda","Dorothy","Reva","Elaina","Fransisca","Nakita","Brandee","Zoraida",
                         "Giovanna","Jodee","Maida","Jung","Florinda","Gianna","Jerri","Karlyn","Etha","Isobel"};

    char *midname[26] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

    char *surname[100] = {"Rudnick","Kershaw","Kowalski","Quezada","Alexis","Norrell","Folsom","Lawhon","Burgher","Frier","Herod","Dalal","Bak","Hoeft","Wease","Feagin",
                            "Zahler","Lococo","Ainsworth","Turmelle","Yandell","Baskins","Linde","Trafton","Luebbert","Filiault","Seale","Whetstone","Moretz","Hammersley",
                            "Nellum","Matney","Kershner","Mcclintock","Radcliff","Giuffre","Dumas","Plasse","Hacker","Wansley","Cummingham","Mcgirt","Dewald","Tillery","Scipio",
                            "Bone","Deharo","Mcglothlin","Work","Truesdell","Glidewell","Curren","Pilot","Maddock","Eggert","Toby","Borg","Phung","Mancuso","Garr","Hazeltine",
                            "Kisner","Connery","Bussell","Simpler","Farver","Delsignore","Coury","Coonrod","Buttner","Rothman","Balbuena","Silverberg","Peltz","Flake","Lehmkuhl",
                            "Harten","Hanford","Lima","Armagost","Croker","Manners","Greely","Wine","Dana","Chae","Hoos","Gardea","Silsby","Arbuckle","Gaetano","Hennessey","Willams",
                            "Cavin","Neagle","Scheff","Haworth","Tompson","Eble","Pricer"};
    
	 strcpy(al.nome,name[(int)rand()%100]);
              strcat(al.nome, " ");
              strcat(al.nome,midname[(int)rand()%26]);
              strcat(al.nome, " ");
              strcat(al.nome,surname[(int)rand()%100]);
			                   
	NomeDoAluno[0]=0; //inicializa a String como String vazia
	//Adiciona o prefixo / nome
	strcpy(NomeDoAluno, name[(int)rand()%100]);
    strcat(NomeDoAluno, " ");
    //Adiciona o nome do meio
	strcpy(NomeDoAluno, midname[(int)rand()%26]);
    strcat(NomeDoAluno, " ");
    //Adiciona o �ltimo nome
	strcpy(NomeDoAluno, surname[(int)rand()%100]);
    strcat(NomeDoAluno, " ");
	
	return;
}

long int determineNumberOfRegistries(long int fileSizeVariable2)
{
	long int fileSizeInBytes;
	long int numberOfRegistries;
	
	fileSizeInBytes=(fileSizeVariable2*1024)*1024; //De megabytes para bytes
	
	numberOfRegistries=fileSizeInBytes/sizeof(Aluno); //Da quantidade de bytes para a quantidade de registros
	
	return(numberOfRegistries);
}

void createFileByRegistryAmmount(FILE *fpp, long int numberOfRegistries)  //Opção 2
{
	struct timeval tm_ini, tm_fim;
	gettimeofday(&tm_ini, NULL);
	    
    long int y=0;
    
    int size = sizeof(Aluno);
    Aluno *aluno = (Aluno*)malloc((numberOfRegistries) * sizeof (Aluno));

    rewind(fpp);
    while(y<numberOfRegistries)
    {
        NameGen(aluno[y].nomeLocal);
        fflush(stdin);
        aluno[y].dataColeta = GeraData();
        fflush(stdin);
        aluno[y].temperatura = rand() % 45;
        fflush(stdin);
        y++;
    }
    fseek(fpp, size, SEEK_END);
    if(numberOfRegistries==1)
    {
		fwrite(aluno, size * numberOfRegistries, 1, fpp);
	}
	else
	{
		fwrite(aluno, size * (numberOfRegistries-1), 1, fpp);
	}
	free(aluno);

    gettimeofday(&tm_fim, NULL);
    double diff_sec = difftime(tm_fim.tv_sec, tm_ini.tv_sec);
    double diff_milli = difftime(tm_fim.tv_usec, tm_ini.tv_usec)/1000000;

    printf("Os relatorios foram gerados em %f segundos, e o arquivo agora possui %li bytes, %li Mbytes \n", diff_sec+diff_milli, ftell(fpp), ((ftell(fpp))/1024)/1024);
  
    rewind(fpp);

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
	
		createFileByRegistryAmmount(fppp, (blockSizeInBytes/sizeof(Aluno)));
	}

 
	
	totalRest = fileSizeInBytes % blockSizeInBytes;
	totalRest = totalRest + (blockSizeInBytes % sizeof(Aluno));
	totalRest = totalRest/sizeof(Aluno);
	//resto dos blocos

	createFileByRegistryAmmount(fppp, totalRest);
}




/** \ fn
    Funcao escrever no Arquivo
*/
void writeFile(FILE *fp5)
{
	Aluno relatorio1;
	int size = sizeof(Aluno);
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
	printf("\n\n Digite o mes em que a previsao foi feita:(numerico, de 0 a 12) \n\n");
	scanf("%i",&relatorio1.dataColeta.tm_mon);
	fflush(stdin);
	printf("\n\n Digite o dia do mes em que a previsao foi feita: (numerico, de 0 a 31) \n\n");
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
   
  while ( out_of_range ( option, 1, 7 ) ) {
    printf ( "\n\t Sistema de Relatorios Climaticos - Digite a opcao desejada - \n" );
    printf ( "[1] Inserir registro no arquivo \n" );
    printf ( "[2] Apagar todos os registros / Limpar o arquivo \n" );
    printf ( "[3] Listar o ultimo registro \n" );
    printf ( "[4] Exibir na tela o tamanho do arquivo contendo os registros \n" );
    printf ( "[5] Inserir registros, determinando o tamanho do bloco e o tamanho do arquivo resultante \n" );
    printf ( "[6] Consultar registros \n" );
    printf ( "[7] Sair\n\n" ); 
    fflush(stdin);	
    scanf ( "%d", &option );
     
    if ( out_of_range ( option, 1, 7 ) )
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

/** \ fn/
 Submenu de consulta */
static int consultaMenu (void)
{
  int option = 0;
   
  while ( out_of_range ( option, 1, 4 ) ) 
  {
    printf ( "\n\n Consulta de Registros - Digite a opcao desejada - \n" );
    printf ( "[1] Consultar registros por local \n" );
    printf ( "[2] Consultar registros por temperatura \n" );
    printf ( "[3] Consultar registros por data \n" );
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
	int intConsultaMenu=0;
	long int fileSizeVariable=0;
	long int numberOfRegistries=0;
	long int BlockSize=0;
	char paramConsulta[50];
	paramConsulta[0]=0;
	
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
	while((intMenu = menu())!=7)
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
					printf ( "\n\n [1].[1] Inserir registros determinando o tamanho do Bloco e do arquivo. \n\n" );
					printf ( "\n\n [1].[1] Qual é o tamanho do bloco?(Em megabytes) \n\n ");
    				scanf ( "%li", &BlockSize );
    				printf ( "\n\n [1].[2] Qual e o tamanho do arquivo, contendo registros aleatorios, que voce gostaria de adicionar ao arquivo?(em MegaBytes) \n\n ");
   					scanf ( "%li", &fileSizeVariable);
   					
   					struct timeval tm_ini, tm_fim;
					gettimeofday(&tm_ini, NULL);
   					
   					writeToFileByBlocks(fp1, BlockSize,fileSizeVariable);
   					
   					gettimeofday(&tm_fim, NULL);
					double diff_sec = difftime(tm_fim.tv_sec, tm_ini.tv_sec);
					double diff_milli = difftime(tm_fim.tv_usec, tm_ini.tv_usec)/1000000;
					
					printf("Os relatorios foram gerados em %f segundos", diff_sec+diff_milli);
		}
		
		if(intMenu == 6)
		{
			printf ( " \n \n [6] Funcao de consultar registros, gostaria de consultar por: \n [6].[1]local?(Opcao 1),  \n [6].[2] temperatura?(Opcao 2)  ou \n [6].[3] data?(Opcao 3) []\n \n ");
			while((intConsultaMenu = consultaMenu())!=4)
			{
				if (intConsultaMenu == 1)
				{
					printf ( "\n\n [6].[1] Consultar registros por local \n\n" );
					printf ( "\n\n [6].[1] Deseja consultar os registros de qual local? \n\n ");
    				scanf ( "%s", &paramConsulta );
    				printf( " \n \n Consultando as registros de %s \n \n", paramConsulta);
    				printf("a");
    				//readFileToListByParam(fp1, 1, paramConsulta);
				}
				if (intConsultaMenu == 2)
				{
					printf ( "\n\n [6].[2] Consultar registros por temperatura \n\n" );
					printf ( "\n\n [6].[2] Deseja consultar os registros com qual temperatura? \n\n ");
    				scanf ( "%s", &paramConsulta );
    				printf( " \n \n Consultando as registros de temperatura %s \n \n", paramConsulta);
    				//readFileToListByParam(fp1, 2, paramConsulta);
				}
				if (intConsultaMenu == 3)
				{
					printf ( "\n\n [6].[3] Consultar registros por data \n\n" );
					printf ( "\n\n [6].[3] Deseja consultar os registros de qual data?(DD/MM/YYYY) \n\n ");
    				scanf ( "%s", &paramConsulta );
    				printf( " \n \n Consultando as registros da data %s \n \n", paramConsulta);
    				//readFileToListByParam(fp1, 3, paramConsulta);
				}
			}
		}
		
		if(intMenu == 7)
		{
			printf ( "\n \n [7] Sair \n \n " );
		} 
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}

