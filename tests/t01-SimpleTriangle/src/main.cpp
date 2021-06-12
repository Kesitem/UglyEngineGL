#include "TestApplication.h"

int main()
{
	return ugly::Engine::getInstance()->run(new TestApplication());
}