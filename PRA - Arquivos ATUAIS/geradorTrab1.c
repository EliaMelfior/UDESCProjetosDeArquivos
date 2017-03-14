#include <stdio.h>
#include <stdlib.h
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct aluno{
        char nome[30];
        long mat;
        float *notas;
        int faltas;
        float media;
        int sitAc;
}Aluno;

int main(){
        srand((unsigned)time(NULL));
        int x,aux,aux2,i;
        float md;
        Aluno al;
        long int tamA;
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
     do{
          FILE *arq = fopen("arq.bin","ab");
          for(x=5000000;x>=0;x--){
              md=0;
              al.faltas=rand()%20;
              aux=rand()%10+1;
              al.notas = (float *)malloc(aux*sizeof(float));
              for(i=0;i<aux;i++){
                  al.notas[i]=((float)rand())/(float)RAND_MAX*10;
                  md=md+al.notas[i];
              }
              strcpy(al.nome,name[(int)rand()%100]);
              strcat(al.nome, " ");
              strcat(al.nome,midname[(int)rand()%26]);
              strcat(al.nome, " ");
              strcat(al.nome,surname[(int)rand()%100]);
              al.media=md/aux;
              if((al.faltas<=18)&&(al.media>=7.0)){
                  al.sitAc=1;
              }
              else{
                   al.sitAc=0;
              }
              aux=rand();
              aux2=rand();
              al.mat=abs(aux*aux2);
              fwrite(&al, sizeof(Aluno), 1, arq);
          }
          fclose(arq);
          FILE *fpp=fopen("arq.bin","rb");
          fseek(fpp, 0, SEEK_END);
          tamA = ftell(fpp)/1024;
          fclose(fpp);
      }while(tamA<1000000);
      system("pause");
}



