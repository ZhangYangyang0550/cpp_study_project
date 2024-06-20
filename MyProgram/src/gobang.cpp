#include".\include\gobang.h"

//����������� û������ 0  ���� 1  ���� 2
enum Chess {
	none,
	black,
	white//����1 2 3 
};
std::vector<std::tuple<std::string, std::string, int>> g_Gamer_Data;
//�����ͼ����
int g_Gobang_Map[ROW][COL] = { 0 };
bool g_IsWin, g_IsFull = 0;
int g_B_Win, g_W_Win = 0;
std::string g_ID, g_Password;

struct Pos { //���λ�ýṹ��
	int row;
	int col;
	bool is_show;//�Ƿ���ʾ����
	int chess_play;//����
}g_Pos = { -1, -1, false, black };//��������

IMAGE background, gobangmenu, gobanglogin;//���ص�ͼ

void Gobang::gamer_data_read() {
	std::ifstream file(GOBANGFILE); // ���ı��ļ�
	g_Gamer_Data.clear(); // ���
	if (!file.is_open()) {
		std::cerr << "�޷����ļ�" << std::endl;
		return;
	}

	std::string line;
	std::tuple<std::string, std::string, int> current_tuple;

	int lineCount = 0;
	while (std::getline(file, line)) {
		if (lineCount == 0) {
			std::get<0>(current_tuple) = line;
		}
		else if (lineCount == 1) {
			std::get<1>(current_tuple) = line;
		}
		else {
			std::get<2>(current_tuple) = std::stoi(line);
			g_Gamer_Data.push_back(current_tuple); // ����ǰԪ��洢��������
		}

		lineCount = (lineCount + 1) % 3;
	}

	file.close(); // �ر��ļ�
}

void Gobang::gamer_data_write() {
	std::ofstream file(GOBANGFILE, std::ofstream::trunc);
	if (!file.is_open()) {
		std::cerr << "�޷�������ļ�" << std::endl;
		return;
	}

	for (const auto& data : g_Gamer_Data) {
		file << std::get<0>(data) << "\n"; // д��id������
		file << std::get<1>(data) << "\n"; // д��password������
		file << std::get<2>(data) << "\n"; // д��÷ֲ�����
	}

	file.close(); // �ر��ļ�
	return;
}

void Gobang::gobang_loading() {
	loadimage(&background, _T("..\\assets\\gobangͼ��\\background.jpg"), 840, 700);
	loadimage(&gobangmenu, _T("..\\assets\\gobangͼ��\\menu.jpg"), 840, 700);
	loadimage(&gobanglogin, _T("..\\assets\\gobangͼ��\\login.jpg"), 840, 700);
}

bool Gobang::judge_winner() {
	//��������
	//���򣺱�����
	// ���巽�����������  
	//˼·��������һ��
	std::vector<std::pair<int, int>> directions = {
		{0, 1}, {0, -1}, // ˮƽ����  
		{1, 0}, {-1, 0}, // ��ֱ����  
		{1, 1}, {-1, -1}, // �Խ��߷���1  
		{1, -1}, {-1, 1}  // �Խ��߷���2  
	};
	//��������Ƿ�����
	for (int x = 0; x < ROW; x++) {
		for (int y = 0; y < COL; y++) {
			g_IsFull = 1;
			if (g_Gobang_Map[x][y] == none) {
				g_IsFull = 0;
				break;
			}
		}
		if (!g_IsFull)break;
	}
	// ��ѭ��������п��ܵ�λ�úͷ���  
	for (int x = 0; x < ROW; x++) {
		for (int y = 0; y < COL; y++) {
			for (const auto& dir : directions) {
				int dx = dir.first, dy = dir.second;
				bool foundPattern = true;
				// ������������λ��  
				for (int i = 1; i <= 4; i++) {
					int nx = x + dx * i;
					int ny = y + dy * i;

					// ��������Ƿ������̷�Χ��  
					if (nx < 0 || nx >= 15 || ny < 0 || ny >= 15) {
						foundPattern = false;
						break;
					}
					// ���ֵ�Ƿ�ƥ�� 
					if (i == 1 && (g_Gobang_Map[nx][ny] != g_Pos.chess_play || g_Gobang_Map[x][y] != g_Pos.chess_play)) {
						foundPattern = false;
						break;
					}
					if (i > 1 && g_Gobang_Map[nx][ny] != g_Pos.chess_play) {
						foundPattern = false;
						break;
					}
				}
				if (foundPattern) {
					return true;  // ����ҵ����飬�򷵻�true  
				}
			}
		}
	}
	return false; // ���û���ҵ����飬�򷵻�false
}

void Gobang::mouse_move_message(ExMessage* msg) {//����ƶ�
	//�������������
	g_Pos.is_show = false;
	g_Pos.row = msg->y / LATTIC_LEN;
	g_Pos.col = msg->x / LATTIC_LEN;
	//����У׼
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			//��ȡÿ���������Ͻǵ�����
			int gridx = j * LATTIC_LEN + SPACE;
			int gridy = i * LATTIC_LEN + SPACE;
			//msg->y,msg->x У׼�жϣ��÷��������������Ľ���� abs()ȡ����ֵ
			if (abs(msg->x - gridx) < 20 && abs(msg->y - gridy) <= 20) {
				g_Pos.is_show = true;
				g_Pos.row = i;
				g_Pos.col = j;
			}
		}
	}
}

void Gobang::mouse_press_mseeage(ExMessage* msg) {//��갴��
	//�������������������
	if (msg->message == WM_LBUTTONDOWN && g_Gobang_Map[g_Pos.row][g_Pos.col] == 0 && g_Pos.is_show) {
		g_Gobang_Map[g_Pos.row][g_Pos.col] = g_Pos.chess_play;
		if (judge_winner()) {
			//�������ڽ���
			g_IsWin = judge_winner();
			if (g_Gobang_Map[g_Pos.row][g_Pos.col] == black) {
				setfillcolor(BLACK);
				solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
				//"const char *" ���͵�ʵ���� "LPCWSTR" ���͵��ββ�����
				MessageBox(GetHWnd(), _T("����Ӯ��"), _T("��Ϸ����nefu"), MB_OK);
				//exit(0);
			}
			else if (g_Gobang_Map[g_Pos.row][g_Pos.col] == white) {
				setfillcolor(WHITE);
				solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
				MessageBox(GetHWnd(), _T("����Ӯ��"), _T("��Ϸ����nefu"), MB_OK);
				//exit(0);
			}
		}
		//�л�����
		g_Pos.chess_play = (g_Pos.chess_play == black ? white : black);
	}
}

void Gobang::show_gobang() {
	putimage(0, 0, &background);
	//���������� 15*15
	setlinestyle(PS_SOLID, 1);//��ϸ
	setlinecolor(BLACK);//������ɫ
	for (int i = 0; i < 14; i++) {
		line(SPACE, i * LATTIC_LEN + SPACE, 20 * LATTIC_LEN - SPACE, i * LATTIC_LEN + SPACE);//���ƺ���
		line(i * LATTIC_LEN + SPACE, +SPACE, i * LATTIC_LEN + SPACE, 20 * LATTIC_LEN - SPACE);//��������
	}

	//���Ʊ߿�(�Ӵ֣�
	setlinestyle(PS_SOLID, 2);
	rectangle(SPACE, SPACE, SPACE + 14 * LATTIC_LEN, SPACE + 14 * LATTIC_LEN);
	//����
	setfillcolor(BLACK);//��ɫ
	solidcircle(SPACE + 7 * LATTIC_LEN, SPACE + 7 * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 - 4) * LATTIC_LEN, SPACE + (7 - 4) * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 - 4) * LATTIC_LEN, SPACE + (7 + 4) * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 + 4) * LATTIC_LEN, SPACE + (7 - 4) * LATTIC_LEN, 5);
	solidcircle(SPACE + (7 + 4) * LATTIC_LEN, SPACE + (7 + 4) * LATTIC_LEN, 5);

	//��������
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (g_Gobang_Map[i][j] == black) {//��
				setfillcolor(BLACK);
				solidcircle(j * LATTIC_LEN + SPACE, i * LATTIC_LEN + SPACE, 14);
			}
			else if (g_Gobang_Map[i][j] == white) {//��
				setfillcolor(WHITE);
				solidcircle(j * LATTIC_LEN + SPACE, i * LATTIC_LEN + SPACE, 14);
			}
			//��
		}
	}

	//��������ƶ�ʱ������
	setlinecolor(CYAN);
	if (g_Pos.is_show) {
		rectangle(g_Pos.col * LATTIC_LEN + SPACE - 12, g_Pos.row * LATTIC_LEN + SPACE - 12, g_Pos.col * LATTIC_LEN + SPACE + 12, g_Pos.row * LATTIC_LEN + SPACE + 12);
	}
}

int Gobang::evaluate_direction(int row, int col, int dirRow, int dirCol, int player) {
	static const int scores[] = { 0, 10, 30, 60, 90, 100 };  // �÷ֲ��ұ�
	int count = 0;
	// ��ǰ����
	int r = row, c = col;
	while (r >= 0 && r < ROW && c >= 0 && c < COL && g_Gobang_Map[r][c] == player) {
		if (++count >= 5) return scores[5];  // �������5�ӣ�����
		r += dirRow;
		c += dirCol;
	}
	// �������
	r = row - dirRow;
	c = col - dirCol;
	while (r >= 0 && r < ROW && c >= 0 && c < COL && g_Gobang_Map[r][c] == player) {
		if (++count >= 5) return scores[5];  // �������5�ӣ�����
		r -= dirRow;
		c -= dirCol;
	}
	return scores[count];  // ����������������÷�
}


int Gobang::evaluate_move(int row, int col, int player) {
	int score = 0;
	int opponent = (player == black) ? white : black;

	// ����ˮƽ��������
	score += evaluate_direction(row, col, 0, 1, player);
	// ���´�ֱ��������
	score += evaluate_direction(row, col, 1, 0, player);
	// �����¶Խ��߷�������
	score += evaluate_direction(row, col, 1, 1, player);
	// �����¶Խ��߷�������
	score += evaluate_direction(row, col, 1, -1, player);

	// ����ˮƽ������������
	score += evaluate_direction(row, col, 0, 1, opponent);
	// ���´�ֱ������������
	score += evaluate_direction(row, col, 1, 0, opponent);
	// �����¶Խ��߷�����������
	score += evaluate_direction(row, col, 1, 1, opponent);
	// �����¶Խ��߷�����������
	score += evaluate_direction(row, col, 1, -1, opponent);

	return score;
	//��һ����������Ҳ��Ϊ�����������˴�����ظ�����ԭ���ķ�����ȣ����Ӽ��

}

std::pair<int, int>Gobang::get_next_move() {
	int max_score = -1;
	std::pair<int, int> best_move = { -1, -1 };

	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (g_Gobang_Map[row][col] == none) {
				int score = evaluate_move(row, col, g_Pos.chess_play);
				if (score > max_score) {
					max_score = score;
					best_move = { row, col };
				}
			}
		}
	}
	if (max_score == 0) {
		int r0 = rand() % 15;
		int c0 = rand() % 15;
		if (g_Gobang_Map[r0][c0] == none)best_move = { r0, c0 };
	}

	return best_move;
}

void Gobang::robot() {
	std::pair<int, int> best = get_next_move();
	g_Pos.row = best.first;
	g_Pos.col = best.second;
	g_Gobang_Map[g_Pos.row][g_Pos.col] = g_Pos.chess_play;
	if (judge_winner()) {
		//�������ڽ���
		g_IsWin = judge_winner();
		if (g_Gobang_Map[g_Pos.row][g_Pos.col] == black) {
			g_B_Win++;
			setfillcolor(BLACK);
			solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
			//"const char *" ���͵�ʵ���� "LPCWSTR" ���͵��ββ�����
			MessageBox(GetHWnd(), _T("����Ӯ��"), _T("��Ϸ����nefu"), MB_OK);
		}
		else if (g_Gobang_Map[g_Pos.row][g_Pos.col] == white) {
			g_W_Win++;
			setfillcolor(WHITE);
			solidcircle(g_Pos.col * LATTIC_LEN + SPACE, g_Pos.row * LATTIC_LEN + SPACE, 14);
			MessageBox(GetHWnd(), _T("����Ӯ��"), _T("��Ϸ����nefu"), MB_OK);
		}
	}
	//�л�����
	g_Pos.chess_play = (g_Pos.chess_play == black ? white : black);
}

bool Gobang::compare_tuple(const std::tuple<std::string, std::string, int>& a, const std::tuple<std::string, std::string, int>& b) {
	return std::get<2>(a) < std::get<2>(b);
}

void Gobang::leader_board() {
	system("cls");
	std::sort(g_Gamer_Data.begin(), g_Gamer_Data.end(), compare_tuple);
	int count = 0;
	for (const auto& data : g_Gamer_Data) {
		if (std::get<2>(data) != 9999) {
			std::cout << "ID:" << std::get<0>(data) << "  " << "սʤ���������õĲ���:" << std::get<2>(data) << std::endl;
			count++;
		}
		if (count == 10) {
			break;
		}
	}

	return;
}

void Gobang::pvp() {
	initgraph(840, 700, SHOWCONSOLE);
	while (!g_IsWin && !g_IsFull) {
		BeginBatchDraw();
		show_gobang();
		EndBatchDraw();
		//����������Ϣ
		ExMessage msg;
		//��ȡ��Ϣ
		if (peekmessage(&msg, EM_MOUSE)) {//��ȡ�������
			switch (msg.message) {//��Ϣ����
			case WM_MOUSEMOVE://����ƶ���Ϣ
				mouse_move_message(&msg);
				break;
			case WM_LBUTTONDOWN://������Ҽ�����
				mouse_press_mseeage(&msg);
				break;
			default:
				break;
			}
		}
	}
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			g_Gobang_Map[i][j] = 0;
		}
	}
	g_IsWin = 0;
	g_IsFull = 0;
}
int Gobang::pvr() {
	int gamerscore = 0;
	initgraph(840, 700, SHOWCONSOLE);
	while (!g_IsWin && !g_IsFull) {
		BeginBatchDraw();
		show_gobang();
		EndBatchDraw();
		//����������Ϣ
		ExMessage msg;
		//��ȡ��Ϣ
		if (peekmessage(&msg, EM_MOUSE)) {//��ȡ�������
			switch (msg.message) {//��Ϣ����
			case WM_MOUSEMOVE://����ƶ���Ϣ
				mouse_move_message(&msg);
				break;
			case WM_LBUTTONDOWN: {//������Ҽ�����
				int pre_chees = g_Pos.chess_play;
				mouse_press_mseeage(&msg);
				if (pre_chees != g_Pos.chess_play)robot();
				
				gamerscore++;
				break;
			}
			default:
				break;
			}
		}
	}
	if (g_Gobang_Map[g_Pos.row][g_Pos.col] == black) {
		for (int i = 0; i < ROW; ++i) {
			for (int j = 0; j < COL; ++j) {
				g_Gobang_Map[i][j] = 0;
			}
		}
		g_IsWin = 0;
		g_IsFull = 0;
		return 9999;
	}
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COL; ++j) {
			g_Gobang_Map[i][j] = 0;
		}
	}
	g_IsWin = 0;
	g_IsFull = 0;
	return gamerscore;
}

void Gobang::rvr() {
	initgraph(840, 700, SHOWCONSOLE);
	for (int game_num = 0; game_num < 10; game_num++) {
		std::cout << "ģ���" << game_num + 1 << "��" << std::endl;
		std::cout << "����ʤ��" << g_B_Win << "��" << std::endl;
		std::cout << "����ʤ��" << g_W_Win << "��" << std::endl;
		while (!g_IsWin && !g_IsFull) {
			BeginBatchDraw();
			show_gobang();
			EndBatchDraw();
			robot();
			Sleep(10);
		}
		system("cls");
		for (int i = 0; i < ROW; ++i) {
			for (int j = 0; j < COL; ++j) {
				g_Gobang_Map[i][j] = 0;
			}
		}
		g_IsWin = 0;
		g_IsFull = 0;
	}
	std::cout << "ģ���10��" << std::endl;
	std::cout << "����ʤ��" << g_B_Win << "��" << std::endl;
	std::cout << "����ʤ��" << g_W_Win << "��" << std::endl;
	std::cout << "ģ�����,5����˳�" << std::endl;
	Sleep(5000);
	system("cls");
}

void Gobang::gobang() {
	gamer_data_read();
	initgraph(840, 700, SHOWCONSOLE);
	gobang_loading();
	putimage(0, 0, &gobanglogin);
	std::cout << "ID:";
	std::cin >> g_ID;
	std::cout << "password:";
	std::cin >> g_Password;
	std::cout << "�ɹ�����......";
	std::tuple<std::string, std::string, int> temp = { g_ID ,g_Password ,9999 };
	g_Gamer_Data.push_back(temp);
	Sleep(1000);
	system("cls");
	int PVRscore = 9999;
	while (1) {
		putimage(0, 0, &gobangmenu);
		char key = _getch();
		switch (key) {
		case 'p': {system("cls"); pvp(); break; }
		case 'o': {system("cls"); PVRscore = pvr(); break; }
		case 'i': {system("cls"); rvr();g_B_Win = 0;g_W_Win =0; break; }
		case 'y': {system("cls"); leader_board(); break; }
		case 'u': {system("cls"); gamer_data_write(); return; break; }
		default:
			break;    //�쳣����
		}
		for (auto& data : g_Gamer_Data) {
			if (std::get<0>(data) == g_ID) {
				if (PVRscore < std::get<2>(data)) {
					std::get<2>(data) = PVRscore; // ���µ�����ֵΪ PVRscore
				}
			}
		}
	}
}