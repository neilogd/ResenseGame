/**************************************************************************
*
* File:		GaPawnComponent.cpp
* Author:	Neil Richardson 
* Ver/Date:	
* Description:
*		Pawn component.
*		
*
*
* 
**************************************************************************/

#include "GaPawnComponent.h"

#include "Math/MaBSPTree.h"

#include "System/Os/OsCore.h"

//////////////////////////////////////////////////////////////////////////
// Define resource internals.
DEFINE_RESOURCE( GaPawnComponent );

void GaPawnComponent::StaticRegisterClass()
{
	ReRegisterClass< GaPawnComponent, Super >()
		.addAttribute( new ScnComponentAttribute( 0 ) );
}

//////////////////////////////////////////////////////////////////////////
// initialise
void GaPawnComponent::initialise( const Json::Value& Object )
{
	Super::initialise();
	
	Position_ = MaVec3d( 0.0f, 0.0f, 0.0f );
	MoveDirection_ = MaVec3d( 0.0f, 0.0f, 0.0f );

}

//////////////////////////////////////////////////////////////////////////
// update
//virtual
void GaPawnComponent::update( BcF32 Tick )
{
	MaBSPInfo BSPInfo;
	MaVec3d TargetPosition = Position_;
	BcF32 RotationSpeed = 1.0f * Tick;
	BcF32 MoveSpeed = MoveDirection_.magnitude();
	MaVec3d MoveVector = MoveDirection_.normal();
	MaVec3d SideVector = MaVec3d( 0.0f, 0.0f, 1.0f ).cross( MoveVector );
	BcF32 MoveDirection = 0.0f;
	BcF32 PlayerRadius = 0.25f;
	BcF32 LineCheckRadius = 0.75f;

	// Collide against walls.
	MaVec3d AppliedMoveVector = MoveVector * MoveSpeed * Tick;
	MaVec3d RadiusMoveVector = MoveVector * LineCheckRadius;
	
	// Debug draw:
	if( BSP_->InEditorMode_ )
	{
		MaVec2d Position2D = MaVec2d( Position_.x(), Position_.y() );
		MaVec2d BoxSize2D = MaVec2d( PlayerRadius, PlayerRadius );
		Canvas_->drawLineBox( Position2D - BoxSize2D, Position2D + BoxSize2D, RsColour::GREEN, 10 );
	}

	// If we're moving do the collision checks.
	if( MoveSpeed > 0.0f )
	{
		BcU32 Tries = 3;
		do
		{
			MaVec3d SidePositionA = ( Position_ - SideVector * PlayerRadius );
			MaVec3d SidePositionB = ( Position_ + SideVector * PlayerRadius );
			MaVec3d SidePositionC = ( Position_ + MoveVector * PlayerRadius );
			BcBSPPointInfo BSPPointInfoA;
			BcBSPPointInfo BSPPointInfoB;
			BcBSPPointInfo BSPPointInfoC;
			BcBool PointAIntersection = BSP_->lineIntersection( SidePositionA, SidePositionA + RadiusMoveVector, &BSPPointInfoA );
			BcBool PointBIntersection = BSP_->lineIntersection( SidePositionB, SidePositionB + RadiusMoveVector, &BSPPointInfoB );
			BcBool PointCIntersection = BSP_->lineIntersection( SidePositionC, SidePositionC + RadiusMoveVector, &BSPPointInfoC );

			if( BSP_->InEditorMode_ )
			{
				Canvas_->drawLine( MaVec2d( SidePositionA.x(), SidePositionA.y() ), MaVec2d( BSPPointInfoA.Point_.x(), BSPPointInfoA.Point_.y() ), RsColour::GREEN, 10 );
				Canvas_->drawLine( MaVec2d( SidePositionB.x(), SidePositionB.y() ), MaVec2d( BSPPointInfoB.Point_.x(), BSPPointInfoB.Point_.y() ), RsColour::GREEN, 10 );
				Canvas_->drawLine( MaVec2d( SidePositionC.x(), SidePositionC.y() ), MaVec2d( BSPPointInfoC.Point_.x(), BSPPointInfoC.Point_.y() ), RsColour::GREEN, 10 );
			}
		
			if( PointAIntersection )
			{
				MaVec3d Normal = BSPPointInfoA.Plane_.normal();
				BcF32 MoveAwaySpeed = AppliedMoveVector.dot( Normal );
				AppliedMoveVector -= Normal * MoveAwaySpeed * 1.001f;
			}

			if( PointBIntersection )
			{
				MaVec3d Normal = BSPPointInfoB.Plane_.normal();
				BcF32 MoveAwaySpeed = AppliedMoveVector.dot( Normal );
				AppliedMoveVector -= Normal * MoveAwaySpeed * 1.001f;
			}

			if( PointCIntersection )
			{
				MaVec3d Normal = BSPPointInfoC.Plane_.normal();
				BcF32 MoveAwaySpeed = AppliedMoveVector.dot( Normal );
				AppliedMoveVector -= Normal * MoveAwaySpeed * 1.001f;
			}

			// Move to position.
			TargetPosition = Position_ + AppliedMoveVector;

		}	
		while( !BSP_->checkPointFront( TargetPosition, PlayerRadius, &BSPInfo ) && --Tries != 0 );

		// Place down player, if possible.
		if( BSP_->checkPointFront( TargetPosition, PlayerRadius, &BSPInfo ) )
		{
			Position_ = TargetPosition;

			Pressure_->addSample( Position_, MoveSpeed * Tick * 2.0f );
		}
	}

	// Set position in entity.
	getParentEntity()->setLocalPosition( Position_ );
}

//////////////////////////////////////////////////////////////////////////
// onAttach
//virtual
void GaPawnComponent::onAttach( ScnEntityWeakRef Parent )
{
	// Don't forget to attach!
	Super::onAttach( Parent );
	
	ScnEntityRef WorldEntity = ScnCore::pImpl()->findEntity( "WorldEntity_0" );
	Canvas_ = WorldEntity->getComponentByType< ScnCanvasComponent >( 0 );
	BSP_ = WorldEntity->getComponentByType< GaWorldBSPComponent >( 0 );
	Pressure_ = WorldEntity->getComponentByType< GaWorldPressureComponent >( 0 );

	// Grab position.
	Position_ = Parent->getLocalPosition();
}

//////////////////////////////////////////////////////////////////////////
// onDetach
//virtual
void GaPawnComponent::onDetach( ScnEntityWeakRef Parent )
{
	OsCore::pImpl()->unsubscribeAll( this );

	Canvas_ = NULL;
	BSP_ = NULL;
	Pressure_ = NULL;

	// Don't forget to detach!
	Super::onDetach( Parent );
}

//////////////////////////////////////////////////////////////////////////
// setPosition
void GaPawnComponent::setPosition( const MaVec3d& Position )
{
	Position_ = Position;
}

//////////////////////////////////////////////////////////////////////////
// setMove
void GaPawnComponent::setMove( const MaVec3d& MoveDirection )
{
 	MoveDirection_ = MoveDirection;
}
