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
	// stores the pointer to the SDAUIBlend instance
	typedef std::shared_ptr<class SDAUIBlend> SDAUIBlendRef;

	class SDAUIBlend
	{
	public:
		SDAUIBlend(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIBlendRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIBlend>(new SDAUIBlend(aSDASettings, aSDASession));
		}
		~SDAUIBlend();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		char						buf[64];
		int							xPos, yPos;

	};
}