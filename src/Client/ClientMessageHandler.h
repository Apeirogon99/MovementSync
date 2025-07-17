#pragma once
#include "Common/Protocol/Message.h"
#include "Common/Protocol/Protocol.h"
#include "World.h"

void Handle_INVALID(uint16_t Id, uint16_t Size, const std::vector<BYTE>& Data);
//void Handle_S2C_SPAWN(const std::unique_ptr<World>& World, const S2C_SPAWN* Protocol);
//void Handle_S2C_DESPAWN(const std::unique_ptr<World>& World, const S2C_DESPAWN* Protocol);
void Handle_S2C_MOVE(const std::unique_ptr<World>& World, const S2C_MOVE* Protocol);
void Handle_S2C_TOGGLE_WALKABLE(const std::unique_ptr<World>& World, const S2C_TOGGLE_WALKABLE* Protocol);

class ClientMessageHandler
{
public:
	static void ProcessMessage(const std::unique_ptr<World>& World, std::unique_ptr<Message>& Message)
	{
		uint16_t id = Message->GetId();
		uint16_t size = Message->GetSize();
		std::vector<BYTE> data = Message->GetData();

		switch (static_cast<EMessageId>(id))
		{
		case EMessageId::PKT_S2C_SPAWN:
			//Handle_S2C_SPAWN(World, MessageSerializer::Deserialize<S2C_SPAWN>(data, size));
			break;
		case EMessageId::PKT_S2C_DESPAWN:
			//Handle_S2C_DESPAWN(World, MessageSerializer::Deserialize<S2C_DESPAWN>(data, size));
			break;
		case EMessageId::PKT_S2C_MOVE:
			Handle_S2C_MOVE(World, MessageSerializer::Deserialize<S2C_MOVE>(data, size));
			break;
		case EMessageId::PKT_S2C_TOGGLE_WALKABLE:
			Handle_S2C_TOGGLE_WALKABLE(World, MessageSerializer::Deserialize<S2C_TOGGLE_WALKABLE>(data, size));
			break;
		default:
			Handle_INVALID(id, size, data);
			break;
		}
	}
};

