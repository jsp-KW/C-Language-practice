#include <stdio.h>
#include <string.h>

#pragma warning(disable: 4996)

struct phone_book {
	char name[25];
	char phone_num[20];
	int short_num;
};

int count = 0;

void menu(); // 메뉴 선택 함수
void print(struct phone_book* list); // 해당하는 전화번호부 출력
void add(struct phone_book li[]);// 전화번호부에 새로운 항목 추가
void search_name(struct phone_book li[], char* s); // 이름으로 항목 찾기
void search_phone(struct phone_book li[], char* s);// 전화번호로 항목 찾기
void search_short(struct phone_book li[], int short_num);// 단축키로 항목 찾기
void delete (struct phone_book li[]);// 항목 삭제하기
void update(struct phone_book li[]);// 항목 수정하기
void printAll(struct phone_book li[]);// 모두 출력하기

int main() {
	int choice = 0;

	struct phone_book li[50] = { "\0", };


	while (1) {
		menu();
		printf("선택: ");
		scanf("%d", &choice);

		while (getchar() != '\n');
		switch (choice)
		{
		case 1:
			add(&li);
			break;
		case 2:
		{
			char name[25];
			printf("검색할 이름을 입력하세요: ");
			gets(name);
			search_name(li, name);
		}
		break;
		case 3:
		{
			char phone[20];
			printf("검색할 전화번호를 입력하세요: ");
			gets(phone);
			search_phone(li, phone);
		}
		break;
		case 4:
		{
			int short_num;
			printf("검색할 단축키를 입력하세요: ");
			scanf("%d", &short_num);
			search_short(li, short_num);
		}
		break;

		case 5:
			delete(li);
			break;

		case 6:
			update(li);
			break;

		case 7:
			printAll(li);
			break;

		default:
			printf("잘못된 선택입니다. 다시 선택하세요.\n");
			break;
		}
	}

	return 0;
}


void menu() {
	system("cls");

	printf("1. 전화번호 저장\n");
	printf("2. 이름으로 검색\n");
	printf("3. 전화번호로 검색\n");
	printf("4. 전화번호 단축키로 검색\n");
	printf("5. 전화번호 삭제하기\n");
	printf("6. 전화번호 수정하기\n");
	printf("7. 전화번호 모두 보기\n\n");

}


void print(struct phone_book* list) {
	printf("이름 : %-10s 전화번호: %-20s 단축키: %d\n", list->name, list->phone_num, list->short_num);
}

void add(struct phone_book li[]) {

	if (count == 50) {
		printf("전화번호를 추가하기엔 용량이 꽉 찻습니다.");
		return;
	}

	int idx = 0;
	int name_len = 0;

	printf("이름입력: ");

	while (1) { //fgets함수를 이용하여도 가능.
		char ch = getchar();
		if (ch == '\n' || name_len >= 25) {
			li[count].name[idx] = '\0';
			break;
		}

		li[count].name[idx] = ch;
		name_len++;
		idx++;
	}


	if (idx == 0) {
		printf("이름이 입력되지 않았습니다. 전화번호 추가를 취소합니다.\n\n");
		while (getchar() != '\n');
		return;
	}

	for (int i = 0; i < count; i++) {
		if (strcmp(li[i].name, li[count].name) == 0) {
			printf("입력하신 이름이 이미 존재합니다.\n 다른 이름으로 설정하세요.\n\n");
			add(li);
			return;
		}
	}


	int dup_phone = 0;
	while (1) {
		dup_phone = 0;
		printf("전화번호 입력: ");
		gets(li[count].phone_num);

		for (int i = 0; i < count; i++) {
			if (strcmp(li[i].phone_num, li[count].phone_num) == 0) {
				printf("입력하신 전화번호가 이미 존재합니다.\n 다른 전화번호로 설정하세요.\n\n");
				dup_phone = 1;
				break;
			}
		}

		if (!dup_phone) {
			break;
		}


	}

	// 단축키 중복검사.
	int duplicated = 0;

	while (1) {

		duplicated = 0;
		printf("단축키 설정(설정시 0~9의 조합으로 입력해주세요): ");
		int num = 0;
		scanf("%d", &num);

		for (int i = 0; i < count; i++) {
			if (li[i].short_num == num) {
				printf("입력하신 단축키가 이미 존재합니다.\n 다른 단축키로 설정하세요.\n\n");
				duplicated = 1;
				break;
			}
		}

		if (!duplicated) {
			li[count].short_num = num;
			break;
		}

	}

	print(&li[count]);
	count++;

	system("pause");

}

void search_name(struct phone_book li[], char* s)
{
	int find = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(li[i].name, s) == 0) {

			printf("이름과 일치하는 전화번호부를 찾았습니다.\n");
			print(&li[i]);
			find = 1;
			break;
		}
	}

	if (!find) {
		printf("입력하신 이름이 일치하는 전화번호부가 존재하지 않습니다.\n\n");

	}
	system("pause");

}


void search_phone(struct phone_book li[], char* s) {

	int find = 0;
	for (int i = 0; i < count; i++) {
		if (strcmp(li[i].phone_num, s) == 0) {
			printf("전화번호부를 찾았습니다.\n");
			print(&li[i]);
			find = 1;
			break;
		}
	}

	if (!find) {
		printf("입력하신 전화번호부와 일치하는 전화번호부가 존재하지 않습니다.\n\n");
	}

	system("pause");
}

void search_short(struct phone_book li[], int short_num) {

	if (short_num < 0) {
		printf("음수 단축키는 존재하지 않습니다.\n\n");
		return;
	}

	int find = 0;

	for (int i = 0; i < count; i++) {
		if (li[i].short_num == short_num) {
			printf("단축키와 일치하는 전화번호부를 찾았습니다.\n\n");
			print(&li[i]);
			find = 1;
			break;
		}
	}

	if (!find) {
		printf("입력하신 전화번호 단축키와 일치하는 전화번호부가 존재하지 않습니다.\n\n");
	}

	system("pause");
}


void delete (struct phone_book li[]) {
	char name[25];
	printf("삭제할 전화번호부에 저장된 이름을 입력하세요: ");
	gets(name);

	int found = 0;

	for (int i = 0; i < count; i++) {
		if (strcmp(li[i].name, name) == 0) {
			found = 1;
			for (int j = i; j < count - 1; j++) {
				strcpy(li[j].name, li[j + 1].name);
				strcpy(li[j].phone_num, li[j + 1].phone_num);
				li[j].short_num = li[j + 1].phone_num;
			}
			count--;
			printf("삭제완료\n");
		}
	}

	if (!found) {
		printf("입력한 이름과 일치하는 전화번호부가 존재하지 않습니다.\n\n");
	}

	system("pause");


}

void update(struct phone_book li[]) {

	char name[25];
	printf("수정할 항목의 이름을 입력하세요");
	gets(name);

	int found = 0;
	int del_idx = 0;

	for (int i = 0; i < count; i++) {
		if (strcmp(li[i].name, name) == 0) {
			del_idx = i;
			found = 1;
			break;
		}
	}

	printf("수정할 항목의 인덱스 :%d\n\n", del_idx);


	if (!found) {
		printf("입력하신 이름과 일치하는 전화번호가 존재하지 않습니다.\n\n");
	}
	else {

		int phone_dup = 0;
		int short_dup = 0;

		while (1) {
			phone_dup = 0;
			printf("새로운 전화번호를 입력하세요: ");
			scanf("%s", li[del_idx].phone_num);

			for (int i = 0; i < count; i++) {
				if (i != del_idx) {
					if (strcmp(li[i].phone_num, li[del_idx].phone_num) == 0) {
						phone_dup = 1;
						break;
					}
				}
			}


			if (!phone_dup) {
				printf("전화번호 수정완료\n\n");
				break;
			}
			else {
				printf("입력한 전화번호가 이미 존재합니다.\n\n");
			}


		}
		while (1) {

			short_dup = 0;
			printf("새로운 단축키를 입력하세요: ");
			scanf("%d", &li[del_idx].short_num);

			for (int i = 0; i < count; i++) {
				if (i != del_idx) {
					if (li[i].short_num == li[del_idx].short_num) {
						short_dup = 1;
						break;
					}
				}
			}

			if (!short_dup) {
				printf("단축키 수정완료\n\n");
				break;
			}
			else {
				printf("입력한 단축키가 이미 존재합니다.\n\n");
			}

		}

		printf("항목 수정이 완료되었습니다.\n");


	}

	system("pause");
}


void printAll(struct phone_book li[]) {

	printf("===================전화번호부 목록==============================\n\n");

	if (count >= 1) {
		for (int i = 0; i < count; i++) {
			printf("이름 : %-10s 전화번호: %-20s 단축키: %d\n", li[i].name, li[i].phone_num, li[i].short_num);
		}
	}

	else
		printf("아직까지 저장된 전화번호가 없습니다 \n\n");

	printf("================================================================\n\n\n");

	system("pause");
}
