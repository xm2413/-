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
	int roundCount;//回合数
	int startTeam;//初始主场队伍（1A 2B）
	char nameA[MAXNAMELEN];//A队名称
	char nameB[MAXNAMELEN];//B队名称
	double winRateA;//A队胜率
	double winRateB;//B队胜率
	int result[MAXLEN];

	PrintTitle("设置比赛信息");

	InputString(dataName, "设置比赛名称：");

	InputInt(&roundCount, "设置回合数：");
	InputInt(&startTeam, "设置主场队伍(1代表A队，2代表B队)：");

	InputString(nameA, "设置A队名称：");
	InputString(nameB, "设置B队名称：");

	InputDouble(&winRateA, "设置A队主场胜率(0-1.00)：");
	InputDouble(&winRateB, "设置B队主场胜率(0-1.00)：");

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
	Print("模拟对局中...");
	Sleep(1000);
	Fenge();
	Print("模拟完成...");
	Fenge();
	SetWait();

	Clear();
	PrintTitle("模拟结果");

	PrintDataInfo(&newData);
	Fenge();
	SetWait();


}

void LastPage() {
	Clear();
	Data data = Load();
	PrintTitle("上次结果");
	if (strcmp(data.dataName, nullData.dataName) == 0) {
		Print("还没有模拟过");
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
		PrintTitle("主菜单");
		char* selections[] = {"创建新的比赛", "查看上次结果", "退出程序"};
		ShowSelect(3, selections);
		int id = -1;
		InputInt(&id, "选择选项：");

		if (id <= 0 || id >= 4) {
			Print("未找到该选项，请重试");
			Fenge();
			SetWait();
			continue;
		}

		if (id == 1) NewPage();
		else if (id == 2) LastPage();
		else if (id == 3) ExitPage();
		else printf("请输入1-3之间的数字！");
	}
}
void MainMenu2() {
	int index = 0;

	while (1) {
		Clear();
		PrintTitle("主菜单");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.创建新的比赛\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.查看上次结果\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.退出程序\n");
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
		if (c == 13 || c == ' ') { //回车或者空格
			if (index == 0) NewPage();
			else if (index == 1) LastPage();
			else if (index == 2) ExitPage();

		}
	}
}
int main() {
	PrintTitle("欢迎使用模拟系统");
	SetWait();
	MainMenu2();
	return 0;
}
