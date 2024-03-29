#include "Shop.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

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
	std::string name;
	std::string description;
	std::string stat;
	float val = 0.0f;
	int weight = 0;

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
			ShopItem* item = new ShopItem(name, description, stat, val);
			for (int i = 0; i < weight; i++) {
				s_MasterShopItemList.push_back(item);
			}
			continue;
		}
		//If we got this far, we're making a new object. Name, description, stat, value, weight.
		name = workingString;
		std::getline(pho, workingString);
		description = workingString;
		std::getline(pho, workingString);
		stat = workingString;
		std::getline(pho, workingString);
		val = std::stof(workingString);
		std::getline(pho, workingString);
		weight = std::stof(workingString);

	}
}

void Shop::GenerateRandomCards()
{
	std::vector<ShopItem*> items = s_MasterShopItemList;

	s_AvailableItems.clear();
	for (int i = 0; i < 3; i++) {
		int card = std::rand() % items.size();
		s_AvailableItems.push_back(items[card]); 
		items.erase(std::remove(items.begin(), items.end(), items[card]), items.end());
	}
}

void Shop::ShowShopScreen()
{
	isDisplaying = true;
	isPaused = true;
	
	//these can be condensed but i needed fewer magic numbers
	const int padding = 20;
	const int cardSize = 311;
	const int cardOffset = cardSize + padding;
	const int xSpaceLeft = m_nWinWidth / 2 - cardOffset;
	const int spaceBeforeFirstCard = xSpaceLeft / 2 + cardSize / 2;
	const int verticalCenter = m_nWinHeight / 2;
	const Vector2 halfRes(m_nWinWidth / 2, m_nWinHeight / 2);
	Vector2 camPos = m_pRenderer->GetCameraPos();
	camPos -= halfRes;

	//Generate all of the cards, create objects for them centered on the screen.
	Shop::GenerateRandomCards();
	CObject* card1 = m_pObjectManager->create(s_AvailableItems[0]->m_upgradeCard, camPos + Vector2(spaceBeforeFirstCard, verticalCenter));
	card1->m_fRoll = 0.0f;
	CObject* card2 = m_pObjectManager->create(s_AvailableItems[1]->m_upgradeCard, camPos + Vector2(spaceBeforeFirstCard + cardOffset, verticalCenter));
	card2->m_fRoll = 0.0f;
	CObject* card3 = m_pObjectManager->create(s_AvailableItems[2]->m_upgradeCard, camPos + Vector2(spaceBeforeFirstCard + (cardOffset * 2), verticalCenter));
	card3->m_fRoll = 0.0f;

	Shop::s_CardObjects.push_back(card1);
	Shop::s_CardObjects.push_back(card2);
	Shop::s_CardObjects.push_back(card3);

}

void Shop::DrawShopText() {
	float padding = 20;
	float cardWidth = 311;
	float cardOffset = cardWidth + padding;
	float leftCardPos = (m_nWinWidth - cardOffset * 2 - cardWidth) /2;
	float textPadding = 30;
	float nameY = m_nWinHeight / 2 - 80;
	float descY = m_nWinHeight / 2 - 30;
	float changeY = m_nWinHeight / 2  + 50;

	for (int i = 0; i < 3; i++) {
		float cardPos = leftCardPos + textPadding + cardOffset * i;
		std::string name = s_AvailableItems[i]->name;
		std::string description = s_AvailableItems[i]->description;
		if (description.length() > 20) {
			auto space = description.find(" ", 20);
			description.replace(space, 1, "\n");
		}
		m_pRenderer->DrawScreenText(name.c_str(), Vector2(cardPos, nameY), Colors::White);
		m_pRenderer->DrawScreenText(description.c_str(), Vector2(cardPos, descY), Colors::White);

		std::string currentStat = "Current " + s_AvailableItems[i]->StatName() + ": " + s_AvailableItems[i]->CurrentPlayerStat();
		m_pRenderer->DrawScreenText(currentStat.c_str(), Vector2(cardPos, changeY), Colors::White);
	}

}

void Shop::BuyItem(ShopItem* item)
{
	if (dynamic_cast<ShopItem*>(item) == nullptr) return;
	switch (item->m_stat)
	{
		//LISTEN
		//YEAH, IM USING A SWITCH STATEMENT
		//I *APOLOGIZE*, OKAY?
		
		//but i like switch statements

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
	case ShopItem::Stat::FlatBulletCount:
		m_pPlayer->SetFlatBulletCountIncrease(item->amount);
		break;
	case ShopItem::Stat::FlatProjectileSpeed:
		m_pPlayer->SetFlatProjectileSpeedIncrease(item->amount);
		break;
	case ShopItem::Stat::PctProjectileSpeed:
		m_pPlayer->SetPercentProjectileSpeedIncrease(item->amount);
		break;
	case ShopItem::Stat::FullHeal:
		m_pPlayer->health = m_pPlayer->getMaxHealth();
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