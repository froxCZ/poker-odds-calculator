/* 
 * File:   InterativeController.cpp
 * Author: frox
 * 
 * Created on May 25, 2014, 2:54 PM
 */

#include "InteractiveController.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <climits>
#include <signal.h>

using namespace std;
bool InterativeController::bSimulate = false;
InterativeController::InterativeController() {
    game = NULL;    
    signal(SIGINT, InterativeController::StopSimulation);
    
}

InterativeController::InterativeController(const InterativeController& orig) {
}

InterativeController::~InterativeController() {
}

void InterativeController::Run() {
    stringstream ss;
    string cmd;
    run = true;
    cardCounter = 0;
    while (run) {
        cin >> cmd;
        ExecuteCmd(cmd);
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
    if (IsGameInitialized() == false)return;
    cout << "== Simulating game == " << endl;
    cout << "players:" << setw(10) << players << endl;
    cout << "my cards:" << setw(10) << my1 << " " << my2 << endl;
    cout << "table cards:" << setw(10) << f1 << " " << f2 << " " << f3 << " " << f4 << " " << f5 << endl;
    cout << "avg chance per player:"<<setw(10)<<1.0/players;
    int i = 0;
    unsigned long long int gamesPlayed = 0;
    unsigned long long int wins = 0;
    cout.precision(4);    
    InterativeController::bSimulate = true;
    while (true) {
        if (i == 10000) {
            i = 0;
            double chanceToWin = (wins * 1.0) / gamesPlayed;
            cout << "\rchance to win: " << chanceToWin <<  " games played: " << gamesPlayed;
        }
        if (gamesPlayed == ULLONG_MAX || InterativeController::bSimulate == false) {
            cout << "\nsimulation finished" << endl;
            break;
        }
        game->Reset();
        if (my1.length() > 0)game->SetHand(my1, my2);
        if (f1.length() > 0)game->SetFlop(f1, f2, f3);
        if (f4.length() > 0)game->AddSharedCard(f4);
        if (f5.length() > 0)game->AddSharedCard(f5);
        if (game->FinishGame(false) == 0) {
            wins++;
        }
        gamesPlayed++;
        i++;
    }
}

void InterativeController::ExecuteCmd(string cmd) {
    if (cmd == "new") {
        Reset();
        cardCounter = 0;
        cout << "players: ";
        cin >> players;
        game = new Game(players);
        cout << "card1 and 2: ";
        cin >> my1;
        cin >> my2;
        int tmp;
        if (CardSet::StrToCard(my1, tmp, tmp) == false) {
            cout << "incorrect card " << my1 << endl;
            return;
        }
        if (CardSet::StrToCard(my2, tmp, tmp) == false) {
            cout << "incorrect card " << my2 << endl;
            return;
        }
        Simulate();
        return;
    }
    if (cmd == "add") {
        if (IsGameInitialized() == false)return;
        if (cardCounter == 0)cmd = "flop";
        if (cardCounter == 3)cmd = "turn";
        if (cardCounter == 4)cmd = "river";
    }
    int tmp;
    if (cmd == "flop") {
        cout << "flop card1,2,3: ";
        cin >> f1;
        cin >> f2;
        cin >> f3;
        if (CardSet::StrToCard(f1, tmp, tmp) == false) {
            cout << "incorrect card " << f1 << endl;
            return;
        }
        if (CardSet::StrToCard(f2, tmp, tmp) == false) {
            cout << "incorrect card " << f2 << endl;
            return;
        }
        if (CardSet::StrToCard(f3, tmp, tmp) == false) {
            cout << "incorrect card " << f3 << endl;
            return;
        }
        cardCounter += 3;
        Simulate();
    } else if (cmd == "turn") {
        cout << "turn card4: ";
        cin >> f4;
        if (CardSet::StrToCard(f4, tmp, tmp) == false) {
            cout << "incorrect card " << f4 << endl;
            return;
        }
        cardCounter++;
        Simulate();
    } else if (cmd == "river") {
        cout << "river card5: ";
        cin >> f5;
        if (CardSet::StrToCard(f4, tmp, tmp) == false) {
            cout << "incorrect card " << f4 << endl;
            return;
        }
        cardCounter++;
        Simulate();
    } else if (cmd == "p") {
        cout << "enter players number: ";
        cin >> players;
        delete game;
        game = new Game(players);
    } else if (cmd == "smlt") {
        Simulate();
    } else if (cmd == "exit") {
        Finish();
    } else if (cmd == "help") {
        cout << "print help" << endl;
    } else {
        cout << "unknown command: " << cmd << endl;
    }
}

void InterativeController::Finish() {
    run = false;
}
void InterativeController::StopSimulation(int signal){
    if(signal == SIGINT)InterativeController::bSimulate = false;
}

bool InterativeController::IsGameInitialized() {
    if (game == NULL) {
        cout << "game was not started. Type 'new' to initialize game or 'help' for more instructions";
        return false;
    }
    return true;
}

