#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_DEBT_SPIRAL) == EFFECT_THIRD_EYE);
}

// For some reason SINGLE_BATTLE_TEST didn't catch these two issues.
WILD_BATTLE_TEST("Ion Deluge works the same way as always when used by a mon with Volt Absorb")
{
    GIVEN {
        PLAYER(SPECIES_CHIBI_YUUGI);
        OPPONENT(SPECIES_NORMAL_NITORI) { Ability(ABILITY_VOLT_ABSORB); HP(1); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_DEBT_SPIRAL); }
    } SCENE {
        MESSAGE("The wild Lanturn used Ion Deluge!");
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_VOLT_ABSORB);
            HP_BAR(opponent);
            MESSAGE("Wild Lanturn restored HP using its Volt Absorb!");
        }
        MESSAGE("A deluge of ions showers the battlefield!");
    }
}

WILD_BATTLE_TEST("Ion Deluge works the same way as always when used by a mon with Lightning Rod / Motor Drive")
{
    u16 ability;
    PARAMETRIZE { ability = ABILITY_LIGHTNING_ROD; }
    PARAMETRIZE { ability = ABILITY_MOTOR_DRIVE; }

    GIVEN {
        PLAYER(SPECIES_CHIBI_YUUGI);
        OPPONENT(SPECIES_ZEBSTRIKA) { Ability(ability); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_DEBT_SPIRAL); }
    } SCENE {
        MESSAGE("The wild Zebstrika used Ion Deluge!");
        NONE_OF {
            ABILITY_POPUP(opponent, ability);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            MESSAGE("Wild Zebstrika's Sp. Atk rose!");
            MESSAGE("Wild Zebstrika's Speed rose!");
        }
        MESSAGE("A deluge of ions showers the battlefield!");
    }
}

SINGLE_BATTLE_TEST("Ion Deluge makes Normal type moves Electric type")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SCRATCH) == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_GOLBAT);
    } WHEN {
        TURN { MOVE(opponent, MOVE_DEBT_SPIRAL); MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        MESSAGE("The opposing Golbat used Ion Deluge!");
        MESSAGE("A deluge of ions showers the battlefield!");
        MESSAGE("Wobbuffet used Scratch!");
        MESSAGE("It's super effective!"); // Because Scratch is now electric type.
    }
}
