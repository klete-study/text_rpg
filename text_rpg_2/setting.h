#pragma once
#include <iostream>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "list.h"
#include "parson.h"
#include "stack.h"
#define inventory_Count 5

const int gStrMax = 256;

enum elife {
    lifeDeath, lifeAlive
};

enum euserSelect {
    userSelectInventory = 1, userSelectTravel, userSelectStat, userSelectSave
};

enum eevent {
    eventSuperbView, eventHomesick, eventTraining, eventTurtle, eventMushroom, eventMax
};

enum eeventGet {
    eventGetEquip, eventGetItem, eventGetMax
};

enum egame {
    gameRestart = 1, gameExit
};

enum emonster {
    monsterZombie, monsterDevilBlood, monsterDragon, monsterMax
};

enum eobject {
    selectEquip = 1, selectItem, selectBack
};

enum estat {
    statHp, statAtk, statDef, statCri, statCriPesentage, statAddInventoryCount, statExp
};

class Exp
{
public:
    Exp(void);

    ~Exp() {}

    int get(int level) {
        return maxExp[level - 1];
    }

private:
    int* maxExp;
};

class Monster
{
public:
    Monster(void);

    int GetValue(enum estat num);

    void DamageHp(int userAtk) {
        hp -= userAtk;
    }

private:
    int hp;
    int atk;
    int def;
    int exp;
};

class Object
{
public:
    Object* GetEquip(stack* equipList, int equipCount);
    Object* GetItem(list* itemList, int itemCount);

    Object* SetData(JSON_Object* src, Object* data);

    void PrintEquip(int num);
    void PrintItem(int num);

    char* WearEquip(char* applyEquip);

    const char* const GetName(void) {
        return name;
    }

    int GetValue(enum estat num);

private:
    int hp;
    int maxHp;
    int atk;
    int def;
    float cri;
    float criPersentage;
    int addInventoryCount;
    char name[gStrMax];
    char explain[gStrMax];
};

class Inventory
{
public:
    Inventory(void);

    ~Inventory() { }

    void_pointer GetEquipData(int num) {
        return equipInventory[num];
    }

    void_pointer GetItemData(int num) {
        return itemInventory[num];
    }

    void SaveFile(void);

    void LoadFile(stack* equipList, list* itemList);

    void ShowItem(void); // void*형을 Equipment형 변환

    void ShowEquip(void);

    void AddEquip(void_pointer choose);

    void AddItem(void_pointer choose);

    int InventoryCount(void) {
        return maxInventoryCount;
    }

    void DeleteEquip(int num) {
        equipInventory[num - 1] = NULL;
    }

    void DeleteItem(int num) {
        itemInventory[num - 1] = NULL;
    }

    void PlusCount(int num);


private:
    int maxInventoryCount;
    void_pointer* equipInventory;
    void_pointer* itemInventory;
};

class EquipStat
{
public:

    ~EquipStat() {}

    void LoadFile(char* equipName);

    void SaveFile(char* equipName);

    void Reset(void);

    void ApplyEquip(int count, stack* src, const char* const applyEquip);

    void ApplyItem(int count, list* src, Object* data);

    void ShowStat(char* applyEquip);

    int GetValue(enum estat num);

private:
    int hp;
    int maxHp;
    int atk;
    int def;
    float cri;
    float criPersentage;
};

class User
{
public:

    ~User() {
        bag.~Inventory();
        userEquip.~EquipStat();
    }

    void SaveFile(char* applyEquip);

    void LoadFile(char* applyEquip, stack* equipList, list* itemList, FILE* userFile);

    void SetStat(char* name);

    int GetExp(void) {
        return userExp;
    }

    void LevelUp(void) {
        userLevel++;
    }

    void ResetExp(void);

    void Event(void);

    void ShowStat(Exp& data);

    bool CheckDeath(void);

    bool DoBattle(int itemCount, list* src, Monster& monster);

    void PlusHp(Object* data);

    void ShowInventory(enum eobject num);

    void ResetEquipStat(void) {
        userEquip.Reset();
    }

    void ApplyEquip(int count, stack* src, char* applyEquip) {
        userEquip.ApplyEquip(count, src, applyEquip);
    }

    void ApplyItem(int count, list* src, Object* data) {
        userEquip.ApplyItem(count, src, data);
    }

    void DeleteInventory(enum eobject num, int count);

    void_pointer GetData(enum eobject num, int count);

    void AddInventory(enum eobject num, void_pointer choose);

    int GetInventoryCount()
    {
        return bag.InventoryCount();
    }

    void PlusInventoryCount(int num) {
        bag.PlusCount(num);
    }

    void ShowEquipStat(char* applyEquip) {
        userEquip.ShowStat(applyEquip);
    }

private:
    Inventory bag;
    EquipStat userEquip;

    char userName[gStrMax];
    int hp;
    int maxHp;
    int atk;
    int def;
    float cri;
    float criPersentage;
    int userExp;
    int userLevel;
};

stack* loadEquipmentData(int& count, JSON_Value* valueSrc);

list* loadItemData(int& count, JSON_Value* valueSrc);

void eventEquip(stack* equipList, int equipCount, User& user);

void eventItem(list* itemList, int itemCount, User& user);