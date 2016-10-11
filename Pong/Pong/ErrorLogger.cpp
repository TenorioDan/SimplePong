#include <iostream>
#include <sstream>
#include <string>
#include <SDL.h>
#include "ErrorLogger.h"

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/



void logSDLError(std::ostream &os, const std::string &msg){
	std::ostringstream errMsg;
	errMsg << "message: " << msg << " error: " << SDL_GetError() << std::endl;
	OutputDebugString(errMsg.str().c_str());
	os << msg << " error: " << SDL_GetError() << std::endl;
}