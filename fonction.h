#ifndef FONCTION_H
#define FONCTION_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_H 750
#define SCREEN_W 1200
#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3
#define EMPTY_CELL 0
#define PLAYER_X 1
#define PLAYER_O 2
#define PLAYER_TURN 0
#define PLAYER_X_TURN 1
#define PLAYER_O_TURN 2
#define CELL_WIDTH 100
#define CELL_HEIGHT 100
#define NO_WINNER 0

typedef struct {
    char *url;
    SDL_Rect pos_img_affiche;
    SDL_Rect pos_img_ecran;
    SDL_Surface *img;
} image;

typedef struct {
    SDL_Rect position;
    SDL_Surface *images[16];
    int current_image;
    int direction;
    int move;
    int jump;
    int jump_speed;
}Personne;

typedef struct 
{
    SDL_Rect position_map;
    SDL_Surface *images[11];
    float direction_map;
    int move_map;
    int jump_map;
    int jump_speed_map;
    int nbimages;
} Personnemap;

typedef struct{
    SDL_Surface* Img[2];
    SDL_Rect Pos;
    Mix_Chunk *son;
    int num;
}Boutton;

typedef struct
{
    SDL_Surface *txt;
    SDL_Rect pos_txt;
    SDL_Color color_txt;
    TTF_Font *police;
}texte;

typedef struct {
    char quest[100];
    char rep1[100];
    char rep2[100];
    char rep3[100];
    char rep11[100];
    char rep22[100];
    char rep33[100];
    char rep111[100];
    char rep222[100];
    char rep333[100];
    int rep;
} Enigme;

typedef struct Time 
{
    SDL_Surface *msg;
    TTF_Font *font;
    SDL_Rect positiontemps;
    int time;
    char timestring[20];
 }Time; 

typedef struct
{
    SDL_Rect pos_img_affiche;
    SDL_Rect frame;
    SDL_Surface *sprite;
    int direction1;
    int direction; 
}enemi;

void initialiser_back(image *image, char path[], int x, int y);

void afficher_back(SDL_Surface *screen,image imge);

void initialiser_image(image *image, char path[], int x, int y);

void afficher(SDL_Surface *screen,image imge);

void liberer_image(image imge);

void initialiser_audio(Mix_Music *music);

void initialiser_audiobref(Mix_Chunk **music , char path[]);

void liberer_musiquebref(Mix_Chunk **music);

void afficher_nb(SDL_Surface* screen, int time_left, int x, int y,char path[],int t,int r1,int g1,int b1,int r2 ,int g2, int b2);

void afficher_texte(SDL_Surface* screen,char ch[],int x, int y,char path[],int t,int r,int g, int b);

void anim(SDL_Surface* screen, int cp);

void anim2(SDL_Surface* screen, int cp);

void initialiser_Boutton(Boutton* BTN, char path1[], char path2[], int x, int y, int num);

void afficher_boutton(SDL_Event event, Boutton* btn, SDL_Surface* screen);

void afficher_boutton_clav(Boutton btn, SDL_Surface* screen);

void initPerso(Personne *p);

void afficherPerso(Personne p, SDL_Surface * screen);

void deplacerPerso(Personne *p,int current_map_level);

void saut(Personne* p,int *jump,int* jump_speed,int current_map_level);

void animerPerso(Personne* p,int left);

void scrolling(image *b, image *e,image *c,image *d,image *z,Personne *p,int current_map_level, SDL_Surface *screen);

void initicon(Personnemap *m);

void afficheicon(Personnemap m, SDL_Surface * screen);

void deplacerPersomap(Personnemap *m);

void sautmap(Personnemap* m,int *jump_map,int* jump_speed_map);

void animerPersomini(Personnemap* m,int left);

void initializerTemps(Time *time);

void afficherTemps(Time *time,SDL_Surface *ecran);

Enigme generer(char* nom_du_fichier);

void afficherEnigme(Enigme e, SDL_Surface *screen);

void map_afrique(SDL_Surface* screen, int cp);

void anim_e(SDL_Surface* screen, int cp,Enigme e);

void resol(SDL_Surface* screen, int cp, image img);

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

int load_files(SDL_Surface** x_img,SDL_Surface** o_img);

int minimax(int* board, int player);

int handle_events(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, int* board, int* turn);

void draw_board(SDL_Surface* screen, SDL_Surface* x_img, SDL_Surface* o_img, int* board);

int check_win(int* board);

void clean_up(SDL_Surface* x_img, SDL_Surface* o_img);

void LOAD(Boutton *BTN1, Boutton *BTN2, Boutton *BTN3, Boutton *BTN4, Boutton *BTN5, Boutton *BTN6, Boutton *BTN7, Boutton *BTN8, Boutton *BTN9, Boutton *BTN0, Boutton *BTNe,Boutton *BTNd);

void aff(SDL_Surface*screen,SDL_Event event, Boutton BTN1, Boutton BTN2, Boutton BTN3, Boutton BTN4, Boutton BTN5, Boutton BTN6, Boutton BTN7, Boutton BTN8, Boutton BTN9, Boutton BTN0, Boutton BTNe,Boutton BTNd);

int numero(int *quit,SDL_Surface*screen,SDL_Event event);

void save(int lvl,int pbx,int pxp,int pxmp,int s,int v, int ee, int id);

void charge(int *lvl,Sint16* pbx, Sint16* pxp, Sint16* pxmp, int* s, int* v, int *ee,int id);

int meilleur_score();

void initialisation_enemy(enemi *e);

void afficher_enemy(SDL_Surface *screen, enemi e);

void animer_enemy(enemi *e);

int detect_collision(enemi e, Personne e1);

void deplacer_enemy(enemi *e );

void deplacer_IA(enemi *e , Personne perso , int speed);

void liberer_enemy(enemi e);

void final(SDL_Surface* screen, int cp);

void punch(Personne *perso , int punch_flag);

#endif
