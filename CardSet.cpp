/* 
 * File:   CardSet.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 1:51 PM
 */

#include "CardSet.h"

CardSet::CardSet() {
}

CardSet::CardSet(const CardSet& orig) {
}

CardSet::~CardSet() {
}

std::ostream& operator<<(std::ostream& os, const CardSet& obj){
    os << "Game";
}
