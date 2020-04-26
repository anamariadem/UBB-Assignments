//
// Created by Ana Maria on 21/04/2020.
//

#ifndef ASSIGNMENT8_TURRETVALIDATOR_H
#define ASSIGNMENT8_TURRETVALIDATOR_H

#include "Turret.h"

class MyException : public std::exception{
private:
    std::string message;

public:
    MyException(const std::string& errorMessage) {this->message = errorMessage;}
    const char* what() const noexcept override{ return message.c_str();}
    //std::string getErrorMessage() const { return this->message;}
};

class TurretValidator {
public:
    TurretValidator()= default;
    static void validateTurret(const NorvenTurret& turretToValidate);
};


#endif //ASSIGNMENT8_TURRETVALIDATOR_H
