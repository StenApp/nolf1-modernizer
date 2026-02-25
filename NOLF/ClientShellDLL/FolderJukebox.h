#pragma once
#include "BaseFolder.h"

class CFolderJukebox : public CBaseFolder
{
public:
	CFolderJukebox();
	virtual ~CFolderJukebox();

	// Build the folder
	LTBOOL   Build();
	uint32 OnCommand(uint32 dwCommand, uint32 dwParam1, uint32 dwParam2);
	void    OnFocus(LTBOOL bFocus);
	virtual void	UpdateHelpText();

protected:

	LTBOOL PlayScore(int scoreId);

	CMusicState m_PreviousMusicState;

	CListCtrl* m_SongListCtrl;

	std::string m_sCurrentSong;
	std::map<std::string, int>* m_CurrentSongList;

	std::vector<int> m_ThemeIDsToSkip;

	std::vector< std::map<std::string, int> > m_Songs;

	// WAV playback support
	HLTSOUND	m_hCurrentWAV;			// Handle to currently playing WAV
	bool		m_bCurrentThemeIsWAV;	// Is the active theme WAV-based?
	std::string	m_sCurrentWAVDirectory;	// Directory of current WAV theme

	void		StopCurrentWAV();		// Stop WAV and release handle

private:

};

