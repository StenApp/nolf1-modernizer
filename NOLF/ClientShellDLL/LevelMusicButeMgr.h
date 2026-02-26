// ----------------------------------------------------------------------- //
//
// MODULE  : LevelMusicButeMgr.h
//
// PURPOSE : Maps level names to PS2 WAV music files (loaded from LevelMusic.txt)
//
// ----------------------------------------------------------------------- //

#ifndef __LEVEL_MUSIC_BUTE_MGR_H__
#define __LEVEL_MUSIC_BUTE_MGR_H__

#pragma once

#include "GameButeMgr.h"
#include "ltbasetypes.h"
#include "iltcsbase.h"
#include <string>

class CLevelMusicButeMgr;
extern CLevelMusicButeMgr* g_pLevelMusicButeMgr;

class CLevelMusicButeMgr : public CGameButeMgr
{
public:
    CLevelMusicButeMgr();
    ~CLevelMusicButeMgr();

    LTBOOL  Init(ILTCSBase* pInterface, const char* szAttributeFile = "Attributes\\LevelMusic.txt");
    void    Term();

    // Returns the WAV filename (e.g. "nolf_ps2_01.wav") for the given world name.
    // pszWorldName may contain a path and/or extension – both are stripped automatically.
    // Returns an empty CString if no mapping exists or the level maps to "unknown_music.wav".
    CString GetWAVForLevel(const char* pszWorldName);

private:
    LTBOOL      m_bLoaded;  // LTFALSE wenn LevelMusic.txt nicht geladen werden konnte

    // Strips path and extension from a world name and returns the lowercase stem.
    std::string ExtractStem(const char* pszWorldName) const;
};

#endif // __LEVEL_MUSIC_BUTE_MGR_H__
