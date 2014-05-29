/* 
 * File:   InterativeController.h
 * Author: frox
 *
 * Created on May 25, 2014, 2:54 PM
 */

#ifndef INTERATIVECONTROLLER_H
#define	INTERATIVECONTROLLER_H
#include "Game.h"
class InterativeController {
public:
    Game* game;
    string my1,my2;
    string f1,f2,f3,f4,f5;
    bool run;
    int players;
    int cardCounter;
    static bool bSimulate;
    InterativeController();
    InterativeController(const InterativeController& orig);
    virtual ~InterativeController();
    void Run();    
    void Finish();
    static void StopSimulation(int signal);
private:
    void Reset();
    void Simulate();
    void ExecuteCmd(string cmd);
    bool IsGameInitialized();    

};

#endif	/* INTERATIVECONTROLLER_H */

