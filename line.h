#include <exception>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <vector>
#include <complex>
const int MAX_SIZE = 10000;
template<class T> class Line;
template <class T>struct Point {
    T x;
    T y;
    Point() {
        x = 0.0;
        y = 0.0;
    }
    Point<T>& operator =(const Point<T>& b) {
        x = b.x;
        y = b.y;
        return *this;
    }
    Line<T> operator+(Line<T>& v) {
        if (v.size() == MAX_SIZE) throw std::out_of_range("too large concat result");
        Line<T> tmp(v.size() + 1);
        tmp[0] = *this;
        for (int i = 1; i <= v.size(); ++i) tmp[i] = v[i - 1];
        return tmp;
    }
};
template<class T> class Line {
private:
    std::vector<Point<T>> data;// Point<T>* data
    int sz;
    static double eps;
public:
    Line(int n = 0) {
        sz = n;
        if (sz<0 || sz>MAX_SIZE) {
            throw std::out_of_range("incorrect size");
        }
        data = std::vector<Point<T>>(n);
    }
    Line(Line<T>& v) = default;
    int size() { return sz; }
    Point<T>& operator [](int i) {
        if (i >= sz || i < 0) throw std::out_of_range("index out of range");
        return data[i];
    }
    bool operator==(const Line<T>& v) {
        if (sz != v.sz) return false;
        for (int i = 0; i < sz; ++i) {
            if (std::abs(data[i].x - v.data[i].x) > eps || std::abs(data[i].y - v.data[i].y) > eps) return false;
        }
        return true;
    }
    bool operator!=(const Line<T>& v) {
        return !(*this == v);
    }
    Line<T>& operator = (const Line<T>& v) = default;
    Line<T> operator +(const Line<T>& v) {
        if (sz + v.sz > MAX_SIZE) throw std::out_of_range("too large concat result");
        Line<T> tmp(sz + v.sz);
        for (int i = 0; i < sz; ++i) tmp[i] = data[i];
        for (int i = 0; i < v.sz; ++i) {
            tmp[sz + i] = v.data[i];
        }
        return tmp;
    }
    Line<T> operator +(const Point<T>& p) {
        if (sz == MAX_SIZE) throw std::out_of_range("too large concat result");
        Line<T> tmp(sz + 1);
        for (int i = 0; i < sz; ++i) tmp[i] = data[i];
        tmp[sz] = p;
        return tmp;
    }
    typename std::vector<Point<T>>::iterator begin() { return data.begin(); }
    typename std::vector<Point<T>>::iterator end() { return data.end(); }
    double len() {
        double ans = 0;
        for (int i = 0; i < sz - 1; ++i) {
            T dx = data[i + 1].x - data[i].x;
            T dy = data[i + 1].y - data[i].y;
            ans += sqrt(std::abs(dx) * std::abs(dx) + std::abs(dy) * std::abs(dy));
        }
        return ans;
    }
    friend std::ostream& operator<<(std::ostream& ostr,  Line<T>& v) {
        for (auto el : v) ostr << el.x << ' ' << el.y << "\n";
        return ostr;
    }
    ~Line() = default;
};