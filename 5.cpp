
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include "5.h"

class Coords {
    long sourceStartRange;
    long targetStartRange;
    long range;
    
public:
    Coords(long sourceStartRange, long targetStartRange, long range) : sourceStartRange(sourceStartRange), targetStartRange(targetStartRange), range(range) {}
    
    long getSourceStartRange()
    {
        return sourceStartRange;
    }
    
    long getTargetStartRange()
    {
        return targetStartRange;
    }
    
    long getRange() {
        return range;
    }
};

class Map {
    std::vector<Coords> coords;
    std::string name;
    
public:
    Map(std::string name) : name(name) { }
    
    void addRange(long target, long source, long range)
    {
        coords.push_back(Coords{source, target, range});
    }
    
    long checkSeed (long seed)
    {
        for (int i = 0; i < coords.size(); i++) {
            if (seed >= coords.at(i).getSourceStartRange() and seed < coords.at(i).getSourceStartRange() + coords.at(i).getRange()) {
                return (seed - coords.at(i).getSourceStartRange()) + coords.at(i).getTargetStartRange();
            }
        }
        
        return seed;
    }
};

void extractSeeds(std::vector<long> &seeds, std::string line) {
    std::string stringNumber;
    std::vector<long> tmp;
    bool isSeedNum = true;
    for (int i = 7; i < line.length(); i++ ) {
        if (std::isdigit(line[i])) {
            stringNumber.push_back(line[i]);
        } else {
            tmp.push_back(std::stol(stringNumber));
            stringNumber.clear();
        }
    }
    tmp.push_back(std::stol(stringNumber));
    
    for (int i = 0; i < tmp.size() - 1; i += 2) {
        for (long j = 0; j <= tmp.at(i + 1); j++) {
            seeds.push_back(tmp.at(i) + j);
        }
    }
    
}


int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<long> seeds;
    std::vector<Map*> maps;
    int count = 0;
    
    Map *map = nullptr;
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1; // Exit with an error code
    }
    
    std::string tmp;
    
    while (std::getline(inputFile, line)) {
        if (line.length() == 0 and map == nullptr)
            continue;
        
        if (count == 0) {
            extractSeeds(seeds, line);
            count++;

            continue;
          
        } else if (line.find("map") != std::string::npos) {
            map = new Map{line};
        } else if (line.length() == 0 and map != nullptr) {
            maps.push_back(map);
            continue;
        } else {
            int i = 0;
            long target = 0;
            long source = 0;
            long range = 0;
            
            for (char c : line) {
                if (std::isdigit(c)) {
                    tmp.push_back(c);
                } else {
                    switch (i) {
                        case 0:
                            target = std::stol(tmp);
                            tmp.clear();
                            i++;
                            break;
                        case 1:
                            source = std::stol(tmp);
                            tmp.clear();
                            i++;
                            break;
                        default:
                            break;
                    }
                }
                
            }
            range = std::stoi(tmp);
            tmp.clear();
            map->addRange(target, source, range);
            
        }

        
        count++;
    }
    maps.push_back(map);

    std::vector<long> locations;
    for (long seed : seeds) {
        long tmp = seed;
        for (Map* m : maps) {
            tmp = m->checkSeed(tmp);
        }
        locations.push_back(tmp);
    }
    
    long lowestLocation = locations.at(0);
    for (int i = 1; i < locations.size(); i++) {
        if (locations.at(i) < lowestLocation)
            lowestLocation = locations.at(i);
    }
    
    std::cout << lowestLocation << std::endl;
    
    for (Map* m : maps) {
        delete m;
    }
    inputFile.close();
    

    return 0;
}


