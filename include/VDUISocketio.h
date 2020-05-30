#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "VDSettings.h"
// Session
#include "VDSession.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define IM_ARRAYSIZE(_ARR)			((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace videodromm
{
	// stores the pointer to the VDUISocketio instance
	typedef std::shared_ptr<class VDUISocketio> VDUISocketioRef;

	class VDUISocketio
	{
	public:
		VDUISocketio(VDSettingsRef aVDSettings, VDSessionRef aVDSession);
		static VDUISocketioRef	create(VDSettingsRef aVDSettings, VDSessionRef aVDSession)
		{
			return shared_ptr<VDUISocketio>(new VDUISocketio(aVDSettings, aVDSession));
		}
		~VDUISocketio();
		void    Run(const char* title);
	private:
		// Settings
		VDSettingsRef				mVDSettings;
		// Session
		VDSessionRef				mVDSession;
		// imgui
		float						f = 0.0f;
		char						buf[64];
	};
}