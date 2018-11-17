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
	// stores the pointer to the SDAUITempo instance
	typedef std::shared_ptr<class SDAUITempo> SDAUITempoRef;

	class SDAUITempo
	{
	public:
		SDAUITempo(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUITempoRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUITempo>(new SDAUITempo(aSDASettings, aSDASession));
		}
		~SDAUITempo();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		float						f = 0.0f;
		char						buf[64];
	};
}