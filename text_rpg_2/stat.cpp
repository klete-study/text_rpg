#include "setting.h"

void User::SetStat(char* name)
{
	srand(time(NULL));
	memcpy(userName, name, gStrMax);
	maxHp = rand() % 100 + 100;
	atk = rand() % 20 + 15;
	//atk = 0;
	def = rand() % 20 + 10;
	hp = maxHp;
	cri = 0;
	criPersentage = 0;
}

void User::ShowStat(Exp& data)
{
	std::cout << " === 스탯 ===" << std::endl;
	std::cout << "유저 이름 : " << userName << std::endl;
	std::cout << "maxHp  : " << maxHp << std::endl;
	std::cout << "hp     : " << hp << std::endl;
	std::cout << "def    : " << def << std::endl;
	std::cout << "atk    : " << atk << std::endl;
	std::cout.precision(2);
	std::cout << "criPer : " << criPersentage << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout.precision(0);
	std::cout << "level  : " << userLevel << std::endl;
	std::cout << "현재 경험치 : " << userExp << std::endl;
	std::cout << "남은 경험치 : " << data.get(userLevel) - userExp << std::endl;

}

void EquipStat::ShowStat(char* applyEquip)
{
	std::cout << " === 장비 스탯 ===" << std::endl;
	std::cout << "hp     : " << hp << std::endl;
	std::cout << "def    : " << def << std::endl;
	std::cout << "atk    : " << atk << std::endl;
	std::cout.precision(2);
	std::cout << "criPer : " << criPersentage << std::endl;
	std::cout << "착용한 무기 : " << applyEquip << std::endl;
}

void User::PlusHp(Object* data)
{
	hp = data->GetValue(statHp);

	if (data->GetValue(statHp) >= 1000 || hp >= maxHp) {
		hp = maxHp;
	}
}

bool User::CheckDeath() {

	std::cout << "\n\n";

	if (hp == lifeDeath) {
		std::cout << "독버섯만 먹다가 게임이 끝났네요...\n\n당신의 체력 : " << hp;
		return true;
	}

	else if (atk == lifeDeath) {
		std::cout << "당신은 칼자루를 들 힘도 없습니다... 결국 그 자리에 쓰러졌군요\n\n당신의 공격력 : " << atk;
		return true;
	}

	else if (def == lifeDeath) {
		std::cout << "최선의 공격은 방어입니다만, 방어 할 수가 없네요...\n\n당신의 방어력 : " << def;
		return true;
	}

	return false;
}

int EquipStat::GetValue(enum estat num)
{
	switch (num)
	{
	case statAtk:
		return atk;
	case statDef:
		return def;
	case statCri:
		return cri;
	case statCriPesentage:
		return criPersentage;
	default:
		break;
	}
	return 0;
}

int Object::GetValue(enum estat num)
{
	switch (num)
	{
	case statHp:
		return hp;
	case statAtk:
		return atk;
	case statDef:
		return def;
	case statCri:
		return cri;
	case statCriPesentage:
		return criPersentage;
	default:
		break;
	}
	return 0;
}

int Monster::GetValue(enum estat num)
{
	switch (num)
	{
	case statHp:
		return hp;
	case statAtk:
		return atk;
	case statDef:
		return def;
	case statExp:
		return exp;
	default:
		break;
	}
	return 0;
}