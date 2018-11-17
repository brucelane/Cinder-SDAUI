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
	// stores the pointer to the SDAUIColor instance
	typedef std::shared_ptr<class SDAUIColor> SDAUIColorRef;

	class SDAUIColor
	{
	public:
		SDAUIColor(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIColorRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIColor>(new SDAUIColor(aSDASettings, aSDASession));
		}
		~SDAUIColor();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef					mSDASettings;
		// Session
		SDASessionRef					mSDASession;
		float							getValue(unsigned int aCtrl);
		void							setValue(unsigned int aCtrl, float aValue);
		void							toggleAuto(unsigned int aCtrl);
		void							toggleTempo(unsigned int aCtrl);
		void							resetAutoAnimation(unsigned int aCtrl);
		float							getMinUniformValueByIndex(unsigned int aIndex);
		float							getMaxUniformValueByIndex(unsigned int aIndex);

		// imgui
		int								ctrl;
		map<int, float>					localValues;
		float							f = 0.0f;
		char							buf[64];
		float							color[4];
		float							backcolor[4];

	};
}