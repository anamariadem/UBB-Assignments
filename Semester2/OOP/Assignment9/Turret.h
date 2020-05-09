//
// Created by Ana Maria on 10/04/2020.
//

#ifndef ASSIGNMENT7_TURRET_H
#define ASSIGNMENT7_TURRET_H

#include <string>
#include <vector>
#include <sstream>

class NorvenTurret {
private:
    std::string location;
    std::string size;
    int auraLevel;
    int separateParts;
    std::string vision;

public:
    // default constructor
    NorvenTurret();

    //constructor with parameters
    NorvenTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string& vision);

    std::string getLocationOfTurret() const { return location;}
    std::string getSizeOfTurret() const { return size; }
    int getAuraLevelOfTurret() const { return auraLevel; }
    int getNumberOfSeparatePartsOfTurret() const {return separateParts;}
    std::string getVisionOfTurret() const { return vision; }

    void setSizeOfTurret(std::string& newSize) { size = newSize; }
    void setAuraLevelOfTurret(int newAuraLevel) { auraLevel = newAuraLevel;}
    void setNumberOfSeparatePartsOfTurret(int newNumberOfSeparateParts) { separateParts = newNumberOfSeparateParts; }
    void setVisionOfTurret(std::string& newVision) { vision = newVision;}

    friend std::istream& operator>>(std::istream& iStream, NorvenTurret& turret);
    friend std::ostream& operator<<(std::ostream& oStream, const NorvenTurret& turret);
    friend std::vector<std::string> separate(const std::string& stringToBeSeparated, char delimiter);

    std::string toString();
};


#endif //ASSIGNMENT7_TURRET_H
