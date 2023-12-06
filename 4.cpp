
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

class Card {
    int id;
    std::vector<int> numbers;
    int wins;
    std::vector<Card*> wonCards;
    
public:
    Card() : id(-1) { }
    
    void setId(int id)
    {
        this->id = id;
    }
    
    void addNumber(int number)
    {
        numbers.push_back(number);
    }
    
    bool checkNumbers(int number)
    {
        for (int i : numbers) {
            if (i == number)
                return true;
        }
        
        return false;
    }
    void setWins(int wins)
    {
        this->wins = wins;
    }
    int getWins()
    {
        return wins;
    }
    void addCard(Card *c)
    {
        wonCards.push_back(c);
    }
    std::vector<Card*> getCards()
    {
        return wonCards;
    }
    int calcTotal()
    {
        if (wonCards.size() == 0) {
            return 0;
        } else {
            int total = (int) wonCards.size();
            for (Card *c : wonCards) {
                total += c->calcTotal();
            }
            return total;
        }
        
    }
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<Card> cards;
    int sum = 0;
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit with an error code
    }
    
    std::string tmp;
    int finalResult = 0;
    while (std::getline(inputFile, line)) {
        Card card;
        tmp.clear();
        bool winningNumbersReached = false;
        bool first = true;
        sum = 0;
        
        for (int i = 5; i < line.length(); i++) {
            if (std::isdigit(line[i])) {
                tmp.push_back(line[i]);
            } else if (line[i] == ' ') {
                if (tmp.size() == 0)
                    continue;
                
                int convertedNumber = std::stoi(tmp);
                if (!winningNumbersReached) {
                    if (first) {
                        card.setId(convertedNumber);
                        first = false;
                    } else {
                        card.addNumber(convertedNumber);
                    }
                    tmp.clear();
                } else {
                    if (card.checkNumbers(convertedNumber)) {
                        sum++;
                    }
                }
                tmp.clear();
            } else if (line[i] == '|') {
                winningNumbersReached = true;
                tmp.clear();
            }
            if (i == line.length() - 1) {
                int convertedNumber = std::stoi(tmp);
                if (card.checkNumbers(convertedNumber)) {
                    sum++;
                }
                
            }
        }
        card.setWins(sum);
        cards.push_back(card);
        finalResult += sum;
    }
    
    for (int i = 0; i < cards.size() - 1; i++){
        Card &main = cards.at(i);
        for (int j = i + 1; j <= i + cards[i].getWins(); j++) {
            Card &wonCard = cards.at(j);
            main.addCard(&wonCard);
        }
    }
    
    int total = cards.size();
    for (Card c : cards) {
        total += c.calcTotal();
    }

    inputFile.close();
    
    std::cout << total << std::endl;

    return 0;
}
