/**************************************************************************
*
* File:		MainGame.cpp
* Author: 	Neil Richardson 
* Ver/Date:	
* Description:
*		Main Game Entrypoint.
*		
*
*
* 
**************************************************************************/

#include "Psybrus.h"

#include "System/Content/CsCore.h"

#include "GaEnemyComponent.h"
#include "GaPawnComponent.h"
#include "GaPlayerComponent.h"
#include "GaPlayerSoundComponent.h"
#include "GaWorldInfoComponent.h"
#include "GaWorldBSPComponent.h"
#include "GaWorldPressureComponent.h"


//////////////////////////////////////////////////////////////////////////
// GPsySetupParams
PsySetupParams GPsySetupParams( "Resense", psySF_GAME_DEV, 1.0f / 60.0f );	

//////////////////////////////////////////////////////////////////////////
// PsyGameInit
void PsyGameInit()
{

}

//////////////////////////////////////////////////////////////////////////
// PsyLaunchGame
void PsyLaunchGame()
{
	// Spawn the editor entity.
	ScnEntitySpawnParams Params = 
	{
		"default", "EditorEntity", "WorldEntity_0",
		BcMat4d(),
		NULL
	};
	ScnCore::pImpl()->spawnEntity( Params );
}

//////////////////////////////////////////////////////////////////////////
// PsyGameRegisterResources
void PsyGameRegisterResources()
{
	CsCore::pImpl()->registerResource< GaWorldInfoComponent >();
	CsCore::pImpl()->registerResource< GaWorldBSPComponent >();
	CsCore::pImpl()->registerResource< GaWorldPressureComponent >();
	CsCore::pImpl()->registerResource< GaEnemyComponent >();
	CsCore::pImpl()->registerResource< GaPlayerComponent >();
	CsCore::pImpl()->registerResource< GaPlayerSoundComponent >();
	CsCore::pImpl()->registerResource< GaPawnComponent >();
}

//////////////////////////////////////////////////////////////////////////
// PsyGameUnRegisterResources
void PsyGameUnRegisterResources()
{
	CsCore::pImpl()->unregisterResource< GaWorldInfoComponent >();
	CsCore::pImpl()->unregisterResource< GaWorldBSPComponent >();
	CsCore::pImpl()->unregisterResource< GaWorldPressureComponent >();
	CsCore::pImpl()->unregisterResource< GaEnemyComponent >();
	CsCore::pImpl()->unregisterResource< GaPlayerComponent >();
	CsCore::pImpl()->unregisterResource< GaPlayerSoundComponent >();
	CsCore::pImpl()->unregisterResource< GaPawnComponent >();
}
