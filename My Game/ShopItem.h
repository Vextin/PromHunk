#pragma once
#include "GameDefines.h"
#include <map>
#include "Common.h"

class ShopItem:
	public CCommon
{
public:
	enum class Stat
	{
		Error,
		FlatDamage, PctDamage,
		FlatHealth, PctHealth,
		FlatSpeed, PctSpeed,
		FlatAttackSpeed, PctAttackSpeed,
		FlatAuraDamage, PctAuraDamage,
		FlatBulletCount,
		FlatProjectileSpeed, PctProjectileSpeed,
		FullHeal
	};
	ShopItem(std::string name, std::string description, std::string stat, float val);
	ShopItem(std::string id);
	static Stat stringToStat(std::string);
	eSprite m_upgradeCard;
	ShopItem::Stat m_stat;
	float amount;
	std::string name;
	std::string description;
	std::string StatName();
	std::string CurrentPlayerStat();
protected:
	static const std::map<std::string, eSprite> idToSprite;
};

