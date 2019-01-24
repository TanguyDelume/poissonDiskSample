#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>

PoissonDiskSample::PoissonDiskSample
(int startx,
 int starty,
 int windowWidth,
 int windowHeight,
 int minDistance,
 int sampleRejectLimit
 SDL_Renderer* renderer):
	_windowWidth(windowWidth),
	_windowHeight(windowHeight),
	_minDistance(minDistance),
	_sampleRejectLimit(sampleRejectLimit),
	_renderer(renderer)
{
	_origin(startx, starty);
	_cellSize = _minDistance / sqrt(2);
	_nbColumns = floor(_windowWidth / _cellSize);
	_nbRows = floor(_windowHeigth / _cellSize);
	for (int i = 0; i < nbColumns * nbRows; i++)
	{
		_samples.push_back(Vector2(-1,-1));
	}
	_samples[floor(_origin.x / _cellSize) * _nbColumns + floor(_origin.x / _cellSize) * _nbRows] = _origin;
	srand (time(NULL));
}


void PoissonDiskSample::computeNewSamples()
{
	_newSamples.push_back(origin);
	while(!_newSamples.empty())
	{
		int sampleIndex = random(0, _newSamples.size() - 1);
		Vector2 samplePos = _newSamples[newSampleIndex];
		bool sampleValidated = false;
		for (int i = 0; i < _sampleRejectLimit; i++)
		{
			double angle = rand() * M_PI * 2;
			Vector2 direction = Vector2(sin(angle), cose(angle));
			Vector2 newSamplePos = samplePos + direction * random(_minDistance, 2 * _minDistance) 
				if (isValidated(newSamplePos))
				{
					_samples[floor(newSamplePos.x / _cellSize), floor(newSamplePos.y / _cellSize)] = newSamplePos;
					_newSamples.push_back(newSamplePos);
					sampleValidated = true;
					break;
				}
		}
		if (!sampleValidated)
			_newSamples.erase(_newSamples.begin() + sampleIndex);
	}
}

bool PoissonDiskSample::isValidated(Vector2 sample)
{
	if (sample.x >= 0 && sample.x < _windowWidth && sample.y >= 0 && sample.y < windowHeight)
	{
		int cellX = floor(sample.x/_cellSize);
		int cellY = floor(candidate.y/_cellSize);
		int startX = std::max(0, cellX - 2);
		int startY = std::max(0, cellY - 2);	       	
		int endX = std::min(cellX + 2, _nbColumns - 1); 	
		int endY = std::min(cellY + 2, _nbRows - 1);

		for(int i = startX; i <= endX; i++)
		{
			for (int j = startY; j <= endY; j++)
			{
				Vector2 neighbor = _samples[i * _nbColumns + j * _nbrows];
				if (neighbor.x != -1)
				{
					Vector2 distance = sample - neighbor;
					i						double distanceLength = sqrt(distance.x * distance.x + distance.y * distance.y); 
					if (distanceLength < _minDistance)
						return false;
				}
			}
		}

		return true;
	}
	return false;
}

static int PoissonDiskSample::random (int min, int max) 
{ 
	if (max == 0) 
		return 0; 
	else 
		return rand() % max + min; 
}

static void drawSample(int posX, int posY, int radius, int r, int g, int b, int a)
{
   SDL_SetRenderDrawColor(_renderer, r, g, b, a); 
   int x = radius - 1; 
   int y = 0; 
   int tx = 1; 
   int ty = 1; 
   int err = tx - (radius << 1);  
   while (x >= y) 
   { 
      SDL_RenderDrawPoint(_renderer, posX + x, posY - y); 
      SDL_RenderDrawPoint(_renderer, posX + x, posY + y); 
      SDL_RenderDrawPoint(_renderer, posX - x, posY - y); 
      SDL_RenderDrawPoint(_renderer, posX - x, posY + y); 
      SDL_RenderDrawPoint(_renderer, posX + y, posY - x); 
      SDL_RenderDrawPoint(_renderer, posX + y, posY + x); 
      SDL_RenderDrawPoint(_renderer, posX - y, posY - x); 
      SDL_RenderDrawPoint(_renderer, posX - y, posY + x); 
 
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
         err += tx - (radius << 1); 
      } 
   } 
}
