#include"speechManager.h"
SpeechManager::SpeechManager() {
	this->initspeech();
	this->createspeaker();
	//加载往届记录
	this->loadRecord();
}

void SpeechManager::show_meun()
{
	cout << "***************************************" << endl;
	cout << "***********欢迎参加演讲比赛************" << endl;
	cout << "***********1.开始演讲比赛**************" << endl;
	cout << "***********2.查看往届记录**************" << endl;
	cout << "***********3.清空比赛记录**************" << endl;
	cout << "***********0.退出比赛程序**************" << endl;
	cout << "***************************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
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
		string name = "选手";
		name += nameSeed[i];
		sp.m_name = name;
		for (int j = 0; j < 2; j++) sp.m_Score[j] = 0;
		this->v1.push_back(i + 10001);
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::startspeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechcontest();
	//3、显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();
	//2、比赛
	this->speechcontest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数到文件
	this->saveRecord();

	//重置比赛，获取记录
	this->initspeech();
	this->createspeaker();
	this->loadRecord();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "第<< " << this->m_Index << " >>轮比赛选手正在抽签" << endl;
	cout << "-------------------------------------" << endl;
	cout << "抽签后的顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else	//第二轮比赛
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
	cout << "-----------第" << this->m_Index << "轮比赛正式开始-----------" << endl;
	//准备临时容器存放小组成绩
	multimap<double, int, greater<double>>groupScore;
	int num = 0;	//记录人员个数，6人一组
	vector<int> v_src;	//比赛选手容器
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
		d.pop_back();	//去掉最高最低分
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double aver = sum / (double)d.size();

		this->m_speaker[*it].m_Score[this->m_Index - 1] = aver;
		groupScore.insert(make_pair(aver, *it));
		//每6人取前三
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次:" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号： " << it->second << " 姓名： " << this->m_speaker[it->second].m_name << " 成绩： "<<this->m_speaker[it->second].m_Score[this->m_Index - 1] << endl;
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
	cout << "----------第" << this->m_Index << "轮比赛完毕！------------" << endl;
	system("pause");

}

void SpeechManager::showScore()
{
	cout << "--------------第" << this->m_Index << "轮晋级选手如下：--------------" << endl;
	vector<int> v;
	if (this->m_Index == 1) v = v2;
	else v = vVictory;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号： " << *it << " 姓名： " << this->m_speaker[*it].m_name << "得分： " << this->m_speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_meun();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//追加写
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty = 0;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);//读文件
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在!" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);	//将上面读取的单个字符放回来
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
		cout << it->first << "冠军编号：" << it->second[0] << " 分数：" << it->second[1] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件为空" << endl;
	}
	for (int i = 0; i < this->m_Record.size(); i++)
	{
		cout << "第" << i + 1 << "界 " << "冠军编号：" << this->m_Record[i][0] << " 得分： " << this->m_Record[i][1] << " " << "亚军编号： " << this->m_Record[i][2] << " 得分： " << this->m_Record[i][3] << " " << "季军编号： " << this->m_Record[i][4] << " 得分： " << this->m_Record[i][5] << endl;
	}
	system("pause");
}

void SpeechManager::clearRecord()
{
	cout << "是否确定清空文件？" << endl;
	cout << "1.是" << endl;
	cout << "2.否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initspeech();
		this->createspeaker();
		this->loadRecord();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}