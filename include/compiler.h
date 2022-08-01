#ifndef COMPILER_H
#define COMPILER_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ErrorHandler.h"

void Compile(string file);
ErrorHandler ReadingFile(string file);
void ThrowError(int errorcode, string error);

#endif