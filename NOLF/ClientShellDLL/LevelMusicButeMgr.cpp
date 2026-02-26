// ----------------------------------------------------------------------- //
//
// MODULE  : LevelMusicButeMgr.cpp
//
// PURPOSE : Maps level names to PS2 WAV music files (loaded from LevelMusic.txt)
//
// ----------------------------------------------------------------------- //

#include "stdafx.h"
#include "LevelMusicButeMgr.h"

// Attribute keys inside each [levelname] section
#define LMM_WAV_KEY  "WAV"

// Sentinel value in LevelMusic.txt that means "no track known"
#define LMM_UNKNOWN  "unknown_music.wav"

CLevelMusicButeMgr* g_pLevelMusicButeMgr = nullptr;

// ---------------------------------------------------------------------------

CLevelMusicButeMgr::CLevelMusicButeMgr()
    : m_bLoaded(LTFALSE)
{
}

CLevelMusicButeMgr::~CLevelMusicButeMgr()
{
    Term();
}

LTBOOL CLevelMusicButeMgr::Init(ILTCSBase* pInterface, const char* szAttributeFile)
{
    if (g_pLevelMusicButeMgr || !szAttributeFile) return LTFALSE;

    // Always register the global pointer so GetWAVForLevel() is safely callable
    // even when the .rez does not contain LevelMusic.txt (e.g. stripped builds).
    g_pLevelMusicButeMgr = this;

    if (!Parse(pInterface, szAttributeFile))
    {
        // Non-fatal: PS2 music simply won't play. Log and continue.
#ifndef _FINAL
        if (pInterface)
        {
            pInterface->CPrint("CLevelMusicButeMgr: WARNING – '%s' not found or failed to parse. "
                               "PS2 music will be silent.", szAttributeFile);
        }
#endif
        m_bLoaded = LTFALSE;
        return LTFALSE;   // caller can log/handle, but the game keeps running
    }

    m_bLoaded = LTTRUE;
    return LTTRUE;
}

void CLevelMusicButeMgr::Term()
{
    m_bLoaded = LTFALSE;
    g_pLevelMusicButeMgr = nullptr;
}

// ---------------------------------------------------------------------------
// GetWAVForLevel
//
// Looks up the WAV filename for the given world name.
// The section name in LevelMusic.txt is the lowercase stem of the world name
// (e.g. "m01s01a"), and the value is the WAV filename under Music\PS2Music\.
//
// Returns an empty CString when:
//  - pszWorldName is NULL or empty
//  - no matching section exists in LevelMusic.txt
//  - the section maps to "unknown_music.wav"
// ---------------------------------------------------------------------------
CString CLevelMusicButeMgr::GetWAVForLevel(const char* pszWorldName)
{
    // Datei wurde nicht geladen (fehlt in der .rez) – still degradieren
    if (!m_bLoaded)
        return "";

    if (!pszWorldName || !pszWorldName[0])
        return "";

    std::string sStem = ExtractStem(pszWorldName);
    if (sStem.empty())
        return "";

    // Section name == level stem (e.g. "m01s01a")
    if (!m_buteMgr.Exist(sStem.c_str()))
        return "";

    CString sWAV = m_buteMgr.GetString(sStem.c_str(), LMM_WAV_KEY);

    // Treat the sentinel as "no track"
    if (sWAV.CompareNoCase(LMM_UNKNOWN) == 0)
        return "";

    return sWAV;
}

// ---------------------------------------------------------------------------
// ExtractStem  (private helper)
//
// "Worlds\m01s01a.ltc"  ->  "m01s01a"
// "M02S01B"             ->  "m02s01b"
// ---------------------------------------------------------------------------
std::string CLevelMusicButeMgr::ExtractStem(const char* pszWorldName) const
{
    // Find last path separator
    const char* pStem = pszWorldName;
    for (const char* p = pszWorldName; *p; ++p)
    {
        if (*p == '\\' || *p == '/')
            pStem = p + 1;
    }

    // Copy up to '.' and convert to lower-case
    std::string sStem;
    for (int i = 0; pStem[i] && pStem[i] != '.'; ++i)
    {
        char c = pStem[i];
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        sStem += c;
    }

    return sStem;
}
