#include "TestApplication.h"

int main()
{
	ugly::Engine::getInstance()->initialize();
	ugly::Engine::getInstance()->run(std::make_shared<TestApplication>());

	return 0;
}