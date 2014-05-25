/* 
 * File:   CardSetTests.cpp
 * Author: frox
 *
 * Created on May 22, 2014, 5:16:39 PM
 */

#include <stdlib.h>
#include <iostream>
#include "CardSet.h"
#include "Constants.h"

int cards[] = {ACE, KING, CARD_8, CARD_10, JACK, CARD_2, CARD_9, CARD_5, QUEEN};
int suits[] = {CLUBS, DIAMONDS, SPADES, HEARTS, DIAMONDS, CLUBS, SPADES, CLUBS, HEARTS};
string cardStrings[] = {"Ac", "Kd", "8s", "0h", "Jd", "2c", "9s", "5c", "Qh"};
/*
 * Simple C++ Test Suite
 */
CardSet cardSet;

void cardToStrTest() {
    string result;
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        result = cardSet.CardToStr(cards[i], suits[i]);
        if (result != cardStrings[i]) {
            std::cout << "%TEST_FAILED% time=0 testname=cardToStrTest (CardSetTests) message=error message sample" << result << std::endl;
        }
    }
}

void strToCardTest() {
    int card, suit;
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        if (cardSet.StrToCard(cardStrings[i], card, suit) == false || card != cards[i] || suit != suits[i]) {
            std::cout << "%TEST_FAILED% time=0 testname=strToCardTest (CardSetTests) message=" << cardStrings[i] << " converted to " << card << suit << std::endl;
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
        std::cout << "%TEST_FAILED% time=0 testname=AddHandTest (CardSetTests) message=AddHand failed. Expected hand should be: " << expectedHand << " but was: " << ss.str() << std::endl;
    }
}

void SimpleAddHandTest() {
    for (int i = 0; i<sizeof (cards) / sizeof (int); i++) {
        AddHandTestExecuter(&cardStrings[i], 1, cardStrings[i] + " ");
    }
}

void ComplexAddHandTest() {
    string addArr[][3] = {
        {"8c", "4d"},
        {"8c", "4d", "2c"},
        {"Ad", "0h", "Qs"}
    };
    AddHandTestExecuter(addArr[0], 2, "4d 8c ");
    AddHandTestExecuter(addArr[1], 3, "2c 4d 8c ");
    AddHandTestExecuter(addArr[2], 3, "0h Qs Ad ");

}
void FigureRankStraightFlushTest();
void FigureRankPokerTest();
void FigureRankFullHouse();
void FigureRankFlush();
void FigureRankStraight();
void FigureRankPairs();

void FigureRankTest() {
    FigureRankStraightFlushTest();
    FigureRankPokerTest();
    FigureRankFullHouse();
    FigureRankFlush();
    FigureRankStraight();
    FigureRankPairs();
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% CardSetTests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% cardToStrTest (CardSetTests)" << std::endl;
    cardToStrTest();
    std::cout << "%TEST_FINISHED% time=0 cardToStrTest (CardSetTests)" << std::endl;

    std::cout << "%TEST_STARTED% strToCardTest (CardSetTests)\n" << std::endl;
    strToCardTest();
    std::cout << "%TEST_FINISHED% time=0 strToCardTest (CardSetTests)" << std::endl;

    std::cout << "%TEST_STARTED% SimpleAddHandTest (CardSetTests)\n" << std::endl;
    SimpleAddHandTest();
    std::cout << "%TEST_FINISHED% time=0 SimpleAddHandTest (CardSetTests)" << std::endl;

    std::cout << "%TEST_STARTED% ComplexAddHandTest (CardSetTests)\n" << std::endl;
    ComplexAddHandTest();
    std::cout << "%TEST_FINISHED% time=0 ComplexAddHandTest (CardSetTests)" << std::endl;

    std::cout << "%TEST_STARTED% FigureRankTest (CardSetTests)\n" << std::endl;
    FigureRankTest();
    std::cout << "%TEST_FINISHED% time=0 FigureRankTest (CardSetTests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

void FigureRankStraightFlushTest() {
    CardSet set1;
    set1.AddCard("Ac");
    set1.AddCard("Jc");
    set1.AddCard("Qc");
    set1.AddCard("Kc");
    set1.AddCard("0c");
    set1.AddCard("8d");
    set1.AddCard("2s");
    if (set1.GetFigureRank() != STRAIGHT_FLUSH + CARD_10) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    set1.Reset();
    set1.AddCard("3s");
    set1.AddCard("6s");
    set1.AddCard("4s");
    set1.AddCard("Kc");
    set1.AddCard("0c");
    set1.AddCard("5s");
    set1.AddCard("2s");
    if (set1.GetFigureRank() != STRAIGHT_FLUSH + CARD_2) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    set1.Reset();
    set1.AddCard("8s");
    set1.AddCard("6s");
    set1.AddCard("4s");
    set1.AddCard("Kc");
    set1.AddCard("0c");
    set1.AddCard("5s");
    set1.AddCard("2s");
    if (set1.GetFigureRank() >= STRAIGHT_FLUSH) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
}

void FigureRankPokerTest() {
    CardSet set1;
    set1.AddCard("8d");
    set1.AddCard("8h");
    set1.AddCard("Ac");
    set1.AddCard("Kc");
    set1.AddCard("8s");
    set1.AddCard("8c");
    if (set1.GetFigureRank() != POKER + (CARD_8<<4) + ACE) {
        std::cout << "%TEST_FAILED% time=0 testname=PokerTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    CardSet set2;
    set2.AddCard("8c");
    set2.AddCard("8s");
    set2.AddCard("8h");
    set2.AddCard("8d");
    set2.AddCard("Qc");
    if (set1.GetFigureRank() <= set2.GetFigureRank()) {
        std::cout << "%TEST_FAILED% time=0 testname=PokerTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }

}

void FigureRankFullHouse() {
    cardSet.Reset();
    cardSet.AddCard("8c");
    cardSet.AddCard("8h");
    cardSet.AddCard("8d");
    cardSet.AddCard("2c");
    cardSet.AddCard("2d");
    cardSet.AddCard("9c");
    if (cardSet.GetFigureRank() != FULL_HOUSE + (CARD_8 << 4) + CARD_2) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << cardSet << endl;
    }
    cardSet.AddCard("9d");
    if (cardSet.GetFigureRank() != FULL_HOUSE + (CARD_8 << 4) + CARD_9) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << cardSet << endl;
    }
    CardSet set1;
    set1.AddCard("8c");
    set1.AddCard("8h");
    set1.AddCard("8d");
    set1.AddCard("2c");
    set1.AddCard("2d");
    set1.AddCard("9c");
    if (cardSet.GetFigureRank() <= set1.GetFigureRank()) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << cardSet << endl;
    }
    set1.AddCard("Ad");
    set1.AddCard("Ac");
    set1.AddCard("As");
    if (set1.GetFigureRank() != FULL_HOUSE + (ACE << 4) + CARD_8) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
}

void FigureRankFlush() {
    CardSet set1;
    CardSet set2;
    set1.AddCard("Ac");
    set1.AddCard("Jc");
    set1.AddCard("8c");
    set1.AddCard("9c");
    set1.AddCard("0c");
    if (set1.GetFigureRank() <= FLUSH || set1.GetFigureRank() >= FULL_HOUSE) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    set2.AddCard("Ac");
    set2.AddCard("Jc");
    set2.AddCard("7c");
    set2.AddCard("9c");
    set2.AddCard("0c");
    if (set1.GetFigureRank() <= set2.GetFigureRank()) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
}

void FigureRankStraight() {
    CardSet set1;
    set1.AddCard("7c");
    set1.AddCard("3h");
    set1.AddCard("4h");
    set1.AddCard("5s");
    set1.AddCard("6d");
    set1.AddCard("6h");
    if (set1.GetFigureRank() >= FLUSH || set1.GetFigureRank() <= STRAIGHT) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
}

void FigureRankPairs() {
    CardSet set1;
    CardSet set2;
    set1.AddCard("5c");
    if (set1.GetFigureRank() <= HIGH_CARD || set1.GetFigureRank() >= ONE_PAIR) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    set2.AddCard("6c");
    if (set1.GetFigureRank() >= set2.GetFigureRank()) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    set1.AddCard("5h");
    cout << set1.GetFigureRank() << endl;
    if (set1.GetFigureRank() >= TWO_PAIRS || set1.GetFigureRank() <= ONE_PAIR) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    if (set1.GetFigureRank() <= set2.GetFigureRank()) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }
    set2.AddCard("5s");
    set2.AddCard("5h");
    set1.AddCard("6h");
    set1.AddCard("Ad");
    if (set1.GetFigureRank() <= set2.GetFigureRank()) {
        std::cout << "%TEST_FAILED% time=0 testname=FigureRankTest (CardSetTests) message=Evaluating figure rank failed" << set1 << endl;
    }

}