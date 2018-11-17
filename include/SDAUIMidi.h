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

namespace SophiaDigitalArt
{
	// stores the pointer to the SDAUIMidi instance
	typedef std::shared_ptr<class SDAUIMidi> SDAUIMidiRef;

	class SDAUIMidi
	{
	public:
		SDAUIMidi(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIMidiRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIMidi>(new SDAUIMidi(aSDASettings, aSDASession));
		}
		~SDAUIMidi();
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