#include "Transform.h"

namespace neu
{
    bool Transform::Write(const rapidjson::Value& value) const
    {
        return false;
    }

    bool Transform::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, position);
        READ_DATA(value, scale);

        glm::vec3 euler;
        READ_NAME_DATA(value, "rotation", euler);
        rotation = math::EulerToQuaternion(euler);

        return false;
    }
}
