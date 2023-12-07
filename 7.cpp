
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

enum HandTypes {
    high_card,
    one_pair,
    two_pairs,
    three_of_a_kind,
    full_house,
    four_of_a_kind,
    five_of_a_kind,
    not_defined
};


class Hand {
    std::string cards;
    int bid;
    
    HandTypes getHandType(const std::map<char, int> &map)
    {
        switch (map.size()) {
            case 5:
                return high_card;
            case 4:
                return one_pair;
            case 3:
                for (const auto& pair : map) {
                    if (pair.second == 3)
                        return three_of_a_kind;
                }
                return two_pairs;
            case 2:
                for (const auto& pair : map) {
                    if (pair.second == 4)
                        return four_of_a_kind;
                }
                return full_house;
            case 1:
                return five_of_a_kind;
            default:
                return not_defined;
                
        }
    }
    
public:
    Hand(std::string cards, int bid) : cards(cards), bid(bid) {}
    
    std::string getCards()
    {
        return cards;
    }
    
    int getBid()
    {
        return bid;
    }
    
    HandTypes checkHandType()
    {
        std::map<char, int> map;
        for (char c : cards) {
            map[c]++;
        }
        
        auto tmp = map['J'];
        if (tmp == 5)
            return five_of_a_kind;
        
        auto it = map.find('J');
        if (it != map.end()) {
            map.erase(it);
        }
        
        HandTypes highest = high_card;
        
        for (auto &pair : map) {
            pair.second += tmp;
            if (highest < getHandType(map))
                highest = getHandType(map);
            
            pair.second -= tmp;
        }
    
        
        return highest;
    }
    
};

void addHand(Hand hand, std::vector<Hand> &hands) {
    for (Hand h : hands) {
        
    }
}

int getValueOfCard(char c)
{
    switch (c) {
        case 'T':
            return 10;
        case 'J':
            return 1;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
            
        default:
            return -1;
    }
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<Hand> hands;
    std::vector<long> records;
    
    
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit with an error code
    }
    
    while (std::getline(inputFile, line)) {
        std::string numberString;
        std::string cards;
        int bid;
        for (char c : line) {
            if (c != ' ') {
                numberString.push_back(c);
            } else {
                cards = numberString;
                numberString.clear();
            }
        }
        bid = std::stoi(numberString);
        numberString.clear();
        hands.push_back(Hand(cards, bid));
        
    }
    
    sort(hands.begin(), hands.end(), []( Hand& lhs,  Hand& rhs) {
        if (lhs.checkHandType() == rhs.checkHandType()) {
            for (int i = 0; i < lhs.getCards().length(); i++) {
                int lhsCardValue = std::isdigit(lhs.getCards().at(i)) ? lhs.getCards().at(i) - '0' : getValueOfCard(lhs.getCards().at(i));
                int rhsCardValue = std::isdigit(rhs.getCards().at(i)) ? rhs.getCards().at(i) - '0' : getValueOfCard(rhs.getCards().at(i));
                if (lhsCardValue == rhsCardValue)
                    continue;
                
                return lhsCardValue < rhsCardValue;
            }
            return false;
        } else {
            return lhs.checkHandType() < rhs.checkHandType();
        }
       });

    long result = 0;
    int i = 1;
    for (auto &pair : hands) {
        result += pair.getBid() == 0 ? 0 : pair.getBid() * i++;
        std::cout << pair.getCards() << " " << pair.getBid() << std::endl;
    }
    
    std::cout << result << std::endl;
    inputFile.close();
    

    return 0;
}




