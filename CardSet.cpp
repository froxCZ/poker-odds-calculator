/* 
 * File:   CardSet.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 1:51 PM
 */

#include <string.h>

#include "CardSet.h"

CardSet::CardSet() {
    this->id = -1;
    Reset();
}

CardSet::CardSet(int id) {
    this->id = id;
    Reset();
}

CardSet::CardSet(const CardSet& orig) {
}

CardSet::~CardSet() {
}

void CardSet::Reset() {
    memset(ranks, 0, CARDS_CNT * sizeof (int));
    memset(suits, 0, SUITS_CNT * sizeof (int));
    for (int i = 0; i < CARDS_CNT; i++) {
        for (int j = 0; j < SUITS_CNT; j++) {
            availableCards[i][j] = false;
        }
    }

}

void CardSet::AddCard(string cardStr) {
    int card, suit;
    if (StrToCard(cardStr, card, suit) == false) return;
    ranks[card]++;
    suits[suit]++;
    availableCards[card][suit] = true;
    cardsCnt++;
}

int CardSet::GetFigureRank() {
    int score = 0;
    if (score = GotStraightFlush())return score;
    if (score = GotPoker())return score;
    if (score = GotFullHouse())return score;
    if (score = GotFlush())return score;
    if (score = GotStraight())return score;
    if (score = GotThree())return score;
    if (score = GotTwoPairs())return score;
    if (score = GotOnePair())return score;
    if (score = GotHighCard())return score;
    cout << "internal error: end of evaluate - should not happen!" << endl;
    return 0;
}

int CardSet::GotStraightFlush() {
    for (int iSuit = 0; iSuit < SUITS_CNT; iSuit++) {
        bool gotFigure = false;
        int seqCnt = 0;
        int iRank = ACE;
        for (; iRank >= CARD_2; iRank--) {
            if (availableCards[iRank][iSuit] == true) {
                seqCnt++;
                if (seqCnt == 5) {
                    gotFigure = true;
                    break;
                }
            } else {
                seqCnt = 0;
            }
        }
        if (gotFigure)return STRAIGHT_FLUSH + iRank;
    }
}

int CardSet::GotPoker() {
    int iRank = ACE;
    bool gotFigure = false;
    for (; iRank >= CARD_2; iRank--) {
        if (ranks[iRank] == 4) {
            gotFigure = true;
            break;
        }
    }
    if (gotFigure)return POKER + iRank;
    return 0;
}

int CardSet::GotFullHouse() {
    int twoRank = -1;
    int threeRank = -1;
    for (int iRank = ACE; iRank >= CARD_2; iRank--) {
        if (ranks[iRank] >= 3 && threeRank == -1) {
            threeRank = iRank;
        } else if (ranks[iRank] >= 2 && twoRank == -1) {
            twoRank = iRank;
        }
    }
    if (threeRank != -1 && twoRank != -1) {
        return FULL_HOUSE + threeRank * 100 + twoRank;
    }
    return 0;
}

int CardSet::GotFlush() {
    int bestFlushRank = 0;
    for (int iSuit = 0; iSuit < SUITS_CNT; iSuit++) {
        if (suits[iSuit] >= 5) {            
            int flushRank = FLUSH;
            int cardVal = 10000;
            for (int iRank = ACE; iRank >= CARD_2 && cardVal > 0; iRank--) {
                if (availableCards[iRank][iSuit] == true) {
                    flushRank += cardVal*iRank;
                    cardVal /= 10;
                }
            }            
            if (flushRank > bestFlushRank)bestFlushRank = flushRank;
        }
    }
    return bestFlushRank;
}

int CardSet::GotStraight() {
    return 0;
}

int CardSet::GotThree() {
    return 0;
}

int CardSet::GotTwoPairs() {
    return 0;
}

int CardSet::GotOnePair() {
    return 0;
}

int CardSet::GotHighCard() {
    return 0;
}

bool CardSet::StrToCard(string& str, int& rank, int& suit) {
    if (str.length() != 2) {
        cout << "strToCard error" << endl;
        return false;
    }
    char cardChar = str[0];
    char suitChar = str[1];
    if (cardChar >= '2' && cardChar <= '9') {
        rank = cardChar - '0' - 2;
    } else {
        switch (cardChar) {
            case '0':
                rank = CARD_10;
                break;
            case 'J':
                rank = JACK;
                break;
            case 'Q':
                rank = QUEEN;
                break;
            case 'K':
                rank = KING;
                break;
            case 'A':
                rank = ACE;
                break;
            default:
                cout << "strToCard error" << endl;
                return false;
        }
    }
    switch (suitChar) {
        case 'h':
            suit = HEARTS;
            break;
        case 'd':
            suit = DIAMONDS;
            break;
        case 'c':
            suit = CLUBS;
            break;
        case 's':
            suit = SPADES;
            break;
    }
    return true;
}

string CardSet::CardToStr(int rank, int suit) {
    string cardStr;
    if (rank >= 0 && rank <= 7) {
        stringstream tmpSs;
        tmpSs << rank + 2;
        cardStr.append(tmpSs.str());
    } else {
        switch (rank) {
            case CARD_10:
                cardStr.append("0");
                break;
            case JACK:
                cardStr.append("J");
                break;
            case QUEEN:
                cardStr.append("Q");
                break;
            case KING:
                cardStr.append("K");
                break;
            case ACE:
                cardStr.append("A");
                break;
        }
    }
    switch (suit) {
        case HEARTS:
            cardStr.append("h");
            break;
        case DIAMONDS:
            cardStr.append("d");
            break;
        case CLUBS:
            cardStr.append("c");
            break;
        case SPADES:
            cardStr.append("s");
            break;
    }
    return cardStr;
}

std::ostream& operator<<(std::ostream& os, const CardSet& cardSet) {
    for (int i = 0; i < CARDS_CNT; i++) {
        for (int j = 0; j < SUITS_CNT; j++) {
            if (cardSet.availableCards[i][j] == true)
                os << cardSet.CardToStr(i, j) << " ";
        }
    }
    return os;
}

