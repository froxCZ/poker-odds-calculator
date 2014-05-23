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
int cards[] = {ACE, KING, CARD_8, CARD_10, JACK, CARD_2, CARD_9, CARD_5, QUEEN};
int suits[] = {CLUBS, DIAMONDS, SPADES, HEARTS, DIAMONDS, CLUBS, SPADES, CLUBS, HEARTS};
string cardStrings[] = {"Ac", "Kd", "8s", "0h", "Jd", "2c", "9s", "5c", "Qh"};

void cardToStrTest() {
    string result;
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        result = cardSet.CardToStr(cards[i], suits[i]);
        if (result != cardStrings[i]) {
            std::cout << "%TEST_FAILED% time=0 testname=cardToStrTest (CardConvertion) message=error message sample" << result << std::endl;
        }
    }
}

void strToCardTest() {
    int card, suit;
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        if (cardSet.StrToCard(cardStrings[i], card, suit) == false || card != cards[i] || suit != suits[i]) {
            std::cout << "%TEST_FAILED% time=0 testname=strToCardTest (CardConvertion) message=" << cardStrings[i] << " converted to " << card << suit << std::endl;
        }
    }
}

void AddHandTestExecuter(string* cardsToAdd, int addCnt, string expectedHand) {
    CardSet localSet;
    for (int i = 0; i < addCnt; i++) {
        localSet.AddCard(cardsToAdd[i]);
    }
    stringstream ss;
    ss << localSet;
    if (expectedHand != ss.str()) {
        std::cout << "%TEST_FAILED% time=0 testname=AddHandTest (CardConvertion) message=AddHand failed. Expected hand should be: " << expectedHand << " but was: " << ss.str() << std::endl;
    }
}

void SimpleAddHandTest() {
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        AddHandTestExecuter(&cardStrings[i], 1, cardStrings[i] + " ");
    }
}

void ComplexAddHandTest() {
    string addArr[][3] = {
        {"8c", "4d"},{"8c", "4d","2c"},{"Ad","0h","Qs"}};
    AddHandTestExecuter(addArr[0], 2, "4d 8c ");
    AddHandTestExecuter(addArr[1], 3, "2c 4d 8c ");    
    AddHandTestExecuter(addArr[2], 3, "0h Qs Ad ");
    
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

    std::cout << "%TEST_STARTED% SimpleAddHandTest (CardConvertion)\n" << std::endl;
    SimpleAddHandTest();
    std::cout << "%TEST_FINISHED% time=0 SimpleAddHandTest (CardConvertion)" << std::endl;

    std::cout << "%TEST_STARTED% ComplexAddHandTest (CardConvertion)\n" << std::endl;
    ComplexAddHandTest();
    std::cout << "%TEST_FINISHED% time=0 ComplexAddHandTest (CardConvertion)" << std::endl;
    
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

