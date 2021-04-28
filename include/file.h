#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <SDL.h>



SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,int screenWidth, int screenHeight, const char* windowTitle);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

void print(int i, int j, int **nguon,SDL_Renderer *renderer,int Size);

void right(int i, int j,int **trang_thai,SDL_Renderer *renderer,int Size,int &so_co);

void left( int i, int j,int **nguon,int **trang_thai,int &ketqua,SDL_Renderer *renderer, int Size );

void khoi_tao_bom(int **nguon,int so_bom);

void bom_xq(int **nguon);

void ketthuc(int **nguon, int **trang_thai,int ketqua,SDL_Renderer *ren, int Size, bool &thoat);

int kiemtra(int **nguon, int **trang_thai);

void menu(SDL_Renderer* renderer, bool &thoat);

void drawtext (std ::string text, int x, int y, SDL_Renderer *renderer, int size);



#endif // FILE_H
