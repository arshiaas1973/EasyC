#include <iostream>
#include <fstream>
#include <cstdlib>
#include "compiler.h"
#include "ErrorHandler.h"

using namespace std;

ErrorHandler ReadingFile(string file){
    ifstream data(file);
    ErrorHandler err;
    if(!data){
        err.status = "error";
        err.ErrorID = 11;
        err.desc = "Source File could not be opened.\n Try this command in linux: sudo chmod 777 <sourcefile>.\n For Windows Users, NO RECOMMENDATION. (I'm a Linux User).\n Hope you can fix it.\nBYE!!";
        return err;
    }
    err.desc = "";
    err.status = "ok";
    string laststr = "";
    int z = 0;
    int h = 0;
    while ( data ) {
        getline(data, laststr);
        err.desc += laststr;
        data.tellg(); // Removing last repeated word.
    }
    data.close();
    
    return err;
}

void Compile(string file){

    ErrorHandler fhandler = ReadingFile(file);
    string text = "";

    if(fhandler.status == "error"){
        ThrowError(fhandler.ErrorID, fhandler.desc);
    }else if(fhandler.status == "ok"){
        text = fhandler.desc;
        
    }else{
        cout << fhandler.status << endl;
        ThrowError(12, "\""+fhandler.status+"\" is a new returned status.");
    }

}