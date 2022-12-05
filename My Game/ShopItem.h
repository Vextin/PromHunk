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
		FlatAuraDamage, PctAuraDamage,
		FlatBulletCount,
		FlatProjectileSpeed, PctProjectileSpeed
	};
	ShopItem(std::string name, std::string description, std::string stat, float val);
	ShopItem(std::string id);
	static Stat stringToStat(std::string);
	eSprite m_upgradeCard;
	ShopItem::Stat m_stat;
	float amount;
	std::string name;
	std::string description;
protected:
	static const std::map<std::string, eSprite> idToSprite;
};

