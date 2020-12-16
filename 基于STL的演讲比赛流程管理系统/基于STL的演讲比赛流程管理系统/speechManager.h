#pragma once	//��ֹͷ�ļ��ظ�����
#include<iostream>
#include<vector>
#include<map>
#include<deque>
#include<functional>
#include<numeric>
#include<string>
#include<algorithm>
#include<fstream>
#include"Speaker.h"
using namespace std;
class SpeechManager {
public:
	SpeechManager();

	void show_meun();

	void exitSystem();

	void initspeech();

	void createspeaker();

	void startspeech();

	void speechDraw();

	void speechcontest();

	void showScore();

	void saveRecord();

	void loadRecord();

	void showRecord();

	void clearRecord();

	bool fileIsEmpty;

	map<int, vector<string>>m_Record;	//��������¼
	vector<int>v1;	//�����һ�ֱ���ѡ�ֱ��
	vector<int>v2;	//��ڶ��ֱ���ѡ�ֱ��
	vector<int>vVictory;	//ʤ��ǰ����ѡ�ֱ��
	map<int, Speaker>m_speaker;
	int m_Index;	//��ű�������
	~SpeechManager();
};