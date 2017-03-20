#include "functions.h"


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
					/*
					printf ( "\n\n [1].[3] Inserir registro manualmente \n\n" );
    				printf( " \n \n Adicionar registro manualmente \n \n");
    				writeFile(fp1);
    				*/
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
			printf ( "\n \n [3] Listar o ultimo registro \n \n" );
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

