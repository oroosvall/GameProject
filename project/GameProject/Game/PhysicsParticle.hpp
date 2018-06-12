#ifndef PHYSICS_PARTICLE_HPP
#define PHYSICS_PARTICLE_HPP

/// Project Includes

/// External Includes
#include <PhysicsEngine/PhysicsEngine.hpp>
#include <PhysicsEngine/RigidBody.hpp>

/// Std Includes

class PhysicsParticle : public ICollisionResponse {

public:

	PhysicsParticle(PhysicsEngine* pPgysEngine);
	virtual ~PhysicsParticle();

	virtual void response();

	const bool sholdRemove() const { return remove; }

private:

	bool remove;

	RigidBody* rb;
	PhysicsEngine* physEngine;

};

#endif
