/* 
 * File:   CardSet.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 1:51 PM
 */

#include "CardSet.h"

CardSet::CardSet() {
    CardSet(-1);
}

CardSet::CardSet(int id) {
    this->id = id;
}

CardSet::CardSet(const CardSet& orig) {
}

CardSet::~CardSet() {
}

bool CardSet::StrToCard(string& str, int& card, int& suit) {
    if (str.length() != 2) {
        cout << "strToCard error" << endl;
        return false;
    }
    char cardChar = str[0];
    char suitChar = str[1];
    if (cardChar - '0' >= 1 && cardChar - '0' <= 9) {
        card = cardChar - '0';
    } else {
        switch (cardChar) {
            case '0':
                card = 10;
                break;
            case 'J':
                card = JACK;
                break;
            case 'Q':
                card = QUEEN;
                break;
            case 'K':
                card = KING;
                break;
            case 'A':
                card = ACE;
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

string CardSet::CardToStr(int card, int suit) {
    string cardStr;
    if (card >= 0 && card <= 9) {
        stringstream tmpSs;
        tmpSs << card;
        cardStr.append(tmpSs.str());
    } else {
        switch (card) {
            case 10:
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

std::ostream& operator<<(std::ostream& os, const CardSet& obj) {
    os << "CardSet";
}

