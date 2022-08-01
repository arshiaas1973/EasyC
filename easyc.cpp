#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <locale>
#include "include/compiler.h"
#include "include/functions.h"

using namespace std;

void printHelp(){
    cout << "Usage: easyc [options] file..."<< endl;
    cout << "Options:"<< endl;
    cout << "\t-s <file>\t\t\tOutput of Source Code Compilation will be a file with the name you specify."<< endl;
    cout << "\t-o <file>\t\t\tSource Code that Compiler is going to be the file path you specify."<< endl;
    cout << "Hope you have a great time using this compiler."<< endl;
    cout << "Bye!!"<< endl;
}

int ValidateNNulString(std::string text){
    int count = 0;
    std::locale loc;

    // string alpha = "ABCDEFGHIJKLMINOPQRSTUVWXYZabcdefghijklmnopqrstuwxyz";
    // for (char i : text)
    // {
    //     for (char j : alpha)
    //     {
    //         if(text[i] == alpha[j]){
    //             count++;
    //         }
    //     }
    // }

    for (std::string::iterator it=text.begin(); it!=text.end(); ++it)
    {
        if (std::isalpha(*it,loc))
            count++;
    }
    return count;
}

string GetExtensionOfFilename(string file){
    string ext = "";
    for (size_t x = (file.find('.')+1); x < size(file); x++){
        ext += file[x];
    }
    return ext;
}

int main(int argc, char** argv){
    
    bool isSourceDetected = false;
    bool isOutputDetected = false;
    bool isCorrectExtension = false;
    bool isOSDetected = false;

    int SourceIndex = 0;
    int OutputIndex = 0;

    string os = "";
    string file = "";
    string output = "";

    // Detecting OS
    #ifdef _WIN32
	    #ifdef _WIN64
	        isOSDetected = true;
            os = "win64";
	    #else 
	        isOSDetected = true;
            os = "win32";
	    #endif
    #endif
    #ifdef __APPLE__
        isOSDetected = true;
        os = "mac";
    #endif
    #ifdef __unix__
        isOSDetected = true;
        os = "unix";
    #endif
    #ifdef BSD
        isOSDetected = true;
        os = "bsd";
    #endif
    #ifdef __linux__
        isOSDetected = true;
        os = "linux";
    #endif
    #ifdef __ANDROID__
        isOSDetected = true;
        os = "android";
    #endif

    os="win32";
    
    if(argc >= 1){
        for (int i = 1; i < argc; i++)
        {
            if(strcmp(argv[i],"-h")==0){
                printHelp();
                exit(72697680);
            }else if(strcmp(argv[i],"--help")==0){
                printHelp();
                exit(72697680);
            }
            else if(strcmp(argv[i],"-s")==0){
                if(isSourceDetected){
                    ThrowError(01,"Source Code Defines only ONE Time!!!");
                }else{
                    isSourceDetected = true;
                    SourceIndex = i;
                }
            }else if(strcmp(argv[i],"-o")==0){
                if(isOutputDetected){
                    ThrowError(02,"Output File Defines only ONE Time!!!");
                }else{
                    isOutputDetected = true;
                    OutputIndex = i;
                }
            }else{
                if(isSourceDetected && file == "" && (i = (SourceIndex+1))){
                    file = argv[i];
                }else if(isOutputDetected && output == "" && (i = (OutputIndex+1))){
                    output = argv[i];
                }else{
                    if(argc == 2){
                        file = argv[i];
                    }else if(argc == 3){
                        if(i = 0){
                            file = argv[i];
                        }else{
                            output = argv[i];
                        }
                    }else{
                        ThrowError(03,"You are entering Extra Argument. Stop entering extra arguments.");
                    }
                }
            }
        }
        
    }

    if(file == "" || file == " "){
        ThrowError(04, "No Source File Specified");
    }else{
        if(ValidateNNulString(file) > 0){
            if(file.find('.') != std::string::npos){
                string ext = GetExtensionOfFilename(file);
                if(ValidateNNulString(ext) > 0){
                    if(ext == "ec"){
                        isCorrectExtension = true;
                    }else{
                        ThrowError(10, "Source File has a wrong file extension.");
                    }
                }else{
                    ThrowError(07, "Source Code's file extension doesn't contain a single character.");
                }
            }else{
                ThrowError(06, "Source File doesn't contain an extention.");
            }
        }else{
            ThrowError(05, "Source File must contain at least on character.");
        }
    }



    if((output == "" || output == " ")&&(file != "" && file != " ")){
        if(isCorrectExtension){
            string linuxExt = file.substr(0, file.find('.'));
            string unixExt = file.substr(0, file.find('.'));
            string windowsExt = file.substr(0, file.find('.')) + ".exe";
            string macExt = file.substr(0, file.find('.'));
            string bsdExt = file.substr(0, file.find('.'));

            if(os == "win64" || os == "win32")
                output = windowsExt;
            else if(os == "linux")
                output = linuxExt;
            else if(os == "mac")
                output = macExt;
            else if(os == "unix")
                output = unixExt;
            else if(os == "bsd")
                output = bsdExt;
        }
    }

    Compile(file);
    
}
