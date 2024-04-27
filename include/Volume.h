#ifndef VOLUME_H
#define VOLUME_H
#include <mmdeviceapi.h>
#include <endpointvolume.h>

bool Mute_state(BOOL mute){	//�þ���״̬ 
	HMODULE hDll = ::LoadLibrary("ole32.dll");
	typedef int (* type_CoCreateInstance)(REFCLSID,LPUNKNOWN,DWORD,REFIID,LPVOID);
	type_CoCreateInstance CoCreateInstance = (type_CoCreateInstance)GetProcAddress(hDll, "CoCreateInstance");

	// ��ȡ�������ƽӿ�
    IAudioEndpointVolume *pVolume = NULL;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (hr == S_OK) {
        hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
        if (hr == S_OK) {
            hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pVolume);
        }
        pEnumerator->Release();
        pDevice->Release();
    }
 
    // ��������
    if (pVolume) {
        // ȡ������
        pVolume->SetMute(mute, NULL);
        pVolume->Release();
        return true;
    }
    FreeLibrary(hDll);
    return false;
}
bool Set_Volume(float value){//�������� 
	HMODULE hDll = ::LoadLibrary("ole32.dll");
	typedef int (* type_CoCreateInstance)(REFCLSID,LPUNKNOWN,DWORD,REFIID,LPVOID);
	type_CoCreateInstance CoCreateInstance = (type_CoCreateInstance)GetProcAddress(hDll, "CoCreateInstance");

	// ��ȡ�������ƽӿ�
    IAudioEndpointVolume *pVolume = NULL;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (hr == S_OK) {
        hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
        if (hr == S_OK) {
            hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pVolume);
        }
        pEnumerator->Release();
        pDevice->Release();
    }
    // ��������
    if (pVolume) {
        pVolume->SetMasterVolumeLevelScalar(static_cast<float>(value), NULL);
        return true;
    }
    FreeLibrary(hDll);
    return false;
}

#endif
