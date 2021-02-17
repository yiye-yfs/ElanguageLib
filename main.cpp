//main.cpp
//仅用于调试
#include <iostream>
#include "ElanguageLib.h"

using namespace std;
using namespace ELL;

int main() {
	
	Process::PauseProcess(Process::GetPIDByProcessName("HMCL-3.1.94.exe"),true);
	while (1);
	return 0;
}