//
// Created by Ana Maria on 21/04/2020.
//

#include "TurretValidator.h"

void TurretValidator::validateTurret(const NorvenTurret &turretToValidate) {
    std::string errorMessage;

    if(turretToValidate.getLocationOfTurret().size() < 5)
        errorMessage += std::string("The location of a turret cannot be less than 5 characters!\n");
    if(turretToValidate.getSizeOfTurret().size() < 5)
        errorMessage += std::string("The size of a turret cannot be less than 5 characters!\n");
    if(turretToValidate.getAuraLevelOfTurret() < 0)
        errorMessage += std::string("The aura level of a turret cannot be negative!\n");
    if(turretToValidate.getNumberOfSeparatePartsOfTurret() < 0)
        errorMessage += std::string("The number of separate parts of a turret cannot be negative!\n");
    if(turretToValidate.getVisionOfTurret().size() < 5)
        errorMessage += std::string("The vision of a turret cannot be less than 5 characters!\n");

    if(!errorMessage.empty())
        throw MyException(errorMessage);
}
