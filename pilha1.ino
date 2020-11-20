/*

UFV - Universidade Federal de Viçosa

Trabalho apresentado como parte das exigências da disciplina Algoritmos e Estruturas de Dados

Alunos: João Lucas Mayrinck D'Oliveira e Jeanluca Martins
Matriculas: 6320 e 5960

*/

//Carrega a biblioteca LiquidCrystal
#include <stdio.h>
#include <stdlib.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(4, 5, 3, 2, 1, 0);

byte pinosL[]  = {6,7,8,9};

byte pinosC[] = {10,11,12,13};

char teclas[4][4] =  {{'1','2','3','A'},
                      {'4','5','6','B'},
                      {'7','8','9','C'},
                      {'*','0','#','D'}};

Keypad teclado = Keypad( makeKeymap(teclas), pinosL, pinosC, 4, 4);  

typedef struct saluno
{
  int mat;
  int bol;
  int veg;
  char nome[40],curso[30];
  float saldo;
}aluno;

typedef struct sno
{
  aluno info;
  struct sno *next;
}no;


no* topo = NULL;
int bol=0,veg=0,vebol=0,vis=0,viveg=0,n=0;
aluno r[11]; //Registro de alunos
char matricula[5];
int i=0,j;

//Funções
void limp(); //limpa a tela
int cmp(char c[]);// retorna o comprimento de c
void cpy(char x[], char *y);// copia a string x para a y
int igual(char x[],char y[]);// verifica de a string x eh igual a y
int vaz(no *pon);// verifica se a pilha esta vazia
void freeall(no**pon); //Desempilha e faz a contagem. 
int consulta(char MatDigitada[]); //consulta o banco de dados e retorna a localização da matricula
void empilhar(no** ptrPilha, char MatDigitada[]); //adiciona pessoas a pilha
void inicializar(aluno r[]); //Inicializa o registro de alunos com dados de alunos

void limp() //Limpa a tela
{
    lcd.clear();
}

int cmp(char c[]) // Funcao que mede comprimento de strings.
{
    int i;
    for(i=0; c[i]!='\0'; i++);
    return i;
}

void cpy(char x[], char *y) // Funcao que copia x em y; 
{
    int i,j;

    for(i=0;i<cmp(x);i++)
    y[i]=x[i];

    y[cmp(x)]='\0';
}

int igual(char x[],char y[]) // Funcao que diz se 2 strings sao iguais.
{
    int i,j,k;

    if(cmp(x)!=cmp(y))
    {
        return 0;
    }

    j=cmp(x);
    
    for(i=0;((i<j)&&(x[i]==y[i]));i++);   

    if(i==j)
    {
      return 1;
    }
    else
    {
        return 0;
    }    
}

int vaz(no *pon)
{
  if(pon==NULL)
  return 1;
  
  return 0;
}

int consulta(char MatDigitada[])
{
   int i;
   for (i = 0; i < 11; i++)
   {
       if(atoi(MatDigitada) == r[i].mat)
       {
          return i;
       }
   }
  return -1;
}

void inicializar(aluno r[])
{
    
    cpy("Joao Lucas Mayrinck D Oliveira",r[0].nome);
	r[0].mat = 6320;
	cpy("Sistemas de Informacao",r[0].curso);
	r[0].saldo = 23.50;
	r[0].bol=1; 
    r[0].veg=0;

	cpy("Jeanluca Martins",r[1].nome);
	r[1].mat = 5960;
	cpy("Sistemas de Informacao",r[1].curso);
	r[1].saldo = 0;
	r[1].bol=1;
    r[1].veg=0;

	cpy("Amanda Aparecida",r[2].nome);
	r[2].mat = 5430;
	cpy("Nutricao",r[2].curso);
	r[2].saldo = 0;
	r[2].bol=1;
	r[2].veg=0;

	cpy("Pedro Olveira Silva",r[3].nome);
	r[3].mat = 3555;
	cpy("Ciencias Biologicas",r[3].curso);
	r[3].saldo = 4.50;
	r[3].bol=0;
	r[3].veg=1;

	cpy("Thiago Ferreira",r[4].nome);
	r[4].mat = 3410;
	cpy("Quimica",r[4].curso);
	r[4].saldo = 23.50;
	r[4].bol=0;
    r[4].veg=1;

	cpy("Cicera Vieira",r[5].nome);
	r[5].mat = 1234;
	cpy("Administracao",r[5].curso);
	r[5].saldo = 21.0;
	r[5].bol=1; 
	r[5].veg=1;

	cpy("Erica Martins",r[6].nome);
	r[6].mat = 7584;
	cpy("Engenharia Civil",r[6].curso);
	r[6].saldo = 3.50;
	r[6].bol=1; 
	r[6].veg=1;

	cpy("Iuri Alves Beltrao",r[7].nome);
    r[7].mat = 6381;
    cpy("Sistemas de Informacao",r[7].curso);
    r[7].saldo = 33.50;
    r[7].bol=0;
    r[7].veg=1;
    
    
    cpy("Kaio Costa",r[8].nome);
	r[8].mat = 1297;
	cpy("Ciencias Contabeis",r[8].curso);
	r[8].saldo = 24.0;
	r[8].bol=0; 
	r[8].veg=0;

	cpy("Stefani Kaline Leonel Dias",r[9].nome);
	r[9].mat = 4702;
	cpy("Sistemas de Informacao",r[9].curso);
	r[9].saldo = 12.50;
	r[9].bol=0; 
	r[9].veg=0;

	cpy("Geovana Helena Ribeiro Araújo",r[10].nome);
    r[10].mat = 6287;
    cpy("Agronomia",r[10].curso);
    r[10].saldo = 3.90;
    r[10].bol=0;
    r[10].veg=0;
}


void empilhar(no** ptrPilha, char MatDigitada[])
{
	int pos;
  	no *q;
  
  	q = (no*) malloc (sizeof(no));
  
  	
  	if (*ptrPilha != NULL)
    {
    	if (((*ptrPilha)->info).mat == atoi(MatDigitada))
    	{ 
        	lcd.print("Refeiçao ja Efetuada");
        	return;
        }
    }
  
    pos = consulta(MatDigitada);
	if (pos >= 0)
	{
		
      if(r[pos].bol==1)
      {
		lcd.print(r[pos].nome);
        lcd.print(" R$:");
      	lcd.print(r[pos].saldo);
      	lcd.setCursor(0, 1);
      	lcd.print(r[pos].curso);
        
		if (r[pos].bol == 1)
		{
			lcd.print(" Bolsista");
		}
		if (r[pos].veg == 1)
		{
			lcd.print(" Veg.");

        }
        
        if (q != NULL)
		{
			q->next = *ptrPilha;
		 	*ptrPilha = q;
			q->info = r[pos];
      	}
      }
		else if (r[pos].saldo >= 1.90)
		{
			
			r[pos].saldo = r[pos].saldo - 1.90;
          
         	lcd.print(r[pos].nome);
      		lcd.print(" R$:");
      		lcd.print(r[pos].saldo);
          	
          	if (r[pos].saldo >= 1.90 && r[pos].saldo <= 10.0)
			{
          		lcd.print("(Final)");	
			}
          
      		lcd.setCursor(0, 1);
      		lcd.print(r[pos].curso);
			if (r[pos].bol == 1)
			{
				lcd.print(" Bolsista");
			}
			if (r[pos].veg == 1)
			{
				lcd.print(" Veg.");
			}
			
			if (q != NULL)
			{
				q->next = *ptrPilha;
			    *ptrPilha = q;
		     	q->info = r[pos];
			}
		}else {
		    	lcd.print ("Saldo insuficiente\n");
          		free(q);
				return;
			}
	  }else {
	  		
      			if(igual(MatDigitada,"001"))
                {
                  lcd.print("Visitante");
                  (q->info).bol=-1;
                  (q->info).veg=-1;
                }
      			else if(igual(MatDigitada,"002"))
                {
                  lcd.print("Visitante Vegetariano");
                  (q->info).bol=-1;
                  (q->info).veg=1;
                }
      			else
      			{
   					lcd.print("Voce digitou: ");
                  	lcd.print(MatDigitada);
                  return;
      			}
      	 		q->next = *ptrPilha;
	         	*ptrPilha = q;
		     	(q->info).mat = atoi(MatDigitada);
      
	  }
	}

void freeall(no**pon) //Desempilha e faz a contagem. 
{
  no* aux;
  
  aux=(*pon);//ponteiro auxiliar
  
  while(aux!=NULL) //Enquanto a pilha n estiver vazia ele faz a contagem e vai tirando os nós da pilha
  {
  	
    if((aux->info).mat==001) //Se ao inves de curso o campo contiver apenas a letra , significa que é um vistante. Logo aumenta-se 1 no contador vis
    {
      	vis+=1;
    }
    else if((aux->info).mat==002) //Se o campo curso contiver apenas a letra C, significa que é um visitante vegetariano. Logo acrescenta-se 1 ao contador viveg
   	{
    	viveg+=1;
      	vis+=1;
      	veg+=1;
    }
  	
    else if((aux->info).bol==0 && (aux->info).veg==0)
    {
    	n+=1;
    }
    else if((aux->info).bol==1 && (aux->info).veg==1)
    {
    	bol+=1;
      	veg+=1;
      	vebol+=1;
    }
    else if((aux->info).bol==1)
    {
      	bol+=1;
    }
    else if((aux->info).veg==1)
    {
      	veg+=1;
    }
    
    free(aux); //O nó atual é retirado da pilha e liberado da memoria.
    (*pon)=(*pon)->next; //O ponteiro externo passa a apontar para o proximo nó
    aux=(*pon); //O auxiliar passa a apontar para o novo topo
  }
  
}
  
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  inicializar(r);
  
}

void loop()
{
  char tecla_p = teclado.getKey();
  
  if(tecla_p)
  {
    
    if(tecla_p=='*')
    {
      	limp();
      	
      	i--;
      
      	if(i>4 || i <0)
        {
        	i=0;
        }
      
      	matricula[i]='\0';
      
      	lcd.print(matricula);
        
    }
    else if(tecla_p=='#')
    {
      	limp();
      
     	if(igual(matricula,"0"))
        {    
          
        	freeall(&topo);
          
          	lcd.print("Ve. Bol. BolV. Vi. VisV. Norm. TT.");
          	lcd.setCursor(0, 1);
            lcd.print(veg);
            lcd.print("   ");
            lcd.print(bol);
            lcd.print("    "); 
            lcd.print(vebol);
            lcd.print("     ");
            lcd.print(vis);
            lcd.print("   ");
          	lcd.print(viveg);
            lcd.print("     ");
            lcd.print(n);
            lcd.print("     ");
          	lcd.print((veg+bol+vis+n)-(viveg+vebol));
          	
          	bol=0;
          	veg=0;
          	vebol=0;
          	vis=0;
          	viveg=0;
            n=0;
         
          	
        }
      	else
        {
          	empilhar(&topo,matricula);
        }
      	i=0;
       	matricula[i]='\0';
    }
    else
    {
      	
      	limp();
      
    	matricula[i]=tecla_p;
    	i++;
      
      	if(i>4 || i <0)
        {
        	i=0;
        }
      
      	matricula[i]='\0';
      	lcd.print(matricula);
    }
    
  }else
  {
    if(matricula[0]=='\0')
    { 
    	lcd.scrollDisplayLeft();//Faz a rolagem do texto
    	delay(5);
    }
  }

}