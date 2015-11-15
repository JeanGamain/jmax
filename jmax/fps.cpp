#include <cstdio>
#include <iostream>
#include "fps.h"

fps::fps(int avg) {
	lastFrame = NULL;
	averageOfFrames = avg;
	lastFrameTimes = new std::deque<float>(averageOfFrames);
	framesToUpdate = averageOfFrames;
	fpsString = new char[15];
}

void fps::timeFrame() {
	tempTime = clock();

	if (lastFrame != NULL) {
		if (lastFrameTimes->size() >= averageOfFrames) {
			lastFrameTimes->pop_back();
		}
		lastFrameTimes->push_front(tempTime - lastFrame);
	}
	lastFrame = tempTime;
}

char *fps::getFps() {
	framesToUpdate--;
	if (lastFrameTimes->size() < averageOfFrames) {
		return "Calculating";
	}

	if (framesToUpdate <= 0) {
		averageFps = 0;
		for (unsigned int i = 0; i < lastFrameTimes->size(); i++) {
			averageFps += lastFrameTimes->at(i);
		}
		averageFps /= lastFrameTimes->size();
		averageFps = CLOCKS_PER_SEC / averageFps;
		std::cout << averageFps << "FPS" << std::endl;
		sprintf_s(fpsString, 15, "%4.2f FPS", averageFps);
		framesToUpdate = averageOfFrames;
	}
	return fpsString;
}