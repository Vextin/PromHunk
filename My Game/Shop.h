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
#include "Game.h"
class Shop : UIMenu, CCommon
{
protected:
	static std::vector<ShopItem> s_MasterShopItemList;
	const std::map<std::string, eSprite> cardMap
	{
		{"damage1",eSprite::ShopCard_Damage1}
	};
	static std::vector<eSprite> GenerateRandomCards();
public:
	static void LoadJSON();
	static void ProcessLine(std::string str, ShopItem *item);
	static void ShowShopScreen();

};

