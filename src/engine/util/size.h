#ifndef NAGE_ENGINE_UTIL_OBJ_SIZE_H_
#define NAGE_ENGINE_UTIL_OBJ_SIZE_H_

namespace NAGE
{
    template <typename T>
    class Size
    {
    public:
        Size() : mWidth(0), mHeight(0) {}
        Size(T _width, T _height) : mWidth(_width), mHeight(_height) {}

        // Getters
        T width() const { return mWidth; }
        T height() const { return mHeight; }

        // Setters
        void setWidth(T _width) { mWidth = _width; }
        void setHeight(T _height) { mHeight = _height; }

        bool operator==(const Size<T>& _rhs) { return this->mWidth == _rhs.mWidth && this->mHeight == _rhs.mHeight; }
        bool operator!=(const Size<T>& _rhs) { return !(*this == _rhs); }

    private:
        T mWidth, mHeight;
    };
}

#endif // NAGE_ENGINE_UTIL_OBJ_SIZE_H_
