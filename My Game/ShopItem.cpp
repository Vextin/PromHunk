#include "ShopItem.h"
//Use to find a shop card sprite by ID
const std::map<std::string, eSprite> ShopItem::idToSprite =
{
	{"damage_1",eSprite::ShopCard_Damage1},
	{"damage_2",eSprite::ShopCard_Damage1},
	{"damage_3",eSprite::ShopCard_Damage1},
	{"damage_4",eSprite::ShopCard_Damage1},
	{"pctDamage_1",eSprite::ShopCard_Damage1},
	{"pctDamage_2",eSprite::ShopCard_Damage1}
};

//Complete constructor if you know all of the fields
ShopItem::ShopItem(std::string id, ShopItem::Stat stat, float val)
{

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
	if (s.compare("PctDamage") == 0)
	{
		return Stat::PctDamage;
	}
	if (s.compare("FlatHealth") == 0)
	{
		return Stat::FlatHealth;
	}
	if (s.compare("PctHealth") == 0)
	{
		return Stat::PctHealth;
	}
	if (s.compare("FlatSpeed") == 0)	{
		return Stat::FlatSpeed;
	}
	if (s.compare("PctSpeed") == 0)
	{
		return Stat::PctSpeed;
	}
	if (s.compare("FlatAttackSpeed") == 0)
	{
		return Stat::FlatAttackSpeed;
	}
	if (s.compare("PctAttackSpeed") == 0)
	{
		return Stat::PctAttackSpeed;
	}
	if (s.compare("FlatAuraDamage") == 0)
	{
		return Stat::FlatAuraDamage;
	}
	if (s.compare("PctAuraDamage") == 0)
	{
		return Stat::PctAuraDamage;
	}
	//if we don't know what stat it is... screw it i guess? just get damage?
	return Stat::FlatDamage;
}