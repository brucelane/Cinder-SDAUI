#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "VDSettings.h"
// Session
#include "VDSessionFacade.h"
// UIFbos
#include "VDUIFbos.h"
// Animation
#include "VDUIAnimation.h"
// Warps
#include "VDUIWarps.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace videodromm
{
	// stores the pointer to the VDConsole instance
	typedef std::shared_ptr<class VDUI> VDUIRef;

	class VDUI
	{
	public:
		VDUI(VDSettingsRef aVDSettings, VDSessionFacadeRef aVDSessionFacade);
		static VDUIRef	create(VDSettingsRef aVDSettings, VDSessionFacadeRef aVDSessionFacade)
		{
			return shared_ptr<VDUI>(new VDUI(aVDSettings, aVDSessionFacade));
		}

		void    Run(const char* title, unsigned int fps);
		void resize() {
			mIsResizing = true;
			// disconnect ui window and io events callbacks
			ImGui::disconnectWindow(getWindow());
		}
		bool	isReady() { return !mIsResizing; };
	private:
		// Settings
		VDSettingsRef				mVDSettings;
		// Session
		//VDSessionRef				mVDSession;
		VDSessionFacadeRef			mVDSession;
		// UIFbos
		VDUIFbosRef					mUIFbos;
		bool						showUIFbos;
		bool						mShowFbos;
		// UIAnimation
		VDUIAnimationRef			mUIAnimation;
		bool						showUIAnimation;
		
		// UIWarps
		VDUIWarpsRef				mUIWarps;
		bool						showUIWarps;
		bool						mShowWarps;

		// imgui
		char						buf[64];
		bool						mIsResizing;
		float						color[4];
		float						backcolor[4];
		float						multx;
		bool						mouseGlobal;
		int							ctrl;
		float						contour, iVAmount, iVFallOff, iWeight0, iWeight1, iWeight2, iWeight3, iWeight4, iWeight5, iWeight6, iWeight7;

		bool getBoolValue(unsigned int aCtrl) {
			return mVDSession->getUniformValue(aCtrl);
		}
		void toggleValue(unsigned int aCtrl) {
			mVDSession->toggleValue(aCtrl);
		}
		void mToggleShowWarps() {
			mShowWarps = !mShowWarps;
		}
		void mToggleShowFbos() {
			mShowFbos = !mShowFbos;
		}
		void setFloatValue(unsigned int aCtrl, float aValue) {
			mVDSession->setUniformValue(aCtrl, aValue);
		}
		float getMinUniformValue(unsigned int aIndex) {
			return mVDSession->getMinUniformValue(aIndex);
		}
		float getMaxUniformValue(unsigned int aIndex) {
			return mVDSession->getMaxUniformValue(aIndex);
		}
		float							getFloatValue(unsigned int aCtrl) {
			return mVDSession->getUniformValue(aCtrl);
		};
		// mouse
		float						mouseX, mouseY;
		bool						mouseZ;
	};
}