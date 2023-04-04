#include <stdio.h>
#include "./util/scrabble.h"
#include <stdlib.h>
#include <string.h>

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

int verificare_posibilitate(char game_board[15][15],char XX[4],char YY[4],char words[100],int *x,int *y,int *d,int *scor_words)
{
int i,j,output;
long unsigned int ct;
output=0;
int x_0,y_0,d_0,check_0=0,scor_words_0=0;
int x_1,y_1,d_1,check_1=0,scor_words_1=0;
for(i=0;i<15;i++)
{
    for(j=0;j<15;j++)
    {
        next_piece0:
        if(game_board[i][j]==words[0])
        {
            if(game_board[i][j+1]=='.' && (j + strlen(words))<=15)
            {
                for(ct=1;ct<strlen(words);ct++)
                {
                    if(game_board[i][j+ct]!='.')
                    {
                        j++;
                        goto next_piece0;
                    }    
                }
                x_0=i;
                y_0=j;
                d_0=0;
                check_0=1;
                /**x=i;
                *y=j;
                *d=0;*/
                output=1;
                goto next;
                //goto final;
            }
        }
    }
}
next:
printf("CUVANT:%s\n",words);

for(i=0;i<15;i++)
{
    for(j=0;j<15;j++)
    {
        next_piece1:
        if(game_board[i][j]==words[0])
        {
            if(game_board[i+1][j]=='.' && (i + strlen(words))<=15)
            {
                for(ct=1;ct<strlen(words);ct++)
                {
                    if(game_board[i+ct][j]!='.')
                    {
                        j++;
                        goto next_piece1;
                    }
                }
                x_1=i;
                y_1=j;
                d_1=1;
                output=1;
                /**x=i;
                *y=j;
                *d=1;*/
                check_1=1;
                goto final;
            }
        }
    }
}
final:
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

char adaugare_next_line(char word[100])
{
    char ch='\n';
    strncat(word,&ch,1);
    return word[100];
}

char eliminare_next_line(char word[100])
{
    char *temp;
    temp=strtok(word, "\n");
    strcpy(word,temp);
    return word[100];
}

void task_5()
{
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
    
    //citire info despre cuvinte
    for(i=0;i<n;i++)
    {
        fgets(char_sir,sizeof(char_sir),stdin);
        temp =strtok(char_sir,s);
        x[i] = (int)strtoll(temp, NULL, 10);
        temp=strtok(NULL,s);
        y[i] = (int)strtoll(temp, NULL, 10);
        temp=strtok(NULL,s);
        d[i] = (int)strtoll(temp, NULL, 10);
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

    //calculator scor P1 si P2
    for(i=0;i<n;i+=2)
        scor_player1+=scor_word[i];

    for(i=1;i<n;i+=2)
        scor_player2+=scor_word[i];
    //adaugare \n
    for(k=0;k<NUM_WORDS;k++)
        adaugare_next_line(words[k]);
    for(k=0;k<NUM_WORDS;k++)
        ok_words[k]=verificare_posibilitate(game_board,XX,YY,words[k],&x_words[k],&y_words[k],&d_words[k],&scor_words[k]);
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1)
        {
            adaugare_next_line(words[k]);
        }
    }
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
    /*for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1)
        {
        scor_words[k]=calculator_scor_cuvant(words[k]);
        scor_words[k]=calculator_scor_bonus_XX_cuvant(words[k],scor_words[k],XX,x_words[k],y_words[k],d_words[k]);
        scor_words[k]=calculator_scor_bonus_YY_cuvant(words[k],scor_words[k],YY,x_words[k],y_words[k],d_words[k]);
        }
    }*/
    for(k=0;k<NUM_WORDS;k++)
        if(ok_words[k]==1)
            printf("cuvant:%s scor:%d x:%d y:%d\n",words[k],scor_words[k],x_words[k],y_words[k]);

    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 && scor_max < scor_words[k])
        {
            scor_max=scor_words[k];
            //printf("scor max:%d\n",scor_max);
        }
    }
    printf("\n\n");

    

    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 && scor_words[k]==scor_max)
        {
            printf("cuvant:%s scor:%d x:%d y:%d\n",words[k],scor_words[k],x_words[k],y_words[k]);
            if(x_words[k]<x_min)
            {
                x_min=x_words[k];
            }
        }
    }

    printf("\n\n");

    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 && scor_words[k]==scor_max && x_words[k]==x_min)
        {
            printf("cuvant:%s scor:%d x:%d y:%d\n",words[k],scor_words[k],x_words[k],y_words[k]);
            if(y_words[k]<y_min)
            {
                y_min=y_words[k];
            }
        }
    }
    for(k=0;k<NUM_WORDS;k++)
    {
        if(ok_words[k]==1 &&scor_words[k]==scor_max && x_words[k]==x_min && y_words[k]==y_min) 
            cuvant=k;
    }

    /*if((scor_player2 + scor_max) >= scor_player1)
    {
        adaugare_next_line(words[cuvant]);
        scriere_matrice(game_board,words[cuvant],x_words[cuvant],y_words[cuvant],d_words[cuvant]);
        print_board(game_board);
    }
    else
        printf("Fail!");
    */
    
}

int main()
{
    char char_task[10];
    int task;
    fgets(char_task, sizeof(char_task), stdin);
    task = (int)strtol(char_task, NULL, 10);
    task_5();
}