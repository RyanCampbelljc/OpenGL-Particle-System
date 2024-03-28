//-----------------------------------------------------------------------------
// File:			Reciever.cpp
// Original Author:	Ryan Campbell
//-----------------------------------------------------------------------------
#include "Reciever.hpp"

std::vector<Reciever*> Reciever::s_recievers{};

void Reciever::sendSignal(SignalType signal, std::function<bool(Reciever*)> predicate)
{
	for (const auto& reciever : s_recievers) {
		if (predicate == nullptr || predicate(reciever))
			reciever->handleSignal(signal);
	}
}
