#include <iostream>
#include <SDL.h>
#include <string.h>

#include <file.h>
#include <SDL_ttf.h>
#include <time.h>


const int SCREEN_WIDTH = 380;
const int SCREEN_HEIGHT = 730;
const int hang = 20;
const int cot = 10;
const int so_bom = 30;


SDL_Window* window;
SDL_Renderer* renderer;

const char* WINDOW_TITLE = "Minesweeper";

int main(int argc, char* argv[])
{
    if (TTF_Init() < 0)
    {
        SDL_Log("%s", TTF_GetError());
        return -1;
    }
    initSDL(window, renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    SDL_RenderClear(renderer);
    bool thoat=false;

    menu(renderer,thoat);


    while(true)
    {
        if (thoat==true) break;

        int so_co =30;

        int **nguon =new int *[20];
        for(int i=0; i<20; i++)
            nguon[i] = new int [10];

        for (int i=0;i<20; i++)
            for (int j=0; j<10; j++)
                nguon[i][j]=0;

        int **trang_thai = new int *[20];
        for(int i=0; i<20; i++)
            trang_thai[i] = new int [10];

        for (int i=0;i<20; i++)
            for (int j=0; j<10; j++)
                trang_thai[i][j]=0;
        SDL_Texture *bg=loadTexture("anh\\nen3.bmp", renderer);
        SDL_Texture *co=loadTexture("anh\\co.bmp", renderer);

        SDL_Texture *background = loadTexture("anh\\bg.bmp", renderer);
        renderTexture( background, renderer, 0, 0,SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_Texture *nen_o1=loadTexture("anh\\nen.bmp", renderer);
        SDL_Texture *nen_o2=loadTexture("anh\\nen1.bmp", renderer);

        SDL_Texture *button=loadTexture("anh\\replay.bmp", renderer);
        renderTexture( button, renderer, 25, 10, 88, 36);

        button=loadTexture("anh\\exit.bmp", renderer);
        renderTexture( button, renderer, 25, 50, 88, 36);

        khoi_tao_bom(nguon,so_bom);
        bom_xq(nguon);

        for (int i=0; i<hang; i++)
        {
            for (int j=0; j<cot; j++)
            {
                if ((i+j)%2==0)
                    renderTexture(nen_o1, renderer, 40 + 30 * j,100 + 30 * i,30,30);
                else
                    renderTexture(nen_o2, renderer, 40 + 30 * j,100 + 30 * i,30,30);

            }
        };

        std::string s = std::to_string(30);
        drawtext(s, 270,15,renderer,40);
        renderTexture(co, renderer, 313,20,35,35);
        SDL_RenderPresent(renderer);

        SDL_Event e;
        while (thoat == false)
        {
            int ketqua=0;

            // Đợi 10 mili giây
            SDL_Delay(10);

            // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
            if ( SDL_WaitEvent(&e) == 0) continue;

            // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
            if (e.type == SDL_QUIT)
            {
                thoat=true;
                break;
            }

            // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
            {
                thoat = true;
                break;
            }

          //   Nếu chuột (mouse) được nhấn (xuống)
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT && e.button.x>25 && e.button.x<113 && e.button.y>10 && e.button.y<46)
                {
                    thoat = false;
                    break;
                }
                else if (e.button.button == SDL_BUTTON_LEFT && e.button.x>25 && e.button.x<113 && e.button.y>50 && e.button.y<86)
                {
                    menu(renderer,thoat);
                    break;
                }
                if (e.button.x>40 && e.button.x<340 && e.button.y>100 && e.button.y<700)

                {
                    int x1,x2;

                    x1=(e.button.y-100)/30;
                    x2=(e.button.x-40)/30;

                    if (e.button.button == SDL_BUTTON_LEFT)
                        left(x1,x2,nguon,trang_thai,ketqua,renderer,30);

                    else
                        right(x1,x2,trang_thai,renderer,30,so_co);

                };
                if (ketqua != -1)
                ketqua = kiemtra(nguon,trang_thai);
            };
            if (ketqua !=0)
            {
                ketthuc(nguon,trang_thai,ketqua,renderer,30,thoat);
                break;
            }
        };

        SDL_DestroyTexture(background);
        SDL_DestroyTexture(button);
        SDL_DestroyTexture(nen_o1);
        SDL_DestroyTexture(nen_o2);
        SDL_DestroyTexture(bg);
        SDL_DestroyTexture(co);

        for(int i = 0; i < 20; i++)
            delete []nguon[i];
        delete []nguon;
        for(int i = 0; i < 20; i++)
            delete []trang_thai[i];
        delete []trang_thai;

        if (thoat == true) break;
    };

    quitSDL(window,renderer);
    TTF_Quit();





    return 0;
};




