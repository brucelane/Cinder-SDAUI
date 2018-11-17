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

#define IM_ARRAYSIZE(_ARR)			((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace SophiaDigitalArt
{
	// stores the pointer to the SDAUIWebsockets instance
	typedef std::shared_ptr<class SDAUIWebsockets> SDAUIWebsocketsRef;

	class SDAUIWebsockets
	{
	public:
		SDAUIWebsockets(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIWebsocketsRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIWebsockets>(new SDAUIWebsockets(aSDASettings, aSDASession));
		}
		~SDAUIWebsockets();
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