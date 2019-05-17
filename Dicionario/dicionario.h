/***********************************************************************
Instituto Federal de Educação, Ciência e Tecnologia do Ceará - IFCE
Nome: Isaac Gondim Geraldo
Turma: P6 Informática           Semestre: 2019.1
Diciplina: Estrutura de dados   Professor: Ernani Leite

Descrição: Implementação de biblioteca para manipulação de arvores em C
***********************************************************************/

// DECLARAÇÃO DE BIBLIOTECAS *******************************************
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>

// DECLARAÇÃO DAS ESTRUTURAS *******************************************

typedef struct
{
    char *palavra;
    char *significado;
}conteudo;

typedef struct notype *No;

struct notype
{
    conteudo vocabulo;
    No direita;
    No esquerda;
    int contador;
    int fb;
};

// DECLARAÇÕES AUXILIARES **********************************************

char *recebeString(char *string)
{
    int c,i=0;
    string = (char *)malloc(0);
    fflush(stdin);

    while((c = getchar()) != '\n')
    {
        i++;
        string = (char *)realloc(string,i*sizeof(char));

        if(string == NULL)
        {
            printf("MEMORIA INSUFICIENTE");
            exit(1);
        }
        string[i-1] = c;
    }

    string = (char *)realloc(string,(i+1)*sizeof(char));

    if(string == NULL)
    {
        printf("MEMORIA INSUFICIENTE");
        exit(1);
    }

    string[i] = '\0';

    return string;
}

//----------------------------------------------------------------------

void gotoxy(int x, int y)//OK
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//----------------------------------------------------------------------

void insere(conteudo vocabulo, No *atual, bool *cresceu)
{
    No aux1,aux2;
    if((*atual) == NULL)
    {
        *atual = (struct notype *)malloc(sizeof(struct notype));
        cresceu = true;
        (*atual)->vocabulo = vocabulo;
        (*atual)->contador = 1;
        (*atual)->direita = NULL;
        (*atual)->esquerda = NULL;
        (*atual)->fb = 0;
    }
    else if (vocabulo.palavra[0] < (*atual)->vocabulo.palavra[0])
    {
        insere(vocabulo, &((*atual)->esquerda), cresceu);
        if(cresceu)
        {
            switch((*atual)->fb)
            {
                case -1:
                    (*atual)->fb = 0;
                    cresceu = false;
                    break;

                case 0:
                    (*atual)->fb = +1;
                    break;

                case +1:
                    aux1 = (*atual)->esquerda;
                    if(aux1->fb == +1) //ROTAÇÃO LL
                    {
                        (*atual)->esquerda = aux1->direita;
                        aux1->direita = (*atual);
                        (*atual)->fb = 0;
                        (*atual) = aux1;
                    }
                    else //ROTAÇÃO LR
                    {
                        aux2 = aux1->direita;
                        aux1->direita = aux2->esquerda;
                        aux2->direita = aux1;
                        (*atual)->esquerda = aux2->direita;
                        aux2->direita = (*atual);
                        if(aux2->fb == +1) (*atual)->fb = -1;
                        else (*atual)->fb = 0;
                        if(aux2->fb == -1) aux1->fb = +1;
                        else aux1->fb = 0;
                        (*atual) = aux2;
                    }
                    (*atual)->fb = 0;
                    cresceu = false;
            }
        }
    }
    else /*if(vocabulo.palavra[0] > (*atual)->vocabulo.palavra[0])*/
    {
        insere(vocabulo, &((*atual)->direita), cresceu);
        if(cresceu)
        {
            switch((*atual)->fb)
            {
                case +1:
                    (*atual)->fb =0;
                    cresceu = false;
                    break;

                case 0:
                    (*atual)->fb = -1;
                    break;

                case -1:
                    aux1 = (*atual)->direita;
                    if(aux1->fb == -1)// ROTAÇÃO RR
                    {
                        (*atual)->direita = aux1->esquerda;
                        aux1->esquerda = (*atual);
                        (*atual)->fb = 0;
                        (*atual) = aux1;
                    }
                    else//ROTAÇÃO RL
                    {
                        aux2 = aux1->esquerda;
                        aux1->esquerda = aux2->direita;
                        aux2->direita = aux1;
                        (*atual)->direita = aux2->esquerda;
                        aux2->esquerda = (*atual);
                        if(aux2->fb == -1) (*atual)->fb = +1;
                        else (*atual)->fb = 0;
                        if(aux2->fb == +1) aux1->fb = -1;
                        else aux1->fb = 0;
                        (*atual) = aux2;
                    }
                    (*atual)->fb = 0;
                    cresceu = false;
            }
        }
    }
    //else (*atual)->contador++;
}

//----------------------------------------------------------------------

void insereNo(No *dicionario)
{
    conteudo vocabulo;
    bool *mudou = false;
    system("cls");
    printf("ESCREVA A PALAVRA A SER ADICIONADA:");
    vocabulo.palavra = recebeString(vocabulo.palavra);
    printf("DIGITE O SIGNIFICADO DA PALAVRA:");
    vocabulo.significado = recebeString(vocabulo.significado);

    insere(vocabulo, dicionario, mudou);
}

//----------------------------------------------------------------------

void balanceiaesquerda( No *atual, bool diminuiu)
{
    No aux1,aux2;
    int fb1, fb2;

    switch((*atual)->fb)
    {
        case +1:
            (*atual)->fb = 0;
            break;

        case 0:
            (*atual)->fb = -1;
            diminuiu = false;
            break;

        case -1:
            aux1 = (*atual)->direita;
            fb1 = aux1->fb;
            if(fb1 <= 0)//ROTAÇÃO RR
            {
                (*atual)->direita = aux1->esquerda;
                aux1->esquerda = (*atual);
                if(fb1 == 0)
                {
                    (*atual)->fb = -1;
                    aux1->fb = +1;
                    diminuiu = false;
                }
                else
                {
                    (*atual)->fb = 0;
                    aux1->fb = 0;
                }
                (*atual) = aux1;
            }
            else //ROTAÇÃO RL
            {
                aux2 = aux1->esquerda;
                fb2 = aux2->fb;
                aux1->esquerda = aux2->direita;
                aux2->direita = aux1;
                (*atual)->direita = aux2->esquerda;
                aux2->esquerda = (*atual);
                if(fb2 == -1) (*atual)->fb = +1;
                else (*atual)->fb = 0;
                if(fb2 == +1) aux1->fb = -1;
                else aux1->fb = 0;
                (*atual) = aux2;
                aux2->fb = 0;
            }
    }
}

//----------------------------------------------------------------------

void balanceiadireita(No *atual, bool diminuiu)
{
    No aux1,aux2;
    int fb1,fb2;

    switch((*atual)->fb)
    {
        case -1:
            (*atual)->fb = 0;
            break;

        case 0:
            (*atual)->fb = +1;
            diminuiu = false;
            break;

        case +1:
            aux1 = (*atual)->esquerda;
            fb1 = aux1->fb;
            if(fb1 >= 0)//ROTAÇÃO LL
            {
                (*atual)->esquerda = aux1->direita;
                aux1->direita = (*atual);
                if(fb1 == 0)
                {
                    (*atual)->fb = +1;
                    aux1->fb = -1;
                    diminuiu = false;
                }
                else
                {
                    (*atual)->fb = 0;
                    aux1->fb = 0;
                }
                (*atual) = aux1;
            }
            else// ROTAÇÃO LR
                {
                    aux2 = aux1->direita;
                    fb2 = aux2->fb;
                    aux1->direita = aux2->esquerda;
                    aux2->esquerda = aux1;
                    (*atual)->esquerda = aux2->direita;
                    aux2->direita = (*atual);
                    if(fb2 == +1) (*atual)->fb = -1;
                    else (*atual)->fb = 0;
                    if(fb2 == -1) aux1->fb = +1;
                    else aux1->fb = 0;
                    (*atual) = aux2;
                    aux2->fb = 0;
                }
    }
}

//----------------------------------------------------------------------

void deletemim(No *q, No *r, bool *h)
{
    if((*r)->esquerda != NULL)
    {
        deletemim(&(*q), &((*r)->esquerda), h);
        if(h) balanceiaesquerda(&(*r),h);
    }
    else
    {
        strcpy((*r)->vocabulo.palavra, (*q)->vocabulo.palavra);
        strcpy((*r)->vocabulo.significado, (*q)->vocabulo.significado);
        (*q)->contador = (*r)->contador;
        (*q) = (*r);
        (*r) = (*r)->direita;
        h = true;
    }
}

//----------------------------------------------------------------------

void Delete(conteudo vocabulo, No *atual, bool *h)
{
    No q;
    if((*atual) == NULL)
    {
        printf("PALAVRA NAO ENCONTRADA");
        abort();
    }
    else if(strcmp(vocabulo.palavra, (*atual)->vocabulo.palavra) == 0)
    {
        q = (*atual);
        if (q->direita == NULL)
        {
            (*atual) = q->esquerda;
            h = true;
        }
        else if(q->esquerda == NULL)
        {
            (*atual) = q->direita;
            h = true;
        }
        else
        {
            deletemim(&q,&(q->direita), h);
            if(h) balanceiadireita(&q,h);
        }
        free(q);
    }
    else if(vocabulo.palavra[0] < (*atual)->vocabulo.palavra[0])
    {
        Delete(vocabulo, &((*atual)->esquerda), h);
        if(h) balanceiaesquerda(&(*atual),h);
    }
    else
    {
        Delete(vocabulo, &((*atual)->direita), h);
        if(h) balanceiadireita(&q,h);
    }
}

//----------------------------------------------------------------------

void buscaDelete(No *dicionario)
{
    conteudo vocabulo;
    bool *mudou = false;
    system("cls");
    printf("ESCREVA A PALAVRA A SER APAGADA:");
    vocabulo.palavra = recebeString(vocabulo.palavra);
    
    Delete(vocabulo, dicionario, mudou);
}

//----------------------------------------------------------------------

void visitaRaiz(No no)
{
  printf("PALAVRA: %s\n\n",no->vocabulo.palavra);
  printf("SIGNIFICADO: %s \n", no->vocabulo.significado);
  int x;
  for(x=0;x<73;x++)
  {
    printf("-");
  }
  printf("\n");
}

//----------------------------------------------------------------------

void em_ordem(No p)
{
  if (p != NULL) {
     em_ordem(p->esquerda);
     visitaRaiz(p);
     em_ordem(p->direita);
  }
}

//----------------------------------------------------------------------

void buscaPalavra(No *atual, bool *achou, char *palavra)
{
  if((*atual)==NULL) *achou = false;
  else if(strcmp((*atual)->vocabulo.palavra,palavra)==0)
  {
    printf("PALAVRA: %s\n\n",(*atual)->vocabulo.palavra);
  printf("SIGNIFICADO: %s \n", (*atual)->vocabulo.significado);
    *achou = true;
  }
  else if(palavra[0] < (*atual)->vocabulo.palavra[0] ) buscaPalavra((&(*atual)->esquerda), achou, palavra);
  else if(palavra[0] >= (*atual)->vocabulo.palavra[0] ) buscaPalavra((&(*atual)->direita), achou, palavra);
}

//----------------------------------------------------------------------

void pesquisaDicionario(No *atual)
{
  bool achou=false;
  system("cls");
  printf("DIGITE A PALAVRA A SER PROCURADA:");
  char *palavra = recebeString(palavra);
  buscaPalavra(atual,&achou,palavra);

  if(!achou)
  {
    printf("\n\nPALAVRA NAO ENCONTRADA");
  }
}