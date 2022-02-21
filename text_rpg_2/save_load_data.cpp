#include "setting.h"

void User::SaveFile(char* applyEquip)
{
	FILE* saveUserStat;

	fopen_s(&saveUserStat, "user_data.txt", "w");

	if (saveUserStat == NULL) {
		printf("저장 실패");

		exit(0);
	}

	fprintf(saveUserStat, "%s\n%d\n%d\n%d\n", userName, hp, def, atk);
	fprintf(saveUserStat, "%f\n%f", criPersentage, cri);

	bag.SaveFile();
	userEquip.SaveFile(applyEquip);
}

void Inventory::SaveFile() {

	FILE* saveInventoryEquip;
	FILE* saveInventoryItem;

	fopen_s(&saveInventoryEquip, "inventory_equip.txt", "w");
	fopen_s(&saveInventoryItem, "inventory_item.txt", "w");

	if (saveInventoryEquip == NULL || saveInventoryItem == NULL) {
		printf("인벤토리 저장 실패");
		exit(0);
	}
	for (int i = 0; i < maxInventoryCount; i++) {
		Object* equip = new Object;
		equip = (Object*)GetEquipData(i);
		if (equip != NULL) {
			fprintf(saveInventoryEquip, "%s\n", equip->GetName());
		}
	}

	for (int i = 0; i < maxInventoryCount; i++) {
		Object* Item = new Object;
		Item = (Object*)GetEquipData(i);
		if (Item != NULL) {
			fprintf(saveInventoryItem, "%s\n", Item->GetName());
		}
	}

	fclose(saveInventoryEquip);
	fclose(saveInventoryItem);
}

void EquipStat::SaveFile(char* equipName)
{
	FILE* saveEquipStat;

	fopen_s(&saveEquipStat, "equip_stat.txt", "w");

	if (saveEquipStat == NULL) {
		printf("저장 실패");

		exit(0);
	}

	fprintf(saveEquipStat, "%s\n%d\n%d\n%d\n", equipName, hp, def, atk);
	fprintf(saveEquipStat, "%f\n%f", criPersentage, cri);
	fclose(saveEquipStat);

}

void User::LoadFile(char* applyEquip, stack* equipList, list* itemList, FILE* userFile)
{
	fscanf_s(userFile, "%s", userName, gStrMax);
	fscanf_s(userFile, "%d%d%d%d", &hp, &maxHp, &atk, &def);
	fscanf_s(userFile, "%d%d%d%d", &cri, &criPersentage, &userExp, &userLevel);
	fclose(userFile);

	bag.LoadFile(equipList, itemList);
	userEquip.LoadFile(applyEquip);
}

void Inventory::LoadFile(stack* equipList, list* itemList)
{
	FILE* loadInventoryEquip;
	FILE* loadInventoryItem;

	fopen_s(&loadInventoryEquip, "inventory_equip.txt", "r");
	fopen_s(&loadInventoryItem, "inventory_item.txt", "r");

	if (loadInventoryEquip == NULL || loadInventoryItem == NULL) {
		printf("인벤토리 불러오기 실패");
		exit(0);
	}
	char* objectName = new char[gStrMax];

	while (fgets(objectName, gStrMax, loadInventoryEquip) != NULL) {
		objectName[strlen(objectName) - 1] = '\0';
		for (int i = 0; i < maxInventoryCount; i++) {
			Object* equip = (Object*)search(equipList, i);

			if (strcmp(equip->GetName(), objectName) == 0) {
				AddEquip(equip);
				break;
			}
		}
	}

	while (fgets(objectName, gStrMax, loadInventoryItem) != NULL) {
		objectName[strlen(objectName) - 1] = '\0';
		for (int i = 0; i < maxInventoryCount; i++) {
			Object* Item = (Object*)searchNode(itemList, i);

			if (strcmp(Item->GetName(), objectName) == 0) {
				AddEquip(Item);
				break;
			}
		}
	}
}

void EquipStat::LoadFile(char* equipName)
{
	FILE* loadEquipStat;

	fopen_s(&loadEquipStat, "equip_stat.txt", "r");

	if (loadEquipStat == NULL) {
		printf("저장 실패");

		exit(0);
	}

	fscanf_s(loadEquipStat, "%s", equipName, gStrMax);
	fscanf_s(loadEquipStat, "%d%d%d%f%f", &hp, &def, &atk, &criPersentage, &cri);

	if (equipName[0] == '0') {
		memset(equipName, NULL, gStrMax);
	}

}

stack* loadEquipmentData(int& count, JSON_Value* valueSrc)
{
	stack* newList = create();

	JSON_Object* rootEquipObject = json_value_get_object(valueSrc);
	JSON_Array* equipment = json_object_get_array(rootEquipObject, "equip");

	count = (int)json_object_get_number(rootEquipObject, "equip_count");

	for (int i = 0; i < count; ++i) {
		Object* newEquip = new Object;
		JSON_Object* equipInfo = json_array_get_object(equipment, i);

		newEquip = newEquip->SetData(equipInfo, newEquip);

		push(newList, (void_pointer)&newEquip);
	}

	return newList;
}

list* loadItemData(int& count, JSON_Value* valueSrc)
{
	list* newList = create_list();

	JSON_Object* rootItemObject = json_value_get_object(valueSrc);
	JSON_Array* item = json_object_get_array(rootItemObject, "item");

	count = (int)json_object_get_number(rootItemObject, "item_count");

	for (int i = 0; i < count; ++i) {
		Object* newItem = new Object;
		JSON_Object* itemInfo = json_array_get_object(item, i);

		newItem = newItem->SetData(itemInfo, newItem);

		pushBack(newList, (void_pointer)newItem);
	}

	return newList;
}

Object* Object::SetData(JSON_Object* src, Object* data)
{
	memcpy(data->name, json_object_get_string(src, "ko"), sizeof(data->name));
	memcpy(data->explain, json_object_get_string(src, "ep"), sizeof(data->explain));
	data->atk = (int)json_object_get_number(src, "at");
	data->def = (int)json_object_get_number(src, "de");
	data->hp = (int)json_object_get_number(src, "hp");
	data->cri = (float)json_object_get_number(src, "ct");
	data->criPersentage = (float)json_object_get_number(src, "cp");
	data->addInventoryCount = (int)json_object_get_number(src, "ic");

	return data;
}