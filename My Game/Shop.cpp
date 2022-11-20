#include "Shop.h"
#include <iostream>
#include <fstream>
#include <string>

std::vector<ShopItem> Shop::s_MasterShopItemList = {};

void Shop::LoadJSON()
{
	//std::vector<ShopItem> s_MasterShopItemList;	//list of all objects that can be shown in the shop
	std::ifstream pho("Media/GameData/Upgrades.pho"); //PromHunkObject file

	if (!pho)
	{
		std::cout << "PromHunkObject File not found.";
		return;
	}
	std::string workingString;	//will hold each line one by one, via getline
	std::string id;
	std::string stat;
	float val;

	while (pho)
	{
		std::getline(pho, workingString);

		if (workingString[0] == '#')
		{
			//This is a comment. We're done.
			continue;
		}
		if (workingString[0] == ';')
		{
			//This is an "end object" marker. start a new object.
			ShopItem *item = new ShopItem(id);
			item->m_stat = ShopItem::stringToStat(stat);
			item->amount = val;
			s_MasterShopItemList.push_back(*item);
			continue;
		}
		//If we got this far, we're making a new object. ID, then stat, then value.
		id = workingString;
		std::getline(pho, workingString);
		stat = workingString;
		std::getline(pho, workingString);
		val = std::stof(workingString);
		
	}
}

std::vector<eSprite> Shop::GenerateRandomCards()
{
	std::vector<eSprite> sprites;
	int card1 = std::rand() % s_MasterShopItemList.size();
	int card2 = std::rand() % s_MasterShopItemList.size();
	int card3 = std::rand() % s_MasterShopItemList.size();

	sprites.push_back(s_MasterShopItemList[card1].m_upgradeCard);
	sprites.push_back(s_MasterShopItemList[card2].m_upgradeCard);
	sprites.push_back(s_MasterShopItemList[card3].m_upgradeCard);

	return sprites;
	
}

void Shop::ShowShopScreen()
{
	const int padding = 10;
	const int cardOffset = 331;
	const int shopSize = 311 + (2 * padding);
	const int xSpaceLeft = 1280/2 - shopSize;
	const int spaceBeforeFirstCard = xSpaceLeft / 2 + 311 / 2;
	const int verticalCenter = 720 / 2;
	std::vector<eSprite> sprites = Shop::GenerateRandomCards();
	CObject *card1 = m_pObjectManager->create(sprites[0], Vector2(311.0f, 452.0f));
	card1->m_fRoll = 0.f;
	card1->m_vPos = Vector2(static_cast<float>(spaceBeforeFirstCard), verticalCenter);
	CObject* card2 = m_pObjectManager->create(sprites[0], Vector2(311.0f, 452.0f));
	card2->m_fRoll = 0.f;
	card2->m_vPos = Vector2(spaceBeforeFirstCard+cardOffset, verticalCenter);
	CObject* card3 = m_pObjectManager->create(sprites[0], Vector2(311.0f, 452.0f));
	card3->m_fRoll = 0.f;
	card3->m_vPos = Vector2(spaceBeforeFirstCard+(cardOffset*2), verticalCenter);
}