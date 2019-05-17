#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
  char *placa;
  char *proprietario;
}tipoItem;

typedef struct no *apontador;

struct no {
  tipoItem item;
  apontador esq;
  apontador dir;
};

char *recebeString(char *string){
    int c,i=0;
    string = (char *)malloc(0);
    fflush(stdin);
    while((c = getchar()) != '\n'){
        i++;
        string = (char *)realloc(string,i*sizeof(char));
        if(string == NULL){
            printf("MEMORIA INSUFICIENTE");
            exit(1);
        }
        string[i-1] = c;
    }
    string = (char *)realloc(string,(i+1)*sizeof(char));
    if(string == NULL){
        printf("MEMORIA INSUFICIENTE");
        exit(1);
    }
    string[i] = '\0';
    return string;
}

void cls(void){
    COORD coordScreen = {0, 0}; 
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; 
    DWORD dwConSize; 
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
     GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void insere(tipoItem x, apontador *p){
  if ((*p) == NULL) {
     *p = (apontador) malloc(sizeof(struct no));
     (*p)->item = x;
     (*p)->esq = NULL;
     (*p)->dir = NULL;
  }
  else if (x.placa[0] < (*p)->item.placa[0])
	  insere(x, &((*p)->esq));
       else insere(x, &((*p)->dir));
}

void insereD(tipoItem x, apontador *p){
  if ((*p) == NULL) {
     *p = (apontador) malloc(sizeof(struct no));
     (*p)->item = x;
     (*p)->esq = NULL;
     (*p)->dir = NULL;
  }
  else if (x.proprietario[0] < (*p)->item.proprietario[0])
	  insereD(x, &((*p)->esq));
       else insereD(x, &((*p)->dir));
}

void inserirNos(apontador *placas, apontador *donos){
  tipoItem x;
    cls();
    printf("Digite a placa:");
    x.placa = recebeString(x.placa);
    printf("Digite o nome do proprietario:");
    x.proprietario = recebeString(x.proprietario);
    insereD(x,donos);
    insere(x, placas);
}

void visitaRaiz(apontador no){
  printf("PROPRIETARIO: %s\n",no->item.proprietario);
  printf("PLACA: %s \n", no->item.placa);
  int x;
  for(x=0;x<73;x++){
    printf("-");
  }
  printf("\n");
}

void em_ordem(apontador p){
  if (p != NULL) {
     em_ordem(p->esq);
     visitaRaiz(p);
     em_ordem(p->dir);
  }
}

void antecessor(apontador q, apontador *r){
  if ((*r)->dir != NULL)
     antecessor(q, &((*r)->dir));
  else{
     q->item = (*r)->item;
     q = *r;
     *r = (*r)->esq;
     free(q);
  }
}

void retira(tipoItem x, apontador *p, int *operacao){
  apontador aux;
  if ((*p) == NULL)
     *operacao = 0;
  else if (x.placa[0] < (*p)->item.placa[0]) retira(x, (&(*p)->esq), operacao);
  else if (x.placa[0] > (*p)->item.placa[0]) retira(x, (&(*p)->dir), operacao);
  else{
    *operacao = 1;
    if ((*p)->dir == NULL){
      aux = *p;
      *p = (*p)->esq;
      free(aux);
    }
    else if ((*p)->esq == NULL){
      aux = *p;
      *p = (*p)->dir;
      free(aux);
    }
    else antecessor((*p), (&(*p)->esq));
  }
}

void removerNos(apontador *placas, apontador *donos){
  tipoItem x;
  int operacao;
  cls();
  printf("Digite a placa do carro a ser apagado:\n");
  fflush(stdin);
  x.placa = recebeString(x.placa);
  retira(x, placas, &operacao);
  retira(x, donos, &operacao);
  if (operacao == 1)printf("\n\nItem removido.");
  else printf("\n\nRegistro nao encontrado.");
  printf("\n\nPressione [algo] para prosseguir.");
  getch();
}

void buscaPlaca(apontador *raiz, bool *achou, char *placa){
  if((*raiz)==NULL) *achou = false;
  else if(strcmp((*raiz)->item.placa,placa)==0){
    printf("Proprietario: %s\n",(*raiz)->item.proprietario);
    printf("Placa: %s \n", (*raiz)->item.placa);
    *achou = true;
  }
  else if(placa[0] < (*raiz)->item.placa[0]) buscaPlaca((&(*raiz)->esq),achou,placa);
  else if(placa[0] >= (*raiz)->item.placa[0]) buscaPlaca((&(*raiz)->dir),achou,placa);
}

void pesquisaPlaca(apontador *raiz){
  bool achou;
  cls();
  printf("Digite a placa para ser procurada:");
  char *placa = recebeString(placa);
  buscaPlaca(raiz,&achou,placa);
  if(!achou)printf("\n\nPlaca nao encontrada");
  printf("\n\nPressione qualquer tecla para prosseguir.");
  fflush(stdin);
  getch();
}


void buscaProprietario(apontador *raiz, bool *achou, char *proprietario){
  if((*raiz)==NULL) *achou = false;
  else if(strcmp((*raiz)->item.proprietario,proprietario)==0){
    printf("Proprietario: %s\n",(*raiz)->item.proprietario);
    printf("Placa: %s \n", (*raiz)->item.placa);
    *achou = true;
  }
  else if(proprietario[0] < (*raiz)->item.proprietario[0] ) buscaProprietario((&(*raiz)->esq),achou,proprietario);
  else if(proprietario[0] >= (*raiz)->item.proprietario[0] ) buscaProprietario((&(*raiz)->dir),achou,proprietario);
}

void pesquisaProprietario(apontador *raiz){
  bool achou=false;
  cls();
  printf("Digite o proprietario para ser procurada:");
  char *proprietario = recebeString(proprietario);
  buscaProprietario(raiz,&achou,proprietario);
  if(!achou) printf("\n\nProprietario nao encontrada");
  printf("\n\nPressione qualquer tecla para prosseguir.");
  fflush(stdin);
  getch();
}