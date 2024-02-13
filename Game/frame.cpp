#include "frame.h"

void frameHandler(int fps)
{
	time_t frame_time = clock();
	while (true)
	{
		if (clock() - frame_time >= static_cast<double>(1000 / fps))
		{
			for (int i = 0; i < FrameHandler::functions_queue.size(); i++)
			{
				FrameHandler::functions_queue.front()();
				FrameHandler::functions_queue.pop();
			}
			frame_time = clock();
		}
	}
}
