#include "materialtype.h"

namespace NAGE
{
    const Material MaterialType::DEFAULT = Material(
                Vector3f(0.0f, 0.0f, 0.0f),
                Vector3f(0.01f, 0.01f, 0.01f),
                Vector3f(0.5f, 0.5f, 0.5f),
                0.25f);

    const Material MaterialType::EMERALD = Material(
                Vector3f(0.0215f, 0.1745f, 0.0215f),
                Vector3f(0.07568f, 0.61424f, 0.07568f),
                Vector3f(0.633f, 0.727811f, 0.633f),
                0.6f);

    const Material MaterialType::JADE = Material(
                Vector3f(0.135f, 0.2225f, 0.1575f),
                Vector3f(0.54f, 0.89f, 0.63f),
                Vector3f(0.316228f, 0.316228f, 0.316228f),
                0.1f);

    const Material MaterialType::OBSIDIAN = Material(
                Vector3f(0.05375f, 0.05f, 0.06625f),
                Vector3f(0.18275f, 0.17f, 0.22525f),
                Vector3f(0.332741f, 0.328634f, 0.346435f),
                0.3f);
}
