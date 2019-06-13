#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// DEFINICAO DE FUNCOES AUXILIARES ********************************************

void continuar();
char *recebeString(char *string);
void CriaArquivo(FILE *arquivo);
void LerDoArquivo(FILE *arquivo);
void CriptografarArquivo(FILE *arquivo);
void DescriptografarArquivo(FILE *arquivo);

// FUNCAO PRINCIPAL ***********************************************************

int main()
{
    int opcao;
    FILE *Save;

    do{
        system("cls");

        printf("             *** MENU PRINCIPAL ***             \n");
        printf("________________________________________________\n");
        printf("| 1) CRIAR UMA MENSAGEM                         |\n");
        printf("| 2) LER MENSAGEM                               |\n");
        printf("| 3) CRIPITOGRAFAR MENSAGEM                     |\n");
        printf("| 4) DESCRIPTOGRAFAR MENSAGEM                   |\n");
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
            CriptografarArquivo(Save);
            break;

        case 4:
            DescriptografarArquivo(Save);
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
    char NomeArquivo[30], mensagem[30], operacao[3];
    int opcao;

    printf("Digite o nome do arquivo:");
	fflush(stdin);
	gets(NomeArquivo);
    printf("\nDigite a Mensagem para ser colocada no arquivo:");
	gets(mensagem);
    int tamanho = strlen(mensagem);
    do{
        system("cls");

        printf("       *** SELECIONAR TIPO DE ARQUIVO ***       \n");
        printf("________________________________________________\n");
        printf("| 1) TEXTO                                      |\n");
        printf("| 2) BINARIA                                    |\n");
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
                if((arquivo=fopen(NomeArquivo, "w+"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
                    if(!fwrite(&mensagem, 30*sizeof(char), 1, arquivo)) printf("ERRO NA ESCRITA\n");
                    else puts("GRAVACAO REALIZADA COM SUCESSO\n");
                    fclose(arquivo);
                }
                continuar();
                break;
            
            case 2:
                if((arquivo=fopen(NomeArquivo, "w+b"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
                    if(!fwrite(&mensagem, 30*sizeof(char), 1, arquivo)) printf("ERRO NA ESCRITA\n");
                    else puts("GRAVACAO REALIZADA COM SUCESSO\n");
                    printf("%s",mensagem);
                    fclose(arquivo);
                }
                continuar();
                break;
 
            default:
                printf("   *** OPCAO INVALIDA   ***");
                break;
        }
    }while(opcao <0 || opcao>2);
}

//-----------------------------------------------------------------------------

void LerDoArquivo(FILE *arquivo) 
{
	char NomeArquivo[30], mensagem[30], operacao[2];
    int opcao;
	
    printf("Digite o nome do arquivo:");
	fflush(stdin);
	gets(NomeArquivo);

    do{
        system("cls");

        printf("       *** SELECIONAR TIPO DE ARQUIVO ***       \n");
        printf("________________________________________________\n");
        printf("| 1) TEXTO                                      |\n");
        printf("| 2) BINARIA                                    |\n");
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
                if((arquivo=fopen(NomeArquivo, "r"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
                    if(fread(&mensagem, 30*sizeof(char), 1, arquivo) != 1 )
                    {
                        printf("ERRO NA LEITURA");
                    }
                    else 
                    {
                        int i=0;
                        while(mensagem[i]!='\0')
                        {
                            printf("%c",mensagem[i++]);
                        }
                        // printf("\n%s\n",mensagem);
                    }
                    fclose(arquivo);
                }
                continuar();
                break;
            
            case 2:
                if((arquivo=fopen(NomeArquivo, "rb"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
                    if(fread(&mensagem, 30*sizeof(char), 1, arquivo) != 1 )
                    {
                        printf("ERRO NA LEITURA");
                    }
                    else 
                    {
                        int i=0;
                        while(mensagem[i]!='\0')
                        {
                            printf("%c",mensagem[i++]);
                        }
                        // printf("\n%s\n",mensagem);
                    }
                    fclose(arquivo);
                }
                continuar();
                break;
 
            default:
                printf("   *** OPCAO INVALIDA   ***");
                break;
        }
    }while(opcao <0 || opcao>2);
}

//-----------------------------------------------------------------------------

void CriptografarArquivo(FILE *arquivo) 
{
	char NomeArquivo[30], mensagem[30], operacao[2];
    int opcao, primeiro_numero, primeira_operacao,i,numero_usado;
	
    printf("Digite o nome do arquivo:");
	fflush(stdin);
	gets(NomeArquivo);

    do{
        system("cls");

        printf("       *** SELECIONAR TIPO DE ARQUIVO ***       \n");
        printf("________________________________________________\n");
        printf("| 1) TEXTO                                      |\n");
        printf("| 2) BINARIA                                    |\n");
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
                if((arquivo=fopen(NomeArquivo, "r"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
                    if(fread(&mensagem, 30*sizeof(char), 1, arquivo) != 1 )
                    {
                        printf("ERRO NA LEITURA");
                    }
                    fclose(arquivo);
                }
                
                primeiro_numero = rand() % 100;
                primeira_operacao = rand() % 2;
                i=0;

                if(primeira_operacao)
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2==0)
                        {
                            mensagem[i] = mensagem[i]+(numero_usado++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]-(numero_usado++);
                        }
                        i++;
                    }
                }
                else
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2!=0)
                        {
                            mensagem[i] = mensagem[i]+(numero_usado++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]-(numero_usado++);
                        }
                    }
                    i++;
                }

                printf("\n\nmensagem:%s \nprimeiro numero: %d\nprimeira operacao: %d\n\n", mensagem, primeiro_numero, primeira_operacao);
                

                if((arquivo=fopen(NomeArquivo, "r+"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
                    if(!fwrite(&mensagem, 30*sizeof(char), 1, arquivo) || !fwrite(&primeiro_numero, sizeof(int), 1, arquivo) || !fwrite(&primeira_operacao, sizeof(int), 1, arquivo)) printf("ERRO NA ESCRITA\n");
                    else puts("GRAVACAO REALIZADA COM SUCESSO\n");
                    fclose(arquivo);
                }
                continuar();
                break;
            
            case 2:
                if((arquivo=fopen(NomeArquivo, "rb"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
                    if(fread(&mensagem, 30*sizeof(char), 1, arquivo) != 1 )
                    {
                        printf("ERRO NA LEITURA");
                    }
                    fclose(arquivo);
                }

                primeiro_numero = rand() % 100;
                primeira_operacao = rand() % 2;
                i=0;
                

                if(primeira_operacao)
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2==0)
                        {
                            mensagem[i] = mensagem[i]+(primeiro_numero++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]-(primeiro_numero++);
                        }
                        i++;
                    }
                }
                else
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2!=0)
                        {
                            mensagem[i] = mensagem[i]+(primeiro_numero++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]-(primeiro_numero++);
                        }
                    }
                    i++;
                }

                if((arquivo=fopen(NomeArquivo, "w+b"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
                    if(!fwrite(&mensagem, 30*sizeof(char), 1, arquivo) || !fwrite(&primeiro_numero, sizeof(int), 1, arquivo) || !fwrite(&primeira_operacao, sizeof(int), 1, arquivo)) printf("ERRO NA ESCRITA\n");
                    else puts("GRAVACAO REALIZADA COM SUCESSO\n");
                    printf("%s",mensagem);
                    fclose(arquivo);
                }
                continuar();
                break;
 
            default:
                printf("   *** OPCAO INVALIDA   ***");
                break;
        }
    }while(opcao <0 || opcao>2);
}

//-----------------------------------------------------------------------------

void DescriptografarArquivo(FILE *arquivo) 
{
	char NomeArquivo[30], mensagem[30], operacao[2];
    int opcao,primeiro_numero,primeira_operacao,i;
	
    printf("Digite o nome do arquivo:");
	fflush(stdin);
	gets(NomeArquivo);

    do{
        system("cls");

        printf("       *** SELECIONAR TIPO DE ARQUIVO ***       \n");
        printf("________________________________________________\n");
        printf("| 1) TEXTO                                      |\n");
        printf("| 2) BINARIA                                    |\n");
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
                if((arquivo=fopen(NomeArquivo, "r"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
                    if(fread(&mensagem, 30*sizeof(char), 1, arquivo) != 1 || fread(&primeiro_numero, sizeof(int), 1, arquivo) != 1 || fread(&primeira_operacao, sizeof(int), 1, arquivo) != 1 )
                    {
                        printf("ERRO NA LEITURA");
                    }
                    fclose(arquivo);
                }

                printf("\n\nmensagem:%s \nprimeiro numero: %d\nprimeira operacao: %d\n\n", mensagem, primeiro_numero, primeira_operacao);


                i=0;
                if(primeira_operacao)
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2==0)
                        {
                            mensagem[i] = mensagem[i]-(primeiro_numero++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]+(primeiro_numero++);
                        }
                        i++;
                    }
                }
                else
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2!=0)
                        {
                            mensagem[i] = mensagem[i]-(primeiro_numero++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]+(primeiro_numero++);
                        }
                    }
                    i++;
                }
                

                if((arquivo=fopen(NomeArquivo, "r+"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
                    if(!fwrite(&mensagem, 30*sizeof(char), 1, arquivo) ) printf("ERRO NA ESCRITA\n");
                    else puts("GRAVACAO REALIZADA COM SUCESSO\n");
                    fclose(arquivo);
                }
                continuar();
                break;
            
            case 2:
                if((arquivo=fopen(NomeArquivo, "rb"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA LEITURA COM SUCESSO.\n",NomeArquivo);
                    if(fread(&mensagem, 30*sizeof(char), 1, arquivo) != 1 || fread(&primeiro_numero, sizeof(int), 1, arquivo) != 1 || fread(&primeira_operacao, sizeof(int), 1, arquivo) != 1  )
                    {
                        printf("ERRO NA LEITURA");
                    }
                    fclose(arquivo);
                }

                i=0;
                if(primeira_operacao)
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2==0)
                        {
                            mensagem[i] = mensagem[i]-(primeiro_numero++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]+(primeiro_numero++);
                        }
                        i++;
                    }
                }
                else
                {
                    while(mensagem[i]!='\0')
                    {
                        if(i%2!=0)
                        {
                            mensagem[i] = mensagem[i]-(primeiro_numero++);
                        }
                        else
                        {
                            mensagem[i] = mensagem[i]+(primeiro_numero++);
                        }
                    }
                    i++;
                }

                if((arquivo=fopen(NomeArquivo, "w+b"))==NULL)
                {
                    printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeArquivo);
                    perror("fopen");
                }
                else
                {
                    printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeArquivo);
                    if(!fwrite(&mensagem, 30*sizeof(char), 1, arquivo) ) printf("ERRO NA ESCRITA\n");
                    else puts("GRAVACAO REALIZADA COM SUCESSO\n");
                    printf("%s",mensagem);
                    fclose(arquivo);
                }
                continuar();
                break;
 
            default:
                printf("   *** OPCAO INVALIDA   ***");
                break;
        }
    }while(opcao <0 || opcao>2);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------