#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

#include "poissonDisk.hpp"

class Window 
{
	public:
	Window(const std::string &title, int width, int height);
	~Window();
	void clear() const;
	void clearDots();
	inline bool isClosed() const {return _closed;}
	void pollEvents();
	PoissonDiskSample *_poissonDisk = nullptr;

	private:
	bool init();


	private:
	std::string _title;

	int _width = 800;
	int _height = 600;
	bool _closed = false;
	SDL_Window *_window = nullptr;
	SDL_Renderer *_renderer = nullptr;
};
