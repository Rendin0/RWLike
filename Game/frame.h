#pragma once
#include <queue>
#include <ctime>

class FrameHandler
{
	time_t frame_time;
	int fps;

	void frameHandler();
public:
	FrameHandler(int fps);
	static std::queue<void(*)()> functions_queue;

};