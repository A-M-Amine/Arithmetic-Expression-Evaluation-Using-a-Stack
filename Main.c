#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef enum Bool
{
    false, true
} Bool;

typedef struct Element
{
    char info[50];
    struct Element *svt;
} Element, *Pile;

/*les primitives de la pile*/

Pile initPile()
{
    return NULL;
}

Pile empiler(Pile sommet, char *x)
{
    Element *p = (Element*)malloc(sizeof(Element));
    if (p == NULL)
    {
        printf("erreur allocation dynamique");
        exit(EXIT_FAILURE);
    }
    strcpy(p->info,x);
    p->svt = sommet;

    return p;
}

Pile depiler(Pile sommet, char *x)
{
    Element *p = sommet;
    sommet = sommet->svt;
    strcpy(x,p->info);
    free(p);

    return sommet;
}

char* sommetPile(Pile sommet)
{
    return sommet->info;
}

Bool pileVide(Pile sommet)
{
    if (sommet == NULL)
        return true;
    else
        return false;
}


Pile afficherPile(Pile sommet)
{
    Pile p = initPile();
    char tmp[50];

    while (!pileVide(sommet))
    {
        sommet = depiler(sommet, tmp);
        printf("%s ",tmp);
        p = empiler(p, tmp);
    }
    printf("\n");
    while (!pileVide(p))
    {
        p = depiler(p, tmp);
        sommet = empiler(sommet, tmp);
    }

    return sommet;
}

// - - - - - - - - - - - - - -


int nombre (char x )  // fct qui verifier c'est un caractere donne est un nbr
{
    switch (x)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return 0 ;
        break ;
    default :
        return 1 ;
    }
}

int symb_reel(char x)  // fct qui verifier les symboles d'un nbr reel
{
    switch (x)
    {
    case 'E':
    case 'e':
    case '.':
        return 0 ;
        break ;
    default :
        return 1 ;
    }
}


int operateur_car(char x )   // fct qui verifier c'est un caractere donne est un operateur
{
    switch (x)
    {
    case '+':
    case '-':
    case '%':
    case '/':
    case '*':
        return 0 ;
        break ;
    default :
        return 1 ;
        break ;
    }
}



int operateur(char *t)  //fct qui determine si t est un operateur
{
    if(operateur_car(t[0]) == 1 || t[0]== '(' || t[0]== ')')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int operande(char *t) //fct qui determine si t est un operande
{
    if(isdigit(t[0]))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

char* codification(char x)  // fonction qui cree un code pour les symboles d'une expression
{
    switch(x)
    {
    case '(' :
        return "a";
        break ;
    case ')' :
        return "b";
        break ;
    case '*' :
        return "c";
        break ;
    case '/' :
        return "d";
        break ;
    case '%' :
        return "f";
        break ;
    case '+' :
        return "g";
        break ;
    case '-' :
        return "h";
        break ;
    }
}

char* decode(char *t)
{
    switch (t[0])
    {
    case 'c':
    case 'd':
    case 'f':
    case 'g':
    case 'h':
        return "+";
        break;
    default :
        return "z";
        break ;
    }
}


int priorite(char *t) //fct qui retourne la proirite d'un operateur
{

    switch(t[0])
    {
    case 'a' :
        return 6;
        break ;
    case 'b' :
        return 5;
        break ;
    case 'c' :
        return 4;
        break ;
    case 'd' :
        return 3;
        break ;
    case 'f' :
        return 2;
        break ;
    case 'g' :
        return 1;
        break ;
    case 'h' :
        return 0;
        break ;
    }
}




int verifie (char x)
{
    switch(x)
    {
    case '(' :
    case ')' :
    case '.' :
    case 'e' :
    case 'E' :
        return 0 ;
    }
    if (nombre(x)!=0 && operateur_car(x)!=0)
    {
        return 1;
    }
    else
    {
        return 0 ;
    }
}

void verf_reel(char *x,int *r,int *e,int *pos)  // verifie si une chaine x represente un nbr reel
{
    int L = strlen(x);

    int i=0;

    while(i<L)
    {
        if(x[i] == '.')
        {
            *r = 1;
        }
        if(x[i] == 'E' || x[i] == 'e')
        {
            if(*e == 0)
            {
                *pos = i;
            }
            *e = 1;
        }

        i++;
    }
}


void vider_chaine(char *t) // fonction qui vider une chaine
{
    int L = strlen(t);
    int i;
    for(i=0; i<=L; i++)
    {
        t[i] = '\0';
    }
}


char* Extrait(char ch1[], char ch2[],int i,int n)  //fct qui extrait une chaine apartir une autre chaine
{
    char* chtemp=ch2;
    int j=0;
    while(j<n)
    {
        chtemp[j]=ch1[i];
        i++;
        j++;
    }
    return chtemp;
}

float conv_nb(char *y) // fct qui faire la conversion
{
    int L = strlen(y);
    int e=0,r=0,pos=0;
    int i=0;
    int Expo;
    char tmp[50];
    int cpt=0;
    float nb;

    verf_reel(y,&r,&e,&pos);

    if(e == 0)
    {
        sscanf(y, "%f", &nb);
    }
    else
    {
        vider_chaine(tmp);
        strcpy(tmp,Extrait(y,tmp,0,pos+1));
        sscanf(tmp, "%f", &nb);
        printf(" %f \n",nb);
        pos++;
        strcpy(tmp,Extrait(y,tmp,pos,L));
        sscanf(tmp, "%d",&Expo);
        nb = nb * pow(10,Expo);
    }

    return nb;

}

float operate(float x1,float x2,char *op) // fonction qui retourne le resultat d'une operation sur 2 nbrs reel
{
    switch(op[0])
    {
    case 'c' :
        return x1*x2;
        break ;
    case 'd' :
        return x1/x2;
        break ;
    case 'f' :
        return fmod(x1,x2);
        break ;
    case 'g' :
        return x1+x2;
        break ;
    case 'h' :
        return x1-x2;
        break ;
    }
}

void operation(char *x1,char *x2,char *op,char *RSLT) // fct operation qui calcul le resultat d'une operation
{
    float z1,z2,rez;
    //
    z1 = conv_nb(x1);
    z2 = conv_nb(x2);
    rez = operate(z1,z2,op);

    sprintf(RSLT, "%f",rez);

    return RSLT;
}




Pile Trans_post_fixee(char **V,int L)  // fct de transformation vers la forme postfixée
{
    Pile P = initPile();
    Pile R = initPile();

    char x[20];

    int i;
    for(i=0; i<L; i++)
    {
        if(operande(V[i]) == 0)
        {
            R = empiler(R,V[i]);
        }
        else
        {
            if(operateur(decode(V[i])) == 0)
            {
                while(!pileVide(P) && operateur(decode(sommetPile(P)))  == 0 && ( priorite(V[i]) <= priorite(sommetPile(P)) ) )
                {
                    P = depiler(P,x);
                    R = empiler(R,x);
                }
                P = empiler(P,V[i]);
            }
            else
            {
                if(strcmp(V[i],"a") == 0)
                {
                    P = empiler(P,V[i]);
                }
                else
                {

                    if(strcmp(V[i],"b") == 0)
                    {
                        while(!pileVide(P) && strcmp(sommetPile(P),"a") != 0 )
                        {
                            P = depiler(P,x);
                            R = empiler(R,x);
                        }
                        P = depiler(P,x);
                    }
                }

            }

        }
    }
    while(!pileVide(R))
    {
        R = depiler(R,x);
        P = empiler(P,x);
    }

    return P;
}




Pile evaluation_PF(Pile P)  // fct  d'evaluation  d'une forme postfixeé
{
    char x[50],x1[50],x2[50];
    char Res[50];
    Pile R = initPile();
    float z1,z2,rez;
    while(!pileVide(P))
    {
        P = depiler(P,x);
        if(isdigit(x[0]))
        {
            R = empiler(R,x);
        }
        else
        {
            R = depiler(R,x1);
            R = depiler(R,x2);
            operation(x1,x2,x,Res);
            P = empiler(P,Res);
        }

    }
    return R;
}




int valide (char *t) // fct qui verifie une expression arithmetique
{
    int i=0 ;
    /**verfie si ellle conetient les symboles de l expression arthmetique **/
    int l=strlen(t);
    int b=0 ;
    while (i<l && b==0 )
    {
        if (verifie (t[i])==1)
            b=1;
        i++ ;
    }
    if(b==1)
    {
        printf ("\n\t SYNTAX ERROR 1  ") ;
        return 1 ;
    }
    i=0 ;
    //  test si le nombre  est signé
    if (t[0]=='-' || t[0]=='+' )
        i=1 ;
    /**verfie si le peremeir caractere est un nombre ou une parenthese ouverte **/

    if ( nombre(t[i])==1 && t[i]!='(')
    {
        printf ("\n\t SYNTAX ERROR 2 ") ;
        return 1  ;
    }

    int cpt=0; // compteur pour controleer les parenthéese saisie par l utilisateur
    int nbr ; // compteur pour controler le e  d 'un nombre saisie par l utilisateur
    int nbv=0; // compteur pour controler la virgule d'un nombre saisie par l'utilisateur
    int L2 = strlen(t);

    while (i<L2)
    {
        /**verfie si il y a un nombre  avant le e **/
        if (t[i]=='e' ||  t[i]=='E')
        {
            nbr++ ;
            if(nombre(t[i-1])==1 )
            {
                printf ("\n\t SYNTAX ERROR 4  ") ;
                return 1 ;
            }
            if(nombre(t[i+1])==1 && t[i+1]!='+' && t[i+1]!='-')
            {
                printf ("\n\t SYNTAX ERROR 4 ");
                return 1 ;
            }
            else
            {
                if (t[i+1]=='+'  ||  t[i+1]=='-')
                    i=i+2 ;

            }

        }

        /** verfie si  il y a un nombre apres et avant la virgule **/
        if (t[i]=='.' )
        {
            nbv++;
            if (nombre(t[i-1])!=0 && nombre(t[i+1])!=0)
            {
                printf ("\n\t SYNTAX ERROR 3 ") ;
                return 1 ;
            }
        }

        if (t[i]=='(')
            cpt++ ;
        if (t[i]==')')
            cpt-- ;
        /**verifie s il y a deux operateur qui ce suive**/
        if (operateur_car(t[i])==0  )
        {
            if(nbv>1 && nbr>1)
            {
                printf ("\n\t SYNTAX ERROR 5") ;
                return 1 ;
            }
            nbv=0;
            nbr=0 ;
            if(nombre(t[i-1])==1 && t[i-1] != ')' )
            {
                printf ("\n\t SYNTAX ERROR 6");
                return 1 ;
            }
            else
            {

                if (t[i+1]=='%'|| t[i+1]=='*'|| t[i+1]=='/')
                {
                    printf ("\n\t SYNTAX ERROR 7  ") ;
                    return 1 ;
                }
            }
        }

        i++ ;
    }
    /**verifie si le derneir element est un operateur **/
    if (operateur_car(t[i])==0)
    {
        printf ("\n\t SYNTAX ERROR 8 ") ;
        return 1 ;
    }
    /**verfie si le nombre de parenthese ouverante est egale au nombre de parenthese fermante**/
    if (cpt!=0)
    {
        printf ("\n\t SYNTAX ERROR 9 ") ;
        return 1 ;
    }
    /**Testons  le sens des parenthèses et les parenthèses vide du genre 2+() est terminé. **/

    return 0 ;
}



int tab(char **V,char *t) // fonction de creation de tableau apartir de la chaine de caractere
{
    int i,j=0;

    int cpt=0; // compteur de chaine tmp

    int L=strlen(t);

    char tmp[L]; // une chaine intermediere pour sauvgarder les nbrs

    i=0;

    while(i<L)
    {
        if(nombre(t[i]) == 0 || symb_reel(t[i]) == 0 )  // verifie si le caractere est un nbr reel ou entier
        {
            while( ((nombre(t[i]) == 0) || symb_reel(t[i]) == 0) && i<L)
            {
                tmp[cpt] = t[i];
                i++;
                cpt++;
            }
            cpt=0;
            strcpy(V[j],tmp);
            vider_chaine(tmp);
            j++;
        }
        else        // si le caractere n'est pas un nbr la codification
        {

            strcpy(V[j],codification(t[i]));

            j++;
            i++;

        }
    }
    return j;

}




void creation_fichier(int n,int m)  // fct qui creer un fichier d'expression arithmetique
{
    FILE *F;
    char ch[m];
    int i=0;
    F=fopen("BOI.txt","w");
    while(i<n)
    {
        printf("Donner une expression : ");
        scanf("%s",ch);
        fprintf(F,"%s\t",ch);
        i++;
    }
    fclose(F);
}

void terminate()        // fct qui controle la fermeture de prog
{
    system("cls");
    printf("Goodbye");
    system("color a0");
    exit(EXIT_SUCCESS);
}


int main()
{
    int a;
    int n=50;
    system("color e0");
    do
    {
        printf("AHMANE Mohamed Amine , Azzouz Mouhmed Soheyb \n");
        printf("Bienvenu(e) : \n");
        printf("1- Evaluation a partir de saisie \n");
        printf("2- Evaluation a partir d'un fichir \n");
        printf("3- Exit\n");
        printf("           *** P.S Le programme n'acceptera pas les valeurs negatives\n");
        printf("           Votre choix : ");
        scanf("%d",&a);

    }
    while((a > 3)||(a < 1));

    switch(a)
    {
    case 1:
    {

        char *c ;
        c=(char*)malloc(sizeof(char)*n);
autre:
        printf("donner l'expression a lire : \n ");
        scanf("%s",c);
        int l=valide(c);
        if(l==1)
        {
            printf("donner une autre expression svp \n");

            goto autre;
        }
        else
        {
            printf ("cette expression est valide ! \n");
        }


        int i;
        int longeur;

        char **A =(char **)malloc(n*sizeof(char *));
        for(i=0; i<n; i++)
        {
            A[i] = (char *)malloc(n*sizeof(char));
        }

        longeur = tab(A,c);

        printf("Le tableau code : \n");

        for(i=0; i<longeur; i++)
        {
            printf("%s  ",A[i]);
        }

        printf("\n");

        Pile F = initPile();

        F = Trans_post_fixee(A,longeur);

        printf("La forme Postfixee : \n");

        afficherPile(F);

        Pile H = initPile();

        H = evaluation_PF(F);

        printf("le resultat final : ");

        afficherPile(H);

    }
    break;
    case 2:
    {
        int m;
        n = 50;
        char x[50];
        int i;
        int longeur=0;
        char era[50];
        Pile F,H;
        printf("Donner le nombre des experssions dans le fichier : ");
        scanf("%d",&m);

        creation_fichier(m,n);



        F=fopen("BOI.txt","r");


        fclose(F);

        F=fopen("BOI.txt","r");

        while(!feof(F))
        {
            vider_chaine(era);

            fscanf(F,"%[^\t]",&era);

            strcpy(x,era);


            char **A =(char **)malloc(n*sizeof(char *));

            for(i=0; i<n; i++)
            {
                A[i] = (char *)malloc(n*sizeof(char));
            }

            longeur = tab(A,x);

            printf("Le tableau code : \n");

            for(i=0; i<longeur; i++)
            {
                printf("%s  ",A[i]);
            }

            F = initPile();

            F = Trans_post_fixee(A,longeur);

            printf("\nLa forme Postfixee : \n");

            afficherPile(F);

            H = initPile();

            H = evaluation_PF(F);

            printf("le resultat final : ");

            afficherPile(H);

        }

        fclose(F);


    }
    break;
    case 3:
    {
        terminate();
    }
    break;
    }

    return 0;
}
