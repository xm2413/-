#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>

#include "ui.h"
#include "data.h"

void NewPage() {
	Clear();
	char dataName[MAXNAMELEN];
	int roundCount;//�غ���
	int startTeam;//��ʼ�������飨1A 2B��
	char nameA[MAXNAMELEN];//A������
	char nameB[MAXNAMELEN];//B������
	double winRateA;//A��ʤ��
	double winRateB;//B��ʤ��
	int result[MAXLEN];

	PrintTitle("���ñ�����Ϣ");

	InputString(dataName, "���ñ������ƣ�");

	InputInt(&roundCount, "���ûغ�����");
	InputInt(&startTeam, "������������(1����A�ӣ�2����B��)��");

	InputString(nameA, "����A�����ƣ�");
	InputString(nameB, "����B�����ƣ�");

	InputDouble(&winRateA, "����A������ʤ��(0-1.00)��");
	InputDouble(&winRateB, "����B������ʤ��(0-1.00)��");

	srand(time(0));
	for (int i = 0; i < roundCount; i++) {
		double winRate = startTeam == 1 ? winRateA : winRateB;
		int temp = winRate * 100;
		if ((rand() % 100 + 1) <= temp) result[i] = 1;
		else result[i] = 2;
	}
	Data newData = CreateNewData(dataName, roundCount, startTeam, nameA, nameB, winRateA, winRateB);
	SetResult(&newData, result);
	Save(&newData);

	Fenge();
	Print("ģ��Ծ���...");
	Sleep(1000);
	Fenge();
	Print("ģ�����...");
	Fenge();
	SetWait();

	Clear();
	PrintTitle("ģ����");

	PrintDataInfo(&newData);
	Fenge();
	SetWait();


}

void LastPage() {
	Clear();
	Data data = Load();
	PrintTitle("�ϴν��");
	if (strcmp(data.dataName, nullData.dataName) == 0) {
		Print("��û��ģ���");
		Fenge();
		SetWait();
		return;
	}
	PrintDataInfo(&data);
	Fenge();
	SetWait();
}

void ExitPage() {

	exit(0);
}

void MainMenu() {
	while (1) {
		Clear();
		PrintTitle("���˵�");
		char* selections[] = {"�����µı���", "�鿴�ϴν��", "�˳�����"};
		ShowSelect(3, selections);
		int id = -1;
		InputInt(&id, "ѡ��ѡ�");

		if (id <= 0 || id >= 4) {
			Print("δ�ҵ���ѡ�������");
			Fenge();
			SetWait();
			continue;
		}

		if (id == 1) NewPage();
		else if (id == 2) LastPage();
		else if (id == 3) ExitPage();
		else printf("������1-3֮������֣�");
	}
}
void MainMenu2() {
	int index = 0;

	while (1) {
		Clear();
		PrintTitle("���˵�");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.�����µı���\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.�鿴�ϴν��\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�˳�����\n");
		if (index == 3) printf("> ");
		else printf("  ");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 2;
			else index--;
		}
		if (c == 80) { //down
			if (index == 2) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //�س����߿ո�
			if (index == 0) NewPage();
			else if (index == 1) LastPage();
			else if (index == 2) ExitPage();

		}
	}
}
int main() {
	PrintTitle("��ӭʹ��ģ��ϵͳ");
	SetWait();
	MainMenu2();
	return 0;
}
