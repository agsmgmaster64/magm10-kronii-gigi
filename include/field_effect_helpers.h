#ifndef GUARD_FIELD_EFFECT_HELPERS_H
#define GUARD_FIELD_EFFECT_HELPERS_H

// States for bobbing up and down while surfing
enum {
    // No bobbing
    BOB_NONE,
    // Both the surf blob/mon should bob up and down
    BOB_PLAYER_AND_MON,
    // Only the surf blob/mon should bob up and down
    // For when the player has jumped/flown off
    BOB_JUST_MON,
};

// States for ORAS Dowsing
enum
{
    ORASD_WIGGLE_NONE,
    ORASD_WIGGLE_SLOW,
    ORASD_WIGGLE_NORMAL,
    ORASD_WIGGLE_FAST,
    ORASD_WIGGLE_FASTER
};

extern const u16 gFieldEffectPal_ORASDowsing[];

u8 CreateWarpArrowSprite(void);
u8 StartUnderwaterSurfBlobBobbing(u8 blobSpriteId);
void SetSurfBlob_BobState(u8 spriteId, u8 state);
void SetSurfBlob_DontSyncAnim(u8 spriteId, bool8 dontSync);
void SetSurfBlob_PlayerOffset(u8 spriteId, bool8 hasOffset, s16 offset);
bool8 UpdateRevealDisguise(struct ObjectEvent *objectEvent);
void StartRevealDisguise(struct ObjectEvent *objectEvent);
void StartAshFieldEffect(s16 x, s16 y, u16 metatileId, s16 delay);
void SetUpReflection(struct ObjectEvent *objectEvent, struct Sprite *sprite, bool8 stillReflection);
void SetUpShadow(struct ObjectEvent *objectEvent);
u32 StartFieldEffectForObjectEvent(u8, struct ObjectEvent *objectEvent);
u8 FindTallGrassFieldEffectSpriteId(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y);
u8 FindSnowGrassFieldEffectSpriteId(u8 localId, u8 mapNum, u8 mapGroup, s16 x, s16 y);
void UpdateRayquazaSpotlightEffect(struct Sprite *sprite);
void UpdateShadowFieldEffect(struct Sprite *sprite);
void UpdateTallGrassFieldEffect(struct Sprite *sprite);
void WaitFieldEffectSpriteAnim(struct Sprite *sprite);
void UpdateAshFieldEffect(struct Sprite *sprite);
void UpdateSurfBlobFieldEffect(struct Sprite *sprite);
void UpdateJumpImpactEffect(struct Sprite *sprite);
void UpdateFootprintsTireTracksFieldEffect(struct Sprite *sprite);
void UpdateSplashFieldEffect(struct Sprite *sprite);
void UpdateLongGrassFieldEffect(struct Sprite *sprite);
void UpdateSandPileFieldEffect(struct Sprite *sprite);
void UpdateDisguiseFieldEffect(struct Sprite *sprite);
void UpdateShortGrassFieldEffect(struct Sprite *sprite);
void UpdateHotSpringsWaterFieldEffect(struct Sprite *sprite);
void UpdateBubblesFieldEffect(struct Sprite *sprite);
void UpdateSparkleFieldEffect(struct Sprite *sprite);
void SetSpriteInvisible(u8 spriteId);
void ShowWarpArrowSprite(u8 spriteId, u8 direction, s16 x, s16 y);
void UpdateSnowGrassFieldEffect(struct Sprite *);
void UpdateORASDowsingFieldEffect(struct Sprite *sprite);
void UpdateDowsingAnimDirection(struct Sprite *sprite, struct ObjectEvent *playerObj);
void EndORASDowsing(void);

#endif //GUARD_FIELD_EFFECT_HELPERS_H
