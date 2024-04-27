#ifndef SOUNDS_H
#define SOUNDS_H 
#include <mmsystem.h>
#include <iostream> 
void Set_Sound_Name(std::string filename){	//…Ë÷√“Ù¿÷√˚ 
	std::string n="open \""+filename+"\" alias s1";
	mciSendString(n.c_str(),NULL,0,NULL);
}
void Play_Sound(){
	mciSendString(TEXT("play s1"),NULL,0,NULL);
}
void Pause_Sound(){
	mciSendString(TEXT("pause s1"),NULL,0,NULL);
}
void Stop_Sound(){
	mciSendString(TEXT("stop s1"),NULL,0,NULL);
}
#endif
