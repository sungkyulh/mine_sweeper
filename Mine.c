#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>


int key_input(); //Ű���� �Է�  ��1,��2,��3,��4,Ű1 5,Ű2 6,Ű3 7,F2 8,esc 9��ȯ
void gotoxy(int x, int y); // Ŀ�� ��ġ ����
void print_gotoxy(int x, int y, char *s1); // Ŀ�� ��ġ ������ ���� ���
void main_screen(); // ���� ȭ�� ���� 0, �ɼ� 1, ���� 3 ��ȯ 
void **create_mine(int xx,int yy); // ���� �迭
void **create_show_mine();//���� ��Ȳ 10:�� 0:�������� 1:�������� 2:��� 3:����ǥ
void open_mine(int **mine_stete,int **show_mine,int oxx,int oyy, int key_input);//ĭ ����
void game_over(int over);//���ӿ���&Ŭ����
void move(int keyinput);//�� ������ Ŀ�� �̵�
void game_play();//���� �÷���
void key(); // ������ Ű�Է¿� ���� ����
void open_group(int oxx,int oyy); // �������� ����
void free_mine();// ����� ����
void game_option();//�ɼ�
void change_difficult(int d_state);//���̵� ����
void print_difficult(int px,int py);//���̵� ���
void load_key(); //key setting ���� �ҷ��� �Ҵ�
void print_key(int px, int py);//���� Ű ��Ȳ ���
void ranking_save(int PorS, int diff);



char key1 = '+', key2 = '+', key3 = '+', key_up='+', key_down='+', key_right='+', key_left='+';
int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;
int re_up = 1, re_left = 2, re_down = 3, re_right = 4;
int x = 0, y = 0; //��ǥ��
int xx = 0, yy = 0;//�� �� ��ǥ
int sx=0, sy=1;//������ ��� �⺻ ��ġ
int keyinput = 0;
int size_x = 16, size_y = 16, num_mine = 40,num_mine1;//num1�� Ŭ���� ���� �Ǵܿ�
int openmine = 0;
int time_state = 0;
int flag_count = 0;
int **mine_state;
int **show_mine;
char s1[7][6]; // Ű ���� �ҷ��� �Ҵ��
CONSOLE_CURSOR_INFO cursorInfo = { 0, };


int main()
{
	system("title ����ã��"); //�����ٿ� �̸� ǥ��
	system("color 8F"); //ȸ����濡 ���� ��� �۾�
	srand(time(NULL)); //���� ������ ���̺� ����
	cursorInfo.dwSize = 100; // Ŀ�� ������ �ƽ�
	cursorInfo.bVisible = FALSE; // Ŀ�� ������ �ʵ���
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//Ŀ�� ����

	load_key();
	main_screen(); // ����ȭ�� �ҷ���

	system("pause");
	return 0;
}

int key_input() //��1,��2,��3,��4,Ű1 5,Ű2 6,Ű3 7,F2 8,esc 9, F5 10��ȯ
{
	char c;

	c = _getch();

	if (c == -32) //����Ű�� ���� 2��
	{
		c = _getch();
		if (c == LEFT) return re_left;
		else if (c == UP) return re_up;
		else if (c == RIGHT) return re_right;
		else if (c == DOWN) return re_down;
	}
	else if (c == 0)
	{
		c = _getch();
		if(c==60) return 8; // F2
		else if (c == 63) return 10; //F5
	}
	else if (c == key1) return 5;
	else if (c == key2) return 6;
	else if (c == key3) return 7;
	else if (c == 27) return 9; //esc
	else if (c == key_up) return 1;
	else if (c == key_down) return 3;
	else if (c == key_left) return 2;
	else if (c == key_right) return 4;
	

}

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void print_gotoxy(int x, int y,char *s1)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	printf("%s", s1);
}

void main_screen()
{
	system("cls");
	print_gotoxy(0, 0, "�������������������������������������������\n�ᢼ�颼�硡�������碼���碼�ꢼ�衡�����袼���ꢼ�颼�袼���颼�硡���碼��袼��\n�ᢼ���������颼������������ꢼ���ꢼ���ꢼ�����������\n�����뢼���ᢼ��ꢼ������袼��碼���ꢼ�����袼��颼���������\n���ᢼ�ᢼ�ᢼ��颼����������������ꢼ��������ꢼ����颼���\n���ᢼ��ᢼ������碼���袼�颼����뢼���������ꢼ��ꢼ�뢼���\n�ᢼ�����ꢼ��袼���������颼�����ᢼ���顡����袼�������뢼���\n����碼��袼�ᢼ���颼������ꢼ���������ᢼ��������颼����\n�ᢼ�����������ꢼ��ᢼ�袼���������ꢼ��ꢼ����袼���뢼��\n���ᢼ��碼��ᢼ��袼�������颼���ᢼ�颼��ᢼ��颼��ꢼ����碼����\n�����������碼�������颼�������뢼��������ᢼ����������\n������碼������������ᢼ���颼�ᢼ�颼�좼���硡��������ᡡ��\n��袼�����颼���颼�袼�����袼��颼����袼�颼���硡�����袼�����硡����\n�������������������������������������������\n");
	int sx1=39,sy1=17,sy2=2; // ȭ�� ����ҋ� ������ġ�� ����
	int state = 0;
	system("color 8F");
	cursorInfo.bVisible = FALSE; // Ŀ�� �����
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	print_key(0, 24);
	print_difficult(47, 24); 

	x = sx1, y = sy1; //�޴� ���
	print_gotoxy(x, y,"������");
	y = sy1+sy2;
	print_gotoxy(x, y, "���ɼ�");
	y = sy1+(sy2*2);
	print_gotoxy(x, y, "������");
	y = sy1;
	

	while (1) // Ŀ�� �̵��� ���ý� ����
	{
		
		keyinput = key_input();

		if (keyinput == 1)
		{
			if (state != 0) state--;
		}

		else if (keyinput == 3)
		{
			if (state != 2) state++;
		}

		else if (keyinput == 5)
		{
			if (state == 0)
			{
				game_play();
			}

			else if (state == 1)
			{
				game_option();
			}

			else if (state == 2)
			{
				system("cls");
				exit(0);
			}
		}

		gotoxy(x, y);


		print_gotoxy(x, y, "��");
		x = sx1, y = sy1+(sy2*state);
		print_gotoxy(x, y, "��");
		
	}
}

void **create_mine(int xx,int yy)
{
	int cnum_mine; //���� ������ ���� �ӽ� ����
	int xxx = 0, yyy = 0;

	cnum_mine = num_mine;

	int **mine_state1 = malloc(sizeof(int *)*(size_y+2));//2���� ���� �迭

	for (int i = 0; i < (size_y+2); i++)
	{
		mine_state1[i] = calloc((size_x+2),sizeof(int));
	}

	for (int i = 0; i < size_x + 2; i++) //�� �迭
	{
		mine_state1[0][i] = 10;
		mine_state1[size_y + 1][i] = 10;
	}

	for (int i = 1; i < size_y + 2; i++) //�� �迭
	{
		mine_state1[i][0] = 10;
		mine_state1[i][size_x + 1] = 10;
	}

	while(cnum_mine>0) // �ߺ����� ���� ��ġ
	{
		xxx = (rand() % size_x)+1;
		yyy = (rand() % size_y)+1;
		if (xxx == xx&&yyy == yy) continue;
		if (mine_state1[yyy][xxx] == 0)
		{
			mine_state1[yyy][xxx] = 9;
			cnum_mine--;
		}
	}


	for (int i = 1; i < size_y+1; i++) //���ڼ��� ���� ���� �迭
	{
		for (int j = 1; j < size_x+1; j++)
		{
			int count = 0;

			if (mine_state1[i][j] == 0)
			{
				if (mine_state1[i-1][j-1] == 9) count++;
				if (mine_state1[i-1][j] == 9) count++;
				if (mine_state1[i-1][j+1] == 9) count++;
				if (mine_state1[i][j-1] == 9) count++;
				if (mine_state1[i][j+1] == 9) count++;
				if (mine_state1[i+1][j-1] == 9) count++;
				if (mine_state1[i+1][j] == 9) count++;
				if (mine_state1[i+1][j+1] == 9) count++;

				mine_state1[i][j] = count;
			}
			
		}
	}

	return mine_state1;

}

void **create_show_mine()
{

	int **show_state = malloc(sizeof(int *)*(size_y + 2));//2���� ���� �迭

	for (int i = 0; i < (size_y + 2); i++)
	{
		show_state[i] = calloc((size_x + 2), sizeof(int));
	}

	for (int i = 0; i < size_x + 2; i++) //�� �迭
	{
		show_state[0][i] = 10;
		show_state[size_y + 1][i] = 10;
	}

	for (int i = 1; i < size_y + 2; i++) //�� �迭
	{
		show_state[i][0] = 10;
		show_state[i][size_x + 1] = 10;
	}

	return show_state;

}

void open_mine(int **mine_state, int **show_mine, int oxx, int oyy, int key_input) // 5 6 7
{
	if (key_input == 5)//Ű1�Է½�
	{
		if (show_mine[oyy][oxx] == 0)//���� �ȿ��������
		{
			show_mine[oyy][oxx] = 1;//���� ���·� ����
			openmine--;
			switch (mine_state[oyy][oxx])
			{
			case 0: //��ĭ�ϰ�� �ֺ�ĭ ����
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x87);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				for (int i = oyy - 1; i < oyy + 2; i++)
				{
					for (int j = oxx - 1; j < oxx + 2; j++)
					{
						if (i == oyy&&j == oxx) continue;
						open_mine(mine_state, show_mine, j, i , 5);
					}
				}
				break;
			case 1: // �� �����ϰ�� ���� ���
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x81);
				print_gotoxy((oxx * 2) + sx, (oyy) + sy, "��");
				open_group(oxx, oyy);
				break;
			case 2:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x82);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 3:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x84);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 4:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 5:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x85);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 6:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x83);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 7:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 8:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "��");
				open_group(oxx, oyy);
				break;
			case 9: //�����Ͻ� ���ӿ���
				game_over(0);
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
			gotoxy((oxx * 2) + sx, oyy + sy);
		}
		else if (show_mine[oyy][oxx] == 2 || show_mine[oyy][oxx] == 3)//����̳� ����ǥ�� Ŭ���� ���ڿ��� �Ǵ�
		{
			show_mine[oyy][oxx] = 0;
			open_mine(mine_state, show_mine, oxx, oyy, 5);
		}
	}

	else if (key_input == 6)//Ű2�Է½�
	{
		if (show_mine[oyy][oxx] == 0)//��ĭ�̸� ��߷�
		{
			show_mine[oyy][oxx] = 2;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
			print_gotoxy((oxx * 2) + sx, (oyy) + sy, "��");
			if (mine_state[oyy][oxx] == 9)
			{
				num_mine1--;
			}
			flag_count++;
			if (num_mine - flag_count >= 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				gotoxy(sx, sy - 1);
				printf("%3d", num_mine - flag_count);
			}
			gotoxy((oxx * 2) + sx, (oyy)+sy);
		}
		else if (show_mine[oyy][oxx] == 2)//����̸� ?��
		{
			show_mine[oyy][oxx] = 3;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
			print_gotoxy((oxx * 2) + sx, (oyy) + sy, "?");
			if (mine_state[oyy][oxx] == 9)
			{
				num_mine1++;
			}
			flag_count--;
			if (num_mine - flag_count >= 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				gotoxy(sx, sy - 1);
				printf("%3d", num_mine - flag_count);
			}
			gotoxy((oxx * 2) + sx, (oyy)+sy);
		}
		else if (show_mine[oyy][oxx] == 3)//?�� ��ĭ����
		{
			show_mine[oyy][oxx] = 0;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
			print_gotoxy((oxx * 2) + sx, (oyy) + sy, "��");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
		}
		gotoxy((oxx * 2) + sx, oyy + sy);
	}

	else if (key_input == 7)//Ű3�Է½�
	{
		if (show_mine[oyy][oxx] == 1)//���µ� ��Ȳ�ϰ��
		{
			int count = 0; //�ֺ� 8��ĭ ��߼� ��ȸ
			if (show_mine[oyy - 1][oxx - 1] == 2) count++;
			if (show_mine[oyy - 1][oxx] == 2) count++;
			if (show_mine[oyy - 1][oxx + 1] == 2) count++;
			if (show_mine[oyy][oxx - 1] == 2) count++;
			if (show_mine[oyy][oxx + 1] == 2) count++;
			if (show_mine[oyy + 1][oxx - 1] == 2) count++;
			if (show_mine[oyy + 1][oxx] == 2) count++;
			if (show_mine[oyy + 1][oxx + 1] == 2) count++;

			if (count == mine_state[oyy][oxx])//��߼��� ���ڶ� �������
			{
				for (int i = oyy - 1; i < oyy + 2; i++)
				{
					for (int j = oxx - 1; j < oxx + 2; j++)
					{
						if (i == oyy&&j == oxx) continue;
						if (show_mine[i][j] == 0 || show_mine[i][j] == 3)//���� ���³� ?ǥ��� ����
						{
							open_mine(mine_state, show_mine, j, i, 5);
						}
						else if (show_mine[i][j] == 2) // ����ϰ��
						{
							if (mine_state[i][j] != 9) //����ε� ���ڰ��ƴҰ�� ����
							{
								open_mine(mine_state, show_mine, j, i, 5);
							}
							else continue; // �����Ͻ� �н�
						}

					}
				}
				gotoxy((oxx * 2) + sx, oyy + sy);
			}
			else // Ȯ��Ű ���� �ֺ�ĭ ������
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
				cursorInfo.bVisible = FALSE;
				SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
				for (int i = oyy - 1; i < oyy + 2; i++)
				{
					for (int j = oxx - 1; j < oxx + 2; j++)
					{
						if(i == oyy&&j == oxx) continue;
						if (show_mine[i][j] == 0)
						{
							print_gotoxy((j * 2) + sx, (i)+sy, "��");
							
						}
					}
				}
				Sleep(50);
				
				for (int i = oyy - 1; i < oyy + 2; i++)
				{
					for (int j = oxx - 1; j < oxx + 2; j++)
					{
						if (i == oyy&&j == oxx) continue;
						if (show_mine[i][j] == 0)
						{
							print_gotoxy((j * 2) + sx, (i)+sy, "��");
						}
					}
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
				gotoxy((oxx*2)+sx, oyy+sy);
				cursorInfo.bVisible = TRUE;
				SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			}
		}
	}

}

void game_over(int over)
{
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	if (over == 1)//Ŭ����
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8E);
		for (int i = 1; i < size_y + 1; i++)
		{
			for (int j = 1; j < size_x + 1; j++)
			{
				if (mine_state[i][j] == 9)
				{
					print_gotoxy((j * 2) + sx, (i)+sy, "��");
				}
			}
			Sleep(150);
			
		}

		if (size_x == 9 && size_y == 9 && num_mine == 10)
		{
			ranking_save(1, 1);
		}
		else if (size_x == 16 && size_y == 16 && num_mine == 40)
		{
			ranking_save(1, 2);
		}
		else if (size_x == 30 && size_y == 16 && num_mine == 99)
		{
			ranking_save(1, 3);
		}
		free_mine();
		system("cls");
		main_screen();
	}
	else if (over == 0)//���ӿ���
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
		for (int i = 1; i < size_y + 1; i++)
		{
			for (int j = 1; j < size_x + 1; j++)
			{
				if (show_mine[i][j] == 2 && mine_state[i][j] == 9);
				else if (mine_state[i][j] == 9)
				{
					print_gotoxy((j * 2) + sx, (i)+sy, "��");
				}
				else if (show_mine[i][j] == 2 && mine_state[i][j] != 9)
				{
					print_gotoxy((j * 2) + sx, (i)+sy, "X");
				}
			}
		}
		key_input();
		free_mine();
		system("cls");
		main_screen();
	}
}

void move(int keyinput)//�����ǿ����� Ŀ�� �̵�
{
	 
	if (keyinput == 1)
	{
		if (yy != 1)
		{
			gotoxy((2 * xx) + sx, yy + sy - 1);
			yy--;
		}
	}
	else if (keyinput == 2)
	{
		if (xx != 1)
		{
			gotoxy((2 * xx) + sx - 2, yy + sy);
			xx--;
		}
	}
	else if (keyinput == 3)
	{
		if (yy != size_y)
		{
			gotoxy((2 * xx) + sx, yy + sy + 1);
			yy++;
		}
	}
	else if (keyinput == 4)
	{
		if (xx != size_x)
		{
			gotoxy((2 * xx) + sx + 2, yy + sy);
			xx++;
		}
	}
	else if (keyinput == 9)
	{
		main_screen();
	}
	else if (keyinput == 10)
	{
		change_difficult(1);
	}
	
}

void key()
{
	keyinput = key_input();
	switch (keyinput)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		move(keyinput);
		break;
	case 5:
	case 6:
	case 7:
		open_mine(mine_state, show_mine, xx, yy, keyinput);
		break;
	case 8: //����ŸƮ
		system("cls");
		game_play();
		break;
	case 9://����
		system("cls");
		free_mine();
		main_screen();
		break;
	case 10:
		free_mine();
		change_difficult(1);
		break;
	default:
		break;
	}
}

void free_mine()
{
	for (int i = 0; i < size_y + 2; i++) // ���� (������)
	{
		free(mine_state[i]);
	}

	free(mine_state);

	for (int i = 0; i < size_y + 2; i++) // ���� (������ ���� ����)
	{
		free(show_mine[i]);
	}

	free(show_mine);
}

void open_group(int oxx,int oyy) // �����µ� �ֺ��� ��ĭ�������� �����̷� ����
{
	for (int k = oyy - 1; k < oyy + 2; k++)
	{
		for (int h = oxx - 1; h < oxx+2; h++)
		{
			if (k == oyy&&h == oxx) continue;
			if (mine_state[k][h] == 0)
			{
				open_mine(mine_state, show_mine, h, k, 5);
			}
		}
	}

}

void game_play()
{
	system("cls");
	system("color 8F");
	openmine = size_x*size_y;
	flag_count = 0;
	num_mine1 = num_mine;
	gotoxy(sx, sy - 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
	printf("%3d", num_mine);
	gotoxy(sx + (size_x * 2), sy - 1);
	printf("  0");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
	gotoxy(sx, sy);
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	for (int i = 0; i < size_y + 2; i++) // Ʋ ���
	{
		for (int j = 0; j < size_x + 2; j++)
		{
			if (i == 0 || i == size_y + 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				printf("��");
			}
			else
			{
				if (j == 0 || j == size_x + 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
					printf("��");
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
					printf("��");
				}
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
	print_difficult(0,sy+size_y+2);
	xx = (size_x+1)/2; //���۽� Ŀ���� �߾����� ��ġ
	yy = (size_y+1)/2;
	gotoxy((xx * 2) + sx, (yy) + sy);
	int mine_maked = 0;
	time_t start_t, state_t;
	time_state = 0;
	double t_diff;

	while (1)
	{
		if (mine_maked == 0) //ù �Է��Ͻ� ������ ����
		{
			keyinput = key_input();
			if (keyinput == 5)
			{
				mine_state = create_mine(xx,yy);
				show_mine = create_show_mine();
				mine_maked = 1;
				start_t = time(NULL);
				open_mine(mine_state, show_mine, xx, yy, keyinput);
			}
			else
			{
				move(keyinput);
			}
		}
		else
		{
			if (openmine == num_mine) //Ŭ���� ����
			{
				game_over(1);
			}
			else
			{
				if (_kbhit())
				{
					key();
				}
				state_t = time(NULL);
				t_diff = difftime(state_t, start_t);
				if (t_diff >= (1 + time_state)) //Ÿ�̸�
				{
					time_state++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
					gotoxy(sx + (size_x * 2), sy - 1);
					printf("%3d", time_state);
					gotoxy((2 * xx) + sx, yy + sy);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
					
				}
			}
		}
		Sleep(25);
	}
}

void game_option()
{
	system("cls");
	int sx1 = 39, sy1 = 7, sy2 = 6;
	int state = 0;
	system("color 8F");

	x = sx1, y = sy1;
	print_gotoxy(x, y, "�����̵�");
	y = sy1+sy2;
	print_gotoxy(x, y, "����ŷ");
	y = sy1+(sy2*2);
	print_gotoxy(x, y, "�����ư���");
	y = sy1;


	while (1)
	{

		keyinput = key_input();

		if (keyinput == 1)
		{
			if (state != 0) state--;
		}

		else if (keyinput == 3)
		{
			if (state != 2) state++;
		}

		else if (keyinput == 5)
		{
			if (state == 0)
			{
				system("cls");
				change_difficult(0);
			}

			else if (state == 1)
			{
				ranking_save(0,0);
			}

			else if (state == 2)
			{
				system("cls");
				main_screen();
			}
		}

		gotoxy(x, y);

		
		print_gotoxy(x, y, "��");
		x = sx1, y = sy1+(sy2*state);
		print_gotoxy(x, y, "��");
		
	}
}

void change_difficult(int d_state)
{
	int sx1 = 39, sy1 = 7, sy2 = 4;
	int state = 0;
	system("cls");
	system("color 8F");
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	print_difficult(sx1, 3);
		
	x = sx1, y = sy1;
	print_gotoxy(x, y, "���ʱ� ( 9 X 9 , 10 )");
	y = sy1+sy2;
	print_gotoxy(x, y, "���߱� ( 16 X 16 , 40 )");
	y = sy1+(sy2*2);
	print_gotoxy(x, y, "����� ( 30 X 16 , 99 )");
	y = sy1 + (sy2 * 3);
	print_gotoxy(x, y, "������� ����");
	y = sy1 + (sy2 * 4);
	print_gotoxy(x, y, "�����ư���");
	y = sy1;


	while (1)
	{

		keyinput = key_input();

		if (keyinput == 1)
		{
			if (state != 0) state--;
		}

		else if (keyinput == 3)
		{
			if (state != 4) state++;
		}

		else if (keyinput == 5)
		{
			if (state == 0)
			{
				size_x = 9;
				size_y = 9;
				num_mine = 10;
				if (d_state == 0) game_option(); // �޴����� ������ �޴��� ���ư�
				else if (d_state == 1) game_play(); // �����߿� ������ �ٽ� �ٷ� ���� ����
			}

			else if (state == 1)
			{
				size_x = 16;
				size_y = 16;
				num_mine = 40;
				if (d_state == 0) game_option(); // �޴����� ������ �޴��� ���ư�
				else if (d_state == 1) game_play(); // �����߿� ������ �ٽ� �ٷ� ���� ����
			}

			else if (state == 2)
			{
				size_x = 30;
				size_y = 16;
				num_mine = 99;
				if (d_state == 0) game_option(); // �޴����� ������ �޴��� ���ư�
				else if (d_state == 1) game_play(); // �����߿� ������ �ٽ� �ٷ� ���� ����
			}

			else if (state == 3)
			{
				while (1)
				{
					y = sy1 + (sy2 * 3) + 1;
					print_gotoxy(x, y, "����,����,���ڼ��� �����̽� �ٷ� �����ؼ� �Է��� ����");
					gotoxy(x, y + 1);
					scanf("%d %d %d", &size_x, &size_y, &num_mine);
					y = sy1 + (sy2 * 3);

					if(size_x<1||size_y<1||num_mine<1)
					{
						gotoxy(x, y + 2);
						printf("���� ũ�⳪ ������ ���� ����� �����մϴ�");
						Sleep(1000);
						gotoxy(x, y + 2);
						printf("                                           ");
					}
					else
					{
						if (size_x*size_y - 1 > num_mine) break;
						else
						{
							gotoxy(x, y + 2);
							printf("���ڼ��� ĭ������ ũ�� �ȵ˴ϴ�");
							Sleep(1000);
							gotoxy(x, y + 2);
							printf("                               ");
						}
					}
				}
				if (d_state == 0) game_option(); // �޴����� ������ �޴��� ���ư�
				else if (d_state == 1) game_play(); // �����߿� ������ �ٽ� �ٷ� ���� ����
			}

			else if (state == 4)
			{
				if (d_state == 0) game_option(); // �޴����� ������ �޴��� ���ư�
				else if (d_state == 1) game_play(); // �����߿� ������ �ٽ� �ٷ� ���� ����
			}

			
		}

		gotoxy(x, y);

		
		print_gotoxy(x, y, "��");
		x = sx1, y = sy1+(sy2*state);
		print_gotoxy(x, y, "��");
		
	}
}

void print_difficult(int px,int py)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
	gotoxy(px, py);
	printf("���� ���̵� : ");
	if (size_x == 9 && size_y == 9 && num_mine == 10)
	{
		printf("�ʱ� ( 9 X 9 , 10 )");
	}
	else if (size_x == 16 && size_y == 16 && num_mine == 40)
	{
		printf("�߱� ( 16 X 16 , 40 )");
	}
	else if (size_x == 30 && size_y == 16 && num_mine == 99)
	{
		printf("��� ( 30 X 16 , 99 )");
	}
	else
	{
		printf("����� ���� ( %d X %d , %d )", size_x, size_y, num_mine);
	}
}

void load_key()
{
	char s2[7]; // ���� �Ҵ��;


	FILE *KS = fopen("key setting.txt", "r"); // Ű���� ���� �о��

	if (KS != NULL) //������
	{
		fscanf(KS, "%s %s %s %s %s %s %s", s1[0], s1[1], s1[2], s1[3], s1[4], s1[5], s1[6]);

		fclose(KS);
	}
	else //�о���� ���н�
	{
		system("cls");
		system("color 8F"); //ȸ����濡 ���� ��� �۾�

		printf("key setting ������ ã�µ� �����Ͽ����ϴ�\n\nkey setting ������ �����ϰ� ������� 'z' Ű�� �Է��� �ּ���.\n���Ḧ ���Ͻǰ�� �ƹ�Ű�� �����ּ���\n");

		char c;

		c = _getch();

		if (c == 'z')
		{
			FILE *KS = fopen("key setting.txt", "w");

			fprintf(KS, "up left down right z x c\n\n�� �� �� �� Ű1 Ű2 Ű3 ������ �� ���ٿ� ���⸦ �������� �Է����ּ���\n�� Ű�� �˹ٺ�Ű�� �Ҵ��ϰ� ������ �ش���ġ�� ���ĺ��� ����Ű�� �Ҵ��ϰ�\n������� up, down, left, right�� �����ֽø� �˴ϴ�.\n\nex) ����Ű�� �����ϰ� Ű 1, 2, 3�� z x c�� �����ϰ���� ���\nup left down right z x c\n\nex2) wasd�� �����ϰ� ����Ű �Ʒ� 3���� Ű1, 2, 3�� �����ϰ� �������\nw a s d left down right");

			fclose(KS);

			printf("���� �Ϸ�\n");
		
		}
		exit(0);
	}

	for (int i = 0; i < 7; i++)
	{
		if (strcmp(s1[i], "up") == 0)
		{
			s2[i] = '1';
		}
		else if (strcmp(s1[i], "down") == 0)
		{
			s2[i] = '3';
		}
		else if (strcmp(s1[i], "left") == 0)
		{
			s2[i] = '2';
		}
		else if (strcmp(s1[i], "right") == 0)
		{
			s2[i] = '4';
		}
		else
		{
			s2[i] = s1[i][0];
		}
	}

	for (int i = 0; i < 7; i++)
	{
		if (s2[i] == '1' || s2[i] == '2' || s2[i] == '3' || s2[i] == '4')
		{
			switch (s2[i])
			{
			case '1':
				re_up = i + 1;
				break;
			case '2':
				re_left = i + 1;
				break;
			case '3':
				re_down = i + 1;
				break;
			case '4':
				re_right = i + 1;
				break;
			}
		}
		else
		{
			switch (i)
			{
			case 0:
				key_up = s2[i];
				break;
			case 1:
				key_left = s2[i];
				break;
			case 2:
				key_down = s2[i];
				break;
			case 3:
				key_right = s2[i];
				break;
			case 4:
				key1 = s2[i];
				break;
			case 5:
				key2 = s2[i];
				break;
			case 6:
				key3 = s2[i];
				break;
			}
		}
	}


}

void print_key(int px, int py)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
	gotoxy(px, py);
	
	printf("���� Ű:");
	for (int i = 0; i < 7; i++)
	{
		printf("%s ", s1[i]);
	}
}

void ranking_save(int PorS,int diff)//0 ��� 1 ����
{
	typedef struct {
		int time;
		char name[11];
	} ranking;

	ranking eazy[5];
	ranking nomal[5];
	ranking hard[5];


	FILE *SAVE = fopen("save.txt", "rt");
	if (SAVE != NULL) //������
	{
		for (int i = 0; i < 15; i++)
		{
			if (i >= 0 && i <= 4)
			{
				fscanf(SAVE, "%d %s\n", &eazy[i].time, &eazy[i].name);
			}
			else if (i >= 5 && i <= 9)
			{
				fscanf(SAVE, "%d %s\n", &nomal[i - 5].time, &nomal[i - 5].name);
			}
			else if (i >= 10 && i <= 14)
			{
				fscanf(SAVE, "%d %s\n", &hard[i - 10].time, &hard[i - 10].name);
			}
		}
		fclose(SAVE);

		if (PorS == 0)
		{
			system("cls");
			system("color 8F"); //ȸ����濡 ���� ��� �۾�

			print_gotoxy(17, 4, "�ʱ�");
			print_gotoxy(35, 4, "�߱�");
			print_gotoxy(53, 4, "���");

			print_gotoxy(15, 6, "�ð� �̸�");
			print_gotoxy(33, 6, "�ð� �̸�");
			print_gotoxy(51, 6, "�ð� �̸�");

			for (int i = 0; i < 5; i++)
			{
				gotoxy(15, 8 + (i * 2));
				printf("%3d  %s", eazy[i].time, eazy[i].name);
			}

			for (int i = 0; i < 5; i++)
			{
				gotoxy(33, 8 + (i * 2));
				printf("%3d  %s", nomal[i].time, nomal[i].name);
			}

			for (int i = 0; i < 5; i++)
			{
				gotoxy(51, 8 + (i * 2));
				printf("%3d  %s", hard[i].time, hard[i].name);
			}

			print_gotoxy(39, 20, "�����ư���");
			int a;
			a = key_input();
			while (a != 5)
			{
				a = key_input();
			}

			game_option();
		}
		else
		{
			ranking now[7];
			now[5].time = time_state;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
			print_gotoxy(0, 21,"�̸��� �Է��� �ּ���:");
			scanf("%s", &now[5].name);
			now[5].name[10] = NULL;

			if (diff == 1) // �ʱ�
			{
				for (int i = 0; i < 5; i++)
				{
					now[i] = eazy[i];
				}
			}
			else if (diff == 2) //�߱�
			{
				for (int i = 0; i < 5; i++)
				{
					now[i] = nomal[i];
				}
			}
			else if (diff == 3)//���
			{
				for (int i = 0; i < 5; i++)
				{
					now[i] = hard[i];
				}
			}


			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (now[j].time > now[j + 1].time)
					{
						now[6] = now[j];
						now[j] = now[j + 1];
						now[j + 1] = now[6];
					}
				}
			}

			if (diff == 1) // �ʱ�
			{
				for (int i = 0; i < 5; i++)
				{
					eazy[i]= now[i];
				}
			}
			else if (diff == 2) //�߱�
			{
				for (int i = 0; i < 5; i++)
				{
					nomal[i]= now[i];
				}
			}
			else if (diff == 3)//���
			{
				for (int i = 0; i < 5; i++)
				{
					hard[i]= now[i];
				}
			}
			
			FILE *SAVE = fopen("save.txt", "wt");

			for (int i = 0; i < 15; i++)
			{
				if (i >= 0 && i <= 4)
				{
					fprintf(SAVE, "%d %s\n", eazy[i].time, eazy[i].name);
				}
				else if (i >= 5 && i <= 9)
				{
					fprintf(SAVE, "%d %s\n", nomal[i - 5].time, nomal[i - 5].name);
				}
				else if (i >= 10 && i <= 14)
				{
					fprintf(SAVE, "%d %s\n", hard[i - 10].time, hard[i - 10].name);
				}
			}

			fclose(SAVE);

		}
		
	}
	else //�о���� ���н�
	{
		system("cls");
		system("color 8F"); //ȸ����濡 ���� ��� �۾�

		printf("save.txt ������ ã�µ� �����Ͽ����ϴ�\n\nsave ������ �����ϰ� ������� 'z' Ű�� �Է��� �ּ���.\n���Ḧ ���Ͻǰ�� �ƹ�Ű�� �����ּ���\n");

		char c;

		c = _getch();

		if (c == 'z')
		{
			FILE *SAVE = fopen("save.txt", "w");

			fprintf(SAVE, "999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n");
			fclose(SAVE);

			printf("���� �Ϸ�\n");

			fclose(SAVE);

			ranking_save(PorS,diff);
		}
	}
	

}