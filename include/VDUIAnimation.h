#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "VDSettings.h"
// Session
#include "VDSessionFacade.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace videodromm
{
	// stores the pointer to the VDUIAnimation instance
	typedef std::shared_ptr<class VDUIAnimation> VDUIAnimationRef;
	typedef std::shared_ptr<class VDUIOsc> VDUIOscRef;
#define IM_ARRAYSIZE(_ARR)			((int)(sizeof(_ARR)/sizeof(*_ARR)))
	class VDUIAnimation
	{
	public:
		VDUIAnimation(VDSettingsRef aVDSettings, VDSessionFacadeRef aVDSession);
		static VDUIAnimationRef	create(VDSettingsRef aVDSettings, VDSessionFacadeRef aVDSession)
		{
			return shared_ptr<VDUIAnimation>(new VDUIAnimation(aVDSettings, aVDSession));
		}
		~VDUIAnimation();
		void    Run(const char* title);
	private:
		// Settings
		VDSettingsRef					mVDSettings;
		// Session
		VDSessionFacadeRef				mVDSession;

		// imgui
		float							getFloatValue(unsigned int aCtrl) {
			return mVDSession->getUniformValue(aCtrl);
		};
		void							setFloatValue(unsigned int aCtrl, float aValue) {
			mVDSession->setUniformValue(aCtrl, aValue);
		};
		float							getFloatValueByName(const string& aCtrlName) {
			return 1.0;// TODO mVDSession->getUniformValueByName(aCtrlName);
		}

		int								getIntValue(unsigned int aCtrl) {
			return mVDSession->getUniformValue(aCtrl);
		}

		void							toggleValue(unsigned int aCtrl) {
			mVDSession->toggleValue(aCtrl);
		};
		void							toggleAuto(unsigned int aCtrl) {
			mVDSession->setAnim(aCtrl, mVDSettings->ANIM_TIME); 
		};
		void							toggleTempo(unsigned int aCtrl) {
			mVDSession->setAnim(aCtrl, mVDSettings->ANIM_AUTO);
		};
		void							toggleBass(unsigned int aCtrl) {
			mVDSession->setAnim(aCtrl, mVDSettings->ANIM_BASS);
		};
		void							toggleMid(unsigned int aCtrl) {
			mVDSession->setAnim(aCtrl, mVDSettings->ANIM_MID);
		};
		void							toggleTreble(unsigned int aCtrl) {
			mVDSession->setAnim(aCtrl, mVDSettings->ANIM_TREBLE);
		};
		void							resetAutoAnimation(unsigned int aCtrl) {
			mVDSession->setAnim(aCtrl, mVDSettings->ANIM_NONE);
		};
		bool							getBoolValue(unsigned int aCtrl) {
			return mVDSession->getUniformValue(aCtrl);
		};
		float							getMinUniformValue(unsigned int aIndex) {
			return mVDSession->getMinUniformValue(aIndex);
		};
		float							getMaxUniformValue(unsigned int aIndex) {
			return mVDSession->getMaxUniformValue(aIndex);
		};

		void							setIntValue(unsigned int aCtrl, int aValue) {
			mVDSession->setUniformValue(aCtrl, aValue);
		}

		unsigned int					ctrl;
		map<int, float>					localValues;
		float							f = 0.0f;
		char							buf[64];
		// zoom
		float							minZoom;
		float							maxZoom;
		// tempo
		void							toggleSpinalTap() { spinalTap = !spinalTap; };
		bool							spinalTap = false;

		// render
		float							contour, iVAmount, iVFallOff;
		int								iResolutionX, iResolutionY;
		int								iOutW, iOutH, iBarBeat;
		// contour
		float							minContour;
		float							maxContour;
		// color
		float							color[4];
		float							backcolor[4];
	};
}