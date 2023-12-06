#include <map>
#include <string>
#include <vector>


class Turn {
    std::map<std::string, int> colors;

    public:
    Turn(std::string& input);
    std::map<std::string, int> getColors();
};

class Game {
    int id;
    std::vector<Turn> turns;
    bool possible = true;
    
    constexpr static int MAX_RED      = 12;
    constexpr static int MAX_GREEN    = 13;
    constexpr static int MAX_BLUE     = 14;

    public:
    Game(std::string& input);
    void checkGame();
    int getId();
    bool isPossible();
    std::vector<Turn> getTurns();
};