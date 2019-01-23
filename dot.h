#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Dot {
	public:
		Dot(SDL_Renderer *renderer, int x, int y, int rad, int r, int g, int b, int a);
		void draw() const;
		void pollEvents(SDL_Event &event);
	private:
		SDL_Renderer *_renderer;
		int _x, _y;
		int _rad;
		int _r, _g, _b, _a;
};
