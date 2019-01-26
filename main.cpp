#include "window.hpp"

int main()
{
	Window window("Poisson Disk Sample", 800, 600);


	while (!window.isClosed())
	{
		window.pollEvents();
		if (window._poissonDisk != nullptr)
			window._poissonDisk->reDraw();
		else
			window.clear();
	}
	return 0;
}

