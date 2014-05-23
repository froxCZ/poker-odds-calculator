/* 
 * File:   GameTests.cpp
 * Author: frox
 *
 * Created on May 23, 2014, 3:04:05 PM
 */

#include <stdlib.h>
#include <iostream>

#include "Game.h"

/*
 * Simple C++ Test Suite
 */
void SetHandAndRiverTest() {
    Game game(1);
    game.SetHand("Ac","2d");
    string expected = "Table:\t\t\nplayer0:\t2d Ac \n";
    stringstream ss;
    ss<<game;
    if(expected!=ss.str()){
        std::cout << "%TEST_FAILED% time=0 testname=SetHandAndRiverTest (GameTests) message=SetHand failed. Expected out: \n" << expected << "but was: \n" << ss.str() << std::endl;        
    }    
    ss.str("");
    ss.clear();
    game.SetRiver("9c");
    game.SetRiver("Ks");
    game.SetRiver("8d");
    expected = "Table:\t\t8d 9c Ks \nplayer0:\t2d Ac \n";
    ss<<game;
    if(expected!=ss.str()){
        std::cout << "%TEST_FAILED% time=0 testname=SetHandAndRiverTest (GameTests) message=SetHand failed. Expected out: \n" << expected << "but was: \n" << ss.str() << std::endl;        
    }        
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% GameTests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% SetHandTest (GameTests)" << std::endl;
    SetHandAndRiverTest();
    std::cout << "%TEST_FINISHED% time=0 SetHandTest (GameTests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

