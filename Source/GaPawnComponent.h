/**************************************************************************
*
* File:		GaPawnComponent.h
* Author:	Neil Richardson 
* Ver/Date:	
* Description:
*		Pawn component.
*		
*
*
* 
**************************************************************************/

#ifndef __GaPawnComponent_H__
#define __GaPawnComponent_H__

#include "Psybrus.h"
#include "System/Scene/ScnCanvasComponent.h"

#include "GaWorldBSPComponent.h"
#include "GaWorldPressureComponent.h"

//////////////////////////////////////////////////////////////////////////
// GaExampleComponentRef
typedef ReObjectRef< class GaPawnComponent > GaPawnComponentRef;

//////////////////////////////////////////////////////////////////////////
// GaPawnComponent
class GaPawnComponent:
	public ScnComponent
{
public:
	DECLARE_RESOURCE( ScnComponent, GaPawnComponent );

	void								initialise( const Json::Value& Object );

	virtual void						update( BcF32 Tick );
	virtual void						onAttach( ScnEntityWeakRef Parent );
	virtual void						onDetach( ScnEntityWeakRef Parent );

	void								setPosition( const MaVec3d& Position );
	void								setMove( const MaVec3d& MoveDirection );

private:
	MaVec3d								Position_;
	MaVec3d								MoveDirection_;
	
	ScnCanvasComponentRef				Canvas_;
	GaWorldBSPComponentRef				BSP_;
	GaWorldPressureComponentRef			Pressure_;
};

#endif

