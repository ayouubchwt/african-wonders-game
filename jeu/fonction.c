#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "fonction.h"

void initialiser_back(image *image, char path[], int x, int y){
    (*image).url = path;
    (*image).img = IMG_Load((*image).url);
    if ((*image).img == NULL)
    {
        printf("Unable to load background image %s \n", SDL_GetError());

    }
    (*image).pos_img_ecran.x = x;
    (*image).pos_img_ecran.y = y;
    (*image).pos_img_affiche.x = 0;
    (*image).pos_img_affiche.y = 0;
    (*image).pos_img_affiche.h=SCREEN_H;
    (*image).pos_img_affiche.w=SCREEN_W;
}

void afficher_back(SDL_Surface *screen,image imge){
    SDL_BlitSurface(imge.img, &imge.pos_img_affiche, screen, &imge.pos_img_ecran);
}

void initialiser_image(image *image, char path[], int x, int y){
    (*image).url = path;
    (*image).img = IMG_Load((*image).url);
    if ((*image).img == NULL)
    {
        printf("Unable to load background image %s \n", SDL_GetError());

    }
    (*image).pos_img_ecran.x = x;
    (*image).pos_img_ecran.y = y;
    (*image).pos_img_ecran.w = (*image).img->w;
    (*image).pos_img_ecran.h = (*image).img->h;
}

void afficher(SDL_Surface *screen,image imge){
    SDL_BlitSurface(imge.img, NULL, screen, &imge.pos_img_ecran);
}

void liberer_image(image imge){
    SDL_FreeSurface(imge.img);
}

void initialiser_audio(Mix_Music *music){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", SDL_GetError());
    }
    music = Mix_LoadMUS("./menu/Path/bak.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 3.5);
}

void initialiser_audiobref(Mix_Chunk **music , char path[])
{   Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    *music = Mix_LoadWAV(path);
    if ((*music) == NULL)
    {
        printf("%s", SDL_GetError());
    }
}

void liberer_musiquebref(Mix_Chunk **music){
    Mix_FreeChunk(*music);
}

void afficher_nb(SDL_Surface* screen, int time_left, int x, int y,char path[],int t,int r1,int g1,int b1,int r2 ,int g2, int b2){
    texte txte;
    TTF_Init();
    txte.police = TTF_OpenFont(path,t);
    txte.color_txt.r = r1;
    txte.color_txt.g = g1;
    txte.color_txt.b = b1;
    txte.pos_txt.x = x;
    txte.pos_txt.y = y;
    char ch[20];
    if (time_left>=10)
        sprintf(ch, "%d", time_left);
    else if (time_left<10){
        sprintf(ch, "%d%d",0, time_left);
        if(time_left<=5){
            txte.color_txt.r = r2;
            txte.color_txt.g = g2;
            txte.color_txt.b = b2;
        }
    }
    txte.txt = TTF_RenderText_Blended(txte.police, ch, txte.color_txt);
    SDL_BlitSurface(txte.txt, NULL, screen, &txte.pos_txt);
    SDL_FreeSurface(txte.txt);
    TTF_CloseFont(txte.police);
    TTF_Quit();
}

void afficher_texte(SDL_Surface* screen,char ch[],int x, int y,char path[],int t,int r,int g, int b){
    texte txte;
    TTF_Init();
    txte.police = TTF_OpenFont(path,t);
    txte.color_txt.r = r;
    txte.color_txt.g = g;
    txte.color_txt.b = b;
    txte.pos_txt.x = x;
    txte.pos_txt.y = y;
    txte.txt = TTF_RenderText_Blended(txte.police, ch, txte.color_txt);
    SDL_BlitSurface(txte.txt, NULL, screen, &txte.pos_txt);
    SDL_FreeSurface(txte.txt);
    TTF_CloseFont(txte.police);
    TTF_Quit();
}

void anim(SDL_Surface* screen, int cp){
    image i0,i1,i2,i3;
    initialiser_image(&i0,"./menu/Back/B1.png", 0, 0);
    initialiser_image(&i1,"./menu/Back/B2.png", 0, 0);
    initialiser_image(&i2,"./menu/Back/B3.png", 0, 0);
    initialiser_image(&i3,"./menu/Back/B4.png", 0, 0);

    if(cp<=1)
        afficher(screen, i0);
    else if(cp<=2)
        afficher(screen, i1);
    else if(cp<=3)
        afficher(screen, i2);
    else if(cp<=4)
        afficher(screen, i3);

    liberer_image(i1);
    liberer_image(i2);
    liberer_image(i3);
    liberer_image(i0);
}

void anim2(SDL_Surface* screen, int cp){
    image i0,i1,i2,i3;
    initialiser_image(&i0,"./menu/Back/m1.png", 150, 255);
    initialiser_image(&i1,"./menu/Back/m2.png", 151, 260);
    initialiser_image(&i2,"./menu/Back/m3.png", 151, 260);
    initialiser_image(&i3,"./menu/Back/m4.png", 151, 260);

    if(cp<=1)
        afficher(screen, i0);
    else if(cp<=2)
        afficher(screen, i1);
    else if(cp<=3)
        afficher(screen, i2);
    else if(cp<=4)
        afficher(screen, i3);

    liberer_image(i1);
    liberer_image(i2);
    liberer_image(i3);
    liberer_image(i0);
}

void initialiser_Boutton(Boutton* BTN, char path1[], char path2[], int x, int y, int num) {
    BTN->Img[0] = IMG_Load(path1);
    BTN->Img[1] = IMG_Load(path2);
    if (BTN->Img[0] == NULL || BTN->Img[1] == NULL) {
        printf("Unable to load BUTTON %s \n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    BTN->Pos.x = x;
    BTN->Pos.y = y;
    BTN->Pos.w = BTN->Img[0]->w;
    BTN->Pos.h = BTN->Img[0]->h;
    BTN->son = Mix_LoadWAV("./menu/Path/simple.wav");
    BTN->num = num;
}

void afficher_boutton(SDL_Event event, Boutton* btn, SDL_Surface* screen){
    int flag = 0;
    SDL_Rect dstRect;

    SDL_BlitSurface(btn->Img[0], NULL, screen, &btn->Pos);
    if (btn->Img[0] == NULL)
        printf("Unable to load background image %s \n", SDL_GetError());

    dstRect = btn->Pos;
    if ((event.motion.y <= (btn->Img[0]->h) + btn->Pos.y && event.motion.y >= btn->Pos.y) && (event.motion.x <= (btn->Img[0]->w) + btn->Pos.x && event.motion.x >= btn->Pos.x)){
        SDL_BlitSurface(btn->Img[1], NULL, screen, &btn->Pos);
        flag = 1;
    }
    else if (flag == 1)
        flag = 0;
}

void afficher_boutton_clav(Boutton btn, SDL_Surface* screen){   
    SDL_BlitSurface(btn.Img[1], NULL, screen, &btn.Pos);
    if (btn.Img[1] == NULL)
        printf("Unable to load background image %s \n", SDL_GetError());
}

void initPerso(Personne *p)
{
    p->position.x = 0;
    p->position.y = SCREEN_H - 250;
    p->current_image = 0;
    p->direction = 1;
    p->move = 0;
    p->images[0] = IMG_Load("./jeu/image/jou.png");
    p->images[1] = IMG_Load("./jeu/image/jou1.png");
    p->images[2] = IMG_Load("./jeu/image/jou2.png");
    p->images[3] = IMG_Load("./jeu/image/jou3.png");
    p->images[4] = IMG_Load("./jeu/image/jou4.png");
    p->images[5] = IMG_Load("./jeu/image/jou5.png");
    p->images[6] = IMG_Load("./jeu/image/jou6.png");
    p->images[7] = IMG_Load("./jeu/image/jou7.png");
    p->images[8] = IMG_Load("./jeu/image/jour.png");
    p->images[9] = IMG_Load("./jeu/image/jour1.png");
    p->images[10] = IMG_Load("./jeu/image/jour2.png");
    p->images[11] = IMG_Load("./jeu/image/jour3.png");
    p->images[12] = IMG_Load("./jeu/image/jour4.png");
    p->images[13] = IMG_Load("./jeu/image/jour5.png");
    p->images[14] = IMG_Load("./jeu/image/jour6.png");
    p->images[15] = IMG_Load("./jeu/image/jour7.png");
}

void afficherPerso(Personne p, SDL_Surface * screen){
    SDL_BlitSurface(p.images[p.current_image], NULL, screen, &(p.position));
}

void deplacerPerso(Personne *p,int current_map_level)
{
    if(p->move == 1)
    {
        p->position.x += p->direction * 2;
        if(p->position.x <=0)
        {
            p->move = 0;
            p->position.x=0;
        }
    }
}

void saut(Personne* p,int *jump,int* jump_speed,int current_map_level) {
    if (*jump) {
        p->position.y -= *jump_speed; 
        (*jump_speed)--; 

        if (p->position.y >= SCREEN_H - 250) { 
            *jump = 0; 
            p->position.y=SCREEN_H - 250;
        }
        else if(((p->position.x>=120)&&(p->position.x<=210))&&(p->position.y>=SCREEN_H-400)&&(current_map_level==2))
        { 
                *jump = 0; 
                p->position.y=250;
                
        }
        else if(((p->position.x>=260)&&(p->position.x<=340))&&(p->position.y>=SCREEN_H-400)&&(current_map_level==2))
        { 
                *jump = 0; 
                p->position.y=240;
                
        }
        else if(((p->position.x>=370)&&(p->position.x<=470))&&(p->position.y>=SCREEN_H-400)&&(current_map_level==2))
        {
                
                *jump = 0; 
                p->position.y=250;
        }
        else if(((p->position.x>=500)&&(p->position.x<=590))&&(p->position.y>=SCREEN_H-400)&&(current_map_level==2))
        {
             
               *jump = 0; 
                p->position.y=240;
               
        }
               
    }

}
void animerPerso(Personne* p,int left)
{
    static int counter;
    const int animation_speed = 10; 
    static int change;
    counter++;
    if (counter >= animation_speed)
    {
        if(p->move == 0)
        {
            if(left)
            {
                p->current_image = 8 + change;
                change= (change + 1) % 2;
            }
            else
            {
                p->current_image = 0 + change;
                change= (change + 1) % 2;
            }
        }
        else
        {
            if(left)
            {
                p->current_image++;
                if(p->current_image < 9 || p->current_image > 15)
                {
                    p->current_image = 8;
                }
            }
            else
            {
                p->current_image--;
                if(p->current_image < 1 || p->current_image > 7)
                {
                    p->current_image = 7;
                }
               
            }
        }
        
        counter = 0;
    }
}

void scrolling(image *b, image *e,image *c,image *d,image *z,Personne *p,int current_map_level, SDL_Surface *screen)
{
    int scrollSpeed = 3,scrollSpeed1=-3;

    if((p->move == 1)&&(current_map_level==1))
    {
        b->pos_img_ecran.x+= p->direction * scrollSpeed1;
        e->pos_img_ecran.x+=p->direction *scrollSpeed1;
    }
    else if((p->move == 1)&&(current_map_level==2))
    {
        
        c->pos_img_affiche.x += p->direction * scrollSpeed;
    }
    else if((p->move == 1)&&(current_map_level==3))
    {
        d->pos_img_ecran.x += p->direction * scrollSpeed1;
        z->pos_img_ecran.x += p->direction * scrollSpeed1;
        if(p->position.x>=SCREEN_W-60){
            p->move=0;
        }
    }
}

void initicon(Personnemap *m){
    m->position_map.x = 280;
    m->position_map.y = 80;
    m->direction_map = 1;
    m->move_map = 0;
    m->nbimages=0;
    m->images[0] = IMG_Load("./jeu/imagemini/icon.png");
    m->images[1] = IMG_Load("./jeu/imagemini/icon1.png");
    m->images[2] = IMG_Load("./jeu/imagemini/icon2.png");
    m->images[3] = IMG_Load("./jeu/imagemini/icon3.png");
    m->images[4] = IMG_Load("./jeu/imagemini/icon4.png");
    m->images[5] = IMG_Load("./jeu/imagemini/icon5.png");
    m->images[6] = IMG_Load("./jeu/imagemini/left.png");
    m->images[7] = IMG_Load("./jeu/imagemini/left1.png");
    m->images[8] = IMG_Load("./jeu/imagemini/left2.png");
    m->images[9] = IMG_Load("./jeu/imagemini/left3.png");
    m->images[10] = IMG_Load("./jeu/imagemini/left4.png");
}

void afficheicon(Personnemap m, SDL_Surface * screen)
{
    SDL_BlitSurface(m.images[m.nbimages], NULL, screen, &(m.position_map));
}

void deplacerPersomap(Personnemap *m)
{
    if (m->move_map == 1)
    {   
        m->position_map.x += m->direction_map+0.95;
        
        if (m->position_map.x > SCREEN_W-335 || m->position_map.x < 280)
        {
            m->direction_map = 0;
            m->move_map = 0;
        }
     }  
}

void sautmap(Personnemap* m,int *jump_map,int* jump_speed_map)
 {
    if (*jump_map) {
        m->position_map.y -= *jump_speed_map; 
        (*jump_speed_map)--; 

        if (m->position_map.y == 80) { 
            *jump_map = 0;    
        }
    }
}

void animerPersomini(Personnemap* m,int left)
{
    static int counter = 0;
    const int animation_speed = 7; 
    static int change = 0;
    counter++;
    if (counter >= animation_speed)
    {
        if(m->move_map== 0)
        {
            if(left)
            {
                m->nbimages= 6 + change;
                change = (change + 1) % 2;
            }
            else
            {
                m->nbimages = 0 + change;
                change = (change + 1) % 2;
            }
        }
        else
        {
            if(left)
            {
                m->nbimages++;
                if(m->nbimages < 6 || m->nbimages > 10)
                {
                    m->nbimages = 6;
                }
            }
            else
            {
                m->nbimages--;
                if(m->nbimages < 1 || m->nbimages > 5)
                {
                    m->nbimages = 5;
                }
            }
        }
        
        counter = 0;
    }
}

void initializerTemps(Time *time)
{
    TTF_Init();
    time->font = TTF_OpenFont("./menu/Path/police.ttf", 25);
    time->time = 0;
    sprintf(time->timestring, "00:00");
    SDL_Color color = { 0, 0, 0 };
    time->msg = TTF_RenderText_Solid(time->font, time->timestring, color);
    time->positiontemps.x = 10;
    time->positiontemps.y = 50;
}

void afficherTemps(Time *time, SDL_Surface *ecran)
{
    SDL_Color color = { 0, 0, 0 };
    time->time++;
    if (time->time % 60 == 0)
    {
        sprintf(time->timestring, "%02d:%02d", time->time / 60 / 60, (time->time / 60) % 60);
        time->msg = TTF_RenderText_Solid(time->font, time->timestring, color);
    }
    SDL_BlitSurface(time->msg, NULL, ecran, &time->positiontemps);
    printf("%s\n",time->timestring);
}

Enigme generer(char* nom_du_fichier) {
    Enigme e;
    FILE* fichier = NULL;
    fichier=fopen(nom_du_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }
    int nb_lignes = 0;
    char buffer[256];
    while (fgets(buffer, 256, fichier)) {
        nb_lignes++;
    }
    rewind(fichier);
    srand(time(NULL));
    int num_ligne = rand() % nb_lignes +1;
    int i = 1;
    while (i < num_ligne) 
    {
        if (fgetc(fichier) == '\n')
            i++;
    }
    fscanf(fichier,"%s %s %s %s %d %s %s %s %s %s %s",e.quest,e.rep1,e.rep2,e.rep3,&e.rep,e.rep11,e.rep22,e.rep33,e.rep111,e.rep222,e.rep333);
    fclose(fichier);
    return e;
}

void afficherEnigme(Enigme e, SDL_Surface *screen){
    image question, reponse1, reponse2, reponse3;
    
    initialiser_image(&question,e.quest,100,50);
    initialiser_image(&reponse1,e.rep1,100,200);
    initialiser_image(&reponse2,e.rep2,100,300);
    initialiser_image(&reponse3,e.rep3,100,400);

    afficher(screen, question);
    afficher(screen, reponse1);
    afficher(screen, reponse2);
    afficher(screen, reponse3);

    liberer_image(question);
    liberer_image(reponse1);
    liberer_image(reponse2);
    liberer_image(reponse3);
}

void map_afrique(SDL_Surface* screen, int cp){
    image images[24];
    for (int i = 0; i < 24; i++) {
        char path[50];
        sprintf(path, "./enigme/afr/%d.png", i+1);
        initialiser_image(&images[i], path, 485, 276);
    }

    switch(cp)
    {
        case 1:
            afficher(screen, images[0]);
            break;
        case 2:
            afficher(screen, images[1]);
            break;
        case 3:
            afficher(screen, images[2]);
            break;
        case 4:
            afficher(screen, images[3]);
            break;
        case 5:
            afficher(screen, images[4]);
            break;
        case 6:
            afficher(screen, images[5]);
            break;
        case 7:
            afficher(screen, images[6]);
            break;
        case 8:
            afficher(screen, images[7]);
            break;
        case 9:
            afficher(screen, images[8]);
            break;
        case 10:
            afficher(screen, images[9]);
            break;
        case 11:
            afficher(screen, images[10]);
            break;
        case 12:
            afficher(screen, images[11]);
            break;
        case 13:
            afficher(screen, images[12]);
            break;
        case 14:
            afficher(screen, images[13]);
            break;
        case 15:
            afficher(screen, images[14]);
            break;
        case 16:
            afficher(screen, images[15]);
            break;
        case 17:
            afficher(screen, images[16]);
            break;
        case 18:
            afficher(screen, images[17]);
            break;
        case 19:
            afficher(screen, images[18]);
            break;
        case 20:
            afficher(screen, images[19]);
            break;
        case 21:
            afficher(screen, images[20]);
            break;
        case 22:
            afficher(screen, images[21]);
            break;
        case 23:
            afficher(screen, images[22]);
            break;
        case 24:
            afficher(screen, images[23]);
            break;
    }


    for (int i = 0; i < 24; i++){
        liberer_image(images[i]);
    }
}

void anim_e(SDL_Surface* screen, int cp,Enigme e){

    char* filenames[] = {e.rep111, e.rep222, e.rep333};
    image images[3];

    for (int i = 0; i < 3; i++) {
        initialiser_image(&images[i], filenames[i], 300, 500);
    }

    if(cp<=10)
        afficher(screen, images[0]);
    else if(cp<=20)
        afficher(screen, images[1]);
    else if(cp<=30)
        afficher(screen, images[2]);

    for (int i = 0; i < 3; i++){
        liberer_image(images[i]);
    }
}


void resol(SDL_Surface* screen, int cp, image img){
    if(cp<=40)
        afficher(screen, img);
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, destination, &offset);
}

int load_files(SDL_Surface** x_img,SDL_Surface** o_img){
    *x_img = IMG_Load("./menu/XO/X.png");
    if (*x_img == NULL)
    {
        fprintf(stderr, "Error loading X image: %s\n", SDL_GetError());
        return 1;
    }

    *o_img = IMG_Load("./menu/XO/O.png");
    if (*o_img == NULL)
    {
        fprintf(stderr, "Error loading O image: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

int minimax(int* board, int player)
{
    int winner = check_win(board);
    if (winner != 0) {
        if (winner == player) {
            return 1;
        } else if (winner == 3) {
            return 0;
        } else {
            return -1;
        }
    }
    
    int best_score = -2;
    int move = -1;
    
    for (int i = 0; i < 9; i++) {
        if (board[i] == 0) {
            board[i] = player;
            int score = -minimax(board, 3 - player);
            board[i] = 0;
            if (score > best_score) {
                best_score = score;
                move = i;
            }
        }
    }
    
    if (move == -1) {
        return 0;
    } else if (player == PLAYER_X) {
        return best_score;
    } else {
        return move;
    }
}

int handle_events(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, int* board, int* turn){
    int quit = 0;
    SDL_Event event;
    int mouse_x = 0, mouse_y = 0;
    int play_x = -1, play_y = -1;

    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            mouse_x = event.button.x;
            mouse_y = event.button.y;
            play_x = (mouse_x-175) / CELL_WIDTH;
            play_y = (mouse_y-300) / CELL_HEIGHT;
        }
    }

    if (*turn == PLAYER_X_TURN && play_x >= 0 && play_y >= 0 && board[play_x + play_y * BOARD_WIDTH] == EMPTY_CELL)
    {
        board[play_x + play_y * BOARD_WIDTH] = PLAYER_X;
        *turn = PLAYER_O_TURN;
        play_x = -1;
        play_y = -1;
    }

    if ((*turn == PLAYER_O_TURN)&&(!check_win(board))){
        int best_move = -1;
        int best_score = -9999;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY_CELL) {
                board[i] = PLAYER_O;
                int score = -minimax(board, PLAYER_X);
                board[i] = EMPTY_CELL;
                if (score > best_score) {
                    best_score = score;
                    best_move = i;
                }
            }
        }

        if (best_move != -1){
            board[best_move] = PLAYER_O;
            *turn = PLAYER_X_TURN;
        }
    }

    draw_board(screen, x_img, o_img,board);

    int winner = check_win(board);
    if (winner != EMPTY_CELL)
        quit = 1;

    SDL_UpdateRect(screen, 0, 0, SCREEN_W, SCREEN_H);
    SDL_Delay(10);
    return 1;
}

void draw_board(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, int* board){
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int cell = board[row * 3 + col];
            if (cell == 1)
            {
                apply_surface((col * 100+35)+175, (row * 100+25)+300, x_img, screen, NULL);
            }
            else if (cell == 2)
            {
                apply_surface((col * 100+35)+175, (row * 100+25)+300, o_img, screen, NULL);
            }
        }
    }
}

int check_win(int* board){
    for (int row = 0; row < 3; row++)
    {
        if (board[row * 3] != 0 && board[row * 3] == board[row * 3 + 1] && board[row * 3] == board[row * 3 + 2])
        {
            return board[row * 3];
        }
    }
    for (int col = 0; col < 3; col++)
    {
        if (board[col] != 0 && board[col] == board[col + 3] && board[col] == board[col + 6])
        {
            return board[col];
        }
    }
    if (board[0] != 0 && board[0] == board[4] && board[0] == board[8])
    {
        return board[0];
    }
    if (board[2] != 0 && board[2] == board[4] && board[2] == board[6])
    {
        return board[2];
    }
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            return 0;
        }
    }
    return -1;
}

void clean_up(SDL_Surface* x_img, SDL_Surface* o_img){
    if (x_img != NULL)
    {
        SDL_FreeSurface(x_img);
        x_img = NULL;
    }
    if (o_img != NULL)
    {
        SDL_FreeSurface(o_img);
        o_img = NULL;
    }
    SDL_Quit();
}

void LOAD(Boutton *BTN1, Boutton *BTN2, Boutton *BTN3, Boutton *BTN4, Boutton *BTN5, Boutton *BTN6, Boutton *BTN7, Boutton *BTN8, Boutton *BTN9, Boutton *BTN0, Boutton *BTNe,Boutton *BTNd)
{ 
    initialiser_Boutton(BTN1,"./menu/LOAD/BTN/1.png","./menu/LOAD/BTN/11.png", 490, 358, 1);
    initialiser_Boutton(BTN2,"./menu/LOAD/BTN/2.png","./menu/LOAD/BTN/22.png", 584, 358, 2);
    initialiser_Boutton(BTN3,"./menu/LOAD/BTN/3.png","./menu/LOAD/BTN/33.png", 678, 358, 3);
    initialiser_Boutton(BTN4,"./menu/LOAD/BTN/4.png","./menu/LOAD/BTN/44.png", 490, 450, 4);
    initialiser_Boutton(BTN5,"./menu/LOAD/BTN/5.png","./menu/LOAD/BTN/55.png", 584, 450, 5);
    initialiser_Boutton(BTN6,"./menu/LOAD/BTN/6.png","./menu/LOAD/BTN/66.png", 678, 450, 6);
    initialiser_Boutton(BTN7,"./menu/LOAD/BTN/7.png","./menu/LOAD/BTN/77.png", 490, 544, 7);
    initialiser_Boutton(BTN8,"./menu/LOAD/BTN/8.png","./menu/LOAD/BTN/88.png", 584, 544, 8);
    initialiser_Boutton(BTN9,"./menu/LOAD/BTN/9.png","./menu/LOAD/BTN/99.png", 678, 544, 9);
    initialiser_Boutton(BTN0,"./menu/LOAD/BTN/0.png","./menu/LOAD/BTN/00.png", 584, 634, 0);
    initialiser_Boutton(BTNe,"./menu/LOAD/BTN/e.png","./menu/LOAD/BTN/ee.png", 490, 634, 10);
    initialiser_Boutton(BTNd,"./menu/LOAD/BTN/d.png","./menu/LOAD/BTN/dd.png", 678, 634, 10);
}

void aff(SDL_Surface*screen,SDL_Event event, Boutton BTN1, Boutton BTN2, Boutton BTN3, Boutton BTN4, Boutton BTN5, Boutton BTN6, Boutton BTN7, Boutton BTN8, Boutton BTN9, Boutton BTN0, Boutton BTNe,Boutton BTNd)
{      
    afficher_boutton(event,&BTN1,screen);
    afficher_boutton(event,&BTN2,screen);
    afficher_boutton(event,&BTN3,screen);
    afficher_boutton(event,&BTN4,screen);
    afficher_boutton(event,&BTN5,screen);
    afficher_boutton(event,&BTN6,screen);
    afficher_boutton(event,&BTN7,screen);
    afficher_boutton(event,&BTN8,screen);
    afficher_boutton(event,&BTN9,screen);
    afficher_boutton(event,&BTN0,screen);
    afficher_boutton(event,&BTNe,screen);
    afficher_boutton(event,&BTNd,screen);
}

int numero(int *quit,SDL_Surface*screen,SDL_Event event)
{
    image back,t1,t2;
    Boutton BTN1,BTN2,BTN3,BTN4,BTN5,BTN6,BTN7,BTN8,BTN9,BTN0,BTNe,BTNd;
    int num=-1,cn1=0,cn2=0,l=0,k=-1,k1=-1;
    char *pp,*pp2;
    image bt,bt2;
    LOAD(&BTN1,&BTN2,&BTN3,&BTN4,&BTN5,&BTN6,&BTN7,&BTN8,&BTN9,&BTN0,&BTNe,&BTNd);
    initialiser_image(&back,"./menu/LOAD/back.png",0,0);
    initialiser_image(&t1,"./menu/LOAD/t1.png",477,235);
    initialiser_image(&t2,"./menu/LOAD/t2.png",488,247);

    while (*quit)
    {                                     
        SDL_Flip(screen);
        afficher(screen,back);
        afficher(screen,t1);
        afficher(screen,t2);

        aff(screen,event,BTN1,BTN2,BTN3,BTN4,BTN5,BTN6,BTN7,BTN8,BTN9,BTN0,BTNe,BTNd);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                        *quit = 0;
                        break;

                case SDL_MOUSEBUTTONDOWN:
                    if((l==0)&&(cn1==0))
                    {
                        if ((event.motion.y <= BTN1.Img[0]->w + 357 && event.motion.y >= 357) && (event.motion.x <= BTN1.Img[0]->w + 490 && event.motion.x >= 490))
                        {
                            pp="./menu/LOAD/BTN/001.png";
                            cn1=1;
                            k=1;
                        }
                        else if ((event.motion.y <= BTN2.Img[0]->h + 357 && event.motion.y >= 357) && (event.motion.x <= BTN1.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp="./menu/LOAD/BTN/002.png";
                            cn1=1;
                            k=2;
                        }
                        else if ((event.motion.y <= BTN3.Img[0]->h + 357 && event.motion.y >= 357) && (event.motion.x <= BTN3.Img[0]->w + 678 && event.motion.x >= 678))
                        {
                            pp="./menu/LOAD/BTN/003.png";
                            cn1=1;
                            k=3;
                        }
                        else if ((event.motion.y <= BTN4.Img[0]->h + 450 && event.motion.y >= 450) && (event.motion.x <= BTN4.Img[0]->w + 490 && event.motion.x >= 490))
                        {
                            pp="./menu/LOAD/BTN/004.png";
                            cn1=1;
                            k=4;
                        }
                        else if ((event.motion.y <= BTN5.Img[0]->h + 450 && event.motion.y >= 450) && (event.motion.x <= BTN5.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp="./menu/LOAD/BTN/005.png";
                            cn1=1;
                            k=5;
                        }
                        else if ((event.motion.y <= BTN6.Img[0]->h + 450 && event.motion.y >= 450) && (event.motion.x <= BTN6.Img[0]->w + 678 && event.motion.x >= 678))
                        {
                            pp="./menu/LOAD/BTN/006.png";
                            cn1=1;
                            k=6;
                        }
                        else if ((event.motion.y <= BTN7.Img[0]->h + 544 && event.motion.y >= 544) && (event.motion.x <= BTN7.Img[0]->w + 490 && event.motion.x >= 490))
                        {
                            pp="./menu/LOAD/BTN/007.png";
                            cn1=1;
                            k=7;
                        }
                        else if ((event.motion.y <= BTN8.Img[0]->h + 544 && event.motion.y >= 544) && (event.motion.x <= BTN8.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp="./menu/LOAD/BTN/008.png";
                            cn1=1;
                            k=8;
                        }
                        else if ((event.motion.y <= BTN9.Img[0]->h + 544 && event.motion.y >= 544) && (event.motion.x <= BTN9.Img[0]->w + 678 && event.motion.x >= 678))
                        {
                            pp="./menu/LOAD/BTN/009.png";
                            cn1=1;
                            k=9;
                        }
                        else if ((event.motion.y <= BTN0.Img[0]->h + 634 && event.motion.y >= 634) && (event.motion.x <= BTN0.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp="./menu/LOAD/BTN/000.png";
                            cn1=1;
                            k=0;
                        }
                        if(cn1==1){
                            l=1;
                            initialiser_image(&bt,pp,560,252);
                        }

                    }

                    else if((l==1)&&(cn2==0))
                    {
                        if ((event.motion.y <= BTN1.Img[0]->w + 357 && event.motion.y >= 357) && (event.motion.x <= BTN1.Img[0]->w + 490 && event.motion.x >= 490))
                        {
                            pp2="./menu/LOAD/BTN/001.png";
                            cn2=1;
                            k1=1;
                        }
                        else if ((event.motion.y <= BTN2.Img[0]->h + 357 && event.motion.y >= 357) && (event.motion.x <= BTN1.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp2="./menu/LOAD/BTN/002.png";
                            cn2=1;
                            k1=2;
                        }
                        else if ((event.motion.y <= BTN3.Img[0]->h + 357 && event.motion.y >= 357) && (event.motion.x <= BTN3.Img[0]->w + 678 && event.motion.x >= 678))
                        {
                            pp2="./menu/LOAD/BTN/003.png";
                            cn2=1;
                            k1=3;
                        }
                        else if ((event.motion.y <= BTN4.Img[0]->h + 450 && event.motion.y >= 450) && (event.motion.x <= BTN4.Img[0]->w + 490 && event.motion.x >= 490))
                        {
                            pp2="./menu/LOAD/BTN/004.png";
                            cn2=1;
                            k1=4;
                        }
                        else if ((event.motion.y <= BTN5.Img[0]->h + 450 && event.motion.y >= 450) && (event.motion.x <= BTN5.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp2="./menu/LOAD/BTN/005.png";
                            cn2=1;
                            k1=5;
                        }
                        else if ((event.motion.y <= BTN6.Img[0]->h + 450 && event.motion.y >= 450) && (event.motion.x <= BTN6.Img[0]->w + 678 && event.motion.x >= 678))
                        {
                            pp2="./menu/LOAD/BTN/006.png";
                            cn2=1;
                            k1=6;
                        }
                        else if ((event.motion.y <= BTN7.Img[0]->h + 544 && event.motion.y >= 544) && (event.motion.x <= BTN7.Img[0]->w + 490 && event.motion.x >= 490))
                        {
                            pp2="./menu/LOAD/BTN/007.png";
                            cn2=1;
                            k1=7;
                        }
                        else if ((event.motion.y <= BTN8.Img[0]->h + 544 && event.motion.y >= 544) && (event.motion.x <= BTN8.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp2="./menu/LOAD/BTN/008.png";
                            cn2=1;
                            k1=8;
                        }
                        else if ((event.motion.y <= BTN9.Img[0]->h + 544 && event.motion.y >= 544) && (event.motion.x <= BTN9.Img[0]->w + 678 && event.motion.x >= 678))
                        {
                            pp2="./menu/LOAD/BTN/009.png";
                            cn2=1;
                            k1=9;
                        }
                        else if ((event.motion.y <= BTN0.Img[0]->h + 634 && event.motion.y >= 634) && (event.motion.x <= BTN0.Img[0]->w + 584 && event.motion.x >= 584))
                        {
                            pp2="./menu/LOAD/BTN/000.png";
                            cn2=1;
                            k1=0;
                        }
                        if(cn2==1){
                            l=1;
                            initialiser_image(&bt2,pp2,607,252);
                        }

                    }
                    if ((cn2==1)&&(event.motion.y <= BTNd.Img[0]->h + 634 && event.motion.y >= 634) && (event.motion.x <= BTNd.Img[0]->w + 676 && event.motion.x >= 676))
                    {
                        cn2=0;
                        l=1;
                    }
                    else if ((cn1==1)&&(event.motion.y <= BTNd.Img[0]->h + 634 && event.motion.y >= 634) && (event.motion.x <= BTNd.Img[0]->w + 676 && event.motion.x >= 676))
                    {
                        cn1=0;
                        l=0;
                    }
                    if ((cn1==1)&&(cn2==1)&&(event.motion.y <= BTNe.Img[0]->h + 634 && event.motion.y >= 634) && (event.motion.x <= BTNe.Img[0]->w + 490 && event.motion.x >= 490))
                    {
                        num=k*10+k1;
                        printf("%d\n",num);
                        *quit=0;
                    }
                    
                    break;
            }
        }
        if(cn1==1)
            afficher(screen,bt);
        if(cn2==1)
            afficher(screen,bt2);
    }
    return num;
}

void save(int lvl,int pbx, int pxp,int pxmp,int s,int v, int ee, int id)
{
    FILE *f=NULL;

    f=fopen("./menu/LOAD/load.txt","a");

    fprintf(f,"%d %d %d %d %d %d %d %d\n",lvl,pbx,pxp,pxmp,s,v,ee,id);

    fclose(f);
}

void charge(int *lvl,Sint16* pbx,Sint16* pxp, Sint16* pxmp, int* s, int* v, int *ee,int id)
{
    int num;
    FILE* f = NULL;

    f = fopen("./menu/LOAD/load.txt", "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }
    else{
        while (fscanf(f, "%d %hd %hd %hd %d %d %d %d",lvl,pbx,pxp,pxmp,s, v, ee,&num) == 8) {
            if (num == id) {
                fclose(f);
                return;
            }
        }
    }

    fclose(f);
}

int meilleur_score()
{
    int ms = 0;
    int lvl, pbx, pxp, pxmp, s, v, num,ee;

    FILE* f = fopen("./menu/LOAD/load.txt", "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return ms;
    } else {
        while (fscanf(f, "%d %d %d %d %d %d %d %d", &lvl, &pbx, &pxp, &pxmp, &s, &v, &num, &ee) == 8) {
            if (s > ms) {
                ms = s;
            }
        }
    }
    fclose(f);
    return ms;
}

void initialisation_enemy(enemi *e)
{
    int h = 1852/6, w = 1300/4 ;
    e->sprite = IMG_Load("./jeu/sprite.png");
    if(e->sprite == NULL)
    {
        printf("couldnt load sprite");
    }
    e->frame.w = w ;
    e->frame.h = h ;
    e->direction1 = 1 ;
    e->pos_img_affiche.x=120;
    e->pos_img_affiche.y=SCREEN_H - 390;
    e->pos_img_affiche.w=w ;
    e->pos_img_affiche.h=h ;
}
void afficher_enemy(SDL_Surface *screen, enemi e)
{
    SDL_BlitSurface(e.sprite, &(e.frame), screen, &(e.pos_img_affiche));
}

int detect_collision(enemi e, Personne e1 )
{
    if (e.pos_img_affiche.x < e1.position.x + e1.position.w &&
            e.pos_img_affiche.x + e.pos_img_affiche.w > e1.position.x &&
            e.pos_img_affiche.y < e1.position.y + e1.position.h &&
            e.pos_img_affiche.y + e.pos_img_affiche.h > e1.position.y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void deplacer_enemy(enemi *e )
{
    int posMax, posMin ;
    srand(time(0));
    do
    {
        posMax = (rand() % (1000 - 5 + 1)) + 5;
        posMin = (rand() % 500 - 0 + 1) + 0;
    }
    while((posMax - posMin) < 100);
    if (e->pos_img_affiche. x > posMax)
    {
        e->direction1 =-1;
        e->direction = 1 ;
    }
    if(e->pos_img_affiche. x < posMin)
    {
        e->direction1 = 1 ;
        e->direction = 0;
    }
    if(e-> direction1 == 1)
    {
        e->pos_img_affiche.x  = e->pos_img_affiche.x + 2 ;
    }
    else if (e->direction1 == -1)
    {
        e->pos_img_affiche.x = e->pos_img_affiche.x  - 2 ;
    }
    else
    {
        e->pos_img_affiche.x = e->pos_img_affiche.x;
    }
}

void animer_enemy(enemi* e)
{
    static Uint32 lastFrameTime = 0;
    Uint32 currentFrameTime = SDL_GetTicks();
    Uint32 elapsedTime = currentFrameTime - lastFrameTime;
    Uint32 animationDelay = 100;

    if (elapsedTime >= animationDelay)
    {
        e->frame.y = e->direction * e->frame.h;
        e->frame.x += e->frame.w;

        if (e->frame.x >= e->sprite->w)
        {
            e->frame.x = 0;
        }

        lastFrameTime = currentFrameTime;
    }
}

void deplacer_IA(enemi *e, Personne perso, int speed)
{
    int collision_flag ;
    float dist ;
    dist = perso.position.x - (e->pos_img_affiche.x + 1800/16) ;
    collision_flag = detect_collision(*e, perso);
    if (perso.position.y - perso.position.h < e->pos_img_affiche.y){
                e->pos_img_affiche.x = e->pos_img_affiche.x;
                e->direction1  = 0 ;
                e->direction = 2 ;

    }
    else if (collision_flag == 1 )
    {
        if (collision_flag == 1 &&   e->pos_img_affiche.x+200 < perso.position.x -5 )
        {
            e->direction1  = 0 ;
            e->direction = 4 ;
        }
        if (collision_flag == 1 &&  e->pos_img_affiche.x+200 > perso.position.x -5 )
        {
            e->direction1  = 0 ;
            e->direction = 5 ;
        }
    }
    else if (abs(dist)<750 && abs(dist)>650)
    {
        e->pos_img_affiche.x = e->pos_img_affiche.x;
        if (e->direction1 == 1 )
        {
            e->direction = 2 ;
        }
        if(e->direction1 == -1)
        {
            e->direction = 3 ;
        }
    }
    else if (abs(dist)<650)
    {

        if (dist > 0)
        {
            e->pos_img_affiche.x += speed;
            e->direction1 = 1;
            e->direction = 0;
        }
        else if(dist < 0 )
        {
            e->pos_img_affiche.x -= speed;
            e->direction1 = -1;
            e->direction = 1 ;
        }
    }
    else
    {
        deplacer_enemy(e);
    }
}

void liberer_enemy(enemi e)
{
    SDL_FreeSurface(e.sprite);
}

void final(SDL_Surface* screen, int cp){
    image i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15;
    initialiser_image(&i1,"./final/1.png", 0,0);
    initialiser_image(&i2,"./final/2.png", 0,0);
    initialiser_image(&i3,"./final/3.png", 0,0);
    initialiser_image(&i4,"./final/4.png", 0,0);
    initialiser_image(&i5,"./final/5.png", 0,0);
    initialiser_image(&i6,"./final/6.png", 0,0);
    initialiser_image(&i7,"./final/7.png", 0,0);
    initialiser_image(&i8,"./final/8.png", 0,0);
    initialiser_image(&i9,"./final/9.png", 0,0);
    initialiser_image(&i10,"./final/10.png", 0,0);
    initialiser_image(&i11,"./final/11.png", 0,0);
    initialiser_image(&i12,"./final/12.png", 0,0);
    initialiser_image(&i13,"./final/13.png", 0,0);
    initialiser_image(&i14,"./final/14.png", 0,0);
    initialiser_image(&i15,"./final/15.png", 0,0);
    
    if(cp<=2)
        afficher(screen, i1);
    else if(cp<=3)
        afficher(screen, i2);
    else if(cp<=4)
        afficher(screen, i3);
    else if(cp<=5)
        afficher(screen, i4);
    else if(cp<=6)
        afficher(screen, i5);
    else if(cp<=7)
        afficher(screen, i6);
    else if(cp<=8)
        afficher(screen, i7);
    else if(cp<=9)
        afficher(screen, i8);
    else if(cp<=10)
        afficher(screen, i9);
    else if(cp<=11)
        afficher(screen, i10);
    else if(cp<=12)
        afficher(screen, i11);
    else if(cp<=13)
        afficher(screen, i12);
    else if(cp<=14)
        afficher(screen, i13);
    else if(cp<=15)
        afficher(screen, i14);
    else if(cp<=16)
        afficher(screen, i15);
}

void punch(Personne *perso , int punch_flag){
    if (punch_flag == 1 ) {
    //modifie the animation fonction and call it to do a punch animation the add a punch sound 
    }
}
