//
// Created by Ana Maria on 19/03/2020.
//

#ifndef ASSIGNMENT5_DOMAIN_H
#define ASSIGNMENT5_DOMAIN_H


#include <string>

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
    NorvenTurret(const std::string& location, const std::string& size, const int& auraLevel, const int& separateParts, const std::string vision);

    std::string getLocationOfTurret() const { return location;}
    std::string getSizeOfTurret() const { return size; }
    int getAuraLevelOfTurret() const { return auraLevel; }
    int getNumberOfSeparatePartsOfTurret() const {return separateParts;}
    std::string getVisionOfTurret() const { return vision; }

    void setSizeOfTurret(std::string newSize) {size = newSize; }
    void setAuraLevelOfTurret(int newAuraLevel) {auraLevel = newAuraLevel;}
    void setNumberOfSeparatePartsOfTurret(int newNumberOfSeparateParts) {separateParts = newNumberOfSeparateParts; }
    void setVisionOfTurret(std::string newVision) {vision = newVision;}

    std::string toString();

};


#endif //ASSIGNMENT5_DOMAIN_H
