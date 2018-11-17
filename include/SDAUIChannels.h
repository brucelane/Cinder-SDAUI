#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Session
#include "SDASession.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace VideoDromm
{
	// stores the pointer to the SDAUIChannels instance
	typedef std::shared_ptr<class SDAUIChannels> SDAUIChannelsRef;

	class SDAUIChannels
	{
	public:
		SDAUIChannels(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIChannelsRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIChannels>(new SDAUIChannels(aSDASettings, aSDASession));
		}
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