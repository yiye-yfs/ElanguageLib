//main.cpp
//仅用于调试
#include <iostream>
#include "ElanguageLib.h"

using namespace std;
using namespace ELL;

int main() {
	
	Process::PauseProcess(Process::GetPIDByProcessName("taskmgr.exe"),true);
	while (1);
	return 0;
}