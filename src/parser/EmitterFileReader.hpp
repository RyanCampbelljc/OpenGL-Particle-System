#include "XmlFileReader.hpp"
#include "particleSystem/Emitter.hpp"
class EmitterFileReader final : public XmlFileReader
{
	using Base = XmlFileReader;

public:
	explicit EmitterFileReader(std::string path);
	EmitterFileReader(const EmitterFileReader&) = delete;
	void parse() override;
	const std::string& getName() const;
	int getNumParticles() const;
	float getDuration() const;
	Emitter::EmitterType getType() const;
	int getSpawnRate() const;

private:
	std::string m_name;
	int m_numParticles;
	float m_duration;
	Emitter::EmitterType m_type;
	int m_spawnRate;
};