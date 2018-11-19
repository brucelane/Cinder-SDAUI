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
	// stores the pointer to the SDAUIRender instance
	typedef std::shared_ptr<class SDAUIRender> SDAUIRenderRef;

	class SDAUIRender
	{
	public:
		SDAUIRender(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIRenderRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIRender>(new SDAUIRender(aSDASettings, aSDASession));
		}
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef					mSDASettings;
		// Session
		SDASessionRef					mSDASession;
		float							getValue(unsigned int aCtrl);
		float							getValueByName(string aCtrlName);
		void							setValue(unsigned int aCtrl, float aValue);
		void							toggleAuto(unsigned int aCtrl);
		void							toggleTempo(unsigned int aCtrl);
		void							toggleSpoutSender();
		bool							getBoolValue(unsigned int aCtrl);
		void							toggleValue(unsigned int aCtrl);
		void							resetAutoAnimation(unsigned int aCtrl);
		float							getMinUniformValueByIndex(unsigned int aIndex);
		float							getMaxUniformValueByIndex(unsigned int aIndex);

		// imgui
		int								ctrl;
		float							contour, iVAmount, iVFallOff, iWeight0, iWeight1, iWeight2, iWeight3, iWeight4;
		int								iResolutionX, iResolutionY;
		// contour
		float							minContour;
		float							maxContour;
		// imgui
		char						buf[64];
		int							xPos, yPos;
	};
}