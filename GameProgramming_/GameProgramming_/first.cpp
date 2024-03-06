#include<iostream>
#include<SDL.h>
using namespace std;

int main(int argc, char *argv[]) 
{
	SDL_Init(SDL_INIT_EVERYTHING);

	const char *displayname=SDL_GetDisplayName(0);
	cout << displayname<<"\n";
	cout << "dd";
	return 0;

}