#pragma once
#include <Windows.h>

#include <tlhelp32.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <math.h>

#include <string>
#include <vector>


namespace File {

}

namespace Process {
	typedef unsigned short int PORT;

	bool DEPProtect(DWORD Flags = 0);
	//数据执行保护开关; 成功返回true, 失败返回false
	//dwFlags：如果DEP系统策略为OptIn或OptOut并且为该进程启用了DEP, 则将dwFlags设置为0将禁用该进程的DEP

	bool SetDubugPrivilege(DWORD ProcessId = NULL);
	//成功返回true，把一个进程的权限提升到调试级权限
	//ProcessId：如果为空则默认为当前进程ID

	int PIDGetModules(DWORD ProcessID, std::vector <MODULEENTRY32>& ModulesList);//通过PID获取模块
	//失败为0，成功返回模块数量

	std::string PIDGetProcessName(DWORD ProcessID = NULL);
	//通过进程ID取得该进程执行文件名，也就是进程名

	bool IsPIDVaild(DWORD ProcessId);
	//判断一个进程ID是否存在（有效）

	PORT PIDGetLocalPorts(DWORD ProcessId);
	//通过进程PID取出本地端口
	//???

	DWORD CreateProcess(std::string ExePath, std::string CommandLine, PROCESS_INFORMATION* ProcessInfo);
	//创建一个程序进程(成功返回进程ID,失败返回0)
	//???

	int Enum(std::vector <PROCESSENTRY32>& ProcessInfoList);
	//失败返回0，成功返回进程数量

	void Pause(DWORD ProcessId, bool status = true);
	//将指定进程暂停(无返回值)
	//status：false = 恢复进程,true = 暂停进程
	//???

	unsigned int MemoryUseSituation(DWORD ProcessId = NULL, int ShowType = 1);
	//查看指定进程ID的内存使用情况
	//ShowType：0=Byte，1=KB，2=MB，3=GB，默认为1

	int GetPriorityClass(DWORD ProcessId = NULL);
	//特殊进程需要特权，检索指定的进程的优先级。返回值：0=最高,1=高于标准,2=实时,3=标准,4=低于标准,5=低,返回-1表示无权限访问进程。

	int GetHandleNumber(DWORD ProcessId = NULL);
	//获取指定进程句柄数量,与XP系统任务管理器功能一样，失败返回-1。特殊进程需要特权.

	std::string GetCommandLine32(DWORD ProcessId);
	//取指定进程ID的命令行.32位系统专用
	//???

	std::string GetCommandLine64(DWORD ProcessId);
	//取指定进程ID的命令行.64位系统专用
	//???

	PORT PortGetPID(PORT Port);
	//通过本地端口取出进程PID
	//???

	bool SetCannotOpen();
	//设置当前进程禁止被打开
	//???

	bool SetPriorityClass(DWORD ProcessId = NULL, DWORD Priority = 0);
	//设置一个进程的优先级别,成功返回true，失败返回false。特殊进程需要特权

	bool Terminate(DWORD ProcessId = NULL);
	bool Terminate(std::string ProcessName = "");//???
	//结束指定进程。成功返回true，失败返回false。


	bool IsProcessSuspending(DWORD ProcessId, int TimeOut = 100);
	//检测进程是否被暂停，亦可用于窗口是否假死
	//TimeOut：检测窗口的响应时间，超时则为假死，单位：毫秒；可空，默认100毫秒
	//???

	bool IsProcessNameVaild(std::string ProcessName, bool Case = false);
	//判断指定进程是否存在(此判断与进程其它信息无关联)(存在返回true，不存在或失败返回false)
	//Case：区分大小写。true = 区分大小写，false = 不区分大小写
	//???

	bool IsProcess64Bit(DWORD ProcessId = NULL);
	//判断进程是否为64位

	int GetThreadsNumber(DWORD ProcessId);
	int GetThreadsNumber(std::string ProcessName);
	//通过进程ID或进程名获取指定进程线程数。
	//???

	int GetSystemProcessList(std::vector <PROCESSENTRY32>& SystemProcessList);
	//失败返回0，成功返回进程数量
	//???

	std::string GetExePath();
	//取指定进程的程序路径，成功返回程序路径，失败或进程不存在返回空文本
	//???

	std::string GetProcessUser(DWORD ProcessId = NULL);
	//获取指定进程的用户名
	//???

	DWORD GetProcessParentHandle(DWORD ProcessId);
	DWORD GetProcessParentHandle(std::string ProcessName);
	//根据进程名或进程ID取出进程父ID，失败返回-1。
	//???

	std::string GetCurrentCommandLine();
	//取当前进程的命令行
	//???

	int GetSameNamePID(std::string ProcessName, std::vector<PROCESSENTRY32>& ProcessList);
	//取相同名称进程，成功返回进程id数量。返回-1表示失败。
	//???

	DWORD GetCurrentPID();
	//获取当前进程的PID

	int ProcessNameGetPIDList(std::string ProcessName, std::vector <PROCESSENTRY32>& ProcessList, bool Case = false);
	//取指定进程名称的所有进程的进程ID(返回进程ID数目,没有返回0)
	//Case：区分大小写。true = 区分大小写，false = 不区分大小写
	//???

	std::string GetProcessStartTime(DWORD ProcessId = NULL);
	//返回进程启动时间
	//???

	DWORD ProcessNameGetPID(std::string ProcessName, bool Case = false);
	//通过进程名取进程ID；失败返回0
	//Case：区分大小写。true = 区分大小写，false = 不区分大小写
	//???

	std::string PIDGetExePath(DWORD ProcessId);
	//通过进程ID获取进程路径
	//???
}