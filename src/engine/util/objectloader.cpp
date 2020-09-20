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
        supportedExt_.push_back("obj");

        processFile(_path);
    }

    std::vector<std::string> ObjectLoader::supportedExt() const
    {
        return supportedExt_;
    }

    ModelData ObjectLoader::data() const
    {
        return modelData_;
    }

    std::string ObjectLoader::fileExt(const std::string& _path)
    {
        std::size_t position_ = _path.rfind(".");

        if(position_ != std::string::npos)
            return _path.substr(position_ + 1);

        // If no extension return empty string.
        return "";
    }

    int ObjectLoader::supportedExt(const std::string& _path)
    {
        for(unsigned int i = 0; i < supportedExt_.size(); i++)
        {
            if(supportedExt_[i] == fileExt(_path))
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
            std::vector<unsigned int> faceIdxs, uv_Idxs, normal_Idxs;

            while(std::getline(file, line))
            {
                std::stringstream stringStream;

                if(line.substr(0, 2) == "v ")
                {
                    float x, y, z;

                    stringStream << line.substr(2);
                    stringStream >> x >> y >> z;

                    modelData.position_.push_back(Vector3f(x, y, z));
                }
                else if(line.substr(0, 2) == "vt")
                {
                    float x, y;

                    stringStream << line.substr(3);
                    stringStream >> x >> y;

                    modelData.uv_.push_back(Vector2f(x, y));
                }
                else if(line.substr(0, 2) == "vn")
                {
                    float x, y, z;

                    stringStream << line.substr(2);
                    stringStream >> x >> y >> z;

                    modelData.normal_.push_back(Vector3f(x, y, z));
                }
                else if(line.substr(0, 2) == "f ")
                {
                    // v/vt/vn
                    unsigned int faceIdx[3], textureIdx[3], normal_Idx[3];
                    const char* chLine = line.c_str();

                    sscanf(chLine, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faceIdx[0], &textureIdx[0], &normal_Idx[0],
                        &faceIdx[1], &textureIdx[1], &normal_Idx[1], &faceIdx[2], &textureIdx[2], &normal_Idx[2]);

                    // Face indexes
                    faceIdxs.push_back(faceIdx[0]);
                    faceIdxs.push_back(faceIdx[1]);
                    faceIdxs.push_back(faceIdx[2]);

                    // Texture indexes
                    uv_Idxs.push_back(textureIdx[0]);
                    uv_Idxs.push_back(textureIdx[1]);
                    uv_Idxs.push_back(textureIdx[2]);

                    // normal_ indexes
                    normal_Idxs.push_back(normal_Idx[0]);
                    normal_Idxs.push_back(normal_Idx[1]);
                    normal_Idxs.push_back(normal_Idx[2]);
                }
            }

            file.close();

            for(unsigned int i = 0; i < faceIdxs.size(); i++)
            {
                unsigned int vertexIndex = faceIdxs[i];
                unsigned int uv_Index = uv_Idxs[i];
                unsigned int normal_Index = normal_Idxs[i];

                Vector3f vertex = modelData.position_[vertexIndex - 1];
                Vector2f uv_ = modelData.uv_[uv_Index - 1];
                Vector3f normal_ = modelData.normal_[normal_Index - 1];

                modelData_.position_.push_back(vertex);
                modelData_.uv_.push_back(uv_);
                modelData_.normal_.push_back(normal_);
                modelData_.indices_.push_back(i);
            }
        }
        catch(std::ifstream::failure& error)
        {
            Log::error("Loader: Cannot open file.");
            return;
        }
    }
}
