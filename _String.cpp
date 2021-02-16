#include "ElanguageLib.h"

std::string ELL::String::FillZero(std::string Str, UINT Lenght){
	if (Str.length() < Lenght) {
		UINT len = Lenght - Str.length();
		for (UINT i = 0; i < len; i++){
			Str = "0" + Str;
		}
		return Str;
	}
	else {
		return Str;
	}
}