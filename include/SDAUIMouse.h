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
	// stores the pointer to the SDAUIMouse instance
	typedef std::shared_ptr<class SDAUIMouse> SDAUIMouseRef;

	class SDAUIMouse
	{
	public:
		SDAUIMouse(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIMouseRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIMouse>(new SDAUIMouse(aSDASettings, aSDASession));
		}
		~SDAUIMouse();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		float						getValue(unsigned int aCtrl);
		void						setValue(unsigned int aCtrl, float aValue);

		// imgui
		float						f = 0.0f;
		char						buf[64];
		bool						mouseGlobal;
		int							ctrl;
		float						mouseX, mouseY;
		bool						mouseZ;
	};
}