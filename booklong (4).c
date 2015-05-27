#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define LENGTH 10

struct data* root=NULL;
struct data {
	char last_name [LENGTH];
	char first_name[LENGTH];
	long number_1;
	long number_2;
	struct data* right;
	struct data* left;
	};

void uppercase(char* name)
{
name[0] = toupper(name[0]); 
}

void lowercase(char* name, int size)
{
int i;
for(i=0; i<size; i++)
  {
  name[i] = tolower(name[i]);
  }
}

void fill(struct data* record)
{
	printf("DANE\n");
	printf("Podaj imie: \n");
	scanf("%s", (*record).first_name);
	lowercase((*record).first_name, LENGTH);
	//fgets((*record).first_name, LENGTH, stdin);
	printf("Podaj nazwisko:\n");
	scanf("%s", (*record).last_name);
	lowercase((*record).last_name, LENGTH);
	//fgets((*record).last_name, LENGTH, stdin);
	printf("Podaj pierwszy numer telefonu: \n");
	scanf("%ld", &((*record).number_1));
	printf("Podaj drugi numer telefonu: \n");
	scanf("%ld", &((*record).number_2));
	(*record).right=NULL;
	(*record).left= NULL;
}

void create_root(struct data** root)
{
struct data *new=(struct data*)malloc(sizeof(struct data));
if(new==NULL)
	{
	printf("Nie udalo sie przydzielic pamieci.");
	return;
	}
else
	fill(new);
	*root=new;
}

void create_record(struct data** record)
{
struct data* new=(struct data*)malloc(sizeof(struct data));
if(new==NULL)
	{
	printf("Nie udalo sie przydzielic pamieci.");
	return;
	}
else
	{
	fill(new);
	*record=new;
	}
}

void print_record(struct data* record)
{
	uppercase((*record).last_name);
	puts((*record).last_name);
	lowercase((*record).last_name, LENGTH);
	uppercase((*record).first_name);
	puts((*record).first_name);
	lowercase((*record).first_name, LENGTH);
	printf("%ld \n", (*record).number_1);
	printf("%ld \n\n", (*record).number_2);
}

void insert(struct data** root, struct data* record)
{
	struct data* p=NULL;
	p=*root;
	while((*p).right!=record && (*p).left!=record)
		{
		if(strcmp((*record).last_name, (*p).last_name)==0  && strcmp((*record).first_name, (*p).first_name)==0 )
			{
			printf("Podana osoba juz isnieje. Czy zauktualizowac baze?\n 1) TAK 2) NIE\n");
			int rep;
			scanf("%d", &rep);
			if(rep==1)
				{
				(*p).number_1=(*record).number_1;
				(*p).number_2=(*record).number_2;
				}
  		free(record);
			}
			
		else if((*p).right==NULL && strcmp((*record).last_name, (*p).last_name)>0)
			(*p).right=record;
		else if ((*p).left==NULL && strcmp((*record).last_name, (*p).last_name)<0)
			(*p).left=record;
		else if( strcmp((*record).last_name, (*p).last_name)>0)
			p=(*p).right;
		else if( strcmp((*record).last_name, (*p).last_name)<0)
			p=(*p).left;
		else if( strcmp((*record).last_name, (*p).last_name)==0 && strcmp((*record).first_name, (*p).first_name)<0)
			p=(*p).left;
		else if( strcmp((*record).last_name, (*p).last_name)==0 && strcmp((*record).first_name, (*p).first_name)>0)
			p=(*p).right;
		}
}

void print_inorder( struct data* root)
{
	if(root!=NULL)
		{
		print_inorder((*root).left);
		uppercase((*root).last_name);
		puts((*root).last_name);
		lowercase((*root).last_name, LENGTH);
		uppercase((*root).first_name);
		puts((*root).first_name);
		lowercase((*root).first_name, LENGTH);
		printf("%ld \n", (*root).number_1);
		printf("%ld \n\n", (*root).number_2);
		print_inorder((*root).right);
		}
}
		
void find(struct data*root, char* last_name_x, char* first_name_x)
{
	if(root)
		{
		find((*root).left, last_name_x, first_name_x);
		if(strcmp((*root).last_name, last_name_x)==0 && strcmp((*root).first_name, first_name_x)==0)
			{
			printf("Szukany rekord:\n");
			uppercase(last_name_x);
			puts(last_name_x);
			uppercase(first_name_x);
			puts(first_name_x);
			printf("%ld \n", (*root).number_1);
			printf("%ld \n\n", (*root).number_2);
			return;
			}
		find((*root).right, last_name_x, first_name_x);
		}
}

struct data* min(struct data* root)
{
	if((*root).left)
		return min((*root).left);
	else
		return root;
}

struct data* max(struct data* root)
{
	if((*root).right)
		return max((*root).right);
	else
		return root;
}



void count(struct data*root, int* node)
{
	if(root)
		{
		count((*root).left, node);
		(*node)++;
		count((*root).right, node);
		}
}

int height(struct data* root)
{
if(root == NULL)
  {
  return 0;
  }
else
  {
  int height_l = height((*root).left);
  int height_r = height((*root).right);
  if(height_l>height_r)
    {
    return height_l+1;
    }
  else
    {
    return height_r+1;
    }
  }  
}

main()
{ 
  int s=1;
	int f=0;
  do{
      printf("Wybierz funkcje:\n");
      printf("1. dodaj rekord\n2. wypisz ksiazke telefoniczna\n3. wyszukaj\n4. minimum\n5. maksimum\n6. zlicz wezly\n7. policz wysokosc\n8. zakoncz program\n");
      
      scanf("%d", &f);
			
    switch(f)
      {
      case 1:
				if(s==1)
	  			{
	  			create_root(&root);
	 				if(root!=NULL)
	    			s++;
	  			}
				else
	  			{ 
	  			struct data* record=NULL;
	  			create_record(&record);
	  			insert(&root, record);
	  			}
				break;
      case 2:
				if(s==1)
	  			printf("Baza jest pusta, nie ma danych do wyswietlenia\n");
				else
	 			 print_inorder(root);
				break;
      case 3:
				if(s==1)
	 			 printf("Baza jest pusta\n");
				else
	 			 {
	 			 printf("Podaj nazwisko do znalezienia:\n");
	 			 char last_name_x[LENGTH];
	 			 scanf("%s", last_name_x);
	 			 lowercase(last_name_x, LENGTH);
				  printf("Podaj imie do znalezienia");
				  char first_name_x [LENGTH];
				  scanf("%s", first_name_x);
				  lowercase(first_name_x, LENGTH);
				  find(root, last_name_x, first_name_x);
				  }
				break;
      case 4:
				if(s==1)
				  printf("Baza jest pusta, minimum nie istnieje\n");
				else
				  {
				  printf("MIN\n");
				  struct data*minimum=min(root);
				  print_record(minimum);
				  }
				break;
      case 5:
				if(s==1)
				  printf("Baza jest pusta, maksimum nie istnieje\n");
				else
	  			{
	 				printf("MAX\n");
	 				struct data*maximum=max(root);
	 				print_record(maximum);
				  }
				break;
      case 6:
				if(s==1)
	 			printf("Baza jest pusta, liczba wezlow: 0");
				else
				  {
					int node=0;
					int*p;
					p=&node;
				  count(root, p);
	 				printf("Liczba wezlow: %d\n", node);
	  			}
				break;
			case 7:
				if(s==1)
	 				printf("Baza jest pusta, liczba wezlow: 0\n");
				else
					{
					int h;
					h=height(root);
					printf("Wysokosc drzewa: %d\n", h);
					}
				break;
      }
    }
  while(f<8);
}
      
      
      
