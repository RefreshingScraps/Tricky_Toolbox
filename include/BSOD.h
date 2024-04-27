#ifndef BSOD_H
#define BSOD_H
#include <windows.h>
using namespace std;
int BSOD_Custom(ULONG code){	//立即蓝屏（自定义代码） 
	const unsigned int SE_SHUTDOWN_PRIVILEGE = 0x13;
	HMODULE hDll = ::LoadLibrary("ntdll.dll");
	typedef int (* type_RtlAdjustPrivilege)(int, bool, bool, bool*);
	typedef int (* type_NtRaiseHardError)(ULONG,UINT,UINT,PUINT_PTR,UINT,UINT*);
	type_RtlAdjustPrivilege RtlAdjustPrivilege = (type_RtlAdjustPrivilege)GetProcAddress(hDll, "RtlAdjustPrivilege");
	type_NtRaiseHardError NtRaiseHardError = (type_NtRaiseHardError)GetProcAddress(hDll, "NtRaiseHardError");
	bool nEn = false;
	UINT Response;
	int nResult = RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, true, false, &nEn);
	nResult = NtRaiseHardError(code,0,0,NULL,6,&Response);
	FreeLibrary(hDll);
	return nResult;
}
#endif
