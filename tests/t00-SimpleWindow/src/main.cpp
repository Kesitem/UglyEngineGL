#include "UglyEngine.h"

int main()
{
	ugly::Engine::getInstance()->initialize();
	ugly::Engine::getInstance()->run(std::make_shared<ugly::Application>());

	return 0;
}