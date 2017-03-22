#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define FNAME "arq.bin"


typedef struct aluno{  // Struct do ALuno
        char nome[30]; // variavel usada para o nome do Aluno
        long mat; // variavel usada para a matricula do Aluno
        float notas[10]; // variavel usada para as notas do Aluno
        int faltas; // variavel usada para a quantidade de faltas do Aluno
        float media; // variavel usada para a media do Aluno
        int sitAc; // variavel usada para a situação do nome do Aluno
        int qntNotas; // variavel usada para a quantidade de notas do Aluno
}Aluno;

long int fileSize(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq);
}

void readLastOnFile(){ // função para saber o ultimo registro do arquivo
	FILE *arq = fopen(FNAME,"rb"); // abertura do arquivo
	Aluno al;
	int i,size=sizeof(Aluno);
	fseek(arq, -size, SEEK_END);
	fread(&al,size,1,arq);
	printf("Nome: %s\n",al.nome); // mostrar o nome do aluno
	printf("Matricula: %li\n",al.mat); // mostrar a matricula do aluno
	printf("Qnt de Faltas: %i\nNotas: ",al.faltas); // mostrar a quantidade de faltas do aluno
	for(i=0;i<al.qntNotas;i++){ // for para mostrar todas as notas do aluno, vai de 0 até o nº de notas que o aluno tem
		printf("%.2f ",al.notas[i]); // mostrar as notas do aluno
	}
	printf("\nMedia: %.2f\n",al.media); // mostrar a media do aluno
	if(al.sitAc==1){ // condição para saber a situação do aluno
		printf("Situacao: Aprovado"); // mostrar que o aluno está aprovado
	}
	if(al.sitAc==2){
		printf("Situacao: Em Exame"); // mostrar que o aluno está em exame
	}
	if(al.sitAc==0){
		printf("Situacao: Reprovado"); // mostrar que o aluno está reprovado
	}
	printf("\n");
	system("pause");
	fclose(arq); // fechamento do aquivo
}

void readByPag(int nPag){ // função para ler os registro por paginação
	FILE *arq = fopen(FNAME,"rb"); // abertura do arquivo
	int i,j,k=0,size=sizeof(Aluno);
	Aluno *al;
	size_t read;
	al = (Aluno*)malloc(nPag*sizeof(Aluno));
	while(fread(al,size,nPag,arq)==nPag){
		for(j=0;j<nPag;j++){ // for para mostrar a quantidade de registros que o usuario informou em cada pagina
			printf("Nome: %s\n",al[j].nome); // mostrar o nome do aluno
			printf("Matricula: %li\n",al[j].mat); // mostrar a matricula do aluno
			printf("Qnt de Faltas: %i\nNotas: ",al[j].faltas);  // mostrar a quantidade de faltas do aluno
			for(i=0;i<al[j].qntNotas;i++){ // for para mostrar todas as notas do aluno, vai de 0 até o nº de notas que o aluno tem
				printf("%.2f ",al[j].notas[i]); // mostrar as notas do aluno
			}
			printf("\nMedia: %.2f\n",al[j].media); // mostrar a media do aluno
			if(al[j].sitAc==1){ // condição para saber a situação do aluno
				printf("Situacao: Aprovado"); // mostrar que o aluno está aprovado
			}
			if(al[j].sitAc==2){
				printf("Situacao: Em Exame"); // mostrar que o aluno está em exame
			}
			if(al[j].sitAc==0){
				printf("Situacao: Reprovado"); // mostrar que o aluno está reprovado
			}
			printf("\n\n");
		}
		k++; // contador para quantas vezes as paginas foram mostradas
		system("pause");
		system("cls");
	}
	Aluno aux;
	rewind(arq);
	fseek(arq, (sizeof(Aluno)*nPag)*k, SEEK_SET);
	printf("Restante dos registros:\n\n");
	while(fread(&aux,size,1,arq)==1){ // condição para mostrar os registros que faltaram 
		printf("Nome: %s\n",aux.nome); // mostrar o nome do aluno
		printf("Matricula: %li\n",aux.mat); // mostrar a matricula do aluno
		printf("Qnt de Faltas: %i\nNotas: ",aux.faltas); // mostrar a quantidade de faltas do aluno
		for(i=0;i<aux.qntNotas;i++){ // for para mostrar todas as notas do aluno, vai de 0 até o nº de notas que o aluno tem
			printf("%.2f ",aux.notas[i]); // mostrar as notas do aluno
		}
		printf("\nMedia: %.2f\n",aux.media); // mostrar a media do aluno
		if(aux.sitAc==1){ // condição para saber a situação do aluno
			printf("Situacao: Aprovado"); // mostrar que o aluno está aprovado
		}
		if(aux.sitAc==2){
			printf("Situacao: Em Exame"); // mostrar que o aluno está em exame
		}
		if(aux.sitAc==0){
			printf("Situacao: Reprovado"); // mostrar que o aluno está reprovado
		}
		printf("\n\n");
	}
	system("pause");
	fclose(arq); // fechamento do arquivo
}

long int HowManyRegisters(){ // função para saber quantos registros tem o arquivo
	FILE *arq=fopen(FNAME,"rb"); // abertuda do arquivo
	long int tamA;
	Aluno al;
	tamA=fileSize(arq); // atribuição do tamanho do arquivo que o usuario informou
	fclose(arq); // fechamento do arquivo
	return (tamA/sizeof(al));
}

Aluno returnRnd(){ // função para inserir os dados do aluno randomicamente
    int aux,aux2,i;
    float md;
    Aluno al;
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


    md=0;
    al.faltas=rand()%25; // random para atribuir a quantidade de faltas do aluno 
    al.qntNotas = rand()%10+1; // random para atribuir a quantidade de notas do aluno
    for(i=0;i<al.qntNotas;i++){ // for para os valores das notas que o aluno possui, vai de 0 até a quantidade de notas que o aluno possui
    	aux=rand(); // random para gerar um numero
    	if(aux%2==0){ // se o valor do aux gerado pelo random anterior for PAR entra nessa condição
       		al.notas[i]=(((float)rand())/(float)RAND_MAX*3)+7; // atribuição para saber a nota do aluno, nessa condição a nota do aluno será necessariamente maior que 7
		}
		else{ // se o valor do aux gerado pelo random anterior for IMPAR entra nessa condição
			al.notas[i]=(((float)rand())/(float)RAND_MAX*5); // atribuição para saber a nota do aluno, nessa condição a nota do aluno será necessariamente menor que 7
		}
        md=md+al.notas[i]; // para somar as notas do aluno
    }
    strcpy(al.nome,name[(int)rand()%100]); // random para atruibuir o primeiro nome do aluno
    strcat(al.nome, " "); // usado para a concatenação do primeiro nome do aluno
    strcat(al.nome,midname[(int)rand()%26]); // random para atruibuir o nome do meio do aluno
    strcat(al.nome, " "); // usado para a concatenação do nome do meio do aluno
    strcat(al.nome,surname[(int)rand()%100]); // random para atruibuir o sobrenome do aluno
    al.media=md/al.qntNotas; // usado para calcular a media do aluno
    if((al.faltas<=18)&&(al.media>=7.0)){ // condição para saber se o aluno está aprovado, o nº de faltas deve ser menor que 18 e media maior que 7
      al.sitAc=1; // atribuição de que a situação do aluno é aprovado
    }
    else{
       if(al.faltas<=18) // condição que o aluno tem menos de 18 faltas e media menor que 7
            al.sitAc=2; // atribuição de que a situação do aluno é em exame
       else
           al.sitAc=0; // atribuição de que o aluno está reprovado 
    }
    aux=rand(); // random para gerar um valor para aux 
    aux2=rand(); // random para gerar um valor para aux2
    al.mat=abs(aux*aux2); // multiplicação dos valores de aux e aux2 para atribuir uma matricula para o aluno
    return al;
}

void writeByPag(int nPag){ // função para escrever por paginação
	FILE *arq = fopen(FNAME,"ab"); // abertuda do aquivo
    int x;
    Aluno *al,aux;
    al = (Aluno*)malloc(nPag*sizeof(Aluno));
    for(x=0;x<nPag;x++){ // for para colocar na variavel o registro do aluno, vai de 0 até um valor informado pelo usuario
        al[x]=returnRnd(); // atribuição do registro do aluno para a variavel
    }
    fwrite(al, sizeof(Aluno), nPag, arq); // escrita no arquivo por paginação, colocando todos os registros que estavam na variavel de uma vez
    fclose(arq); // fechamento do arquivo
}

void createByRegister(int nRegister){ // função para criar o numero de registro que o arquivo vai ter
    FILE *arq = fopen(FNAME,"ab"); // abertura do arquivo
    int x;
    for(x=nRegister;x>0;x--){
        Aluno al;
        al = returnRnd();
        fwrite(&al, sizeof(Aluno), 1, arq);
    }
    fclose(arq); // fechamento do arquivo
}

void createBySize(int tamArq){ // função para criar o arquivo de um determinado tamanho informado pelo usuario
    long int tamA;
    Aluno a;
    createByRegister(tamArq/sizeof(a));
    printf("%li Registro Criados!\n", tamArq/sizeof(a)); // mostrar o nº de registros criados
}

void readFileSequential(){ // função para ler o aquivo de forma sequencial
	FILE *arq = fopen(FNAME,"rb"); // abertura do arquivo
	Aluno al;
	int i,size=sizeof(Aluno);
	while(fread(&al,size,1,arq)==1){
		printf("Nome: %s\n",al.nome); // mostrar o nome do aluno
		printf("Matricula: %li\n",al.mat); // mpstrar a matricula do aluno
		printf("Qnt de Faltas: %i\nNotas: ",al.faltas); // mostrar a quantidade de faltas do aluno
		for(i=0;i<al.qntNotas;i++){ // for para mostrar todas as notas do aluno, vai de 0 até o nº de notas que o aluno tem
			printf("%.2f ",al.notas[i]); // mostrar as notas do aluno
		}
		printf("\nMedia: %.2f\n",al.media); // mostrar a media do aluno
		if(al.sitAc==1){ // condição para saber a situação do aluno
			printf("Situacao: Aprovado"); // mostrar que o aluno está aprovado
		}
		if(al.sitAc==2){
			printf("Situacao: Em Exame"); // mostrar que o aluno está em exame
		}
		if(al.sitAc==0){
			printf("Situacao: Reprovado"); // mostrar que o aluno está reprovado
		}
		printf("\n");
		system("pause");
		printf("\n\n");
	}
	fclose(arq); // fechamento do arquivo
}

int main(){
    int choise,tamA,nPag;
    clock_t begin,end;
    double ts;
    FILE *arq;
    srand((unsigned)time(NULL));
    do{ // menu do programa
        system("cls");
        printf("1--Inserir por Tamanho de Arquivo\n2--Inserir por Quantidade de Registro\n3--Leitura Sequencial\n");
        printf("4--Tamanho do Arquivo\n5--Ler Ultimo Registro\n6--Quantidade de Registros\n7--Escrita por Paginacao\n");
        printf("8--Leitura por Paginacao\n");
        printf("0--Sair\n-->");
        scanf("%i",&choise); // recebe o valor escolhido pelo usuario
        switch(choise){ 
            case 1: // opção para definir o tamanho do arquivo a ser criado
                system("cls");
                printf("Digite o tamanho do arquivo a ser criado em Mbytes: ");
                scanf("%i",&tamA); // recebe o tamanho do arquivo que o usuario definiu
                begin=clock(); // pega o horario que o programa começou a criar o arquivo
                createBySize((tamA*1024)*1024); // manda para a função o tamanho do arquivo
                end=clock(); // pega o horario que o programa terminou de criar o arquivo
                ts=(double)(end - begin)/CLOCKS_PER_SEC; // calcula quanto tempo levou para criar o arquivo
                printf("Tempo Decorrido:%.5lf ms\n",ts); // mostra o tempo que levou para criar o arquivo
                system("Pause");
                break;
            case 2: // opção para definir a quantidade de registro a ser criado
                system("cls");
                printf("Digite a quantidade de registros a ser criado: ");
                scanf("%i",&tamA); // recebe a quantidade de registro que o arquivo deve ter
                begin=clock(); // pega o horario que o programa começou a criar o arquivo
                createByRegister(tamA); // manda para a função a quantidade de registro que o arquivo deve ter
                end=clock(); // pega o horario que o programa terminou de criar o arquivo
                ts=(double)(end - begin)/CLOCKS_PER_SEC; // calcula quanto tempo levou para criar o arquivo
                printf("Tempo Decorrido:%.5lf ms\n",ts); // mostra o tempo que levou para criar o arquivo
                system("Pause");
                break;
            case 3: // opção para mostrar o arquivo na forma sequencial
                system("cls");
                readFileSequential(); 
                break;
            case 4: // opção para mostrar o tamanho do arquivo
                system("cls");
                arq=fopen(FNAME,"rb");
                printf("O tamanho do arquivo eh de %li em bytes, e %li em Mbytes\n",fileSize(arq), ((fileSize(arq))/1024)/1024);
                fclose(arq);
                system("Pause");
                break;
            case 5: // opção para mostrar o ultimo registro do arquivo
            	system("cls");
            	readLastOnFile();
            	break;
            case 6: // opção para mostrar a quantidade de registros do arquivo
            	printf("Quantidade de Registros no Arquivo: %li\n",HowManyRegisters());
            	system("pause");
            	break;
            case 7: // opção para escrever no aquivo por paginação
            	system("cls");
            	printf("Escrita por Paginacao\nQuantos registros devem ser escritos em uma pagina: ");
            	scanf("%i",&nPag); // recebe a quantidade de registros que devem ser escritos por paginação
            	begin=clock(); // pega o horario que o programa começou a criar o arquivo
				writeByPag(nPag); // manda para a função a quantidade de registros ser escritos por paginação
                end=clock(); // pega o horario que o programa terminou de criar o arquivo
                ts=(double)(end - begin)/CLOCKS_PER_SEC; // calcula quanto tempo levou para criar o arquivo
                printf("Tempo Decorrido:%.5lf ms\n",ts); // mostra o tempo que levou para criar o arquivo
                system("pause");
            	system("cls");
            	break;
            case 8: // opção para mostrar os registros por paginação
            	system("cls");
            	printf("Leitura por Paginacao\nQuantos registros devem ser lidos em uma pagina: ");
            	scanf("%i",&nPag); // recebe a quantidade de registro que devem ser mostrado em uma pagina
            	system("cls");
            	readByPag(nPag); // manda para a função a quantidade de registro que deve ter em uma pagina
            	break;
            case 0:
                break;
            default:
                break;
        }
    }while(choise!=0);
    return 1;
}
