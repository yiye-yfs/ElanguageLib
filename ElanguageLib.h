#pragma once
#include <Windows.h>

#include <tlhelp32.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <math.h>

#include <string>
#include <vector>


namespace ELL{ // E Language Library ����д
	typedef unsigned short int PORT;

	namespace Window {//����

		namespace Enum {//�˵�

		}

	}

	namespace String {//�ַ���(�ı�)

	}

	namespace File {//�ļ�
		
	}

	namespace Web {//��ҳ

	}

	namespace Mouse {//���

	}

	namespace KeyBoard {//����

	}

	namespace Music {//����

	}

	namespace Voice {//����

	}

	namespace Code {//����

	}

	namespace Thread {//�߳�

	}

	namespace System {//ϵͳ

	}

	namespace Directory {//Ŀ¼

	}

	namespace Time {//ʱ��

	}
	
	namespace Image {//ͼƬ

	}
	
	namespace Semaphore {//�ź���

	}

	namespace DialogBox {//�Ի���

	}

	namespace Process {//����

		namespace Contact {//����ͨѶ

		}

		BOOL DEPProtect(DWORD Flags = 0);
		//����ִ�б�������; �ɹ�����true, ʧ�ܷ���false
		//dwFlags�����DEPϵͳ����ΪOptIn��OptOut����Ϊ�ý���������DEP, ��dwFlags����Ϊ0�����øý��̵�DEP

		BOOL SetDubugPrivilege(DWORD ProcessId = NULL);
		//�ɹ�����true����һ�����̵�Ȩ�����������Լ�Ȩ��
		//ProcessId�����Ϊ����Ĭ��Ϊ��ǰ����ID

		INT GetModulesByPID(DWORD ProcessID, std::vector <MODULEENTRY32>& ModulesList);//ͨ��PID��ȡģ��
		//ʧ��Ϊ0���ɹ�����ģ������

		std::string GetProcessNameByPID(DWORD ProcessID = NULL);
		//ͨ������IDȡ�øý���ִ���ļ�����Ҳ���ǽ�����

		BOOL IsPIDVaild(DWORD ProcessId);
		//�ж�һ������ID�Ƿ���ڣ���Ч��

		PORT GetLocalPortsByPID(DWORD ProcessId);
		//ͨ������PIDȡ�����ض˿�
		//???

		DWORD CreateProcess(std::string ExePath, std::string CommandLine, PROCESS_INFORMATION* ProcessInfo);
		//����һ���������(�ɹ����ؽ���ID,ʧ�ܷ���0)
		//???
		
		INT Enum(std::vector <PROCESSENTRY32>& ProcessInfoList);
		//ʧ�ܷ���0���ɹ����ؽ�������

		VOID Pause(DWORD ProcessId, BOOL status = TRUE);
		//��ָ��������ͣ(�޷���ֵ)
		//status��false = �ָ�����,true = ��ͣ����
		//???

		UINT GetMemoryUseSituation(DWORD ProcessId = NULL, INT ShowType = 1);
		//�鿴ָ������ID���ڴ�ʹ�����
		//ShowType��0=Byte��1=KB��2=MB��3=GB��Ĭ��Ϊ1

		INT GetPriorityClass(DWORD ProcessId = NULL);
		//���������Ҫ��Ȩ������ָ���Ľ��̵����ȼ�������ֵ��0=���,1=���ڱ�׼,2=ʵʱ,3=��׼,4=���ڱ�׼,5=��,����-1��ʾ��Ȩ�޷��ʽ��̡�

		INT GetHandleNumber(DWORD ProcessId = NULL);
		//��ȡָ�����̾������,��XPϵͳ�������������һ����ʧ�ܷ���-1�����������Ҫ��Ȩ.

		std::string GetCommandLine32(DWORD ProcessId);
		//ȡָ������ID��������.32λϵͳר��
		//???

		std::string GetCommandLine64(DWORD ProcessId);
		//ȡָ������ID��������.64λϵͳר��
		//???

		PORT GetPIDByPort(PORT Port);
		//ͨ�����ض˿�ȡ������PID
		//???

		BOOL SetCannotOpen();
		//���õ�ǰ���̽�ֹ����
		//???

		BOOL SetPriorityClass(DWORD ProcessId = NULL, DWORD Priority = 0);
		//����һ�����̵����ȼ���,�ɹ�����true��ʧ�ܷ���false�����������Ҫ��Ȩ

		BOOL Terminate(DWORD ProcessId = NULL);
		BOOL Terminate(std::string ProcessName = "");//???
		//����ָ�����̡��ɹ�����true��ʧ�ܷ���false��


		BOOL IsProcessSuspending(DWORD ProcessId, INT TimeOut = 100);
		//�������Ƿ���ͣ��������ڴ����Ƿ����
		//TimeOut����ⴰ�ڵ���Ӧʱ�䣬��ʱ��Ϊ��������λ�����룻�ɿգ�Ĭ��100����
		//???

		BOOL IsProcessNameVaild(std::string ProcessName, BOOL Case = FALSE);
		//�ж�ָ�������Ƿ����(���ж������������Ϣ�޹���)(���ڷ���true�������ڻ�ʧ�ܷ���false)
		//Case�����ִ�Сд��true = ���ִ�Сд��false = �����ִ�Сд
		//???

		BOOL IsProcess64Bit(DWORD ProcessId = NULL);
		//�жϽ����Ƿ�Ϊ64λ

		INT GetThreadsNumber(DWORD ProcessId);
		INT GetThreadsNumber(std::string ProcessName);
		//ͨ������ID���������ȡָ�������߳�����
		//???

		INT GetSystemProcessList(std::vector <PROCESSENTRY32>& SystemProcessList);
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

		INT GetSameNamePID(std::string ProcessName, std::vector<PROCESSENTRY32>& ProcessList);
		//ȡ��ͬ���ƽ��̣��ɹ����ؽ���id����������-1��ʾʧ�ܡ�
		//???
		
		DWORD GetCurrentPID();
		//��ȡ��ǰ���̵�PID

		INT GetPIDListByProcessName(std::string ProcessName, std::vector <PROCESSENTRY32>& ProcessList, BOOL Case = FALSE);
		//ȡָ���������Ƶ����н��̵Ľ���ID(���ؽ���ID��Ŀ,û�з���0)
		//Case�����ִ�Сд��true = ���ִ�Сд��false = �����ִ�Сд
		//???

		std::string GetProcessStartTime(DWORD ProcessId = NULL);
		//���ؽ�������ʱ��
		//???

		DWORD GetPIDByProcessName(std::string ProcessName, BOOL Case = FALSE);
		//ͨ��������ȡ����ID��ʧ�ܷ���0
		//Case�����ִ�Сд��true = ���ִ�Сд��false = �����ִ�Сд
		//???

		std::string GetExePathByPID(DWORD ProcessId);
		//ͨ������ID��ȡ����·��
		//???
	}
}