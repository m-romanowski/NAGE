#include "lsystem.h"
#include <random>

namespace mr::nage
{
    LSystem::LSystem()
        : axiom_("X"),
          randomRotations_(RANDOM_ROTATIONS_COUNT, 0.0f)
    {
        /*std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<float> distr(-1.0f, 1.0f);

        for(auto& rotation : randomRotations_)
            rotation = distr(gen);

        rules.insert(std::make_pair('X', "[-FX][+FX][FX]"));
        rules.insert(std::make_pair('F', "FF"));

        generate();*/
    }

    void LSystem::generate()
    {
        /*currentPath = axiom_;

        std::string pathBuilder;

        for(int i = 0; i < iterations; i++)
        {
            char* currentPathChars = currentPath.data();
            while(*currentPathChars != '\0')
            {
                auto it = rules.find(*currentPathChars);
                it != rules.end()
                    ? pathBuilder.append(rules.at(*currentPathChars))
                    : pathBuilder.append(std::string(1, *currentPathChars));

                currentPath = pathBuilder;
                pathBuilder = "";
                currentPathChars++;
            }
        }

        for(unsigned int i = 0; i < currentPath.length(); i++)
        {
            switch(currentPath[i])
            {
                case 'F':
                    bool isLeaf = false;

                    Mesh currentElement;
                    if(currentPath[i + 1] % currentPath.length() == 'X' ||
                        (currentPath[i + 3] % currentPath.length() == 'F' &&
                        currentPath[i + 4] % currentPath.length() == 'X'))
                    {
                        currentElement = leaf;
                    }
                    else
                    {
                        currentElement = branch;
                    }

                    Transform* transform = new Transform;
            }
        }*/
    }
}
