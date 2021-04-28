#include "file.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL_ttf.h>

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
	//Khởi tạo là nullptr để tránh lỗi 'dangling pointer'
	SDL_Texture *texture = nullptr;
	//Nạp ảnh từ tên file (với đường dẫn)
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//Nếu không có lỗi, chuyển đổi về dạng texture and và trả về
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Đảm bảo việc chuyển đổi không có lỗi
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface",0);
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP",0);
	}
	return texture;
};


	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
};



void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
};


void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,int screenWidth, int screenHeight, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);

#ifndef LAB
    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
#else
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
#endif // LAB

    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
};


void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
};

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}



void print(int i, int j, int **nguon,SDL_Renderer*renderer,int Size)
{
    SDL_Texture *in = NULL;
    if ((i+j)%2==0)
        in = loadTexture("anh\\rong1.bmp", renderer);
    else
        in = loadTexture("anh\\rong3.bmp", renderer);
    renderTexture(in, renderer, j*Size+40, i*Size+100,30, 30);
    if (nguon[i][j] == 1)
        in = loadTexture("anh\\1bom.bmp", renderer);
    else if (nguon[i][j] == 2)
        in = loadTexture("anh\\2bom.bmp", renderer);
    else if (nguon[i][j] == 3)
        in = loadTexture("anh\\3bom.bmp", renderer);
    else if (nguon[i][j] == 4)
        in = loadTexture("anh\\4bom.bmp", renderer);
    else if (nguon[i][j] == 5)
        in = loadTexture("anh\\5bom.bmp", renderer);
    else if (nguon[i][j] == 6)
        in = loadTexture("anh\\6bom.bmp", renderer);
    else if (nguon[i][j] == 7)
        in = loadTexture("anh\\7bom.bmp", renderer);
    else if (nguon[i][j] == 8)
        in = loadTexture("anh\\8bom.bmp", renderer);

    renderTexture(in, renderer, j*Size+40, i*Size+100,30, 30);

    SDL_DestroyTexture(in);

};
void left( int i, int j,int **nguon,int **trang_thai,int &ketqua,SDL_Renderer*renderer,int Size )
{
    if (nguon[i][j] == -1 && trang_thai[i][j] == 0 )
    {
        ketqua = -1;
        return;
    };

    if (trang_thai[i][j] == 1 || trang_thai[i][j] == -1)
        return;

    if (nguon[i][j] == 0 && trang_thai[i][j] == 0 )
    {
        trang_thai[i][j] = 1;
        print( i, j, nguon,renderer,Size);
        for (int p = 0; p < 20; p++)
            for (int u = 0; u < 20; u++)
                for (int v = 0; v < 10; v++)
                {
                    if (trang_thai[u][v] == 1 || trang_thai[u][v] == -1)
                        continue;
                    if (u > 0)
                    {
                        if (nguon[u-1][v] == 0 && trang_thai[u-1][v] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u, v,nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (u < 19)
                    {
                        if (nguon[u+1][v] == 0 && trang_thai[u+1][v] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v, nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (v > 0)
                    {
                        if (nguon[u][v-1] == 0 && trang_thai[u][v-1] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v,nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (v < 9)
                    {
                        if (nguon[u][v+1] == 0 && trang_thai[u][v+1] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v,nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (u > 0 && v > 0)
                    {
                        if (nguon[u-1][v-1] == 0 && trang_thai[u-1][v-1] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v,nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (u < 19 && v > 0)
                    {
                        if (nguon[u+1][v-1] == 0 && trang_thai[u+1][v-1] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v,nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (u > 0 && v < 9)
                    {
                        if (nguon[u-1][v+1] == 0 && trang_thai[u-1][v+1] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v,nguon,renderer,Size);
                                continue;
                            }
                    };
                    if (u < 19 && v < 9)
                    {
                        if (nguon[u+1][v+1] == 0 && trang_thai[u+1][v+1] == 1)
                            {
                                trang_thai[u][v] = 1;
                                print(u,v,nguon,renderer,Size);
                                continue;
                            }
                    }

                }
    };

    if (nguon[i][j] > 0 && trang_thai[i][j] == 0 )
    {
        trang_thai[i][j] = 1;
        print(i,j,nguon,renderer,Size);
    }
    SDL_RenderPresent(renderer);
};


void right(int i, int j ,int **trang_thai,SDL_Renderer*renderer,int Size, int & so_co)
{
    if (trang_thai[i][j] == 1 || (trang_thai[i][j]==0 && so_co == 0))
        return;

    SDL_Texture *co = NULL;

    if (trang_thai[i][j] == 0 )
    {
        trang_thai[i][j] = -1;
        so_co -= 1;
        co = loadTexture("anh\\co.bmp", renderer);
    }

    else if (trang_thai[i][j] == -1)
    {
        trang_thai[i][j] = 0;
        so_co += 1;
        if ((i+j)%2 == 0)
            co = loadTexture("anh\\nen.bmp", renderer);
        else
            co = loadTexture("anh\\nen1.bmp", renderer);
    };
    SDL_Texture *bg=loadTexture("anh\\nen3.bmp", renderer);
    SDL_Texture *co1=loadTexture("anh\\co.bmp", renderer);
    renderTexture(bg, renderer, 115,0,265,99);
    renderTexture(co1, renderer, 313,20,35,35);

    std::string s = std::to_string(so_co);
    if (so_co>9)
        drawtext(s, 270,15,renderer,40);
    else drawtext(s, 290,15,renderer,40);
    renderTexture(co, renderer,j*Size +40 ,i*Size+100 ,30,30);
    SDL_RenderPresent(renderer);

};

void khoi_tao_bom(int **nguon,int so_bom)
{

    int check[so_bom] = {-1};
    srand((int)time(0));
    int a = 0;
    while (true)
    {
        bool b=1;
        int k;
        k = rand() % 200 ;

        for (int j = 0; j < so_bom; j++)
        {
            if (k == check[j])
                b = 0;

        }
        if( b == 0)
            continue;

        check[a] = k;
        a += 1;

        int x1,x2;
        x2 = k % 10;
        x1 = k / 10;

        nguon[x1][x2] -= 1;

        if (a == so_bom)
            return;
    }

};
void bom_xq( int **nguon)
{
    for (int u = 0; u < 20; u++)
        for (int v = 0; v < 10; v++)
        {
            if(nguon[u][v] != 0)
                continue;

            if (u > 0)
            {
                if (nguon[u-1][v] == -1)
                    nguon[u][v] += 1;
            };

            if (u < 19)
            {
                if (nguon[u+1][v] == -1)
                    nguon[u][v] += 1;
            };

            if (v > 0)
            {
                if (nguon[u][v-1] == -1)
                    {
                        nguon[u][v] += 1;
                    }
            };

            if (v < 9)
            {
                if (nguon[u][v+1] == -1)
                    {
                        nguon[u][v] += 1;
                    }
            };

            if (u > 0 && v > 0)
            {
                if (nguon[u-1][v-1] == -1)
                    {
                        nguon[u][v] += 1;
                    }
            };

            if (u < 19 && v > 0)
            {
                if (nguon[u+1][v-1] == -1)
                    {
                        nguon[u][v] += 1;
                    }
            };

            if (u > 0 && v < 9)
            {
                if (nguon[u-1][v+1] == -1)
                    {
                        nguon[u][v] += 1;
                    }
            };

            if (u < 19 && v < 9)
            {
                if (nguon[u+1][v+1] == -1)
                    {
                        nguon[u][v] += 1;
                    }
            };

        }

};


void ketthuc(int **nguon, int **trang_thai,int ketqua,SDL_Renderer *renderer,int Size,bool &thoat)
{
    if (ketqua == -1)
    {
        SDL_Texture *bom = NULL;
        SDL_Texture *co = NULL;
        for ( int i=0; i<20; i++)
            for ( int j=0; j<10; j++)
        {
            if ((i+j)%2 == 0)
                co = loadTexture("anh\\nen.bmp", renderer);
            else
                co = loadTexture("anh\\nen1.bmp", renderer);
            if ( nguon[i][j] == -1 && trang_thai[i][j] == 0)
            {
                bom = loadTexture("anh\\bom.bmp",renderer);
                renderTexture(co, renderer,j*Size +40 ,i*Size+100 ,30,30);
                renderTexture(bom, renderer, j * Size + 40, i * Size + 100 , 30, 30);
            }
            else if (nguon[i][j] != -1 && trang_thai[i][j] == -1)
            {
                bom = loadTexture("anh\\daux.bmp",renderer);
                renderTexture(bom, renderer, j * Size + 40, i * Size + 100 , 30, 30);
            }
        };
        SDL_RenderPresent(renderer);
        SDL_Delay(1500);
        bom = loadTexture("anh\\red.bmp",renderer);
        renderTexture(bom, renderer, 85, 250, 210, 240 );

        bom = loadTexture("anh\\lose.bmp",renderer);
        renderTexture(bom, renderer, 85, 250, 210, 90 );
    }
    else if (ketqua == 1)
    {
        SDL_Texture *bom = loadTexture("anh\\green.bmp",renderer);
        renderTexture(bom, renderer, 85, 250, 210, 240 );

        bom = loadTexture("anh\\win.bmp",renderer);
        renderTexture(bom, renderer, 85, 250, 210, 90 );
    };
    SDL_Texture *bom = loadTexture("anh\\replay.bmp",renderer);
    renderTexture(bom, renderer, 125, 360, 132, 50 );

    bom = loadTexture("anh\\exit.bmp",renderer);
    renderTexture(bom, renderer, 125, 430, 132, 50 );

    SDL_RenderPresent(renderer);
    SDL_Event a;
    while (true)
    {
        // Đợi 10 mili giây
        SDL_Delay(10);

        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&a) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (a.type == SDL_QUIT)
        {
            thoat=true;
            break;
        }

        // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
        if (a.type == SDL_KEYDOWN && a.key.keysym.sym == SDLK_ESCAPE)
        {
            thoat = true;
            break;
        }

      //   Nếu chuột (mouse) được nhấn (xuống)
        if (a.type == SDL_MOUSEBUTTONDOWN)
            if (a.button.button == SDL_BUTTON_LEFT && a.button.x>125 && a.button.x<257 && a.button.y>360 && a.button.y<410)
            {
                thoat = false;
                break;
            }
            else if (a.button.button == SDL_BUTTON_LEFT && a.button.x>125 && a.button.x<257 && a.button.y>430 && a.button.y<480)
            {
                menu(renderer,thoat);
                break;
            }

    };


    SDL_DestroyTexture(bom);
};

int kiemtra(int **nguon, int **trang_thai)
{
    bool x=true;
    for (int i = 0; i < 20; i++)
        for(int j = 0; j < 10; j++)
        {
            if (nguon[i][j] == -1 && trang_thai[i][j] != -1 )
            {
                x = false;
                break;
            }
        };
    if (x == false)
        return 0;
    else return 1;
    return 0;

}
void menu(SDL_Renderer* renderer, bool &thoat)
{
    SDL_Texture *background = loadTexture("anh\\bg1.bmp", renderer);
    renderTexture( background, renderer, 0, 0, 380, 730);

    SDL_Texture *button = loadTexture("anh\\play.bmp",renderer);
    renderTexture(button, renderer, 125, 290, 132, 50 );

    button = loadTexture("anh\\exit.bmp",renderer);
    renderTexture(button, renderer, 125, 350, 132, 50 );

    SDL_RenderPresent(renderer);
    SDL_Event a;
    while (true)
    {
        // Đợi 10 mili giây
        SDL_Delay(10);

        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if ( SDL_WaitEvent(&a) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (a.type == SDL_QUIT)
        {
            thoat=true;
            break;
        }

        // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
        if (a.type == SDL_KEYDOWN && a.key.keysym.sym == SDLK_ESCAPE)
        {
            thoat = true;
            break;
        }

      //   Nếu chuột (mouse) được nhấn (xuống)
        if (a.type == SDL_MOUSEBUTTONDOWN)
            if (a.button.button == SDL_BUTTON_LEFT && a.button.x>125 && a.button.x<257 && a.button.y>290 && a.button.y<340)
            {
                thoat = false;
                break;

            }
            else if (a.button.button == SDL_BUTTON_LEFT && a.button.x>125 && a.button.x<257 && a.button.y>350 && a.button.y<400)
            {
                thoat = true;
                break;
            }

    };
};
void drawtext (std ::string text, int x, int y, SDL_Renderer *renderer,int size)
{
    TTF_Font* font = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

    font = TTF_OpenFont("times.ttf", size);

    SDL_Color fg = { 51, 0, 0 };

    surface = TTF_RenderText_Solid(font, text.c_str(), fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;

    //Copy a portion of the texture to the current rendering target.
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
    //draw to screen
    SDL_RenderPresent(renderer);
};






