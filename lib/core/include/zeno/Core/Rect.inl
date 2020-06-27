template <typename T>
Rect<T>::Rect(void) :
    left(0),
    bot(0),
    width(0),
    height(0) {
}

template <typename T>
Rect<T>::Rect(T _left, T _bot, T _width, T _height) :
    left(_left),
    bot(_bot),
    width(_width),
    height(_height) {
}

template <typename T>
Rect<T>::Rect(const Vector2<T>& _position, const Vector2<T>& _size) :
    left(_position.x),
    bot(_position.y),
    width(_size.x),
    height(_size.y) {
}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& _rect) :
    left(static_cast<T>(_rect.left)),
    bot(static_cast<T>(_rect.bot)),
    width(static_cast<T>(_rect.width)),
    height(static_cast<T>(_rect.height)) {
}

template <typename T>
bool Rect<T>::contains(T _x, T _y) {
    T minX = std::min(left, static_cast<T>(left + width));
    T maxX = std::max(left, static_cast<T>(left + width));
    T minY = std::min(bot, static_cast<T>(bot + height));
    T maxY = std::max(bot, static_cast<T>(bot + height));

    return (_x >= minX) && (_x < maxX) && (_y >= minY) && (_y < maxY);
}
template <typename T>
bool Rect<T>::contains(const Vector2<T>& _position) {
    return contains(_position.x, _position.y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& _rect, Rect<T>& _intersection /*= Rect<T>()*/) {

    T r1MinX = std::min(left, static_cast<T>(left + width));
    T r1MaxX = std::max(left, static_cast<T>(left + width));
    T r1MinY = std::min(bot, static_cast<T>(bot + height));
    T r1MaxY = std::max(bot, static_cast<T>(bot + height));

    // Compute the min and max of the second rectangle on both axes
    T r2MinX = std::min(_rect.left, static_cast<T>(_rect.left + _rect.width));
    T r2MaxX = std::max(_rect.left, static_cast<T>(_rect.left + _rect.width));
    T r2MinY = std::min(_rect.bot, static_cast<T>(_rect.bot + _rect.height));
    T r2MaxY = std::max(_rect.bot, static_cast<T>(_rect.bot + _rect.height));

    // Compute the intersection boundaries
    T interLeft = std::max(r1MinX, r2MinX);
    T interbot = std::max(r1MinY, r2MinY);
    T interRight = std::min(r1MaxX, r2MaxX);
    T interTop = std::min(r1MaxY, r2MaxY);

    // If the intersection is valid (positive non zero area), then there is an intersection

    if ((interLeft < interRight) && (interbot < interTop)) {
        _intersection = Rect<T>(interLeft, interbot, interRight - interLeft, interTop - interbot);
        return true;
    }

    _intersection = Rect<T>(0, 0, 0, 0);
    return false;
}

template <typename T>
void Rect<T>::expandToContain(const Rect<T>& _rect) {
    T r1MinX = std::min(left, static_cast<T>(left + width));
    T r1MaxX = std::max(left, static_cast<T>(left + width));
    T r1MinY = std::min(bot, static_cast<T>(bot + height));
    T r1MaxY = std::max(bot, static_cast<T>(bot + height));

    // Compute the min and max of the second rectangle on both axes
    T r2MinX = std::min(_rect.left, static_cast<T>(_rect.left + _rect.width));
    T r2MaxX = std::max(_rect.left, static_cast<T>(_rect.left + _rect.width));
    T r2MinY = std::min(_rect.bot, static_cast<T>(_rect.bot + _rect.height));
    T r2MaxY = std::max(_rect.bot, static_cast<T>(_rect.bot + _rect.height));

    T minX = std::min(r1MinX, r2MinX);
    T maxX = std::max(r1MaxX, r2MaxX);
    T minY = std::min(r1MinY, r2MinY);
    T maxY = std::max(r1MaxY, r2MaxY);

    left = minX;
    width = maxX - minX;

    bot = minY;
    height = maxY - minY;
}

template <typename T>
bool operator ==(const Rect<T>& _left, const Rect<T>& _right) {
    return (_left.left == _right.left 	&&
        _left.bot == _right.bot	&&
        _left.width == _right.width &&
        _left.height == _right.height);
}

template <typename T>
bool operator !=(const Rect<T>& _left, const Rect<T>& _right) {
    return !(_left == _right);
}