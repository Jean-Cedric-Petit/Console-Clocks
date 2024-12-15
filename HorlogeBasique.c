/*
 * Created on Tue Nov 29 2022
 * Last edit on Mon Dec 5 2022
 * 
 * Copyright (c) 2020 - Naoki Takei
 * 
 * Je n'ai pas testé sous Linux.(Meme si j'y ai accès à un Linux...)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Pour le sleep
#ifdef _WIN32
    #include <windows.h>
    #define PIXEL 219 //Permet de retrouver le char carré.
#elif defined __unix__
    #include <unistd.h>
    #define PIXEL 35 //Permet de retrouver le char carré.
#endif 




//Permet de debug rapidement
//#define DEBUG


//nbr de colonne = 6*5+1*2+7 = 39
//nbr de lignes = 5

void PrintDebug(int *disp); //affiche la matrice pseudo 2D en une ligne

void display(int *disp); //affiche
void display2(int *screen,int largeur,int hauteur);
void InitializeDisplay(int *disp); //remplie de char vide
void colon(int *input); //met les ":"

void zero(int *input,int position);
void un(int *input,int position);
void deux(int *input,int position);
void trois(int *input,int position);
void quatre(int *input,int position);
void cinq(int *input,int position);
void six(int *input,int position);
void sept(int *input,int position);
void huit(int *input,int position);
void neuf(int *input,int position);

void analyzeTime(int *input,int h,int m,int s);

void newWindow();// <----- completement inutile

int main(int argc, char *argv[]){
    #ifdef _WIN32
        system("cls");
    #elif defined __unix__
        system("clear");
    #endif 
    int screen[(39)*5]; //Array contenant tout ce qui est à afficher.
    InitializeDisplay(screen);
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    int sec,min,hour;
    
    while(1){
        #ifdef _WIN32
            system("cls");
        #elif defined __unix__
            system("clear");
        #endif
        //newWindow();
        printf("\n\n\n\n");//On centre... enfin, on essaie...
        InitializeDisplay(screen);//Permet de remettre à zero.... J'ai oublié que "cls" ne nettoyait pas mon array ...
        t = time(NULL);
        ptr = localtime(&t);
        sec=ptr->tm_sec;
        min=ptr->tm_min;
        hour=ptr->tm_hour;
        #ifdef DEBUG
            six(screen,2);// Je défini qu'il n'y a pas de slot 0 et qu'on  commence avec le slot 1.
            sept(screen,1);
            huit(screen,3);
            neuf(screen,4);
            quatre(screen,5);
            cinq(screen,6);
        #endif

        analyzeTime(screen,hour,min,sec);//voir ce que j'ai ecris a propos de cette func plus bas... 

        display2(screen,39,5);
        
        #ifdef _WIN32
            Sleep(110); //110ms : WINDOWS et Linux ont differentes implémentation de Sleep. celle de linux ne prend que des secondes donc j'utilise usleep.
        #elif defined __unix__
            usleep(110000); //110ms normalement
        #endif
        #ifdef DEBUG
            printf("\n%d:%d:%d",hour,min,sec);
            PrintDebug(screen);
            exit(0);
        #endif
    }
    return 0;
}



/*
* 
*
*   PARTIE FONCTIONS ********************************************************************************************************************************************************************************************************************************************************************************************************************************************************
*
*
*
*/

void PrintDebug(int *disp){
    printf("\n");
    for(int i=0;i<5*39;i++){
        printf("%c",disp[i]);
    }
}


void display(int *disp){
    for(int i=0;i<5;i++){//ligne
        for(int j=0;j<39;j++){//colonne
            if(j==0){
                printf("\t\t");//C'est pour essayer de centrer.
            }
            printf("%c",disp[39*i+j]);
        }
        printf("\n");
    }
    printf("\n");
}

void display2(int *screen,int largeur,int hauteur){
    char disp[(largeur+1)*hauteur+1];
    //initializeScreen(disp,(largeur+2)*hauteur);
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            //printf("%c",screen[i*largeur+j]);
            disp[j+i*(largeur+1)]=screen[j+i*largeur];
        }
        disp[largeur+i*(largeur+1)]='\n';
    }
    disp[(largeur+1)*hauteur+1]='\0';
    printf("%s",disp);
}

void InitializeDisplay(int *disp){
    for(int i=0;i<39*5;i++){
        disp[i]=32;
    }
    colon(disp); //On met les ":"
}

//Normalement on y touche qu'une seule fois....
void colon(int *input){
    //Premier
    input[8+39*1]=PIXEL;
    input[8+39*3]=PIXEL;
    //Second
    input[18+39*1]=PIXEL;
    input[18+39*3]=PIXEL;
}

void zero(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){ //C'est franchement pas élégant, mais on va dire que c'est pour la beauté du display
        start+=2;
        finish+=2;
    }else if(position>=5){//C'est parce qu'on a besoin de compenser les espaces utilisé et autour des colons.
        start+=4;
        finish+=4;
    }
    
    for(int i=0;i<5;i++){//LIGNE
        for(int j=start;j<finish;j++){//COLONNE
            if((j-start)%3==2 || (j-start)%3==0 || i==0 || i == 4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void un(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if((j-start)%3==2){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void deux(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){ 
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if( ((j-start)%3==2 &&(i<3)) || ((j-start)%3==0 &&(i>2))  || i==0 || i==2 || i==4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void trois(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if( (j-start)%3==2 || i==0 || i==2 || i==4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void quatre(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if( (j-start)%3==2 || ((j-start)%3==0 &&(i<3))  || i==2 ){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void cinq(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if( ((j-start)%3==0 &&(i<3)) || ((j-start)%3==2 &&(i>2))  || i==0 || i==2 || i==4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void six(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if( (j-start)%3==0 || ((j-start)%3==2 &&(i>2))  || i==0 || i==2 || i==4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void sept(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if((j-start)%3==2 || i==0){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void huit(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){ 
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if((j-start)%3==2 || (j-start)%3==0 || i==0 || i==2|| i==4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

void neuf(int *input,int position){
    int start=(position-1)*3+position-1;
    int finish=position*3+position-1;

    if(position>2 && position<5){
        start+=2;
        finish+=2;
    }else if(position>=5){
        start+=4;
        finish+=4;
    }

    for(int i=0;i<5;i++){
        for(int j=start;j<finish;j++){
            if( ((j-start)%3==0 &&(i<3)) || (j-start)%3==2  || i==0 || i==2 || i==4){
                input[j+39*i]=PIXEL;
            }
        }
    }
}

//Voici ce qu'il se passe quand on commence a l'envers.... c'est assez stupide car on ne connait pas a l'avance les chiffres qu'on va afficher, mais on connait leurs positions dans l'horlorge....
//On est donc obligé de faire de switch-case terrible....
void analyzeTime(int *input,int h,int m,int s){
    #ifdef DEBUG
        printf("\n %d \n",s);
    #endif
    switch (h/10)
    {
    case 0:
        zero(input,1);
        break;
    case 1:
        un(input,1);
        break;
    case 2:
        deux(input,1);
        break;
    default:
        printf("Heure supérieur à 30.....");
        exit(-1);
    }

    switch (h%10)
    {
    case 0:
        zero(input,2);
        break;
    case 1:
        un(input,2);
        break;
    case 2:
        deux(input,2);
        break;
    case 3:
        trois(input,2);
        break;
    case 4:
        quatre(input,2);
        break;
    case 5:
        cinq(input,2);
        break;
    case 6:
        six(input,2);
        break;
    case 7:
        sept(input,2);
        break;
    case 8:
        huit(input,2);
        break;
    case 9:
        neuf(input,2);
        break;
    default:
        printf("Heure inconnu qui n'appartient pas à 0-9");
        exit(-1);
        break;
    }

    switch (m/10)
    {
    case 0:
        zero(input,3);
        break;
    case 1:
        un(input,3);
        break;
    case 2:
        deux(input,3);
        break;
    case 3:
        trois(input,3);
        break;
    case 4:
        quatre(input,3);
        break;
    case 5:
        cinq(input,3);
        break;
    case 6:
        six(input,3);
        break;
    case 7:
        sept(input,3);
        break;
    case 8:
        huit(input,3);
        break;
    case 9:
        neuf(input,3);
        break;
    
    default:
        printf("Minute inconnu superieur a 60");
        exit(-1);
        break;
    }

    switch (m%10)
    {
    case 0:
        zero(input,4);
        break;
    case 1:
        un(input,4);
        break;
    case 2:
        deux(input,4);
        break;
    case 3:
        trois(input,4);
        break;
    case 4:
        quatre(input,4);
        break;
    case 5:
        cinq(input,4);
        break;
    case 6:
        six(input,4);
        break;
    case 7:
        sept(input,4);
        break;
    case 8:
        huit(input,4);
        break;
    case 9:
        neuf(input,4);
        break;
    default:
        printf("minute inconnu qui n'appartient pas à 0-9");
        exit(-1);
        break;
    }

    switch (s/10)
    {
    case 0:
        zero(input,5);
        break;
    case 1:
        un(input,5);
        break;
    case 2:
        deux(input,5);
        break;
    case 3:
        trois(input,5);
        break;
    case 4:
        quatre(input,5);
        break;
    case 5:
        cinq(input,5);
        break;
    case 6:
        six(input,5);
        break;
    case 7:
        sept(input,5);
        break;
    case 8:
        huit(input,5);
        break;
    case 9:
        neuf(input,5);
        break;
    
    default:
        printf("Secondes inconnu superieur a 60");
        exit(-1);
        break;
    }

    switch (s%10)
    {
    case 0:
        zero(input,6);
        break;
    case 1:
        un(input,6);
        break;
    case 2:
        deux(input,6);
        break;
    case 3:
        trois(input,6);
        break;
    case 4:
        quatre(input,6);
        break;
    case 5:
        cinq(input,6);
        break;
    case 6:
        six(input,6);
        break;
    case 7:
        sept(input,6);
        break;
    case 8:
        huit(input,6);
        break;
    case 9:
        neuf(input,6);
        break;
    default:
        printf("Secondes inconnu qui n'appartient pas à 0-9");
        exit(-1);
        break;
    }
}

//Je trouvais que system("cls") faisait trop d'instabilité lors de l'affichage...
//Alors plutot que de tout effacer, pourquoi ne pas tout décaler vers le haut...
//Sauf que c'est pire.
void newWindow(){
    for(int i=0;i<80;i++){
        printf("\n");
    }
}
