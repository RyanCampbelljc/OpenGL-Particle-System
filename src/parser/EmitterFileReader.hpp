#pragma once
#include "PropertyNodeReader.hpp"
#include "XmlFileReader.hpp"
#include "particleSystem/Emitter.hpp"
class EmitterFileReader final : public XmlFileReader
{
	using Base = XmlFileReader;

public:
	explicit EmitterFileReader(std::string path);
	~EmitterFileReader();
	EmitterFileReader(const EmitterFileReader&) = delete;
	void parse() override;
	const std::string& getName() const;
	int getNumParticles() const;
	float getDuration() const;
	EmitterType getType() const;
	int getSpawnRate() const;
	std::unordered_map<std::string, PropertyNodeReader*> getSpawnProperties() const
	{
		return m_spawnProperties;
	}

private:
	std::string m_name;
	int m_numParticles;
	float m_duration;
	EmitterType m_type;
	int m_spawnRate;
	// todo make a map of emitter properties.
	std::unordered_map<std::string, PropertyNodeReader*> m_spawnProperties;
};