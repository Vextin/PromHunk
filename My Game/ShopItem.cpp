#include "ShopItem.h"
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
		return Stat::PctAuraDamage;
	}
	else if (s.compare("FlatProjectileSpeed") == 0)
	{
		return Stat::PctAuraDamage;
	}
	else if (s.compare("PctProjectileSpeed") == 0)
	{
		return Stat::PctAuraDamage;
	}
	//if we don't know what stat it is... screw it i guess? just get damage?
	return Stat::FlatDamage;
}