/* 
 * File:   Player.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 12:40 PM
 */

#include "Player.h"
Player::Player(int id) {
    this->id = id;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}
std::ostream& operator<<(std::ostream& os, const Player& obj){
    os << "Game";
}