
template <class T>
struct vector_type {
  using value_type = T;
  value_type x, y;
  vector_type(): x(0), y(0) { }
  vector_type(value_type x_, value_type y_): x(x_), y(y_) { }
  vector_type &operator += (const vector_type &rhs) { x += rhs.x; y += rhs.y; return *this; }
  vector_type operator + (const vector_type &rhs) const { return vector_type(*this) += rhs; }
  vector_type &operator -= (const vector_type &rhs) { x -= rhs.x; y -= rhs.y; return *this; }
  vector_type operator - (const vector_type &rhs) const { return vector_type(*this) -= rhs; }
  vector_type operator - () const { return vector_type(-x, -y); }
  vector_type &operator *= (value_type rhs) { x *= rhs; y *= rhs; return *this; }
  vector_type &operator /= (value_type rhs) { x /= rhs; y /= rhs; return *this; }
  bool operator == (const vector_type &rhs) const { return equal(x, rhs.x) && equal(y, rhs.y); }
  bool operator != (const vector_type &rhs) const { return !equal(x, rhs.x) || !equal(y, rhs.y); }
};

template <class T, class U>
vector_type<T> operator * (vector_type<T> v, U rhs) { return v *= rhs; }
template <class T, class U>
vector_type<T> operator * (U rhs, vector_type<T> v) { return v *= rhs; }
template <class T, class U>
vector_type<T> operator / (vector_type<T> v, U rhs) { return v /= rhs; }

template <class T>
std::istream& operator >> (std::istream& is, vector_type<T> &v) { return is >> v.x >> v.y; }
template <class T>
std::ostream& operator << (std::ostream& os, const vector_type<T> &v) { return os << v.x << ' ' <<  v.y; }

template <class T>
T norm(const vector_type<T> &v) { return v.x * v.x + v.y * v.y; }
template <class T>
T abs(const vector_type<T> &v) { return std::sqrt(norm(v)); }
template <class T>
T argr(const vector_type<T> &v) {  
  auto res = std::atan2(v.y, v.x); 
  return res < 0 ? res + 2 * real_constant<T>::pi() : res;
}
template <class T>
T argd(const vector_type<T> &v) { return argr(v) * 180 / real_constant<T>::pi(); }
template <class T>
T distance(const vector_type<T> &v, const vector_type<T> &u) { return abs(v - u); }
template <class T>
T dot(const vector_type<T> &v, const vector_type<T> &u) { return v.x * u.x + v.y * u.y; }
template <class T>
T cross(const vector_type<T> &v, const vector_type<T> &u) { return v.x * u.y - v.y * u.x; }

template <class T>
size_t orthan(const vector_type<T> &v) {
  if (v.x > 0 && v.y >= 0) return 0;
  if (v.x <= 0 && v.y > 0) return 1;
  if (v.x < 0 && v.y <= 0) return 2;
  if (v.x >= 0 && v.y < 0) return 3;
  return 0;
}

template <class T>
bool cmp_x(const vector_type<T> &v, const vector_type<T> &u) {
  if (equal(v.x, u.x)) return v.y < u.y;
  return v.x < u.x;
}
template <class T>
bool cmp_y(const vector_type<T> &v, const vector_type<T> &u) {
  if (equal(v.y, u.y)) return v.x < u.x;
  return v.y < u.y;
}
template <class T>
bool cmp_arg(const vector_type<T> &v, const vector_type<T> &u) {
  if (orthan(v) != orthan(u)) return orthan(v) < orthan(u);
  if (!equal(cross(v, u), 0)) return cross(v, u) > 0;
  return norm(v) < norm(u);
}

template <class T>
struct line_type {
  using value_type = T;
  value_type a, b, c;
  line_type(): a(0), b(0), c(0) { }
  line_type(value_type a_, value_type c_): a(a_), b(-1), c(c_) { }
  line_type(value_type a_, value_type b_, value_type c_): a(a_), b(b_), c(c_) { }
  value_type valx(value_type y) const { return (b * y + c) / (-a); }
  value_type valy(value_type x) const { return (a * x + c) / (-b); }
  bool operator == (const value_type &l) const { return equal(a * l.b, b * l.a) && equal(a * l.c, c * l.a); }
  bool operator != (const value_type &l) const { return !equal(a * l.b, b * l.a) || !equal(a * l.c, c * l.a); }
};

template <class T>
bool parallel(const line_type<T> &l, const line_type<T> &m) { return equal(l.a * m.b, l.b * m.a); };
template <class T>
bool vertical(const line_type<T> &l, const line_type<T> &m) { return equal(l.a * m.a + l.b * m.b, 0); };
template <class T>
bool is_on(const line_type<T> &l, const vector_type<T> &v) { return equal(l.a * v.x + l.b * v.y + l.c, 0);}

template <class T>
vector_type<T> intersection(const line_type<T> &l, const line_type<T> &m) {
  auto x = (l.b * m.c - l.c * m.b) / (l.a * m.b - l.b * m.a);
  auto y = (l.c * m.a - l.a * m.c) / (l.a * m.b - l.b * m.a);
  return vector_type<T>(x, y);
}
template <class T>
vector_type<T> direction(const line_type<T> &l) { return vector_type<T>(-l.b, l.a); }
template <class T>
vector_type<T> perpend(const line_type<T> &l, const vector_type<T> &v) {
  auto u = vector_type<T>(l.a, l.b);
  auto d = -l.c / norm(u);
  auto e = dot(v, u) / norm(u);
  return (d - e) * u;
}
template <class T>
vector_type<T> project(const line_type<T> &l, const vector_type<T> &v) {
  return v + perpend(l, v);
}
template <class T>
vector_type<T> relfect(const line_type<T> &l, const vector_type<T> &v) {
  return v + perpend(l, v) * 2;
}

template <class T>
T distance(const line_type<T> &l, const vector_type<T> &v) { 
  return std::abs(l.a * v.x + l.b * v.y + l.c) / abs(vector_type<T>(l.a, l.b)); 
}

template <class T>
struct segment_type {
  using value_type = T;
  vector_type<value_type> st, en;
  segment_type(): st(0, 0), en(0, 0) { }
  segment_type(const vector_type<value_type> &l, const vector_type<value_type> &r): st(l), en(r) { }
  segment_type(value_type x1, value_type y1, value_type x2, value_type y2): st(x1, y1), en(x2, y2) { } 
  bool operator == (const segment_type &s) const { 
    return (st == s.st && en == s.en) || (st == s.en && en == s.st);
  }
  bool operator != (const segment_type &s) const { 
    return !(st == s.st && en == s.en) && !(st == s.en && en == s.st);
  }
};

template <class T>
vector_type<T> direction(const segment_type<T> &l) { return l.en - l.st;; }
template <class T>
line_type<T> to_line(const segment_type<T> &s) {
  auto v = direction(s);
  auto c = v.y * s.st.x - v.x * s.st.y;
  return line_type<T>(-v.y, v.x, c);
}
template <class T>
line_type<T> bisect(const segment_type<T> &s) {
  auto v = direction(s), u = (s.st + s.en) / 2;
  return line_type<T>(v.x, v.y, -v.x * u.x - v.y * u.y);
}

template <class T>
bool intersects(const segment_type<T> &s, const segment_type<T> &t) {
  auto v = direction(s), u = direction(t);
  auto d = cross(v, t.st - s.st) * cross(v, t.en - s.st);
  auto e = cross(u, s.st - t.st) * cross(u, s.en - t.st);
  return leq(d, 0) && leq(e, 0);
}

template <class T>
struct circle_type {
  using value_type = T;
  vector_type<value_type> cn;
  value_type rd;
  circle_type(): cn(0, 0), rd(0) { }
  circle_type(const vector_type<value_type> &cn_, value_type rd_): cn(cn_), rd(rd_) { }
  circle_type(value_type x_, value_type y_, value_type rd_): cn(x_, y_), rd(rd_) { }
};

template <class T>
bool is_on(const circle_type<T> &c, const vector_type<T> &v) {
  return equal(c.rd * c.rd, norm(v - c.cn));
}
template <class T>
bool is_inside(const circle_type<T> &c, const vector_type<T> &v) {
  return geq(c.rd * c.rd, norm(v - c.cn));
}

template <class T>
std::vector<vector_type<T>> intersection(const circle_type<T> &c, const circle_type<T> &d) {
  auto v = d.cn - c.cn;
  auto l = abs(v);
  if (equal(l, 0)) return {};
  if (equal(l + c.rd + d.rd, std::max({ l, c.rd, d.rd }) * 2)) return { c.cn + v * (c.rd / l) };
  if (l + c.rd + d.rd < std::max({ l, c.rd, d.rd }) * 2) return {};
  auto x = -(d.rd * d.rd - l * l - c.rd * c.rd) / (l * 2);
  auto y = std::sqrt(c.rd * c.rd - x * x);
  auto mid = c.cn + v * (x / l);
  auto vec = (-v.y, v.x);
  return { mid + vec * (y / l), mid - vec * (y / l) };
}
template <class T>
std::vector<vector_type<T>> intersection(const circle_type<T> &c, const line_type<T> &l) {
  auto v = project(l, c.cn);
  if (is_on(c, v)) return { v };
  if (!is_inside(c, v)) return {};
  auto u = direction(l);
  auto d = std::sqrt(c.rd * c.rd - norm(v - c.cn)) / abs(u);
  return { v + u * d, v - u * d };
}
