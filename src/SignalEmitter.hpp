#pragma once
#include "Reciever.hpp"
#include "Utility.hpp"
#include <unordered_set>
/// @brief Singleton that you send signal requests to and
// it passes them off to the proper signal reciver
class SignalEmitter
{
public:
	static SignalEmitter& Instance()
	{
		static SignalEmitter instance;
		return instance;
	}
	// todo should these be const references
	void registerReciever(Reciever* reciever);
	void emitSignal(SignalType type, Reciever* reciever) const;
	// void update();

private:
	SignalEmitter()
	{
	}

	std::unordered_set<Reciever*> m_recievers;
};