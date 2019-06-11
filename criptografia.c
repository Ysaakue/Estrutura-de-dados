#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// DEFINICAO DE FUNCOES AUXILIARES ********************************************

void continuar();
char *recebeString(char *string);
void CriaArquivo(FILE *arquivo);
void LerDoArquivo(FILE *arquivo);

// FUNCAO PRINCIPAL ***********************************************************

int main()
{
    int opcao;
    FILE *Save;

    do{
        system("clear");
        int coluna=2,linha=2;

        printf("             *** MENU PRINCIPAL ***             \n");
        printf("________________________________________________\n");
        printf("| 1) CRIAR UMA MENSAGEM                         |\n");
        printf("| 2) LER MENSAGEM                               |\n");
        printf("|                                               |\n");
        printf("| 0) SAIR                                       |\n");
        printf("|_______________________________________________|\n");
        printf("OPCAO:");
        fflush(stdin);
        scanf("%d",&opcao);

        switch(opcao) 
        {
        case 0: break;

        case 1:
            CriaArquivo(Save);
            break;
        
        case 2:
            LerDoArquivo(Save);
            break;
        
        case 3:
            break;

        case 4:
            
            break;

        default:
            printf("   *** OPCAO INVALIDA   ***");
            break;
        }

    }while(opcao!=0);
}

// FUNCOES AUXILIXARES ********************************************************

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

//-----------------------------------------------------------------------------

void continuar()
{
	puts("\nPRESSIONE ENTER PARA CONTINUAR");
	fflush(stdin);
    getchar();
}

//-----------------------------------------------------------------------------

void CriaArquivo(FILE *arquivo)
{
    char NomeArquivo[30];
    char mensagem[30];

    printf("Digite o nome do arquivo:");
    strcpy(NomeArquivo,"teste.bin");
    printf("\nDigite a Mensagem para ser colocada no arquivo:");
    scanf("%s", mensagem);

    if((arquivo=fopen(NomeArquivo, "w+b"))==NULL)
	{
		printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
		perror("fopen");
	}
	else
	{
		printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
        if(!fwrite(&mensagem, sizeof(mensagem), 1, arquivo)) printf("ERRO NA ESCRITA\n");
        else puts("GRAVACAO REALIZADA COM SUCESSO\n");
		fclose(arquivo);
	}
    continuar();
}
//-----------------------------------------------------------------------------

void LerDoArquivo(FILE *arquivo) 
{
	char NomeArquivo[30], mensagem[30];
	
    printf("Digite o nome do arquivo:");
    strcpy(NomeArquivo,"teste.bin");

	if((arquivo=fopen(NomeArquivo, "rb"))==NULL)
	{
		printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
		perror("fopen");
	}
	else
	{
		printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
        if(fread(&mensagem, sizeof(30*sizeof(char)), 1, arquivo) != 1 )
        {
            printf("ERRO NA LEITURA");
        }
        else 
        {
            printf("\n%s\n",mensagem);
        }
		fclose(arquivo);
	}
    continuar();
}

//-----------------------------------------------------------------------------