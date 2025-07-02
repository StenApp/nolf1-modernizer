// ----------------------------------------------------------------------- //
//
// MODULE  : VersionMgr.h
//
// PURPOSE : Definition of versioning manager
//
// CREATED : 11/16/2000
//
// (c) 2000 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //

#include "stdafx.h"
#include "VersionMgr.h"

#include "regmgr.h"

#ifdef _DEMO
static const char* s_szVersion		= "";
static const char* s_szBuild		= "Demo Build 7";
#else
static const char* s_szVersion		= "v1.006 Modern";
static const char* s_szBuild		= "Modern";
#endif 
static const uint32 s_nSaveVersion  = 4;

static const float s_fLatestPatch = 3.2f;


CVersionMgr* g_pVersionMgr = NULL;

// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CVersionMgr::CVersionMgr()
//
//	PURPOSE:	Constructor
//
// ----------------------------------------------------------------------- //

CVersionMgr::CVersionMgr()
{
	g_pVersionMgr = this;

	// Determine what language version the game is using...

	m_szLanguage[0]	= '\0';
	m_bLowViolence	= false;
	m_bIsGOTY		= false;

	// Get the language registry key...
	CRegMgr	regMgr;

	if (regMgr.Init("Monolith Productions", "No One Lives Forever", "1.0"))
	{
		unsigned int nBufSize = sizeof(m_szLanguage);
		regMgr.Get("Language", m_szLanguage, nBufSize, "English");

		/*if (m_szLanguage[0])
		{
			if (_stricmp(m_szLanguage, "German") == 0)
			{
				m_bLowViolence = true; //German version is uncut by commenting these lines
			}
		}*/
	}

	// Check to see if we've got the GOTY file!
	std::ifstream gotyFile("NolfGOTY.rez");
	if (gotyFile.good()) 
	{
		m_bIsGOTY = true;
	}
	gotyFile.close();
}

// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CVersionMgr::GetVersion()
//
//	PURPOSE:	Get the current version string
//
// ----------------------------------------------------------------------- //

const char* CVersionMgr::GetVersion()
{
	return s_szVersion;
}

// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CVersionMgr::GetSaveVersion()
//
//	PURPOSE:	Get the current save version 
//
// ----------------------------------------------------------------------- //

const uint32 CVersionMgr::GetSaveVersion()
{
	return s_nSaveVersion;
}

const float CVersionMgr::GetLatestPatchVersion()
{
	return s_fLatestPatch;
}

// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CVersionMgr::GetBuild()
//
//	PURPOSE:	Get the current build string
//
// ----------------------------------------------------------------------- //

const char* CVersionMgr::GetBuild()
{
	return s_szBuild;
}