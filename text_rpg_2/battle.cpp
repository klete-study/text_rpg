#include "setting.h"

Monster::Monster()
{
	int choice = rand() % monsterMax;

	if (choice == monsterZombie) {
		hp = rand() % 30 + 10;
		atk = rand() % 10 + 1;
		def = rand() % 10 + 1;
		exp = hp * 0.5 + atk * 0.5 + def * 0.3;
		printf("괴상하게 생긴 좀비를 만났습니다!\n전투에 돌입합니다\n");
	}

	else if (choice == monsterDevilBlood) {
		hp = rand() % 50 + 40;
		atk = rand() % 10 + 20;
		def = rand() % 15 + 5;
		exp = hp * 0.6 + atk * 0.6 + def * 0.4;
		printf("어디서 많이 본 듯한 악마 피붙이를 만났습니다!\n전투에 돌입합니다\n");
	}

	else if (choice == monsterDragon) {
		hp = rand() % 80 + 70;
		atk = rand() % 20 + 15;
		def = rand() % 20 + 15;
		exp = hp * 0.8 + atk * 0.7 + def * 0.5;
		printf("어마어마한 크기의 용을 만났습니다!\n전투에 돌입합니다\n");
	}
}

bool User::DoBattle(int itemCount, list* src, Monster& monster)
{
	while (true) {
		int choice;

		Sleep(1000);
		system("cls");

		std::cout << userName << "의 체력 : " << hp << ", 몬스터의 체력 : " << monster.GetValue(statHp);
		std::cout << "\n\n계속 하시겠습니까?\n------------------------\n";
		std::cout << "1. 싸운다 2. 아이템을 사용한다 3. 도망친다.\n\n";
		std::cout << "선택 : ";
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


			std::cout << "싸우는중...\n\n";

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

			std::cout << "\n\n\n어떤 아이템을 선택하시겠습니까? (" << GetInventoryCount() + 1 << "이상의 번호를 누르시면 다시 돌아갑니다) : ";
			std::cin >> choiceItem;

			if (choiceItem > GetInventoryCount()) {
				break;
			}

			std::cout << "\n\n" << choiceItem << "번 아이템을 선택하셨습니다\n";
			std::cout << "아이템을 어떻게 하시겠습니까?\n----------------------------------\n";
			std::cout << "1. 사용한다, 나머지 번호. 돌아간다\n\n선택 : ";
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
			std::cout << "도망치겠습니다";
			break;
		}
	}

	return false;
}