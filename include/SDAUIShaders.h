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
#define IM_ARRAYSIZE(_ARR)			((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace SophiaDigitalArt
{
	// stores the pointer to the SDAUIShaders instance
	typedef std::shared_ptr<class SDAUIShaders> SDAUIShadersRef;

	class SDAUIShaders
	{
	public:
		SDAUIShaders(SDASettingsRef aSDASettings, SDASessionRef aSDASession);
		static SDAUIShadersRef	create(SDASettingsRef aSDASettings, SDASessionRef aSDASession)
		{
			return shared_ptr<SDAUIShaders>(new SDAUIShaders(aSDASettings, aSDASession));
		}
		~SDAUIShaders();
		void    Run(const char* title);
	private:
		// Settings
		SDASettingsRef				mSDASettings;
		// Session
		SDASessionRef				mSDASession;
		// imgui
		char						buf[64];
		//! default fragment shader
		std::string					mFboTextureFragmentShaderString;
		string						mError;
		gl::GlslProgRef				aShader;
		std::string					mPassthruVextexShaderString;
		int							xPos, yPos;
	};
}