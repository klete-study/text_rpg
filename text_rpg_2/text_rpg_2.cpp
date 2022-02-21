#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <iostream>
#include "setting.h"

int main()
{
	JSON_Value* rootEquipValue = json_parse_file("equipment.json");
	JSON_Value* rootItemValue = json_parse_file("item.json");

	int equipCount;
	int itemCount;

	stack* equipList = loadEquipmentData(equipCount, rootEquipValue);
	list* itemList = loadItemData(itemCount, rootItemValue);

	json_value_free(rootEquipValue);
	json_value_free(rootItemValue);

	Exp expData;

	char* applyEquip = new char[gStrMax];
	memset(applyEquip, NULL, gStrMax);

	while (true) {
		User user;
		user.ResetExp();

		srand(time(NULL));

		int life = lifeAlive;
		int level = 1;
		int loadselect;

		FILE* userData;
		fopen_s(&userData, "user_data.txt", "r");


		if (userData != NULL) {
			std::cout << "이미 저장된 파일이 있습니다 불러오시겠습니까?\n";
			std::cout << "1. 예 2. 아니요\n선택 : ";
			std::cin >> loadselect;

			if (loadselect == 1) {
				user.LoadFile(applyEquip, equipList, itemList, userData);
			}
		}
		fclose(userData);

		char name[gStrMax];

		system("cls");

		std::cout << "시작하기에 앞서 이름을 정하도록 하겠습니다\n";

		while (true) {
			std::cout << "입력할 수 있는 이름의 범위는 한글 5글자, 영어 10글자입니다.\n";
			std::cout << "주인공의 이름을 입력해주세요 : ";
			std::cin >> name;

			if (strlen(name) < 11) {
				break;
			}

			printf("다시 입력하세요\n\n");
			system("cls");
		}

		std::cout << "\n\n주인공의 이름은 " << name << "입니다";
		std::cout << "\n\n이어서 능력치를 정하도록 하겠습니다.\n";
		std::cout << "잠시만 기다려 주세요...\n\n";
		Sleep(1000);

		while (true) {
			int selectUserStat;
			system("cls");

			user.SetStat(name);
			user.ShowStat(expData);
			std::cout << "\n\n이 능력치로 하시겠습니까? (그렇다면 1) : ";
			std::cin >> selectUserStat;

			if (selectUserStat != 1) {
				system("cls");
				std::cout << "능력치를 재설정합니다 \n\n";
				Sleep(1000);
			}

			else {
				break;
			}
		}

		Sleep(1000);
		std::cout << "\n\n지금부터 게임을 시작하겠습니다\ntext rpg에 오신 것을 환영합니다\n";
		Sleep(500);

		while (true) {
			int userSelect = 0;

			system("cls");
			std::cout << "당신이 하실 행동을 선택해주세요\n--------------------------------------------\n";
			std::cout << "1. 인벤토리 2. 여행 3. 스탯 4. 저장&불러오기\n\n";
			std::cout << "선택 : ";
			std::cin >> userSelect;

			while (userSelect == userSelectInventory) {
				int ChoiceEquipOrItem;
				int selectInventory;
				int choiceEquip;
				int choiceItem;

				system("cls");
				std::cout << "장비와 아이템 중 하나를 고르세요\n-----------------------------\n";
				std::cout << "1. 장비 2. 아이템 3. 돌아간다\n\n";
				std::cout << "선택 : ";
				std::cin >> ChoiceEquipOrItem;

				while (ChoiceEquipOrItem == selectEquip) {

					system("cls");
					user.ShowInventory(selectEquip);

					std::cout << "\n\n\n어떤 장비를 선택하시겠습니까? (" << user.GetInventoryCount() + 1 << "이상의 번호를 누르시면 다시 돌아갑니다) : ";
					std::cin >> choiceEquip;

					if (choiceEquip > user.GetInventoryCount()) {
						break;
					}

					std::cout << "\n\n" << choiceEquip << "번 장비를 선택하셨습니다\n";
					std::cout << "장비를 어떻게 하시겠습니까?\n----------------------------------\n";
					std::cout << "1. 장착한다. 2. 버린다 3. 돌아간다\n\n선택 : ";
					std::cin >> selectInventory;

					if (selectInventory == 1) {
						char* tempEquip = new char[gStrMax];
						memcpy(tempEquip, applyEquip, gStrMax);

						Object* Equip = (Object*)user.GetData(selectEquip, choiceEquip - 1);
						applyEquip = Equip->WearEquip(applyEquip);

						if (tempEquip[0] != '\0' && tempEquip != applyEquip) {
							user.ResetEquipStat();
						}
						Sleep(1000);

						user.ApplyEquip(equipCount, equipList, applyEquip);
						user.DeleteInventory(selectEquip, choiceEquip);
						continue;
					}

					else if (selectInventory == 2) {
						user.DeleteInventory(selectEquip, choiceEquip);

						std::cout << "장비를 버렸습니다";
						Sleep(1000);
						continue;
					}

					else if (selectInventory == selectBack) {
						;
						continue;
					}
				}

				while (ChoiceEquipOrItem == selectItem) {

					system("cls");
					user.ShowInventory(selectItem);

					std::cout << "\n\n\n어떤 아이템을 선택하시겠습니까? (" << user.GetInventoryCount() + 1 << "이상의 번호를 누르시면 다시 돌아갑니다) : ";
					std::cin >> choiceItem;

					if (choiceItem > user.GetInventoryCount()) {
						break;
					}

					std::cout << "\n\n" << choiceItem << "번 아이템을 선택하셨습니다\n";
					std::cout << "아이템 어떻게 하시겠습니까?\n----------------------------------\n";
					std::cout << "1. 사용한다. 2. 버린다 3. 돌아간다\n\n선택 : ";
					std::cin >> selectInventory;

					if (selectInventory == 1) {
						Object* item = (Object*)user.GetData(selectItem, choiceItem - 1);
						user.ApplyItem(itemCount, itemList, item);
						std::cout << "아이템을 사용하셨습니다\n";
						Sleep(1000);

						if (item->GetValue(statHp()) != 0) {
							user.PlusHp(item);
						}

						if (item->GetValue(statAddInventoryCount) != 0) {
							user.PlusInventoryCount(item->GetValue(statAddInventoryCount));
						}
						user.DeleteInventory(selectItem, choiceItem);
						continue;
					}

					else if (selectInventory == 2) {
						user.DeleteInventory(selectItem, choiceItem);

						std::cout << "아이템을 버렸습니다";
						Sleep(1000);
						continue;
					}

					else if (selectInventory == selectBack) {
						continue;
					}
				}

				if (ChoiceEquipOrItem == selectBack) {
					break;
				}
			}

			while (userSelect == userSelectTravel) {
				int selectTravel;
				bool bfightResult = true;

				system("cls");
				std::cout << "둘 중 하나를 선택해주세요\n-----------------------------\n";
				std::cout << "1. 사냥 2. 이벤트 3. 돌아가기 \n\n";
				std::cout << "선택 : ";
				std::cin >> selectTravel;

				if (selectTravel == 1) {
					Monster make;
					bfightResult = user.DoBattle(itemCount, itemList, make);

					if (bfightResult == true) {
						std::cout << "승리하셨습니다!\n\n";
						std::cout << "얻은 경험치 : " << make.GetValue(statExp);
						Sleep(1000);

						if (user.GetExp() >= expData.get(level)) {
							level++;
							user.LevelUp();
							std::cout << "\n\n축하합니다! 레벨업 하셨습니다!\n\n";
							std::cout << "현재 레벨" << level << "다음 레벨까지 필요한 경험치" << expData.get(level);
						}
					}
					continue;
				}

				else if (selectTravel == 2) {
					//int selectEvent = rand() % 2;
					int selectEvent = 1;

					if (selectEvent == 0) {
						user.Event();
						Sleep(1500);
					}

					else if (selectEvent == 1) {
						//int choiceEvent = rand() % eventGetMax;
						int choiceEvent = eventGetEquip;

						if (choiceEvent == eventGetEquip) {
							eventEquip(equipList, equipCount, user);
						}

						else if (choiceEvent == eventGetItem) {
							eventItem(itemList, equipCount, user);
						}
						Sleep(1500);
					}

					if (user.CheckDeath()) {
						life = lifeDeath;
					}
				}

				else if (selectTravel == selectBack) {
					break;
				}

				if (life == lifeDeath) {
					int lastChoice = 0;
					Sleep(1500);
					system("cls");
					std::cout << "게임이 종료되었습니다\n\n다시 시작하시겠습니까?\n\n";
					std::cout << "1. 예 2. 아니요\n\n선택 : ";
					std::cin >> lastChoice;

					user.~User();

					if (lastChoice == gameRestart) {

						break;
					}

					else if (lastChoice == gameExit) {
						delete[] applyEquip;
						releaseStack(equipList);
						releaseList(itemList);
						std::cout << "게임을 종료하겠습니다";

						_CrtDumpMemoryLeaks();
						return 0;
					}
				}
			}

			if (life == lifeDeath) {
				system("cls");
				break;
			}

			if (userSelect == userSelectStat) {
				system("cls");
				user.ShowStat(expData);
				Sleep(1500);
				system("cls");
				user.ShowEquipStat(applyEquip);
				Sleep(1500);
				std::cout << "체력, 공격력, 방어력이 0이하일 시 게임이 종료됩니다.\n\n";
				std::cout << "확인이 다 끝나셨다면 돌아가겠습니다";
			}

			else if (userSelect == userSelectSave) {
				user.SaveFile(applyEquip);
			}
		}
	}
	return 0;
}