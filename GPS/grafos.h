// DEFINIÇÃOO DE BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>

// DEFINES PARA OS ESTADOS
#define quantidade 26

#define Acre 0
#define AC 0

#define Alagoas 1 
#define AL 1

#define Amapa 2
#define AP 2

#define Amazonas 3
#define AM 3

#define Bahia 4
#define BA 4

#define Ceara 5
#define CE 5

#define Espirito_Santo 6
#define ES 6

#define Goias 7
#define GO 7

#define Maranhao 8
#define MA 8

#define Mato_Grosso 9
#define MT 9

#define Mato_Grosso_do_Sul 10
#define MS 10

#define Minas_Gerais 11
#define MG 11

#define Para 12
#define PA 12

#define Paraiba 13
#define PB 13

#define Parana 14
#define PR 14

#define Pernambuco 15
#define PE 15

#define Piaui 16
#define PI 16

#define Rio_de_Janeiro 17
#define RJ 17

#define Rio_Grande_do_Norte 18
#define RN 18

#define Rio_Grande_do_Sul 19
#define RS 19

#define Rondonia 20
#define RO 20

#define Roraima 21
#define RR 21

#define Santa_Catarina 22
#define SC 22

#define Sao_Paulo 23
#define SP 23

#define Sergipe 24
#define SE 24

#define Tocantins 25
#define TO 25

// DEFINIÇÃOO DA STRUCT
struct no{
	char nome[20];
	char sigla[2];
};

struct arco{
	bool adj;
	int distancia;
};

struct graph{
	struct no nos[quantidade];
	struct arco matriz[quantidade][quantidade];
};

// DEFINIÇÃO DE FUNÇÕES
void continuar()
{
	puts("\nPRESSIONE ENTER PARA CONTINUAR");
	getchar();
}

//**********************************************************************

void iniciar(struct graph *grafo)
{
	int x,y;

	strcpy(grafo->nos[0].nome,"Acre");
	strcpy(grafo->nos[0].sigla,"AC");
	
	strcpy(grafo->nos[1].nome,"Alagoas");
	strcpy(grafo->nos[1].sigla,"AL");
	
	strcpy(grafo->nos[2].nome,"Amapa");
	strcpy(grafo->nos[2].sigla,"AP");

	strcpy(grafo->nos[3].nome,"Amazonas");
	strcpy(grafo->nos[3].sigla,"AM");
	
	strcpy(grafo->nos[4].nome,"Bahia");
	strcpy(grafo->nos[4].sigla,"BA");
	
	strcpy(grafo->nos[5].nome,"Ceara");
	strcpy(grafo->nos[5].sigla,"CE");
	
	strcpy(grafo->nos[6].nome,"Espirito Santo");
	strcpy(grafo->nos[6].sigla,"ES");
	
	strcpy(grafo->nos[7].nome,"Goias");
	strcpy(grafo->nos[7].sigla,"GO");
	
	strcpy(grafo->nos[8].nome,"Maranhao");
	strcpy(grafo->nos[8].sigla,"MA");

	strcpy(grafo->nos[9].nome,"Mato Grosso");
	strcpy(grafo->nos[9].sigla,"MT");

	strcpy(grafo->nos[10].nome,"Mato Grosso do sul");
	strcpy(grafo->nos[10].sigla,"MS");

	strcpy(grafo->nos[11].nome,"Minas Gerais");
	strcpy(grafo->nos[11].sigla,"MG");

	strcpy(grafo->nos[12].nome,"Para");
	strcpy(grafo->nos[12].sigla,"PA");

	strcpy(grafo->nos[13].nome,"Paraiba");
	strcpy(grafo->nos[13].sigla,"PB");

	strcpy(grafo->nos[14].nome,"Parana");
	strcpy(grafo->nos[14].sigla,"PR");

	strcpy(grafo->nos[15].nome,"Pernambuco");
	strcpy(grafo->nos[15].sigla,"PE");

	strcpy(grafo->nos[16].nome,"Piaui");
	strcpy(grafo->nos[16].sigla,"PI");

	strcpy(grafo->nos[17].nome,"Rio de Janeiro");
	strcpy(grafo->nos[17].sigla,"RJ");

	strcpy(grafo->nos[18].nome,"Rio Grande do Norte");
	strcpy(grafo->nos[18].sigla,"RN");

	strcpy(grafo->nos[19].nome,"Rio Grande do Sul");
	strcpy(grafo->nos[19].sigla,"RS");

	strcpy(grafo->nos[20].nome,"Rondonia");
	strcpy(grafo->nos[20].sigla,"RO");

	strcpy(grafo->nos[21].nome,"Roraima");
	strcpy(grafo->nos[21].sigla,"RR");

	strcpy(grafo->nos[22].nome,"Santa Catarina");
	strcpy(grafo->nos[22].sigla,"RC");

	strcpy(grafo->nos[23].nome,"Sao Paulo");
	strcpy(grafo->nos[23].sigla,"SP");

	strcpy(grafo->nos[24].nome,"Sergipe");
	strcpy(grafo->nos[24].sigla,"SE");

	strcpy(grafo->nos[25].nome,"Tocantins");
	strcpy(grafo->nos[25].sigla,"TO");

	for(x=0;x<quantidade;x++)
	{
		for(y=0;y<quantidade;y++)
		{
			grafo->matriz[x][y].adj=false;
		}
	}

	
}


//**********************************************************************

//void CriarArquivo_1(FILE *arquivo,const char *NomeDoArquivo)
//{
//	int test;
//
//	if((arquivo=fopen(NomeDoArquivo, "ab"))==NULL)
//	{
//		printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeDoArquivo);
//		//printf("\nERRO AO ABRIR O ARQUIVO 'Arquivo.bin'.\n");
//		perror("fopen");
//		//exit(1);
//	}
//	else
//	{
//		printf("\nARQUIVO '%s' ABERTO COM SUCESSO.\n",NomeDoArquivo);
//		//printf("\nARQUIVO '%s' CRIADO COM SUCESSO.\n",NomeDoArquivo);
//		//printf("\nARQUIVO 'Arquivo.bin' CRIADO COM SUCESSO.\n");
//	}
//	
//	fclose(arquivo);
//}
//
////**********************************************************************
//
//void Salvar_10(FILE *arquivo,const char *NomeDoArquivo) 
//{
//	int i;
//	
//	if((arquivo=fopen(NomeDoArquivo, "r+b"))==NULL)
//	{
//		printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeDoArquivo);
//		perror("fopen");
//	}
//	else
//	{
//		printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeDoArquivo);
//		for(i = 0; i < QuantidadeAlunos-1; i++) // escreve cada elemento do vetor no arquivo
//		{
//			
//			if(!isnull(Alunos[i].nome))
//			{
////				ImprimirUmRegistro(i);
//				if(fwrite(&Alunos[i], sizeof(struct Dados), 1, arquivo) != 1 ) printf("ERRO NA ESCRITA DO REGISTRO %d\n",i+1);
//				else puts("GRAVACAO REALIZADA COM SUCESSO\n");
//			}
//			
//		}
//		fclose(arquivo);
//	}
//}
//
////**********************************************************************
//
//void LerDoArquivo_2(FILE *arquivo,const char *NomeDoArquivo) 
//{
//	int i;
//	
//	if((arquivo=fopen(NomeDoArquivo, "rb"))==NULL)
//	{
//		printf("\nERRO AO ABRIR O ARQUIVO '%s'.\n",NomeDoArquivo);
//		perror("fopen");
//	}
//	else
//	{
//		printf("\nARQUIVO '%s' ABERTO PARA GRAVACAO COM SUCESSO.\n",NomeDoArquivo);
//		for(i = 0; i < QuantidadeAlunos-1; i++) // escreve cada elemento do vetor no arquivo
//		{
//			if(fread(&Alunos[i], sizeof(struct Dados), 1, arquivo) != 1 )
//			{
//				 printf("ERRO NA LEITURA DO REGISTRO %d\n",i+1);
//				 if (feof(arquivo)) break;
//			}
//			
////			else puts("LEITURA REALIZADA COM SUCESSO\n");
//		}
//		fclose(arquivo);
//	}
//}
//
////**********************************************************************
