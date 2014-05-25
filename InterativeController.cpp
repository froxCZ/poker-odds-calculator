/* 
 * File:   InterativeController.cpp
 * Author: frox
 * 
 * Created on May 25, 2014, 2:54 PM
 */

#include "InterativeController.h"
#include <sstream>
#include <iostream>
using namespace std;

InterativeController::InterativeController() {
    game = NULL;
}

InterativeController::InterativeController(const InterativeController& orig) {
}

InterativeController::~InterativeController() {
}

void InterativeController::Run() {
    stringstream ss;
    string cmd;
    int n;
    while (true) {
        cin >> cmd;
        if (cmd == "new") {
            Reset();
            cout << "players: ";
            cin >> players;
            game = new Game(players);
            cout << "card1 and 2: ";
            cin >> my1;
            cin >> my2;
            Simulate();
        } else if (cmd == "flop") {
            cout << "flop card1,2,3: ";
            cin >> f1;
            cin >> f2;
            cin >> f3;
            Simulate();
        } else if (cmd == "turn") {
            cout << "turn card4: ";
            cin >> f4;
            Simulate();
        } else if (cmd == "river") {
            cout << "river card5: ";
            cin >> f5;
            Simulate();
        } else if (cmd == "p") {
            cout << "enter players number: ";
            cin >> players;
            delete game;
            game = new Game(players);
        }else if(cmd == "simulate"){
            Simulate();
        }
    }
}

void InterativeController::Reset() {
    my1 = "";
    my2 = "";
    f1 = "";
    f2 = "";
    f3 = "";
    f4 = "";
    f5 = "";
    delete game;
}

void InterativeController::Simulate() {
    int gamesToPlay = 100000;
    int iWon = 0;
    for (int i = 0; i < gamesToPlay; i++) {
        game->Reset();
        if (my1.length() > 0)game->SetHand(my1, my2);
        if (f1.length() > 0)game->SetFlop(f1, f2, f3);
        if (f4.length() > 0)game->AddSharedCard(f4);
        if (f5.length() > 0)game->AddSharedCard(f5);
        if (game->FinishGame(false) == 0) {
            iWon++;
        }
    }
    double chanceToWin = (iWon * 1.0) / gamesToPlay;
    cout << "chance to win: " << chanceToWin << " avg chance: " << 1.0 / players << endl;
}

