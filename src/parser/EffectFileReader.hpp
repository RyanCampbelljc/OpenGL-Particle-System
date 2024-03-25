#pragma once
#include "XmlFileReader.hpp"
/// @brief Class to read Effect xml files.
class EffectFileReader final : public XmlFileReader
{
	using Base = XmlFileReader;

public:
	struct EmitterTag {
		EmitterTag(const std::string& file, const glm::vec3& offset)
			: file(file)
			, offset(offset)
		{
		}
		// cannot be references as they are deleted while being parsed
		const std::string file;
		const glm::vec3 offset;
	};
	// todo what this do
	explicit EffectFileReader(std::string path);
	EffectFileReader(const EffectFileReader&) = delete;

	void parse() override;
	const std::string& getName() const;
	const std::vector<EmitterTag>& getEmitterTags() const;

private:
	std::string m_name;
	std::vector<EmitterTag> m_emitters;
};