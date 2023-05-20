#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

int main (){

    SDL_Surface *screen;
    Mix_Music *music;
    Mix_Chunk *mus;
    SDL_Event event;

    int boucle=1;
    image mxo,xo,question,l,lg,ln,ivie,tabl,tp,fire,game_over,scf,scf1;
    image settings,mmap1,mmap2,mmap3,mmap11,mmap33,back1,back11,back2,back3,back33,backL,btnp,bk;
    Boutton BTN_START,BTN_LOAD,BTN_SETT,BTN_QUIT,BTN_SAVE,BTN_RESUME,BTN_QUIT2,reponse11, reponse22, reponse33;
    int click=1,click1=0,click2=0,click3=0,cxo=0;
    enemi enemi,monster;
    Time time;
    int k=0,i=0,con=1,cp=0;
    int v=MIX_MAX_VOLUME,maxi=100;
    int current_map_level=1,maxi0=0,maxi1=3,eer=1;

    Personne perso;
    Personnemap permi;
    int speed_x=0;
    int speed_y=0;
    int left=0,flag=0,flag1=0;
    int punch_flag = 0; 

    Enigme e;
    int etat_enigme=-1;
    int reponse1=-1,reponse2=-1,reponse3=-1;
    Uint32 start_time;
    int time_left= 20,con1=1,ee=1,con2=1,n=0,tt=1,cf=0,conf;
    int board[9] = {0},turn = 1;
    int clp=0,clsave=0,num=-1,num2=-1,quit=1,quit2=1;

    SDL_WM_SetCaption("Helloafrica", "Helloafrica");
    screen = SDL_SetVideoMode (SCREEN_W,SCREEN_H,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_Surface* x_img = NULL;
    SDL_Surface* o_img = NULL;
    load_files(&x_img, &o_img);
    int punch_timer = -1;

    initialiser_back(&settings,"./menu/Back/setting.png",0,0);
    initialiser_Boutton(&BTN_START,"./menu/BTN/START1.png","./menu/BTN/START2.png", 745, 235, 1);
    initialiser_Boutton(&BTN_LOAD,"./menu/BTN/LOAD1.png","./menu/BTN/LOAD2.png", 745, 360, 2);
    initialiser_Boutton(&BTN_SETT,"./menu/BTN/SETT1.png","./menu/BTN/SETT2.png", 745, 485, 3);
    initialiser_Boutton(&BTN_QUIT,"./menu/BTN/QUIT1.png","./menu/BTN/QUIT2.png", 745, 610, 4);
    initialiser_Boutton(&BTN_SAVE,"./menu/LOAD/SAVE1.png","./menu/LOAD/SAVE2.png", 440, 285, 5);
    initialiser_Boutton(&BTN_RESUME,"./menu/LOAD/RESUME1.png","./menu/LOAD/RESUME2.png", 440, 430, 6);
    initialiser_Boutton(&BTN_QUIT2,"./menu/LOAD/QUIT1.png","./menu/LOAD/QUIT2.png", 440, 575, 7);
    initialiser_image(&game_over,"./jeu/game_over.png",0,0);
    initialiser_image(&scf,"./final/score.png",0,0);
    initialiser_image(&scf1,"./final/ms.png",0,0);

    initialiser_image(&mxo,"./menu/XO/mXO.png",140,610);
    initialiser_image(&xo,"./menu/XO/XO.png",175,300);

    initialiser_back(&back1,"./jeu/map/back1.png",0,0);
    initialiser_back(&back11,"./jeu/map/back11.png",0,0);
    initialiser_back(&back2,"./jeu/map/back2.png",0,0);
    initialiser_back(&back3,"./jeu/map/back3.png",0,0);
    initialiser_back(&back33,"./jeu/map/back33.png",0,0);

    initialiser_back(&mmap1,"./jeu/map/mmap1.png",280,5);
    initialiser_back(&mmap2,"./jeu/map/mmap2.png",280,5);
    initialiser_back(&mmap3,"./jeu/map/mmap3.png",280,5);
    initialiser_back(&mmap11,"./jeu/map/mmap11.png",280,5);
    initialiser_back(&mmap33,"./jeu/map/mmap33.png",280,5);

    initicon(&permi);
    initPerso(&perso);

    initialiser_image(&ivie,"./jeu/live.png",160,20);
    initialiser_image(&l,"./enigme/l.png",50,25);
    initialiser_image(&lg,"./enigme/good.png",50,25);
    initialiser_image(&ln,"./enigme/no.png",50,25);
    initialiser_image(&btnp,"./menu/LOAD/btnp1.png",1085,20);
    initialiser_image(&tp,"./menu/LOAD/PAUSE.png",400,240);
    initialiser_image(&fire,"./jeu/obs1.png",330,480);

    initialiser_audiobref(&mus,"./jeu/punch.wav");
    initialisation_enemy(&enemi);

    initialiser_audio (music);
    initializerTemps(&time);
    
    while (boucle)
    {                                     
        SDL_Flip(screen);

        if(click==1){
        	anim(screen,con);
            anim2(screen,con);
            con++;
            if(con>=5)
                con=1;

            afficher_boutton(event,&BTN_START,screen);
            afficher_boutton(event,&BTN_LOAD,screen);
            afficher_boutton(event,&BTN_SETT,screen);
            afficher_boutton(event,&BTN_QUIT,screen);

            if(cxo==0){
                afficher(screen,mxo);
                int board[9]={0};
            }

            if(cxo==1)
            {
                afficher(screen,xo);
                cxo = handle_events(screen, x_img, o_img,board, &turn);

                draw_board(screen, x_img, o_img,board);

                int winner = check_win(board);
                if (winner != 0) {
                    SDL_Delay(1000);
                    char message[30];
                    if (winner == 1) {
                        sprintf(message, "X wins!");
                    }
                    else if (winner == 2) {
                        sprintf(message, "O wins!");
                    }
                    else {
                        sprintf(message, "Tie game!");
                    }
                    SDL_WM_SetCaption(message, NULL);
                    SDL_Delay(1000);
                    SDL_WM_SetCaption("Helloafrica", "Helloafrica");
                    cxo = 0;
                }
            }
            
            afficher_texte(screen,"Bienvenue",475,20,"./menu/Path/theme.ttf",45,255,255,255);
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                    case SDL_QUIT:
                        boucle = 0;
                        break;

                    case SDL_MOUSEBUTTONDOWN:

                        if ((event.motion.y <= 335 && event.motion.y >= 235) && (event.motion.x <= 1115 && event.motion.x >= 745))
                            click1=1;

                        else if ((event.motion.y <= 460 && event.motion.y >= 360) && (event.motion.x <= 1115  && event.motion.x >= 745))
                            click2=1;

                        else if ((event.motion.y <= 585 && event.motion.y >= 485) && (event.motion.x <= 1115  && event.motion.x >= 745))
                            click3=1;

                        else if ((event.motion.y <= 710 && event.motion.y >= 610) && (event.motion.x <= 1115 && event.motion.x >= 745))
                            boucle=0;

                        else if ((event.motion.y <= 720 && event.motion.y >= 610) && (event.motion.x <= 250 && event.motion.x >= 140))
                            cxo=1;

                        else if ((event.motion.y<=667 && event.motion.y>=605) && (event.motion.x<=121&& event.motion.x>=50))
                            system("xdg-open ./menu/Path/credit.txt");

                        else if ((event.motion.y<=740 && event.motion.y>=680) && (event.motion.x<=121 && event.motion.x>=50)) 
                            system("xdg-open http://victorem.e-monsite.com");

                        break;

                        
                    case (SDL_KEYDOWN):

                        if(event.key.keysym.sym==SDLK_o)
                            click3=1;

                        if((event.key.keysym.sym==SDLK_x)&&(cxo==1))
                            cxo=0;

                        if(event.key.keysym.sym==SDLK_f)
                            cf=1;

                        switch(event.key.keysym.sym)
                        {
                            case SDLK_UP:
                                k=1;
                                i--;
                                break;

                            case SDLK_DOWN:
                                k=1;
                                i++;
                                break;

                            case SDLK_RETURN:

                                if(i==1) 
                                    click1=1;

                                if(i==2)
                                    click2=1;

                                if(i==3)
                                    click3=1;

                                if(i==4) 
                                    boucle=0;

                                break;
                        }
                        break;
                }
            }

            if(k!=0){
                if(i>4)
                    i=1;
                else if(i<1)
                    i=4;
            }

            if(i==1)
                afficher_boutton_clav(BTN_START, screen);

            else if(i==2)
                afficher_boutton_clav(BTN_LOAD, screen);

            else if(i==3)
                afficher_boutton_clav(BTN_SETT, screen);

            else if(i==4)
                afficher_boutton_clav(BTN_QUIT, screen);
        }
        
        if(click1==1)
        {
            click=0;
            if (maxi1==0)
            {
                afficher(screen, game_over);
                while (SDL_PollEvent(&event))
                { 
                    switch (event.type)
                    { 
                        case SDL_QUIT:
                            boucle=0;
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            if (event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=562 && event.motion.y>=522 && event.motion.x<=671 && event.motion.x>627))
                            {
                                boucle=0;
                            }
                            else if (event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=562 && event.motion.y>=522 && event.motion.x<=590 && event.motion.x>529))
                            {
                                current_map_level = 1 ; 
                                maxi1 = 3 ;
                                maxi0=100;
                                initialiser_back(&back1,"./jeu/map/back1.png",0,0);
                                initialiser_back(&back11,"./jeu/map/back11.png",0,0);
                                initialiser_back(&back2,"./jeu/map/back2.png",0,0);
                                initialiser_back(&back3,"./jeu/map/back3.png",0,0);
                                initialiser_back(&back33,"./jeu/map/back33.png",0,0);
                                initialiser_back(&mmap1,"./jeu/map/mmap1.png",280,5);
                                initialiser_back(&mmap2,"./jeu/map/mmap2.png",280,5);
                                initialiser_back(&mmap3,"./jeu/map/mmap3.png",280,5);
                                initicon(&permi);
                                initPerso(&perso);
                                initialiser_image(&ivie,"./jeu/live.png",160,20);
                                initialiser_image(&l,"./enigme/l.png",50,25);
                                initialiser_image(&lg,"./enigme/good.png",50,25);
                                initialiser_image(&ln,"./enigme/no.png",50,25);
                                initialiser_image(&btnp,"./menu/LOAD/btnp1.png",1085,20);
                                initialiser_image(&tp,"./menu/LOAD/PAUSE.png",400,240);
                                initialiser_image(&fire,"./jeu/obs1.png",330,480);
                                initialiser_audiobref(&mus,"./jeu/punch.wav");
                                initialisation_enemy(&enemi);
                                initializerTemps(&time);
                                k=0,i=0,con=1,cp=0,speed_x=0,speed_y=0,left=0,flag=0,flag1=0;
                                e = generer("./enigme/enigme.txt");
                                time_left= 20,con1=1,ee=1,con2=1,n=0,tt=1,cf=0,conf,etat_enigme=-1;
                                clp=0,clsave=0,num=-1,num2=-1,quit=1,quit2=1;
                                reponse1=-1,reponse2=-1,reponse3=-1,eer=1;
                            }
                            break;
                    }
                }
            }
            else{
                if (current_map_level == 1) { 
                    if (perso.position.x >= SCREEN_W-60) { 
                        maxi0=maxi0+1000; 
                        current_map_level = 2; 
                        perso.position.x=0;
                        perso.position.y=330;
                        permi.position_map.x=280;
                    }
                }

                if(current_map_level==2){
                    if(perso.position.x>=SCREEN_W-60){
                        maxi0=maxi0+1000;
                        current_map_level =3;
                        perso.position.x=0;
                        permi.position_map.x=280;
                    }
                }

                if(current_map_level==3){
                    if(perso.position.x>=SCREEN_W-100){
                        conf=1;
                        cf=1;
                    }
                }

                if (current_map_level == 1) 
                { 
                    if(cp%30>=20){
                        afficher(screen,back1);
                        afficher(screen,mmap1);
                        cp++;
                    }else{
                        afficher(screen,back11);
                        afficher(screen,mmap11);
                        cp++;
                    }
                    bk=back1;
                }

                else if (current_map_level==2)
                { 
                    afficher_back(screen,back2);
                    afficher(screen,mmap2);
                    if (perso.position.x >=  600 ){
                        animer_enemy(&enemi); 
                        afficher_enemy(screen, enemi); 
                        if (detect_collision(enemi, perso)) {
                            if (punch_timer == -1 || SDL_GetTicks() - punch_timer > 1000){
                                Mix_PlayChannel(-1, mus, 0);
                                Mix_VolumeChunk(mus, MIX_MAX_VOLUME);
                                punch_timer = SDL_GetTicks();
                                printf("you take a hit from enemy\n");
                                maxi1 = maxi1 -1 ;
                            }
                        }
                        deplacer_IA(&enemi , perso , 10);
                    }   
                    bk=back2;
                }

                else if ( current_map_level == 3)
                {    
                    if(cp%30>=20){
                       afficher(screen,back3);
                       afficher(screen,mmap3);
                       cp++;
                    }
                    else{
                       afficher(screen,back33);
                       afficher(screen,mmap33);
                       cp++;
                    }
                    bk=back3;
                }

                afficher(screen,btnp);
                printf("x %d\n",perso.position.x);
                printf("y %d\n",perso.position.y);
                
                if(current_map_level==1)
                {
                    if((perso.position.x==180)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x>=350)&&(perso.position.x<=370)&&(perso.position.y==SCREEN_H-250))
                    {
                        afficher(screen,fire);
                    }
                    if((perso.position.x==360)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x==540)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x==920)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x==1030)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                }

                if(current_map_level==2)
                {
                    if((perso.position.x<=660)&&(perso.position.y==SCREEN_H-250))
                        maxi1=0;
                }

                if(current_map_level==3)
                {
                    if((perso.position.x==160)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x==330)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x==530)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                    if((perso.position.x==750)&&(perso.position.y==SCREEN_H-250))
                    {
                        maxi1--;
                    }
                }

                afficherPerso(perso,screen);
                afficheicon(permi,screen);
                animerPerso(&perso,left);
                animerPersomini(&permi,left);
                afficherTemps(&time,screen);
                afficher_texte(screen,"score: ",10, 20,"./menu/Path/theme.ttf",20,0,0,0);
                afficher(screen,ivie);
                afficher_nb(screen,maxi0,95,20,"./menu/Path/police.ttf",20,0,0,0,0,0,0);
                afficher_nb(screen,maxi1,190,20,"./menu/Path/police.ttf",20,0,0,0,0,0,0);

                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                        case SDL_QUIT:
                            boucle=0;
                            break;

                        case SDL_MOUSEBUTTONDOWN:
                            if (event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=300 && event.motion.y>=250 && event.motion.x<=423 && event.motion.x>213))
                                boucle=0;

                            if (event.button.button==SDL_BUTTON_LEFT && (event.motion.y<=100 && event.motion.y>=20 && event.motion.x<=1175 && event.motion.x>1085))
                                clp=1;

                            break;

                         case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                                case SDLK_m:
                                    click1=0;
                                    click=1;

                                case SDLK_RIGHT:
                                    left=0;
                                    perso.direction = 1;
                                    perso.move= 1;
                                    permi.move_map = 1;
                                    permi.direction_map =1;
                                    maxi0=maxi0+10;
                                    break;
                          
                                case SDLK_LEFT:
                                    left=1;
                                    perso.direction = -1;
                                    perso.move = 1;
                                    permi.direction_map = -1;
                                    permi.move_map = 1;
                                    maxi0=maxi0+10;
                                    break;

                                case SDLK_UP:
                                    if(!flag)
                                    {
                                        flag=1;
                                        perso.jump_speed = 22; 
                                    } 
                                    if(!flag1)
                                    {
                                        flag1=1;
                                        permi.jump_speed_map=13;
                                    }
                                    maxi0=maxi0+10;
                                    break;

                                case SDLK_LSHIFT:
                                    if(perso.direction>=0)
                                    {
                                        perso.direction = 7;
                                        permi.direction_map = 3;
                                    }
                                    else
                                    {
                                        perso.direction= -3;
                                        permi.direction_map = -3;
                                    }
                                    maxi0=maxi0+50;
                                    break;
                            }
                            break;

                        case SDL_KEYUP:
                            switch (event.key.keysym.sym)
                            {
                                case SDLK_RIGHT:
                                    perso.move=0;
                                    permi.move_map=0;
                                    maxi0=maxi0+10;
                                    break;
                                case SDLK_LEFT:
                                    perso.move=0;
                                    permi.move_map=0;
                                    maxi0=maxi0+10;
                                    break;
                                case SDLK_LSHIFT:
                                    if(perso.direction>=0)
                                    {
                                        maxi0=maxi0+50;
                                        perso.direction = 1;
                                    }
                                    else
                                    {
                                        maxi0=maxi0+50;
                                        perso.direction= -1;
                                    }
                                    break;
                            }
                            break;    
                    }
                }

                if(clp==1)
                {
                    afficher_back(screen,backL);
                    afficher(screen,tp);
                    afficher_boutton(event,&BTN_SAVE,screen);
                    afficher_boutton(event,&BTN_RESUME,screen);
                    afficher_boutton(event,&BTN_QUIT2,screen);

                    if ((event.button.button == SDL_BUTTON_LEFT) && (event.motion.y <= 385 && event.motion.y >= 285) && (event.motion.x <= 810  && event.motion.x >= 440))
                    {
                        clsave=1;
                        //quit=1;
                    }

                    else if ((event.button.button == SDL_BUTTON_LEFT) && (event.motion.y <= 530 && event.motion.y >= 430) && (event.motion.x <= 810 && event.motion.x >= 440))
                    {
                        clp=0;
                    }

                    else if ((event.button.button == SDL_BUTTON_LEFT) && (event.motion.y <= 675 && event.motion.y >= 575) && (event.motion.x <= 810 && event.motion.x >= 440))
                    {
                        boucle=0;
                    }
                }

                if(clsave==1)
                {
                    num=numero(&quit,screen,event);
                    if(num!=-1){
                        save(current_map_level,bk.pos_img_ecran.x,perso.position.x,permi.position_map.x,maxi,maxi1, ee, num);
                        boucle=0;
                    }
                }
                if((perso.position.x==710)&&(ee==1)&&(current_map_level==1)){
                    etat_enigme=1;
                    e = generer("./enigme/enigme.txt");
                    start_time = SDL_GetTicks();
                    ee=2;
                    con1=1,con2=1,n=0;
                    initialiser_image(&question,e.quest,117,190);
                    initialiser_Boutton(&reponse11,e.rep1,e.rep11,157,327,1);
                    if(e.rep==2)
                        initialiser_Boutton(&reponse22,e.rep2,e.rep22,166,403,2);
                    else
                        initialiser_Boutton(&reponse22,e.rep2,e.rep22,166,383,2);
                    initialiser_Boutton(&reponse33,e.rep3,e.rep33,176,450,3);
                }
                if((perso.position.x==410)&&(ee==2)&&(current_map_level==2)){
                    etat_enigme=2;
                    e = generer("./enigme/enigme2.txt");
                    start_time = SDL_GetTicks();
                    ee=3;
                    con1=1,con2=1;
                    time_left=20,n=0;
                    initialiser_image(&question,e.quest,117,190);
                    if(e.rep==1){
                        initialiser_Boutton(&reponse11,e.rep1,e.rep11,107,397,1);
                        initialiser_Boutton(&reponse22,e.rep2,e.rep22,116,453,2);
                        initialiser_Boutton(&reponse33,e.rep3,e.rep33,126,518,3);
                    }
                    else{
                        initialiser_Boutton(&reponse11,e.rep1,e.rep11,157,327,1);
                        initialiser_Boutton(&reponse22,e.rep2,e.rep22,166,383,2);
                        initialiser_Boutton(&reponse33,e.rep3,e.rep33,176,450,3);
                    }
                }
                if((perso.position.x==920)&&(ee==3)&&(current_map_level==3)){
                    etat_enigme=3;
                    e = generer("./enigme/enigme3.txt");
                    start_time = SDL_GetTicks();
                    ee=4;
                    con1=1,con2=1,n=0;
                    time_left=20;
                    initialiser_image(&question,e.quest,50,25);
                    initialiser_Boutton(&reponse11,e.rep1,e.rep11,210,525,1);
                    initialiser_Boutton(&reponse22,e.rep2,e.rep22,450,500,2);
                    initialiser_Boutton(&reponse33,e.rep3,e.rep33,335,580,3);
                }

                if((etat_enigme==1)&&(time_left!=-1))
                {
                    perso.direction = 0;
                    perso.move= 0;
                    permi.move_map = 0;
                    permi.direction_map =0;
                    perso.jump_speed = 0; 
                    permi.jump_speed_map=0;

                    afficher(screen,l);

                    afficher(screen,question);
                    afficher_boutton(event,&reponse11,screen);
                    afficher_boutton(event,&reponse22,screen);
                    afficher_boutton(event,&reponse33,screen);

                    map_afrique(screen,con1);
                    con1++;
                    if(con1>24)
                        con1=1;

                    anim_e(screen,con2,e);
                    con2++;
                    if(con2>=30)
                        con2=1;

                    afficher_nb(screen,time_left,290,120,"./enigme/theme.ttf",80,255,255,255,255,0,0);
                    Uint32 current_time = SDL_GetTicks();
                    int elapsed_time = (current_time - start_time) / 1000;
                    time_left = 20 - elapsed_time;
                    
                    while (SDL_PollEvent(&event)) {
                        switch(event.type)
                        {
                            case SDL_QUIT:
                                boucle=0;
                                break;
                                
                            case SDL_MOUSEBUTTONDOWN:
                                if ((event.motion.y <= reponse11.Img[0]->h + 327 && event.motion.y >= 327) && (event.motion.x <= reponse11.Img[0]->w + 157 && event.motion.x >= 157))
                                {
                                    reponse1=1;
                                }
                                else if ((event.motion.y <= reponse22.Img[0]->h + 403 && event.motion.y >= 403) && (event.motion.x <= reponse22.Img[0]->w + 155 && event.motion.x >= 155))
                                {
                                    reponse1=2;
                                }
                                else if ((event.motion.y <= reponse33.Img[0]->h + 448 && event.motion.y >= 448) && (event.motion.x <= reponse33.Img[0]->w + 176 && event.motion.x >= 176))
                                {
                                    reponse1=3;
                                }
                                break;

                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_KP1:
                                        reponse1=1;
                                        break;
                                    case SDLK_KP2:
                                        reponse1=2;
                                        break;
                                    case SDLK_KP3:
                                        reponse1=3;
                                        break;
                                }
                                break;

                            }
                    }
                    if((reponse1!=-1)||(time_left==0))
                            etat_enigme=4;
                }

                if ((etat_enigme==4)&&(reponse1==e.rep)){
                    resol(screen,n,lg);
                    n++;
                }
                if ((etat_enigme==4)&&((reponse1!=e.rep)||(reponse1==-1))){
                    resol(screen,n,ln);
                    n++;
                }
                if ((etat_enigme==4)&&(reponse1==e.rep)&&(eer==1)){
                    maxi0=maxi0+1000;
                    maxi1++;
                    eer=2;
                }
                else if ((etat_enigme==4)&&((reponse1!=e.rep)||(reponse1==-1))&&(eer==2)){
                    maxi1--;
                    eer=2;
                }

                if((etat_enigme==2)&&(time_left!=-1))
                {
                    perso.direction = 0;
                    perso.move= 0;
                    permi.move_map = 0;
                    permi.direction_map =0;
                    perso.jump_speed = 0; 
                    permi.jump_speed_map=0;

                    afficher(screen,l);

                    afficher(screen,question);
                    afficher_boutton(event,&reponse11,screen);
                    afficher_boutton(event,&reponse22,screen);
                    afficher_boutton(event,&reponse33,screen);

                    map_afrique(screen,con1);
                    con1++;
                    if(con1>24)
                        con1=1;

                    anim_e(screen,con2,e);
                    con2++;
                    if(con2>=30)
                        con2=1;

                    afficher_nb(screen,time_left,290,120,"./enigme/theme.ttf",80,255,255,255,255,0,0);
                    Uint32 current_time = SDL_GetTicks();
                    int elapsed_time = (current_time - start_time) / 1000;
                    time_left = 20 - elapsed_time;
                    
                    while (SDL_PollEvent(&event)) {
                        switch(event.type)
                        {
                            case SDL_QUIT:
                                boucle=0;
                                break;
                                
                            case SDL_MOUSEBUTTONDOWN:
                                if ((event.motion.y <= reponse11.Img[0]->h + 327 && event.motion.y >= 327) && (event.motion.x <= reponse11.Img[0]->w + 157 && event.motion.x >= 157))
                                {
                                    reponse2=1;
                                }
                                else if ((event.motion.y <= reponse22.Img[0]->h + 403 && event.motion.y >= 403) && (event.motion.x <= reponse22.Img[0]->w + 155 && event.motion.x >= 155))
                                {
                                    reponse2=2;
                                }
                                else if ((event.motion.y <= reponse33.Img[0]->h + 448 && event.motion.y >= 448) && (event.motion.x <= reponse33.Img[0]->w + 176 && event.motion.x >= 176))
                                {
                                    reponse2=3;
                                }
                                break;

                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_KP1:
                                        reponse2=1;
                                        break;
                                    case SDLK_KP2:
                                        reponse2=2;
                                        break;
                                    case SDLK_KP3:
                                        reponse2=3;
                                        break;
                                }
                                break;

                            }
                    }
                    if((reponse2!=-1)||(time_left==0))
                            etat_enigme=5;
                }

                if ((etat_enigme==5)&&(reponse2==e.rep)){
                    resol(screen,n,lg);
                    n++;
                }
                else if ((etat_enigme==5)&&((reponse2!=e.rep)||(reponse2==-1))){
                    resol(screen,n,ln);
                    n++;
                }
                if ((etat_enigme==5)&&(reponse2==e.rep)&&(eer==2)){
                    maxi0=maxi0+1000;
                    maxi1++;
                    eer=3;
                }
                else if ((etat_enigme==5)&&((reponse2!=e.rep)||(reponse2==-1))&&(eer==2)){
                    maxi1--;
                    eer=3;
                }

                if((etat_enigme==3)&&(time_left!=-1))
                {
                    perso.direction = 0;
                    perso.move= 0;
                    permi.move_map = 0;
                    permi.direction_map =0;
                    perso.jump_speed = 0; 
                    permi.jump_speed_map=0;

                    afficher(screen,l);

                    afficher(screen,question);
                    afficher_boutton(event,&reponse11,screen);
                    afficher_boutton(event,&reponse22,screen);
                    afficher_boutton(event,&reponse33,screen);

                    map_afrique(screen,con1);
                    con1++;
                    if(con1>24)
                        con1=1;

                    anim_e(screen,con2,e);
                    con2++;
                    if(con2>=30)
                        con2=1;

                    afficher_nb(screen,time_left,290,120,"./enigme/theme.ttf",80,255,255,255,255,0,0);
                    Uint32 current_time = SDL_GetTicks();
                    int elapsed_time = (current_time - start_time) / 1000;
                    time_left = 20 - elapsed_time;
                    
                    while (SDL_PollEvent(&event)) {
                        switch(event.type)
                        {
                            case SDL_QUIT:
                                boucle=0;
                                break;
                                
                            case SDL_MOUSEBUTTONDOWN:
                                if ((event.motion.y <= reponse11.Img[0]->h + 525 && event.motion.y >= 525) && (event.motion.x <= reponse11.Img[0]->w + 211 && event.motion.x >= 211))
                                {
                                    reponse3=1;
                                }
                                else if ((event.motion.y <= reponse22.Img[0]->h + 500 && event.motion.y >= 500) && (event.motion.x <= reponse22.Img[0]->w + 450 && event.motion.x >= 450))
                                {
                                    reponse3=2;
                                }
                                else if ((event.motion.y <= reponse33.Img[0]->h + 580 && event.motion.y >= 580) && (event.motion.x <= reponse33.Img[0]->w + 335 && event.motion.x >= 335))
                                {
                                    reponse3=3;
                                }
                                break;

                            case SDL_KEYDOWN:
                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_KP1:
                                        reponse3=1;
                                        break;
                                    case SDLK_KP2:
                                        reponse3=2;
                                        break;
                                    case SDLK_KP3:
                                        reponse3=3;
                                        break;
                                }
                                break;

                            }
                    }
                    if((reponse3!=-1)||(time_left==0))
                            etat_enigme=6;
                }

                if ((etat_enigme==6)&&(reponse3==e.rep)){
                    resol(screen,n,lg);
                    n++;
                }
                else if ((etat_enigme==6)&&((reponse3!=e.rep)||(reponse3==-1))){
                    resol(screen,n,ln);
                    n++;
                }
                if ((etat_enigme==6)&&(reponse3==e.rep)&&(eer==3)){
                    maxi0=maxi0+1000;
                    maxi1++;
                    eer=4;
                }
                else if ((etat_enigme==6)&&((reponse3!=e.rep)||(reponse3==-1))&&(eer==3)){
                    maxi1--;
                    eer=4;
                }

                punch(&perso , punch_flag);
                saut(&perso, &flag, &perso.jump_speed,current_map_level);
                sautmap(&permi,&flag1,&permi.jump_speed_map);
                SDL_Delay(3);
                scrolling(&back1,&back11,&back2,&back3,&back33,&perso,current_map_level,screen);
                deplacerPerso(&perso,current_map_level);
                deplacerPersomap(&permi);
            }
        }
        else
            click1=0;

        if(click2==1)
        {
            click=0;
            num2=numero(&quit2,screen,event);
            if(num2!=0){
                charge(&current_map_level,&bk.pos_img_ecran.x,&perso.position.x,&permi.position_map.x,&maxi0,&maxi1, &ee, num2);
                if(current_map_level==1){
                    back1.pos_img_ecran.x=bk.pos_img_ecran.x;
                    back11.pos_img_ecran.x=bk.pos_img_ecran.x;
                }
                else if(current_map_level==2){
                    back2.pos_img_ecran.x=bk.pos_img_ecran.x;
                }
                else if(current_map_level==3){
                    back3.pos_img_ecran.x=bk.pos_img_ecran.x;
                    back33.pos_img_ecran.x=bk.pos_img_ecran.x;
                }
            }
            click1=1;
            click2=0;
            while (SDL_PollEvent(&event))
            {
                
                switch(event.type)
                {
                    case SDL_QUIT:
                        boucle=0;
                        break;

                    case SDL_KEYDOWN:
                        if(event.key.keysym.sym ==SDLK_m){
                            click2=0;
                            click=1;
                        }
                        break;
                }
            }
        }
        else
            click2=0;

        if(click3==1)
        {
            click=0;
            afficher(screen,settings);
            afficher_nb(screen,maxi,850,250,"./menu/Path/theme1.ttf",100,0,0,0,0,0,0);
            afficher_texte(screen,"{mute}",1020,600,"./menu/Path/theme.ttf",35,255,255,255);
            afficher_texte(screen,"{Resume}",725,600,"./menu/Path/theme.ttf",35,255,255,255);
            afficher_texte(screen,"{FULLSCREEN}",250,600,"./menu/Path/theme.ttf",35,255,255,255);    
            afficher_texte(screen,"{NORMAL}",50,600,"./menu/Path/theme.ttf",35,255,255,255);  

            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        boucle=0;
                        break;
                    
                    case SDL_MOUSEBUTTONDOWN:
               
                        if((event.motion.y <= 563 && event.motion.y >= 433) && (event.motion.x <= 1180 && event.motion.x >= 980))
                            Mix_PauseMusic();
                        
                        else if ((event.motion.y <= 563 && event.motion.y >= 433) && (event.motion.x <= 920 && event.motion.x >= 720))
                            Mix_ResumeMusic();

                        else if((event.motion.y <=335 && event.motion.y >=233) && (event.motion.x <=787 && event.motion.x >= 675))
                        { 
                            maxi = maxi + 10;
                            if (maxi > 100)
                                maxi = 100;
                            v = (maxi * MIX_MAX_VOLUME) / 100;
                            Mix_VolumeMusic(v);             
                        }

                        else if((event.motion.y <=335 && event.motion.y >=233) && (event.motion.x <=628 && event.motion.x >= 516))
                        { 
                            maxi = maxi - 10;
                            if (maxi < 0)
                                maxi = 0;
                            v = (maxi * MIX_MAX_VOLUME) / 100;
                            Mix_VolumeMusic(v);      

                        }

                        else if((event.button.button == SDL_BUTTON_LEFT)&&(event.motion.y <=563 && event.motion.y >=433) && (event.motion.x <=215 && event.motion.x >= 60)) 
                            SDL_WM_ToggleFullScreen(screen);

                        else if((event.button.button == SDL_BUTTON_LEFT)&&(event.motion.y <=563 && event.motion.y >=433) && (event.motion.x <410 && event.motion.x >= 260)) 
                            SDL_WM_ToggleFullScreen(screen);   

                        break;
                         
                    case(SDL_KEYDOWN):
                        if(event.key.keysym.sym ==SDLK_m){
                            click3=0;
                            click=1;
                        }

                        break;
                
                }
             }
        }
        else
            click3=0;

        if(cf==1){
            click1=0;
            final(screen,conf);
            conf++;
            printf("%d\n",conf);
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        boucle=0;
                        break;
                }
            }
            if(conf>=17)
            {
                afficher(screen,scf);
                afficher_nb(screen,maxi0,684,311,"./enigme/theme.ttf",80,0,0,0,0,0,0);
            }
            if(conf>=30)
            {
                afficher(screen,scf1);
                afficher_nb(screen,maxi0,684,311,"./enigme/theme.ttf",80,0,0,0,0,0,0);
                int ms=meilleur_score();
                if(maxi0>ms)
                    ms=maxi0;
                afficher_nb(screen,ms,809,472,"./enigme/theme.ttf",80,0,0,0,0,0,0);
            }
            if (conf==60){
                cf=0;
                click=1;
            }
        }  
    }


    liberer_image (back1);
    liberer_image (back2);
    liberer_image (back3);
    liberer_image (settings);
    liberer_image (mxo);
    liberer_image (xo);
    SDL_FreeSurface(BTN_START.Img[0]);
    SDL_FreeSurface(BTN_LOAD.Img[0]);
    SDL_FreeSurface(BTN_SETT.Img[0]);
    SDL_FreeSurface(BTN_QUIT.Img[0]);
    SDL_FreeSurface(BTN_SAVE.Img[0]);
    SDL_FreeSurface(BTN_RESUME.Img[0]);
    SDL_FreeSurface(BTN_QUIT2.Img[0]);
    Mix_CloseAudio();
    

    SDL_Quit();
    return 0;
}
