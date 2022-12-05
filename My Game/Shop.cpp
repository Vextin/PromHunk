#include "Shop.h"
#include <iostream>
#include <fstream>
#include <string>

std::vector<ShopItem*> Shop::s_MasterShopItemList = {};
std::vector<ShopItem*> Shop::s_AvailableItems = {};
std::vector<CObject*> Shop::s_CardObjects = {};
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
	float val = 0.0f;

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
			ShopItem* item = new ShopItem(id);
			item->m_stat = ShopItem::stringToStat(stat);
			item->amount = val;
			s_MasterShopItemList.push_back(item);
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

std::vector<ShopItem*> Shop::GenerateRandomCards()
{
	std::vector<ShopItem*> items;
	int card1 = std::rand() % s_MasterShopItemList.size();
	int card2 = std::rand() % s_MasterShopItemList.size();
	int card3 = std::rand() % s_MasterShopItemList.size();

	items.push_back(s_MasterShopItemList[card1]);
	items.push_back(s_MasterShopItemList[card2]);
	items.push_back(s_MasterShopItemList[card3]);

	s_AvailableItems.clear();
	s_AvailableItems.push_back(items[0]);
	s_AvailableItems.push_back(items[1]);
	s_AvailableItems.push_back(items[2]);

	return items;

}

void Shop::ShowShopScreen()
{
	isDisplaying = true;
	isPaused = true;
	
	//these can be condensed but i needed fewer magic numbers
	const int padding = 10;
	const int cardOffset = 331;
	const int shopSize = 311 + (2 * padding);
	const int xSpaceLeft = 1280 / 2 - shopSize;
	const int spaceBeforeFirstCard = xSpaceLeft / 2 + 311 / 2;
	const int verticalCenter = 720 / 2;
	const Vector2 halfRes(1280 / 2, 720 / 2);
	Vector2 camPos = m_pRenderer->GetCameraPos();
	camPos -= halfRes;



	//Generate all of the cards, create objects for them centered on the screen.
	std::vector<ShopItem*> items = Shop::GenerateRandomCards();
	CObject* card1 = m_pObjectManager->create(items[0]->m_upgradeCard, Vector2(311.0f, 452.0f));
	card1->m_fRoll = 0.f;
	card1->m_vPos = camPos + Vector2(static_cast<float>(spaceBeforeFirstCard), verticalCenter);
	CObject* card2 = m_pObjectManager->create(items[1]->m_upgradeCard, Vector2(311.0f, 452.0f));
	card2->m_fRoll = 0.f;
	card2->m_vPos = camPos + Vector2(spaceBeforeFirstCard + cardOffset, verticalCenter);
	CObject* card3 = m_pObjectManager->create(items[2]->m_upgradeCard, Vector2(311.0f, 452.0f));
	card3->m_fRoll = 0.f;
	card3->m_vPos = camPos + Vector2(spaceBeforeFirstCard + (cardOffset * 2), verticalCenter);

	Shop::s_CardObjects.push_back(card1);
	Shop::s_CardObjects.push_back(card2);
	Shop::s_CardObjects.push_back(card3);

}
void Shop::BuyItem(ShopItem* item)
{
	if (dynamic_cast<ShopItem*>(item) == nullptr) return;
	switch (item->m_stat)
	{
		//LISTEN
		//YEAH, IM USING A SWITCH STATEMENT
		//I *APOLOGIZE*, OKAY?

	case ShopItem::Stat::FlatDamage:
		m_pPlayer->SetFlatDamageIncrease(item->amount);
		break;
	case ShopItem::Stat::PctDamage:
		m_pPlayer->SetPercentDamageIncrease(item->amount);
		break;
	case ShopItem::Stat::FlatHealth:
		m_pPlayer->SetFlatHealthIncrease(item->amount);
		break;
	case ShopItem::Stat::PctHealth:
		m_pPlayer->SetPercentHealthIncrease(item->amount);
		break;
	case ShopItem::Stat::FlatSpeed:
		m_pPlayer->SetFlatSpeedIncrease(item->amount);
		break;
	case ShopItem::Stat::PctSpeed:
		m_pPlayer->SetPercentSpeedIncrease(item->amount);
		break;
	case ShopItem::Stat::FlatAttackSpeed:
		m_pPlayer->SetFlatAttackSpeedIncrease(item->amount);
		break;
	case ShopItem::Stat::PctAttackSpeed:
		m_pPlayer->SetPercentAttackSpeedIncrease(item->amount);
		break;
	case ShopItem::Stat::FlatAuraDamage:
		m_pPlayer->SetFlatAuraDamageIncrease(item->amount);
		break;
	case ShopItem::Stat::PctAuraDamage:
		m_pPlayer->SetPercentDamageIncrease(item->amount);
		break;
	}
	isDisplaying = false;
	isPaused = false;
	Shop::DeleteCards();
}

void Shop::BuyItem(int i)
{
	Shop::BuyItem(s_AvailableItems[i]);
	
}

void Shop::DeleteCards()
{
	for (int i = 0; i < s_CardObjects.size(); i++)
	{
		s_CardObjects[i]->Die();
	}
	s_CardObjects.clear();
	s_AvailableItems.clear();
}