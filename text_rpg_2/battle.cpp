#include "setting.h"

Monster::Monster()
{
	int choice = rand() % monsterMax;

	if (choice == monsterZombie) {
		hp = rand() % 30 + 10;
		atk = rand() % 10 + 1;
		def = rand() % 10 + 1;
		exp = hp * 0.5 + atk * 0.5 + def * 0.3;
		printf("�����ϰ� ���� ���� �������ϴ�!\n������ �����մϴ�\n");
	}

	else if (choice == monsterDevilBlood) {
		hp = rand() % 50 + 40;
		atk = rand() % 10 + 20;
		def = rand() % 15 + 5;
		exp = hp * 0.6 + atk * 0.6 + def * 0.4;
		printf("��� ���� �� ���� �Ǹ� �Ǻ��̸� �������ϴ�!\n������ �����մϴ�\n");
	}

	else if (choice == monsterDragon) {
		hp = rand() % 80 + 70;
		atk = rand() % 20 + 15;
		def = rand() % 20 + 15;
		exp = hp * 0.8 + atk * 0.7 + def * 0.5;
		printf("���� ũ���� ���� �������ϴ�!\n������ �����մϴ�\n");
	}
}

bool User::DoBattle(int itemCount, list* src, Monster& monster)
{
	while (true) {
		int choice;

		Sleep(1000);
		system("cls");

		std::cout << userName << "�� ü�� : " << hp << ", ������ ü�� : " << monster.GetValue(statHp);
		std::cout << "\n\n��� �Ͻðڽ��ϱ�?\n------------------------\n";
		std::cout << "1. �ο�� 2. �������� ����Ѵ� 3. ����ģ��.\n\n";
		std::cout << "���� : ";
		std::cin >> choice;

		if (choice == 1) {
			int setCriPersentage = rand() % 101 + 0;
			int userAtk;

			if (100 - setCriPersentage <= userEquip.GetValue(statCriPesentage)) {
				userAtk = atk + userEquip.GetValue(statAtk) + (atk + userEquip.GetValue(statAtk)) * userEquip.GetValue(statCri) * 0.01 - monster.GetValue(statDef) * 0.5f;
			}

			else {
				userAtk = atk + userEquip.GetValue(statAtk) - (monster.GetValue(statDef) * 0.5f);
			}

			int monsterAtk = monster.GetValue(statAtk) - (def + userEquip.GetValue(statDef)) * 0.3f;


			std::cout << "�ο����...\n\n";

			monster.DamageHp(userAtk);
			hp -= monsterAtk;

			if (monster.GetValue(statHp) <= lifeDeath) {
				userExp += monster.GetValue(statExp);
				return true;
			}

			else if (hp <= lifeDeath) {
				return false;
			}
		}

		else if (choice == 2) {

			int choiceItem;
			int selectInventory;
			system("cls");
			ShowInventory(selectItem);

			std::cout << "\n\n\n� �������� �����Ͻðڽ��ϱ�? (" << GetInventoryCount() + 1 << "�̻��� ��ȣ�� �����ø� �ٽ� ���ư��ϴ�) : ";
			std::cin >> choiceItem;

			if (choiceItem > GetInventoryCount()) {
				break;
			}

			std::cout << "\n\n" << choiceItem << "�� �������� �����ϼ̽��ϴ�\n";
			std::cout << "�������� ��� �Ͻðڽ��ϱ�?\n----------------------------------\n";
			std::cout << "1. ����Ѵ�, ������ ��ȣ. ���ư���\n\n���� : ";
			std::cin >> selectInventory;

			if (selectInventory == 1) {
				Object* item = (Object*)User::GetData(selectItem, choiceItem - 1);
				User::userEquip.ApplyItem(itemCount, src, item);
				if (item->GetValue(statHp) != 0) {
					PlusHp(item);
				}

				if (item->GetValue(statAddInventoryCount) != 0) {
					PlusInventoryCount(item->GetValue(statAddInventoryCount));
				}
				DeleteInventory(selectItem, choiceItem - 1);
			}
		}

		else if (choice == 3) {
			std::cout << "����ġ�ڽ��ϴ�";
			break;
		}
	}

	return false;
}