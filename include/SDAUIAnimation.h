#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "SDASettings.h"
// Mix
#include "SDAMix.h"
// Session
#include "SDASession.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace VideoDromm
{
	// stores the pointer to the SDAUIAnimation instance
	typedef std::shared_ptr<class SDAUIAnimation> SDAUIAnimationRef;

	class SDAUIAnimation
	{
	public:
		SDAUIAnimation(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIAnimationRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIAnimation>(new SDAUIAnimation(aSDASettings, aSDASession));
		}
		~SDAUIAnimation();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef					mSDASettings;
		// Session
		SDASessionRef					mSDASession;

		// imgui
		float							getValue(unsigned int aCtrl);
		void							setValue(unsigned int aCtrl, float aValue);
		void							toggleValue(unsigned int aCtrl);
		void							toggleAuto(unsigned int aCtrl);
		void							toggleTempo(unsigned int aCtrl);
		void							toggleBass(unsigned int aCtrl);
		void							toggleMid(unsigned int aCtrl);
		void							toggleTreble(unsigned int aCtrl);
		bool							getBoolValue(unsigned int aCtrl);
		void							resetAutoAnimation(unsigned int aCtrl);
		float							getMinUniformValueByIndex(unsigned int aIndex);
		float							getMaxUniformValueByIndex(unsigned int aIndex);

		unsigned int					ctrl;
		map<int, float>					localValues;
		float							f = 0.0f;
		char							buf[64];
		// zoom
		float							minZoom;
		float							maxZoom;
	};
}