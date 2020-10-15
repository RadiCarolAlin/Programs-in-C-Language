/*  We read a text from keyboard.
    The text will be divide in words depeneding on the space between them.
    The words will be only with numbers or only with letters (if in one of the word will be numbers and letters,that word will not be added to the list).
    The words will be append to a list.
    Function for reversing the items in the list.
    Function for lexicographic sorting.
    Function to add only words with letters from the main list to a secondary list.
    Function that counts the items in a list.
    Function for concatenating two lists.
 */




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum{
FALSE,TRUE
}Boleean;

typedef enum{
    CUVANT,NUMAR,GRESIT
}Tip;
typedef struct UnitateLexicala{
char continut[20];
Tip tip;
struct UnitateLexicala *next;
}UnitateLexicala;
typedef struct{
 UnitateLexicala *root;
}Lista;
void init(Lista *l);                                 // function for init a list
void adauga(Lista *l,UnitateLexicala *a);            // function for append element to a list
Boleean estecuvant(char s[]);                        //function for checking a word if it is written in letters
Boleean estenumar(char s[]);                         //function for checking a word if it is written in numbers
void Afisare(UnitateLexicala a);                     //function for print the structure
void AfisareL(Lista l);                              //function for print the list
UnitateLexicala* clona(UnitateLexicala p);           // function to makes clones of the elements in the structure
Lista inversareLista(Lista l);                       //function for reversing the items in the list
void sortareLista(Lista l);                          // function for lexicographic sorting
Lista cuvinteL(Lista l);                             //function to add only words with letters from the main list to a secondary list
int elementeL(Lista l);                              //function that counts the items in a list
Lista concatenareL(Lista l,Lista a);                 //Function for concatenating two lists.
int main()
{

 char str[250];
 gets(str);
 char *pch;
 pch=strtok(str," ");
 Lista l;
 Lista copie;
 init(&l);
 while(pch!=NULL)
 {
     UnitateLexicala *u=(UnitateLexicala*)malloc(sizeof(UnitateLexicala));
     strcpy(u->continut,pch);
     if(estecuvant(u->continut)==TRUE)
     {
         u->tip=CUVANT;
     }
     else if(estenumar(u->continut)==TRUE)
     {
         u->tip=NUMAR;
     }
     else
     {
         u->tip=GRESIT;
     }
     u->next=NULL;
    adauga(&l,u);
    pch=strtok(NULL," ");
 }
 AfisareL(l);
 printf("\n **********");
 copie=inversareLista(l);
 AfisareL(copie);
 printf("\n **********");
 sortareLista(l);
 AfisareL(l);
 Lista cuvinte;
 cuvinte=cuvinteL(l);
 AfisareL(cuvinte);
 int s=elementeL(l);
 printf(" \n %d",s);
 printf("\n ***********************************");
 Lista concatenare;
 concatenare=concatenareL(l,cuvinte);
 AfisareL(concatenare);
}
void init(Lista *l)
{
    l->root=NULL;
}
void adauga(Lista *l,UnitateLexicala *a)
{

        if(l->root!=NULL)
        {
            a->next=l->root;
            l->root=a;
            //printf("adaugare intermediara %s %s\n",l->root->continut,l->root->next->continut);
        }
        else
        {
            //printf("adaugare initiala \n");
            l->root=a;
        }
}
Boleean estecuvant(char s[])
{
    int k=0;
    for(int i=0;i<strlen(s);i++)
    {
        if((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))
        {
            k++;
        }
    }
    if(k==strlen(s))
            return TRUE;
        else
            return FALSE;
}
Boleean estenumar(char s[])
{
    int k=0;
    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]>='0'&&s[i]<='9')
        {
            k++;
        }
    }
    if(k==strlen(s))
            return TRUE;
        else
            return FALSE;
}
void Afisare(UnitateLexicala a)
{
    printf("\n %s %s",a.continut,a.tip==CUVANT?"CUVANT":"NUMAR");
}
void AfisareL(Lista l)
{
    UnitateLexicala *x=l.root;
    while(x!=NULL)
    {
        Afisare(*x);
        x=x->next;
    }
}
UnitateLexicala* clona(UnitateLexicala p)
{
  UnitateLexicala* u=(UnitateLexicala*)malloc(sizeof(UnitateLexicala));
  strcpy(u->continut,p.continut);
  u->tip=p.tip;
  u->next=NULL;
  return u;
}
Lista inversareLista(Lista l)
{
   Lista invers;
   init(&invers);
   UnitateLexicala *x=l.root;
    while(x!=NULL)
    {
        adauga(&invers,clona(*x));
        x=x->next;
    }
    return invers;
}
void sortareLista(Lista l)
{
    Boleean esteSortat=FALSE;
    while(esteSortat==FALSE)
    {
        esteSortat=TRUE;
        UnitateLexicala *x=l.root;
        while(x->next!=NULL)
        {
            if(strcmp(x->continut,x->next->continut)>0)
            {
                UnitateLexicala aux;
                strcpy(aux.continut,x->continut);
                aux.tip=x->tip;
                strcpy(x->continut,x->next->continut);
                x->tip=x->next->tip;
                strcpy(x->next->continut,aux.continut);
                x->next->tip=aux.tip;
                esteSortat=FALSE;
            }
            x=x->next;
        }
    }

}
Lista cuvinteL(Lista l)
{
    Lista cuvinte;
    init(&cuvinte);
    UnitateLexicala*x=l.root;
    while(x!=NULL)
    {
        if(x->tip==CUVANT)
        {
            adauga(&cuvinte,clona(*x));
        }
        x=x->next;
    }
    return cuvinte;
}
int elementeL(Lista l)
{
    int k=0;
    UnitateLexicala*x=l.root;
    while(x!=NULL)
    {
       k++;
       x=x->next;
    }
    return k;
}
Lista concatenareL(Lista l,Lista a)
{
    Lista concatenat;
    init(&concatenat);
    UnitateLexicala *x=l.root;
    while(x!=NULL)
    {
        adauga(&concatenat,clona(*x));
        x=x->next;
    }
    UnitateLexicala *y=a.root;
    while(y!=NULL)
    {
        adauga(&concatenat,clona(*y));
        y=y->next;
    }
    return concatenat;
}


