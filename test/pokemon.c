#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/overworld_script.h"
#include "test/test.h"

TEST("Nature independent from Hidden Nature")
{
    u32 i, j, nature = 0, hiddenNature = 0;
    struct Pokemon mon;
    for (i = 0; i < NUM_NATURES; i++)
    {
        for (j = 0; j < NUM_NATURES; j++)
        {
            PARAMETRIZE { nature = i; hiddenNature = j; }
        }
    }
    CreateMonWithNature(&mon, SPECIES_CHIBI_AMELIA, 100, 0, nature);
    SetMonData(&mon, MON_DATA_HIDDEN_NATURE, &hiddenNature);
    EXPECT_EQ(GetNature(&mon), nature);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HIDDEN_NATURE), hiddenNature);
}

TEST("Terastallization type defaults to primary or secondary type")
{
    u32 i, teraType;
    struct Pokemon mon;
    for (i = 0; i < 128; i++) PARAMETRIZE {}
    CreateMon(&mon, SPECIES_CHIBI_MEDICINE, 100, 0, FALSE, 0, OT_ID_PRESET, 0);
    teraType = GetMonData(&mon, MON_DATA_TERA_TYPE);
    EXPECT(teraType == GetSpeciesType(SPECIES_PIDGEY, 0)
        || teraType == GetSpeciesType(SPECIES_PIDGEY, 1));
}

TEST("Terastallization type can be set to any type except TYPE_NONE")
{
    u32 i, teraType;
    struct Pokemon mon;
    for (i = 1; i < NUMBER_OF_MON_TYPES; i++)
    {
        PARAMETRIZE { teraType = i; }
    }
    CreateMon(&mon, SPECIES_CHIBI_AMELIA, 100, 0, FALSE, 0, OT_ID_PRESET, 0);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &teraType);
    EXPECT_EQ(teraType, GetMonData(&mon, MON_DATA_TERA_TYPE));
}

TEST("Terastallization type is reset to the default types when setting Tera Type back to TYPE_NONE")
{
    u32 i, teraType, typeNone;
    struct Pokemon mon;
    for (i = 1; i < NUMBER_OF_MON_TYPES; i++)
    {
        PARAMETRIZE { teraType = i; typeNone = TYPE_NONE; }
    }
    CreateMon(&mon, SPECIES_CHIBI_MEDICINE, 100, 0, FALSE, 0, OT_ID_PRESET, 0);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &teraType);
    EXPECT_EQ(teraType, GetMonData(&mon, MON_DATA_TERA_TYPE));
    if (typeNone == TYPE_NONE)
        typeNone = GetTeraTypeFromPersonality(&mon);
    SetMonData(&mon, MON_DATA_TERA_TYPE, &typeNone);
    typeNone = GetMonData(&mon, MON_DATA_TERA_TYPE);
    EXPECT(typeNone == GetSpeciesType(SPECIES_PIDGEY, 0)
        || typeNone == GetSpeciesType(SPECIES_PIDGEY, 1));
}

TEST("Shininess independent from PID and OTID")
{
    u32 pid, otId, data;
    bool32 isShiny;
    struct Pokemon mon;
    PARAMETRIZE { pid = 0; otId = 0; }
    CreateMon(&mon, SPECIES_CHIBI_YUUGI, 100, 0, TRUE, pid, OT_ID_PRESET, otId);
    isShiny = IsMonShiny(&mon);
    data = !isShiny;
    SetMonData(&mon, MON_DATA_IS_SHINY, &data);
    EXPECT_EQ(pid, GetMonData(&mon, MON_DATA_PERSONALITY));
    EXPECT_EQ(otId, GetMonData(&mon, MON_DATA_OT_ID));
    EXPECT_EQ(!isShiny, GetMonData(&mon, MON_DATA_IS_SHINY));
}

TEST("Hyper Training increases stats without affecting IVs")
{
    u32 data, hp, atk, def, speed, spatk, spdef, friendship = 0;
    struct Pokemon mon;
    CreateMon(&mon, SPECIES_WOBBUFFET, 100, 3, TRUE, 0, OT_ID_PRESET, 0);

    // Consider B_FRIENDSHIP_BOOST.
    SetMonData(&mon, MON_DATA_FRIENDSHIP, &friendship);
    CalculateMonStats(&mon);

    hp = GetMonData(&mon, MON_DATA_HP);
    atk = GetMonData(&mon, MON_DATA_ATK);
    def = GetMonData(&mon, MON_DATA_DEF);
    speed = GetMonData(&mon, MON_DATA_SPEED);
    spatk = GetMonData(&mon, MON_DATA_SPATK);
    spdef = GetMonData(&mon, MON_DATA_SPDEF);

    data = TRUE;
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_HP, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_ATK, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_DEF, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_SPEED, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_SPATK, &data);
    SetMonData(&mon, MON_DATA_HYPER_TRAINED_SPDEF, &data);
    CalculateMonStats(&mon);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ATK_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_DEF_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPATK_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPDEF_IV), 3);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPEED_IV), 3);

    EXPECT_EQ(hp - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_HP));
    EXPECT_EQ(atk - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_ATK));
    EXPECT_EQ(def - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_DEF));
    EXPECT_EQ(speed - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_SPEED));
    EXPECT_EQ(spatk - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_SPATK));
    EXPECT_EQ(spdef - 3 + MAX_PER_STAT_IVS, GetMonData(&mon, MON_DATA_SPDEF));
}

TEST("Status1 round-trips through BoxPokemon")
{
    u32 status1;
    struct Pokemon mon1, mon2;
    PARAMETRIZE { status1 = STATUS1_NONE; }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(1); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(2); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(3); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(4); }
    PARAMETRIZE { status1 = STATUS1_SLEEP_TURN(5); }
    PARAMETRIZE { status1 = STATUS1_POISON; }
    PARAMETRIZE { status1 = STATUS1_BURN; }
    PARAMETRIZE { status1 = STATUS1_FREEZE; }
    PARAMETRIZE { status1 = STATUS1_PARALYSIS; }
    PARAMETRIZE { status1 = STATUS1_TOXIC_POISON; }
    PARAMETRIZE { status1 = STATUS1_FROSTBITE; }
    CreateMon(&mon1, SPECIES_CHIBI_YUUGI, 100, 0, FALSE, 0, OT_ID_PRESET, 0);
    SetMonData(&mon1, MON_DATA_STATUS, &status1);
    BoxMonToMon(&mon1.box, &mon2);
    EXPECT_EQ(GetMonData(&mon2, MON_DATA_STATUS), status1);
}

TEST("canhypertrain/hypertrain affect MON_DATA_*_IV and recalculate stats")
{
    u32 atk, friendship = 0;
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 100, 0, FALSE, 0, OT_ID_PRESET, 0);

    // Consider B_FRIENDSHIP_BOOST.
    SetMonData(&gPlayerParty[0], MON_DATA_FRIENDSHIP, &friendship);
    CalculateMonStats(&gPlayerParty[0]);

    atk = GetMonData(&gPlayerParty[0], MON_DATA_ATK);

    RUN_OVERWORLD_SCRIPT(
        canhypertrain STAT_ATK, 0;
    );
    EXPECT(VarGet(VAR_RESULT));

    RUN_OVERWORLD_SCRIPT(
        hypertrain STAT_ATK, 0;
        canhypertrain STAT_ATK, 0;
    );
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 31);
    EXPECT_EQ(atk + 31, GetMonData(&gPlayerParty[0], MON_DATA_ATK));
    EXPECT(!VarGet(VAR_RESULT));
}

TEST("hasgigantamaxfactor/togglegigantamaxfactor affect MON_DATA_GIGANTAMAX_FACTOR")
{
    CreateMon(&gPlayerParty[0], SPECIES_CHIBI_AMELIA, 100, 0, FALSE, 0, OT_ID_PRESET, 0);

    RUN_OVERWORLD_SCRIPT(
        hasgigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));

    RUN_OVERWORLD_SCRIPT(
        togglegigantamaxfactor 0;
        hasgigantamaxfactor 0;
    );
    EXPECT(VarGet(VAR_RESULT));
    EXPECT(GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR));

    RUN_OVERWORLD_SCRIPT(
        togglegigantamaxfactor 0;
        hasgigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));
    EXPECT(!GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR));
}

TEST("togglegigantamaxfactor fails for Melmetal")
{
    CreateMon(&gPlayerParty[0], SPECIES_MELMETAL, 100, 0, FALSE, 0, OT_ID_PRESET, 0);

    RUN_OVERWORLD_SCRIPT(
        hasgigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));

    RUN_OVERWORLD_SCRIPT(
        togglegigantamaxfactor 0;
    );
    EXPECT(!VarGet(VAR_RESULT));
    EXPECT(!GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR));
}

TEST("givemon [simple]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_CHIBI_AMELIA, 100;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_CHIBI_AMELIA);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
}

TEST("givemon respects perfectIVCount")
{
    ZeroPlayerPartyMons();
    u32 perfectIVs[6] = {0};

    ASSUME(gSpeciesInfo[SPECIES_MEW].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_CELEBI].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_JIRACHI].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_MANAPHY].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_VICTINI].perfectIVCount == 3);
    ASSUME(gSpeciesInfo[SPECIES_DIANCIE].perfectIVCount == 3);

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_MEW, 100;
        givemon SPECIES_CELEBI, 100;
        givemon SPECIES_JIRACHI, 100;
        givemon SPECIES_MANAPHY, 100;
        givemon SPECIES_VICTINI, 100;
        givemon SPECIES_DIANCIE, 100;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_MEW);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_CELEBI);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_SPECIES), SPECIES_JIRACHI);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_SPECIES), SPECIES_MANAPHY);
    EXPECT_EQ(GetMonData(&gPlayerParty[4], MON_DATA_SPECIES), SPECIES_VICTINI);
    EXPECT_EQ(GetMonData(&gPlayerParty[5], MON_DATA_SPECIES), SPECIES_DIANCIE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[4], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[5], MON_DATA_LEVEL), 100);
    for (u32 j = 0; j < 6; j++)
    {
        for (u32 k = 0; k < NUM_STATS; k++)
        {
            if (GetMonData(&gPlayerParty[j], MON_DATA_HP_IV + k) == MAX_PER_STAT_IVS)
                perfectIVs[j]++;
        }
        EXPECT_GE(perfectIVs[j], 3);
    }
}

TEST("givemon respects FORM_CHANGE_ITEM_HOLD")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_ARCEUS_NORMAL, 100, item=ITEM_ZAP_PLATE;
        givemon SPECIES_ARCEUS_GRASS, 100, item=ITEM_ZAP_PLATE;
        givemon SPECIES_ARCEUS_ELECTRIC, 100, item=ITEM_ZAP_PLATE;
        givemon SPECIES_GIRATINA_ORIGIN, 100, item=ITEM_POTION;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_ARCEUS_ELECTRIC);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_SPECIES), SPECIES_ARCEUS_ELECTRIC);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_SPECIES), SPECIES_ARCEUS_ELECTRIC);
    EXPECT_EQ(GetMonData(&gPlayerParty[3], MON_DATA_SPECIES), SPECIES_GIRATINA_ALTERED);
}

TEST("givemon [moves]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_WOBBUFFET, 100, move1=MOVE_SCRATCH, move2=MOVE_SPLASH, move3=MOVE_NONE, move4=MOVE_NONE;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_CHIBI_AMELIA);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), MOVE_SCRATCH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), MOVE_SPLASH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), MOVE_NONE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), MOVE_NONE);
}

TEST("givemon [all]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_WOBBUFFET, 100, item=ITEM_LEFTOVERS, ball=ITEM_MASTER_BALL, nature=NATURE_BOLD, abilityNum=2, gender=MON_MALE, hpEv=1, atkEv=2, defEv=3, speedEv=4, spAtkEv=5, spDefEv=6, hpIv=7, atkIv=8, defIv=9, speedIv=10, spAtkIv=11, spDefIv=12, move1=MOVE_SCRATCH, move2=MOVE_SPLASH, move3=MOVE_CELEBRATE, move4=MOVE_EXPLOSION, isShiny=TRUE, gmaxFactor=TRUE, teraType=TYPE_FIRE, dmaxLevel=7;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_CHIBI_AMELIA);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_BENTO_BOX);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_POKEBALL), BALL_MASTER);
    EXPECT_EQ(GetNature(&gPlayerParty[0]), NATURE_BOLD);
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), GetSpeciesAbility(SPECIES_WOBBUFFET, 2));
    EXPECT_EQ(GetMonGender(&gPlayerParty[0]), MON_MALE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 1);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_EV), 2);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_EV), 3);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_EV), 4);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_EV), 5);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_EV), 6);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_IV), 7);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 8);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_IV), 9);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_IV), 10);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_IV), 11);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_IV), 12);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), MOVE_SCRATCH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), MOVE_SPLASH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), MOVE_CELEBRATE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), MOVE_EXPLOSION);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_TERA_TYPE), TYPE_FIRE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DYNAMAX_LEVEL), 7);
}

TEST("givemon [vars]")
{
    ZeroPlayerPartyMons();

    VarSet(VAR_TEMP_C, SPECIES_CHIBI_AMELIA);
    VarSet(VAR_TEMP_D, 100);
    VarSet(VAR_0x8000, ITEM_BENTO_BOX);
    VarSet(VAR_0x8001, ITEM_MASTER_ORB);
    VarSet(VAR_0x8002, NATURE_BOLD);
    VarSet(VAR_0x8003, 2);
    VarSet(VAR_0x8004, MON_MALE);
    VarSet(VAR_0x8005, 1);
    VarSet(VAR_0x8006, 2);
    VarSet(VAR_0x8007, 3);
    VarSet(VAR_0x8008, 4);
    VarSet(VAR_0x8009, 5);
    VarSet(VAR_0x800A, 6);
    VarSet(VAR_0x800B, 7);
    VarSet(VAR_TEMP_0, 8);
    VarSet(VAR_TEMP_1, 9);
    VarSet(VAR_TEMP_2, 10);
    VarSet(VAR_TEMP_3, 11);
    VarSet(VAR_TEMP_4, 12);
    VarSet(VAR_TEMP_5, MOVE_SCRATCH);
    VarSet(VAR_TEMP_6, MOVE_SPLASH);
    VarSet(VAR_TEMP_7, MOVE_CELEBRATE);
    VarSet(VAR_TEMP_8, MOVE_EXPLOSION);
    VarSet(VAR_TEMP_9, TRUE);
    VarSet(VAR_TEMP_A, TRUE);
    VarSet(VAR_TEMP_B, TYPE_FIRE);
    VarSet(VAR_TEMP_E, 7);

    RUN_OVERWORLD_SCRIPT(
        givemon VAR_TEMP_C, VAR_TEMP_D, item=VAR_0x8000, ball=VAR_0x8001, nature=VAR_0x8002, abilityNum=VAR_0x8003, gender=VAR_0x8004, hpEv=VAR_0x8005, atkEv=VAR_0x8006, defEv=VAR_0x8007, speedEv=VAR_0x8008, spAtkEv=VAR_0x8009, spDefEv=VAR_0x800A, hpIv=VAR_0x800B, atkIv=VAR_TEMP_0, defIv=VAR_TEMP_1, speedIv=VAR_TEMP_2, spAtkIv=VAR_TEMP_3, spDefIv=VAR_TEMP_4, move1=VAR_TEMP_5, move2=VAR_TEMP_6, move3=VAR_TEMP_7, move4=VAR_TEMP_8, isShiny=VAR_TEMP_9, gmaxFactor=VAR_TEMP_A, teraType=VAR_TEMP_B, dmaxLevel=VAR_TEMP_E;
    );

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), SPECIES_CHIBI_AMELIA);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_BENTO_BOX);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_POKEBALL), BALL_MASTER);
    EXPECT_EQ(GetNature(&gPlayerParty[0]), NATURE_BOLD);
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), GetSpeciesAbility(SPECIES_WOBBUFFET, 2));
    EXPECT_EQ(GetMonGender(&gPlayerParty[0]), MON_MALE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_EV), 1);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_EV), 2);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_EV), 3);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_EV), 4);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_EV), 5);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_EV), 6);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HP_IV), 7);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ATK_IV), 8);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DEF_IV), 9);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPEED_IV), 10);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPATK_IV), 11);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPDEF_IV), 12);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE1), MOVE_SCRATCH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE2), MOVE_SPLASH);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE3), MOVE_CELEBRATE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_MOVE4), MOVE_EXPLOSION);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_IS_SHINY), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_GIGANTAMAX_FACTOR), TRUE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_TERA_TYPE), TYPE_FIRE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_DYNAMAX_LEVEL), 7);
}

TEST("checkteratype/setteratype work")
{
    CreateMon(&gPlayerParty[0], SPECIES_CHIBI_MEDICINE, 100, 0, FALSE, 0, OT_ID_PRESET, 0);

    RUN_OVERWORLD_SCRIPT(
        checkteratype 0;
    );
    EXPECT(VarGet(VAR_RESULT) == TYPE_REASON);

    RUN_OVERWORLD_SCRIPT(
        setteratype TYPE_FIRE, 0;
        checkteratype 0;
    );
    EXPECT(VarGet(VAR_RESULT) == TYPE_FIRE);
}

TEST("createmon [simple]")
{
    ZeroPlayerPartyMons();

    RUN_OVERWORLD_SCRIPT(
        createmon 1, 0, SPECIES_CHIBI_AMELIA, 100;
        createmon 1, 1, SPECIES_CHIBI_MEDICINE, 10;
    );

    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_SPECIES), SPECIES_CHIBI_AMELIA);
    EXPECT_EQ(GetMonData(&gEnemyParty[0], MON_DATA_LEVEL), 100);
    EXPECT_EQ(GetMonData(&gEnemyParty[1], MON_DATA_SPECIES), SPECIES_CHIBI_MEDICINE);
    EXPECT_EQ(GetMonData(&gEnemyParty[1], MON_DATA_LEVEL), 10);
}

TEST("Pokémon level up learnsets fit within MAX_LEVEL_UP_MOVES and MAX_RELEARNER_MOVES")
{
    KNOWN_FAILING;

    u32 j, count, species = 0;
    const struct LevelUpMove *learnset;

    for(j = 0; j < SPECIES_EGG; j++)
    {
        PARAMETRIZE { species = j; }
    }

    learnset = GetSpeciesLevelUpLearnset(species);
    count = 0;
    for (j = 0; learnset[j].move != LEVEL_UP_MOVE_END; j++)
        count++;
    EXPECT_LT(count, MAX_LEVEL_UP_MOVES);
    EXPECT_LT(count, MAX_RELEARNER_MOVES - 1); // - 1 because at least one move is already known
}

TEST("Optimised GetMonData")
{
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 5, 0, FALSE, 0, OT_ID_PRESET, 0x12345678);
    u32 exp = 0x123456;
    SetMonData(&gPlayerParty[0], MON_DATA_EXP, &exp);
    struct Benchmark optimised,
        vanilla = (struct Benchmark) { .ticks = 137 }; // From prior testing
    u32 expGet = 0;
    BENCHMARK(&optimised) { expGet = GetMonData(&gPlayerParty[0], MON_DATA_EXP); }
    EXPECT_EQ(exp, expGet);
    EXPECT_FASTER(optimised, vanilla);
}

TEST("Optimised SetMonData")
{
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 5, 0, FALSE, 0, OT_ID_PRESET, 0x12345678);
    u32 exp = 0x123456;
    struct Benchmark optimised,
        vanilla = (struct Benchmark) { .ticks = 205 }; // From prior testing
    BENCHMARK(&optimised) { SetMonData(&gPlayerParty[0], MON_DATA_EXP, &exp); }
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_BAD_EGG), FALSE);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_EXP), exp);
    EXPECT_FASTER(optimised, vanilla);
}
