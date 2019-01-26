#pragma once
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>
#include <SDL2/SDL.h>

class Vector2
{
	public:
		Vector2(double X, double Y) : x(X), y(Y) {}; 
		Vector2 operator+(Vector2 vector) 
		{ 
			return Vector2(this->x + vector.x, this->y + vector.y);
		}
		Vector2 operator-(Vector2 vector) 
		{ 
			return Vector2(this->x - vector.x, this->y - vector.y);
		}

		Vector2 operator*(double n) 
		{ 
			return Vector2(this->x * n, this->y * n);
		}

		double x;
		double y;
};

class PoissonDiskSample
{
	public:
	PoissonDiskSample
		(int startx,
		 int starty,
		 int windowWidth,
		 int windowHeight,
		 int minDistance,
		 int sampleRejectLimit,
		 SDL_Renderer* renderer,
		 SDL_Event* event);

	~PoissonDiskSample() 
	{
		if (_grid != nullptr)
		{
			for (int i = 0; i < _nbColumns; i++)
			{
				delete[] _grid[i];
			}
			delete[] _grid;
		}
	}
	void pollEvents();
	void reDraw();
	static int random (int min, int max);
	
	private:
	void drawSample(int posX, int posY, int radius, int r, int g, int b, int a);
	void computeNewSamples();
	bool isValidated(Vector2 sample);


	private:
	SDL_Renderer* _renderer;
	SDL_Event* _event;
	bool _stopped = false;
	double _cellSize;
	std::vector<Vector2> _newSamples;
	std::vector<Vector2> _samples;
	int** _grid = nullptr;
	int _nbColumns;
	int _nbRows;
	int _startIndex;
	Vector2 _origin;
	int _windowWidth; 
	int _windowHeight;
	int _minDistance;
	int _sampleRejectLimit;
};
