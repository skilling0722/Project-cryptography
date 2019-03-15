#include<stdio.h>
#include<windows.h>
#include<conio.h>

void menu_select();
void menu();
void menu_star();
void gotoxy();
void input_key_plain();
void KCP();
void polyalphabetic();
void Key_Encryption();

int* PPE1_encryption();
int* PPE2_encryption();
int* GGE_encryption();
int* GGE2_encryption();
int* XOR_encryption();

int* PPE1_decryption();
int* PPE2_decryption();
int* GGE_decryption();
int* GGE2_decryption();
int* XOR_decryption();

int input_done = 0;
int encryption_done = 0;
int menu_select_position;
int klen;
int mlen;
int* okey;
int* m;

int* key1;
int* key2;
int* key3;
int* key4;
int* orderkey;

int* mcryp;
int* mcryp2;
int* mcryp3;
int* mcryp4;
int* mcryp5;

int* mdecryp;
int* mdecryp2;
int* mdecryp3;
int* mdecryp4;
int* mdecryp5;

void gotoxy(int x, int y) {									//좌표 설정
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void menu() {													//콘솔창 메뉴 프린트
	gotoxy(7, 0);
	puts("11조 프로젝트");
	gotoxy(2, 1);
	puts("-----------------------");
	gotoxy(3, 3);
	puts("키, 평문 입력하기");
	gotoxy(3, 4);
	puts("암호화 시작");
	gotoxy(3, 5);
	puts("복호화 시작");
	gotoxy(3, 6);
	puts("종료");
}

void menu_star(int y) {										//메뉴 선택 별
	gotoxy(0, y);
	puts("*");
}

void input_exit() {											//키 입력시 메뉴 exit
	int key = 0;
	printf("\n\n 스페이스바를 입력하여 종료하세요.\n");
	while (1) {
		key = _getch();
		if (key == 32) {
			system("cls");
			menu_select();
			break;
		}
	}
}

void menu_select() {											//메뉴
	menu_select_position = 3;
	int key;
	menu();
	menu_star(menu_select_position);
	while (1) {
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				if (menu_select_position > 3)
					menu_select_position--;
				system("cls");
				menu_star(menu_select_position);
				menu();
				break;
			case 80:
				if (menu_select_position < 6)
					menu_select_position++;
				system("cls");
				menu_star(menu_select_position);
				menu();
				break;
			}
		}
		else if (key == 13) {
			switch (menu_select_position) {
			case 3:
				system("cls");
				input_key_plain();
				input_done = 1;
				input_exit();
				break;
			case 4:
				system("cls");
				if (input_done == 1) {
					printf("\n------------암호화------------\n\n");
					printf("평문: \n");
					for (int i = 0; i < mlen; i++) {
						printf("%c", m[i]);
					}
					mcryp  = PPE1_encryption(m, key4);
					mcryp2 = PPE2_encryption(mcryp, klen);
					mcryp3 = GGE_encryption(mcryp2, key1, key4);
					mcryp4 = GGE2_encryption(mcryp3, key2, key3);
					mcryp5 = XOR_encryption(mcryp4, key3);
					encryption_done = 1;
					input_exit();
					break;
				}
				else {
					printf("평문과 키를 입력받은 후에 시도하세요.\n");
					input_exit();
					break;
				}
			case 5:
				system("cls");
				if (input_done == 1 && encryption_done == 1) {
					printf("\n\n------------복호화------------");
					mdecryp  = XOR_decryption(mcryp5, key3);
					mdecryp2 = GGE2_decryption(mdecryp, key2, key3);
					mdecryp3 = GGE_decryption(mdecryp2, key1, key4);
					mdecryp4 = PPE2_decryption(mdecryp3, klen);
					mdecryp5 = PPE1_decryption(mdecryp4, key4);
					printf("\n평문: \n");
					for (int i = 0; i < mlen; i++) {
						printf("%c", m[i]);
					}
					for (int i = 0; i < mlen; i++) {
						if (m[i] == mdecryp5[i]) {
							if (i == mlen - 1) {
								printf("\n\n평문과 복호문이 일치합니다.");
							}
						}
						else printf("\n\n평문과 복호문이 일치하지않습니다.");
					}
					input_exit();
					break;
				}
				else {
					printf("암호화 과정을 거친 후에 시도하세요.\n");
					input_exit();
					break;
				}
			case 6:
				for (int q = 3; q > 0; q--) {
					system("cls");
					printf("\n%d초 뒤에 종료됩니다.\n", q);
					Sleep(1000);
				}
				exit(1);
			}
		}
	}
}

void input_key_plain() {
	klen = 1;
	mlen = 1;
	okey = (int *)malloc(klen * sizeof(int));
	m = (int *)malloc(mlen * sizeof(int));

	printf("키를 입력하세요: ");								//KEY 입력
	for (int i = 0; i < klen; i++) {
		char ki = _getch();
		if (ki != 13 && ki != 8) {
			okey = (int *)realloc(okey, sizeof(int)*klen);
			okey[i] = ki;
			klen++;
			printf("%c", okey[i]);
		}
		else if (ki == 8) {
			i -= 2;
			klen--;
		}
		else if (ki == 13) {
			klen--;
		}
	}

	Key_Encryption();											//KEY 암호화

	printf("\n\nkey1: ");										//KEY1 출력
	for (int i = 0; i < klen; i++) {
		printf("%c", key1[i]);
	}
	printf("\nkey2: ");										//KEY2 출력
	for (int i = 0; i < klen; i++) {
		printf("%c", key2[i]);
	}
	printf("\nkey3: ");										//KEY3 출력
	for (int i = 0; i < klen; i++) {
		printf("%c", key3[i]);
	}
	printf("\nkey4: ");										//KEY4 출력
	for (int i = 0; i < klen; i++) {
		printf("%c", key4[i]);
	}

	printf("\n\n평문을 입력하세요: ");
	for (int j = 0; j < mlen; j++) {
		char mj = _getch();
		if (mj != 13 && mj != 8) {
			m = (int *)realloc(m, sizeof(int)*mlen);
			m[j] = mj;
			mlen++;
			printf("%c", m[j]);
		}
		else if (mj == 13) {
			mlen--;
		}
		else if (mj == 8) {
			mlen--;
			j -= 2;
		}
	}

	printf("\n\n평문: \n");									//평문 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", m[i]);
	}
	free(okey);
}

void KCP(int *okey, int klen) {
	key1 = (int *)malloc(klen * sizeof(int));
	key2 = (int *)malloc(klen * sizeof(int));
	for (int i = 0; i < klen; i++) {
		key1[i] = okey[i] + klen;
		while (key1[i] > 126) {                        // 아스키 코드값을 벗어날 경우
			key1[i] -= 95;
		}
	}
	for (int j = 0; j < klen; j++) {
		key2[j] = okey[j] - (klen % 95);
		while (key2[j] < 32) {                        // 아스키 코드값을 벗어날 경우
			key2[j] += 95;
		}
	}
}

void polyalphabetic(int *okey, int* key1, int* key2) {
	key3 = (int *)malloc(klen * sizeof(int));
	key4 = (int *)malloc(klen * sizeof(int));
	for (int an = 0; an < klen;) {
		for (int bn = 0; bn < klen && an < klen; an++, bn++) {  
			int m = okey[bn] - 32;                            // 키의 상대적인 크기 계산
			int n = key1[an] + m;								// 키의 상대적 크기만큼 평문 시프트
			if (n > 126) {									// 아스키 코드값을 벗어날 경우
				n -= 95;										// 아스키 코드의 처음으로 돌아감(명령어 스킵)
			}
			key3[an] = n;										// 시프트된 값 저장
		}
	}

	for (int an = 0; an < klen;) {
		for (int bn = 0; bn < klen && an < klen; an++, bn++) {  
			int m = okey[bn] - 32;                            // 키의 상대적인 크기 계산
			int n = key2[an] + m;								// 키의 상대적 크기만큼 평문 시프트
			if (n > 126) {									// 아스키 코드값을 벗어날 경우
				n -= 95;										// 아스키 코드의 처음으로 돌아감(명령어 스킵)
			}
			key4[an] = n;										// 시프트된 값 저장
		}
	}
}

void Key_Encryption() {
	KCP(okey, klen);
	polyalphabetic(okey, key1, key2);
}

int* PPE2_encryption(int* plain, int klen) {
	mcryp2 = (int *)malloc(mlen * sizeof(int));
	int l = klen % 3 + 2;							// 키의 길이를 이용한 달팽이배열 크기 계산
	
	int **Sarr;										// 2차원 배열 동적할당
	Sarr = (int**)malloc(sizeof(int *)*l);	
	for (int i = 0; i < l; i++) {				
		Sarr[i] = (int*)malloc(sizeof(int) *l);
	}

	int div = 0;
	int olen = mlen;

	while (olen >= l * l) {
		div += 1;
		olen -= l * l;
	}
	int an = 0;
	int an2 = 0;
	for (int i = 0; i < div; i++) {
		int j = 0;
		int k = 0;
		int trow = 0;
		int brow = 0;
		int lcol = 0;
		int rcol = 0;
		for (int rot = 0; trow + brow < l && lcol + rcol < l;) {
			switch (rot % 4)                        // 회전수를 4단계로 구분 윗변 - 우변 
			{										//	- 아랫변 - 좌변 순으로 진행
			case 0:									// 윗변
				for (j = lcol; j < l - rcol; j++) {
					Sarr[trow][j] = plain[an];
					an += 1;
				}
				j -= 1;                             //반복이 끝나고도 j가 한번 더 더해지므로 다시 빼준다
				rot += 1;                           //연산 종료 후 다음 변으로 회전
				trow += 1;                          // 사용된 행이 다시 사용되지 않도록 top row 표시
				break;
			case 1:									// 우변
				for (k = trow; k < l - brow; k++) {
					Sarr[k][j] = plain[an];             // j에 대한 선언이 반복문 바깥에 있으므로 
					an += 1;						// 초기화되지않고 이전 단계의 값 유지
				}
				k -= 1;
				rot += 1;
				rcol += 1;
				break;
			case 2:									// 아랫변
				for (j = (l - 1) - rcol; j >= lcol; j--) {
					Sarr[k][j] = plain[an];
					an += 1;
				}
				j += 1;
				rot += 1;
				brow += 1;
				break;
			case 3:									// 좌변
				for (k = (l - 1) - brow; k >= trow; k--) {
					Sarr[k][j] = plain[an];
					an += 1;
				}
				k += 1;
				rot += 1;
				lcol += 1;
				break;
			}
		}

		for (int m = 0; m < l; m++) {				//만들어진 달팽이 배열을 암호문 배열에 저장
			for (int n = 0; n < l; n++) {
				mcryp2[an2] = Sarr[m][n];
				an2 += 1;
			}
		}
	}
	for (int i = mlen - olen; i < mlen; i++) {		//달팽이 배열에 속하지못한 평문 처리
		mcryp2[i] = plain[i];
	}

	printf("\n핑핑이2 암호문 : \n");
	for (int i = 0; i < mlen; i++) {				//결과 출력
		printf("%c", mcryp2[i]);
	}
	printf("\n");

	for (int i = 0; i < l; i++) {					// 배열 동적할당 초기화
		free(Sarr[i]);
	}
	free(Sarr);
	return mcryp2;
}

int* PPE1_encryption(int* plain, int* key) {
	mcryp = (int *)malloc(mlen * sizeof(int));
	int div = 1;
	int olen = mlen;
	int seq = 0;
	int size=7;
	int* l;

	l = (int *)malloc(1 * sizeof(int));
	
	for (int i = 0; i < div; i++) {
		if (seq < mlen) {
			int seq2 = seq;
			while (seq2 >= klen) {
				seq2 -= klen;
			}
			if ((key[seq2] % size + 3)*(key[seq2] % size + 3) > olen) {
				break;
			}
			l = (int *)realloc(l, div * sizeof(int));
			l[i] = key[seq2] % size + 3;
			seq += (l[i] * l[i]);
			olen -= (l[i] * l[i]);
			div++;
		}
	}
	div--;

	int an = 0;
	int an2 = 0;
	for (int i = 0; i < div; i++) {
		int **Sarr;
		Sarr = (int**)malloc(sizeof(int *)*l[i]);
		for (int j = 0; j < l[i]; j++) {
			Sarr[j] = (int*)malloc(sizeof(int) *l[i]);
		}

		int j = 0;
		int k = 0;
		int trow = 0;
		int brow = 0;
		int lcol = 0;
		int rcol = 0;
		for (int rot = 0; trow + brow < l[i] && lcol + rcol < l[i];) {
			switch (rot % 4)                        // 회전수를 4단계로 구분 윗변 - 우변 
			{										//	- 아랫변 - 좌변 순으로 진행
			case 0:									// 윗변
				for (j = lcol; j < l[i] - rcol; j++) {
					Sarr[trow][j] = plain[an];
					an += 1;
				}
				j -= 1;                             //반복이 끝나고도 j가 한번 더 더해지므로 다시 빼준다
				rot += 1;                           //연산 종료 후 다음 변으로 회전
				trow += 1;                          // 사용된 행이 다시 사용되지 않도록 top row 표시
				break;
			case 1:									// 우변
				for (k = trow; k < l[i] - brow; k++) {
					Sarr[k][j] = plain[an];             // j에 대한 선언이 반복문 바깥에 있으므로 
					an += 1;						// 초기화되지않고 이전 단계의 값 유지
				}
				k -= 1;
				rot += 1;
				rcol += 1;
				break;
			case 2:									// 아랫변
				for (j = (l[i] - 1) - rcol; j >= lcol; j--) {
					Sarr[k][j] = plain[an];
					an += 1;
				}
				j += 1;
				rot += 1;
				brow += 1;
				break;
			case 3:									// 좌변
				for (k = (l[i] - 1) - brow; k >= trow; k--) {
					Sarr[k][j] = plain[an];
					an += 1;
				}
				k += 1;
				rot += 1;
				lcol += 1;
				break;
			}
		}

		for (int m = 0; m < l[i]; m++) {				//만들어진 달팽이 배열을 암호문 배열에 저장
			for (int n = 0; n < l[i]; n++) {
				mcryp[an2] = Sarr[m][n];
				an2 += 1;
			}
		}
		for (int j = 0; j < l[i]; j++) {					// 배열 동적할당 초기화
			free(Sarr[j]);
		}
		free(Sarr);
	}

	for (int i = mlen - olen; i < mlen; i++) {		//달팽이 배열에 속하지못한 평문 처리
		mcryp[i] = plain[i];
	}

	printf("\n\n핑핑이1 암호문 : \n");
	for (int i = 0; i < mlen; i++) {				//결과 출력
		printf("%c", mcryp[i]);
	}
	printf("\n");

	return mcryp;
}

int* GGE_encryption(int* plain, int* key1, int* key4) {
	mcryp2 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  // bn이 키 배열 크기 보다 커지거나
			if (an % 2 == 0) {									// an이 평문 배열 크기보다 커지면 반복문 종료
				mcryp2[an] = plain[an] - key1[bn];
				while (mcryp2[an] < 32) {                       // 아스키 코드값을 벗어날 경우
					mcryp2[an] += 95;
				}
			}
			else if (an % 2 == 1) {
				mcryp2[an] = plain[an] + key4[bn];
				while (mcryp2[an] > 126) {                      // 아스키 코드값을 벗어날 경우
					mcryp2[an] -= 95;
				}
			}
		}
	}
	printf("\n낑낑이1 암호문 : \n");							// 결과 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", mcryp2[i]);
	}
	return mcryp2;
}

int* GGE2_encryption(int* plain, int* key2, int* key3) {
	mcryp3 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  // bn이 키 배열 크기 보다 커지거나
			if (an > mlen / 2) {								// an이 평문 배열 크기보다 커지면 반복문 종료
				mcryp3[an] = plain[an] - key2[bn];
				while (mcryp3[an] < 32) {                       // 아스키 코드값을 벗어날 경우
					mcryp3[an] += 95;
				}
			}
			else if (an <= mlen / 2) {
				mcryp3[an] = plain[an] + key3[bn];
				while (mcryp3[an] > 126) {                      // 아스키 코드값을 벗어날 경우
					mcryp3[an] -= 95;
				}
			}
		}
	}
	printf("\n\n낑낑이2 암호문 : \n");							//결과 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", mcryp3[i]);
	}
	return mcryp3;
}

int* XOR_encryption(int* plain, int* key) {
	mcryp4 = (int *)malloc(mlen * sizeof(int));
	printf("\n\nXOR 암호문: \n");

	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {      // bn이 키 배열 크기 보다 커지거나
			mcryp4[an] = key[bn] ^ plain[an];						// an이 평문 배열 크기보다 커지면 반복문 종료
			printf("%c ", mcryp4[an]);								// 결과 출력
		}
	}
	return mcryp4;
}

int* PPE1_decryption(int* cipher, int* key) {
	mdecryp5 = (int *)malloc(mlen * sizeof(int));
	int div = 1;
	int olen = mlen;
	int seq = 0;
	int size = 7;

	int* l;
	l = (int *)malloc(1 * sizeof(int));

	for (int i = 0; i < div; i++) {
		if (seq < mlen) {
			int seq2 = seq;
			while (seq2 >= klen) {
				seq2 -= klen;
			}
			if ((key[seq2] % size + 3)*(key[seq2] % size + 3) > olen) {
				break;
			}
			l = (int *)realloc(l, div * sizeof(int));
			l[i] = key[seq2] % size + 3;
			seq += (l[i] * l[i]);
			olen -= (l[i] * l[i]);
			div++;
		}
	}
	div--;

		int dan = 0, dan2 = 0;

		for (int i = 0; i < div; i++) {
			int **DSarr;
			DSarr = (int**)malloc(sizeof(int *)*l[i]);			// 복호화에 이용할 2차원 배열 동적할당
			for (int j = 0; j < l[i]; j++) {
				DSarr[j] = (int*)malloc(sizeof(int) *l[i]);
			}

			for (int m = 0; m < l[i]; m++) {
				for (int n = 0; n < l[i]; n++) {			// 암호문 행렬을 l*l 행렬에 순서대로 저장
					DSarr[m][n] = cipher[dan];
					dan += 1;
				}
			}
			int j = 0, k = 0;
			int trow = 0, brow = 0;
			int lcol = 0, rcol = 0;
			for (int rot = 0; trow + brow < l[i] && lcol + rcol < l[i];) {
				switch (rot % 4)                        // 회전수를 4단계로 구분 윗변 - 우변 
				{										// - 아랫변 - 좌변 순으로 진행
				case 0:									// 윗변
					for (j = lcol; j < l[i] - rcol; j++) {
						mdecryp5[dan2] = DSarr[trow][j];
						dan2 += 1;
					}
					j -= 1;                             //반복이 끝나고도 j가 한번 더 더해지므로 다시 빼준다
					rot += 1;                           //연산 종료 후 다음 변으로 회전
					trow += 1;                          // 사용된 행이 다시 사용되지 않도록 top row 표시
					break;
				case 1:									// 우변
					for (k = trow; k < l[i] - brow; k++) {
						mdecryp5[dan2] = DSarr[k][j];   // j에 대한 선언이 반복문 바깥에 있으므로 
						dan2 += 1;						// 초기화되지않고 이전 단계의 값 유지
					}
					k -= 1;
					rot += 1;
					rcol += 1;
					break;
				case 2:									// 아랫변
					for (j = (l[i] - 1) - rcol; j >= lcol; j--) {
						mdecryp5[dan2] = DSarr[k][j];
						dan2 += 1;
					}
					j += 1;
					rot += 1;
					brow += 1;
					break;
				case 3:									// 좌변
					for (k = (l[i] - 1) - brow; k >= trow; k--) {
						mdecryp5[dan2] = DSarr[k][j];
						dan2 += 1;
					}
					k += 1;
					rot += 1;
					lcol += 1;
					break;
				}
			}

			for (int j = 0; j<l[i]; j++) {				//동적할당 해제
				free(DSarr[j]);
			}
			free(DSarr);
		}

		for (int i = mlen - olen; i < mlen; i++) {		// 달팽이배열에 속하지못한 평문 처리
			mdecryp5[i] = cipher[i];
		}

		printf("\n핑핑이1 복호문: \n");					//결과 출력
		for (int i = 0; i < mlen; i++) {
			printf("%c", mdecryp5[i]);
		}
		printf("\n");

	return mdecryp5;
}

int* PPE2_decryption(int* cipher, int klen) {
	mdecryp4 = (int *)malloc(mlen * sizeof(int));
	int l = klen % 3 + 2;
	int **Sarr;
	Sarr = (int**)malloc(sizeof(int *)*l);			// 2차원 배열 동적할당
	for (int i = 0; i < l; i++) {
		Sarr[i] = (int*)malloc(sizeof(int) *l);
	}
	int div = 0;
	int olen = mlen;
	int dan = 0, dan2 = 0;

	while (olen >= l * l) {
		div += 1;
		olen -= l * l;
	}
	int **DSarr;
	DSarr = (int**)malloc(sizeof(int *)*l);			// 복호화에 이용할 2차원 배열 동적할당
	for (int i = 0; i < l; i++) {
		DSarr[i] = (int*)malloc(sizeof(int) *l);
	}

	for (int i = 0; i < div; i++) {
		for (int m = 0; m < l; m++) {
			for (int n = 0; n < l; n++) {			// 암호문 행렬을 l*l 행렬에 순서대로 저장
				DSarr[m][n] = cipher[dan];
				dan += 1;
			}
		}

		int j = 0, k = 0;
		int trow = 0, brow = 0;
		int lcol = 0, rcol = 0;

		for (int rot = 0; trow + brow < l && lcol + rcol < l;) {
			switch (rot % 4)                        // 회전수를 4단계로 구분 윗변 - 우변 
			{										// - 아랫변 - 좌변 순으로 진행
			case 0:									// 윗변
				for (j = lcol; j < l - rcol; j++) {
					mdecryp4[dan2] = DSarr[trow][j];
					dan2 += 1;
				}
				j -= 1;                             //반복이 끝나고도 j가 한번 더 더해지므로 다시 빼준다
				rot += 1;                           //연산 종료 후 다음 변으로 회전
				trow += 1;                          // 사용된 행이 다시 사용되지 않도록 top row 표시
				break;
			case 1:									// 우변
				for (k = trow; k < l - brow; k++) {
					mdecryp4[dan2] = DSarr[k][j];   // j에 대한 선언이 반복문 바깥에 있으므로 
					dan2 += 1;						// 초기화되지않고 이전 단계의 값 유지
				}
				k -= 1;
				rot += 1;
				rcol += 1;
				break;
			case 2:									// 아랫변
				for (j = (l - 1) - rcol; j >= lcol; j--) {
					mdecryp4[dan2] = DSarr[k][j];
					dan2 += 1;
				}
				j += 1;
				rot += 1;
				brow += 1;
				break;
			case 3:									// 좌변
				for (k = (l - 1) - brow; k >= trow; k--) {
					mdecryp4[dan2] = DSarr[k][j];
					dan2 += 1;
				}
				k += 1;
				rot += 1;
				lcol += 1;
				break;
			}
		}
	}

	for (int i = mlen - olen; i < mlen; i++) {		// 달팽이배열에 속하지못한 평문 처리
		mdecryp4[i] = cipher[i];
	}

	printf("\n\n핑핑이2 복호문: \n");				//결과 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp4[i]);
	}
	printf("\n");

	for (int i = 0; i<l; i++) {						//동적할당 해제
		free(DSarr[i]);
	}
	free(DSarr);
	return mdecryp4;
}

int* GGE_decryption(int* cipher,  int* key1, int* key4) {
	mdecryp3 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  // bn이 키 배열 크기 보다 커지거나
			if (an % 2 == 0) {									//an이 평문 배열 크기보다 커지면 반복문 종료
				mdecryp3[an] = cipher[an] + key1[bn];
				while (mdecryp3[an] > 126) {                    // 아스키 코드값을 벗어날 경우
					mdecryp3[an] -= 95;
				}
			}
			else if (an % 2 == 1) {
				mdecryp3[an] = cipher[an] - key4[bn];
				while (mdecryp3[an] < 32) {                     // 아스키 코드값을 벗어날 경우
					mdecryp3[an] += 95;
				}
			}
		}
	}
	printf("\n낑낑이 복호문:\n");								//결과 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp3[i]);
	}
	return mdecryp3;
}

int* GGE2_decryption(int* cipher, int* key, int* key3) {
	mdecryp2 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {      // bn이 키 배열 크기 보다 커지거나
			if (an > mlen / 2) {									// an이 평문 배열 크기보다 커지면 반복문 종료
				mdecryp2[an] = cipher[an] + key[bn];
				while (mdecryp2[an] > 126) {                        // 아스키 코드값을 벗어날 경우
					mdecryp2[an] -= 95;
				}
			}
			else if (an <= mlen / 2) {
				mdecryp2[an] = cipher[an] - key3[bn];
				while (mdecryp2[an] < 32) {                         // 아스키 코드값을 벗어날 경우
					mdecryp2[an] += 95;
				}
			}
		}
	}
	printf("\n낑낑이2 복호문:\n");									//결과 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp2[i]);
	}
	printf("\n");
	return mdecryp2;
}

int* XOR_decryption(int* cipher, int* key) {
	mdecryp = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  //bn이 키 배열 크기 보다 커지거나
			mdecryp[an] = key[bn] ^ cipher[an];					//an이 평문 배열 크기보다 커지면 반복문 종료
		}
	}
	printf("\n\nXOR 복호문:\n");								//결과 출력
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp[i]);
	}
	printf("\n");
	return mdecryp;
}

int main() {
	menu_select();
	_getch();
	return 0;
}