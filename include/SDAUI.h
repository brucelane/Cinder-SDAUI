#pragma once

#include "cinder/app/App.h"

// UserInterface
#include "CinderImGui.h"
// Settings
#include "SDASettings.h"
// Session
#include "SDASession.h"

// UITextures
#include "SDAUITextures.h"
// UIFbos
#include "SDAUIFbos.h"
// Animation
#include "SDAUIAnimation.h"
// Midi
#include "SDAUIMidi.h"
// Audio
#include "SDAUIAudio.h"
// Color
#include "SDAUIColor.h"
// Tempo
#include "SDAUITempo.h"
// Blend
#include "SDAUIBlend.h"
// Websockets
#include "SDAUIWebsockets.h"
// Osc
#include "SDAUIOsc.h"
// Mouse
#include "SDAUIMouse.h"
// Shaders
#include "SDAUIShaders.h"
// Render
#include "SDAUIRender.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace SophiaDigitalArt
{
	// stores the pointer to the SDAConsole instance
	typedef std::shared_ptr<class SDAUI> SDAUIRef;

	class SDAUI
	{
	public:
		SDAUI(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUI>(new SDAUI(aSDASettings, aSDASession));
		}

		void    Run(const char* title, unsigned int fps);
		void	resize();
		bool	isReady() { return !mIsResizing; };
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;

		// UITextures
		SDAUITexturesRef			mUITextures;
		bool						showUITextures;
		// UIFbos
		SDAUIFbosRef				mUIFbos;
		bool						showUIFbos;
		// UIAnimation
		SDAUIAnimationRef			mUIAnimation;
		bool						showUIAnimation;
		// UIMidi
		SDAUIMidiRef				mUIMidi;
		bool						showUIMidi;
		// UIAudio
		SDAUIAudioRef				mUIAudio;
		bool						showUIAudio;
		// UIColor
		SDAUIColorRef				mUIColor;
		bool						showUIColor;
		// UITempo
		SDAUITempoRef				mUITempo;
		bool						showUITempo;
		// UIBlend
		SDAUIBlendRef				mUIBlend;
		bool						showUIBlend;
		// UIMouse
		SDAUIMouseRef				mUIMouse;
		bool						showUIMouse;
		// UIOsc
		SDAUIOscRef					mUIOsc;
		bool						showUIOsc;
		// UIWebsockets
		SDAUIWebsocketsRef			mUIWebsockets;
		bool						showUIWebsockets;
		// UIShaders
		SDAUIShadersRef				mUIShaders;
		bool						showUIShaders;
		// UIRender
		SDAUIRenderRef				mUIRender;
		bool						showUIRender;
		
		float						getMinUniformValueByIndex(unsigned int aIndex);
		float						getMaxUniformValueByIndex(unsigned int aIndex);
		// imgui
		char						buf[64];
		bool						mIsResizing;
		float						color[4];
		float						backcolor[4];
		float						multx;
		bool						mouseGlobal;
		int							ctrl;
		float						contour, iVAmount, iVFallOff, iWeight0, iWeight1, iWeight2, iWeight3, iWeight4;
		void						setValue(unsigned int aCtrl, float aValue);
	};
}