#include "ElanguageLib.h"

INT ELL::StringToInt(std::string Buf){
    
    return 0;
}

DOUBLE ELL::StringToDouble(std::string Buf){
    return DOUBLE();
}


PROC ELL::GetAPIAddress(std::string DllName, std::string APIName){
    return GetProcAddress(LoadLibraryA(DllName.c_str()),APIName.c_str());
}
