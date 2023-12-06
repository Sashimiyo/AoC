#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

std::vector<std::string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};



int extract_digits(const std::string& line)
{
    char first, last;
    std::string digitWord;
    bool isFirst = true;

    for (char c : line) {
        digitWord.push_back(c);

        for (std::string s : nums) {
            
        }

        if (std::isdigit(c)) {
            if (isFirst) {
                first = c;
                isFirst = false;
            }
            last = c;
        }
    }
   // std::cout << line << " " << std::string(1, first) + last << std::endl;
    return std::stoi(std::string(1, first) + last); 
}

char get_digit_from_word(std::string word)
{
    if (word == "one") {
        return '1';
    } else if (word == "two") {
        return '2';
    } else if (word == "three") {
        return '3';
    } else if (word == "four") {
        return '4';
    } else if (word == "five") {
        return '5';
    } else if (word == "six") {
        return '6';
    } else if (word == "seven") {
        return '7';
    } else if (word == "eight") {
        return '8';
    } else if (word == "nine") {
        return '9';
    } 
}

int extract_digits_with_words(const std::string& line)
{
    char first, last;
    std::string digitWord;
    bool isFirst = true;

    for (int i = 0; i < line.length(); i++) {
        for (std::string s : nums) {
            bool found = true;
            int idx = 0;
            while (idx < s.length()) {
                //std::cout << "first: " << line[i] << " second: " << s[idx]; 
                if (line[i + idx] != s[idx]) {
                    found = false;
                    break;
                }
                idx++;
            }
            if (found) {
                std::cout << "found!!! " << s << std::endl;
                if (isFirst) {
                    first = get_digit_from_word(s);
                    isFirst = false;
                }
                last = get_digit_from_word(s);
            }
        }

        if (std::isdigit(line[i])) {
            if (isFirst) {
                first = line[i];
                isFirst = false;
            }
            last = line[i];
        }
    }
   // std::cout << line << " " << std::string(1, first) + last << std::endl;
    return std::stoi(std::string(1, first) + last); 
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    int sum;
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit with an error code
    }


    while (std::getline(inputFile, line)) {
        // Process the 'line' variable here
        sum += extract_digits_with_words(line);
    }

    inputFile.close();

    std::cout << sum;
}
