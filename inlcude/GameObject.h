#pragma once
#include <Gizmos.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <RakPeerInterface.h>

class GameObject
{
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;
	float radius;
	int ID;
	
	float lifetime;
	glm::vec3 localPosition; // Stored position the client thinks this object is at

	GameObject();

	// Override these functions in your derived GameObject to use your own drawing or update logic
	virtual void draw() { aie::Gizmos::addSphere(localPosition, radius, 32, 32, colour); };
	virtual void update(float deltaTime);

	void Write(RakNet::RakPeerInterface* pPeerInterface, const RakNet::SystemAddress& address, bool broadcast);
	void Read(RakNet::Packet* packet);

	void reconcilePosition(glm::vec3 currentPosition, glm::vec3 goalPosition, float percentage);
	static glm::vec4 GetColour(int id);
};