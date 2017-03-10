#include <stdio.h>
#include <stdlib.h>
#define ordem 100000
typedef int TipoChave;

const T = 2,
	MAX_CHAVES = 3, //quantidade máxima de chaves 2*T-1
	MAX_FILHOS = 4, //quantidade máxima de filhos 2*T
	MIN_OCUP = 1; //ocupação mínima em cada nó T-1
	
typedef struct _No Arvore;

struct _No{
	int numChaves;
	TipoChave chaves[ordem];
	struct _No * filhos[ordem + 1];
};

void insere_chave(Arvore *raiz, int temperatura, Arvore *filhodir){
	int k, pos;
	//Obtem o endereço para inserção da nova chave
	pos = busca_binaria(raiz, temperatura);
	k = raiz->numChaves;
	//libera espaço para inserção da chave na página
	while(k > pos & temperatura < raiz->chaves[k-1]){
		raiz->chaves[k] = raiz->chaves[k-1];
		raiz->filhos[k+1] = raiz->filhos[k];
		k--;
	}
	//insere a chave
	raiz->chaves[pos] = temperatura;
	raiz->filhos[k+1] = filhodir;
	raiz->numChaves++;
}

Arvore* insere(Arvore *raiz, int temperatura, char *h, int *temperatura_retorno){
	int i, j, pos, temperatura_mediano;
	Arvore *temp, *filhodir;
	if(!raiz){
		*h = 1; //atingiu nó folha
		*temperatura_retorno = temperatura;
		return NULL;
	} else {
		pos = busca_binaria(raiz, temperatura);
		if(raiz->numChaves > pos && raiz->chaves[pos] == temperatura){
			printf("Chave ja contida na arvore");
			*h = 0;
		} else {
			filhodir = insere(raiz->filhos[pos], temperatura, h, temperatura_retorno);
			if(*h){
				if(raiz->numChaves < MAX_CHAVES) {
					insere_chave(raiz, *temperatura_retorno, filhodir);
					*h = 0;
				} else { //split and promote
					temp = (Arvore*) malloc(sizeof(Arvore));
					temp->numChaves = 0;
					for(i=0; i<MAX_FILHOS; i++)
						temp->filhos[i] = NULL;
					temperatura_mediano = raiz->chaves[MIN_OCUP]; //promote
					//insere metade da página no temp - split
					temp->filhos[0] = raiz->filhos[MIN_OCUP + 1];
					for(i=MIN_OCUP+1; i<MAX_CHAVES; i++)
						insere_chave(temp, raiz->chaves[i], raiz->filhos[i+1]);
					//atualiza raiz
					for(i=MIN_OCUP; i<MAX_CHAVES; i++){
						raiz->chaves[i] = 0;
						raiz->filhos[i+1] = NULL;
					}
					raiz->numChaves = MIN_OCUP;
					//verifica onde inserir a nova chave
					if(pos<= MIN_OCUP)
						insere_chave(raiz, *temperatura_retorno, filhodir);
					else
						insere_chave(temp, *temperatura_retorno, filhodir);
					*temperatura_retorno = temperatura_mediano;
					return temp;
				}
			}
		}
	}
}

Arvore* insere_arvore(Arvore *raiz, int temperatura) {
	char h;
	int temperatura_retorno, i;
	Arvore *filhodir, *novaraiz;
	
	filhodir = insere(raiz, temperatura, &h, &temperatura_retorno);
	if(h == 1){ //precisa aumentar a altura da arvore
		novaraiz = (Arvore*) malloc(sizeof(Arvore));
		novaraiz->numChaves = 1;
		novaraiz->chaves[0] = temperatura_retorno;
		novaraiz->filhos[0] = raiz;
		novaraiz->filhos[1] = filhodir;
		for(i=2; i<=MAX_CHAVES; i++)
			novaraiz->filhos[i] = NULL;
		return novaraiz;
	}
	return raiz;
}

int busca_binaria(Arvore *no, int temperatura){
	int meio, i=0, f = no->numChaves - 1;
	while(i <= f){
		if(no->chaves[meio] == temperatura)
			return meio; //encontrou a posição da chave procurada
		else if(no->chaves[meio] > temperatura)
			f = meio - 1;
		else
			i = meio + 1;
	}
	return i; //não encontrou
}

Arvore* busca(Arvore *raiz, int temperatura){
	Arvore *no;
	int pos;
	no = raiz;
	while(no){
		pos = busca_binaria(no, temperatura);
		if(pos < no->numChaves && no->chaves[pos] == temperatura)
			return no;
		else
			no = no->filhos[pos];
	}
	return NULL;
}

void em_ordem(Arvore *raiz){
	int i;
	
	if(raiz) {
		for(i=0; i<raiz->numChaves; i++){
			em_ordem(raiz->filhos[i]);
			printf("\n%d", raiz->chaves[i]);
		}
		em_ordem(raiz->filhos[i]);
	}
}

/*------------------------------------------- MÉTODOS PARA REMOÇÃO -----------------------------------------*/

char encontra_chave(int temperatura, Arvore *p, int *k)
{
	if (temperatura < p->chaves[1]) {  
		*k = 0;
		return 0;
	} 
	else {
		*k = p->numChaves;
		while ((temperatura < p->chaves[*k]) && *k > 1){
			(*k)--;
		}
		if(temperatura == p->chaves[*k])
			return 1;
		return 0;
	}
}




void move_direita(Arvore *p, int k)
{
	int c;
	Arvore *t;

	t = p->filhos[k];
	for (c=t->numChaves; c>0; c--){
		t->chaves[c+1]=t->chaves[c];
		t->filhos[c+1]=t->filhos[c];
	}
	t->filhos[1] = t->filhos[0];
	t->numChaves++;
	t->chaves[1] = p->chaves[k];
	t = p->filhos[k-1];
	p->chaves[k] = t->chaves[t->numChaves];

	p->filhos[k]->filhos[0] = t->filhos[t->numChaves];
	t->numChaves--;
}


void move_esquerda(Arvore *p, int k)
{
	int c;
	Arvore *t;

	t = p->filhos[k-1];
	t->numChaves++;
	t->chaves[t->numChaves] = p->chaves[k];
	t->filhos[t->numChaves] = p->filhos[k]->filhos[0];

	t = p->filhos[k];
	p->chaves[k] = t->chaves[1];
	t->filhos[0] = t->filhos[1];
	t->numChaves--;
	for (c=1; c<=t->numChaves; c++){
		t->chaves[c] = t->chaves[c+1];
		t->filhos[c] = t->filhos[c+1];
	}
}

void combina(Arvore *p, int k)
{
	int c;
	Arvore *q; 
	Arvore *l;

	q = p->filhos[k];
	l = p->filhos[k-1];
	l->numChaves++;
	l->chaves[l->numChaves] = p->chaves[k];
	l->filhos[l->numChaves] = q->filhos[0];
	for (c=1; c<=q->numChaves; c++){
		l->numChaves++;
		l->chaves[l->numChaves] = q->chaves[c];
		l->filhos[l->numChaves] = q->filhos[c];
	}
	for (c=k; c<p->numChaves; c++){
		p->chaves[c] = p->chaves[c+1];
		p->filhos[c] = p->filhos[c+1];
	}
	p->numChaves--;
	free(q);
}


void restaura(Arvore *p, int k)
{
	if (k == 0)                /* case: leftmost key */
		if (p->filhos[1]->numChaves > MIN_OCUP)
			move_direita(p, 1);
		else
			combina(p, 1);
  	else if (k == p->numChaves)    /* case: rightmost key */
    	if (p->filhos[k-1]->numChaves > MIN_OCUP)
			move_direita(p, k);
    	else
			combina(p, k);
	else if (p->filhos[k-1]->numChaves > MIN_OCUP) /*remaining cases */
		move_direita(p, k);
	else if (p->filhos[k+1]->numChaves > MIN_OCUP)
		move_esquerda(p, k+1);
	else 
		combina(p, k);
}


void remove_a(Arvore *p, int k)
{
	int i;
	for (i=k+1; i<=p->numChaves; i++){
		p->chaves[i-1] = p->chaves[i];
		p->filhos[i-1] = p->filhos[i];
	}
	p->numChaves--;
}


void sucessor(Arvore *p, int k)
{
	Arvore *q;
	for (q=p->filhos[k]; q->filhos[0]; q=q->filhos[0]);
	p->chaves[k] = q->chaves[1];
}


char remove_recursiva(int temperatura, Arvore *p)
{
	int k;
	char encontrado;

	if (p == NULL)
		return 0;
	else{
		encontrado = encontra_chave(temperatura, p, &k);
		if (encontrado)
			if (p->filhos[k-1]){
				sucessor(p, k);
				if (!(encontrado = remove_recursiva(p->chaves[k], p->filhos[k])))
					printf("Chave nao encontrada na arvore.");
			}else
				remove_a(p, k);
		else
           encontrado=remove_recursiva(temperatura, p->filhos[k]);
           
		if (p->filhos[k] != NULL)
			if (p->filhos[k]->numChaves < MIN_OCUP)
				restaura(p, k);
		return encontrado;
	}
}


Arvore* remove_arvore(Arvore *raiz, int temperatura) {
	Arvore *p,*t;
	
	t = raiz;
	if (remove_recursiva(temperatura, t) == 0)
		printf("Chave nao encontrada na arvore.");
	else 
		if (raiz->numChaves == 0) {
			p = raiz;
			raiz = raiz->filhos[0];
			free(p);
		}
	return raiz;
}