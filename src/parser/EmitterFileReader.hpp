//-----------------------------------------------------------------------------
// File:			EmitterFileReader.hpp
// Original Author:	Ryan Campbell
/// @brief Class to read Emitter xml files
//-----------------------------------------------------------------------------
#pragma once
#include "PropertyNodeWrapper.hpp"
#include "XmlFileReader.hpp"
#include "affectors/BaseAffector.hpp"
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
	std::unordered_map<std::string, std::shared_ptr<PropertyNodeWrapper>> getSpawnProperties() const;
	std::vector<std::shared_ptr<BaseAffector>> getAffectors() const;
	const std::string& getTexturePath() const;
	std::vector<std::string> getBlendModes() const;

private:
	//-----------------------------------------------------------------------------
	// members to hold necessary information to create an emitter
	//-----------------------------------------------------------------------------
	std::string m_name;
	int m_numParticles;
	float m_duration;
	EmitterType m_type;
	int m_spawnRate;
	std::string m_textureFilePath;
	std::unordered_map<std::string, std::shared_ptr<PropertyNodeWrapper>> m_spawnProperties;
	std::vector<std::shared_ptr<BaseAffector>> m_affectors;
	std::vector<std::string> m_blendModes;
};