#include "SignalEmitter.hpp"

void SignalEmitter::registerReciever(Reciever* reciever)
{
	m_recievers.emplace(reciever);
}

void SignalEmitter::emitSignal(SignalType type, Reciever* reciever) const
{
	if (std::find(m_recievers.cbegin(), m_recievers.cend(), reciever) != m_recievers.cend()) {
		reciever->handleSignal(type);
	} else {
		throw std::exception("Reciever not found");
	}
}

// void SignalEmitter::update()
// {
// 	// todo make member
// 	auto pApp = (wolf::App*)(glfwGetWindowUserPointer(glfwGetCurrentContext()));
// 	if (pApp->isKeyJustDown('r')) {
// 		;
// 	}
// }
