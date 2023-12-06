
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

class Number {
    int value;
    int beginIndex;
    int endIndex;
    bool usedOnce;

    public:
        Number(int value, int beginIndex, int endIndex) : value(value), beginIndex(beginIndex), endIndex(endIndex), usedOnce(false) {}
        int getValue() {
            return value;
        }
        int getBeginIndex(int i) {
            if (i >= beginIndex and i <= endIndex)
                return value;

            return 0;
        }
};

class SpecialChar {
    char value;
    int index;

     public:
        SpecialChar(int value, int index) : value(value), index(index) {}
        int getIndex() {
            return index;
        }
};

class Line {
    std::vector<Number> numbers;
    std::vector<SpecialChar> specialChars;

    int index;

    public:
        Line(int index) : index(index) {
            std::cout << "creating line with index " << index << std::endl;
        }
        void addNumber(int value, int beginIdex, int endIndex) 
        {
            Number number(value, beginIdex, endIndex);
            numbers.push_back(number);

        }
        void addSpecialChar(char value, int index)
        {
            SpecialChar specialChar(value, index);
            specialChars.push_back(specialChar);
        }
        int getIndex() {
            return index;
        }
        void printLine() {
            std::cout << index << ": ";
            for (Number n : numbers) {
                std::cout << n.getValue() << ", ";
            }
            std::cout << std::endl;
        }
        int getNumberOnIndex(int i) {
            for (Number n : numbers) {
                if (n.getBeginIndex(i))
            }
        }

        std::vector<Number> getNumbers() {
            return numbers;
        }
        void calcNumbers(Line neighbor)
        {
            int sum;
            for (SpecialChar c : neighbor.specialChars) {
                for (Number n : numbers) {
                    sum += n.getBeginIndex(c.getIndex());
                }
            }
            std::cout << sum;
        }
        
};

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    std::string prevLine;
    std::vector<int> numbers;
    std::vector<Line> lines;
    int sum;
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit with an error code
    }


    while (std::getline(inputFile, line)) {
        // Process the 'line' variable here
        std::string numberString;
        int i;
        bool isSpecialChar;
        Line _line(i);
        Line *prevLine = &_line;

        for (char c : line) {
            if (std::isdigit(c)) {
                numberString.push_back(c);
            } else if (c != '.') {
                _line.addSpecialChar(c, i);
                numberString.clear();

            } else {
                if (numberString.length() > 0) {
                    _line.addNumber(std::stoi(numberString), i - numberString.length(), i);
                    numberString.clear();

                }
            }
        }
        lines.push_back(_line);
        numberString.clear();
        i++;
    }
        

    for (Line l : lines) {
        l.calcNumbers();
    }

    for (int i = 0; i < lines.size(); i++) {
        lines.at(i).calcNumbers(lines.at(i + 1));
    }

    for (int i : numbers) {
       // std::cout << i << std::endl;
    }

    inputFile.close();

    return 0;
}