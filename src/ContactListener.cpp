#include "ContactListener.h"
#include "Game.h"

#include <iostream>

ContactListener::ContactListener()
{
	//bind sounds with buffers
	starSound.setBuffer(*m_soundManager->getSound("star"));
	score.setBuffer(*m_soundManager->getSound("victory"));
	obHit.setBuffer(*m_soundManager->getSound("obHit"));
	boost.setBuffer(*m_soundManager->getSound("boost"));
	button.setBuffer(*m_soundManager->getSound("button"));
}

//Called when two fixtures begin to touch
void ContactListener::BeginContact(b2Contact * contact)
{
	bodyA = contact->GetFixtureA()->GetBody();
	bodyB = contact->GetFixtureB()->GetBody();

	pairA = *(std::pair<std::string, void*>*) bodyA->GetUserData();
	pairB = *(std::pair<std::string, void*>*) bodyB->GetUserData();

	/////////////////////////////////////
	///				BALL			  ///
	/////////////////////////////////////
	if (pairB.first == typeid(Ball).name())
	{
		ballCollided = true;
		b = static_cast<Ball*>(pairB.second);

		if (pairA.first == typeid(Booster).name())
		{
			Booster *booster = static_cast<Booster*>(pairA.second);
			if (b != nullptr)
			{
				boost.play();
				b->Boost(booster->GetSpeedModifier());
			}
		}

		if (pairA.first == typeid(SpeedChanger).name())
		{

			SpeedChanger *sp = static_cast<SpeedChanger*>(pairA.second);
			if (b != nullptr)
			{
				b->SetLinearDamping(sp->getLinDamp());
				b->SetAngularDamping(sp->getAngDamp());
			}
		}

		if (pairA.first == typeid(Ramp).name())
		{
			r = static_cast<Ramp*>(pairA.second);
			if (b != nullptr)
			{
				b->isOnRamp = true;
			}
		}

		if (pairA.first == typeid(Hole).name())
		{
			Hole *h = static_cast<Hole*>(pairA.second);
			if (b != nullptr)
			{
				if (b->getLinearVelocity().x < 0.5f && b->getLinearVelocity().y < 0.5f)
				{
					Game* g = g->getInstance();
					score.play();
					b->scored = true;
					g->LoadNextLevel();
				}
			}
		}

		if (pairA.first == typeid(DoorOpener).name())
		{
			DoorOpener *dO = static_cast<DoorOpener*>(pairA.second);
			if (b != nullptr)
			{
				button.play();
				dO->openDoor(dO->getID());
				dO->changeTexture(m_texManager->getTexture("buttonOn"));
			}
		}

		if (pairA.first == typeid(Star).name())
		{
			Star *s = static_cast<Star*>(pairA.second);
			if (b != nullptr)
			{
				starSound.play();
				m_ui->addStar();
				s->DeleteStar();
			}
		}

		if (pairA.first == typeid(DynamicBlock).name() || pairA.first == typeid(DynamicCircle).name() || pairA.first == typeid(Door).name())
		{
			if (b != nullptr)
			{
				obHit.play();
			}
		}

		if (pairA.first == typeid(StaticBlock).name() || pairA.first == typeid(StaticCircle).name() || pairA.first == typeid(StaticPolygon).name() || pairA.first == typeid(SlidingDoor).name() || pairA.first == typeid(RotatingBlock).name())
		{
			if (b != nullptr)
			{
				obHit.play();
			}
		}
	}

	/////////////////////////////////////
	///				Block			  ///
	/////////////////////////////////////
	if (pairB.first == typeid(DynamicBlock).name())
	{
		block = static_cast<DynamicBlock*>(pairB.second);

		if (pairA.first == typeid(Booster).name())
		{
			Booster *booster = static_cast<Booster*>(pairA.second);
			if (block != nullptr)
			{
				boost.play();
				block->Boost(booster->GetSpeedModifier());
			}
		}

		if (pairA.first == typeid(SpeedChanger).name())
		{
			SpeedChanger *sp = static_cast<SpeedChanger*>(pairA.second);
			if (block != nullptr)
			{
				block->SetLinearDamping(sp->getLinDamp());
				block->SetAngularDamping(sp->getAngDamp());
			}
		}

		if (pairA.first == typeid(Ramp).name())
		{
			r = static_cast<Ramp*>(pairA.second);
			if (block != nullptr)
			{
				block->blockOnRamp = true;
			}
		}

		if (pairA.first == typeid(StaticBlock).name() || pairA.first == typeid(StaticCircle).name() || pairA.first == typeid(StaticPolygon).name() || pairA.first == typeid(SlidingDoor).name() || pairA.first == typeid(RotatingBlock).name())
		{
			if (block != nullptr)
			{
				obHit.play();
			}
		}
	}

	/////////////////////////////////////
	///				Circle			  ///
	/////////////////////////////////////
	if (pairB.first == typeid(DynamicCircle).name())
	{
		circle = static_cast<DynamicCircle*>(pairB.second);

		if (pairA.first == typeid(Booster).name())
		{
			Booster *booster = static_cast<Booster*>(pairA.second);
			if (circle != nullptr)
			{
				boost.play();
				circle->Boost(booster->GetSpeedModifier());
			}
		}

		if (pairA.first == typeid(SpeedChanger).name())
		{
			SpeedChanger *sp = static_cast<SpeedChanger*>(pairA.second);
			if (circle != nullptr)
			{
				circle->SetLinearDamping(sp->getLinDamp());
				circle->SetAngularDamping(sp->getAngDamp());
			}
		}

		if (pairA.first == typeid(Ramp).name())
		{
			r = static_cast<Ramp*>(pairA.second);
			if (circle != nullptr)
			{
				circle->circleOnRamp = true;
			}
		}

		if (pairA.first == typeid(StaticBlock).name() || pairA.first == typeid(StaticCircle).name() || pairA.first == typeid(StaticPolygon).name() || pairA.first == typeid(SlidingDoor).name() || pairA.first == typeid(RotatingBlock).name())
		{
			if (circle != nullptr)
			{
				obHit.play();
			}
		}
	}
}

//Called when two fixtures finish touching
void ContactListener::EndContact(b2Contact * contact)
{
	if (ballCollided == true)
	{
		b->SetLinearDamping(b->getOriginalLinDamp());
		b->SetAngularDamping(b->getOriginalAngDamp());

		b->isOnRamp = false;
		ballCollided = false;

	}
	
	if (blockCollided == true)
	{
		block->SetLinearDamping(block->getOriginalLinDamp());
		block->SetAngularDamping(block->getOriginalAngDamp());

		block->blockOnRamp = false;
		blockCollided = false;
	}

	if (circleCollided == true)
	{
		circle->SetLinearDamping(circle->getOriginalLinDamp());
		circle->SetAngularDamping(circle->getOriginalLinDamp());

		circle->circleOnRamp = false;
		circleCollided = false;
	}

	bodyA = nullptr;
	bodyB = nullptr;
	
}

//Before change of momentum
void ContactListener::PreSolve(b2Contact * contact, const b2Manifold * oldMf)
{
}

//After change of momentum
void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
}

void ContactListener::setUI(UserInterface * ui)
{
	m_ui = ui;
}

ContactListener::~ContactListener()
{
	//clean the memory
	delete pairA.second;
	delete pairB.second;

	bodyA = nullptr;
	bodyB = nullptr;

	b = nullptr;
	circle = nullptr;
	block = nullptr;
	m_ui = nullptr;
	r = nullptr;
}


