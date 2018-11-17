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
	// stores the pointer to the SDAUIOsc instance
	typedef std::shared_ptr<class SDAUIOsc> SDAUIOscRef;
#define IM_ARRAYSIZE(_ARR)			((int)(sizeof(_ARR)/sizeof(*_ARR)))

	class SDAUIOsc
	{
	public:
		SDAUIOsc(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIOscRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIOsc>(new SDAUIOsc(aSDASettings, aSDASession));
		}
		~SDAUIOsc();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		//float						f = 0.0f;
		char						buf[64];
	};
}