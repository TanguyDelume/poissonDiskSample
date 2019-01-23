#include "dot.h"

Dot::Dot(SDL_Renderer *renderer, int x, int y, int rad, int r, int g, int b, int a)
	: _renderer(renderer), _x(x), _y(y), _rad(rad), _r(r), _g(g), _b(b), _a(a)
{
}

void Dot::draw() const 
{
   SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
   int x = _rad - 1;
   int y = 0;
   int tx = 1;
   int ty = 1;
   int err = tx - (_rad << 1); 
   while (x >= y)
   {
      SDL_RenderDrawPoint(_renderer, _x + x, _y - y);
      SDL_RenderDrawPoint(_renderer, _x + x, _y + y);
      SDL_RenderDrawPoint(_renderer, _x - x, _y - y);
      SDL_RenderDrawPoint(_renderer, _x - x, _y + y);
      SDL_RenderDrawPoint(_renderer, _x + y, _y - x);
      SDL_RenderDrawPoint(_renderer, _x + y, _y + x);
      SDL_RenderDrawPoint(_renderer, _x - y, _y - x);
      SDL_RenderDrawPoint(_renderer, _x - y, _y + x);

      if (err <= 0)
      {
         y++;
         err += ty;
         ty += 2;
      }
      if (err > 0)
      {
         x--;
         tx += 2;
         err += tx - (_rad << 1);
      }
   }
}

void Dot::pollEvents(SDL_Event &event)
{
	// for testing the framerate 
		if (event.type == SDL_KEYDOWN)
		{
			_y -= 1;
		}
}
