#pragma once
#include "GameDefines.h"
#include "Common.h"
#include "Effect.h"
#include "Entity.h"
#include "UIMenu.h"
#include <string.h>
#include "ShopItem.h"
#include "ObjectManager.h"
#include "Common.h"
#include <cstdlib>
#include "Game.h" //im absolutely positive this is a bad idea... but it works
class Shop : UIMenu, CCommon, LSettings
{
protected:
	static std::vector<ShopItem*> s_MasterShopItemList;
	static std::vector<ShopItem*> s_AvailableItems;
	static std::vector<CObject*> s_CardObjects;
	static void GenerateRandomCards();
	bool isDisplaying = false;
	static void DeleteCards(); //Remove the cards from the screen
public:
	bool IsDisplaying() { return isDisplaying; };
	static void LoadJSON();
	static void ProcessLine(std::string str, ShopItem *item);
	void ShowShopScreen();
	void BuyItem(ShopItem* item); //Buy a specific item from the shop
	void BuyItem(int i); //Buy an item by its index in the current shop screen (0, 1, or 2)
	void DrawShopText();
};

