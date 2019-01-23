#include "window.h"

int main()
{
	Window window("Poisson Disk Sample", 800, 600);
	//Dot dot(window, 120, 120, 100, 100, 200, 0, 200, 255);

	while (!window.isClosed())
	{
		window.pollEvents();
		for (auto dot : window.getDots())
		{
//			dot.print();
			dot.draw();
		}
		window.clear();
	}
	return 0;
}

