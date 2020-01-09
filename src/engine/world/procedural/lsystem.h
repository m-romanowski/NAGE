#ifndef NAGE_ENGINE_WORLD_PROCEDURAL_LSYSTEM_H_
#define NAGE_ENGINE_WORLD_PROCEDURAL_LSYSTEM_H_

#include <string>
#include <map>

namespace NAGE
{
    class LSystem
    {
    public:
        LSystem();

        // Getters
        char axiom() const { return mAxiom; }
        std::map<char, std::string> rules() const { return mRules; }
        std::string rule(const char _key) const { return mRules.at(_key); };

        // Setters
        void setAxiom(const char _axiom) { mAxiom = _axiom; }
        void setRules(const std::map<char, std::string> _rules) { mRules = _rules; };
        void addRule(const char _key, const std::string _value) { mRules.insert(std::make_pair(_key, _value)); };

        // Plant Settings
        struct SETTINGS
        {
            unsigned int iterations = 3; // Generate iterations.
            float angle = 5.0f; // Angle between branches.
            float width = 0.1f; // Branches / Leafs width.
            float minLeafLength = 0.2f; // Minimum leaf length.
            float maxLeafLength = 0.5f; // Maximum leaf length.
            float minBranchLength = 1.0f; // Minimum branch length.
            float maxBranchLength = 2.0f; // Maximum branch length.
        };

    private:
        char mAxiom;
        std::map<char, std::string> mRules;
    };
}

#endif // NAGE_ENGINE_WORLD_PROCEDURAL_LSYSTEM_H_
