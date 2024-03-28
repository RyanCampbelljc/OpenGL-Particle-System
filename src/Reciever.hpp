#pragma once
#include "Utility.hpp"
#include <functional>
/// @brief Class that encapsulates functionality to recieve a singal
enum class SignalType { ResetEffect };
class Reciever
{
public:
	Reciever()
	{
		s_recievers.push_back(this);
	}
	// default null if you want to send a singal to all the recivers
	static void sendSignal(SignalType signal, std::function<bool(Reciever*)> predicate = nullptr);

private:
	virtual void handleSignal(SignalType signal) = 0;
	static std::vector<Reciever*> s_recievers;
};