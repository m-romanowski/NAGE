#include "objectloader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>

namespace NAGE
{
    ObjectLoader::ObjectLoader(const std::string& _path)
    {
        // Loader supported extensions.
        mSupportedExt.push_back("obj");

        processFile(_path);
    }

    std::vector<std::string> ObjectLoader::supportedExt() const
    {
        return mSupportedExt;
    }

    ModelData ObjectLoader::data() const
    {
        return mModelData;
    }

    std::string ObjectLoader::fileExt(const std::string& _path)
    {
        std::size_t position = _path.rfind(".");

        if(position != std::string::npos)
            return _path.substr(position + 1);

        // If no extension return empty string.
        return "";
    }

    int ObjectLoader::supportedExt(const std::string& _path)
    {
        for(unsigned int i = 0; i < mSupportedExt.size(); i++)
        {
            if(mSupportedExt[i] == fileExt(_path))
                return i;
        }

        return -1;
    }

    void ObjectLoader::processFile(const std::string& _path)
    {
        unsigned int idx = supportedExt(_path);

        if(idx < 0)
        {
            Log::error("Loader: Unsupported file extension.");
            return;
        }

        switch(idx)
        {
            case 0:
                processOBJFile(_path);
                break;
        }
    }

    void ObjectLoader::processOBJFile(const std::string& _path)
    {
        std::ifstream file;

        try
        {
            file.open(_path);
            std::string line;

            ModelData modelData;
            std::vector<unsigned int> faceIdxs, uvIdxs, normalIdxs;

            while(std::getline(file, line))
            {
                std::stringstream stringStream;

                if(line.substr(0, 2) == "v ")
                {
                    float x, y, z;

                    stringStream << line.substr(2);
                    stringStream >> x >> y >> z;

                    modelData.position.push_back(Vector3f(x, y, z));
                }
                else if(line.substr(0, 2) == "vt")
                {
                    float x, y;

                    stringStream << line.substr(3);
                    stringStream >> x >> y;

                    modelData.uv.push_back(Vector2f(x, y));
                }
                else if(line.substr(0, 2) == "vn")
                {
                    float x, y, z;

                    stringStream << line.substr(2);
                    stringStream >> x >> y >> z;

                    modelData.normal.push_back(Vector3f(x, y, z));
                }
                else if(line.substr(0, 2) == "f ")
                {
                    // v/vt/vn
                    unsigned int faceIdx[3], textureIdx[3], normalIdx[3];
                    const char* chLine = line.c_str();

                    sscanf(chLine, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faceIdx[0], &textureIdx[0], &normalIdx[0],
                        &faceIdx[1], &textureIdx[1], &normalIdx[1], &faceIdx[2], &textureIdx[2], &normalIdx[2]);

                    // Face indexes
                    faceIdxs.push_back(faceIdx[0]);
                    faceIdxs.push_back(faceIdx[1]);
                    faceIdxs.push_back(faceIdx[2]);

                    // Texture indexes
                    uvIdxs.push_back(textureIdx[0]);
                    uvIdxs.push_back(textureIdx[1]);
                    uvIdxs.push_back(textureIdx[2]);

                    // Normal indexes
                    normalIdxs.push_back(normalIdx[0]);
                    normalIdxs.push_back(normalIdx[1]);
                    normalIdxs.push_back(normalIdx[2]);
                }
            }

            file.close();

            for(unsigned int i = 0; i < faceIdxs.size(); i++)
            {
                unsigned int vertexIndex = faceIdxs[i];
                unsigned int uvIndex = uvIdxs[i];
                unsigned int normalIndex = normalIdxs[i];

                Vector3f vertex = modelData.position[vertexIndex - 1];
                Vector2f uv = modelData.uv[uvIndex - 1];
                Vector3f normal = modelData.normal[normalIndex - 1];

                mModelData.position.push_back(vertex);
                mModelData.uv.push_back(uv);
                mModelData.normal.push_back(normal);
                mModelData.indices.push_back(i);
            }
        }
        catch(std::ifstream::failure& error)
        {
            Log::error("Loader: Cannot open file.");
            return;
        }
    }
}
