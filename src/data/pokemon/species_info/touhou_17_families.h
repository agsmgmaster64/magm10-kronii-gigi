#ifdef __INTELLISENSE__
const struct SpeciesInfo gSpeciesInfoTouhou17[] =
{
#endif

    [SPECIES_CHIBI_SAKI] =
    {
        .baseHP        = 75,
        .baseAttack    = 110,
        .baseDefense   = 50,
        .baseSpeed     = 100,
        .baseSpAttack  = 45,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_BEAST, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 74,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FIELD),
        .abilities = { ABILITY_STAMINA, ABILITY_QUICK_FEET, ABILITY_BEAST_BOOST },
        .sourceGame = SOURCE_WBAWC,
        .noFlip = TRUE,
        .speciesName = _("CSaki"),
        .cryId = CRY_SAKI,
        .natDexNum = NATIONAL_DEX_KLINKLANG,
        .categoryName = _("Gear"),
        .height = 6,
        .weight = 810,
        .description = COMPOUND_STRING(
            "Its red core functions as an energy tank.\n"
            "It is rotated at high speed for a rapid\n"
            "energy charge. It fires the charged energy\n"
            "through its spikes into an area."),
        .pokemonScale = 422,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CSaki,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_GenericBlinkingAnim,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 3,
        .backPic = gMonBackPic_CSaki,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CSaki,
        .shinyPalette = gMonShinyPalette_CSaki,
        .iconSprite = gMonIcon_CSaki,
        .iconPalIndex = 1,
        SHADOW(0, 11, SHADOW_SIZE_M)
        FOOTPRINT(CSaki)
        .levelUpLearnset = sCSakiLevelUpLearnset,
        .teachableLearnset = sCSakiTeachableLearnset,
        //.eggMoveLearnset = sCNitoriEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 38, SPECIES_NORMAL_SAKI},
                                {EVO_ITEM, ITEM_NEUTRAL_HEART, SPECIES_NORMAL_SAKI, CONDITIONS({IF_PAST_LEVEL, 38})}),
    },

    [SPECIES_NORMAL_SAKI] =
    {
        .baseHP        = 95,
        .baseAttack    = 135,
        .baseDefense   = 75,
        .baseSpeed     = 125,
        .baseSpAttack  = 65,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_BEAST, TYPE_FLYING),
        .catchRate = 45,
        .expYield = 208,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE, EGG_GROUP_FIELD),
        .abilities = { ABILITY_STAMINA, ABILITY_QUICK_FEET, ABILITY_BEAST_BOOST },
        .sourceGame = SOURCE_WBAWC,
        .noFlip = TRUE,
        .speciesName = _("Saki"),
        .cryId = CRY_SAKI,
        .natDexNum = NATIONAL_DEX_TYNAMO,
        .categoryName = _("EleFish"),
        .height = 2,
        .weight = 3,
        .description = COMPOUND_STRING(
            "These Pokémon move in schools.\n"
            "One alone can emit only a trickle of\n"
            "electricity, so a group of them gathers\n"
            "to unleash a powerful electric shock."),
        .pokemonScale = 682,
        .pokemonOffset = 24,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Saki,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_GenericBlinkingAnim,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 5,
        .backPic = gMonBackPic_Saki,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Saki,
        .shinyPalette = gMonShinyPalette_Saki,
        .iconSprite = gMonIcon_Saki,
        .iconPalIndex = 1,
        SHADOW(-2, 14, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Saki)
        .levelUpLearnset = sSakiLevelUpLearnset,
        .teachableLearnset = sSakiTeachableLearnset,
    },

#ifdef __INTELLISENSE__
};
#endif
