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

	// �ϵ��ũ�� �����̱� ���� ����
	ofstream out("2014184034 ������ �α�.txt", ios::app);

	//������Ͽ� �ð��� ����Ѵ�
	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	out << endl;
	out << "_________________________________________________________________________________" << endl;
	out << "����ð� - " << ctime(&t) << " / " << msg;
	out << "_________________________________________________________________________________" << endl;
	out << endl;
}

//#include <chrono>
//#include<thread>
////��������
//auto begin = chrono::high_resolution_clock::now(); //������ �ð�
//												   //���� ���� �ð�
//this_thread::sleep_for(3.3s);
////���� ��
//auto elapsedtime = chrono::high_resolution_clock::now() - begin;
////��� ���
//cout << chrono::duration<double>(elapsedtime).count() << "�� ���" << endl;