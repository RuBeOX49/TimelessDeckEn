#include "core/SDLApplication.h"
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	#endif

	SDLApplication* game = nullptr;

	try {
		game = new SDLApplication();
		game->run();
	} catch (const std::string& e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char* e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception& e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}

	delete game;

	return 0;
}