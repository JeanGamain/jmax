#ifndef FPS_H_
# define FPS_H_

# include <ctime>
# include <deque>

class fps
{
public:
	fps(int averageOfFrames);

	void	timeFrame();
	char	*getFps();

private:
	std::deque<float> *lastFrameTimes;
	time_t	lastFrame;
	time_t	tempTime;
	char	*fpsString;
	unsigned int		averageOfFrames;
	unsigned int		framesToUpdate;
	float	averageFps;
};

#endif /* !FPS_H_ */