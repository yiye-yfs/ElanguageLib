//main.cpp
//�����ڵ���
#include <iostream>
#include "ElanguageLib.h"

using namespace std;
using namespace ELL;

int main() {
	cout << Process::GetPIDByProcessName("QQ.exe") << endl;
	
	while (1);
	return 0;
}