#include "setting.h"

void User::Event()
{
	int choice = rand() % eventMax;

	system("cls");
	switch (choice) {
	case eventSuperbView:
		printf("\n\n����� ���� �ȴ� �� ������ �߰��߽��ϴ�.\n������ ���� ����� ��ģ ����� ������� ������ �ǹ̸� �ٽ� ���޾ҽ��ϴ�.\n\n�ִ� hp�� �����մϴ�!\n");
		maxHp += rand() % 10 + 10;
		break;

	case eventHomesick:
		printf("\n\n����� ������ �ϴ� �� ���� �׸������� �����߽��ϴ�...\n�ƹ����� ������� �ɸ� �� �����ϴ�...\n\nü��, ���ݷ�, ������ �����߽��ϴ�\n");
		hp -= rand() % 10 + 20;
		atk -= rand() % 5 + 5;
		def -= rand() % 5 + 5;
		break;

	case eventTraining:
		printf("\n\n����� �˼��� �밡�� �������ϴ�\n�밡�� ����� ����� �Ϻ��ϰ� ����߽��ϴ�\n\n���ݷ��� ����߽��ϴ�!\n");
		atk += rand() % 10 + 15;
		break;

	case eventTurtle:
		printf("\n\n����� �غ����� ������ �ɾ�� �ź��̸� ���� ����� ���� ������ ��ƿԴ� ���Ÿ� ���÷Ƚ��ϴ�...\n\nü��, ������ ����߽��ϴ�!\n");
		def += rand() % 10 + 10;
		hp += rand() % 10 + 5;

		if (hp >= maxHp) {
			hp = maxHp;
		}
		break;

	case eventMushroom:
		printf("\n\n��Ⱑ �� ����� ������ ������ �߰��߽��ϴ�\n�̷�... �������̾��׿�\n\n����� �ִ�ü�°� ü���� �����մϴ�\n");
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

	std::cout << "\n\n����� ������� ���⸦ �ϳ� ��ĥ���� �մϴ�.\n\n";
	std::cout << equip->name << "�� ������ϴ�";

	return equip;
}

Object* Object::GetItem(list* itemList, int itemCount)
{
	int choice = rand() % itemCount;


	Object* item = (Object*)searchNode(itemList, choice);

	std::cout << "\n\n����� ������� ���⸦ �ϳ� ��ĥ���� �մϴ�.\n\n";
	std::cout << item->name << "�� ������ϴ�";

	return item;
}