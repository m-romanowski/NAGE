#ifndef NAGE_ENGINE_WORLD_PROCEDURAL_LSYSTEM_H_
#define NAGE_ENGINE_WORLD_PROCEDURAL_LSYSTEM_H_

#include <string>
#include <map>

namespace mr::nage
{
    class LSystem
    {
    public:
        LSystem();

        // Getters
        char axiom() const { return axiom_; }
        std::map<char, std::string> rules() const { return rules_; }
        std::string rule(const char _key) const { return rules_.at(_key); };

        // Setters
        void setAxiom(const char _axiom) { axiom_ = _axiom; }
        void setRules(const std::map<char, std::string> _rules) { rules_ = _rules; };
        void addRule(const char _key, const std::string _value) { rules_.insert(std::make_pair(_key, _value)); };

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
        char axiom_;
        std::map<char, std::string> rules_;
    };
}

#endif // NAGE_ENGINE_WORLD_PROCEDURAL_LSYSTEM_H_
