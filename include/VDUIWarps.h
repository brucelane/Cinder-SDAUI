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

namespace videodromm
{
	// stores the pointer to the VDUIWarps instance
	typedef std::shared_ptr<class VDUIWarps> VDUIWarpsRef;

	class VDUIWarps
	{
	public:
		VDUIWarps(VDSettingsRef aVDSettings, VDSessionRef aVDSession);
		static VDUIWarpsRef	create(VDSettingsRef aVDSettings, VDSessionRef aVDSession)
		{
			return shared_ptr<VDUIWarps>(new VDUIWarps(aVDSettings, aVDSession));
		}
		void    Run(const char* title);
	private:
		// Settings
		VDSettingsRef				mVDSettings;
		// Session
		VDSessionRef				mVDSession;
		// imgui
		char						buf[64];
		int							xPos, yPos;
		bool						mUseMixette = false;
		void setValue(unsigned int aCtrl, float aValue) {
			mVDSession->setUniformValue(aCtrl, aValue);
		}
		int							ctrl;
	};
}