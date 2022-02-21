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
	std::cout << " === ���� ===" << std::endl;
	std::cout << "���� �̸� : " << userName << std::endl;
	std::cout << "maxHp  : " << maxHp << std::endl;
	std::cout << "hp     : " << hp << std::endl;
	std::cout << "def    : " << def << std::endl;
	std::cout << "atk    : " << atk << std::endl;
	std::cout.precision(2);
	std::cout << "criPer : " << criPersentage << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout.precision(0);
	std::cout << "level  : " << userLevel << std::endl;
	std::cout << "���� ����ġ : " << userExp << std::endl;
	std::cout << "���� ����ġ : " << data.get(userLevel) - userExp << std::endl;

}

void EquipStat::ShowStat(char* applyEquip)
{
	std::cout << " === ��� ���� ===" << std::endl;
	std::cout << "hp     : " << hp << std::endl;
	std::cout << "def    : " << def << std::endl;
	std::cout << "atk    : " << atk << std::endl;
	std::cout.precision(2);
	std::cout << "criPer : " << criPersentage << std::endl;
	std::cout << "������ ���� : " << applyEquip << std::endl;
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
		std::cout << "�������� �Դٰ� ������ �����׿�...\n\n����� ü�� : " << hp;
		return true;
	}

	else if (atk == lifeDeath) {
		std::cout << "����� Į�ڷ縦 �� ���� �����ϴ�... �ᱹ �� �ڸ��� ����������\n\n����� ���ݷ� : " << atk;
		return true;
	}

	else if (def == lifeDeath) {
		std::cout << "�ּ��� ������ ����Դϴٸ�, ��� �� ���� ���׿�...\n\n����� ���� : " << def;
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