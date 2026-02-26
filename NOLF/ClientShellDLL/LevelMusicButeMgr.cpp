// ----------------------------------------------------------------------- //
//
// MODULE  : LevelMusicButeMgr.cpp
//
// PURPOSE : Maps level names to PS2 WAV music files (loaded from LevelMusic.txt)
//
// ----------------------------------------------------------------------- //

#include "stdafx.h"
#include "LevelMusicButeMgr.h"

#define LMM_LEVEL    "Level"
#define LMM_NAME_KEY "Name"
#define LMM_WAV_KEY  "WAV"

CLevelMusicButeMgr* g_pLevelMusicButeMgr = nullptr;

CLevelMusicButeMgr::CLevelMusicButeMgr()
    : m_bLoaded(LTFALSE)
    , m_nLevelCount(0)
{
}

CLevelMusicButeMgr::~CLevelMusicButeMgr()
{
    Term();
}

LTBOOL CLevelMusicButeMgr::Init(ILTCSBase* pInterface, const char* szAttributeFile)
{
    if (g_pLevelMusicButeMgr || !szAttributeFile) return LTFALSE;
    if (!Parse(pInterface, szAttributeFile))       return LTFALSE;

    // Count entries (Level0, Level1, ...)
    m_nLevelCount = 0;
    std::string sTag = LMM_LEVEL + std::to_string(m_nLevelCount);
    while (m_buteMgr.Exist(sTag.c_str()))
    {
        m_nLevelCount++;
        sTag = LMM_LEVEL + std::to_string(m_nLevelCount);
    }

    g_pLevelMusicButeMgr = this;
    m_bLoaded = LTTRUE;
    return LTTRUE;
}

void CLevelMusicButeMgr::Term()
{
    m_bLoaded = LTFALSE;
    m_nLevelCount = 0;
    g_pLevelMusicButeMgr = nullptr;
}

// ---------------------------------------------------------------------------
// GetWAVForLevel
//
// Searches in loop to get the right level stem (plain name like m01s01) and hands it back.
// Pass empty string if no entry is found.
// ---------------------------------------------------------------------------
CString CLevelMusicButeMgr::GetWAVForLevel(const char* pszWorldName)
{
    if (!m_bLoaded || !pszWorldName || !pszWorldName[0])
        return "";

    std::string sStem = ExtractStem(pszWorldName);
    if (sStem.empty())
        return "";

    for (int i = 0; i < m_nLevelCount; i++)
    {
        std::string sTag = LMM_LEVEL + std::to_string(i);
        CString sName = m_buteMgr.GetString(sTag.c_str(), LMM_NAME_KEY);
        if (sName.CompareNoCase(sStem.c_str()) == 0)
        {
            return m_buteMgr.GetString(sTag.c_str(), LMM_WAV_KEY);
        }
    }

    return "";
}

// ---------------------------------------------------------------------------
// ExtractStem
// "Worlds\m01s01"  ->  "m01s01"
// "M02S01.ltc"     ->  "m02s01"
// ---------------------------------------------------------------------------
std::string CLevelMusicButeMgr::ExtractStem(const char* pszWorldName) const
{
    const char* pStem = pszWorldName;
    for (const char* p = pszWorldName; *p; ++p)
    {
        if (*p == '\\' || *p == '/')
            pStem = p + 1;
    }

    std::string sStem;
    for (int i = 0; pStem[i] && pStem[i] != '.'; ++i)
    {
        char c = pStem[i];
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
        sStem += c;
    }

    return sStem;
}
