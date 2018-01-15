#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>


int key_input(); //키보드 입력  상1,좌2,하3,우4,키1 5,키2 6,키3 7,F2 8,esc 9반환
void gotoxy(int x, int y); // 커서 위치 변경
void print_gotoxy(int x, int y, char *s1); // 커서 위치 변경후 문자 출력
void main_screen(); // 메인 화면 시작 0, 옵션 1, 종료 3 반환 
void **create_mine(int xx,int yy); // 지뢰 배열
void **create_show_mine();//오픈 상황 10:벽 0:닫힌상태 1:열린상태 2:깃발 3:물음표
void open_mine(int **mine_stete,int **show_mine,int oxx,int oyy, int key_input);//칸 오픈
void game_over(int over);//게임오버&클리어
void move(int keyinput);//판 내에서 커서 이동
void game_play();//게임 플레이
void key(); // 게임중 키입력에 따른 반응
void open_group(int oxx,int oyy); // 뭉쳐진거 열기
void free_mine();// 종료시 프리
void game_option();//옵션
void change_difficult(int d_state);//난이도 변경
void print_difficult(int px,int py);//난이도 출력
void load_key(); //key setting 파일 불러와 할당
void print_key(int px, int py);//현재 키 상황 출력
void ranking_save(int PorS, int diff);



char key1 = '+', key2 = '+', key3 = '+', key_up='+', key_down='+', key_right='+', key_left='+';
int UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77;
int re_up = 1, re_left = 2, re_down = 3, re_right = 4;
int x = 0, y = 0; //좌표용
int xx = 0, yy = 0;//판 내 좌표
int sx=0, sy=1;//지뢰판 출력 기본 위치
int keyinput = 0;
int size_x = 16, size_y = 16, num_mine = 40,num_mine1;//num1은 클리어 여부 판단용
int openmine = 0;
int time_state = 0;
int flag_count = 0;
int **mine_state;
int **show_mine;
char s1[7][6]; // 키 설정 불러와 할당용
CONSOLE_CURSOR_INFO cursorInfo = { 0, };


int main()
{
	system("title 지뢰찾기"); //상태줄에 이름 표기
	system("color 8F"); //회색배경에 밝은 흰색 글씨
	srand(time(NULL)); //랜덤 변수용 테이블 고정
	cursorInfo.dwSize = 100; // 커서 사이즈 맥스
	cursorInfo.bVisible = FALSE; // 커서 보이지 않도록
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//커서 적용

	load_key();
	main_screen(); // 시작화면 불러옴

	system("pause");
	return 0;
}

int key_input() //상1,좌2,하3,우4,키1 5,키2 6,키3 7,F2 8,esc 9, F5 10반환
{
	char c;

	c = _getch();

	if (c == -32) //방향키는 값이 2개
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
	print_gotoxy(0, 0, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n■♠③♠①　　　　①♠②①①♠④♠②　　　②♠♠④♠③♠②♠♠③♠①　　①♠②②♠■\n■♠■②③①①①■③③♠■■■■■■①①①③■④♠♠④♠②■④♠■■■■■■■■①■\n■②■■⑤♠④■■♠④④♠♠■■③②♠①①♠■■④♠⑤③②■②♠■③♠♠①①②②①■\n■①■♠■♠■♠■③♠♠③④■■②②③②②②■③■④♠♠①■①②■④♠④②①③♠②■\n■②■♠⑤■♠④■④④②①♠■■②♠③♠④④■⑤♠■③②①■①②■④♠⑤④♠⑤♠③■\n■♠■②②③④♠■②♠♠②②■■①①③♠♠♠■♠③■③　　■②♠■■■■■■⑤♠④■\n■②■①♠②②♠■♠③②③♠■■①②②④♠⑤■③②②■②②■♠④■②②④④③③♠♠■\n■♠■②②②②②■②②①④♠■■♠②♠③②②■②②③■④♠■④♠■③①②♠①②⑤♠■\n■①■♠①①♠①■♠①②♠♠■■③③③♠①①■♠③♠②■♠■③♠■④♠③①①①♠♠■\n■①■②①②③④■②①♠♠♠■■③♠④③③②■③⑤♠♠③■■①②■♠♠③②①②②②■\n■②■③①①♠♠■③①③■■■■■■♠♠③♠■♠③♠⑥♠③■①　■■■■■■■■　■\n■②♠♠①①③♠♠③♠②♠②②②①②♠③③♠④②②②♠③♠♠①　　　②♠♠♠①　　■\n■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	int sx1=39,sy1=17,sy2=2; // 화면 출력할떄 문자위치밑 간격
	int state = 0;
	system("color 8F");
	cursorInfo.bVisible = FALSE; // 커서 지우기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	print_key(0, 24);
	print_difficult(47, 24); 

	x = sx1, y = sy1; //메뉴 출력
	print_gotoxy(x, y,"▶시작");
	y = sy1+sy2;
	print_gotoxy(x, y, "▷옵션");
	y = sy1+(sy2*2);
	print_gotoxy(x, y, "▷종료");
	y = sy1;
	

	while (1) // 커서 이동밑 선택시 반응
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


		print_gotoxy(x, y, "▷");
		x = sx1, y = sy1+(sy2*state);
		print_gotoxy(x, y, "▶");
		
	}
}

void **create_mine(int xx,int yy)
{
	int cnum_mine; //지뢰 생성을 위한 임시 변수
	int xxx = 0, yyy = 0;

	cnum_mine = num_mine;

	int **mine_state1 = malloc(sizeof(int *)*(size_y+2));//2차원 동적 배열

	for (int i = 0; i < (size_y+2); i++)
	{
		mine_state1[i] = calloc((size_x+2),sizeof(int));
	}

	for (int i = 0; i < size_x + 2; i++) //벽 배열
	{
		mine_state1[0][i] = 10;
		mine_state1[size_y + 1][i] = 10;
	}

	for (int i = 1; i < size_y + 2; i++) //벽 배열
	{
		mine_state1[i][0] = 10;
		mine_state1[i][size_x + 1] = 10;
	}

	while(cnum_mine>0) // 중복없는 지뢰 배치
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


	for (int i = 1; i < size_y+1; i++) //지뢰수에 맞춰 숫자 배열
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

	int **show_state = malloc(sizeof(int *)*(size_y + 2));//2차원 동적 배열

	for (int i = 0; i < (size_y + 2); i++)
	{
		show_state[i] = calloc((size_x + 2), sizeof(int));
	}

	for (int i = 0; i < size_x + 2; i++) //벽 배열
	{
		show_state[0][i] = 10;
		show_state[size_y + 1][i] = 10;
	}

	for (int i = 1; i < size_y + 2; i++) //벽 배열
	{
		show_state[i][0] = 10;
		show_state[i][size_x + 1] = 10;
	}

	return show_state;

}

void open_mine(int **mine_state, int **show_mine, int oxx, int oyy, int key_input) // 5 6 7
{
	if (key_input == 5)//키1입력시
	{
		if (show_mine[oyy][oxx] == 0)//아직 안열렸을경우
		{
			show_mine[oyy][oxx] = 1;//열음 상태로 변경
			openmine--;
			switch (mine_state[oyy][oxx])
			{
			case 0: //빈칸일경우 주변칸 오픈
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x87);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "▒");
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
			case 1: // 각 숫자일경우 숫자 출력
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x81);
				print_gotoxy((oxx * 2) + sx, (oyy) + sy, "①");
				open_group(oxx, oyy);
				break;
			case 2:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x82);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "②");
				open_group(oxx, oyy);
				break;
			case 3:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x84);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "③");
				open_group(oxx, oyy);
				break;
			case 4:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "④");
				open_group(oxx, oyy);
				break;
			case 5:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x85);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "⑤");
				open_group(oxx, oyy);
				break;
			case 6:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x83);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "⑥");
				open_group(oxx, oyy);
				break;
			case 7:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "⑦");
				open_group(oxx, oyy);
				break;
			case 8:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
				print_gotoxy((oxx * 2) + sx, (oyy)+sy, "⑧");
				open_group(oxx, oyy);
				break;
			case 9: //지뢰일시 게임오버
				game_over(0);
				break;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
			gotoxy((oxx * 2) + sx, oyy + sy);
		}
		else if (show_mine[oyy][oxx] == 2 || show_mine[oyy][oxx] == 3)//깃발이나 물음표를 클릭시 지뢰여부 판단
		{
			show_mine[oyy][oxx] = 0;
			open_mine(mine_state, show_mine, oxx, oyy, 5);
		}
	}

	else if (key_input == 6)//키2입력시
	{
		if (show_mine[oyy][oxx] == 0)//빈칸이면 깃발로
		{
			show_mine[oyy][oxx] = 2;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
			print_gotoxy((oxx * 2) + sx, (oyy) + sy, "♠");
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
		else if (show_mine[oyy][oxx] == 2)//깃발이면 ?로
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
		else if (show_mine[oyy][oxx] == 3)//?면 빈칸으로
		{
			show_mine[oyy][oxx] = 0;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
			print_gotoxy((oxx * 2) + sx, (oyy) + sy, "□");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
		}
		gotoxy((oxx * 2) + sx, oyy + sy);
	}

	else if (key_input == 7)//키3입력시
	{
		if (show_mine[oyy][oxx] == 1)//오픈된 상황일경우
		{
			int count = 0; //주변 8개칸 깃발수 조회
			if (show_mine[oyy - 1][oxx - 1] == 2) count++;
			if (show_mine[oyy - 1][oxx] == 2) count++;
			if (show_mine[oyy - 1][oxx + 1] == 2) count++;
			if (show_mine[oyy][oxx - 1] == 2) count++;
			if (show_mine[oyy][oxx + 1] == 2) count++;
			if (show_mine[oyy + 1][oxx - 1] == 2) count++;
			if (show_mine[oyy + 1][oxx] == 2) count++;
			if (show_mine[oyy + 1][oxx + 1] == 2) count++;

			if (count == mine_state[oyy][oxx])//깃발수가 숫자랑 같을경우
			{
				for (int i = oyy - 1; i < oyy + 2; i++)
				{
					for (int j = oxx - 1; j < oxx + 2; j++)
					{
						if (i == oyy&&j == oxx) continue;
						if (show_mine[i][j] == 0 || show_mine[i][j] == 3)//닫힌 상태나 ?표기시 오픈
						{
							open_mine(mine_state, show_mine, j, i, 5);
						}
						else if (show_mine[i][j] == 2) // 깃발일경우
						{
							if (mine_state[i][j] != 9) //깃발인데 지뢰가아닐경우 오픈
							{
								open_mine(mine_state, show_mine, j, i, 5);
							}
							else continue; // 지뢰일시 패스
						}

					}
				}
				gotoxy((oxx * 2) + sx, oyy + sy);
			}
			else // 확인키 사용시 주변칸 깜박임
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
							print_gotoxy((j * 2) + sx, (i)+sy, "■");
							
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
							print_gotoxy((j * 2) + sx, (i)+sy, "□");
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
	if (over == 1)//클리어
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8E);
		for (int i = 1; i < size_y + 1; i++)
		{
			for (int j = 1; j < size_x + 1; j++)
			{
				if (mine_state[i][j] == 9)
				{
					print_gotoxy((j * 2) + sx, (i)+sy, "★");
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
	else if (over == 0)//게임오버
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
		for (int i = 1; i < size_y + 1; i++)
		{
			for (int j = 1; j < size_x + 1; j++)
			{
				if (show_mine[i][j] == 2 && mine_state[i][j] == 9);
				else if (mine_state[i][j] == 9)
				{
					print_gotoxy((j * 2) + sx, (i)+sy, "★");
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

void move(int keyinput)//게임판에서의 커서 이동
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
	case 8: //리스타트
		system("cls");
		game_play();
		break;
	case 9://종료
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
	for (int i = 0; i < size_y + 2; i++) // 프리 (지뢰판)
	{
		free(mine_state[i]);
	}

	free(mine_state);

	for (int i = 0; i < size_y + 2; i++) // 프리 (지뢰판 오픈 상태)
	{
		free(show_mine[i]);
	}

	free(show_mine);
}

void open_group(int oxx,int oyy) // 눌렀는데 주변에 빈칸이있을시 뭉텅이로 오픈
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

	for (int i = 0; i < size_y + 2; i++) // 틀 출력
	{
		for (int j = 0; j < size_x + 2; j++)
		{
			if (i == 0 || i == size_y + 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
				printf("■");
			}
			else
			{
				if (j == 0 || j == size_x + 1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x80);
					printf("■");
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
					printf("□");
				}
			}
		}
		printf("\n");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
	print_difficult(0,sy+size_y+2);
	xx = (size_x+1)/2; //시작시 커서를 중앙으로 배치
	yy = (size_y+1)/2;
	gotoxy((xx * 2) + sx, (yy) + sy);
	int mine_maked = 0;
	time_t start_t, state_t;
	time_state = 0;
	double t_diff;

	while (1)
	{
		if (mine_maked == 0) //첫 입력일시 지뢰판 생성
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
			if (openmine == num_mine) //클리어 조건
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
				if (t_diff >= (1 + time_state)) //타이머
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
	print_gotoxy(x, y, "▶난이도");
	y = sy1+sy2;
	print_gotoxy(x, y, "▷랭킹");
	y = sy1+(sy2*2);
	print_gotoxy(x, y, "▷돌아가기");
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

		
		print_gotoxy(x, y, "▷");
		x = sx1, y = sy1+(sy2*state);
		print_gotoxy(x, y, "▶");
		
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
	print_gotoxy(x, y, "▶초급 ( 9 X 9 , 10 )");
	y = sy1+sy2;
	print_gotoxy(x, y, "▷중급 ( 16 X 16 , 40 )");
	y = sy1+(sy2*2);
	print_gotoxy(x, y, "▷고급 ( 30 X 16 , 99 )");
	y = sy1 + (sy2 * 3);
	print_gotoxy(x, y, "▷사용자 지정");
	y = sy1 + (sy2 * 4);
	print_gotoxy(x, y, "▷돌아가기");
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
				if (d_state == 0) game_option(); // 메뉴에서 조절시 메뉴로 돌아감
				else if (d_state == 1) game_play(); // 게임중에 조절시 다시 바로 게임 시작
			}

			else if (state == 1)
			{
				size_x = 16;
				size_y = 16;
				num_mine = 40;
				if (d_state == 0) game_option(); // 메뉴에서 조절시 메뉴로 돌아감
				else if (d_state == 1) game_play(); // 게임중에 조절시 다시 바로 게임 시작
			}

			else if (state == 2)
			{
				size_x = 30;
				size_y = 16;
				num_mine = 99;
				if (d_state == 0) game_option(); // 메뉴에서 조절시 메뉴로 돌아감
				else if (d_state == 1) game_play(); // 게임중에 조절시 다시 바로 게임 시작
			}

			else if (state == 3)
			{
				while (1)
				{
					y = sy1 + (sy2 * 3) + 1;
					print_gotoxy(x, y, "가로,세로,지뢰수를 스페이스 바로 구분해서 입력후 엔터");
					gotoxy(x, y + 1);
					scanf("%d %d %d", &size_x, &size_y, &num_mine);
					y = sy1 + (sy2 * 3);

					if(size_x<1||size_y<1||num_mine<1)
					{
						gotoxy(x, y + 2);
						printf("판의 크기나 지뢰의 수는 양수만 가능합니다");
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
							printf("지뢰수가 칸수보다 크면 안됩니다");
							Sleep(1000);
							gotoxy(x, y + 2);
							printf("                               ");
						}
					}
				}
				if (d_state == 0) game_option(); // 메뉴에서 조절시 메뉴로 돌아감
				else if (d_state == 1) game_play(); // 게임중에 조절시 다시 바로 게임 시작
			}

			else if (state == 4)
			{
				if (d_state == 0) game_option(); // 메뉴에서 조절시 메뉴로 돌아감
				else if (d_state == 1) game_play(); // 게임중에 조절시 다시 바로 게임 시작
			}

			
		}

		gotoxy(x, y);

		
		print_gotoxy(x, y, "▷");
		x = sx1, y = sy1+(sy2*state);
		print_gotoxy(x, y, "▶");
		
	}
}

void print_difficult(int px,int py)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8F);
	gotoxy(px, py);
	printf("현재 난이도 : ");
	if (size_x == 9 && size_y == 9 && num_mine == 10)
	{
		printf("초급 ( 9 X 9 , 10 )");
	}
	else if (size_x == 16 && size_y == 16 && num_mine == 40)
	{
		printf("중급 ( 16 X 16 , 40 )");
	}
	else if (size_x == 30 && size_y == 16 && num_mine == 99)
	{
		printf("고급 ( 30 X 16 , 99 )");
	}
	else
	{
		printf("사용자 지정 ( %d X %d , %d )", size_x, size_y, num_mine);
	}
}

void load_key()
{
	char s2[7]; // 설정 할당용;


	FILE *KS = fopen("key setting.txt", "r"); // 키셋팅 파일 읽어옴

	if (KS != NULL) //성공시
	{
		fscanf(KS, "%s %s %s %s %s %s %s", s1[0], s1[1], s1[2], s1[3], s1[4], s1[5], s1[6]);

		fclose(KS);
	}
	else //읽어오기 실패시
	{
		system("cls");
		system("color 8F"); //회색배경에 밝은 흰색 글씨

		printf("key setting 파일을 찾는데 실패하였습니다\n\nkey setting 파일을 생성하고 싶을경우 'z' 키를 입력해 주세요.\n종료를 원하실경우 아무키나 눌러주세요\n");

		char c;

		c = _getch();

		if (c == 'z')
		{
			FILE *KS = fopen("key setting.txt", "w");

			fprintf(KS, "up left down right z x c\n\n상 좌 하 우 키1 키2 키3 순으로 맨 윗줄에 띄어쓰기를 기준으로 입력해주세요\n각 키에 알바벳키를 할당하고 싶으면 해당위치에 알파벳을 방향키를 할당하고\n싶을경우 up, down, left, right를 적어주시면 됩니다.\n\nex) 방향키로 조작하고 키 1, 2, 3에 z x c를 배정하고싶을 경우\nup left down right z x c\n\nex2) wasd로 조작하고 방향키 아래 3개에 키1, 2, 3을 배정하고 싶을경우\nw a s d left down right");

			fclose(KS);

			printf("생성 완료\n");
		
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
	
	printf("현재 키:");
	for (int i = 0; i < 7; i++)
	{
		printf("%s ", s1[i]);
	}
}

void ranking_save(int PorS,int diff)//0 출력 1 저장
{
	typedef struct {
		int time;
		char name[11];
	} ranking;

	ranking eazy[5];
	ranking nomal[5];
	ranking hard[5];


	FILE *SAVE = fopen("save.txt", "rt");
	if (SAVE != NULL) //성공시
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
			system("color 8F"); //회색배경에 밝은 흰색 글씨

			print_gotoxy(17, 4, "초급");
			print_gotoxy(35, 4, "중급");
			print_gotoxy(53, 4, "고급");

			print_gotoxy(15, 6, "시간 이름");
			print_gotoxy(33, 6, "시간 이름");
			print_gotoxy(51, 6, "시간 이름");

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

			print_gotoxy(39, 20, "▶돌아가기");
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
			print_gotoxy(0, 21,"이름을 입력해 주세요:");
			scanf("%s", &now[5].name);
			now[5].name[10] = NULL;

			if (diff == 1) // 초급
			{
				for (int i = 0; i < 5; i++)
				{
					now[i] = eazy[i];
				}
			}
			else if (diff == 2) //중급
			{
				for (int i = 0; i < 5; i++)
				{
					now[i] = nomal[i];
				}
			}
			else if (diff == 3)//고급
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

			if (diff == 1) // 초급
			{
				for (int i = 0; i < 5; i++)
				{
					eazy[i]= now[i];
				}
			}
			else if (diff == 2) //중급
			{
				for (int i = 0; i < 5; i++)
				{
					nomal[i]= now[i];
				}
			}
			else if (diff == 3)//고급
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
	else //읽어오기 실패시
	{
		system("cls");
		system("color 8F"); //회색배경에 밝은 흰색 글씨

		printf("save.txt 파일을 찾는데 실패하였습니다\n\nsave 파일을 생성하고 싶을경우 'z' 키를 입력해 주세요.\n종료를 원하실경우 아무키나 눌러주세요\n");

		char c;

		c = _getch();

		if (c == 'z')
		{
			FILE *SAVE = fopen("save.txt", "w");

			fprintf(SAVE, "999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n999 AAA\n");
			fclose(SAVE);

			printf("생성 완료\n");

			fclose(SAVE);

			ranking_save(PorS,diff);
		}
	}
	

}