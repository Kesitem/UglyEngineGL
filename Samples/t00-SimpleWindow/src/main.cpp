#include "UglyEngine.h"

int main()
{
	ugly::Engine *engine = ugly::Engine::getInstance();
	engine->run(new ugly::Application());

	return 0;
}