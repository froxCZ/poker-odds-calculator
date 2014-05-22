/* 
 * File:   Player.h
 * Author: frox
 *
 * Created on May 22, 2014, 12:40 PM
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "CardSet.h"

class Player {
public:
    CardSet hand;
    int id;
    Player(int id);
    Player(const Player& orig);
    virtual ~Player();
    friend std::ostream& operator<<(std::ostream& os, const Player& obj);
private:

};

#endif	/* PLAYER_H */

