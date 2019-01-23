#include "window.h"

Window::Window(const std::string &title, int width, int height) :
	_title(title), _width(width), _height(height)
{
	_closed = !init();
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Failed to start SDL. \n";
		return 0;
	}
	_window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
	
	if (_window == nullptr)
	{
		std::cerr << "Failed to create window \n";
		return 0;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == nullptr)
	{
		std::cerr << "failed to create renderer \n";
	}
	return true;
}

void Window::pollEvents()
{
	SDL_Event event;
	if (!SDL_PollEvent(&event))
		return;
	if (event.type == SDL_QUIT)
	{
		_closed = true;
		return;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		SDL_MouseButtonEvent mouseEvent = event.button;
		if (mouseEvent.button == SDL_BUTTON_LEFT )
		{
			clearDots();
			_dots.push_back(Dot(_renderer, mouseEvent.x, mouseEvent.y, 15, 200, 200, 200, 255));
		}
	}
	
	for (auto &dot : _dots)
		dot.pollEvents(event);
}

void Window::clearDots()
{
	_dots.clear();
}

void Window::clear() const 
{
	SDL_RenderPresent(_renderer);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
	SDL_RenderClear(_renderer);
}
