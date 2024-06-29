#include <stdio.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include "tad.h"
int main ()
{
	SetConsoleTitle("Listas");
	char op;
	
	inicioTOP();
	TpAutor *pautor;
	Descritor editoras;
	op=menu();
	int flag=0;
	while(op!=27)
	{
		switch(op)
		{
			case 'A':
				if(flag==0)
				{
					criarBinario();
					pautor=criarLista();
					editoras=criarEditoras(pautor);
					gotoxy(29,4); printf("Arquivo binario criado com sucesso");
					gotoxy(29,5); printf("Lista de autores criada com sucesso");
					gotoxy(29,6); printf("Lista de Editoras criada com sucesso");
					flag=1;
					getche();
				}
				else
				{
					gotoxy(29,4);
					printf("Ja foi inicializado!!!");
					getch();
				}
				break;
			case 'B':
				if(flag==1)
				{
					exibe(pautor);
				}
				else
				{
					gotoxy(29,4);
					printf("Inicialize as estruturas primeiro");
					getch();
				}

				break;
			case 'C':
				if(flag==1)
				{
					excluirLivro(editoras);
				}
				else
				{
					gotoxy(29,4);
					printf("Inicialize as estruturas primeiro");
					getch();
				}				
				break;
			case 'D':
				if(flag==1)
				pautor=alterarNomeCHICO(editoras,pautor);
				else
				{
					gotoxy(29,4);
					printf("Inicialize as estruturas primeiro");
					getch();
				}
				break;
			case 'E':
				if(flag==1)
				alterarNomeLEANDRO(pautor);
				else
				{
					gotoxy(29,4);
					printf("Inicialize as estruturas primeiro");
					getch();
				}
				break;
			case 'F':
				if(flag==1)
				relatorios(editoras,pautor);
				else
				{
					gotoxy(29,4);
					printf("Inicialize as estruturas primeiro");
					getch();
				}
				break;
		}
		op=menu();
	}
	return 0;
}
