#include "2.h"
#include <iostream>
#include <fstream>


Game::Game(std::string& input) {
    std::string stringId;
    std::string turnString;
    int i = 5;

    while (true) {
        stringId.push_back(input[i]);
        i++;

        if (input[i] == ':')
            break;

    }
    this->id = std::stoi(stringId);

    for (i++; i <= input.length(); i++) {
       // std::cout << input[i];
        if (input[i] == ';' or i == input.length()) {
            std::cout << turnString << std::endl;
            Turn turn(turnString);
            this->turns.push_back(turn);
            turnString.clear();
            continue;
        }
        turnString.push_back(input[i]);
    }

    checkGame();
}

void Game::checkGame(){
    for (Turn t : turns) {
        int green = t.getColors()["green"];
        int red = t.getColors()["red"];
        int blue = t.getColors()["blue"];

        //std::cout << "green: " << green << " red: " << red << " blue: " << blue << 
        //  "isPossible: " << possible << std::endl;

        if (green > MAX_GREEN or red > MAX_RED or blue > MAX_BLUE) {
            this->possible = false;
        }
    }
}

int Game::getId() {
    return this->id;
}

bool Game::isPossible() {
    return this->possible;
}


Turn::Turn (std::string& input) {
    std::string color;
    std::string count;
    bool readingCount = false;

    for (char c : input) {
        if (std::isdigit(c)) {
            count.push_back(c);
            readingCount = true;
        }

        else if (c == ' ') {
            continue;
        } else if (c == ':' || c == ',' || c == ';') {
            //std::cout << "adding..." << color << ' ' << count << std::endl;
            this->colors[color] = std::stoi(count);
            color.clear();
            count.clear();
        } else {
            color += c;
        }
    }
                this->colors[color] = std::stoi(count);

}

std::map<std::string, int> Turn::getColors() {
    return this->colors;
}

std::vector<Turn> Game::getTurns()
{
    return turns;
}

void printGame(Game& game) {
    std::cout << "Game " << game.getId() << std::endl;
    std::cout << "Turns: " << std::endl;
    for (Turn t : game.getTurns()) {
        int green = t.getColors()["green"];
        int red = t.getColors()["red"];
        int blue = t.getColors()["blue"];

        std::cout << "green: " << green << " red: " << red << " blue: " << blue << std::endl;

    }
    std::cout << "isPossible: " << game.isPossible() << std::endl;
    std::cout << "----------------------------------\n";
}

int getMinimumPower(Game game)
{
    int minGreen;
    int minRed;
    int minBlue;
    bool first = true;
    for (Turn t : game.getTurns()) {
        int green, red, blue;
        if (first) {
            minGreen = t.getColors()["green"];
            minRed = t.getColors()["red"];
            minBlue = t.getColors()["blue"];
            first = false;
        }

        green = t.getColors()["green"];
        red = t.getColors()["red"];
        blue = t.getColors()["blue"];

        if (green > minGreen)
            minGreen = green;

        if (red > minRed)
            minRed = red;

        if (blue > minBlue)
            minBlue = blue;

        //std::cout << "green: " << green << " red: " << red << " blue: " << blue << std::endl;

    }
    std::cout << minBlue << " " << minGreen << " " << minRed << std::endl;
    return minGreen * minRed * minBlue; 
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
        std::cout << "sum is: " << sum << std::endl;
        Game game(line);
        sum += getMinimumPower(game);
    }

    inputFile.close();

    std::cout << sum;
}