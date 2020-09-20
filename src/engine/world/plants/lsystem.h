#ifndef NAGE_ENGINE_WORLD_PLANTS_LSYSTEM_H_
#define NAGE_ENGINE_WORLD_PLANTS_LSYSTEM_H_

#include "engine/render/model/model.h"
#include <stack>

#define RANDOM_ROTATIONS_COUNT 1000

namespace NAGE
{
    class LSystem
    {
        struct Tree
        {

        };

        struct TreeTransform
        {
            Vector3f position_;
            Quaternion rotation_;
        };

    public:
        LSystem();

    private:
        void generate();

        const std::string axiom_;

        int iterations_;
        float angle_;
        float width_;
        float minLeafLength_;
        float maxLeafLength_;
        float minBranchLength_;
        float maxBranchLength_;
        float variance_;

        Mesh tree_, branch_, leaf_;
        Vector3f initialPosition_;

        std::map<char, std::string> rules_;
        std::stack<TreeTransform> transforms_;

        std::string currentPath_;
        std::vector<float> randomRotations_;
    };
}

#endif // NAGE_ENGINE_WORLD_PLANTS_LSYSTEM_H_
