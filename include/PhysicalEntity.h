#pragma once

/*!
\file PhysicalEntity.h
\class PhysicalEntity
\brief Basic information about all entities

Contains information about entities physical attibutes, as well as some constants and
collision filters information.
*/

#include <Box2D/Box2D.h>

//! Constant conversion from degrees to radians
#define Deg2Rad 0.017453f
//! Constant conversion from radians to degrees
#define Rad2Deg	57.29577f

class PhysicalEntity
{
protected:
	//! m_body Box2D's pointer to body
	b2Body * m_body = nullptr;
	//! mk_fRestitution Default restitution
	const float mk_fRestitution = 0.6f;
	//! mk_fFriction Default friction
	const float mk_fFriction = 0.4f;
	//! mk_fDensity Default density
	const float mk_fDensity = 0.8f;
public:
	//! \enum CollisionFilter Information about shapes categories - used with collision filtering
	enum CollisionFilter { 
		STATIC_OBJECT = 1, //!< static entity filter
		DYNAMIC_OBJECT = 2, //!< dynamic entity filter
		BALL = 4, //!< ball filter
		SPEED_MODIFIER = 8, //!< speed changer filter
		HOLE = 16, //!< hole filter
	};
	//! Provides access to the body's data
	/*!
	\returns Box2D's body
	*/
	b2Body * getBody() { return m_body; }
	//! Destructor
	~PhysicalEntity() { if (m_body != nullptr) { m_body->GetWorld()->DestroyBody(m_body); } };
};