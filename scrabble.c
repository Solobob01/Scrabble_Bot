//Craciun Alexandru-Andrei Grupa 313CD

#include <stdio.h>
#include "./util/print_board.h"
#include "./util/scrabble.h"
#include <stdlib.h>
#include <string.h>

//in cadrul exercitiului se pot observa adaugari de \n si eliminari de \n.
//mi-am dat seama prea tarziu si a trb sa adaptez program la restul functiilor :-D

//functie care scrie cuvantul pe game_board
void scriere_matrice(char game_board[15][15],char word[100],int x,int y,int d)
{
    int j,cop_x,cop_y;
    j=0;
    cop_x=x;
    cop_y=y;
    if(d==1)
    {
        while(word[j]!='\n')
        {
            if(word[j]!='\n')
            {
                game_board[cop_x][cop_y]=word[j];
                cop_x++;
                j++;
            }
        }
    }
    else
    {
        while(word[j]!='\n')
        {
            if(word[j]!='\n')
            {
                game_board[cop_x][cop_y]=word[j];
                cop_y++;
                j++;
            }
        }
    }    
}

//functie care calculeaza scorul unui cuvant fara bonusuri
int calculator_scor_cuvant(char word[100])
{ 
    int valori[]={1 ,3 ,3 ,2 ,1 ,4 ,2 ,4 ,1 ,8 ,5 ,1 ,3 ,1 ,1 ,3 ,10 ,1 ,1 ,1 ,1 ,4 ,4 ,8 ,4 ,10};
    int j,scor_word;
    j=0;
    scor_word=0;
    while(word[j]!='\n')
    {
        scor_word+=valori[word[j]-'A'];
        j++;
    }
    return scor_word;
}

//functie care calculeaza scorul unui cuvant cu bonusul de tip YY
int calculator_scor_bonus_YY_cuvant(char word[100],int scor_word,char YY[4],int x,int y,int d)
{
    int lenght_word,j;
    lenght_word=strlen(word);
        if(strstr(word,YY)!=NULL && d==1)
            for(j=x;j<x+lenght_word-1;j++)
                if(bonus_board[j][y]==2)
                    scor_word=scor_word*(bonus_board[j][y]+1);
        if(strstr(word,YY)!=NULL && d==0)
            for(j=y;j<y+lenght_word-1;j++)
                if(bonus_board[x][j]==2)
                    scor_word=scor_word*(bonus_board[x][j]+1);
    return scor_word;
}

//functie care calculeaza scorul unui cuvant cu bonusul de tip XX
int calculator_scor_bonus_XX_cuvant(char word[100],int scor_word,char XX[4],int x,int y,int d)
{
    int lenght_word,j,k;
    lenght_word=strlen(word);
    j=0;
    if(d==1)
    {
        while(word[j]!='\n')
        {
            if(word[j]==XX[0] && word[j+1]==XX[1])
            {   
                for(k=x;k<x+lenght_word-1;k++)
                    if(bonus_board[k][y]==1)
                    {
                        scor_word=scor_word*(bonus_board[k][y]+1);
                    }
            }
            j++;
        }
    }
    else
    {
        while(word[j]!='\n')
        {
            if(word[j]==XX[0] && word[j+1]==XX[1])
            {   
                for(k=y;k<y+lenght_word-1;k++)
                {
                    if(bonus_board[x][k]==1)
                    {
                        scor_word=scor_word*(bonus_board[x][k]+1);
                    }
                }
            }
            j++;
        }
    }
    return scor_word;
}

//functie care gaseste cel mai optim cuvant de pus pe game_board
int verificare_posibilitate(char game_board[15][15],char words[100],int *x,int *y,int *d)
{
int i,j,output,x_0,y_0,d_0,x_1,y_1,d_1,check_0=0,check_1=0;
long unsigned int ct;
output=0;

//fiecare patratica pe orientarea d == 0
for(i=0;i<15;i++)
{
    for(j=0;j<15;j++)
    {
        next_piece0:
        //verifica ca prima litera din cuvant sa fie pe tabla
        if(game_board[i][j]==words[0])
        {
            //verifica ca cuvantul sa incapa pe tabla
            if(game_board[i][j+1]=='.' && (j + strlen(words))<=15)
            {
                //verifica ca cuvantul sa nu se suprapuna cu alte cuvinte
                for(ct=1;ct<strlen(words);ct++)
                {

                    //in caz contrar trece la urmatoarea patratica
                    if(game_board[i][j+ct]!='.')
                    {
                        j++;
                        goto next_piece0;
                    }    
                }

                //salveaza coordonatele pe orientarea d == 0
                x_0=i;
                y_0=j;
                d_0=0;

                //un checker care verifica daca se poate pune cuvantul pe orientarea d == 0
                check_0=1;
                output=1;

                //trece la urmatoarea orientare
                goto next;
            }
        }
    }
}
next:

//fiecare patratica pe orientarea d == 1
for(i=0;i<15;i++)
{
    for(j=0;j<15;j++)
    {
        next_piece1:

        //verifica ca prima litera din cuvant sa fie pe tabla
        if(game_board[i][j]==words[0])
        {

            //verifica ca cuvantul sa incapa pe tabla
            if(game_board[i+1][j]=='.' && (i + strlen(words))<=15)
            {

                //verifica ca cuvantul sa nu se suprapuna cu alte cuvinte
                for(ct=1;ct<strlen(words);ct++)
                {

                    //in caz contrar trece la urmatoarea patratica
                    if(game_board[i+ct][j]!='.')
                    {
                        j++;
                        goto next_piece1;
                    }
                }

                //salveaza coordonatele pe orientarea d == 1
                x_1=i;
                y_1=j;
                d_1=1;

                //un checker care verifica daca se poate pune cuvantul pe orientarea d == 1
                check_1=1;
                output=1;

                //trece la "puiul de sarpe IF"
                goto final;
            }
        }
    }
}
final:

//"puiul de sarpe IF"
//un mare sir de if care gaseste cea mai optima pozitie in functie de linii si coloane
if(check_0 == 1 && check_1 == 0)
{
    *x=x_0;
    *y=y_0;
    *d=d_0;
}
else if(check_0 == 0 && check_1 == 1)
{
    *x=x_1;
    *y=y_1;
    *d=d_1;
}
else if (check_0 == 1 && check_1 == 1)
{
    if(x_0 < x_1)
    {
        *x=x_0;
        *y=y_0;
        *d=d_0;
    }
    else if(x_1 < x_0)
    {
        *x=x_1;
        *y=y_1;
        *d=d_1;
    }
    else if (x_0 == x_1)
    {
        *x=x_0;
        if(y_0<y_1)
        {
            *y=y_0;
            *d=d_0;
        }
        else if(y_1 < y_0)
        {
            *y=y_1;
            *d=d_1;
        }
    }
}
return output;
}

//functie care gaseste cel mai optim cuvant de pus pe game_board in functie de scorul cuvantului
int verificare_posibilitate_5(char game_board[15][15],char XX[4],char YY[4],char words[100],int *x,int *y,int *d,int *scor_words)
{
int i,j,output=0;
long unsigned int ct,lenght_word;
int x_0,y_0,d_0,check_0=0,scor_words_0=0;
int x_1,y_1,d_1,check_1=0,scor_words_1=0;
lenght_word=strlen(words)-1;

//fiecare patratica pe orientarea d == 0
for(i=0;i<15;i++)
{
    for(j=0;j<15;j++)
    {
        next_piece0:

        //verifica daca inceputul cuvantului exista pe tabla
        if(game_board[i][j]==words[0])
        {
            //verifica daca cuvantul incape pe tabla
            if(game_board[i][j+1]=='.' && (j + lenght_word)<=15)
            {
                //verifica daca fiecare patratica in continuarea cuv este libera
                for(ct=1;ct<=lenght_word;ct++)
                {
                    if(game_board[i][j+ct]!='.')
                    {
                        //in caz contrar trece la urmatoarea patratica
                        j++;
                        goto next_piece0;
                    }    
                }

                //salveaza coordonatele pe orientarea d == 0
                x_0=i;
                y_0=j;
                d_0=0;
                output=1;

                //checker ca sa stim ca se poate pune cuvantul pe orientarea d == 0
                check_0=1;

                //se duce la urmatorul for pentru ca s-a gasit pozitia optima pe orientarea d == 0
                goto next;
            }
        }
    }
}
next:

//fiecare patratica pe orientarea d == 1
for(i=0;i<15;i++)
{
    for(j=0;j<15;j++)
    {
        next_piece1:

        //verifica daca inceputul cuvantului exista pe tabla
        if(game_board[i][j]==words[0])
        {
            //verifica daca cuvantul incape pe tabla
            if(game_board[i+1][j]=='.' && (i + lenght_word)<=15)
            {
                //verifica daca fiecare patratica in continuarea cuv este libera
                for(ct=1;ct<=lenght_word;ct++)
                {
                    if(game_board[i+ct][j]!='.')
                    {
                        //in caz contrar trece la urmatoarea patratica
                        j++;
                        goto next_piece1;
                    }
                }
                //salveaza coordonatele pe orientarea d == 1
                x_1=i;
                y_1=j;
                d_1=1;
                output=1;

                //checker ca sa stim ca se poate pune cuvantul pe orientarea d==1
                check_1=1;

                //se duce la u"sarpele IF" for pentru ca s-a gasit pozitia optima pe orientarea d==0
                goto final;
            }
        }
    }
}
final:

//"sarpele IF"
//un mare sir de if care gaseste cea mai optima pozitie in functie de scor,linii si coloane
if(check_0 == 1 && check_1 == 0)
{
    *x=x_0;
    *y=y_0;
    *d=d_0;
    scor_words_0=calculator_scor_cuvant(words);
    scor_words_0=calculator_scor_bonus_XX_cuvant(words,scor_words_0,XX,x_0,y_0,d_0);
    scor_words_0=calculator_scor_bonus_YY_cuvant(words,scor_words_0,YY,x_0,y_0,d_0);
    *scor_words=scor_words_0;
}
else if(check_0 == 0 && check_1 == 1)
{
    *x=x_1;
    *y=y_1;
    *d=d_1;
    scor_words_1=calculator_scor_cuvant(words);
    scor_words_1=calculator_scor_bonus_XX_cuvant(words,scor_words_1,XX,x_1,y_1,d_1);
    scor_words_1=calculator_scor_bonus_YY_cuvant(words,scor_words_1,YY,x_1,y_1,d_1);
    *scor_words=scor_words_1;
}
else if (check_0 == 1 && check_1 == 1)
{
    scor_words_0=calculator_scor_cuvant(words);
    scor_words_0=calculator_scor_bonus_XX_cuvant(words,scor_words_0,XX,x_0,y_0,d_0);
    scor_words_0=calculator_scor_bonus_YY_cuvant(words,scor_words_0,YY,x_0,y_0,d_0);
    scor_words_1=calculator_scor_cuvant(words);
    scor_words_1=calculator_scor_bonus_XX_cuvant(words,scor_words_1,XX,x_1,y_1,d_1);
    scor_words_1=calculator_scor_bonus_YY_cuvant(words,scor_words_1,YY,x_1,y_1,d_1);
    if(scor_words_0 < scor_words_1)
    {
        *x=x_1;
        *y=y_1;
        *d=d_1;
        *scor_words=scor_words_1;
    }
    else if (scor_words_1 < scor_words_0)
    {
        *x=x_0;
        *y=y_0;
        *d=d_0;
        *scor_words=scor_words_0;
    }
    else if (scor_words_0 == scor_words_1)
    {
        *scor_words=scor_words_0;
        if(x_0 < x_1)
        {
            *x=x_0;
            *y=y_0;
            *d=d_0;
        }
        else if(x_1 < x_0)
        {
            *x=x_1;
            *y=y_1;
            *d=d_1;
        }
        else if (x_0 == x_1)
        {
            *x=x_0;
            if(y_0<y_1)
            {
                *y=y_0;
                *d=d_0;
            }
            else if(y_1 < y_0)
            {
                *y=y_1;
                *d=d_1;
            }
        }
    }
}
return output;
}

//functie care adauga \n la sfaristl cuvantului
char adaugare_next_line(char word[100])
{
    char ch='\n';
    strncat(word,&ch,1);
    return word[100];
}

//functie care elmina \n la sfaristl cuvantului
char eliminare_next_line(char word[100])
{
    char *temp;
    temp=strtok(word, "\n");
    strcpy(word,temp);
    return word[100];
}

//task 0
void task_0()
{
    //declaratii
    char game_board[15][15];
    int i,j;

    //populare game_board cu '.'
    for (i=0;i<15;i++)
        for(j=0;j<15;j++)
            game_board[i][j]='.';
    print_board(game_board);
}

//task 1
void task_1()
{
    //declaratii
    char char_n[50],word[100][100],game_board[15][15],s[4]=" ",char_sir[50];
    char *temp;
    int i,j,n;
    int d[50],x[50],y[50];

    //populare game_board cu '.'
    for (i=0;i<15;i++)
        for(j=0;j<15;j++)
            game_board[i][j]='.';
    
    //citire numar cuvinte
    fgets(char_n, sizeof(char_n), stdin);
    n = (int)strtol(char_n, NULL, 10);

    //citire info despre fiecare cuvant
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);

        //pozitia x
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);

        //pozitia y
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);

        //orientare
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);

        //cuvant
        temp =strtok(NULL,s);
        strcpy(word[i],temp);
    }

    //scriere cuvant pe matrice
    for(i=0;i<n;i++)
        scriere_matrice(game_board,word[i],x[i],y[i],d[i]);

    print_board(game_board);
}

//task 2
void task_2()
{
    //declaratii
    int scor_player1=0,scor_player2=0,scor_word[100];
    char char_n[50],char_sir[50],s[4]=" ",word[100][100];
    char *temp;
    int i,n;
    int d[50],x[50],y[50];

    //citire numar cuvinte
    fgets(char_n, sizeof(char_n), stdin);
    n = (int)strtol(char_n, NULL, 10);

    //citire info despre fiecare cuvant
    //da eroare pentru ca nu sunt folosite variabilele x[50],y[50],d[50] dar sunt folosite ca sa se citeasca corect de la tarstatura(x y d cuvant)
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);

        //pozitia x
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);

        //pozitia y
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);

        //orientare
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);

        //cuvant
        temp =strtok(NULL,s);
        strcpy(word[i],temp);
    }
    
    //calculare scor pentru fiecare cuvant
    for(i=0;i<n;i++)
        scor_word[i]=calculator_scor_cuvant(word[i]);

    //calculare scor P1 si P2
    for(i=0;i<n;i+=2)
        scor_player1+=scor_word[i];
    
    for(i=1;i<n;i+=2)
        scor_player2+=scor_word[i];

    printf("Player 1: %d Points\nPlayer 2: %d Points\n",scor_player1,scor_player2);
}

//task 3
void task_3()
{   
    //declaratii
    char word[100][100],char_n[100],XX[5],YY[5],s[]=" ",char_sir[100];
    char *temp;
    int n,i,scor_player1=0,scor_player2=0,scor_word[100];
    int x[100],y[100],d[100];

    //citire sir
    fgets(XX, sizeof(XX), stdin);
    fgets(YY, sizeof(YY), stdin);

    //citire numar cuvinte
    fgets(char_n, sizeof(char_n), stdin);
    n = (int)strtol(char_n, NULL, 10);
    
    //citire info despre fiecare cuvant
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);

        //pozitia x
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);

        //pozitia y
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);

        //orientare
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);

        //cuvant
        temp =strtok(NULL,s);
        strcpy(word[i],temp);
    }

    //eliminarea elem. '\n' din sirul XX
    temp=strtok(XX, "\n");
    strcpy(XX,temp);
    
    //calculator scor cuvant
    for(i=0;i<n;i++)
        scor_word[i]=calculator_scor_cuvant(word[i]);

    //calculator scor bonus pt sirul YY
    for(i=0;i<n;i++)
        scor_word[i]=calculator_scor_bonus_YY_cuvant(word[i],scor_word[i],YY,x[i],y[i],d[i]);

    //calculator scor bonus pt sirul XX
    for(i=0;i<n;i++)   
        scor_word[i]=calculator_scor_bonus_XX_cuvant(word[i],scor_word[i],XX,x[i],y[i],d[i]);

    //calculator scor P1 si P2
    for(i=0;i<n;i+=2)
        scor_player1+=scor_word[i];

    for(i=1;i<n;i+=2)
        scor_player2+=scor_word[i];

    printf("Player 1: %d Points\nPlayer 2: %d Points",scor_player1,scor_player2);
    
}

//task 4
void task_4()
{
    //declaratii
    char word[100][100],char_n[100],XX[5],YY[5],s[]=" ",char_sir[100],game_board[15][15];
    char *temp;
    int n,i,j,k;
    int ok_words[100];
    int x_words[100],y_words[100],d_words[100];

    int x[100],y[100],d[100];
    
    //citire sir
    fgets(XX, sizeof(XX), stdin);
    fgets(YY, sizeof(YY), stdin);

    //citire numar cuvinte
    fgets(char_n, sizeof(char_n), stdin);
    n = (int)strtol(char_n, NULL, 10);
    
    //citire info despre fiecare cuvant
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);

        //pozitia x
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);

        //pozitia y
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);

        //orientare
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);

        //cuvant
        temp =strtok(NULL,s);
        strcpy(word[i],temp);
    }

    //populare matrice cu '.'
    for (i=0;i<15;i++)
        for(j=0;j<15;j++)
            game_board[i][j]='.';

    //elimina \n din bonusul XX
    eliminare_next_line(XX);
      
    //scriere cuvant pe matrice
    for(i=0;i<n;i++)   
        scriere_matrice(game_board,word[i],x[i],y[i],d[i]);

    //elimina \n din cuvinte
    for(i=0;i<n;i++)
        eliminare_next_line(word[i]);
    
    //verifica daca un cuvant din vector se poate pune pe tabla si daca da atunci gaseste cea mai optima pozitie
    for(k=0;k<NUM_WORDS;k++)
        ok_words[k]=verificare_posibilitate(game_board,words[k],&x_words[k],&y_words[k],&d_words[k]);
    
    //verifica daca un cuvant din vector este deja pe tabla
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1)
        {    for(i=0;i<n;i++)
            {
                if(strcmp(word[i],words[k])==0)
                {
                    ok_words[k]=0;
                }
            }
        }
    }
    
    //adauga primul cuvant optim din vector
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1)
        {
            adaugare_next_line(words[k]);
            scriere_matrice(game_board,words[k],x_words[k],y_words[k],d_words[k]);
            break;
        }
    }
    print_board(game_board); 
}

//task 5
void task_5()
{
    //declaratii
    char XX[4],YY[4],char_n[100],char_sir[100],s[]=" ";
    char word[100][100],game_board[15][15];
    char *temp;
    int n,i,j,k,scor_player1=0,scor_player2=0;
    int x_words[100],y_words[100],d_words[100],scor_words[100],scor_max=0,x_min=16,y_min=16;
    int x[100],y[100],d[100],ok_words[100],scor_word[100],cuvant;

    //citire sir
    fgets(XX, sizeof(XX), stdin);
    fgets(YY, sizeof(YY), stdin);

    //citire numar cuvinte
    fgets(char_n, sizeof(char_n), stdin);
    n = (int)strtol(char_n, NULL, 10);
    
    //citire info despre fiecare cuvant
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);

        //pozitia x
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);

        //pozitia y
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);

        //orientare
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);

        //cuvant
        temp =strtok(NULL,s);
        strcpy(word[i],temp);
    }

    //populare matrice cu '.'
    for (i=0;i<15;i++)
        for(j=0;j<15;j++)
            game_board[i][j]='.';

    //eliminarea elem. '\n' din sirul XX
    temp=strtok(XX, "\n");
    strcpy(XX,temp);
      
    //scriere cuvant pe matrice
    for(i=0;i<n;i++)  
        scriere_matrice(game_board,word[i],x[i],y[i],d[i]);
    
    //calculator scor cuvant
    for(i=0;i<n;i++)
        scor_word[i]=calculator_scor_cuvant(word[i]);

    //calculator scor bonus pt sirul YY
    for(i=0;i<n;i++)
        scor_word[i]=calculator_scor_bonus_YY_cuvant(word[i],scor_word[i],YY,x[i],y[i],d[i]);

    //calculator scor bonus pt sirul XX
    for(i=0;i<n;i++)
        scor_word[i]=calculator_scor_bonus_XX_cuvant(word[i],scor_word[i],XX,x[i],y[i],d[i]);

    //calculator scor P1
    for(i=0;i<n;i+=2)
        scor_player1+=scor_word[i];

    //calculator scor P2
    for(i=1;i<n;i+=2)
        scor_player2+=scor_word[i];

    //adauga \n la cuvintele din vector
    for(k=0;k<NUM_WORDS;k++)
        adaugare_next_line(words[k]);

    //verifica daca un cuvant din vector se poate pune pe tabla si daca da atunci gaseste cea mai optima pozitie
    for(k=0;k<NUM_WORDS;k++)
        ok_words[k]=verificare_posibilitate_5(game_board,XX,YY,words[k],&x_words[k],&y_words[k],&d_words[k],&scor_words[k]);
    
    //adauga \n la cuvintele optime
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1)
        {
            adaugare_next_line(words[k]);
        }
    }

    //verifica daca un cuvant din vector este deja pe tabla
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1)
        {    for(i=0;i<n;i++)
            {
                if(strcmp(word[i],words[k])==0)
                {
                    ok_words[k]=0;
                }
            }
        }
    }
   
    //gaseste scorul maxim din lista de cuvinte optime
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 && scor_max < scor_words[k])
        {
            scor_max=scor_words[k];
        }
    }

    //gaseste cuvantul care are scorul maxim si linia cea mai mica
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 && scor_words[k]==scor_max)
        {
            if(x_words[k]<x_min)
            {
                x_min=x_words[k];
            }
        }
    }

    //gaseste cuvantul care are scorul maxim ,linia cea mai mica si coloana cea mai mica
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 && scor_words[k]==scor_max && x_words[k]==x_min)
        {
            {
                y_min=y_words[k];
            }
        }
    }
    
    //gaseste pozitia in vector a cuvantului optim
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 &&scor_words[k]==scor_max && x_words[k]==x_min && y_words[k]==y_min) 
            cuvant=k;
    }

    //adauga cuvantul optim pe tabla
    if((scor_player2 + scor_max) >= scor_player1)
    {
        adaugare_next_line(words[cuvant]);
        scriere_matrice(game_board,words[cuvant],x_words[cuvant],y_words[cuvant],d_words[cuvant]);
        print_board(game_board);
    }
    else
        printf("Fail!");
    
}

//task 6
void task_6()
{
    //declarari
    char XX[4],YY[4],char_n[100],char_sir[100],s[]=" ";
    char word[100][100],game_board[15][15];
    char *temp;
    int n,i,j,k,scor_player1=0,scor_player2=0,kontor;
    char used_words[100][100];
    int x_words[100],y_words[100],d_words[100],scor_words[100],scor_max=0,x_min=16,y_min=16;
    int x[100],y[100],d[100],ok_words[100],scor_word[100],cuvant;

    //citire sir
    fgets(XX, sizeof(XX), stdin);
    fgets(YY, sizeof(YY), stdin);

    //citire numar cuvinte P1
    fgets(char_n, sizeof(char_n), stdin);
    n = (int)strtol(char_n, NULL, 10);

    //citire info despre fiecare cuvant
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);

        //pozitia x
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);

        //pozitia y
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);

        //orientare
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);

        //cuvant
        temp =strtok(NULL,s);
        strcpy(word[i],temp);
    }

    //populare matrice cu '.'
    for (i=0;i<15;i++)
        for(j=0;j<15;j++)
            game_board[i][j]='.';

    //eliminarea elem. '\n' din sirul XX
    temp=strtok(XX, "\n");
    strcpy(XX,temp);

    //while are scop ca sa joace P2 cu P1 cat timp P1 are cuvinte de pus
    while(kontor!=n)
    {
        x_min=16;
        y_min=16;
        scor_max=0;

        //pune cuvantul lui P1 pe tabla
        scriere_matrice(game_board,word[kontor],x[kontor],y[kontor],d[kontor]);
        scor_word[kontor]=calculator_scor_cuvant(word[kontor]);
        scor_word[kontor]=calculator_scor_bonus_YY_cuvant(word[kontor],scor_word[kontor],YY,x[kontor],y[kontor],d[kontor]);
        scor_word[kontor]=calculator_scor_bonus_XX_cuvant(word[kontor],scor_word[kontor],XX,x[kontor],y[kontor],d[kontor]);
        scor_player1+=scor_word[kontor];
        
        //adauga \n la tot vectorul de cuvinte
        for(k=0;k<NUM_WORDS;k++)
            adaugare_next_line(words[k]);
        
        //gaseste cuvintele care se pot pune pe tabla
        for(k=0;k<NUM_WORDS;k++)
        {
            ok_words[k]=verificare_posibilitate_5(game_board,XX,YY,words[k],&x_words[k],&y_words[k],&d_words[k],&scor_words[k]);
        }
        
        //verifica daca nu a fost folosit deja cuvantul
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1)
            {    
                for(i=0;i<n;i++)
                {
                    if(strcmp(word[i],words[k])==0)
                    {
                        ok_words[k]=0;
                    }
                }
            }
        }
        
        //adauga \n la cuvintele folosite
        for(i=0;i<kontor;i++)
        {
            adaugare_next_line(used_words[i]);
            adaugare_next_line(used_words[i]);
        }

        //verifica daca cuvantul din vector este pe tabla
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1)
            {
                for(i=0;i<kontor;i++)
                {
                    if(strcmp(words[k],used_words[i])==0)
                    {
                        ok_words[k]=0;
                    }
                }
            }  
        }

        //gaseste scorul maxim din lista de cuvinte optime
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1 && scor_max < scor_words[k])
            {
                scor_max=scor_words[k];
            }
        }

        //gaseste cuvantul care are scorul maxim si linia cea mai mica
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1 && scor_words[k]==scor_max)
            {
                if(x_words[k]<x_min)
                {
                    x_min=x_words[k];
                }
            }
        }

        //gaseste cuvantul care are scorul maxim ,linia cea mai mica si coloana cea mai mica
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1 && scor_words[k]==scor_max && x_words[k]==x_min)
            {
                {
                    y_min=y_words[k];
                }
            }
        }

        //gaseste pozitia in vector a cuvantului optim
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1 &&scor_words[k]==scor_max && x_words[k]==x_min && y_words[k]==y_min) 
                cuvant=k;
        }

        //scrie cuvantul optim pe tabal
        adaugare_next_line(words[cuvant]);
        scriere_matrice(game_board,words[cuvant],x_words[cuvant],y_words[cuvant],d_words[cuvant]);
        scor_player2+=scor_max;
        //printf("s2:%d ",scor_player2);

        for(k=0;k<NUM_WORDS;k++)
            eliminare_next_line(words[k]);
        
        for(k=0;k<NUM_WORDS;k++)
        {
            if(ok_words[k]==1)
            {
                eliminare_next_line(words[k]);
            }
        }
        for(i=0;i<kontor;i++)
        {
            eliminare_next_line(used_words[i]);
            eliminare_next_line(used_words[i]);
        }
        eliminare_next_line(words[cuvant]);

        //scrie cuvantul folosit runda asta de P2 intr-un vector cu cuvinte folosite de P2
        strcpy(used_words[kontor],words[cuvant]);
        kontor++;
    }
    print_board(game_board);


    if(scor_player1 > scor_player2)
    {
        printf("Player 1 Won!\n");
    }
    else if(scor_player2 > scor_player1)
    {
        printf("Player 2 Won!\n");
    }

}    

int main()
{
    char char_task[10];
    int task;
    fgets(char_task, sizeof(char_task), stdin);
    task = (int)strtol(char_task, NULL, 10);
    if(task==0)
        task_0();
    else if(task==1)
        task_1();
    else if(task==2)
        task_2();
    else if(task==3)
        task_3();
    else if(task==4)
        task_4();
    else if (task==5)
        task_5();
    else if (task==6)
        task_6();
    
    return 0;
}