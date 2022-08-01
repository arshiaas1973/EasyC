#include <iostream>
#include "functions.h"

using namespace std;

void ThrowError(int errorcode, string error){
    cout << "ERR " << errorcode << ": " << error << endl;
    exit(69828232+errorcode);
}