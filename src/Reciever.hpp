#pragma once
#include "Utility.hpp"
/// @brief Class that encapsulates functionality to recieve a singal
enum class SignalType { ResetEffect };
class Reciever
{
public:
	virtual void handleSignal(SignalType signal) = 0;

private:
};