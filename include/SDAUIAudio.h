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
	// stores the pointer to the SDAUIAudio instance
	typedef std::shared_ptr<class SDAUIAudio> SDAUIAudioRef;

	class SDAUIAudio
	{
	public:
		SDAUIAudio(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIAudioRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIAudio>(new SDAUIAudio(aSDASettings, aSDASession));
		}
		~SDAUIAudio();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		float						f = 0.0f;
		char						buf[64];
		float						multx;
	};
}