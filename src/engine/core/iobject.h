#ifndef NAGE_ENGINE_CORE_SCENE_IOBJECT_H_
#define NAGE_ENGINE_CORE_SCENE_IOBJECT_H_

#include <string>

namespace mr::nage
{
    /**
     * @brief The IObject class is the base interface for engine components.
     */
    class IObject
    {
    public:
        virtual ~IObject() {}
        virtual std::string id() const = 0;
        virtual std::string type() const = 0;
    };
}

#endif // NAGE_ENGINE_CORE_SCENE_IOBJECT_H_
