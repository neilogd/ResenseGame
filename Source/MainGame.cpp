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
		MaMat4d(),
		NULL
	};
	ScnCore::pImpl()->spawnEntity( Params );
}

//////////////////////////////////////////////////////////////////////////
// PsyGameRegisterResources
void PsyGameRegisterResources()
{
	GaWorldInfoComponent::StaticRegisterClass();
	GaWorldBSPComponent::StaticRegisterClass();
	GaWorldPressureComponent::StaticRegisterClass();
	GaEnemyComponent::StaticRegisterClass();
	GaPlayerComponent::StaticRegisterClass();
	GaPlayerSoundComponent::StaticRegisterClass();
	GaPawnComponent::StaticRegisterClass();
}
