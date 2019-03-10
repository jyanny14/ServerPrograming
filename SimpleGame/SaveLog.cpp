#include "stdafx.h"
#include "SaveLog.h"
#include <iostream>
#include <fstream>
#include<chrono>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

void SaveLog(char* msg);

using namespace std;

void SaveLog(char* msg){

	// 하드디스크에 덧붙이기 모드로 쓴다
	ofstream out("2014184034 차은상 로그.txt", ios::app);

	//출력파일에 시간도 기록한다
	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	out << endl;
	out << "_________________________________________________________________________________" << endl;
	out << "저장시간 - " << ctime(&t) << " / " << msg;
	out << "_________________________________________________________________________________" << endl;
	out << endl;
}

//#include <chrono>
//#include<thread>
////측정시작
//auto begin = chrono::high_resolution_clock::now(); //초정밀 시간
//												   //쉬고 싶은 시간
//this_thread::sleep_for(3.3s);
////측정 끝
//auto elapsedtime = chrono::high_resolution_clock::now() - begin;
////결과 출력
//cout << chrono::duration<double>(elapsedtime).count() << "초 경과" << endl;