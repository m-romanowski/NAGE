#ifndef NAGE_ENGINE_UTIL_OBJ_LOADER_H_
#define NAGE_ENGINE_UTIL_OBJ_LOADER_H_

#include "engine/math/NAGEMath/nagemathvector.h"
#include <vector>
#include <string>

namespace NAGE
{
    struct OBJIndex
    {
        unsigned int vertexIndex;
        unsigned int uvIndex;
        unsigned int normalIndex;

        bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
    };

    class IndexedModel
    {
    public:
        /*
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec3> normals;
        */
        std::vector<Vector3f> positions;
        std::vector<Vector2f> texCoords;
        std::vector<Vector3f> normals;
        std::vector<unsigned int> indices;

        void CalcNormals();
    };

    class OBJModel
    {
    public:
        std::vector<OBJIndex> OBJIndices;
        /*
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;
        */
        std::vector<Vector3f> vertices;
        std::vector<Vector2f> uvs;
        std::vector<Vector3f> normals;
        bool hasUVs;
        bool hasNormals;

        OBJModel(const std::string& fileName);

        IndexedModel ToIndexedModel();
    private:
        unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
        void CreateOBJFace(const std::string& line);
        /*
        glm::vec2 ParseOBJVec2(const std::string& line);
        glm::vec3 ParseOBJVec3(const std::string& line);
        */
        Vector2f ParseOBJVec2(const std::string& line);
        Vector3f ParseOBJVec3(const std::string& line);
        OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
    };
}

#endif // NAGE_ENGINE_UTIL_OBJ_LOADER_H_
