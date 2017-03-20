#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RegistrosDoAluno.bin"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

/** \ brief Dois ponteiros como variaveis globais, um para gravar e outro para ler arquivos */
FILE *fp1, *fp2;

/** \ struct
    Struct do aluno
    Dados necessarios:  nome do aluno, 
	                    materia,
					    notas, 
						faltas,
						media,
						situação
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
 Ler o último registro de aluno adicionado
*/
void readLastFile(FILE *fp5)
{
	Aluno aluno2;
	rewind(fp5);
	int size=sizeof(Aluno), contador = 0;
	fseek(fp5, -size, SEEK_END);
	
	fread(&aluno2, size, 1, fp5);
	
	printf("\n\n Um registro lido \n\n");
	fflush(stdin);
	printf("\n\n O nome do aluno : %s ", aluno2.nome);
	fflush(stdin);
	printf("\n\n Este aluno possuia %i faltas", aluno2.faltas);
	
	printf("\n\n A materia deste relatorio é: %s ", aluno2.materia);
	fflush(stdin);
	
	printf("\n\n As %i notas do aluno são : ", aluno2.quantidadeDeNotas);
	
	for(contador=0; contador<aluno2.quantidadeDeNotas; contador++) {
		printf("\n\n As %ia nota do aluno é : %i", contador, aluno2.notas[contador]);
	}
	
	printf("\n\n O aluno está : %s", aluno2.situacao);
	
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
			                   
	//Adiciona o prefixo / nome
	strcpy(NomeDoAluno, name[(int)rand()%100]);
    strcat(NomeDoAluno, " ");
    //Adiciona o nome do meio
	strcpy(NomeDoAluno, midname[(int)rand()%26]);
    strcat(NomeDoAluno, " ");
    //Adiciona o último nome
	strcpy(NomeDoAluno, surname[(int)rand()%100]);
    strcat(NomeDoAluno, " ");
}

void MateriaGen(char* Materia)
{
	char *materiasPossiveis[20] = {"LanguageArts", "Mathematics", "Science", "Health", "Handwriting", 
						  "PhysicalEducation", "Art", "Music", "Movement", "Handwork", "Gardening", 
						  "Dramatics", "Dance", "Spanish" ,"Leadership", "SpecialEducation","Reading", 
						  "English", "Algebra", "Geometry"};
					
	strcpy(Materia, materiasPossiveis[(int)rand()%20]);    
    
}

long int determineNumberOfRegistries(long int fileSizeVariable2)
{
	long int fileSizeInBytes;
	long int numberOfRegistries;
	
	fileSizeInBytes=(fileSizeVariable2*1024)*1024; //De megabytes para bytes
	
	numberOfRegistries=fileSizeInBytes/sizeof(Aluno); //Da quantidade de bytes para a quantidade de registros
	
	return(numberOfRegistries);
}

void createFileByRegistryAmmount(FILE *fpp, long int numberOfRegistries)  //OpÃ§Ã£o 2
{
	struct timeval tm_ini, tm_fim;
	gettimeofday(&tm_ini, NULL);
	    
    long int y=0;
    int size = sizeof(Aluno);
    int contador = 0;
    float somaDasNotas = 0.0;
    Aluno *aluno = (Aluno*)malloc((numberOfRegistries) * sizeof (Aluno));

    rewind(fpp);
    while(y<numberOfRegistries)
    {
        NameGen(aluno[y].nome);
        fflush(stdin);\
        MateriaGen(aluno[y].materia);
        fflush(stdin);
        aluno[y].quantidadeDeNotas = rand() % 20;
        for(contador=0; contador<aluno[y].quantidadeDeNotas; contador++) {
        	aluno[y].notas[contador] = ((float)rand()/(float)(RAND_MAX)) * 10.0;
        	somaDasNotas = somaDasNotas + aluno[y].notas[contador];
		}
		aluno[y].media = somaDasNotas/aluno[y].quantidadeDeNotas;
		aluno[y].faltas = rand() % 36;
		if(aluno[y].faltas<=18 && aluno[y].media >= 7.0) 
		{
			strcpy(aluno[y].situacao, "Aprovado");
		} else {
			strcpy(aluno[y].situacao, "Reprovado");
		}
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
	int numberOfBlocksNeeded, counter, totalRest;
 	
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
/*
void writeFile(FILE *fp5)
{
	Aluno aluno1;
	int size = sizeof(Aluno);
	fseek(fp5, size, SEEK_END);
	
	printf("\n\n Funcao de inserir registros: \n\n");
	fflush(stdin);
	
	printf("\n\n Digite o local cuja previsao sera registrada: \n\n");
	scanf("%s", relatorio1.nomeLocal);
	 
	fwrite(&relatorio1, size , 1, fp5);
	rewind(fp5);
}
*/


/** \ fn
FunÃ§Ã£o para limpar a tela
*/

void clearScreen()
{
	printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n ");
}


/** \ fn
FunÃ§Ã£o que verifica se um valor estÃ¡ entre o intervalo delimitado por lower ou upper, 
sÃ³ retorna verdade se o valor(val) for menor que o limite inferior(lower) ou se o valor(val) for maior que o limite superior(upper)*/
static int out_of_range ( int val, int lower, int upper )
{
  return val < lower || upper < val;
}


/** \ fn
FunÃ§Ã£o menu que apresenta as opÃ§Ãµes do usuÃ¡rio */
static int menu (void)
{
  int option = 0;
   
    while ( out_of_range ( option, 1, 7 ) ) {
    printf ( "\n\t Gerador de relatorios dos alunos - \n" );
    printf ( "[1] Inserir relatório no arquivo (DESATIVADO) \n" );
    printf ( "[2] Apagar todos os registros / Limpar o arquivo \n" );
    printf ( "[3] Listar o ultimo registro \n" );
    printf ( "[4] Exibir na tela o tamanho do arquivo contendo os registros \n" );
    printf ( "[5] Inserir relatorios aleatorios, determinando o tamanho do bloco e o tamanho do arquivo resultante \n" );
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
 Submenu de inserÃ§Ã£o */
static int insertMenu (void)
{
  int option = 0;
   
  while ( out_of_range ( option, 1, 4 ) ) 
  {
    printf ( "\n\n Insercao de Relatorios - Digite a opcao desejada - \n" );
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

