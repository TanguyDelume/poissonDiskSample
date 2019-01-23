#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "dot.h"

class Window 
{
	public:
	Window(const std::string &title, int width, int height);
	~Window();
	std::vector<Dot> getDots() {return _dots; }
	void clear() const;
	void clearDots();
	inline bool isClosed() const {return _closed; }
	void pollEvents();
	private:
	bool init();


	private:
	std::string _title;
	std::vector<Dot> _dots;
	int _width = 800;
	int _height = 600;
	bool _closed = false;
	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
};
