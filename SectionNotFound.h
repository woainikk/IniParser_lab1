//
// Created by Маргарита on 12.09.2017.
//

#pragma once

#include <iostream>



class SectionNotFound : public std::runtime_error {
public:
    explicit SectionNotFound(const std::string &section)  : std::runtime_error("Section " + section+ " does not found") {}
};



