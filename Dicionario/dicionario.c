#include <stdio.h>
#include "dicionario.h"
#include <stdlib.h>
#include <conio.h>

void main()
{
    No dicionario = NULL;
    int opcao;

    do {
        system("cls");
        int coluna=2,linha=2;

        gotoxy(coluna,linha++);printf("             *** MENU PRINCIPAL ***             ");
        gotoxy(coluna,linha++);printf("________________________________________________");
        gotoxy(coluna,linha++);printf("| 1) ADICIONAR PALAVRA                          |");
        gotoxy(coluna,linha++);printf("| 2) REMOVER PALAVRA                            |");
        gotoxy(coluna,linha++);printf("| 3) IMPRIMER PALAVRAS EM ORDREM ALFABETICA     |");
        gotoxy(coluna,linha++);printf("| 4) REALIZAR BUSCA POR UMA PALAVRA             |");
        gotoxy(coluna,linha++);printf("|                                               |");
        gotoxy(coluna,linha++);printf("| 0) SAIR                                       |");
        gotoxy(coluna,linha++);printf("| [?] OPCAO DESEJADA                            |");
        gotoxy(coluna,linha);  printf("|_______________________________________________|");
        fflush(stdin);
        gotoxy((coluna+3),(linha-1));scanf("%d",&opcao);

        switch(opcao) 
        {
        case 0: break;
        case 1: insereNo(&dicionario); break;
        case 2: buscaDelete(&dicionario); break;
        
        case 3:
            system("cls");
            em_ordem(dicionario);
            printf("\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR");
            fflush(stdin);
            getch();
            break;

        case 4:
            pesquisaDicionario(&dicionario);
            printf("\n\nPRESSIONE QUALQUER TECLA PARA CONTINUAR");
            fflush(stdin);
            getch();
            break;

        default:
            gotoxy(coluna,linha+3);printf("   *** OPCAO INVALIDA   ***");
            Sleep(2000);
            break;
        }
    } while (opcao != 0);
}