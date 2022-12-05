#include "ShopItem.h"
#include <string>
#include "Player.h"
#include <sstream>
#include <iomanip>

//Use to find a shop card sprite by ID
const std::map<std::string, eSprite> ShopItem::idToSprite =
{

	{"damage_1",eSprite::ShopCard_Damage1},
	{"damage_2",eSprite::ShopCard_Damage1},
	{"damage_3",eSprite::ShopCard_Damage1},
	{"damage_4",eSprite::ShopCard_Damage1},
	{"pctDamage_1",eSprite::ShopCard_Damage1},
	{"pctDamage_2",eSprite::ShopCard_Damage1},
};

//Complete constructor if you know all of the fields
ShopItem::ShopItem(std::string name, std::string description, std::string stat, float val)
{
	this->name = name;
	this->description = description;
	this->m_stat = ShopItem::stringToStat(stat);
	this->amount = val;
	this->m_upgradeCard = eSprite::ShopCard_Blank;
}
//incomplete constructor for if you only know the id and plan to populate the rest later.
ShopItem::ShopItem(std::string id)
{
	this->m_upgradeCard = ShopItem::idToSprite.at(id);
}

ShopItem::Stat ShopItem::stringToStat(std::string s)
{

	if (s.compare("FlatDamage") == 0)
	{
		return Stat::FlatDamage;
	}
	else if (s.compare("PctDamage") == 0)
	{
		return Stat::PctDamage;
	}
	else if (s.compare("FlatHealth") == 0)
	{
		return Stat::FlatHealth;
	}
	else if (s.compare("PctHealth") == 0)
	{
		return Stat::PctHealth;
	}
	else if (s.compare("FlatSpeed") == 0)	{
		return Stat::FlatSpeed;
	}
	else if (s.compare("PctSpeed") == 0)
	{
		return Stat::PctSpeed;
	}
	else if (s.compare("FlatAttackSpeed") == 0)
	{
		return Stat::FlatAttackSpeed;
	}
	else if (s.compare("PctAttackSpeed") == 0)
	{
		return Stat::PctAttackSpeed;
	}
	else if (s.compare("FlatAuraDamage") == 0)
	{
		return Stat::FlatAuraDamage;
	}
	else if (s.compare("PctAuraDamage") == 0)
	{
		return Stat::PctAuraDamage;
	}
	else if (s.compare("FlatBulletCount") == 0)
	{
		return Stat::FlatBulletCount;
	}
	else if (s.compare("FlatProjectileSpeed") == 0)
	{
		return Stat::FlatProjectileSpeed;
	}
	else if (s.compare("PctProjectileSpeed") == 0)
	{
		return Stat::PctProjectileSpeed;
	}
	else if (s.compare("FullHeal") == 0)
	{
		return Stat::FullHeal;
	}
	return Stat::Error;
}

std::string ShopItem::StatName() {
	switch (m_stat)
	{
	case ShopItem::Stat::FlatDamage:
	case ShopItem::Stat::PctDamage:
		return "damage";
	case ShopItem::Stat::FlatHealth:
	case ShopItem::Stat::PctHealth:
		return "max health";
	case ShopItem::Stat::FlatSpeed:
	case ShopItem::Stat::PctSpeed:
		return "speed";
	case ShopItem::Stat::FlatAttackSpeed:
	case ShopItem::Stat::PctAttackSpeed:
		return "attack speed";
	case ShopItem::Stat::FlatAuraDamage:
	case ShopItem::Stat::PctAuraDamage:
		return "aura damage";
	case ShopItem::Stat::FlatBulletCount:
		return "bullet count";
	case ShopItem::Stat::FlatProjectileSpeed:
	case ShopItem::Stat::PctProjectileSpeed:
		return "bullet speed";
	case ShopItem::Stat::FullHeal:
		return "health";
	}
	return "error";
}

std::string ShopItem::CurrentPlayerStat() {
	std::stringstream ss;
	std::string healthString;

	switch (m_stat)
	{
	case ShopItem::Stat::FlatDamage:
	case ShopItem::Stat::PctDamage:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->getDamage();
		return ss.str();
	case ShopItem::Stat::FlatHealth:
	case ShopItem::Stat::PctHealth:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->getMaxHealth();
		return ss.str();
	case ShopItem::Stat::FlatSpeed:
	case ShopItem::Stat::PctSpeed:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->getSpeed();
		return ss.str();
	case ShopItem::Stat::FlatAttackSpeed:
	case ShopItem::Stat::PctAttackSpeed:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->getAttackSpeed();
		return ss.str();
	case ShopItem::Stat::FlatAuraDamage:
	case ShopItem::Stat::PctAuraDamage:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->getAuraDamage();
		return ss.str();
	case ShopItem::Stat::FlatBulletCount:
		return std::to_string((int)(m_pPlayer->getProjectileCount()));
	case ShopItem::Stat::FlatProjectileSpeed:
	case ShopItem::Stat::PctProjectileSpeed:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->getProjectileSpeed();
		return ss.str();
	case ShopItem::Stat::FullHeal:
		ss << std::fixed << std::setprecision(1) << m_pPlayer->health;
		return ss.str();
	}
	return "error";
}