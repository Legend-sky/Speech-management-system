/*
2020.12.8
�ݽ������������
��ʼ�ݽ�������ÿ�������׶���Ҫ���û�һ����ʾ���û���������������һ�׶�
�鿴�����¼���鿴֮ǰ����ǰ���������ÿ�α��������¼���ļ��У��ļ���.csv��ʽ����
��ձ�����¼�����ļ����������
�˳��������򣺿����˳���ǰ����
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
		cout << "ѡ�ֱ�ţ�" << it->first << " ѡ��������" << it->second.m_name << " ѡ�ַ�����" << it->second.m_Score[0] << endl;
	}*/
	int choice = 0;
	while(1) {
		sm.show_meun();
		cout << "���������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:		//��ʼ�ݽ�����
			sm.startspeech();
			break;
		case 2:		//�鿴�����¼
			sm.showRecord();
			break;
		case 3:		//��ձ�����¼
			sm.clearRecord();
			break;
		case 0:		//�˳�ϵͳ
			sm.exitSystem();	
			break;
		default:
			system("cls");	//����
			break;
		}
	}


	system("pause");
}