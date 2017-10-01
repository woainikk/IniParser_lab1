//
// Created by Маргарита on 01.10.2017.
//

#include "ParamNotFound.h"

ParamNotFound::ParamNotFound(const char*  param) {
    incorrectParam = param;
}
const char* ParamNotFound::what()  const noexcept {
    return incorrectParam;
}
