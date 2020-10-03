#ifndef NAGE_ENGINE_UTIL_SIZE_H_
#define NAGE_ENGINE_UTIL_SIZE_H_

namespace mr::nage
{
    template <typename T>
    class Size
    {
    public:
        Size() : width_(0), height_(0) {}
        Size(T _width, T _height) : width_(_width), height_(_height) {}

        // Getters
        T width() const { return width_; }
        T height() const { return height_; }

        // Setters
        void setWidth(T _width) { width_ = _width; }
        void setHeight(T _height) { height_ = _height; }

        bool operator==(const Size<T>& _rhs) { return this->width_ == _rhs.width_ && this->height_ == _rhs.height_; }
        bool operator!=(const Size<T>& _rhs) { return !(*this == _rhs); }

    private:
        T width_, height_;
    };
}

#endif // NAGE_ENGINE_UTIL_SIZE_H_
