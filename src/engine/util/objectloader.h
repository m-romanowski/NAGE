#ifndef NAGE_ENGINE_UTIL_OBJLOADER_H_
#define NAGE_ENGINE_UTIL_OBJLOADER_H_

#include "glad/glad.h"
#include "engine/math/NAGEMath/nagemathvector.h"
#include "common/log.h"

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

namespace mr::nage
{
    class ModelData
    {
    public:
        std::vector<Vector3f> position_;
        std::vector<Vector2f> uv_;
        std::vector<Vector3f> normal_;
        std::vector<GLuint> indices_;
    };

    class ObjectLoader
    {
    public:
        ObjectLoader(const std::string& _path);

        // Getters
        std::vector<std::string> supportedExt() const;
        ModelData data() const;

    private:
        void processFile(const std::string& _path);
        void processOBJFile(const std::string& _path);

        // Utils
        std::string fileExt(const std::string& _path);
        int supportedExt(const std::string& _path);

        std::vector<std::string> supportedExt_;
        ModelData modelData_;
        std::string path_;
    };
}

#endif // NAGE_ENGINE_UTIL_OBJLOADER_H_
