#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int codigo;
    char *nome;
    bool alugado;
}tipoItem;

typedef struct no *apontador;

struct no {
  tipoItem filme;
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
     (*p)->filme = x;
     (*p)->filme.alugado = false;
     (*p)->esq = NULL;
     (*p)->dir = NULL;
  }
  else if(x.codigo == (*p)->filme.codigo)
  {
    printf("codigo já registrado");
    printf("\n\nPressione [algo] para prosseguir.");
    getch();

  }
  else if (x.codigo < (*p)->filme.codigo) insere(x, &((*p)->esq));
       else insere(x, &((*p)->dir));
}

void inserirNos(apontador *arvore){
    tipoItem x;
    cls();
    printf("Digite o codigo:");
    scanf("%d",&x.codigo);
    printf("Digite o nome filme:");
    x.nome = recebeString(x.nome);
    insere(x, arvore);
}

void visitaRaiz(apontador no, int parametro,bool *imprimiu){
  bool imprimi = false;
  if(parametro == 1 && !no->filme.alugado)
  {
      printf("Nome: %s\n", no->filme.nome);
      printf("Codigo: %d\n", no->filme.codigo);
      imprimi = true;
  }
  else if(parametro == 2 && no->filme.alugado)
  {
      printf("Nome: %s\n", no->filme.nome);
      printf("Codigo: %d\n", no->filme.codigo);
      imprimi = true;
  }
  else  if(parametro == 3)
  {
      printf("Nome: %s\n", no->filme.nome);
      printf("Codigo: %d\n", no->filme.codigo);
      if(no->filme.alugado) printf("Status: indisponivel\n");
      else printf("Status: disponivel\n");
      imprimi = true;
  }
  if(imprimi)
  {
    *imprimiu = true;
    int x;
    for(x=0;x<73;x++){
      printf("-");
    }
    printf("\n");
  }
}

void em_ordem(apontador p, int parametro, bool *imprimiu){
  if (p != NULL) {
     em_ordem(p->esq,parametro,imprimiu);
     visitaRaiz(p,parametro,imprimiu);
     em_ordem(p->dir,parametro,imprimiu);
  }
}

void antecessor(apontador q, apontador *r){
  if ((*r)->dir != NULL)
     antecessor(q, &((*r)->dir));
  else{
     q->filme = (*r)->filme;
     q = *r;
     *r = (*r)->esq;
     free(q);
  }
}

void retira(tipoItem x, apontador *p, int *operacao){
  apontador aux;
  if ((*p) == NULL)
     *operacao = 0;
  else if(x.codigo == (*p)->filme.codigo){
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
  else if (x.codigo < (*p)->filme.codigo) retira(x, (&(*p)->esq), operacao);
  else retira(x, (&(*p)->dir), operacao);
}

void removerNos(apontador *arvore){
  tipoItem x;
  int operacao;
  cls();
  printf("Digite o codigo:");
  scanf("%d",&x.codigo);
  retira(x, arvore, &operacao);

  if (operacao == 1)printf("\n\nItem removido.");
  else printf("\n\nRegistro nao encontrado.");
  
  printf("\n\nPressione [algo] para prosseguir.");
  getch();
}

void buscaFilme(apontador *raiz, bool *achou, int codigo){
  if((*raiz)==NULL) *achou = false;
  else if(codigo == (*raiz)->filme.codigo ){
    printf("Nome: %s\n", (*raiz)->filme.nome);
    printf("Codigo: %d\n", (*raiz)->filme.codigo);
    if((*raiz)->filme.alugado) printf("Status: indisponivel\n");
    else printf("Status: disponivel\n");
    *achou = true;
  }
  else if(codigo < (*raiz)->filme.codigo) buscaFilme((&(*raiz)->esq),achou,codigo);
  else buscaFilme((&(*raiz)->dir),achou,codigo);
}

void pesquisaLocadora(apontador *raiz){
  int codigo;
  bool achou;
  cls();
  printf("Digite o codigo para ser procurado:");
  scanf("%d",&codigo);

  buscaFilme(raiz,&achou,codigo);

  if(!achou)printf("\n\nPlaca nao encontrada");
  
  printf("\n\nPressione qualquer tecla para prosseguir.");
  fflush(stdin);
  getch();
}

void alugar(apontador *p, bool *achou, int codigo)
{
  if((*p)==NULL) *achou = false;
  else if(codigo == (*p)->filme.codigo ){
    if((*p)->filme.alugado)
    {
      printf("filme já alugado");
      printf("\n\nPressione qualquer tecla para prosseguir.");
      fflush(stdin);
      getch();
    }
    else
    {
      printf("Nome: %s\n", (*p)->filme.nome);
      printf("Codigo: %d\n", (*p)->filme.codigo);
      
      printf("Esse e o filme que deseja alugar?[y/n]");
      char c = getch();
      if(c=='y' || c=='Y')(*p)->filme.alugado = true;
      *achou = true;
    }
  }
  else if(codigo < (*p)->filme.codigo) buscaFilme((&(*p)->esq),achou,codigo);
  else buscaFilme((&(*p)->dir),achou,codigo);
}

void Filme(apontador *raiz)
{
  int codigo;
  bool achou;
  cls();
  printf("Digite o codigo do filme que deseja alugar:");
  scanf("%d",&codigo);

  alugar(raiz , &achou, codigo);
}