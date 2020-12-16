#pragma once	//防止头文件重复编译
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

	map<int, vector<string>>m_Record;	//存放往届记录
	vector<int>v1;	//储存第一轮比赛选手编号
	vector<int>v2;	//存第二轮比赛选手编号
	vector<int>vVictory;	//胜出前三轮选手编号
	map<int, Speaker>m_speaker;
	int m_Index;	//存放比赛轮数
	~SpeechManager();
};