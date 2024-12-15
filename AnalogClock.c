/*
 * Created on Tue Nov 30 2022
 * Last edit on Mon Dec 5 2022
 *
 * Copyright (c) 2020 - Naoki Takei
 * 
 * On notera que si la taille est trop petite, le dessin du cercle est un peu raté...
 * A partir de 21 par 21 c'est plutot réussi. La taille par défaut est 49x49.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <inttypes.h>

//Pour le sleep
#ifdef _WIN32
    #include <windows.h>
    #define PIXEL 219 //Permet de retrouver le char carré.
    #define PIXEL1 178
    #define PIXEL2 177
    #define PIXEL3 176
#elif defined __unix__
    #include <unistd.h>
    #define PIXEL 35 //Permet de retrouver le char carré.
    #define PIXEL1 35
    #define PIXEL2 35
    #define PIXEL3 64
#endif 



void initializeScreen(int *screen, int size);
void displayScreen(int *screen,int largeur,int hauteur);

float ABS_F(float f);
int pythagore(int x,int y);
void initializeScreen(int *screen,int size);
void displayScreen(int *screen,int largeur,int hauteur);
void drawBackgroundFrame(int *screen,int largeur, int hauteur);
void NTKdrawLine(int *screen,int x1,int y1, int x2,int y2, int largeur,int thickness,int type);
void NTKdrawBox(int *screen,int x1,int y1,int x2,int y2,int largeur, int type);

int main(int argc, char *argv[]){
    int largeur=49;int hauteur=49; //Par defaut la console peut afficher 50 lignes et 120 colonnes.
    char input[8];
    
    for(int k=0;k<argc;k++){
        printf("argc[%d] ; argv[%d]=%s \n",k,k,argv[k]);
    }

    if(argc>1){
        for(int i=0;i<2;i++){
            strcpy(input,argv[i*2+1]);
            //printf("%s \n",input);
            //On peut pas utiliser de case switch avec les str (en soit si, mais c'est bien plus compliqué que seulement de faire des if else).
            if(!strcmp(input,"LARGEUR") || !strcmp(input, "largeur") || !strcmp(input,"Largeur")){
                largeur=atoi(argv[i*2+2]);
            }
            if(!strcmp(input,"HAUTEUR") || !strcmp(input, "hauteur") || !strcmp(input,"Hauteur")){
                hauteur=atoi(argv[i*2+2]);
            }   
        }
    }
    largeur*=1.5;
    int screen[largeur*hauteur];

    //On fait le nécessaire avec time.h
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    int sec,min,hour;
    float PI=3.14159265;
    float x_endSec=0;float y_endSec=0;
    float x_endMin=0;float y_endMin=0;
    float x_endHou=0;float y_endHou=0;
    initializeScreen(screen,hauteur*largeur);

    //NTKdrawLine(screen,0,hauteur-1,largeur-1,0,largeur,1,PIXEL1);
    
    //NTKdrawLine(screen,largeur/2,hauteur/2,0,hauteur-1,largeur,1,PIXEL1);

    displayScreen(screen,largeur,hauteur);
    while(1){
        #ifdef _WIN32
            system("cls");
        #elif defined __unix__
            system("clear");
        #endif
        initializeScreen(screen,hauteur*largeur);//On le reset a chaque boucle.
        drawBackgroundFrame(screen,largeur,hauteur);//Puis on dessine le contour

        //On met a jour les dernieres valeur de temps.
        t = time(NULL);
        ptr = localtime(&t);
        sec=ptr->tm_sec;
        min=ptr->tm_min;
        hour=ptr->tm_hour%12;

        //Il faut maintenant dessiner les aiguilles!
        //Les aiguilles partent du millieu.
        //Mais elles ont une longueur différentes.
        //printf("%f \n",cos(sec*(PI/30.0)));
        x_endSec=(largeur/2)-(largeur/3)*cos(sec*(PI/30.0)+PI/2);
        y_endSec=(hauteur/2)-(hauteur/3)*sin(sec*(PI/30.0)+PI/2);
        NTKdrawLine(screen,(largeur/2),(hauteur/2)+1,(int)x_endSec,(int)y_endSec,largeur,1,PIXEL3);//Dessine les secondes.

        x_endMin=(largeur/2)-(largeur/3)*cos(min*(PI/30.0)+PI/2);
        y_endMin=(hauteur/2)-(hauteur/3)*sin(min*(PI/30.0)+PI/2);
        NTKdrawLine(screen,(largeur/2),(hauteur/2)+1,(int)x_endMin,(int)y_endMin,largeur,1,PIXEL2);

        //printf("%f \n",(60*hour+min)/720.0);
        x_endHou=(largeur/2)-(largeur/5)*cos((60*hour+min)*PI/360.0 +PI/2);
        y_endHou=(hauteur/2)-(hauteur/5)*sin((60*hour+min)*PI/360.0 +PI/2);
        NTKdrawLine(screen,(largeur/2),(hauteur/2)+1,(int)x_endHou,(int)y_endHou,largeur,1,PIXEL1);


        displayScreen(screen,largeur,hauteur);//On affiche l'horloge toute prête !

        //Copié de mon code précédent (HorlogeBasique.c)
        
        #ifdef _WIN32
            Sleep(110); 
        #elif defined __unix__
            usleep(110000);
        #endif
        
    }
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FONCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ABS_F(float f){
    if(f<0){
        return -f;
    }
    return f;
}

int pythagore(int x, int y){
    return sqrt(x*x+y*y);
}

void initializeScreen(int *screen,int size){
    for(int i=0;i<size;i++){
        screen[i]=' ';
    }
}

void debug2DChars(int *screen,int largeur,int hauteur){
    for(int i=0;i<hauteur;i++){
        for(int j=0;j<largeur;j++){
            printf("%c",screen[j+i*largeur]);
        }
        printf("\n");
    }
}

//Il a fallu optimiser l'affichage...
void displayScreen(int *screen,int largeur,int hauteur){
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

//On veut dessinner un cercle rayon par défaut 25.
void drawBackgroundFrame(int *screen,int largeur , int hauteur){
    float a = largeur/2.0;
    float mid_x = a-0.25; //On veut centrer pour caster en int donc il faut corriger le centre du cercle afin que ca soit symétrique.
    float b = hauteur/2.0;
    float mid_y = b-0.5; //De meme.
    float PI=3.14159265;
    float ang=0;
    for(int y=0;y<hauteur;y++){
        for(int x=0;x<largeur;x++){
            if( ABS_F((((x-mid_x)*(x-mid_x))/(a*a)) + (((y-mid_y)*(y-mid_y))/(b*b))- 1.0) <0.1){
                screen[x+y*largeur] = PIXEL;
            }
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    if(x == ((largeur+i)/2) && y==((hauteur+j)/2)){
                        screen[x+y*largeur] = PIXEL;
                    }
                }
            }
            
        }
        //printf("\n");
    }
}

//J'appelle "type" le char a dessiner
//Commentaire à 5H du matin... Bon sang  j'avais oublié l'ordonnée à l'origine.
void NTKdrawLine(int *screen,int x1,int y1, int x2,int y2, int largeur,int thickness,int type){
    float pente;
    int y=0;
    int ordorg=0;
    if(x2-x1 == 0){
        if(y1<y2){
            for(int i=y1;i<y2;i++){
                screen[x1+i*largeur]=type;
            }
        }else{
            for(int i=y2;i<y1;i++){
                screen[x1+i*largeur]=type;
            }
        }
    }else{
        //Code originelle; qui ne marchait que si x1<x2 et y1<y2...
        if(x1<x2){
            if(y1<=y2){
                pente=((float)y2-y1)/((float)x2-x1);//CASTING EN FLOAT TRES IMPORTANT!!! (bon sang j'ai cherché le probleme pendant 30mn)
                ordorg=-pente*x1+y1;
                //Pour la largeur du trait, faudrait chercher les 2 perpendiculaire(+/-)normalisé puis multiplier par thickness et vérifier/convertir en int.
                //dessin du trait.
                for(float i=x1;i<x2;i+=0.10){
                    
                    y=ordorg+pente*i;
                    screen[(int)i+y*largeur]=type;
                }
            }else{
                pente=((float)y2-y1)/((float)x2-x1);
                ordorg=-pente*x1+y1;
                for(float i=x1;i<x2;i+=0.10){
                    
                    y= ordorg+(pente*i);
                    screen[(int)i+y*largeur]=type;
                    
                }
            }
        }else{
            if(y1<=y2){
                pente=((float)y1-y2)/((float)x1-x2);
                ordorg=-pente*x2+y2;
                for(float i=x2;i<x1;i+=0.10){
                    y= ordorg+pente*i;
                    screen[(int)i+y*largeur]=type;
                }
            }else{
                pente=((float)y1-y2)/((float)x1-x2);
                ordorg=-pente*x2+y2;
                for(float i=x2;i<x1;i+=0.10){
                    y= ordorg+(pente*i);
                    //printf("x:%d\ty:%d\n",i,y);
                    screen[(int)i+y*largeur]=type;
                    
                }
            }
        }
    }
    
    
}

//pour le fun ... Ca devrait marcher, j'ai pas testé.
void NTKdrawBox(int *screen,int x1,int y1,int x2,int y2,int largeur, int type){
    for(int i=y1;i<y2;i++){
        for(int j=x1;j<x2;j++){
            if(i==y1 || i==y2 || j==x1 || j==x2){
                screen[i+j*largeur]=type;
            }
        }
    }
}
