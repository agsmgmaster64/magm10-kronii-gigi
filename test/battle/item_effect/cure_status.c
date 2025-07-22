#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Paralyze Heal heals a battler from being paralyzed")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_PARALYZE_HEAL].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(STATUS1_PARALYSIS); }
        OPPONENT(SPECIES_CHIBI_YUUGI);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_PARALYZE_HEAL, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Antidote heals a battler from being poisoned")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_ANTIDOTE].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(STATUS1_POISON); }
        OPPONENT(SPECIES_CHIBI_YUUGI);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_ANTIDOTE, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Antidote heals a battler from being badly poisoned")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_ANTIDOTE].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(STATUS1_TOXIC_POISON); }
        OPPONENT(SPECIES_CHIBI_YUUGI);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_ANTIDOTE, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Antidote resets Toxic Counter")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_ANTIDOTE].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI);
        OPPONENT(SPECIES_CHIBI_YUUGI);
    } WHEN {
        TURN { MOVE(opponent, MOVE_TOXIC); }
        TURN { ; }
        TURN { USE_ITEM(player, ITEM_ANTIDOTE, partyIndex: 0); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Toxic!");
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Awakening heals a battler from being asleep")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_AWAKENING].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(STATUS1_SLEEP); }
        OPPONENT(SPECIES_CHIBI_YUUGI);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_AWAKENING, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Burn Heal heals a battler from being burned")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_BURN_HEAL].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(STATUS1_BURN); }
        OPPONENT(SPECIES_CHIBI_YUUGI);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_BURN_HEAL, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Ice Heal heals a battler from being frozen or frostbite")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_ICE_HEAL].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_WOBBUFFET) { Status1(status); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_ICE_HEAL, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Full Heal heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_FULL_HEAL].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_FULL_HEAL, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Heal Powder heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_HEAL_POWDER].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_HEAL_POWDER, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Pewter Crunchies heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_GEYSER_WATER].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_GEYSER_WATER, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Lava Cookies heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_LAVA_COOKIE].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_LAVA_COOKIE, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Rage Candy Bar heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_BEER_BOTTLE].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_BEER_BOTTLE, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Old Gateu heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_UNAGI_LUNCH].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_UNAGI_LUNCH, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Casteliacone heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_SAKE_GOURD].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_SAKE_GOURD, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Lumiose Galette heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_EIENTEI_POTION].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_EIENTEI_POTION, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");;
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Shalour Sable heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_HEAVEN_PEACH].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_HEAVEN_PEACH, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Big Malasada heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_REVIVAL_FLOWER].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI) { Status1(status); }
        OPPONENT(SPECIES_NORMAL_KOSUZU);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_REVIVAL_FLOWER, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Jubilife Muffin heals a battler from any primary status")
{
    u16 status;
    PARAMETRIZE { status = STATUS1_SLEEP; }
    PARAMETRIZE { status = STATUS1_POISON; }
    PARAMETRIZE { status = STATUS1_BURN; }
    PARAMETRIZE { status = STATUS1_FREEZE; }
    PARAMETRIZE { status = STATUS1_PARALYSIS; }
    PARAMETRIZE { status = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status = STATUS1_FROSTBITE; }
    GIVEN {
        ASSUME(gItemsInfo[ITEM_JUBILIFE_MUFFIN].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_WOBBUFFET) { Status1(status); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { USE_ITEM(player, ITEM_JUBILIFE_MUFFIN, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT_EQ(player->status1, STATUS1_NONE);
    }
}

SINGLE_BATTLE_TEST("Full Heal, Heal Powder and Local Specialties heal a battler from being confused")
{
    u16 item;
    PARAMETRIZE { item = ITEM_FULL_HEAL; }
    PARAMETRIZE { item = ITEM_HEAL_POWDER; }
    PARAMETRIZE { item = ITEM_GEYSER_WATER; }
    PARAMETRIZE { item = ITEM_LAVA_COOKIE; }
    PARAMETRIZE { item = ITEM_BEER_BOTTLE; }
    PARAMETRIZE { item = ITEM_UNAGI_LUNCH; }
    PARAMETRIZE { item = ITEM_SAKE_GOURD; }
    PARAMETRIZE { item = ITEM_EIENTEI_POTION; }
    PARAMETRIZE { item = ITEM_HEAVEN_PEACH; }
    PARAMETRIZE { item = ITEM_REVIVAL_FLOWER; }
    PARAMETRIZE { item = ITEM_JUBILIFE_MUFFIN; }
    GIVEN {
        ASSUME(gItemsInfo[item].battleUsage == EFFECT_ITEM_CURE_STATUS);
        PLAYER(SPECIES_CHIBI_YUUGI);
        OPPONENT(SPECIES_ATTACK_RAN);
    } WHEN {
        TURN { MOVE(opponent, MOVE_CONFUSE_RAY); }
        TURN { USE_ITEM(player, item, partyIndex: 0); }
    } SCENE {
        MESSAGE("Wobbuffet had its status healed!");
    } THEN {
        EXPECT(player->volatiles.confusionTurns == 0);
    }
}
