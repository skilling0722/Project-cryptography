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

void gotoxy(int x, int y) {									//��ǥ ����
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void menu() {													//�ܼ�â �޴� ����Ʈ
	gotoxy(7, 0);
	puts("11�� ������Ʈ");
	gotoxy(2, 1);
	puts("-----------------------");
	gotoxy(3, 3);
	puts("Ű, �� �Է��ϱ�");
	gotoxy(3, 4);
	puts("��ȣȭ ����");
	gotoxy(3, 5);
	puts("��ȣȭ ����");
	gotoxy(3, 6);
	puts("����");
}

void menu_star(int y) {										//�޴� ���� ��
	gotoxy(0, y);
	puts("*");
}

void input_exit() {											//Ű �Է½� �޴� exit
	int key = 0;
	printf("\n\n �����̽��ٸ� �Է��Ͽ� �����ϼ���.\n");
	while (1) {
		key = _getch();
		if (key == 32) {
			system("cls");
			menu_select();
			break;
		}
	}
}

void menu_select() {											//�޴�
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
					printf("\n------------��ȣȭ------------\n\n");
					printf("��: \n");
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
					printf("�򹮰� Ű�� �Է¹��� �Ŀ� �õ��ϼ���.\n");
					input_exit();
					break;
				}
			case 5:
				system("cls");
				if (input_done == 1 && encryption_done == 1) {
					printf("\n\n------------��ȣȭ------------");
					mdecryp  = XOR_decryption(mcryp5, key3);
					mdecryp2 = GGE2_decryption(mdecryp, key2, key3);
					mdecryp3 = GGE_decryption(mdecryp2, key1, key4);
					mdecryp4 = PPE2_decryption(mdecryp3, klen);
					mdecryp5 = PPE1_decryption(mdecryp4, key4);
					printf("\n��: \n");
					for (int i = 0; i < mlen; i++) {
						printf("%c", m[i]);
					}
					for (int i = 0; i < mlen; i++) {
						if (m[i] == mdecryp5[i]) {
							if (i == mlen - 1) {
								printf("\n\n�򹮰� ��ȣ���� ��ġ�մϴ�.");
							}
						}
						else printf("\n\n�򹮰� ��ȣ���� ��ġ�����ʽ��ϴ�.");
					}
					input_exit();
					break;
				}
				else {
					printf("��ȣȭ ������ ��ģ �Ŀ� �õ��ϼ���.\n");
					input_exit();
					break;
				}
			case 6:
				for (int q = 3; q > 0; q--) {
					system("cls");
					printf("\n%d�� �ڿ� ����˴ϴ�.\n", q);
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

	printf("Ű�� �Է��ϼ���: ");								//KEY �Է�
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

	Key_Encryption();											//KEY ��ȣȭ

	printf("\n\nkey1: ");										//KEY1 ���
	for (int i = 0; i < klen; i++) {
		printf("%c", key1[i]);
	}
	printf("\nkey2: ");										//KEY2 ���
	for (int i = 0; i < klen; i++) {
		printf("%c", key2[i]);
	}
	printf("\nkey3: ");										//KEY3 ���
	for (int i = 0; i < klen; i++) {
		printf("%c", key3[i]);
	}
	printf("\nkey4: ");										//KEY4 ���
	for (int i = 0; i < klen; i++) {
		printf("%c", key4[i]);
	}

	printf("\n\n���� �Է��ϼ���: ");
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

	printf("\n\n��: \n");									//�� ���
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
		while (key1[i] > 126) {                        // �ƽ�Ű �ڵ尪�� ��� ���
			key1[i] -= 95;
		}
	}
	for (int j = 0; j < klen; j++) {
		key2[j] = okey[j] - (klen % 95);
		while (key2[j] < 32) {                        // �ƽ�Ű �ڵ尪�� ��� ���
			key2[j] += 95;
		}
	}
}

void polyalphabetic(int *okey, int* key1, int* key2) {
	key3 = (int *)malloc(klen * sizeof(int));
	key4 = (int *)malloc(klen * sizeof(int));
	for (int an = 0; an < klen;) {
		for (int bn = 0; bn < klen && an < klen; an++, bn++) {  
			int m = okey[bn] - 32;                            // Ű�� ������� ũ�� ���
			int n = key1[an] + m;								// Ű�� ����� ũ�⸸ŭ �� ����Ʈ
			if (n > 126) {									// �ƽ�Ű �ڵ尪�� ��� ���
				n -= 95;										// �ƽ�Ű �ڵ��� ó������ ���ư�(��ɾ� ��ŵ)
			}
			key3[an] = n;										// ����Ʈ�� �� ����
		}
	}

	for (int an = 0; an < klen;) {
		for (int bn = 0; bn < klen && an < klen; an++, bn++) {  
			int m = okey[bn] - 32;                            // Ű�� ������� ũ�� ���
			int n = key2[an] + m;								// Ű�� ����� ũ�⸸ŭ �� ����Ʈ
			if (n > 126) {									// �ƽ�Ű �ڵ尪�� ��� ���
				n -= 95;										// �ƽ�Ű �ڵ��� ó������ ���ư�(��ɾ� ��ŵ)
			}
			key4[an] = n;										// ����Ʈ�� �� ����
		}
	}
}

void Key_Encryption() {
	KCP(okey, klen);
	polyalphabetic(okey, key1, key2);
}

int* PPE2_encryption(int* plain, int klen) {
	mcryp2 = (int *)malloc(mlen * sizeof(int));
	int l = klen % 3 + 2;							// Ű�� ���̸� �̿��� �����̹迭 ũ�� ���
	
	int **Sarr;										// 2���� �迭 �����Ҵ�
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
			switch (rot % 4)                        // ȸ������ 4�ܰ�� ���� ���� - �캯 
			{										//	- �Ʒ��� - �º� ������ ����
			case 0:									// ����
				for (j = lcol; j < l - rcol; j++) {
					Sarr[trow][j] = plain[an];
					an += 1;
				}
				j -= 1;                             //�ݺ��� ������ j�� �ѹ� �� �������Ƿ� �ٽ� ���ش�
				rot += 1;                           //���� ���� �� ���� ������ ȸ��
				trow += 1;                          // ���� ���� �ٽ� ������ �ʵ��� top row ǥ��
				break;
			case 1:									// �캯
				for (k = trow; k < l - brow; k++) {
					Sarr[k][j] = plain[an];             // j�� ���� ������ �ݺ��� �ٱ��� �����Ƿ� 
					an += 1;						// �ʱ�ȭ�����ʰ� ���� �ܰ��� �� ����
				}
				k -= 1;
				rot += 1;
				rcol += 1;
				break;
			case 2:									// �Ʒ���
				for (j = (l - 1) - rcol; j >= lcol; j--) {
					Sarr[k][j] = plain[an];
					an += 1;
				}
				j += 1;
				rot += 1;
				brow += 1;
				break;
			case 3:									// �º�
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

		for (int m = 0; m < l; m++) {				//������� ������ �迭�� ��ȣ�� �迭�� ����
			for (int n = 0; n < l; n++) {
				mcryp2[an2] = Sarr[m][n];
				an2 += 1;
			}
		}
	}
	for (int i = mlen - olen; i < mlen; i++) {		//������ �迭�� ���������� �� ó��
		mcryp2[i] = plain[i];
	}

	printf("\n������2 ��ȣ�� : \n");
	for (int i = 0; i < mlen; i++) {				//��� ���
		printf("%c", mcryp2[i]);
	}
	printf("\n");

	for (int i = 0; i < l; i++) {					// �迭 �����Ҵ� �ʱ�ȭ
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
			switch (rot % 4)                        // ȸ������ 4�ܰ�� ���� ���� - �캯 
			{										//	- �Ʒ��� - �º� ������ ����
			case 0:									// ����
				for (j = lcol; j < l[i] - rcol; j++) {
					Sarr[trow][j] = plain[an];
					an += 1;
				}
				j -= 1;                             //�ݺ��� ������ j�� �ѹ� �� �������Ƿ� �ٽ� ���ش�
				rot += 1;                           //���� ���� �� ���� ������ ȸ��
				trow += 1;                          // ���� ���� �ٽ� ������ �ʵ��� top row ǥ��
				break;
			case 1:									// �캯
				for (k = trow; k < l[i] - brow; k++) {
					Sarr[k][j] = plain[an];             // j�� ���� ������ �ݺ��� �ٱ��� �����Ƿ� 
					an += 1;						// �ʱ�ȭ�����ʰ� ���� �ܰ��� �� ����
				}
				k -= 1;
				rot += 1;
				rcol += 1;
				break;
			case 2:									// �Ʒ���
				for (j = (l[i] - 1) - rcol; j >= lcol; j--) {
					Sarr[k][j] = plain[an];
					an += 1;
				}
				j += 1;
				rot += 1;
				brow += 1;
				break;
			case 3:									// �º�
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

		for (int m = 0; m < l[i]; m++) {				//������� ������ �迭�� ��ȣ�� �迭�� ����
			for (int n = 0; n < l[i]; n++) {
				mcryp[an2] = Sarr[m][n];
				an2 += 1;
			}
		}
		for (int j = 0; j < l[i]; j++) {					// �迭 �����Ҵ� �ʱ�ȭ
			free(Sarr[j]);
		}
		free(Sarr);
	}

	for (int i = mlen - olen; i < mlen; i++) {		//������ �迭�� ���������� �� ó��
		mcryp[i] = plain[i];
	}

	printf("\n\n������1 ��ȣ�� : \n");
	for (int i = 0; i < mlen; i++) {				//��� ���
		printf("%c", mcryp[i]);
	}
	printf("\n");

	return mcryp;
}

int* GGE_encryption(int* plain, int* key1, int* key4) {
	mcryp2 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  // bn�� Ű �迭 ũ�� ���� Ŀ���ų�
			if (an % 2 == 0) {									// an�� �� �迭 ũ�⺸�� Ŀ���� �ݺ��� ����
				mcryp2[an] = plain[an] - key1[bn];
				while (mcryp2[an] < 32) {                       // �ƽ�Ű �ڵ尪�� ��� ���
					mcryp2[an] += 95;
				}
			}
			else if (an % 2 == 1) {
				mcryp2[an] = plain[an] + key4[bn];
				while (mcryp2[an] > 126) {                      // �ƽ�Ű �ڵ尪�� ��� ���
					mcryp2[an] -= 95;
				}
			}
		}
	}
	printf("\n������1 ��ȣ�� : \n");							// ��� ���
	for (int i = 0; i < mlen; i++) {
		printf("%c", mcryp2[i]);
	}
	return mcryp2;
}

int* GGE2_encryption(int* plain, int* key2, int* key3) {
	mcryp3 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  // bn�� Ű �迭 ũ�� ���� Ŀ���ų�
			if (an > mlen / 2) {								// an�� �� �迭 ũ�⺸�� Ŀ���� �ݺ��� ����
				mcryp3[an] = plain[an] - key2[bn];
				while (mcryp3[an] < 32) {                       // �ƽ�Ű �ڵ尪�� ��� ���
					mcryp3[an] += 95;
				}
			}
			else if (an <= mlen / 2) {
				mcryp3[an] = plain[an] + key3[bn];
				while (mcryp3[an] > 126) {                      // �ƽ�Ű �ڵ尪�� ��� ���
					mcryp3[an] -= 95;
				}
			}
		}
	}
	printf("\n\n������2 ��ȣ�� : \n");							//��� ���
	for (int i = 0; i < mlen; i++) {
		printf("%c", mcryp3[i]);
	}
	return mcryp3;
}

int* XOR_encryption(int* plain, int* key) {
	mcryp4 = (int *)malloc(mlen * sizeof(int));
	printf("\n\nXOR ��ȣ��: \n");

	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {      // bn�� Ű �迭 ũ�� ���� Ŀ���ų�
			mcryp4[an] = key[bn] ^ plain[an];						// an�� �� �迭 ũ�⺸�� Ŀ���� �ݺ��� ����
			printf("%c ", mcryp4[an]);								// ��� ���
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
			DSarr = (int**)malloc(sizeof(int *)*l[i]);			// ��ȣȭ�� �̿��� 2���� �迭 �����Ҵ�
			for (int j = 0; j < l[i]; j++) {
				DSarr[j] = (int*)malloc(sizeof(int) *l[i]);
			}

			for (int m = 0; m < l[i]; m++) {
				for (int n = 0; n < l[i]; n++) {			// ��ȣ�� ����� l*l ��Ŀ� ������� ����
					DSarr[m][n] = cipher[dan];
					dan += 1;
				}
			}
			int j = 0, k = 0;
			int trow = 0, brow = 0;
			int lcol = 0, rcol = 0;
			for (int rot = 0; trow + brow < l[i] && lcol + rcol < l[i];) {
				switch (rot % 4)                        // ȸ������ 4�ܰ�� ���� ���� - �캯 
				{										// - �Ʒ��� - �º� ������ ����
				case 0:									// ����
					for (j = lcol; j < l[i] - rcol; j++) {
						mdecryp5[dan2] = DSarr[trow][j];
						dan2 += 1;
					}
					j -= 1;                             //�ݺ��� ������ j�� �ѹ� �� �������Ƿ� �ٽ� ���ش�
					rot += 1;                           //���� ���� �� ���� ������ ȸ��
					trow += 1;                          // ���� ���� �ٽ� ������ �ʵ��� top row ǥ��
					break;
				case 1:									// �캯
					for (k = trow; k < l[i] - brow; k++) {
						mdecryp5[dan2] = DSarr[k][j];   // j�� ���� ������ �ݺ��� �ٱ��� �����Ƿ� 
						dan2 += 1;						// �ʱ�ȭ�����ʰ� ���� �ܰ��� �� ����
					}
					k -= 1;
					rot += 1;
					rcol += 1;
					break;
				case 2:									// �Ʒ���
					for (j = (l[i] - 1) - rcol; j >= lcol; j--) {
						mdecryp5[dan2] = DSarr[k][j];
						dan2 += 1;
					}
					j += 1;
					rot += 1;
					brow += 1;
					break;
				case 3:									// �º�
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

			for (int j = 0; j<l[i]; j++) {				//�����Ҵ� ����
				free(DSarr[j]);
			}
			free(DSarr);
		}

		for (int i = mlen - olen; i < mlen; i++) {		// �����̹迭�� ���������� �� ó��
			mdecryp5[i] = cipher[i];
		}

		printf("\n������1 ��ȣ��: \n");					//��� ���
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
	Sarr = (int**)malloc(sizeof(int *)*l);			// 2���� �迭 �����Ҵ�
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
	DSarr = (int**)malloc(sizeof(int *)*l);			// ��ȣȭ�� �̿��� 2���� �迭 �����Ҵ�
	for (int i = 0; i < l; i++) {
		DSarr[i] = (int*)malloc(sizeof(int) *l);
	}

	for (int i = 0; i < div; i++) {
		for (int m = 0; m < l; m++) {
			for (int n = 0; n < l; n++) {			// ��ȣ�� ����� l*l ��Ŀ� ������� ����
				DSarr[m][n] = cipher[dan];
				dan += 1;
			}
		}

		int j = 0, k = 0;
		int trow = 0, brow = 0;
		int lcol = 0, rcol = 0;

		for (int rot = 0; trow + brow < l && lcol + rcol < l;) {
			switch (rot % 4)                        // ȸ������ 4�ܰ�� ���� ���� - �캯 
			{										// - �Ʒ��� - �º� ������ ����
			case 0:									// ����
				for (j = lcol; j < l - rcol; j++) {
					mdecryp4[dan2] = DSarr[trow][j];
					dan2 += 1;
				}
				j -= 1;                             //�ݺ��� ������ j�� �ѹ� �� �������Ƿ� �ٽ� ���ش�
				rot += 1;                           //���� ���� �� ���� ������ ȸ��
				trow += 1;                          // ���� ���� �ٽ� ������ �ʵ��� top row ǥ��
				break;
			case 1:									// �캯
				for (k = trow; k < l - brow; k++) {
					mdecryp4[dan2] = DSarr[k][j];   // j�� ���� ������ �ݺ��� �ٱ��� �����Ƿ� 
					dan2 += 1;						// �ʱ�ȭ�����ʰ� ���� �ܰ��� �� ����
				}
				k -= 1;
				rot += 1;
				rcol += 1;
				break;
			case 2:									// �Ʒ���
				for (j = (l - 1) - rcol; j >= lcol; j--) {
					mdecryp4[dan2] = DSarr[k][j];
					dan2 += 1;
				}
				j += 1;
				rot += 1;
				brow += 1;
				break;
			case 3:									// �º�
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

	for (int i = mlen - olen; i < mlen; i++) {		// �����̹迭�� ���������� �� ó��
		mdecryp4[i] = cipher[i];
	}

	printf("\n\n������2 ��ȣ��: \n");				//��� ���
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp4[i]);
	}
	printf("\n");

	for (int i = 0; i<l; i++) {						//�����Ҵ� ����
		free(DSarr[i]);
	}
	free(DSarr);
	return mdecryp4;
}

int* GGE_decryption(int* cipher,  int* key1, int* key4) {
	mdecryp3 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  // bn�� Ű �迭 ũ�� ���� Ŀ���ų�
			if (an % 2 == 0) {									//an�� �� �迭 ũ�⺸�� Ŀ���� �ݺ��� ����
				mdecryp3[an] = cipher[an] + key1[bn];
				while (mdecryp3[an] > 126) {                    // �ƽ�Ű �ڵ尪�� ��� ���
					mdecryp3[an] -= 95;
				}
			}
			else if (an % 2 == 1) {
				mdecryp3[an] = cipher[an] - key4[bn];
				while (mdecryp3[an] < 32) {                     // �ƽ�Ű �ڵ尪�� ��� ���
					mdecryp3[an] += 95;
				}
			}
		}
	}
	printf("\n������ ��ȣ��:\n");								//��� ���
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp3[i]);
	}
	return mdecryp3;
}

int* GGE2_decryption(int* cipher, int* key, int* key3) {
	mdecryp2 = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {      // bn�� Ű �迭 ũ�� ���� Ŀ���ų�
			if (an > mlen / 2) {									// an�� �� �迭 ũ�⺸�� Ŀ���� �ݺ��� ����
				mdecryp2[an] = cipher[an] + key[bn];
				while (mdecryp2[an] > 126) {                        // �ƽ�Ű �ڵ尪�� ��� ���
					mdecryp2[an] -= 95;
				}
			}
			else if (an <= mlen / 2) {
				mdecryp2[an] = cipher[an] - key3[bn];
				while (mdecryp2[an] < 32) {                         // �ƽ�Ű �ڵ尪�� ��� ���
					mdecryp2[an] += 95;
				}
			}
		}
	}
	printf("\n������2 ��ȣ��:\n");									//��� ���
	for (int i = 0; i < mlen; i++) {
		printf("%c", mdecryp2[i]);
	}
	printf("\n");
	return mdecryp2;
}

int* XOR_decryption(int* cipher, int* key) {
	mdecryp = (int *)malloc(mlen * sizeof(int));
	for (int an = 0; an < mlen;) {
		for (int bn = 0; bn < klen && an < mlen; an++, bn++) {  //bn�� Ű �迭 ũ�� ���� Ŀ���ų�
			mdecryp[an] = key[bn] ^ cipher[an];					//an�� �� �迭 ũ�⺸�� Ŀ���� �ݺ��� ����
		}
	}
	printf("\n\nXOR ��ȣ��:\n");								//��� ���
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