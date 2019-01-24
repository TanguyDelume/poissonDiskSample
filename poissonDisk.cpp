#include "poissonDisk.h"

PoissonDiskSample::PoissonDiskSample
(int startx,
 int starty,
 int windowWidth,
 int windowHeight,
 int minDistance,
 int sampleRejectLimit,
 SDL_Renderer* renderer):
	_origin(Vector2(startx,starty)),
	_windowWidth(windowWidth),
	_windowHeight(windowHeight),
	_minDistance(minDistance),
	_sampleRejectLimit(sampleRejectLimit),
	_renderer(renderer)
{
	_cellSize = _minDistance / sqrt(2);
	_nbColumns = floor(_windowWidth / _cellSize);
	_nbRows = floor(_windowHeight / _cellSize);
	_grid = new int *[_nbColumns + 1];
	for (int i = 0; i <= _nbColumns; i++)
	{
		_grid[i] = new int [_nbRows + 1];
		for (int j = 0; j <= _nbRows; j++)
			_grid[i][j] = -1;
	}
	_grid[(int)floor(_origin.x / _cellSize)][(int)floor(_origin.y / _cellSize)] = 0;
	_samples.push_back(_origin);
	srand (time(NULL));
	reDraw();
	computeNewSamples();
}


void PoissonDiskSample::computeNewSamples()
{
	_newSamples.push_back(_origin);
	while(!_newSamples.empty())
	{
		int sampleIndex = random(0, _newSamples.size() - 1);
		Vector2 samplePos = _newSamples[sampleIndex];
		bool sampleValidated = false;
		for (int i = 0; i < _sampleRejectLimit; i++)
		{
			double angle = (M_PI * 2) * (random (1, 360) / 360.0 );
			Vector2 direction = Vector2(sin(angle), cos(angle));
			Vector2 newSamplePos = samplePos + direction * random(_minDistance, 2 * _minDistance);
				if (isValidated(newSamplePos))
				{
					_grid[(int)floor(newSamplePos.x / _cellSize)][(int)floor(newSamplePos.y / _cellSize)] = _samples.size();
					_samples.push_back(newSamplePos);
					_newSamples.push_back(newSamplePos);
					sampleValidated = true;
					reDraw();
					break;
				}
		}
		if (!sampleValidated)
		{
			_newSamples.erase(_newSamples.begin() + sampleIndex);
			reDraw();
		}


	}
}

bool PoissonDiskSample::isValidated(Vector2 sample)
{
	if (sample.x >= 0 && sample.x < _windowWidth && sample.y >= 0 && sample.y < _windowHeight)
	{
		if (_grid[(int)floor(sample.x / _cellSize)][(int)floor(sample.y / _cellSize)] != -1)
			return false;
		int cellX = floor(sample.x/_cellSize);
		int cellY = floor(sample.y/_cellSize);
		int startX = std::max(0, cellX - 2);
		int startY = std::max(0, cellY - 2);	       	
		int endX = std::min(cellX + 2, _nbColumns); 	
		int endY = std::min(cellY + 2, _nbRows);
		for(int i = startX; i <= endX; i++)
		{
			for (int j = startY; j <= endY; j++)
			{
				int neighborIndex = _grid[i][j];
				Vector2 neighbor = _samples[neighborIndex];
				if (neighborIndex != -1)
				{
					Vector2 distance = sample - neighbor;
					double distanceLength = sqrt(distance.x * distance.x + distance.y * distance.y); 
					if (distanceLength < _minDistance)
						return false;
				}
			}
		}

		return true;
	}
	return false;
}

int PoissonDiskSample::random (int min, int max) 
{ 
	if (max == 0) 
		return 0; 
	else 
		return rand() % max + min; 
}

void PoissonDiskSample::drawSample(int posX, int posY, int radius, int r, int g, int b, int a)
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

void PoissonDiskSample::reDraw()
{
	SDL_RenderPresent(_renderer);
        SDL_SetRenderDrawColor(_renderer, 0, 0, 200, 255);
	SDL_RenderClear(_renderer);
	for (auto sample : _samples)
	{
		drawSample(sample.x, sample.y, 10, 255, 255, 255, 255);
	}
	for (auto newSample : _newSamples)
	{
		drawSample(newSample.x, newSample.y, 10, 255, 0, 0, 255);
	}
}
