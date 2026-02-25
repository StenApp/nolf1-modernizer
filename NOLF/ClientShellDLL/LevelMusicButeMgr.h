// ----------------------------------------------------------------------- //
//
// MODULE  : LevelMusicButeMgr.h
//
// PURPOSE : Maps level names to PS2 WAV music files
//
// ----------------------------------------------------------------------- //

#ifndef __LEVEL_MUSIC_BUTE_MGR_H__
#define __LEVEL_MUSIC_BUTE_MGR_H__

#pragma once

// Returns the PS2 WAV path for a given world name (e.g. "m01s01").
// Returns NULL if no mapping exists or the level has no PS2 music.
// The returned path is relative to the game root, e.g. "Music\PS2\nolf_ps2_01.wav"
const char* GetPS2MusicForLevel(const char* pszWorldName);

#endif // __LEVEL_MUSIC_BUTE_MGR_H__
