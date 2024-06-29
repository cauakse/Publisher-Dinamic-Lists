struct Registro {
	char autores[1000],titulo[100],editora[100];
	int ano, paginas,status;
};

struct TpAutor{
	char nome[100],sobrenome[100];
	TpAutor * prox;
};

struct TpListaAutor{
	TpAutor *autor;
	TpListaAutor * prox;
};

struct TpLivro {
	TpLivro *ant,*prox;
	char titulo[100];
	int ano,pagina;
	TpListaAutor *lista;
};

struct TpEditora{
	TpEditora *prox;
	char nome[100];
	TpLivro *lista;
};

struct Descritor {
	int qtde;
	TpEditora *ini, *fim;
};

struct TpListaLivro{
	TpListaLivro * prox;
	TpLivro *livro;
};
struct AutorExibe{
	TpListaLivro * lista;
	TpAutor * autor;
	AutorExibe * prox;
};
void quadrado(int ci,int li,int cf,int lf,int cor)
{
	textcolor(cor);
	gotoxy(ci,li);
        printf("%c",201);
    gotoxy(ci,lf);
        printf("%c",200);
    gotoxy(cf,li);
        printf("%c",187);
    gotoxy(cf,lf);
        printf("%c",188);
        
    for(int i=ci+1;i<cf;i++)
    {
    	gotoxy(i,li);
    	printf("%c",205);
    	gotoxy(i,lf);
    	printf("%c",205);
    }
    for(int i=li+1;i<lf;i++)
    {
    	gotoxy(ci,i);
    	printf("%c",186);
    	gotoxy(cf,i);
    	printf("%c",186);
    }
    textcolor(15);
}

char menu()
{
	system("cls");
	quadrado(1,1,80,25,4);
	quadrado(2,2,26,15,7);
	gotoxy(2,22);
	printf("Developed by CAUA");
	quadrado(28,2,78,24,4);
	gotoxy(3,3);
	printf("[A]- INICIA ESTRUTURAS");
	gotoxy(3,4);
	printf("[B]- EXIBE AUTORES");
	gotoxy(3,5);
	printf("[C]- EXCLUIR LIVRO");
	gotoxy(3,6);
	printf("[D]- ALTERAR CHICO");
	gotoxy(3,7);
	printf("[E]- ALTERAR LEANDRO");
	gotoxy(3,8);
	printf("[F]- RELATORIOS");
	gotoxy(3,9);
	gotoxy(3,10);
	printf("[ESQ]- PARA SAIR");
	gotoxy(29,4);
	fflush(stdin);
	return toupper(getch());
}
void inicioTOP()
{
	gotoxy(2,2);
	printf("LiStAs dE LiStAs");
	textcolor(0);
	textbackground(15);
	quadrado(1,1,80,25,4);
	textcolor(15);
	textbackground(0);
	int i,j,k;
	char frase [23];
	strcpy(frase,"EDITORAS CAUA PEREIRA\0");
	for(i=0;i<strlen(frase);i++)
	{
		for(j=strlen(frase);j>i;j--)
		{
			gotoxy(j+28+1,12);printf(" ");
			gotoxy(j+28,12);
			for(k=0;k<8;k++)
			{
				printf("%c",rand()%26+64);
				gotoxy(j+28,12);
			}
			gotoxy(j+28+1,12);printf(" ");
			Sleep(5);
		}
		gotoxy(i+28+1,12);printf(" ");
		gotoxy(i+28,12);
		printf("%c",frase[i]);
	}
	while(!kbhit())
	{
		Sleep(500);
		gotoxy(26,15);
		printf("PRESS ANY KEY TO CONTINUE");
		Sleep(500);
		gotoxy(26,15);
		printf("                          ");
	}
}
AutorExibe* copiaAutores(TpAutor * autores,AutorExibe * lista)
{
	TpAutor * auxA = autores;
	AutorExibe * NC,*auxL;;
	while(auxA!=NULL)
	{
		NC= new AutorExibe;
		NC->autor=auxA;
		NC->prox=NULL;
		NC->lista=NULL;
		if(lista==NULL)
		{
			lista=NC;
		}
		else
		{
			auxL=lista;
			while(auxL->prox!=NULL)
				auxL=auxL->prox;
				
			auxL->prox=NC;
		}
		auxA=auxA->prox;
	}
	
	return lista;
}
TpLivro*  insereLivro(TpLivro * lista , TpLivro * lv)
{
	
	if(lista==NULL)
	{
		lista=lv;
	}
	else
	{
		
		if(stricmp(lv->titulo,lista->titulo)<0)
		{
			lv->prox=lista;
			lista->ant=lv;
			lista=lv;
		}
			else
			{
				TpLivro * aux = lista;
				while(aux->prox!=NULL&&stricmp(aux->titulo,lv->titulo)<0)
				{
					aux=aux->prox;
				}
				
				if(stricmp(aux->titulo,lv->titulo)>0)
				{
					lv->prox=aux;
					lv->ant=aux->ant;
					aux->ant->prox=lv;
					aux->ant=lv;
				}
				else
				{
					lv->ant=aux;
					aux->prox=lv;
				}
			}
	}
	return lista;
}
TpListaLivro *insereListaLivro(TpListaLivro *lista,TpListaLivro *NC)
{
	if(lista==NULL)
	{
		lista=NC;
	}
	else
	{
		if(stricmp(lista->livro->titulo,NC->livro->titulo)>0)
		{
			NC->prox=lista;
			lista=NC;
		}
		else
		{
			TpListaLivro *aux,*ant;
			aux=lista->prox;
			ant=lista;
			while(aux!=NULL&&stricmp(NC->livro->titulo,aux->livro->titulo)!=0)
			{
				ant=aux;
				aux=aux->prox;
			}
			if(aux!=NULL)
			{
				NC->prox=aux;
				ant->prox=NC;
			}
			else
			{
				ant->prox=NC;
			}
		}
		
	}
	return lista;
}
AutorExibe * colocaLivros(Descritor desci,AutorExibe * lista)
{
	AutorExibe * aux;
	Descritor desc= desci;
	TpEditora * auxE = desc.ini;
	TpLivro *auxL;
	TpListaLivro *insere;
	TpListaAutor * auxLa;
	TpAutor * auxA;
	
	while(auxE!=NULL)
	{
		auxL=auxE->lista;
		while(auxL!=NULL)
		{
			auxLa=auxL->lista;
			while(auxLa!=NULL)
			{
				aux=lista;
				while(aux!=NULL)
				{
					if(stricmp(aux->autor->nome,auxLa->autor->nome)==0&&stricmp(aux->autor->sobrenome,auxLa->autor->sobrenome)==0)
					{
							insere= new TpListaLivro;
							insere->prox=NULL;
							insere->livro=auxL;
							aux->lista=insereListaLivro(aux->lista,insere);
					}
					
					aux=aux->prox;
				}
				
				auxLa=auxLa->prox;
			}
			
			auxL=auxL->prox;
		}
		auxE=auxE->prox;
	}
	return lista;
}
void exibeLivrosAutores(Descritor desci,TpAutor * autores)
{
	system("cls");
	quadrado(1,1,120,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,118,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	gotoxy(3,13);
	printf("Utilize as Setas Para");
	gotoxy(3,14);
	printf("Mover as paginas");
	gotoxy(27,25);
	AutorExibe * lista = NULL,*aux;
	TpListaLivro *auxL;
	lista = copiaAutores(autores,lista);
	lista = colocaLivros(desci,lista);
	char op=' ';
	int max=0,i,j,k,pag=0;;
	aux=lista;
	while(aux!=NULL)
	{
		max++;
		aux=aux->prox;
	}
	aux=lista;
	while(op!=27&&op!=10)
	{
		j=0;
		k=0;
		i=3;
		lista=aux;
		while(lista!=NULL&&j<3)
		{
			gotoxy(110,3);printf("Pag: %d",pag+1);
			if(k>=pag*3)
			{
	
				gotoxy(29,i);
				printf("AUTOR [%s]\n",lista->autor->nome);
				i++;
				gotoxy(29,i);
				printf("LIVROS:\n");
				i++;
				auxL=lista->lista;
				while(auxL!=NULL)
				{
					gotoxy(29,i);
					printf("[%s]\n",auxL->livro->titulo);
					auxL=auxL->prox;
					i++;
				}
				i++;
				j++;
			}
			k++;
			lista=lista->prox;
		}
		
		fflush(stdin);
		op=getch();
		switch(op)
		{
			case 77:
				if(pag<max/3)
				pag++;
				break;
			case 75:
				if(pag>0)
				pag--;
				break;
		}
		
		j=3;
		while(j<23)
		{
			gotoxy(29,j);
			printf("                                                                    ");
			j++;
		}		
	}
	while(aux!=NULL)
	{
		lista=aux;
		aux=aux->prox;
		delete(lista);
	}
	
}

void exibeAutoresSemLivros(Descritor desci,TpAutor * autores)
{
	system("cls");
	quadrado(1,1,80,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,78,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	gotoxy(3,13);
	printf("Utilize as Setas Para");
	gotoxy(3,14);
	printf("Mover as paginas");
	gotoxy(27,25);
	AutorExibe * lista = NULL,*aux;
	aux=lista;
	int i,j,k,max=0,pag=0;
	char op=' ';

	lista=copiaAutores(autores,lista);
	lista=colocaLivros(desci,lista);
	
	aux=lista;
	while(aux!=NULL)
	{
		max++;
		aux=aux->prox;
	}
	aux=lista;
	gotoxy(29,3);
	printf("Autores sem livros :\n");
	while(op!=27&&op!=10)
	{
		i=4;
		j=0;
		k=0;
		gotoxy(70,3);printf("Pag: %d",pag+1);
		lista=aux;
		while(lista!=NULL&&j<10)
		{
			if(k>=pag*10)
			{
				if(lista->lista==NULL)
				{
					gotoxy(29,i);
					printf("%s",lista->autor->nome);
					i++;
					j++;
				}
				k++;
			}
			
			lista=lista->prox;
		}
		
		fflush(stdin);
		op=getch();
		
		switch(op)
		{
			case 77:
				if(pag<max/10)
				pag++;
				break;
			case 75:
				if(pag>0)
				pag--;
				break;
		}
		
		j=4;
		while(j<20)
		{
			gotoxy(29,j);
			printf("                               ");
			j++;
		}
	}
	
	lista=aux;
	while(lista!=NULL)
	{
		aux=lista;
		lista=lista->prox;
		delete(aux);
	}	
}

void exibe(TpAutor *autor)
{
	system("cls");
	quadrado(1,1,80,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,78,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	gotoxy(3,13);
	printf("Utilize as Setas Para");
	gotoxy(3,14);
	printf("Mover as paginas");
	gotoxy(27,25);
	int i=3,j,pag=0,k,max=0;;
	TpAutor *lista=autor;
	char op=' ';
	if(lista==NULL)
	{
		gotoxy(29,i);
		printf("Lista esta vazia\n");
		getch();
	}
	else
	{
		while(lista!=NULL)
		{
			max++;
			lista=lista->prox;
		}
		while(op!=27 && op!=10)
		{
			j=0;
			lista=autor;
			k=0;
			i=3;
			gotoxy(70,3);printf("Pag: %d",pag+1);
			while(lista!=NULL&&j<7)
			{
				if(k>=pag*7)
				{
					gotoxy(29,i);
					printf("%s %s",lista->nome,lista->sobrenome);
					j++;
					i++;
				}
				k++;
				lista=lista->prox;
			}
			
			fflush(stdin);
			op=getch();
			
			switch(op)
			{
				case 77:
					if(pag<(max+1)/7)
					pag++;
					break;
				case 75:
					if(pag>0)
					pag--;
					break;
			}
			
			j=3;
			while(j<10)
			{
				gotoxy(29,j);
				printf("                                  ");
				j++;
			}
		}
	
	}
}
int buscaIgual (TpAutor *lista,TpAutor *NC)
{
	while(lista!=NULL&&(stricmp(lista->nome,NC->nome)!=0 || stricmp(lista->sobrenome,NC->sobrenome)!=0))
		lista=lista->prox;
		
	if(lista!=NULL)
		return -1;
	else
		return 1;
}

TpAutor * insereOrdenado(TpAutor * lista, TpAutor * NC)
{
	if(lista==NULL)
	{
		lista=NC;
	}
	else
	{
		if(buscaIgual(lista,NC)!=-1)
		{
			if(stricmp(lista->nome,NC->nome)>0)
			{
				NC->prox=lista;
				lista=NC;
			}
			else
			{
				TpAutor *aux=lista->prox,*ant=lista;
				while(aux!=NULL&&stricmp(aux->nome,NC->nome)<0)
				{
					ant=aux;
					aux=aux->prox;
				}
				if(aux!=NULL)
				{
					NC->prox=aux;
					ant->prox=NC;
				}
				else
				{
					ant->prox=NC;
				}
			}
		}
	}
	return lista;
}
TpAutor * criarLista()
{
	FILE * ptrb = fopen("livros.dat","rb+");
	TpAutor *pautor=NULL;
	TpAutor *NC;
	Registro reg;
	char nome[100],aux[100],primeiro[100];
	int i,j,k;
	
	
	rewind(ptrb);
	//entra lido
	fread(&reg,sizeof(Registro),1,ptrb);
	
	//leio até o final dos registros
	while(!feof(ptrb))
	{
		//vou ler até o final da string que cotém o nome de todos os autores
		i=0;
		while(i<strlen(reg.autores))
		{
			//vou ler até o ; ou o \0, jogando esse nome pra uma string
			j=0;
			while(reg.autores[i]!='\0'&&reg.autores[i]!=';')
			{
				nome[j]=reg.autores[i];
				j++;
				i++;
			}
			//coloco o final da string
			nome[j]='\0';
			
			j=0;
			k=0;
			while(nome[j]!=',')
			{
				if(nome[j]!=',')
				{
					aux[k]=nome[j];
					k++;
				}
				j++;
			}
			aux[k]='\0';
			NC = new TpAutor;
			strcpy(NC->sobrenome,aux);
			
			j+=2;
			k=0;
			while(nome[j]!='\0')
			{
				if(nome[j]!=',')
				{
					aux[k]=nome[j];
					k++;
				}
				
				j++;
				
			}
			aux[k]='\0';
			strcpy(NC->nome,aux);
			
			NC->prox=NULL;
			pautor=insereOrdenado(pautor,NC);
			if(reg.autores[i]!='\0')
			i+=2;
		}
		
		fread(&reg,sizeof(Registro),1,ptrb);	
	}
	fclose(ptrb);
	return pautor;
		
}
void exibee(Descritor desci)
{
	Descritor desc = desci;
	TpLivro * auxLv;
	TpListaAutor * auxA;
	while(desc.ini!=NULL)
	{
		printf("-----------------------------------------------------\n");
		printf("Editora: %s\n",desc.ini->nome);
		printf("Livros:\n");
		auxLv=desc.ini->lista;
		while(auxLv!=NULL)
		{
			printf("%s\n",auxLv->titulo);
			printf("    AUTORES:\n");
			auxA=auxLv->lista;
			while(auxA!=NULL)
			{
				printf("[%s]\n",auxA->autor->nome);
				
				auxA=auxA->prox;
			}
			
			
			printf("    \n");
			auxLv=auxLv->prox;
		}
		
		
		desc.ini=desc.ini->prox;
	}
}

Descritor inicia(Descritor desc)
{
	desc.ini=NULL;
	desc.fim=NULL;
	desc.qtde=0;
	return desc;
}

TpLivro * colocaAutores(TpLivro * lv, TpAutor * autores,Registro reg)
{
	TpListaAutor * naut;
	TpAutor * aut;
	int i,j,k;
	char nome[100],sobrenome[100],primeiro[100];
		lv->prox=NULL;
		lv->ant=NULL;
		lv->lista=NULL;
		lv->ano=reg.ano;
		lv->pagina=reg.paginas;
		strcpy(lv->titulo,reg.titulo);
		i=0;
		while(i<strlen(reg.autores))
		{
			j=0;
			while(reg.autores[i]!='\0'&&reg.autores[i]!=';')
			{
				nome[j]=reg.autores[i];
				i++;
				j++;
			}
			nome[j]='\0';
			
			j=0;
			k=0;
			while(nome[j]!=',')
			{
				if(nome[j]!=',')
				{
					primeiro[k]=nome[j];
					k++;
				}
				
				j++;
			}
			primeiro[k]='\0';
			k=0;
			j+=2;
			
			while(nome[j]!='\0')
			{
				if(nome[j]!=',')
				{
					sobrenome[k]=nome[j];
					k++;
				}
				
				j++;
			}
			sobrenome[k]='\0';
			aut=autores;
				
			while(aut!=NULL && (stricmp(aut->sobrenome,primeiro)!=0 || stricmp(aut->nome,sobrenome)!=0))
			{
				aut=aut->prox;
			}
			
			if(aut!=NULL)
			{
				naut = new TpListaAutor;
				naut->autor=aut;
				naut->prox=lv->lista;
				lv->lista=naut;
			}
			else
			{
				printf("Autor do livro nao encontrado\n");
			}
			
			i+=2;
		}

	return lv;
}
Descritor insereEditoraOrdenada (Descritor desc,TpEditora * ed)
{
	TpEditora * aux;
		if(desc.ini==NULL)
			{
				desc.ini=ed;
				desc.fim=ed;
			}
			else
			{
				if(stricmp(desc.ini->nome,ed->nome)>=0)
				{
					ed->prox=desc.ini;
					desc.ini=ed;
				}
				else
				{
					if(stricmp(desc.fim->nome,ed->nome)<=0)
					{
						desc.fim->prox=ed;
					}
					else
					{
						TpEditora * ant = desc.ini;
						aux= desc.ini->prox;
						while(stricmp(aux->nome,ed->nome)<0)
						{
							ant=aux;
							aux=aux->prox;
						}
						
						ed->prox=aux;
						ant->prox=ed;
					}
				}
			}
			return desc;
}

Descritor criarEditoras (TpAutor * autores)
{
	FILE * ptrb = fopen("livros.dat","rb+");
	Descritor desc=inicia(desc);
	Registro reg;
	TpEditora * ed;
	TpLivro * lv;
	rewind(ptrb);
	fread(&reg,sizeof(Registro),1,ptrb);
	while(!feof(ptrb))
	{
		if(reg.status==1)
		{
			ed= new TpEditora;
			strcpy(ed->nome,reg.editora);
			ed->prox=NULL;
			ed->lista=NULL;
			
			TpEditora * aux=desc.ini;
			while(aux!=NULL&&stricmp(aux->nome,ed->nome)<0)
			{
				aux=aux->prox;
			}
			
			if(aux!=NULL && stricmp(aux->nome,ed->nome)==0)
			{
				//ADICIONAR APENAS O LIVRO A EDITORA JA ENCONTRADA, QUE O PONTEIRO AUX ESTÁ APONTANDO
				lv= new TpLivro;
				lv=colocaAutores(lv,autores,reg);
				aux->lista=insereLivro(aux->lista,lv);
			}
			else
			{
				//ADICIONAR O LIVRO PARA A NOVA EDITORA ANTES DE INSERI-LA
				lv = new TpLivro;
				lv= colocaAutores(lv,autores,reg);
				ed->lista=lv;
				desc=insereEditoraOrdenada(desc,ed);
				desc.qtde++;
			
			}	
		}
		
		fread(&reg,sizeof(Registro),1,ptrb);
	}
		
	fclose(ptrb);
	return desc;
}

void criarBinario()
{
	Registro reg;
	FILE * ptr = fopen("livros.txt","r");
	FILE * ptrb = fopen("livros.dat","wb");
	
	if(ptr !=NULL && ptrb != NULL)
	{
		fscanf(ptr,"%[^|]|%[^|]|%[^|]|%d|%d",&reg.autores,&reg.titulo,&reg.editora,&reg.ano,&reg.paginas);
		while(!feof(ptr))
		{
			reg.status=1;
			fwrite(&reg,sizeof(Registro),1,ptrb);
			fscanf(ptr,"\n%[^|]|%[^|]|%[^|]|%d|%d",&reg.autores,&reg.titulo,&reg.editora,&reg.ano,&reg.paginas);
		}
	}
	else
	{
		printf("Erro ao abrir os arquivos\n");
	}
	

	fclose(ptr);
	fclose(ptrb);
}

void excluiAutores(TpLivro * lv)
{
	TpListaAutor *ex,*at;
	ex=lv->lista;
	at=lv->lista->prox;
	delete(ex);
	while(at!=NULL)
	{
		ex=at;
		at=at->prox;
		delete(ex);
	}
}
void excluirLivro(Descritor desci)
{
	system("cls");
	quadrado(1,1,120,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,118,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	char titulo[100];
	Registro reg;
	gotoxy(29,3);
	printf("Digite o nome do livro que deseja excluir");
	gotoxy(29,4);
	fflush(stdin);
	gets(titulo);
	FILE * ptrb = fopen("livros.dat","rb+");
	fread(&reg,sizeof(Registro),1,ptrb);
	while(!feof(ptrb)&&(stricmp(reg.titulo,titulo)!=0||reg.status!=1))
		fread(&reg,sizeof(Registro),1,ptrb);	
	
	if(feof(ptrb))
	{
		gotoxy(29,5);
		printf("Livro nao encontrado");
	}
	else
	{
		fseek(ptrb,ftell(ptrb)-sizeof(Registro),0);
		reg.status=-1;
		fwrite(&reg,sizeof(Registro),1,ptrb);
		gotoxy(29,5);
		printf("Livro Excluido do arquivo binario!!!");
		
		Descritor desc = desci;
		while(desc.ini!=NULL&&stricmp(reg.editora,desc.ini->nome)>0)
		{
			desc.ini=desc.ini->prox;
		}
		
		if(desc.ini!=NULL&&stricmp(reg.editora,desc.ini->nome)==0)
		{
			TpLivro * auxLv=desc.ini->lista;
			
			if(stricmp(reg.titulo,auxLv->titulo)==0)
			{
				if(auxLv->prox==NULL)
				{
					desc.ini->lista=NULL;
				}
				else
				{
					desc.ini->lista->prox->ant=NULL;
					desc.ini->lista=desc.ini->lista->prox;
				}
				excluiAutores(auxLv);
				delete(auxLv);
				gotoxy(29,6);
				printf("Livro removido da lista!!\n");
			}
			else
			{
				while(auxLv->prox!=NULL && stricmp(reg.titulo,auxLv->titulo)>0)
				{
					auxLv=auxLv->prox;
				}
				
				if(auxLv->prox!=NULL&&stricmp(reg.titulo,auxLv->titulo)==0)
				{
					auxLv->prox->ant=auxLv->ant;
					auxLv->ant->prox=auxLv->prox;
					excluiAutores(auxLv);
					delete(auxLv);
					gotoxy(29,6);
					printf("Livro removido da lista!!\n");
				
				}
				else
				{
					if(stricmp(reg.titulo,auxLv->titulo)==0)
					{
						auxLv->ant->prox=NULL;
						excluiAutores(auxLv);
						delete(auxLv);
						gotoxy(29,6);
						printf("Livro removido da lista!!\n");
					}
					else
					{
						gotoxy(29,6);
						printf("ERRO CRITICO!");
						gotoxy(29,7);
						printf("livro nao encontado na lista");
					}
				}
			
			}
		}
		else
		{
			gotoxy(29,6);
			printf("ERRO CRITICO");
			gotoxy(29,7);
			printf("Editora nao cadastrada na lista\n");
		}
	}
	getche();
	fclose(ptrb);
}


void exclusaoFisica()
{
	Registro reg;
	FILE * ptrb = fopen ("livros.dat","rb");
	FILE * ptrt = fopen ("temp.dat","wb");
	fread(&reg,sizeof(Registro),1,ptrb);
	
	while(!feof(ptrb))
	{
		if(reg.status!=-1)
		{
			fwrite(&reg,sizeof(Registro),1,ptrt);
		}
		fread(&reg,sizeof(Registro),1,ptrb);
	}
	fflush(stdin);
	fclose(ptrt);
	fclose(ptrb);
	remove("livros.dat");
	rename("temp.dat","livros.dat");
}

TpAutor* alterarNomeCHICO(Descritor desci,TpAutor * autores)
{
	system("cls");
	quadrado(1,1,80,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,78,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	gotoxy(27,25);
	char livro[100],nome[100],primeiro[100],segundo[100],completo[100],total[100],alterado[100],first[100],second[100];
	int i,j,k;
	gotoxy(29,3);
	printf("Digite o nome do livro que deseja alterar");
	gotoxy(29,4);
	fflush(stdin);
	gets(livro);
	Registro reg;
	FILE * ptrb = fopen("livros.dat","rb+");
	fread(&reg,sizeof(Registro),1,ptrb);
	while(!feof(ptrb)&&(stricmp(reg.titulo,livro)!=0||reg.status!=1))
		fread(&reg,sizeof(Registro),1,ptrb);
	if(!feof(ptrb))
	{
		Descritor desc = desci;
		while(desc.ini!=NULL && stricmp(reg.editora,desc.ini->nome)>0)
		{
			desc.ini=desc.ini->prox;
		}
		if(desc.ini!=NULL && stricmp(reg.editora,desc.ini->nome)==0)
		{
			TpLivro * auxLv = desc.ini->lista;
			while(auxLv!=NULL && stricmp(reg.titulo,auxLv->titulo)>0)
			{
				auxLv=auxLv->prox;
			}
			if(auxLv!=NULL && stricmp(reg.titulo,auxLv->titulo)==0)
			{
				TpListaAutor * auxLa = auxLv->lista;
				gotoxy(29,5);
				printf("Lista de autores desse livro:");
				int i=6;
				while(auxLa!=NULL)
				{
					gotoxy(29,i);
					printf("%s %s",auxLa->autor->sobrenome,auxLa->autor->nome);
					auxLa=auxLa->prox;
					i++;
				}
				gotoxy(29,i+1);
				i++;
				printf("PRESS ENTER");
				getche();
				while(i>=6)
				{
					gotoxy(29,i);
					printf("                             ");
					i--;
				}
				gotoxy(29,5);
				printf("Digite o sobrenome do autor que deseja alterar");
				gotoxy(29,6);
				fflush(stdin);
				gets(second);
				fflush(stdin);
				gotoxy(29,7);
				printf("Digite o primeiro nome do autor");
				gotoxy(29,8);
				gets(first);
				nome[0]='\0';
				strcat(nome,second);
				strcat(nome,", ");
				strcat(nome,first);
				gotoxy(29,9);
				printf("Digite o novo sobrenome do autor");
				gotoxy(29,10);
				fflush(stdin);
				gets(segundo);
				fflush(stdin);
				gotoxy(29,11);
				printf("Digite o novo nome do autor");
				gotoxy(29,12);
				fflush(stdin);
				gets(primeiro);
				alterado[0]='\0';
				strcat(alterado,segundo);
				strcat(alterado,", ");
				strcat(alterado,primeiro);
				
				i=0;
				while(i<strlen(reg.autores))
				{
					j=0;
					while(i<strlen(reg.autores)&&reg.autores[i]!=';')
					{
					
							completo[j]=reg.autores[i];
							j++;
						
						i++;
					}
					i++;
					completo[j]='\0';
					total[0]='\0';
					if(stricmp(completo,nome)==0)
					{
						strcat(total,alterado);
						if(i<strlen(reg.autores))
						{
							strcat(total,";");
						}
					}
					else
					{
						strcat(total,completo);
						if(i<strlen(reg.autores))
						{
							strcat(total,";");
						}
					}
					fseek(ptrb,ftell(ptrb)-sizeof(ptrb),0);
					strcpy(reg.autores,total);
					fwrite(&reg,sizeof(Registro),1,ptrb);
					auxLa = auxLv->lista;
					while(auxLa!=NULL&&(stricmp(auxLa->autor->nome,first)!=0 || stricmp(auxLa->autor->sobrenome,second)!=0))
						auxLa=auxLa->prox;
					if(auxLa!=NULL)
					{
						TpAutor * auxA = autores;
						while(auxA!=NULL&&(stricmp(auxA->nome,primeiro)!=0 || stricmp(auxA->sobrenome,segundo)!=0))
							auxA=auxA->prox;
							
						if(auxA!=NULL)
						{
							auxLa->autor=auxA;
							gotoxy(29,12);
							printf("Nome do autor alterado com sucesso!!");
						}
						else
						{
							TpAutor * NC = new TpAutor;
							NC->prox=NULL;
							strcpy(NC->nome,primeiro);
							strcpy(NC->sobrenome,segundo);
							autores=insereOrdenado(autores,NC);
							auxLa->autor=NC;
							gotoxy(29,12);
							printf("Autor desconhecido!");
							gotoxy(29,13);
							printf("Nao se preocupe,");
							gotoxy(29,14);
							printf("Adicionamos esse autor a lista de autores");
						}
						
						
					}
					else
					{
						gotoxy(29,8);
						printf("Autor nao encontrado na lista de autores desse livro");
					}
				}
				
			}
			else
			{
				gotoxy(29,8);
				printf("Livro nao encontrado na lista de livros da editora");
			}
			
		}
		else
		{
			gotoxy(29,8);
			printf("Editora nao encontrada na lista");
		}
		
	}
	else
	{
		gotoxy(29,4);
		printf("Livro nao encontado no arquivo bin");
	}
	getch();
	fclose(ptrb);
	return autores;
}
void mudaArquivo(Registro reg, FILE * ptrb, char concatena[100],char alterado[100])
{
	char aux[100],tudo[100];
	int i=0,j;
	tudo[0]='\0';
	while(i<strlen(reg.autores))
	{
		j=0;
		while(i<strlen(reg.autores)&&reg.autores[i]!=';')
		{
			aux[j]=reg.autores[i];
			i++;
			j++;
		}
		i+=2;
		aux[j]='\0';
		if(stricmp(aux,concatena)==0)
		{
			if(tudo[0]!='\0')
			{
				strcat(tudo," ");
			}
			strcat(tudo,alterado);
			if(i<strlen(reg.autores))
			{
				strcat(tudo,";");
			}
		}
		else
		{
			strcat(tudo,aux);
			if(i<strlen(reg.autores))
			{
				strcat(tudo,";");
			}
		}
	}
	strcpy(reg.autores,tudo);
	fseek(ptrb,ftell(ptrb)-sizeof(Registro),0);
	fwrite(&reg,sizeof(Registro),1,ptrb);
}
void alterarNomeLEANDRO(TpAutor * autores)
{
	system("cls");
	quadrado(1,1,80,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,78,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	gotoxy(27,25);
	char nome[100],sobrenome[100],concatena[100],tudo[100],first[100],second[100],aux[100],alterado[100];
	int i,j,k;
	gotoxy(29,3);
	printf("Digite o sobrenome do autor que deseja alterar");
	gotoxy(29,4);
	fflush(stdin);
	gets(second);
	gotoxy(29,5);	
	printf("Digite o nome do autor que deseja alterar");
	gotoxy(29,6);
	fflush(stdin);
	gets(first);
	
	TpAutor * auxA = autores;
	while(auxA!=NULL&&(stricmp(auxA->nome,first)!=0||stricmp(auxA->sobrenome,second)!=0))
	{
		auxA=auxA->prox;
	}
		
	if(auxA!=NULL)
	{
		gotoxy(29,7);
		printf("Digite o novo sobrenome do autor");
		gotoxy(29,8);
		fflush(stdin);
		gets(sobrenome);
		gotoxy(29,9);
		printf("Digite o novo nome do autor");
		gotoxy(29,10);
		gets(nome);
		TpAutor * auxB = autores;
		while(auxB!=NULL && (stricmp(auxB->nome,nome)!=0||stricmp(auxB->sobrenome,sobrenome)!=0))
			auxB=auxB->prox;
			
			if(auxB==NULL)
			{
				strcpy(auxA->nome,nome);
				strcpy(auxA->sobrenome,sobrenome);
				gotoxy(29,11);
				printf("Alterou com sucesso\n");
				concatena[0]='\0';
				strcat(concatena,second);
				strcat(concatena,", ");
				strcat(concatena,first);
				alterado[0]='\0';
				strcat(alterado,sobrenome);
				strcat(alterado,", ");
				strcat(alterado,nome);
				tudo[0]='\0';
				FILE * ptrb = fopen("livros.dat","rb+");
				FILE * ptrba = fopen("livros.dat","rb+");
				Registro reg;
				fread(&reg,sizeof(Registro),1,ptrb);
				while(!feof(ptrb))
				{
					if(reg.status!=-1)
					{
						i=0;
						while(i<strlen(reg.autores))
						{
							j=0;
							while(i<strlen(reg.autores)&&reg.autores[i]!=';')
							{
								
								aux[j]=reg.autores[i];
								j++;
								
								i++;
							}
							aux[j]='\0';
							i+=2;
							
							if(stricmp(concatena,aux)==0)
							{
								fseek(ptrba,ftell(ptrb),0);
								mudaArquivo(reg,ptrba,concatena,alterado);
							}
						}
						
					}
					fread(&reg,sizeof(Registro),1,ptrb);	
				}
				fclose(ptrba);
				fclose(ptrb);
			}
			else
			{
				gotoxy(29,11);
				printf("Ja possui um autor com esse nome\n");
			}
	}
	else
	{
		gotoxy(29,11);
		printf("Autor nao encontrado na lista dinamica\n");
	}
	getche();
}
void exibeLivrosEditoras(Descritor desci)
{
	system("cls");
	quadrado(1,1,120,25,4);
	quadrado(2,2,26,15,7);
	quadrado(28,2,118,24,4);
	gotoxy(8,7);
	printf("PRESS ESCAPE");
	gotoxy(8,8);
	printf("  TO EXIT");
	gotoxy(27,25);
	Descritor desc= desci;
	TpLivro *auxL;
	int i,j,k,pag=0,max=0;
	char op=' ';
	while(desc.ini!=NULL)
	{
		max++;
		desc.ini=desc.ini->prox;
	}
	desc=desci;
	while(op!=27&&op!=10)
	{
		i=3;
		j=0;
		k=0;
		desc=desci;
		while(desc.ini!=NULL&&j<4)
		{
			gotoxy(110,3);printf("Pag: %d",pag+1);
			if(k>=pag*4)
			{
				gotoxy(29,i);
				printf("Editora : [%s]",desc.ini->nome);
				i++;
				gotoxy(29,i);
				printf("Livros:");
				i++;
				auxL=desc.ini->lista;
				while(auxL!=NULL)
				{
					gotoxy(29,i);
					printf("[%s]",auxL->titulo);
					i++;
					auxL=auxL->prox;
				}
				i++;
				j++;
			}
			k++;
			desc.ini=desc.ini->prox;
		}
		
		fflush(stdin);
		op=getch();
		
		switch(op)
		{
			case 77:
				if(pag<max/4)
				pag++;
				break;
			case 75:
				if(pag>0)
				pag--;
				break;
		}
		
		j=3;
		while(j<24)
		{
			gotoxy(29,j);
			printf("                                                                                        ");
			j++;
		}
	}
	
}

void relatorios(Descritor editoras,TpAutor * pautor)
{	
	char op;
	do
	{
		system("cls");
		quadrado(1,1,80,25,4);
		quadrado(2,2,26,15,7);
		gotoxy(2,22);
		printf("Developed by CAUA");
		quadrado(28,2,78,24,4);
		gotoxy(3,3);
		printf("[A]- LIVROS POR AUTOR");
		gotoxy(3,4);
		printf("[B]- AUTORES SEM LIVROS");
		gotoxy(3,5);
		printf("[C]- LIVROS POR EDITORA");
		gotoxy(3,9);
		printf("[ESQ]- PARA SAIR");
		gotoxy(29,4);
		fflush(stdin);
		op=toupper(getche());
		
		switch(op)
		{
			case 'A':
				exibeLivrosAutores(editoras,pautor);
				getche();
				break;
			case 'B':
				exibeAutoresSemLivros(editoras,pautor);
				getche();
				break;
			case 'C':
				exibeLivrosEditoras(editoras);
				getche();
				break;
		}
		
	}while(op!=27);
}
