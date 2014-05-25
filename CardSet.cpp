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

int CardSet::GetFigureScore() {
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
    int pokerRank = 0;
    for (; iRank >= CARD_2; iRank--) {
        if (ranks[iRank] == 4) {
            gotFigure = true;
            pokerRank = iRank;
            break;
        }
    }
    if (gotFigure) {
        int score = POKER;
        ModyfiScoreByCardSignificance(score,pokerRank,2);
        for (int iRank = ACE; iRank >= CARD_2; iRank--) {
            if (iRank != pokerRank && ranks[iRank] >= 1) {
                ModyfiScoreByCardSignificance(score,iRank,1);
                break;
            }
        }
        return score;
    }
    return 0;
}

int CardSet::GotFullHouse() {
    int twoRank = 0;
    int threeRank = 0;
    for (int iRank = ACE; iRank >= CARD_2; iRank--) {
        if (ranks[iRank] >= 3 && threeRank == 0) {
            threeRank = iRank;
        } else if (ranks[iRank] >= 2 && twoRank == 0) {
            twoRank = iRank;
        }
    }
    if (threeRank > 0 && twoRank > 0) {
        int score = FULL_HOUSE;
        ModyfiScoreByCardSignificance(score, threeRank, 2);
        ModyfiScoreByCardSignificance(score, twoRank, 1);
        return score;
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
    int seqCnt = 0;
    for (int iRank = ACE; iRank >= CARD_2; iRank--) {
        if (ranks[iRank]) {
            seqCnt++;
            if (seqCnt == 5) {
                return STRAIGHT + iRank;
            }
        } else {
            seqCnt = 0;
        }
    }

    return 0;
}

int CardSet::GotThree() {
    int rank;
    if (rank = GotN(3)) {
        int score = THREE;
        ModyfiScoreByCardSignificance(score, rank, 3);
        score += GetNonFigureHighestCard(rank, 2);
        return score;
    } else {
        return 0;
    }


}

int CardSet::GotTwoPairs() {
    int score = 0;
    int pairsToFind = 2;
    int otherToFind = 1;
    for (int iRank = ACE; iRank >= CARD_2; iRank--) {
        if (ranks[iRank] >= 2 && pairsToFind > 0) {
            ModyfiScoreByCardSignificance(score, iRank, pairsToFind + 1);
            pairsToFind--;
        } else if (ranks[iRank] == 1 && otherToFind > 0) {
            ModyfiScoreByCardSignificance(score, iRank, otherToFind--);
        }
    }
    if (pairsToFind == 0)return score;
    return 0;
}

int CardSet::GotOnePair() {
    int rank;
    if (rank = GotN(2)) {
        int score = ONE_PAIR;
        ModyfiScoreByCardSignificance(score, rank, 4);
        score += GetNonFigureHighestCard(rank, 3);
        return score;
    }
    return 0;
}

int CardSet::GotHighCard() {
    int score = 0;
    int toFind = 5;
    for (int iRank = ACE; iRank >= CARD_2 && toFind > 0; iRank--) {
        if (ranks[iRank] >= 1) {
            ModyfiScoreByCardSignificance(score, iRank, toFind--);
        }
    }
    return score;
}

int CardSet::GotN(int n) {
    for (int iRank = ACE; iRank >= CARD_2; iRank--) {
        if (ranks[iRank] >= n) {
            return iRank;
        }
    }
    return 0;
}

int CardSet::GetNonFigureHighestCard(int rank, int nToFind) {
    int score = 0;
    for (int iRank = ACE; iRank >= CARD_2 && nToFind > 0; iRank--) {
        if (iRank != rank && ranks[iRank] >= 1) {
            ModyfiScoreByCardSignificance(score, rank, nToFind--);
        }
    }
    return score;
}

bool CardSet::StrToCard(string& str, int& rank, int& suit) {
    if (str.length() != 2) {
        cout << "strToCard error" << endl;
        return false;
    }
    char cardChar = str[0];
    char suitChar = str[1];
    if (cardChar >= '2' && cardChar <= '9') {
        rank = cardChar - '0' - 1;
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
        default:
            cout << "strToCard error" << endl;
            return false;
    }
    return true;
}

string CardSet::CardToStr(int rank, int suit) {
    string cardStr;
    if (CARD_2 >= 0 && rank <= CARD_9) {
        stringstream tmpSs;
        tmpSs << rank + 1;
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

inline void CardSet::ModyfiScoreByCardSignificance(int& score, int rank, int significance) {
    score |= rank << ((significance - 1) * 4);
}

std::ostream& operator<<(std::ostream& os, const CardSet& cardSet) {
    for (int i = CARD_2; i < CARDS_CNT; i++) {
        for (int j = 0; j < SUITS_CNT; j++) {
            if (cardSet.availableCards[i][j] == true)
                os << cardSet.CardToStr(i, j) << " ";
        }
    }
    return os;
}

