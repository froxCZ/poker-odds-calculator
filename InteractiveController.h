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
    int players;
    InterativeController();
    InterativeController(const InterativeController& orig);
    virtual ~InterativeController();
    void Run();    
private:
    void Reset();
    void Simulate();

};

#endif	/* INTERATIVECONTROLLER_H */

