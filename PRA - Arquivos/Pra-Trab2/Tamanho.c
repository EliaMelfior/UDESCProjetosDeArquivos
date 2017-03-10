#include <time.h> /* para calcular data e duracao */
#include <sys/time.h> /* para duracao */
#include <stdio.h>
#include <string.h>/* para limpar a tela durante os menus */
#define FILENAME "RelatoriosClimaticos.bin"
#define NUMERODEBLOCOS 2271282
#define NUMERODEBLOCOSGERAR 873813
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

typedef struct RelatorioClimatico
{ 
        char nomeLocal [50]; 
        struct tm dataColeta;
        int temperatura; 
    
}RelatorioClimatico; 

int main(void)
{
    RelatorioClimatico TesteTamanho;
    int TesteTamanhoInt;
    
    printf("%i, %i", sizeof(TesteTamanho), sizeof(TesteTamanhoInt));
    
}