#ifndef QNAGE_WRAPPER_NAGE_SCENEOBJECT_H_
#define QNAGE_WRAPPER_NAGE_SCENEOBJECT_H_

#include "engine/render/renderableobject.h"
#include "interface/isceneobject.h"
#include "nage_transformation.h"
#include "nage_resource.h"

namespace mr::qnage
{
    class NAGESceneObject
        : public ISceneObject
    {
    public:
        std::string id() const override
        {
            return object_->id();
        }

        ISceneObjectTransformation* transformation() override
        {
            return transformation_;
        }

        ISceneResource* resource() override
        {
            return resource_;
        }

        static NAGESceneObject* from(nage::RenderableObject* _object)
        {
            if(!_object)
                throw new std::invalid_argument("Cannot create item for not defined object");

            return new NAGESceneObject(_object);
        }

        static std::vector<ISceneObject*> map(std::vector<nage::RenderableObject*> _objects)
        {
            std::vector<ISceneObject*> result;
            for(auto object : _objects)
                result.push_back(NAGESceneObject::from(object));

            return result;
        }

    private:
        NAGESceneObject(nage::RenderableObject* _object) :
            object_(_object),
            transformation_(NAGESceneObjectTransformation::from(_object->transformation())),
            resource_(NAGEResource::from(_object->resource())) {}

        nage::RenderableObject* object_;
        ISceneObjectTransformation* transformation_;
        ISceneResource* resource_;
    };
}

#endif // QNAGE_WRAPPER_NAGE_SCENEOBJECT_H_
