#include <stdio.h>
#include "locadora.h"
#include <stdlib.h>
#include <conio.h>

void main()
{
    apontador locadora = NULL;
    int opcao;
    bool imprimiu=false;

    do {
        system("cls");
        int coluna=2,linha=2;

        gotoxy(coluna,linha++);printf("             *** MENU PRINCIPAL ***             ");
        gotoxy(coluna,linha++);printf("________________________________________________");
        gotoxy(coluna,linha++);printf("| 1) ADICIONAR FILME                            |");
        gotoxy(coluna,linha++);printf("| 2) REMOVER FILME                              |");
        gotoxy(coluna,linha++);printf("| 3) ALUGAR UM FILME                            |");
        gotoxy(coluna,linha++);printf("| 4) DEVOLVER UM FILME                          |");
        gotoxy(coluna,linha++);printf("| 5) IMPRIMIR FILMES DISPONIVEIS                |");
        gotoxy(coluna,linha++);printf("| 6) IMPRIMIR FILMES ALUGADOS                   |");
        gotoxy(coluna,linha++);printf("| 7) IMPRIMIR TODOS OS FILMES                   |");
        gotoxy(coluna,linha++);printf("| 8) PROCURAR PO UM FILME                       |");
        gotoxy(coluna,linha++);printf("|                                               |");
        gotoxy(coluna,linha++);printf("| 0) SAIR                                       |");
        gotoxy(coluna,linha++);printf("| [?] OPCAO DESEJADA                            |");
        gotoxy(coluna,linha);  printf("|_______________________________________________|");
        fflush(stdin);
        gotoxy((coluna+3),(linha-1));scanf("%d",&opcao);

        switch(opcao) {
            case 0: break;
            case 1: inserirNos(&locadora); break;
            case 2: removerNos(&locadora); break;
            case 3: 
                Filme(&locadora);
                printf("\nFilme alugado com sucesso");
                printf("\n\nPressione qualquer tecla para continuar");
                fflush(stdin);
                getch();
                break;

            case 4: 
                Filme2(&locadora);
                printf("\nFilme devolvido com sucesso");
                printf("\n\nPressione qualquer tecla para continuar");
                fflush(stdin);
                getch();
                break;

            case 5:
                system("cls");
                em_ordem(locadora,1,&imprimiu);
                if(!imprimiu) printf("Sem registros disponiveis!\n\n\n");
                imprimiu=false;
                printf("\n\nPressione qualquer tecla para continuar");
                fflush(stdin);
                getch();
                break;

            case 6:
                system("cls");
                em_ordem(locadora,2,&imprimiu);
                if(!imprimiu) printf("Sem registros alugados!\n\n\n");
                imprimiu=false;
                printf("\n\nPressione qualquer tecla para continuar");
                fflush(stdin);
                getch();
                break;

            case 7:
                system("cls");
                em_ordem(locadora,3,&imprimiu);
                if(!imprimiu) printf("Sem registros cadastrados!\n\n\n");
                imprimiu=false;
                printf("\n\nPressione qualquer tecla para continuar");
                fflush(stdin);
                getch();
                break;

            case 8:
                pesquisaLocadora(&locadora);
                break;

            default:
                gotoxy(coluna,linha+3);printf("   *** OPCAO INVALIDA   ***");
                Sleep(2000);
                break;
        }
    } while (opcao != 0);
}