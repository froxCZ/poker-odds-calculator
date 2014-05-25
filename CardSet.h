/* 
 * File:   CardSet.h
 * Author: frox
 *
 * Created on May 22, 2014, 1:51 PM
 */

#ifndef CARDSET_H
#define	CARDSET_H
#include "Constants.h"
#include <sstream>
#include <string>
#include <list>
using namespace std;
class CardSet {    
public:
    int ranks[CARDS_CNT];
    int suits[SUITS_CNT];    
    bool availableCards[CARDS_CNT][SUITS_CNT];
    int cardsCnt;   
    int id;
    CardSet();
    CardSet(int id);
    CardSet(const CardSet& orig);
    void Reset();
    void AddCard(string cardStr);
    void AddCard(int rank,int suit);
    int GetFigureScore();
    virtual ~CardSet();
    friend std::ostream& operator<<(std::ostream& os, const CardSet& obj);
    static bool StrToCard(string&str,int&rank,int&suit);
    static string CardToStr(int rank,int suit);    
private:
    int GotStraightFlush();
    int GotPoker();
    int GotFullHouse();
    int GotFlush();
    int GotStraight();
    int GotThree();
    int GotTwoPairs();
    int GotOnePair();
    int GotHighCard();
    int GotN(int n);
    int GetNonFigureHighestCard(int rank, int nToFind);
    inline void ModyfiScoreByCardSignificance(int& score,int rank, int significance);
   

};

#endif	/* CARDSET_H */

