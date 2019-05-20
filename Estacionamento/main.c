#include "biblioteca.h"

void main() {
  apontador placa,dono;
  int opcao;

  dono = NULL;
  placa = NULL;

  do {
    cls();
    int coluna=2,linha=2;

    gotoxy(coluna,linha++);printf("             *** MENU PRINCIPAL ***             ");
    gotoxy(coluna,linha++);printf("________________________________________________");
    gotoxy(coluna,linha++);printf("| 1) ADICIONAR CARRO                            |");
    gotoxy(coluna,linha++);printf("| 2) REMOVER CARRO                              |");
    gotoxy(coluna,linha++);printf("| 3) IMPRIMER PLACAS EM ORDREM ALFABETICA       |");
    gotoxy(coluna,linha++);printf("| 4) IMPRIMIR PROPRIETARIOS EM ORDEM ALFABETICA |");
    gotoxy(coluna,linha++);printf("| 5) REALIZAR BUSCA POR PLACA                   |");
    gotoxy(coluna,linha++);printf("| 6) REALIZAR BUSCA POR PROPRIETARIO            |");
    gotoxy(coluna,linha++);printf("| 0) SAIR                                       |");
    gotoxy(coluna,linha++);printf("| [?] OPCAO DESEJADA                            |");
    gotoxy(coluna,linha);  printf("|_______________________________________________|");
    fflush(stdin);
    gotoxy((coluna+3),(linha-1));scanf("%d",&opcao);

    switch(opcao) 
    {
      case 0: break;
      case 1: inserirNos(&placa,&dono); break;
      case 2: removerNos(&placa,&dono); break;
      
      case 3:
        cls();
        em_ordem(placa);
        printf("\n\nPressione [algo] para prosseguir.");
        getch();
        break;

      case 4:
        cls();
        em_ordem(dono);
        printf("\n\nPressione [algo] para prosseguir.");
        getch();
        break;

      case 5:
        pesquisaPlaca(&placa);
        break;

      case 6:
      pesquisaProprietario(&dono);
        break;
    }

  } while (opcao != 0);
}