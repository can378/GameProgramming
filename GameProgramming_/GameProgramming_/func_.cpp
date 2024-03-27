#include "func_.h"
#include <windows.h>
#include<string>
#include<vector>
#include "SDL_image.h"

int g_input;
double g_elapsed_time_ms;// 흘러간 시간 기록

std::string g_output;

int g_X;
int g_Y;

int sizeH;
int sizeW;

int bulletIndex;





SDL_Rect g_char_pos;
SDL_Texture* g_ryu_sheet_texture;
SDL_Rect g_source_rect[6];
SDL_Rect g_destination_rect;

int g_oryugen_sprite_num;
int g_current_oryugen_id;


class Bullet {

public:
	Bullet(int x, int y, bool isFly)
	{
		posX = x;
		posY = y;
		isFlying = isFly;
	};

	void DrawBullet()
	{
		if (isFlying)
		{
			curB.X = posX;
			curB.Y = posY;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curB);
			std::cout << "!"<<std::endl;
			Flight();
		}
	}
	void Flight()
	{
		posY -= 1;
		if (posY < 0) 
		{ 
			isFlying = false; 
		}
	}
	
	COORD curB;
    int posX;
	int posY;
	bool isFlying;

};


std::vector<Bullet> bullets(5, Bullet(0, 0, false));

/////////////////////////////////////////////////////////////
void InitGame() {
	g_input = 0;
	g_output = "*";
	g_flag_running = true;

	g_X = 0;
	g_Y = 10;

	sizeH = 20;
	sizeW = 30;

	g_elapsed_time_ms = 0;


	//drawing
	g_char_pos.x = 100;
	g_char_pos.y = 100;
	g_char_pos.w = 50;
	g_char_pos.h = 100;
	g_oryugen_sprite_num = 6;
	g_current_oryugen_id = 0;

	SDL_Surface* ryu_sheet_surface = IMG_Load("../Resources/60224.png");
	g_ryu_sheet_texture = SDL_CreateTextureFromSurface(g_renderer, ryu_sheet_surface);
	SDL_FreeSurface(ryu_sheet_surface);

	g_source_rect[0] = { 7  , 1647, 69, 140 };
	g_source_rect[1] = { 94 , 1647, 76, 140 };
	g_source_rect[2] = { 171, 1647, 68, 140 };
	g_source_rect[3] = { 240, 1647, 61, 140 };
	g_source_rect[4] = { 312, 1647, 54, 140 };
	g_source_rect[5] = { 390, 1647, 67, 140 };

	g_destination_rect.x = 300;
	g_destination_rect.y = 200;
	g_destination_rect.w = g_source_rect[0].w;
	g_destination_rect.h = g_source_rect[0].h;


	//bullet
	bulletIndex = 0;


	// std::cout 출력에 버퍼를 사용하여, 출력 속도가 느려지는 현상을 피한다.
	setvbuf(stdout, NULL, _IOLBF, 4096);

	// Clear the console screen.
	system("cls");
}



/////////////////////////////////////////////////////////////


void Update() 
{

	//left
	if (g_input == 1) { g_X--; }
	//right
	else if (g_input == 2) { g_X++;	}
	//up
	else if (g_input == 3) { g_Y--;		}
	//down
	else if(g_input==4){ g_Y++;		}


	//shot space
	if (g_input == 5)
	{
	
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isFlying != true)
			{
				bullets[i].posX = g_X;
				bullets[i].posY = g_Y - 1;
				bullets[i].isFlying = true;
				break;
			}
		}

		g_input = 0;
	}

	if (g_X > sizeW-1) { g_X = 0; }
	if (g_X < 0) { g_X = sizeW-1; }
	if (g_Y < 1) { g_Y = sizeH - 1; }
	if (g_Y > sizeH-1) { g_Y = 0; }


	g_elapsed_time_ms += 33;

	

}



/////////////////////////////////////////////////////////////
// 그림을 그리는 함수.

void Render() {
	//// 1. 배경 그리기.
	// 1.1. 커서를 콘솔 화면의 왼쪽 위 모서리 부분으로 옮긴다. 좌표(0, 0)
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	//// 1.2. 배경 부분
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			if (i == g_Y && j == g_X) { std::cout << "*"; }
			else { std::cout << "_"; }
		}
		std::cout << std::endl;
	}

	//// 1.3. 배경 아래에 시간
	std::cout << "Elapsed Time: " << g_elapsed_time_ms / 1000.0f << std::endl<<bulletIndex<<std::endl;


	//Draw Bullet
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isFlying == true) 
		{ bullets[i].DrawBullet(); }
		
	}


	//// 3. 프레임 완성.
	// std::cout으로 출력한 내용 중, 아직 화면에 표시되 않고 버퍼에 남아 있는 것이 있다면, 모두 화면에 출력되도록 한다.
	std::cout.flush();

}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				g_input = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				g_input = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				g_input = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				g_input = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE)
			{
				g_input = 5;
			}
			break;

		case SDL_KEYUP:
			g_input = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:
			// 마우스 왼쪽 버튼이 눌려 졌을 때.
			break;

		default:
			break;
		}
	}

}




/////////////////////////////////////////////////////////////
// ClearGame() 
// 프로그램이 끝날 때 한 번 호출되는 함수.
// 이 함수에서 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제해야한다.
void ClearGame()
{
}