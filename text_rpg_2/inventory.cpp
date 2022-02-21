#include "setting.h"

Inventory::Inventory(void)
{
	maxInventoryCount = inventory_Count;
	equipInventory = new void_pointer[maxInventoryCount];
	memset(equipInventory, NULL, sizeof(void_pointer) * maxInventoryCount);
	itemInventory = new void_pointer[maxInventoryCount];
	memset(itemInventory, NULL, sizeof(void_pointer) * maxInventoryCount);
}

void User::ShowInventory(enum eobject num)
{
	if (num == selectEquip) {
		bag.ShowEquip();
	}
	else if (num == selectItem) {
		bag.ShowItem();
	}
}

void Inventory::ShowEquip(void)
{
	std::cout << "=== 장비 ===\n\n";
	int i = 0;
	int j = 0;
	while (i < maxInventoryCount) {
		Object* pData = (Object*)GetEquipData(i);
		if (pData != NULL) {
			if (i != j) {
				AddEquip((void_pointer)pData);
				pData->PrintEquip(j);
				DeleteEquip(i + 1);
				continue;
			}
			pData->PrintEquip(j);
			std::cout << std::endl;
			j++;
		}
		i++;
	}
}

void Inventory::ShowItem(void)
{
	std::cout << "=== 아이템 ===\n\n";
	int i = 0;
	int j = 0;
	while (i < maxInventoryCount) {
		Object* pData = (Object*)GetItemData(i);
		if (GetItemData(i) != NULL) {
			if (i != j) {
				AddItem((void_pointer)pData);
				pData->PrintItem(j);
				DeleteItem(i + 1);
				continue;
			}

			pData->PrintItem(i);
			std::cout << std::endl;
			j++;
		}
		i++;
	}
}

void Object::PrintEquip(int num)
{
	std::cout << "장비 " << num + 1 << " : " << name << std::endl;
	std::cout << explain << std::endl;
}

void Object::PrintItem(int num)
{
	std::cout << "아이템 " << num + 1 << " : " << name << std::endl;
	std::cout << explain << std::endl;
}

void User::DeleteInventory(enum eobject num, int count)
{
	if (num == selectEquip) {
		bag.DeleteEquip(count);
	}
	else if (num == selectItem) {
		bag.DeleteItem(count);
	}
}

void_pointer User::GetData(enum eobject num, int count)
{
	if (num == selectEquip) {
		return bag.GetEquipData(count);
	}
	else if (num == selectItem) {
		return bag.GetItemData(count);
	}
}

void User::AddInventory(enum eobject num, void_pointer choose)
{
	if (num == selectEquip) {
		return bag.AddEquip(choose);
	}
	else if (num == selectItem) {
		return bag.AddItem(choose);
	}
}

void Inventory::AddEquip(void_pointer choose)
{
	int equipNum = 0;

	while (equipNum < maxInventoryCount) {
		if (GetEquipData(equipNum) == 0) {
			equipInventory[equipNum] = choose;
			return;
			break;
		}
		equipNum++;
	}
}

void Inventory::AddItem(void_pointer choose)
{
	int itemNum = 0;

	while (itemNum < maxInventoryCount) {
		if (GetItemData(itemNum) == 0) {
			itemInventory[itemNum] = choose;
			return;
			break;
		}
		itemNum++;
	}
}

char* Object::WearEquip(char* applyEquip)
{
	int select;

	if (strlen(applyEquip) == 0) {
		applyEquip = Object::name;
		std::cout << "장비를 장착했습니다\n\n";
	}

	else {
		std::cout << "\n\n착용되어 있는 장비 : " << applyEquip << "\n착용된 장비는 사라집니다\n\n";
		std::cout << "지금까지 모았던 스탯이 전부 사라집니다!\n\n";
		std::cout << "그래도 바꾸시겠습니까?\n\n";
		std::cout << "1. 예 2. 아니요\n 선택 : ";
		std::cin >> select;

		if (select == 1) {
			applyEquip = Object::name;

			std::cout << "장비가 교체되었습니다\n\n";

		}
	}
	return applyEquip;
}

void EquipStat::Reset()
{
	hp = 0;
	maxHp = 0;
	atk = 0;
	def = 0;
	cri = 0;
	criPersentage = 0;
}


void Inventory::PlusCount(int num)
{
	int tempInventoryNum = maxInventoryCount;

	maxInventoryCount += num;
	void_pointer* tempEquip = new void_pointer[maxInventoryCount];
	void_pointer* tempItem = new void_pointer[maxInventoryCount];

	memcpy(tempEquip, equipInventory, sizeof(void_pointer) * tempInventoryNum);
	memcpy(tempItem, itemInventory, sizeof(void_pointer) * tempInventoryNum);

	delete[] equipInventory;
	delete[] itemInventory;

	equipInventory = tempEquip;
	itemInventory = tempItem;

	for (int i = 0; i < maxInventoryCount - tempInventoryNum; i++) {
		DeleteEquip(tempInventoryNum);
		DeleteItem(tempInventoryNum);
	}
}


void EquipStat::ApplyEquip(int count, stack* src, const char* const applyEquip)
{
	for (int i = 0; i < count; ++i) {
		Object* checkEquip = (Object*)search(src, i);
		if (applyEquip == checkEquip->GetName()) {
			atk += checkEquip->GetValue(statAtk);
			def += checkEquip->GetValue(statDef);
			criPersentage += checkEquip->GetValue(statCriPesentage);
			cri += checkEquip->GetValue(statCri);
		}
	}
}


void EquipStat::ApplyItem(int count, list* src, Object* data)
{
	for (int i = 0; i < count; ++i) {
		Object* checkItem = (Object*)searchNode(src, i);
		if (data->GetName() == checkItem->GetName()) {
			atk += checkItem->GetValue(statAtk);
			def += checkItem->GetValue(statDef);
			criPersentage += checkItem->GetValue(statCriPesentage);
			cri += checkItem->GetValue(statCri);
		}
	}
}