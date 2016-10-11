#ifndef ERROR_LOGGER
#define ERROR_LOGGER

#include "Windows.h"
#include <iostream>

void logSDLError(std::ostream &os, const std::string &msg);

#endif