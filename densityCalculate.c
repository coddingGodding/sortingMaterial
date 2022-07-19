#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

//함수 선언
void intro();
void gotoxy(int x, int y);
int start_select();
int startToCalculate();
int calculateDensity(int n, double x);
int dataManage();
void addData();
void deleteData(int z);
int selectDataToDelete();
void option(double x, double y);

//전역변수 선언
//전역변수는 최대한 적어야 하지만, 편의성을 위해 대량의 변수를 전역변수로 설정
double range1 = 0.2;
double range2 = 0.5;
FILE* fp;
FILE* bp;
char num[100];
char density[100];
char name[200];
char name[200];
char tmp[200];
int d = 0;

int main() {
	//파일 테스트
	fp = fopen("nameData.txt", "r");
	if (fp == NULL) {
		printf("오류 : 파일을 열 수 없습니다.\n실행 파일과 같은 디렉토리에 nameData.txt 파일이 없을 수 있습니다.");
		char t = _getch();
		fclose(fp);
		return 0;
	}
	bp = fopen("bufferData.txt", "r");
	if (bp == NULL) {
		printf("오류 : 파일을 열 수 없습니다.\n실행 파일과 같은 디렉토리에 bufferData.txt 파일이 없을 수 있습니다.");
		char t = _getch();
		fclose(bp);
		return 0;
	}
	fclose(bp);
	
	//데이터 개수 설정
	while (fgets(num, sizeof(num), fp) != NULL) {
		fgets(density, sizeof(density), fp);
		fgets(name, sizeof(name), fp);
		d++;
	}
	fclose(fp);
	
	intro(); //인트로
	
	while (1) { //반복 시작
		int y = start_select(); //기본 화면
		if (y == 1) { //물체 분류
			while (1) {
				int u = startToCalculate(); //인터페이스
				if (u == 1) { //질량 + 부피
					system("cls");
					printf("물질의 질량(g)과 부피(mL)를 측정하여 차례대로 적어주세요\n(ex.질량 100g에 부피 70mL인 물질의 경우 100 70 입력)\n\n>");
					double a = 0;
					double b = 0;
					scanf("%lf %lf", &a, &b);
					system("cls");
					double c = a / b;
					calculateDensity(1, c);
				}
				else if (u == 2) { //밀도
					system("cls");
					printf("물질의 밀도(g/mL)를 입력해주세요\n\n>");
					double a = 0;
					scanf("%lf", &a);
					calculateDensity(0, a);
				}
				else if (u == 3) { //뒤로가기
					break;
				}
			}
		}
		else if (y == 2) { //데이터 관리
			while (1) {
				int u = dataManage(); //인터페이스
				if (u == 1) { //데이터 추가
					addData();
				}
				else if (u == 2) { //데이터 삭제
					while (1) {
						int z = selectDataToDelete();
						if (z == d + 1) { //뒤로가기
							break;
						}
						else { //삭제
							deleteData(z);
						}
					}
				}
				else if (u == 3) { //뒤로가기
					break;
				}
			}
		}
		else if (y == 3) {//오차범위 재설정
			option(range1, range2);
		}
		else if (y == 4) { //종료
			system("cls");
			return 0;
		}
	}
	return 0;
}

void intro() { //인트로
	printf("10409 박준성 탐구 발표\n밀도를 통한 물질 분류 시스템\n\n");
	printf("아무 키나 눌러 시작");
	char y = _getch();
	system("cls");
}

void gotoxy(int x, int y) { //커서 이동
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int start_select() {  //메인 인터페이스
	system("cls");
	int s = 1;
	int error = 0;
	char select = NULL;
	while (1) {
		system("cls");
		printf("물질 분류\n데이터 관리\n오차범위 재설정\n종료");
		if (error == 1) { //Caps Lock 활성화
			gotoxy(0, 6);
			printf("Caps Lock을 풀어주세요.");
			error = 0;
		}
		else if (error == 2) { //한/영키 전환
			gotoxy(0, 6);
			printf("한/영키를 바꿔주세요.");
			error = 0;
		}
		if (s == 1) {
			gotoxy(10, 0);
		}
		else if (s == 2) {
			gotoxy(12, 1);
		}
		else if (s == 3) {
			gotoxy(16, 2);
		}
		else if (s == 4) {
			gotoxy(5, 3);
		}
		printf("<");

		while (1) {
			if (_kbhit()) {
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {
					case 72:
						if (s != 1) {
							s--;
							break;
						}
					case 80:
						if (s != 4) {
							s++;
							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}
int startToCalculate() { //물질 분류 인터페이스
	system("cls");
	int s = 1;
	int error = 0;
	char select = NULL;
	while (1) {
		system("cls");
		printf("질량과 부피를 이용해 물질 분류하기\n밀도를 이용해 물질 분류하기\n뒤로가기");
		if (error == 1) { //Caps Lock 활성화
			gotoxy(0, 6);
			printf("Caps Lock을 풀어주세요.");
			error = 0;
		}
		else if (error == 2) { //한/영키 전환
			gotoxy(0, 6);
			printf("한/영키를 바꿔주세요.");
			error = 0;
		}
		if (s == 1) {
			gotoxy(35, 0);
		}
		else if (s == 2) {
			gotoxy(28, 1);
		}
		else if (s == 3) {
			gotoxy(9, 2);
		}
		printf("<");

		while (1) {
			if (_kbhit()) {
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {
					case 72:
						if (s != 1) {
							s--;
							break;
						}
					case 80:
						if (s != 3) {
							s++;
							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}
int calculateDensity(int n, double x) { //밀도 계산
	system("cls");
	if (n == 1) {
		printf("이 물질의 밀도는 %gg/mL입니다.\n", x);
	}
	else {
		printf("입력된 밀도는 %gg/mL입니다.\n", x);
	}
	fp = fopen("nameData.txt", "r");
	int f = 0;
	int a = 0;

	//밀도와 데이터의 완전한 일치
	while (fgets(num, sizeof(num), fp) != NULL) {
		num[strlen(num) - 1] = NULL;
		fgets(density, sizeof(density), fp);
		density[strlen(density) - 1] = NULL;
		fgets(name, sizeof(name), fp);
		name[strlen(name) - 1] = NULL;
		char t[100];
		sprintf(t, "%lf", x);
		if (strcmp(density, t) == 0) {
			if (f == 0) {
				printf("이 물질은 ");
				printf("%s(%gg/mL)", name, x);
				f++;
			}
			else {
				printf(", 혹은 %s(%gg/mL)", name, x);
				f++;
			}
		}
	}
	if (f != 0) {
		printf("일 가능성이 가장 높습니다.\n");
		a++;
	}
	f = 0;
	fclose(fp);

	//1차 오차범위 이내
	fp = fopen("nameData.txt", "r");
	while (fgets(num, sizeof(num), fp) != NULL) {
		num[strlen(num) - 1] = NULL;
		fgets(density, sizeof(density), fp);
		density[strlen(density) - 1] = NULL;
		fgets(name, sizeof(name), fp);
		name[strlen(name) - 1] = NULL;
		char t[100];
		sprintf(t, "%lf", x);
		if (atof(density) + range1 >= x && atof(density) - range1 <= x && strcmp(density, t) != 0) {
			if (f == 0) {
				printf("이 물질은 ");
				printf("%s(%gg/mL)", name, atof(density));
				f++;
			}
			else {
				printf(", 혹은 %s(%gg/mL)", name, atof(density));
				f++;
			}
		}
	}
	if (f != 0) {
		a++;
		if (a == 2) {
			printf("일 가능성이 있습니다.\n");
		}
		else if (f == 1) {
			printf("일 가능성이 가장 높습니다.\n");
		}
	}
	f = 0;
	fclose(fp);

	//2차 오차범위 이내
	fp = fopen("nameData.txt", "r");
	while (fgets(num, sizeof(num), fp) != NULL) {
		num[strlen(num) - 1] = NULL;
		fgets(density, sizeof(density), fp);
		density[strlen(density) - 1] = NULL;
		fgets(name, sizeof(name), fp);
		name[strlen(name) - 1] = NULL;
		if (atof(density) + range2 >= x && atof(density) - range2 <= x && (atof(density) + range1 < x || atof(density) - range1 > x)) {
			if (f == 0) {
				printf("이 물질은 ");
				printf("%s(%gg/mL)", name, atof(density));
				f++;
			}
			else {
				printf(", 혹은 %s(%gg/mL)", name, atof(density));
				f++;
			}
		}
	}
	if (f != 0) {
		printf("일 수도 있습니다.\n");
		a++;
	}
	f = 0;
	fclose(fp);

	//2차 오차범위 밖
	if (a == 0) {
		printf("데이터에 포함되지 않은 밀도입니다.\n");
	}

	printf("\n아무 키나 눌러 뒤로가기");
	char q = NULL;
	q = _getch();
}
void addData() { //데이터 추가
	system("cls");
	printf("추가할 데이터의 이름을 입력하세요.\n\n>");
	fp = fopen("nameData.txt", "r");
	char buffer[100];
	char buffer2[100];
	scanf("%s", buffer);
	system("cls");
	printf("물질 %s의 밀도를 입력하세요.\n\n>", buffer);
	scanf("%s", buffer2);
	char numa[100];
	char densitya[100];
	char buffera[100];
	int cancel = 0;
	while (fgets(numa, sizeof(numa), fp) != NULL) {
		numa[strlen(numa) - 1] = NULL;
		fgets(densitya, sizeof(densitya), fp);
		densitya[strlen(densitya) - 1] = NULL;
		fgets(buffera, sizeof(buffera), fp);
		buffera[strlen(buffera) - 1] = NULL;
			int s = 1;
			int error = 0;
			char select = NULL;
			if (strcmp(buffera, buffer) == 0) { //추가할 데이터와 이름이 같은 데이터가 있을 경우
				while (1) {
				system("cls");
				printf("%s번 데이터 %s(%sg/mL)와 이름이 같습니다.\n무시하고 추가하시겠습니까?\n", numa, buffera, densitya);
				printf("예\n아니오");
				if (error == 1) {
					gotoxy(0, 4);
					printf("Caps Lock을 풀어주세요.");
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 4);
					printf("한/영키를 바꿔주세요.");
					error = 0;
				}
				else if (error == 3) {
					break;
				}
				else if (error == 4) {
					break;
				}
				if (s == 1) {
					gotoxy(3, 2);
				}
				else if (s == 2) {
					gotoxy(7, 3);
				}
				printf("<");

				while (1) {
					if (_kbhit()) {
						select = _getch();
						if (select == -32) {
							select = _getch();
							switch (select) {
							case 72:
								if (s != 1) {
									s--;
									break;
								}
							case 80:
								if (s != 2) {
									s++;
									break;
								}
							}
							break;
						}
						else if (select == 'a') {
							if (s == 1) { //무시하고 추가
								error = 3;
								break;
							}
							else if (s == 2) { //취소
								error = 4;
								break;
							}
						}
						else if (select == 'A') {
							error = 1;
							break;
						}
						else if (select < 0 || select > 126) {
							error = 2;
							break;
						}
					}
				}
			}
			if (error == 4) {
				cancel = 1;
				break;
			}
		}
	}
	fclose(fp);
	if (cancel == 0) {
		fp = fopen("nameData.txt", "a");
		d++;
		fputs(_itoa(d, num, 10), fp);
		fputs("\n", fp);
		fputs(buffer2, fp);
		fputs("\n", fp);
		fputs(buffer, fp);
		fputs("\n", fp);
		fclose(fp);
	}
}
void deleteData(int z) { //데이터 삭제
	fp = fopen("nameData.txt", "r");
	bp = fopen("bufferData.txt", "w");
	int a = 0;

	//bufferData로 데이터 복사/수정
	while (fgets(num, sizeof(num), fp) != NULL) { 
		char numa[100];
		strcpy(numa, num);
		numa[strlen(numa) - 1] = NULL;
		fgets(density, sizeof(density), fp);
		fgets(name, sizeof(name), fp);
		if (atoi(numa) != z) {
			if (a == 0) {
				fputs(num, bp);
				fputs(density, bp);
				fputs(name, bp);
			}
			else if (a == 1) {
				fputs(_itoa(atoi(numa) - 1, numa, 10), bp);
				fputs("\n", bp);
				fputs(density, bp);
				fputs(name, bp);
			}
		}
		if (atoi(numa) == z) {
			a = 1;
		}
	}
	fclose(fp);
	fclose(bp);

	//nameData로 복사
	fp = fopen("nameData.txt", "w");
	bp = fopen("bufferData.txt", "r");
	while (fgets(num, sizeof(num), bp) != NULL) {
		fgets(density, sizeof(density), bp);
		fgets(name, sizeof(name), bp);
		fputs(num, fp);
		fputs(density, fp);
		fputs(name, fp);
	}
	fclose(fp);
	fclose(bp);
	d--;
}
int selectDataToDelete() { //데이터 삭제 인터페이스
	system("cls");
	int s = 1;
	int error = 0;
	char select = NULL;
	while (1) {
		system("cls");
		fopen("nameData.txt", "r");
		while (fgets(num, sizeof(num), fp) != NULL) {
			num[strlen(num) - 1] = NULL;
			fgets(density, sizeof(density), fp);
			density[strlen(density) - 1] = NULL;
			fgets(name, sizeof(name), fp);
			name[strlen(name) - 1] = NULL;
			if (atoi(num) == s) {
				printf("%s - %s %sg/mL <\n\n", num, name, density);
			}
			else {
				printf("%s - %s %sg/mL\n\n", num, name, density);
			}
		}
		fclose(fp);
		if (s == d + 1) {
			printf("뒤로가기 <");
		}
		else {
			printf("뒤로가기");
		}

		if (error == 1) {
			gotoxy(0, 2 * d + 2);
			printf("Caps Lock을 풀어주세요.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 2 * d + 2);
			printf("한/영키를 바꿔주세요.");
			error = 0;
		}
		while (1) {
			if (_kbhit()) {
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {
					case 72:
						if (s != 1) {
							s--;
							break;
						}
					case 80:
						if (s != d + 1) {
							s++;
							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}
int dataManage() { //데이터 관리 인터페이스
	system("cls");
	int s = 1;
	int error = 0;
	char select = NULL;
	while (1) {
		system("cls");
		fopen("nameData.txt", "r");
		while (fgets(num, sizeof(num), fp) != NULL) {
			num[strlen(num) - 1] = NULL;
			fgets(density, sizeof(density), fp);
			density[strlen(density) - 1] = NULL;
			fgets(name, sizeof(name), fp);
			name[strlen(name) - 1] = NULL;
			printf("%s - %s %sg/mL\n\n", num, name, density);
		}
		fclose(fp);
		printf("데이터 추가\n데이터 삭제\n뒤로가기");
		if (error == 1) {
			gotoxy(0, 2 * d + 4);
			printf("Caps Lock을 풀어주세요.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 2 * d + 4);
			printf("한/영키를 바꿔주세요.");
			error = 0;
		}
		if (s == 1) {
			gotoxy(12, 2 * d);
		}
		else if (s == 2) {
			gotoxy(12, 2 * d + 1);
		}
		else if (s == 3) {
			gotoxy(9, 2 * d + 2);
		}
		printf("<");

		while (1) {
			if (_kbhit()) {
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {
					case 72:
						if (s != 1) {
							s--;
							break;
						}
					case 80:
						if (s != 3) {
							s++;
							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					return s;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
	}
}

void option() { //오차범위 설정
	char select = NULL;
	int s = 1;
	int error = 0;
	while (1) {
		system("cls");
		printf("1차 오차범위 : %g\n2차 오차범위 : %g\n\n", range1, range2);
		printf("1차 오차범위 수정\n2차 오차범위 수정\n뒤로가기");
		if (error == 1) {
			gotoxy(0, 7);
			printf("Caps Lock을 풀어주세요.");
			error = 0;
		}
		else if (error == 2) {
			gotoxy(0, 7);
			printf("한/영키를 바꿔주세요.");
			error = 0;
		}
		if (s == 1) {
			gotoxy(18, 3);
		}
		else if (s == 2) {
			gotoxy(18, 4);
		}
		else if (s == 3) {
			gotoxy(10, 5);
		}
		printf("<");
		int x = 0;
		while (1) {
			if (_kbhit()) {
				select = _getch();
				if (select == -32) {
					select = _getch();
					switch (select) {
					case 72:
						if (s != 1) {
							s--;
							break;
						}
					case 80:
						if (s != 3) {
							s++;

							break;
						}
					}
					break;
				}
				else if (select == 'a') {
					x = s;
					break;
				}
				else if (select == 'A') {
					error = 1;
					break;
				}
				else if (select < 0 || select > 126) {
					error = 2;
					break;
				}
			}
		}
		if (x == 1) {
			double q = 0.0;
			error = 0;
			while (1) {
				system("cls");
				printf("현재 1차 오차범위 : %g\n", range1);
				printf("변경할 값을 입력해주세요. : ");
				if (error == 1) {
					gotoxy(0, 3);
					printf("1차 오차범위는 2차 오차범위보다 클 수 없습니다.\n현재 2차 오차범위:%g", range2);
					gotoxy(28, 1);
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 3);
					printf("오차범위는 0보다 작을 수 없습니다.");
					gotoxy(28, 1);
					error = 0;
				}
				scanf("%lf", &q);
				if (q > range2) {
					error = 1;
				}
				else if (q < 0) {
					error = 2;
				}
				else {
					break;
				}
			}
			range1 = q;
			x = 0;
		}
		else if (x == 2) {
			double q = 0.0;
			int error = 0;
			while (1) {
				system("cls");
				printf("현재 2차 오차범위 : %g\n", range2);
				printf("변경할 값을 입력해주세요. : ");
				if (error == 1) {
					gotoxy(0, 3);
					printf("2차 오차범위는 1차 오차범위보다 작을 수 없습니다.\n현재 1차 오차범위:%g", range1);
					gotoxy(28, 1);
					error = 0;
				}
				else if (error == 2) {
					gotoxy(0, 3);
					printf("오차범위는 0보다 작을 수 없습니다.");
					gotoxy(28, 1);
					error = 0;
				}
				scanf("%lf", &q);
				if (q < range1) {
					error = 1;
				}
				else if (q < 0) {
					error = 2;
				}
				else {
					break;
				}
			}
			range2 = q;
			x = 0;
		}
		else if (x == 3) {
			break;
		}
	}
}