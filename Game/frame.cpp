#include "frame.h"

void FrameHandler::frameHandler()
{
	while (true)
	{
		if (clock() - frame_time >= static_cast<double>(1000 / fps))
		{
			for (int i = 0; i < functions_queue.size(); i++)
			{
				functions_queue.front()();
				functions_queue.pop();
			}
			frame_time = clock();
		}
	}
}

FrameHandler::FrameHandler(int fps)
{
	frame_time = clock();
	this->fps = fps;
}
