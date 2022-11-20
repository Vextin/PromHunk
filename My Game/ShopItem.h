#pragma once
#include "GameDefines.h"
#include <map>

class ShopItem
{
public:
	enum class Stat
	{
		FlatDamage, PctDamage,
		FlatHealth, PctHealth,
		FlatSpeed, PctSpeed,
		FlatAttackSpeed, PctAttackSpeed,
		FlatAuraDamage, PctAuraDamage
	};
	ShopItem(std::string id, ShopItem::Stat stat, float val);
	ShopItem(std::string id);
	static Stat stringToStat(std::string);
	eSprite m_upgradeCard;
	ShopItem::Stat m_stat;
	float amount;
protected:
	static const std::map<std::string, eSprite> idToSprite;
};

