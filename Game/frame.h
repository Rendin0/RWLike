#pragma once
#include <queue>
#include <ctime>
#include <functional>

class FrameHandler
{
public:
	static std::queue<std::function<void()>> functions_queue;

};
void frameHandler(int fps);
