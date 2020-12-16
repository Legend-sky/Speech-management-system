/*
2020.12.8
演讲比赛流程设计
开始演讲比赛：每个比赛阶段需要给用户一个提示，用户按任意键后继续下一阶段
查看往届记录：查看之前比赛前三名结果，每次比赛都会记录到文件中，文件用.csv格式保存
清空比赛记录：将文件中数据清空
退出比赛程序：可以退出当前程序
*/
#include<iostream>
#include<ctime>
using namespace std;
#include"speechManager.h"

int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_speaker.begin(); it != sm.m_speaker.end(); it++)
	{
		cout << "选手编号：" << it->first << " 选手姓名：" << it->second.m_name << " 选手分数：" << it->second.m_Score[0] << endl;
	}*/
	int choice = 0;
	while(1) {
		sm.show_meun();
		cout << "请输入你的选择：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//开始演讲比赛
			sm.startspeech();
			break;
		case 2:		//查看往届记录
			sm.showRecord();
			break;
		case 3:		//清空比赛记录
			sm.clearRecord();
			break;
		case 0:		//退出系统
			sm.exitSystem();	
			break;
		default:
			system("cls");	//清屏
			break;
		}
	}


	system("pause");
}