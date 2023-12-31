#include "UglyEngine.h"
#include "test_application.h"

int main()
{
	ugly::Engine *engine = ugly::Engine::getInstance();
	engine->run(new TestApplication());

	return 0;
}