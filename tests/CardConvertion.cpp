/* 
 * File:   CardConvertion.cpp
 * Author: frox
 *
 * Created on May 22, 2014, 5:16:39 PM
 */

#include <stdlib.h>
#include <iostream>
#include "CardSet.h"
#include "Constants.h"

/*
 * Simple C++ Test Suite
 */
CardSet cardSet;
int cards[] = {ACE, KING, 8, 10, JACK, 2, 9,5,QUEEN};
int suits[] = {CLUBS, DIAMONDS, SPADES, HEARTS, DIAMONDS, CLUBS, SPADES,CLUBS,HEARTS};
string results[] = {"Ac", "Kd", "8s", "0h", "Jd", "2c", "9s","5c","Qh"};

void cardToStrTest() {
    string result;
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        result = cardSet.CardToStr(cards[i], suits[i]);
        if (result != results[i]) {
            std::cout << "%TEST_FAILED% time=0 testname=cardToStrTest (CardConvertion) message=error message sample" << result << std::endl;
        }
    }
}

void strToCardTest() {
    int card, suit;
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        if (cardSet.StrToCard(results[i], card, suit) == false || card != cards[i] || suit != suits[i]) {
            std::cout << "%TEST_FAILED% time=0 testname=strToCardTest (CardConvertion) message=" << results[i] << " converted to " << card << suit << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CardConvertion" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% cardToStrTest (CardConvertion)" << std::endl;
    cardToStrTest();
    std::cout << "%TEST_FINISHED% time=0 cardToStrTest (CardConvertion)" << std::endl;

    std::cout << "%TEST_STARTED% strToCardTest (CardConvertion)\n" << std::endl;
    strToCardTest();
    std::cout << "%TEST_FINISHED% time=0 strToCardTest (CardConvertion)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

