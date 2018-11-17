#pragma once

#include "cinder/app/App.h"
#include "cinder/Rand.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "SDASettings.h"
// Session
#include "SDASession.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace VideoDromm
{
	// stores the pointer to the SDAConsole instance
	typedef std::shared_ptr<class SDAUITextures> SDAUITexturesRef;

	class SDAUITextures
	{
	public:
		SDAUITextures(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUITexturesRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUITextures>(new SDAUITextures(aSDASettings, aSDASession));
		}
		~SDAUITextures();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		char						buf[64];
		int							xStep = 1;
		int							yStep = 1;
		// sequence
		int							playheadPositions[12];
		float						speeds[12];
	};
}