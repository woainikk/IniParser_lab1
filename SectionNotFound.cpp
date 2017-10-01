//
// Created by Маргарита on 01.10.2017.
//

#include "SectionNotFound.h"

SectionNotFound::SectionNotFound(const char* section) {
    incorrectSection = section;
}

const char* SectionNotFound::what() const noexcept {
    return incorrectSection;
}