#ifndef NAGE_ENGINE_UTIL_OBJ_LOADER_H_
#define NAGE_ENGINE_UTIL_OBJ_LOADER_H_

#include "glad/glad.h"
#include "engine/math/NAGEMath/nagemathvector.h"
#include "common/log.h"

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <exception>

namespace NAGE
{
    class ModelData
    {
    public:
        std::vector<Vector3f> position;
        std::vector<Vector2f> uv;
        std::vector<Vector3f> normal;
        std::vector<GLuint> indices;
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

        std::vector<std::string> mSupportedExt;
        ModelData mModelData;
        std::string mPath;
    };
}

#endif // NAGE_ENGINE_UTIL_OBJ_LOADER_H_
