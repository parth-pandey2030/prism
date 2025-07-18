template <typename T>
T LIMIT(T (*func)(T), T a, T h) {
    return func(a + h);
}