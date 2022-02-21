#include "setting.h"

Exp::Exp(void)
{
	FILE* exp;
	fopen_s(&exp, "exp.txt", "r");

	if (exp == NULL) {
		printf("불러오기 실패");
		exit(0);
	}

	int maxLevel;

	fscanf_s(exp, "%d\n", &maxLevel);
	maxExp = new int[maxLevel];

	for (int i = 0; i < maxLevel; i++) {
		fscanf_s(exp, "%d", &maxExp[i]);
		fgetc(exp);
	}

	fclose(exp);
}

void User::ResetExp()
{
	userLevel = 1;
	userExp = 0;
}