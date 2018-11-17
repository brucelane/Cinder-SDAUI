#pragma once

#include "cinder/app/App.h"

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
	// stores the pointer to the SDAUIFbos instance
	typedef std::shared_ptr<class SDAUIFbos> SDAUIFbosRef;

	class SDAUIFbos
	{
	public:
		SDAUIFbos(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIFbosRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIFbos>(new SDAUIFbos(aSDASettings, aSDASession));
		}
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		char						buf[64];
		int							xPos, yPos;
		int							xStep = 1;
		int							yStep = 1;
		// sequence
		int							playheadPositions[12];
		float						speeds[12];
	};
}