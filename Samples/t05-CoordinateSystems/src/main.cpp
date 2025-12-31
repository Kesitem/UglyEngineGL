#include "UglyEngine.h"
#include "test_application.h"

int main()
{
	ugly::Engine *engine = ugly::Engine::get_instance();
	engine->initialize();
	engine->run(new TestApplication());
	engine->shutdown();

	return 0;
}

