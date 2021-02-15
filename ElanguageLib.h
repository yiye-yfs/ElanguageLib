#pragma once
#include <Windows.h>

#include <tlhelp32.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <aclapi.h>

#include <math.h>

#include <string>
#include <vector>


namespace ELL{ // E Language Library 的缩写
	typedef unsigned short int PORT;

	namespace Window {//窗口

		namespace Enum {//菜单

		}

	}

	namespace String {//字符串(文本)

	}

	namespace File {//文件
		
	}

	namespace Web {//网页

	}

	namespace Mouse {//鼠标

	}

	namespace KeyBoard {//键盘

	}

	namespace Music {//音乐

	}

	namespace Voice {//音量

	}

	namespace Code {//编码

	}

	namespace Thread {//线程

	}

	namespace System {//系统

	}

	namespace Directory {//目录

	}

	namespace Time {//时间

	}
	
	namespace Image {//图片

	}
	
	namespace Semaphore {//信号量

	}

	namespace DialogBox {//对话框

	}

	namespace Process {//进程

		namespace Contact {//进程通讯

		}

		BOOL DEPProtect(DWORD Flags = 0);
		//数据执行保护开关; 成功返回TRUE, 失败返回FALSE
		//dwFlags：如果DEP系统策略为OptIn或OptOut并且为该进程启用了DEP, 则将dwFlags设置为0将禁用该进程的DEP

		BOOL SetDubugPrivilege(DWORD ProcessId = NULL);
		//成功返回TRUE，把一个进程的权限提升到调试级权限
		//ProcessId：如果为空则默认为当前进程ID

		INT GetModulesByPID(DWORD ProcessID, std::vector <MODULEENTRY32>& ModulesList);//通过PID获取模块
		//失败为0，成功返回模块数量

		std::string GetProcessNameByPID(DWORD ProcessID = NULL);
		//通过进程ID取得该进程执行文件名，也就是进程名

		BOOL IsPIDVaild(DWORD ProcessId);
		//判断一个进程ID是否存在（有效）

		PORT GetLocalPortsByPID(DWORD ProcessId);
		//通过进程PID取出本地端口
		//???

		DWORD CreateProcess(std::string ExePath, std::string CommandLine, PROCESS_INFORMATION* ProcessInfo);
		//创建一个程序进程(成功返回进程ID,失败返回0)
		//???
		
		INT Enum(std::vector <PROCESSENTRY32>& ProcessInfoList);
		//失败返回0，成功返回进程数量

		VOID PauseProcess(DWORD ProcessId, BOOL status = TRUE);
		//将指定进程暂停(无返回值)
		//status：FALSE = 恢复进程,TRUE = 暂停进程
		//???

		UINT GetMemoryUseSituation(DWORD ProcessId = NULL, INT ShowType = 1);
		//查看指定进程ID的内存使用情况
		//ShowType：0=Byte，1=KB，2=MB，3=GB，默认为1

		INT GetPriorityClass(DWORD ProcessId = NULL);
		//特殊进程需要特权，检索指定的进程的优先级。返回值：0=最高,1=高于标准,2=实时,3=标准,4=低于标准,5=低,返回-1表示无权限访问进程

		INT GetHandleNumber(DWORD ProcessId = NULL);
		//获取指定进程句柄数量,与XP系统任务管理器功能一样，失败返回-1。特殊进程需要特权

		std::string GetCommandLine32(DWORD ProcessId);
		//取指定进程ID的命令行.32位系统专用
		//???

		std::string GetCommandLine64(DWORD ProcessId);
		//取指定进程ID的命令行.64位系统专用
		//???

		PORT GetPIDByPort(PORT Port);
		//通过本地端口取出进程PID
		//???

		BOOL SetCannotOpen();
		//设置当前进程禁止被打开
		//???

		BOOL SetPriorityClass(DWORD ProcessId = NULL, DWORD Priority = 0);
		//设置一个进程的优先级别,成功返回TRUE，失败返回FALSE。特殊进程需要特权

		BOOL TerminateProcessByPID(DWORD ProcessId = NULL);
		BOOL TerminateProcessByProcessName(std::string ProcessName = "");//???
		//结束指定进程。成功返回TRUE，失败返回FALSE。


		BOOL IsProcessSuspending(DWORD ProcessId, INT TimeOut = 100);
		//检测进程是否被暂停，亦可用于窗口是否假死
		//TimeOut：检测窗口的响应时间，超时则为假死，单位：毫秒；可空，默认100毫秒
		//???

		BOOL IsProcessNameVaild(std::string ProcessName, BOOL Case = FALSE);
		//判断指定进程是否存在(此判断与进程其它信息无关联)(存在返回TRUE，不存在或失败返回FALSE)
		//Case：区分大小写。TRUE = 区分大小写，FALSE = 不区分大小写
		//???

		BOOL IsProcess64Bit(DWORD ProcessId = NULL);
		//判断进程是否为64位

		INT GetThreadsNumber(DWORD ProcessId);
		INT GetThreadsNumber(std::string ProcessName);
		//通过进程ID或进程名获取指定进程线程数。
		//???

		INT GetSystemProcessList(std::vector <PROCESSENTRY32>& SystemProcessList);
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

		INT GetSameNamePID(std::string ProcessName, std::vector<PROCESSENTRY32>& ProcessList);
		//取相同名称进程，成功返回进程id数量。返回-1表示失败。
		//???
		
		DWORD GetCurrentPID();
		//获取当前进程的PID

		INT GetPIDListByProcessName(std::string ProcessName, std::vector <PROCESSENTRY32>& ProcessList, BOOL Case = FALSE);
		//取指定进程名称的所有进程的进程ID(返回进程ID数目,没有返回0)
		//Case：区分大小写。TRUE = 区分大小写，FALSE = 不区分大小写
		//???

		std::string GetProcessStartTime(DWORD ProcessId = NULL);
		//返回进程启动时间
		//???

		DWORD GetPIDByProcessName(std::string ProcessName, BOOL Case = FALSE);
		//通过进程名取进程ID；失败返回0
		//Case：区分大小写。TRUE = 区分大小写，FALSE = 不区分大小写
		//???

		std::string GetExePathByPID(DWORD ProcessId);
		//通过进程ID获取进程路径
		//???
	}
}