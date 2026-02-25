// ----------------------------------------------------------------------- //
//
// MODULE  : LevelMusicButeMgr.cpp
//
// PURPOSE : Maps level names to PS2 WAV music files
//
// ----------------------------------------------------------------------- //

#include "stdafx.h"
#include "LevelMusicButeMgr.h"
#include <string.h>

// ---------------------------------------------------------------------------
// Static mapping table  (level stem -> WAV path relative to game root)
// "unknown_music.wav" entries are omitted intentionally – those levels have
// no confirmed PS2 track and will fall back to DirectMusic silence.
// ---------------------------------------------------------------------------

struct LevelMusicEntry
{
    const char* pszLevel;   // lower-case world stem, no path, no extension
    const char* pszWAV;     // path relative to game root
};

static const LevelMusicEntry s_LevelMusicTable[] =
{
    { "m01s01",  "Music\\PS2Music\\nolf_ps2_13.wav" },
    { "m01s02",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m01s03",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m01s04",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m02s01",  "Music\\PS2Music\\nolf_ps2_01.wav" }, // B: nolf_ps2_04 (m02s01_B)
    { "m02s02",  "Music\\PS2Music\\nolf_ps2_05.wav" }, // B: nolf_ps2_07 (m02s02_B)
    { "m02s03",  "Music\\PS2Music\\nolf_ps2_08.wav" }, // B: nolf_ps2_01 (m02s03_B)
    { "m03s01",  "Music\\PS2Music\\nolf_ps2_03.wav" },
    { "m03s02",  "Music\\PS2Music\\nolf_ps2_09.wav" }, // B: nolf_ps2_03 (m03s02_B)
    { "m04s01",  "Music\\PS2Music\\nolf_ps2_10.wav" }, // B: nolf_ps2_12 (m04s01_B)
    { "m04s02",  "Music\\PS2Music\\nolf_ps2_10.wav" }, // B: nolf_ps2_12 (m04s02_B)
    { "m05s01",  "Music\\PS2Music\\nolf_ps2_01.wav" }, // B: nolf_ps2_04 (m05s01_B)
    { "m05s02",  "Music\\PS2Music\\nolf_ps2_07.wav" }, // B: nolf_ps2_08 (m05s02_B)
    { "m05s03",  "Music\\PS2Music\\nolf_ps2_01.wav" },
    { "m05s04",  "Music\\PS2Music\\nolf_ps2_04.wav" }, // B: nolf_ps2_07 (m05s04_B)
    { "m05s05",  "Music\\PS2Music\\nolf_ps2_08.wav" }, // B: nolf_ps2_01 (m05s05_B)
    { "m06s01",  "Music\\PS2Music\\nolf_ps2_01.wav" },
    { "m06s02",  "Music\\PS2Music\\nolf_ps2_03.wav" },
    { "m06s03",  "Music\\PS2Music\\nolf_ps2_07.wav" }, // B: nolf_ps2_08 (m06s03_B)
    { "m07s01",  "Music\\PS2Music\\nolf_ps2_03.wav" },
    { "m07s02",  "Music\\PS2Music\\nolf_ps2_06.wav" }, // B: nolf_ps2_03 (m07s02_B), C: nolf_ps2_06 (m07s02_C)
    { "m07s03",  "Music\\PS2Music\\nolf_ps2_06.wav" }, // B: nolf_ps2_03 (m07s03_B)
    { "m08s01",  "Music\\PS2Music\\nolf_ps2_01.wav" },
    // m08s02: kein PS2-Track bekannt
    { "m08s03",  "Music\\PS2Music\\nolf_ps2_05.wav" },
    { "m08s04",  "Music\\PS2Music\\nolf_ps2_07.wav" },
    { "m08s05",  "Music\\PS2Music\\nolf_ps2_08.wav" },
    { "m08s06",  "Music\\PS2Music\\nolf_ps2_01.wav" }, // B: nolf_ps2_04 (m08s06_B)
    { "m09s01",  "Music\\PS2Music\\nolf_ps2_01.wav" },
    { "m09s02",  "Music\\PS2Music\\nolf_ps2_03.wav" }, // B: nolf_ps2_04 (m09s02_B)
    { "m09s03",  "Music\\PS2Music\\nolf_ps2_08.wav" }, // B: nolf_ps2_01 (m09s03_B)
    { "m10s01",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m10s02",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m10s03",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m10s04",  "Music\\PS2Music\\nolf_ps2_02.wav" },
    { "m11s01",  "Music\\PS2Music\\nolf_ps2_06.wav" },
    { "m11s02",  "Music\\PS2Music\\nolf_ps2_06.wav" },
    { "m12s01",  "Music\\PS2Music\\nolf_ps2_05.wav" },
    { "m12s02",  "Music\\PS2Music\\nolf_ps2_05.wav" },
    { "m12s03",  "Music\\PS2Music\\nolf_ps2_05.wav" },
    { "m12s04",  "Music\\PS2Music\\nolf_ps2_05.wav" },
    { "m13s01",  "Music\\PS2Music\\nolf_ps2_11.wav" },
    { "m13s02",  "Music\\PS2Music\\nolf_ps2_11.wav" },
    { "m13s03",  "Music\\PS2Music\\nolf_ps2_11.wav" },
    { "m13s04",  "Music\\PS2Music\\nolf_ps2_11.wav" },
    { "m14s01",  "Music\\PS2Music\\nolf_ps2_09.wav" },
    { "m14s02",  "Music\\PS2Music\\nolf_ps2_09.wav" },
    { "m15s01",  "Music\\PS2Music\\nolf_ps2_03.wav" }, // B: nolf_ps2_09 (m15s01_B)
    { "m15s02",  "Music\\PS2Music\\nolf_ps2_03.wav" }, // B: unknown (m15s02_B)
    // m16s01-m16s04: PC-GOTY only, kein PS2-Aequivalent
    { "thiefmission1", "Music\\PS2Music\\nolf_ps2_03.wav" },
    { "thiefmission2", "Music\\PS2Music\\nolf_ps2_07.wav" },
    { "thiefmission3", "Music\\PS2Music\\nolf_ps2_11.wav" },
};


static const int s_nTableSize = sizeof(s_LevelMusicTable) / sizeof(s_LevelMusicTable[0]);

// ---------------------------------------------------------------------------
// GetPS2MusicForLevel
//
// Strips any path and extension from pszWorldName, does a case-insensitive
// linear search and returns the matching WAV path, or NULL if not found.
// ---------------------------------------------------------------------------
const char* GetPS2MusicForLevel(const char* pszWorldName)
{
    if (!pszWorldName || !pszWorldName[0])
        return NULL;

    // Extract the stem: strip leading path separators and extension
    // e.g. "Worlds\m01s01" -> "m01s01"  or  "m01s01.ltc" -> "m01s01"
    const char* pStem = pszWorldName;

    // Find last backslash or forward slash
    const char* p = pszWorldName;
    while (*p)
    {
        if (*p == '\\' || *p == '/')
            pStem = p + 1;
        ++p;
    }

    // Copy stem, strip extension
    char szStem[64];
    int i = 0;
    while (pStem[i] && pStem[i] != '.' && i < 63)
    {
        // lower-case
        char c = pStem[i];
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        szStem[i] = c;
        ++i;
    }
    szStem[i] = '\0';

    if (!szStem[0])
        return NULL;

    // Linear search (87 entries, no need for a hash map)
    for (int n = 0; n < s_nTableSize; ++n)
    {
        if (_stricmp(s_LevelMusicTable[n].pszLevel, szStem) == 0)
            return s_LevelMusicTable[n].pszWAV;
    }

    return NULL;
}
