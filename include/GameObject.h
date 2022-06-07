#pragma once
#include <Gizmos.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <RakPeerInterface.h>

/// <summary>
/// GameObject is a class used to represent the physical objects in the game scene of
/// all clients. The class contains, by default, position, velocity, colour, radius and
/// client ID, all of which it is configured to read in from the server and write out to
/// the server when requested by either this client or the server. The class is setup to be
/// easily derivable, containing virtual draw and update function that can be overriden
/// with your own drawing and updating logic for whatever GameObject you wish to make, as
/// well as virtual read and write functions that can be overriden if the derived GameObject
/// you wish to make needs to transmit more data than what it does by default (e.g. health
/// or attack).
/// </summary>
class GameObject
{
public:
	// Transmitted data
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;
	float radius;
	int ID;
	
	// Local data
	float lifetime;
	glm::vec3 localPosition; // Local position the client thinks this object is at

	GameObject();
	~GameObject() { }
	static glm::vec4 GetColour(int id);

	// Override these functions in your derived GameObject to use your own drawing, updating, or lerping logic
	virtual void draw() { aie::Gizmos::addSphere(localPosition, radius, 8, 8, colour); }; // Draw the game object as a sphere using bootstrap by default
	virtual void update(float deltaTime);
	virtual void reconcilePosition(float percentage);

	// Network functions, override if you wish to add extra data to your GameObjects 
	virtual void Write(RakNet::RakPeerInterface* pPeerInterface, const RakNet::SystemAddress& address, bool broadcast);
	virtual void Read(RakNet::Packet* packet);
};