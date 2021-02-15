#include "ElanguageLib.h"

BOOL ELL::Process::DEPProtect(DWORD Flags){
    if (GetSystemDEPPolicy() < 2) {
        return false;
    }
    return SetProcessDEPPolicy(Flags);
}

BOOL ELL::Process::SetDubugPrivilege(DWORD ProcessId){
    if (ProcessId == NULL) { ProcessId = GetCurrentProcessId(); }
    HANDLE handleProcess = OpenProcess(2035711, 0, ProcessId);
    if (handleProcess == INVALID_HANDLE_VALUE) { return false; }
    HANDLE token = NULL;
    OpenProcessToken(handleProcess, 983551, &token);
    LUID destLuid = {};
    LookupPrivilegeValueA(NULL, "SeDebugPrivilege", &destLuid);
    TOKEN_PRIVILEGES processPrivilege = {};
    processPrivilege.PrivilegeCount = 1;
    processPrivilege.Privileges->Attributes = 2;
    processPrivilege.Privileges->Luid.LowPart = destLuid.LowPart;
    processPrivilege.Privileges->Luid.HighPart = destLuid.HighPart;
    bool ret = AdjustTokenPrivileges(token, false, &processPrivilege, NULL, NULL, NULL);
    CloseHandle(handleProcess);
    return ret;
}

INT ELL::Process::PIDGetModules(DWORD ProcessID, std::vector <MODULEENTRY32>& ModulesList){
    if (ProcessID == NULL) {
        ProcessID = GetCurrentProcessId();
    }
    unsigned int modulesNumber = 0;
    ModulesList.clear();
    HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
    if (handleSnapshot == INVALID_HANDLE_VALUE) { return 0; }
    MODULEENTRY32 moduleInfo = {};
    moduleInfo.dwSize = sizeof(MODULEENTRY32);
    bool Bool = Module32First(handleSnapshot, &moduleInfo);
    while (Bool) {
        if (moduleInfo.hModule != NULL) {
            modulesNumber++;
            ModulesList.push_back(moduleInfo);
        }
        Bool = Module32Next(handleSnapshot, &moduleInfo);
    }
    CloseHandle(handleSnapshot);
    return modulesNumber;
}

std::string ELL::Process::PIDGetProcessName(DWORD ProcessID){
    if (ProcessID == NULL) {
        ProcessID = GetCurrentProcessId();
    }
    HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, ProcessID);
    if (handleSnapshot == INVALID_HANDLE_VALUE) { return ""; }
     PROCESSENTRY32 processInfo = {};
    processInfo.dwSize = sizeof(PROCESSENTRY32);
    bool Bool = Process32First(handleSnapshot, &processInfo);
    while (Bool) {
        if (processInfo.th32ProcessID == ProcessID) {
            CloseHandle(handleSnapshot);
            return processInfo.szExeFile;
        }
        Bool = Process32Next(handleSnapshot, &processInfo);
    }
    CloseHandle(handleSnapshot);
    return "";
}

BOOL ELL::Process::IsPIDVaild(DWORD ProcessId){
    if (ProcessId == NULL) { return false; }
    DWORD processIdArray[1024] = {0};
    DWORD cbNeeded = 0;
    bool Bool = EnumProcesses(processIdArray,1024 * sizeof(DWORD),&cbNeeded);
    if (Bool == true) {
        for (int i = 0; i <= cbNeeded / 4; i++) {
            if (processIdArray[i] == ProcessId) {
                return true;
            }
        }
    }
    return false;
}

ELL::PORT ELL::Process::PIDGetLocalPorts(DWORD ProcessId){
    /*
    MIB_TCPTABLE_OWNER_PID tcpTable = {};
    DWORD pdwSize = 0;
    DWORD ret  = GetExtendedTcpTable(&tcpTable,&pdwSize,true, AF_INET, TCP_TABLE_OWNER_PID_ALL,NULL);
    if (ret == NULL) {
        for (int i = 0; i <= tcpTable.dwNumEntries; i++) {
            if (ProcessId == tcpTable.table[i].dwOwningPid) {
                return tcpTable.table[i].dwLocalPort;
            }           
        }
    }*/
    return 0;
}

DWORD ELL::Process::CreateProcess(std::string ExePath, std::string CommandLine, PROCESS_INFORMATION* ProcessInfo){

    STARTUPINFO WindowInfo = {};
    return CreateProcessA(ExePath.c_str(), (LPSTR)CommandLine.c_str(), NULL, NULL, NULL, NULL, NULL, "", &WindowInfo, ProcessInfo) ? ProcessInfo->dwProcessId : NULL;
}

INT ELL::Process::Enum(std::vector<PROCESSENTRY32>& ProcessInfoList){
    HANDLE handleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL,NULL);
    if (handleSnapshot == INVALID_HANDLE_VALUE) { return 0; }
    ProcessInfoList.clear();
    PROCESSENTRY32 processInfo = {};
    processInfo.dwSize = sizeof(PROCESSENTRY32);
    bool FindBool = Process32First(handleSnapshot, &processInfo);
    unsigned short int number = 0;
    while (FindBool == true) {
        ProcessInfoList.push_back(processInfo);
        number++;
        FindBool = Process32Next(handleSnapshot, &processInfo);
    }
    CloseHandle(handleSnapshot);
    return number;
}

VOID ELL::Process::Pause(DWORD ProcessId, BOOL status){
    HANDLE handleProcess = OpenProcess(2035711, NULL, ProcessId);
    if (handleProcess == INVALID_HANDLE_VALUE) { return; }
    /*
    if (status) {
        PROC procAPIAddress = GetProcAddress(GetModuleHandleA("ntdll.dll"),"ZwSuspendProcess");
        (*procAPIAddress)();
    }
    else {
        PROC procAPIAddress = GetProcAddress(GetModuleHandleA("ntdll.dll"),"ZwResumeProcess");
        (*procAPIAddress)();
    }
    */
    CloseHandle(handleProcess);
    return;
}

unsigned int ELL::Process::MemoryUseSituation(DWORD ProcessId, INT ShowType){
    if (ShowType == NULL || ShowType < 0) {
        ShowType = 1;
    }
    HANDLE handleProcess = OpenProcess(PROCESS_QUERY_INFORMATION,NULL,ProcessId);
    if (handleProcess == INVALID_HANDLE_VALUE) { return -1; }
    PROCESS_MEMORY_COUNTERS mem = {};
    if (GetProcessMemoryInfo(handleProcess,&mem,40) != NULL) {
        CloseHandle(handleProcess);
        return (unsigned int)mem.WorkingSetSize / pow(1024, ShowType);
    }
    CloseHandle(handleProcess);
    return 0;
}

INT ELL::Process::GetPriorityClass(DWORD ProcessId){
    HANDLE handleProcess = ProcessId == NULL ? GetCurrentProcess() : OpenProcess(1024, NULL, ProcessId);
    if (handleProcess == INVALID_HANDLE_VALUE) { return -1; }
    DWORD Class =  ::GetPriorityClass(handleProcess);
    int type = 0;
    if (Class == HIGH_PRIORITY_CLASS) { type = 0; }
    if (Class == ABOVE_NORMAL_PRIORITY_CLASS) { type = 1; }
    if (Class == REALTIME_PRIORITY_CLASS) { type = 2; }
    if (Class == NORMAL_PRIORITY_CLASS) { type = 3; }
    if (Class == BELOW_NORMAL_PRIORITY_CLASS) { type = 4; }
    if (Class == IDLE_PRIORITY_CLASS) { type = 5; }
    CloseHandle(handleProcess);
    return type;
}

INT ELL::Process::GetHandleNumber(DWORD ProcessId){
    HANDLE handleProcess = ProcessId == NULL ? GetCurrentProcess() : OpenProcess(2035711, NULL, ProcessId);
    DWORD count = 0;
    if (!GetProcessHandleCount(handleProcess, &count)) {
        count = -1;
    }
    CloseHandle(handleProcess);
    return count;
}

std::string ELL::Process::GetCurrentCommandLine(){
    return GetCommandLineA();
}

DWORD ELL::Process::GetCurrentPID(){
    return GetCurrentProcessId();
}

std::string ELL::Process::GetProcessStartTime(DWORD ProcessId){
    HANDLE handleProcess = ProcessId == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcessId);
    FILETIME createTime = {};//���̵Ĵ���ʱ��
    FILETIME exitTime = {};//���̵��˳�ʱ��
    FILETIME kernelTime = {};//�������ں�ģʽ�µ�����ʱ��
    FILETIME userTime = {};//�������û�ģʽ�µ�����ʱ��
    GetProcessTimes(handleProcess, &createTime, &exitTime, &kernelTime, &userTime);
    CloseHandle(handleProcess);
    SYSTEMTIME userSystemTime = {};
    FileTimeToSystemTime(&createTime, &userSystemTime);
    return std::string();//???
}

DWORD ELL::Process::ProcessNameGetPID(std::string ProcessName, BOOL Case){
    return 0;
}

BOOL ELL::Process::IsProcess64Bit(DWORD ProcessId){
    HANDLE handleProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ProcessId);
    if (handleProcess != NULL) {
        BOOL isWow64 = false;
        bool ret = IsWow64Process(handleProcess,&isWow64);
        CloseHandle(handleProcess);
        if (ret) {
            return !isWow64;
        }

    }
    return false;
}

BOOL ELL::Process::SetPriorityClass(DWORD ProcessId, DWORD Priority){
    if (Priority == 0) { Priority = HIGH_PRIORITY_CLASS; }
    if (Priority == 1) { Priority = ABOVE_NORMAL_PRIORITY_CLASS; }
    if (Priority == 2) { Priority = REALTIME_PRIORITY_CLASS; }
    if (Priority == 3) { Priority = NORMAL_PRIORITY_CLASS; }
    if (Priority == 4) { Priority = BELOW_NORMAL_PRIORITY_CLASS; }
    if (Priority == 5) { Priority = IDLE_PRIORITY_CLASS; }
    HANDLE handleProcess = ProcessId == NULL ? GetCurrentProcess() : OpenProcess(PROCESS_SET_INFORMATION, NULL, ProcessId);
    if (handleProcess == INVALID_HANDLE_VALUE) { return false; }
    BOOL ret = ::SetPriorityClass(handleProcess, Priority);
    CloseHandle(handleProcess);
    return ret;
}

BOOL ELL::Process::Terminate(DWORD ProcessId){
    if (ProcessId == NULL) { ProcessId = GetCurrentProcessId(); }
    HANDLE handleProcess = OpenProcess(1, 0, ProcessId);
    bool ret = TerminateProcess(handleProcess,0) == 1;
    return ret;
}

BOOL ELL::Process::Terminate(std::string ProcessName){
    /*
    if (ProcessName == "") {
        CHAR tmp[MAX_PATH] = { NULL };
        if (!GetModuleFileNameA(NULL,tmp,MAX_PATH)) {

        }
        ProcessName = GetModuleFileNameA(); 
    }
    HANDLE handleProcess = OpenProcess(1, 0, ProcessNameGetPID(ProcessName, true));
    bool ret = TerminateProcess(handleProcess, 0) == 1;
    
    return ret;
    */
}
