// AircraftGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "Game.h"
#include "Application.h"

int main()
{
    try
    {
        /*AircraftGame::Game game;
        game.Run();*/

        AircraftGame::Application app;
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
