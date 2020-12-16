#include"speechManager.h"
SpeechManager::SpeechManager() {
	this->initspeech();
	this->createspeaker();
	//���������¼
	this->loadRecord();
}

void SpeechManager::show_meun()
{
	cout << "***************************************" << endl;
	cout << "***********��ӭ�μ��ݽ�����************" << endl;
	cout << "***********1.��ʼ�ݽ�����**************" << endl;
	cout << "***********2.�鿴�����¼**************" << endl;
	cout << "***********3.��ձ�����¼**************" << endl;
	cout << "***********0.�˳���������**************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initspeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_speaker.clear();
	this->m_Index = 1;
	this->m_Record.clear();
}

void SpeechManager::createspeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		Speaker sp;
		string name = "ѡ��";
		name += nameSeed[i];
		sp.m_name = name;
		for (int j = 0; j < 2; j++) sp.m_Score[j] = 0;
		this->v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startspeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechcontest();
	//3����ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_Index++;
	//1����ǩ
	this->speechDraw();
	//2������
	this->speechcontest();
	//3����ʾ���ս��
	this->showScore();
	//4������������ļ�
	this->saveRecord();

	//���ñ�������ȡ��¼
	this->initspeech();
	this->createspeaker();
	this->loadRecord();
	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "��<< " << this->m_Index << " >>�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------" << endl;
	cout << "��ǩ���˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else	//�ڶ��ֱ���
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechcontest()
{
	cout << "-----------��" << this->m_Index << "�ֱ�����ʽ��ʼ-----------" << endl;
	//׼����ʱ�������С��ɼ�
	multimap<double, int, greater<double>>groupScore;
	int num = 0;	//��¼��Ա������6��һ��
	vector<int> v_src;	//����ѡ������
	if (this->m_Index == 1) v_src = v1;
	else v_src = v2;

	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();	//ȥ�������ͷ�
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double aver = sum / (double)d.size();

		this->m_speaker[*it].m_Score[this->m_Index - 1] = aver;
		groupScore.insert(make_pair(aver, *it));
		//ÿ6��ȡǰ��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������:" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ� " << it->second << " ������ " << this->m_speaker[it->second].m_name << " �ɼ��� "<<this->m_speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}
			int count = 0; 
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++)
			{
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}

	}
	cout << "----------��" << this->m_Index << "�ֱ�����ϣ�------------" << endl;
	system("pause");

}

void SpeechManager::showScore()
{
	cout << "--------------��" << this->m_Index << "�ֽ���ѡ�����£�--------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) v = v2;
	else v = vVictory;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "��ţ� " << *it << " ������ " << this->m_speaker[*it].m_name << "�÷֣� " << this->m_speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_meun();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//׷��д
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty = 0;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//���ļ�
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������!" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);	//�������ȡ�ĵ����ַ��Ż���
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (1) {
			//data:1002.86.675,1009,81.3,1007,78.55,
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	/*for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout << it->first << "�ھ���ţ�" << it->second[0] << " ������" << it->second[1] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ��" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "��" << i + 1 << "�� " << "�ھ���ţ�" << this->m_Record[i][0] << " �÷֣� " << this->m_Record[i][1] << " " << "�Ǿ���ţ� " << this->m_Record[i][2] << " �÷֣� " << this->m_Record[i][3] << " " << "������ţ� " << this->m_Record[i][4] << " �÷֣� " << this->m_Record[i][5] << endl;
	}
	system("pause");
}

void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1.��" << endl;
	cout << "2.��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initspeech();
		this->createspeaker();
		this->loadRecord();
		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}