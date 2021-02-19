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

std::string ELL::String::HigherCaseToLowerCase(std::string Str){
	size_t len = Str.size();
	for (int i = 0; i < len; i++) {
		if (Str[i] >= 'A' && Str[i] <= 'Z') {
			Str[i] = Str[i] + 32;
		}
	}
	return Str;
}

std::string ELL::String::LowerCaseToHigherCase(std::string Str){
	size_t len = Str.size();
	for (int i = 0; i < len; i++) {
		if (Str[i] >= 'a' && Str[i] <= 'z') {
			Str[i] = Str[i] - 32;
		}
	}
	return Str;
}
