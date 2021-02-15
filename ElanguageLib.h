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
	//����ִ�б�������; �ɹ�����true, ʧ�ܷ���false
	//dwFlags�����DEPϵͳ����ΪOptIn��OptOut����Ϊ�ý���������DEP, ��dwFlags����Ϊ0�����øý��̵�DEP

	bool SetDubugPrivilege(DWORD ProcessId = NULL);
	//�ɹ�����true����һ�����̵�Ȩ�����������Լ�Ȩ��
	//ProcessId�����Ϊ����Ĭ��Ϊ��ǰ����ID

	int PIDGetModules(DWORD ProcessID, std::vector <MODULEENTRY32>& ModulesList);//ͨ��PID��ȡģ��
	//ʧ��Ϊ0���ɹ�����ģ������

	std::string PIDGetProcessName(DWORD ProcessID = NULL);
	//ͨ������IDȡ�øý���ִ���ļ�����Ҳ���ǽ�����

	bool IsPIDVaild(DWORD ProcessId);
	//�ж�һ������ID�Ƿ���ڣ���Ч��

	PORT PIDGetLocalPorts(DWORD ProcessId);
	//ͨ������PIDȡ�����ض˿�
	//???

	DWORD CreateProcess(std::string ExePath, std::string CommandLine, PROCESS_INFORMATION* ProcessInfo);
	//����һ���������(�ɹ����ؽ���ID,ʧ�ܷ���0)
	//???

	int Enum(std::vector <PROCESSENTRY32>& ProcessInfoList);
	//ʧ�ܷ���0���ɹ����ؽ�������

	void Pause(DWORD ProcessId, bool status = true);
	//��ָ��������ͣ(�޷���ֵ)
	//status��false = �ָ�����,true = ��ͣ����
	//???

	unsigned int MemoryUseSituation(DWORD ProcessId = NULL, int ShowType = 1);
	//�鿴ָ������ID���ڴ�ʹ�����
	//ShowType��0=Byte��1=KB��2=MB��3=GB��Ĭ��Ϊ1

	int GetPriorityClass(DWORD ProcessId = NULL);
	//���������Ҫ��Ȩ������ָ���Ľ��̵����ȼ�������ֵ��0=���,1=���ڱ�׼,2=ʵʱ,3=��׼,4=���ڱ�׼,5=��,����-1��ʾ��Ȩ�޷��ʽ��̡�

	int GetHandleNumber(DWORD ProcessId = NULL);
	//��ȡָ�����̾������,��XPϵͳ�������������һ����ʧ�ܷ���-1�����������Ҫ��Ȩ.

	std::string GetCommandLine32(DWORD ProcessId);
	//ȡָ������ID��������.32λϵͳר��
	//???

	std::string GetCommandLine64(DWORD ProcessId);
	//ȡָ������ID��������.64λϵͳר��
	//???

	PORT PortGetPID(PORT Port);
	//ͨ�����ض˿�ȡ������PID
	//???

	bool SetCannotOpen();
	//���õ�ǰ���̽�ֹ����
	//???

	bool SetPriorityClass(DWORD ProcessId = NULL, DWORD Priority = 0);
	//����һ�����̵����ȼ���,�ɹ�����true��ʧ�ܷ���false�����������Ҫ��Ȩ

	bool Terminate(DWORD ProcessId = NULL);
	bool Terminate(std::string ProcessName = "");//???
	//����ָ�����̡��ɹ�����true��ʧ�ܷ���false��


	bool IsProcessSuspending(DWORD ProcessId, int TimeOut = 100);
	//�������Ƿ���ͣ��������ڴ����Ƿ����
	//TimeOut����ⴰ�ڵ���Ӧʱ�䣬��ʱ��Ϊ��������λ�����룻�ɿգ�Ĭ��100����
	//???

	bool IsProcessNameVaild(std::string ProcessName, bool Case = false);
	//�ж�ָ�������Ƿ����(���ж������������Ϣ�޹���)(���ڷ���true�������ڻ�ʧ�ܷ���false)
	//Case�����ִ�Сд��true = ���ִ�Сд��false = �����ִ�Сд
	//???

	bool IsProcess64Bit(DWORD ProcessId = NULL);
	//�жϽ����Ƿ�Ϊ64λ

	int GetThreadsNumber(DWORD ProcessId);
	int GetThreadsNumber(std::string ProcessName);
	//ͨ������ID���������ȡָ�������߳�����
	//???

	int GetSystemProcessList(std::vector <PROCESSENTRY32>& SystemProcessList);
	//ʧ�ܷ���0���ɹ����ؽ�������
	//???

	std::string GetExePath();
	//ȡָ�����̵ĳ���·�����ɹ����س���·����ʧ�ܻ���̲����ڷ��ؿ��ı�
	//???

	std::string GetProcessUser(DWORD ProcessId = NULL);
	//��ȡָ�����̵��û���
	//???

	DWORD GetProcessParentHandle(DWORD ProcessId);
	DWORD GetProcessParentHandle(std::string ProcessName);
	//���ݽ����������IDȡ�����̸�ID��ʧ�ܷ���-1��
	//???

	std::string GetCurrentCommandLine();
	//ȡ��ǰ���̵�������
	//???

	int GetSameNamePID(std::string ProcessName, std::vector<PROCESSENTRY32>& ProcessList);
	//ȡ��ͬ���ƽ��̣��ɹ����ؽ���id����������-1��ʾʧ�ܡ�
	//???

	DWORD GetCurrentPID();
	//��ȡ��ǰ���̵�PID

	int ProcessNameGetPIDList(std::string ProcessName, std::vector <PROCESSENTRY32>& ProcessList, bool Case = false);
	//ȡָ���������Ƶ����н��̵Ľ���ID(���ؽ���ID��Ŀ,û�з���0)
	//Case�����ִ�Сд��true = ���ִ�Сд��false = �����ִ�Сд
	//???

	std::string GetProcessStartTime(DWORD ProcessId = NULL);
	//���ؽ�������ʱ��
	//???

	DWORD ProcessNameGetPID(std::string ProcessName, bool Case = false);
	//ͨ��������ȡ����ID��ʧ�ܷ���0
	//Case�����ִ�Сд��true = ���ִ�Сд��false = �����ִ�Сд
	//???

	std::string PIDGetExePath(DWORD ProcessId);
	//ͨ������ID��ȡ����·��
	//???
}