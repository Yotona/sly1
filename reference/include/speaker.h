/**
 * @file speaker.h
 *
 * @brief Declarations for the speaker system.
*/
#ifndef SPEAKER_H
#define SPEAKER_H

#include <util.h>
#include <game.h>
#include <joy.h>
#include <mat.h>
#include <font.h>
#include <vec.h>

typedef int GRFPVA;

/**
 * @brief Speaker
 *
 * Either represents a speaker that emits sound in the game world, or a
 * physical speaker in the real world. More research is needed.
 *
 * @todo Figure out exactly what this struct represents.
 * @todo Identify missing fields on this struct.
*/
struct SPEAKER
{
    char padding[0x2e0];
    struct RGBA rgbaText;
    float radFOV;
    float sDistCm;
    float uxTv;
    float uyTv;
    undefined4 field_0x2f4;
    undefined4 field_0x2f8;
    undefined4 field_0x2fc;
    struct VECTOR dposLight;
    struct VECTOR dposLightConfront;
    float uxTvConfront;
    float uyTvConfront;
    OID oidSmIdle;
    struct SM_conflict* psmIdle;
    struct SMA* psmaIdle;
};

/**
 * @brief Dialog Player
*/
struct DP
{
    uint grfdp;
    DPK dpk;
    SPEAKER* pspeakerLeft;
    SPEAKER* pspeakerRight;
    ASEGA* pasegaLipsync;
    float tPauseMin;
};

#endif // SPEAKER_H
