#include "func_.h"
#include <windows.h>
#include<string>
#include<vector>

int g_input;
std::string g_output;

int g_X;
int g_Y;

int sizeH;
int sizeW;



// �귯�� �ð� ���
double g_elapsed_time_ms;

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
			COORD curB;
			curB.X = posX;
			curB.Y = posY;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curB);
			std::cout << "!\n";
			Flight();
		}
	}
	void Flight()
	{
		posY -= 1;
		if (posY == 0) { isFlying = false;  }
	}

	  int posX;
	  int posY;
	  bool isFlying;

};
//std::vector<Bullet> bullets;
Bullet oneBullet(0,0,false);

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


	// std::cout ��¿� ���۸� ����Ͽ�, ��� �ӵ��� �������� ������ ���Ѵ�.
	setvbuf(stdout, NULL, _IOLBF, 4096);

	// Clear the console screen.
	system("cls");
}






/////////////////////////////////////////////////////////////


void Update() 
{

	//left
	if (g_input == 1) {
		g_X--;
	}
	//right
	else if (g_input == 2) {
		g_X++;

	}
	//up
	else if (g_input == 3) {
		g_Y--;

	}
	//down
	else if(g_input==4){
		g_Y++;

	}
	//shot space
	else if (g_input == 5)
	{
		//bullets.push_back(Bullet(g_X, g_Y-1));
		oneBullet.posX = g_X;
		oneBullet.posY = g_Y - 1;
		oneBullet.isFlying = true;
	}

	if (g_X > sizeW-1) { g_X = 0; }
	if (g_X < 0) { g_X = sizeW-1; }
	if (g_Y < 1) { g_Y = sizeH - 1; }
	if (g_Y > sizeH-1) { g_Y = 0; }


	g_elapsed_time_ms += 33;

	

}





/////////////////////////////////////////////////////////////
// �׸��� �׸��� �Լ�.

void Render() {
	//// 1. ��� �׸���.
	// 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
	// <windows.h>���� �����ϴ� �Լ��� ����Ѵ�.
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	//// 1.2. ��� �κ�
	for (int i = 0; i < sizeH; i++) {
		for (int j = 0; j < sizeW; j++) {
			std::cout << "_";
		}
		std::cout << std::endl;
	}

	//// 1.3. ��� �Ʒ��� �ð��� ǥ���Ѵ�,
	std::cout << "Elapsed Time: " << g_elapsed_time_ms / 1000.0f << std::endl;

	/*
	for (Bullet& bullet : bullets)
	{
		bullet.DrawBullet();
	}
	*/

	oneBullet.DrawBullet();

	//// 2. ĳ���� �׸���.
	// 2.1. Ŀ���� ĳ���Ͱ� �׷��� ��ġ�� �ű��. 
	cur.X = g_X;
	cur.Y = g_Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	// 2.2. ĳ���� ǥ���� �׸���.
	std::cout << g_output;

	
	



	//// 3. ������ �ϼ�.
	// std::cout���� ����� ���� ��, ���� ȭ�鿡 ǥ�õ� �ʰ� ���ۿ� ���� �ִ� ���� �ִٸ�, ��� ȭ�鿡 ��µǵ��� �Ѵ�.
	std::cout.flush();


	
	

	//std::printf("x=%d y=%d\n",g_X,g_Y);
}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// �̺�Ʈ�� ó���ϴ� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
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
			// ���콺 ���� ��ư�� ���� ���� ��.
			break;

		default:
			break;
		}
	}
}




/////////////////////////////////////////////////////////////
// ClearGame() 
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame()
{
}