
const int MAXNAMELEN = 101;//名称最大长度 
const int MAXLEN = 10001;//最大单轮模拟次数 
struct Data{//每个Data存储一次模拟的结果
	char dataName[MAXNAMELEN];
	int roundCount;//回合数 
	int startTeam;//初始主场队伍（1A 2B） 
	char nameA[MAXNAMELEN];//A队名称 
	char nameB[MAXNAMELEN];//B队名称 
	double winRateA;//A队胜率
	double winRateB;//B队胜率
	
	int result[MAXLEN];//每轮比赛胜利方（1A，2B） 
	 
};
Data nullData = {"NULL", 0, 0, "NULL", 0, 0, 0, 0};

Data CreateNewData(char* dataName, int roundCount, int startTeam, char* nameA, char* nameB, double winRateA, double winRateB){
	Data data;
	strcpy(data.dataName, dataName);
	data.roundCount = roundCount;
	data.startTeam = startTeam;
	strcpy(data.nameA, nameA);
	strcpy(data.nameB, nameB);
	data.winRateA = winRateA;
	data.winRateB = winRateB;
	
	return data;
}

void SetResult(Data* data, int* resultArray){
	for(int i = 0; i < data->roundCount; i++){
		data->result[i] = resultArray[i];
	}
}

void PrintDataInfo(Data *data){
	printf("赛前统计:\n");
	printf("比赛名称：%s\n", data->dataName);
	printf("比赛双方：%s(主场胜率%.2lf) VS %s(主场胜率%.2lf)\n", data->nameA, data->winRateA, data->nameB, data->winRateB);
	printf("回合数：%d\n", data->roundCount);
	printf("主场队伍：%s\n", (data->startTeam == 1) ? data->nameA : data->nameB);
	printf("比赛结果:\n");
	int aWin = 0, bWin = 0;
	for(int i = 0; i < data->roundCount; i++){
		if(data->result[i] == 1) aWin++;
		if(data->result[i] == 2) bWin++;
	}
	printf("队伍 %s：胜利场数：%d，对局胜率：%.2lf\n", data->nameA, aWin, (double)aWin / data->roundCount);
	printf("队伍 %s：胜利场数：%d，对局胜率：%.2lf\n", data->nameB, bWin, (double)bWin / data->roundCount);
	printf("最终赢家：%s\n", aWin == bWin ? "平局" : aWin > bWin ? data->nameA : data->nameB); 
}


//初始化，程序开始时，读取保存的文件，将其添加到lst数组中 
Data Load(){
	FILE *pf = fopen("Data.sav", "r");
	if(pf != NULL){
		char dataName[MAXNAMELEN];
		int roundCount;//回合数 
		int startTeam;//初始主场队伍（1A 2B） 
		char nameA[MAXNAMELEN];//A队名称 
		char nameB[MAXNAMELEN];//B队名称 
		double winRateA;//A队胜率
		double winRateB;//B队胜率
		
		int result[MAXLEN];
		
		fscanf(pf, "%s", dataName);
		fscanf(pf, "%d", &roundCount);
		fscanf(pf, "%d", &startTeam);
		fscanf(pf, "%s", nameA);
		fscanf(pf, "%s", nameB);
		fscanf(pf, "%lf", &winRateA);
		fscanf(pf, "%lf", &winRateB);
		
		
		for(int i = 0; i < roundCount; i++){
			fscanf(pf, "%d", &result[i]);
		}
		
		Data loadData = CreateNewData(dataName, roundCount, startTeam, nameA, nameB, winRateA, winRateB);
		SetResult(&loadData, result);
		
		fclose(pf);
		return loadData;
	}
	else{
		fclose(pf);
		return nullData;
	}
}

//存储，把当前的列表存储到程序外的文件中（覆盖上一个版本的文件） 
void Save(Data* data){
	FILE *pf = fopen("Data.sav", "w");
	fprintf(pf, "%s\n%d\n%d\n%s\n%s\n%lf\n%lf\n", data->dataName, data->roundCount, data->startTeam, data->nameA, data->nameB, data->winRateA, data->winRateB); 
	for(int i = 0; i < data->roundCount; i++){
		fprintf(pf, "%d ", data->result[i]);
	}
	fclose(pf);
}

