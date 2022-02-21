#include "setting.h"

void User::Event()
{
	int choice = rand() % eventMax;

	system("cls");
	switch (choice) {
	case eventSuperbView:
		printf("\n\n당신은 길을 걷던 중 절경을 발견했습니다.\n절경을 보며 당신은 지친 기색이 사라졌고 여행의 의미를 다시 깨달았습니다.\n\n최대 hp가 증가합니다!\n");
		maxHp += rand() % 10 + 10;
		break;

	case eventHomesick:
		printf("\n\n당신은 여행을 하던 중 집이 그리워지기 시작했습니다...\n아무래도 향수병에 걸린 것 같습니다...\n\n체력, 공격력, 방어력이 감소했습니다\n");
		hp -= rand() % 10 + 20;
		atk -= rand() % 5 + 5;
		def -= rand() % 5 + 5;
		break;

	case eventTraining:
		printf("\n\n당신은 검술의 대가를 만났습니다\n대가의 비법을 당신은 완벽하게 흡수했습니다\n\n공격력이 상승했습니다!\n");
		atk += rand() % 10 + 15;
		break;

	case eventTurtle:
		printf("\n\n당신은 해변에서 느리게 걸어가는 거북이를 보며 당신은 뭐든 빠르게 살아왔던 과거를 떠올렸습니다...\n\n체력, 방어력이 상승했습니다!\n");
		def += rand() % 10 + 10;
		hp += rand() % 10 + 5;

		if (hp >= maxHp) {
			hp = maxHp;
		}
		break;

	case eventMushroom:
		printf("\n\n허기가 진 당신은 숲에서 버섯을 발견했습니다\n이런... 독버섯이었네요\n\n당신의 최대체력과 체력이 감소합니다\n");
		maxHp -= rand() % 10 + 10;
		hp -= rand() % 10 + 20;
		break;

	default:
		break;
	}
}

void eventEquip(stack* equipList, int equipCount, User& user)
{
	Object* choose = new Object;

	choose = choose->GetEquip(equipList, equipCount);
	user.AddInventory(selectEquip, choose);
}

void eventItem(list* itemList, int itemCount, User& user)
{
	Object* choose = new Object;

	choose = choose->GetItem(itemList, itemCount);
	user.AddInventory(selectItem, choose);
}

Object* Object::GetEquip(stack* equipList, int equipCount)
{
	int choice = rand() % equipCount;

	Object* equip = (Object*)search(equipList, choice);

	std::cout << "\n\n당신은 무기고에서 무기를 하나 훔칠려고 합니다.\n\n";
	std::cout << equip->name << "을 얻었습니다";

	return equip;
}

Object* Object::GetItem(list* itemList, int itemCount)
{
	int choice = rand() % itemCount;


	Object* item = (Object*)searchNode(itemList, choice);

	std::cout << "\n\n당신은 무기고에서 무기를 하나 훔칠려고 합니다.\n\n";
	std::cout << item->name << "을 얻었습니다";

	return item;
}