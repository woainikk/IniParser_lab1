//
// Created by Маргарита on 12.09.2017.
//

#pragma once

#include <string>
#include <iostream>


class ParamNotFound : public std::runtime_error {
public:
    explicit ParamNotFound(const std::string &param)  : std::runtime_error("Parameter " + param + " does not found") {}
};


