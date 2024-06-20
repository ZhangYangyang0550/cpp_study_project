#include".\include\push_box.h"

int g_AllMap[3][10][10]{ 
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,2,3,1,0,0,0,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,4,0,0,0,3,1 },
		{ 1,1,1,1,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,1 },
		{ 1,0,2,0,0,1,0,0,0,1 },
		{ 1,0,0,3,1,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,2,3,1,0,0,0,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,4,0,0,0,3,1 },
		{ 1,1,1,1,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,1 },
		{ 1,0,2,0,0,1,0,0,0,1 },
		{ 1,0,0,3,1,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	},
	{
		{ 1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,2,3,1,0,0,0,1 },
		{ 1,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,4,0,0,0,3,1 },
		{ 1,1,1,1,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,2,0,0,1 },
		{ 1,0,2,0,0,1,0,0,0,1 },
		{ 1,0,0,3,1,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1 },
	},
};//0����յأ�1����ǽ��2�������ӣ�3����Ŀ�ĵأ�4�����ˣ�5����������Ŀ�ĵ��ϣ�7��������Ŀ�ĵ���
int g_Push_Box_Map[10][10];//��ǰ�ĵ�ͼ
int g_Level = 0;//��Ϸ�ؿ�
int g_Theme = 1;//����������
int g_R, g_C; //�˵�������
bool g_WoL = true;//win or ose
std::unordered_map<int, int> g_NumsGetBox;//���ӵ��������
IMAGE wall, people, box, goal, blank, getbox, gamewin, gamelose, gameend, themeselection; //ͼ��

void PushBox::push_box_loading(int th) {
	//��ͼ���
	switch (th) {
	case 1: {
		loadimage(&wall, _T("..\\assets\\pushBoxͼ��\\wall.jpg"), 80, 80);
		loadimage(&people, _T("..\\assets\\pushBoxͼ��\\people1.png"), 80, 80);
		loadimage(&box, _T("..\\assets\\pushBoxͼ��\\box1.jpg"), 80, 80);
		loadimage(&goal, _T("..\\assets\\pushBoxͼ��\\goal1.jpg"), 80, 80);
		loadimage(&blank, _T("..\\assets\\pushBoxͼ��\\blank.jpg"), 80, 80);
		loadimage(&getbox, _T("..\\assets\\pushBoxͼ��\\getbox1.jpg"), 80, 80);
		loadimage(&gamewin, _T("..\\assets\\pushBoxͼ��\\gamewin1.png"), 800, 800);
		loadimage(&gamelose, _T("..\\assets\\pushBoxͼ��\\gamelose1.png"), 800, 800);
		loadimage(&gameend, _T("..\\assets\\pushBoxͼ��\\gameend.jpg"), 800, 800);
		loadimage(&themeselection, _T("..\\assets\\pushBoxͼ��\\themeselection.jpg"), 800, 800);
		break;
	}
	case 2: {
		loadimage(&wall, _T("..\\assets\\pushBoxͼ��\\wall.jpg"), 80, 80);
		loadimage(&people, _T("..\\assets\\pushBoxͼ��\\people2.png"), 80, 80);
		loadimage(&box, _T("..\\assets\\pushBoxͼ��\\box2.jpg"), 80, 80);
		loadimage(&goal, _T("..\\assets\\pushBoxͼ��\\goal2.jpg"), 80, 80);
		loadimage(&blank, _T("..\\assets\\pushBoxͼ��\\blank.jpg"), 80, 80);
		loadimage(&getbox, _T("..\\assets\\pushBoxͼ��\\getbox2.jpg"), 80, 80);
		loadimage(&gamewin, _T("..\\assets\\pushBoxͼ��\\gamewin2.png"), 800, 800);
		loadimage(&gamelose, _T("..\\assets\\pushBoxͼ��\\gamelose2.png"), 800, 800);
		loadimage(&gameend, _T("..\\assets\\pushBoxͼ��\\gameend.jpg"), 800, 800);
		loadimage(&themeselection, _T("..\\assets\\pushBoxͼ��\\themeselection.jpg"), 800, 800);
		break;
	}
	case 3: {
		loadimage(&wall, _T("..\\assets\\pushBoxͼ��\\wall.jpg"), 80, 80);
		loadimage(&people, _T("..\\assets\\pushBoxͼ��\\people3.png"), 80, 80);
		loadimage(&box, _T("..\\assets\\pushBoxͼ��\\box3.jpg"), 80, 80);
		loadimage(&goal, _T("..\\assets\\pushBoxͼ��\\goal3.jpg"), 80, 80);
		loadimage(&blank, _T("..\\assets\\pushBoxͼ��\\blank.jpg"), 80, 80);
		loadimage(&getbox, _T("..\\assets\\pushBoxͼ��\\getbox3.jpg"), 80, 80);
		loadimage(&gamewin, _T("..\\assets\\pushBoxͼ��\\gamewin3.png"), 800, 800);
		loadimage(&gamelose, _T("..\\assets\\pushBoxͼ��\\gamelose3.png"), 800, 800);
		loadimage(&gameend, _T("..\\assets\\pushBoxͼ��\\gameend.jpg"), 800, 800);
		loadimage(&themeselection, _T("..\\assets\\pushBoxͼ��\\themeselection.jpg"), 800, 800);
		break;
	}
	}
}
void PushBox::init_map() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			g_Push_Box_Map[i][j] = g_AllMap[g_Level][i][j];
		}
	}
}
void PushBox::theme_selection() {
	putimage(0, 0, &themeselection);
	while (1) {
		char key = _getch();
		switch (key) {
		case '1':
			g_Theme = 1;
			break;
		case '2':
			g_Theme = 2;
			break;
		case '3':
			g_Theme = 3;
			break;
		default:
			continue;
		}
		if (g_Theme != 0) {
			break;
		}
	}
}

void PushBox::show_icon() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			switch (g_Push_Box_Map[i][j]) {
			case 0:putimage(j * 80, i * 80, &blank); break;//�յ�
			case 1:putimage(j * 80, i * 80, &wall); break;//ǽ
			case 2:putimage(j * 80, i * 80, &box); break;//����
			case 3:putimage(j * 80, i * 80, &goal); break;//Ŀ�ĵ�
			case 4:putimage(j * 80, i * 80, &people); break;//��
			case 5:putimage(j * 80, i * 80, &getbox); break;//������Ŀ�ĵ���
			case 7:putimage(j * 80, i * 80, &people); break;//����Ŀ�ĵ���
			}
		}
	}
}
void PushBox::find_people() {
	bool is_find = false;
	//ʱ���ҵ��˵�λ��
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_Push_Box_Map[i][j] == 4 || g_Push_Box_Map[i][j] == 7) {
				g_R = i;
				g_C = j;
				is_find = true;
				break;
			}
		}
		if (is_find)break;
	}
}

bool PushBox::get_box() {
	int num = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_Push_Box_Map[i][j] == 5)num++;
		}
	}
	int a = g_NumsGetBox[num];
	g_NumsGetBox[num]++;
	int b = g_NumsGetBox[num];
	return (a == 0 && b == 1 && num != 0);
}
void PushBox::key() {
	//����
KEY:
	char key = _getch();
	int keyr, keyc;
	switch (key) {
	case 'w':keyr = -1, keyc = 0; break;
	case 's':keyr = 1, keyc = 0; break;
	case 'a':keyr = 0, keyc = -1; break;
	case 'd':keyr = 0, keyc = 1; break;
	case 'q':g_WoL = false; keyr = 0, keyc = 0; break;
	default:
		goto KEY;    //�쳣����
	}
	//������ƶ������ǿյػ�Ŀ�ĵ�
	if (g_Push_Box_Map[g_R + keyr][g_C + keyc] == 0 || g_Push_Box_Map[g_R + keyr][g_C + keyc] == 3) {
		g_Push_Box_Map[g_R + keyr][g_C + keyc] += 4;
		g_Push_Box_Map[g_R][g_C] -= 4;
	}
	//������ƶ�����������
	else if (g_Push_Box_Map[g_R + keyr][g_C + keyc] == 2 || g_Push_Box_Map[g_R + keyr][g_C + keyc] == 5) {
		//���ƶ�������ƶ������ǿյػ�Ŀ�ĵ�
		if (g_Push_Box_Map[g_R + 2 * keyr][g_C + 2 * keyc] == 0 || g_Push_Box_Map[g_R + 2 * keyr][g_C + 2 * keyc] == 3) {
			g_Push_Box_Map[g_R + 2 * keyr][g_C + 2 * keyc] += 2;
			g_Push_Box_Map[g_R + keyr][g_C + keyc] += 2;
			g_Push_Box_Map[g_R][g_C] -= 4;
		}

		//���ƶ�������ƶ����������ӻ�ǽ
	}
	//�����������ǽ
}
bool PushBox::game_win() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (g_Push_Box_Map[i][j] == 2)return false;
		}
	}
	return true;
}
void PushBox::game_play() {
	PushBox::push_box_loading(g_Theme);
	while (g_Level < 4) {
		if (!g_WoL) {
			g_WoL = true;
			Sleep(500);
			putimage(0, 0, &gamelose);
			break;
		}
		std::cout << " ��" << " " << g_Level + 1 << " " << "��" << std::endl;
		std::cout << "����ϷΪ��������Ϸ��Ƥ,�����Ҫ����w(��)s(��)a(��)d(��)  (��q������Ϸ)" << '\n';
		std::cout << "���ƶ�����Ե�ʳ��" << '\n';
		std::cout << "����Ϸ�زľ��������磬��ٰ���:-)" << '\n';
		//std::cout << "����ǧ���� ж�ذ�����ŷ��,лл��лл��" << '\n';
		init_map();
		show_icon();
		g_NumsGetBox.clear();
		while (1) {
			/*system("cls");
			for (int i = 0;i < 10;i++) {
				for (int j = 0;j < 10;j++) {
					cout << map[i][j] << " ";
				}
				cout << '\n';
			}*/
			find_people();
			key();
			show_icon();
			if (get_box()) {
				std::cout << "box has been taken" << std::endl;
			}
			if (game_win()) {
				show_icon();
				Sleep(2000);
				putimage(0, 0, &gamewin);
				Sleep(2000);
				g_Level++;//��¼�ؿ�
				system("cls");
				break;
			}
			else if (!g_WoL) {
				break;
			}
		}
		if (g_Level == 3) {
			g_Level = 0;//��ʼ��
			putimage(0, 0, &gameend);
			Sleep(2000);
			break;
		}
	}
	Sleep(2000);
	system("cls");
}
void PushBox::push_box() {
	initgraph(800, 800, SHOWCONSOLE);
	IMAGE menu;
	loadimage(&menu, _T("..\\assets\\pushBoxͼ��\\menu.jpg"), 800, 800);
	while (1) {
		putimage(0, 0, &menu);
		char key = _getch();
		//int keyr, keyc;
		bool exit = 0;
		switch (key) {
		case 'p':game_play(); break;
		case 'o':theme_selection(); break;
		case 'i':return; break;
		default:
			break;    //�쳣����
		}
	}
}
