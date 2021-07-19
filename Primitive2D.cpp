#include "Primitive2D.h"

#include "Utility.h"

#include <DxLib.h>
#include <assert.h>

double Double2::SqLength()const
{
	return x * x + y * y;
}

double Double2::Length()const
{
	return sqrt(SqLength());
}

double Double2::RadAngle()const
{
	return atan2(y, x);
}

Double2 Double2::GetNormalized()const
{
	const double length = Length();
	if (1.0 - Define::Epsilon < length && length < 1.0 + Define::Epsilon)
		return *this;
	if (length > 0.0)
		return Double2(x / length, y / length);
	return Double2::Zero;
}

double Double2::Dot(const Double2& v)const
{
	return x * v.x + y * v.y;
}

double Double2::Cross(const Double2& v)const
{
	return x * v.y - y * v.x;
}

Double2 Double2::Normalize()
{
	if (*this != Double2::Zero)
		*this = GetNormalized();
	return *this;
}

const Double2 Double2::Zero = { 0.0,0.0 };

Vec2 Vec2::SetLength(const double v)
{
	Normalize();
	return *this *= v;
}

Vec2 Vec2::GetSetLength(const double v) const
{
	return GetNormalized() * v;
}

Vec2 Vec2::AddLength(const double v)
{
	return *this = GetAddedAngle(v);
}

Vec2 Vec2::GetAddedLength(const double v) const
{
	const double newLength = Length() + v;
	return GetSetLength(newLength);
}

Vec2 Vec2::SetAngle(const Vec2& v)
{
	return *this = GetSetAngle(v);
}

Vec2 Vec2::GetSetAngle(const Vec2& v) const
{
	return GetAddedAngle(v.GetAddedAngle(this->GetInvertedAngle()));
}

Vec2 Vec2::AddAngle(const Vec2& v)
{
	return *this = GetAddedAngle(v);
}

Vec2 Vec2::GetAddedAngle(const Vec2& v) const
{
	const Vec2 angle = v.GetNormalized();
	return Vec2(angle.x * x - angle.y * y, angle.y * x + angle.x * y);
}

Vec2 Vec2::InvertAngle(void)
{
	return *this = GetInvertedAngle();
}

Vec2 Vec2::GetInvertedAngle(void) const
{
	return *this * Double2(1.0, -1.0);
}

bool Vec2::IsVertical(const Vec2& v)const
{
	const double dot = Dot(v);
	return 0.0 - Define::Epsilon <= dot && dot <= 0.0 + Define::Epsilon;
}

bool Vec2::IsParallel(const Vec2& v)const
{
	const double cross = Cross(v);
	return 0.0 - Define::Epsilon <= cross && cross <= 0.0 + Define::Epsilon;
}

bool Vec2::IsSharpAngle(const Vec2& v)const
{
	return Dot(v) > 0.0;
}

Point2D Point2D::Leg(const Segment2D& target, double* const tOut)const
{
	const double t = (*this - target.p).Dot(target.v) / target.v.SqLength();
	if (tOut)
		*tOut = t;
	return target.PointOnLine(t);
}

Point2D Point2D::Rotate(const Point2D& pivot, const Vec2& angle)
{
	return *this = GetRotated(pivot, angle);
}

Point2D Point2D::Scale(const Point2D& pivot, const double& scale)
{
	return *this = GetScaled(pivot, scale);
}

Point2D Point2D::GetRotated(const Point2D& pivot, const Vec2& angle) const
{
	return Vec2(*this - pivot).GetAddedAngle(angle) + pivot;
}

Point2D Point2D::GetScaled(const Point2D& pivot, const double& scale) const
{
	return pivot + (*this - pivot) * scale;
}

Primitive2D* const Point2D::PrimRotate(const Point2D& pivot, const Vec2& angle)
{
	return &(Rotate(pivot, angle));
}

Primitive2D* const Point2D::PrimScale(const Point2D& pivot, const double& scale)
{
	return &(Scale(pivot, scale));
}

AABB2D Point2D::GetAABB2D() const
{
	return AABB2D(*this, *this);
}

double Point2D::Distance(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return Distance(*p);
	if (c != nullptr)
		return Distance(*c);
	if (s != nullptr)
		return Distance(*s);
	if (C != nullptr)
		return Distance(*C);
	if (P != nullptr)
		return Distance(*P);
	return 0.0;
}

double Point2D::Distance(const AABB2D& target) const
{
	if (x < target.LeftTop().x) {
		if (y < target.LeftTop().y)
			return Distance(target.LeftTop());
		if (y > target.RightBottom().y)
			return Distance(Point2D(target.LeftTop().x, target.RightBottom().y));
		return target.LeftTop().x - x;
	}
	if (x > target.RightBottom().x) {
		if (y < target.LeftTop().y)
			return Distance(Point2D(target.RightBottom().x, target.LeftTop().y));
		if (y > target.RightBottom().y)
			return Distance(target.RightBottom());
		return x - target.RightBottom().x;
	}
	if (y < target.LeftTop().y)
		return target.LeftTop().y - y;
	if (y > target.RightBottom().y)
		return y - target.RightBottom().y;
	return -min(min(x - target.LeftTop().x, target.RightBottom().x - x), min(y - target.LeftTop().y, target.RightBottom().y - y));
}

double Point2D::Distance(const Point2D& p)const
{
	return (*this - p).Length();
}

double Point2D::Distance(const Circle2D& c)const
{
	return Distance(c.p) - c.r;
}

double Point2D::Distance(const Segment2D& s)const
{
	if (s.v.SqLength() < Define::Epsilon)
		return Distance(s.p);
	double t;
	const Point2D h = Leg(s, &t);
	if (t < 0.0)
		return Distance(s.p);
	if (t > 1.0)
		return Distance(s.PointOnLine());
	return Distance(h);
}

double Point2D::Distance(const Cupsule2D& C)const
{
	return Distance(C.s) - C.r;
}

double Point2D::Distance(const Polygon2D& P)const
{
	int i = 0;
	double dis = Distance(P.Edge(i));
	for (i = 1; i < P.verts.size(); i++) {
		const double tmpDis = Distance(P.Edge(i));
		if (tmpDis < dis)
			dis = tmpDis;
	}
	return (IsCollided(P) ? -1 : +1) * dis;
}

bool Point2D::IsCollided(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return IsCollided(*p);
	if (c != nullptr)
		return IsCollided(*c);
	if (s != nullptr)
		return IsCollided(*s);
	if (C != nullptr)
		return IsCollided(*C);
	if (P != nullptr)
		return IsCollided(*P);
	return 0.0;
}

bool Point2D::IsCollided(const AABB2D& target) const
{
	return x >= target.LeftTop().x && x <= target.RightBottom().x && y >= target.LeftTop().y && y <= target.RightBottom().y;
}

bool Point2D::IsCollided(const Point2D& p)const
{
	return Distance(p) < Define::Epsilon;
}

bool Point2D::IsCollided(const Circle2D& c)const
{
	return Distance(c) <= 0;
}

bool Point2D::IsCollided(const Segment2D& s)const
{
	const Vec2 v(*this - s.p);
	if (v.IsParallel(s.v) &&					//sの始点から自身へ向かうベクトルvがs.vと並行かつ
		s.v.Dot(v) >= 0 &&						//自身がsの始点から見てsの終点側にありかつ
		v.SqLength() <= s.v.SqLength())			//sの始点から自身までの距離がsの長さ以下だったら
		return true;							//自身はs上にある
	return false;
}

bool Point2D::IsCollided(const Cupsule2D& C)const
{
	return Distance(C.s) <= C.r;
}

//Pのすべての辺から見て自身が右側にあったら自身はPの内部にある
bool Point2D::IsCollided(const Polygon2D& P)const
{
	for (int i = 0; i < P.verts.size(); i++) {
		if (P.Edge(i).v.Cross(*this - P.Vert(i)) < 0)
			return false;
	}
	return true;
}

Circle2D Circle2D::Rotate(const Point2D& pivot, const Vec2& angle)
{
	return *this = GetRotated(pivot, angle);
}

Circle2D Circle2D::Scale(const Point2D& pivot, const double& scale)
{
	return *this = GetScaled(pivot, scale);
}

Circle2D Circle2D::GetRotated(const Point2D& pivot, const Vec2& angle) const
{
	return Circle2D(p.GetRotated(pivot, angle), r);
}

Circle2D Circle2D::GetScaled(const Point2D& pivot, const double& scale) const
{
	return Circle2D(p.GetScaled(pivot, scale), r * scale);
}

Primitive2D* const Circle2D::PrimRotate(const Point2D& pivot, const Vec2& angle)
{
	return &(Rotate(pivot, angle));
}

Primitive2D* const Circle2D::PrimScale(const Point2D& pivot, const double& scale)
{
	return &(Scale(pivot, scale));
}

AABB2D Circle2D::GetAABB2D() const
{
	return AABB2D(p - r, p + r);
}

double Circle2D::Distance(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return Distance(*p);
	if (c != nullptr)
		return Distance(*c);
	if (s != nullptr)
		return Distance(*s);
	if (C != nullptr)
		return Distance(*C);
	if (P != nullptr)
		return Distance(*P);
	return 0.0;
}

double Circle2D::Distance(const Point2D& p)const
{
	return p.Distance(*this);
}

double Circle2D::Distance(const Circle2D& c)const
{
	if (!IsCollided(c)) 
		return p.Distance(c.p) - r - c.r;
	const double sqCenterDis = (p - c.p).SqLength();
	const double sqRadiusDif = (r - c.r) * (r - c.r);
	if (sqCenterDis < sqRadiusDif)
		return -(sqrt(sqRadiusDif) - sqrt(sqCenterDis));
	return 0.0;
}

double Circle2D::Distance(const Segment2D& s)const
{
	if (!IsCollided(s))
		return p.Distance(s) - r;
	if (!IsCollided(s.p) || !IsCollided(s.PointOnLine()))
		return 0.0;
	const double sqDisToP = (p - s.p).SqLength();
	const double sqDisToE = (p - s.PointOnLine()).SqLength();
	if (sqDisToP < sqDisToE)
		return sqrt(sqDisToE) - r;
	return sqrt(sqDisToP) - r;
}

double Circle2D::Distance(const Cupsule2D& C)const
{
	if (!IsCollided(C))
		return p.Distance(C.s) - r - C.r;
	const double disPToS = p.Distance(C.s);
	if (r <= C.r) {
		if (C.r - r <= disPToS)
			return 0.0;
		return C.r - r - disPToS;
	}
	if (r - C.r <= disPToS)
		return 0.0;
	return r - C.r - disPToS;
}

double Circle2D::Distance(const Polygon2D& P)const
{
	const double disPToP = p.Distance(P);
	if (disPToP > 0.0)
		return disPToP - r;
	if (-disPToP > r)
		return -disPToP - r;
	return 0.0;
}

double Circle2D::Distance(const AABB2D& target) const
{
	const double pDis = p.Distance(target);
	if (pDis > r)
		return pDis - r;
	if (pDis < -r)
		return pDis + r;
	return 0.0;
}

bool Circle2D::IsCollided(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return IsCollided(*p);
	if (c != nullptr)
		return IsCollided(*c);
	if (s != nullptr)
		return IsCollided(*s);
	if (C != nullptr)
		return IsCollided(*C);
	if (P != nullptr)
		return IsCollided(*P);
	return 0.0;
}

bool Circle2D::IsCollided(const AABB2D& target) const
{
	return p.Distance(target) < r;
}

bool Circle2D::IsCollided(const Point2D& p)const
{
	return p.IsCollided(*this);
}
bool Circle2D::IsCollided(const Circle2D& c)const
{
	return (p - c.p).SqLength() < (r + c.r) * (r + c.r);
}
bool Circle2D::IsCollided(const Segment2D& s)const
{
	return p.Distance(s) < r;
}
bool Circle2D::IsCollided(const Cupsule2D& C)const
{
	return p.Distance(C.s) <= r + C.r;
}
bool Circle2D::IsCollided(const Polygon2D& P)const
{
	return p.Distance(P) <= r;
}

Point2D Segment2D::PointOnLine(const double t) const
{
	return Point2D(p + v * t);
}

Point2D Segment2D::Leg(const Point2D& target, double* const tOut)const
{
	return target.Leg(*this, tOut);
}

Segment2D Segment2D::Rotate(const Point2D& pivot, const Vec2& angle)
{
	return *this = GetRotated(pivot, angle);
}

Segment2D Segment2D::Scale(const Point2D& pivot, const double& scale)
{
	return *this = GetScaled(pivot, scale);
}

Segment2D& Segment2D::SetEndPoint(const Point2D& newEndPoint)
{
	v = newEndPoint - p;
	return *this;
}

Segment2D Segment2D::GetRotated(const Point2D& pivot, const Vec2& angle) const
{
	return Segment2D(p.GetRotated(pivot, angle), v.GetAddedAngle(angle));
}

Segment2D Segment2D::GetScaled(const Point2D& pivot, const double& scale) const
{
	return Segment2D(p.GetScaled(pivot, scale), (Vec2)(v * scale));
}

Primitive2D* const Segment2D::PrimRotate(const Point2D& pivot, const Vec2& angle)
{
	return &(Rotate(pivot, angle));
}

Primitive2D* const Segment2D::PrimScale(const Point2D& pivot, const double& scale)
{
	return &(Scale(pivot, scale));
}

AABB2D Segment2D::GetAABB2D() const
{
	if (v.x > 0) {
		if (v.y > 0)
			return AABB2D(p, PointOnLine());
		return AABB2D(Point2D(p.x, PointOnLine().y), Point2D(PointOnLine().x, p.y));
	}
	if (v.y > 0)
		return AABB2D(Point2D(PointOnLine().x, p.y), Point2D(p.x, PointOnLine().y));
	return AABB2D(PointOnLine(), p);
}

double Segment2D::Distance(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return Distance(*p);
	if (c != nullptr)
		return Distance(*c);
	if (s != nullptr)
		return Distance(*s);
	if (C != nullptr)
		return Distance(*C);
	if (P != nullptr)
		return Distance(*P);
	return 0.0;
}

double Segment2D::Distance(const Point2D& p) const
{
	return p.Distance(*this);
}

double Segment2D::Distance(const Circle2D& c)const
{
	return c.Distance(*this);
}

double Segment2D::Distance(const Segment2D& s)const
{
	if (IsCollided(s))
		return 0.0;
	double H11 = Distance(s.p);
	double H12 = Distance(s.PointOnLine());
	double H21 = p.Distance(s);
	double H22 = PointOnLine().Distance(s);
	double dis = H11;
	if (H12 < dis)
		dis = H12;
	if (H21 < dis)
		dis = H21;
	if (H22 < dis)
		dis = H22;
	return dis;
}

double Segment2D::Distance(const Cupsule2D& C)const
{
	if (!IsCollided(C))
		return Distance(C.s) - C.r;
	if (!p.IsCollided(C) || !PointOnLine().IsCollided(C))
		return 0.0;
	const double disP = p.Distance(C);
	const double disE = PointOnLine().Distance(C);
	return (disP < disE) ? disE : disP;
}
double Segment2D::Distance(const Polygon2D& P)const
{
	if (!IsCollided(P)) {
		int i = 0;
		double dis = Distance(P.Edge(i));
		for (i = 1; i < P.verts.size(); i++) {
			const double tmpDis = Distance(P.Edge(i));
			if (tmpDis < dis)
				dis = tmpDis;
		}
		return dis;
	}
	if (!p.IsCollided(P) || !PointOnLine().IsCollided(P))
		return 0.0;
	int i = 0;
	const double disP = p.Distance(P);
	const double disE = PointOnLine().Distance(P);
	return (disP < disE) ? disE : disP;
}

double Segment2D::Distance(const AABB2D& target) const
{
	if (IsCollided(target)) {
		if (!p.IsCollided(target) || !PointOnLine().IsCollided(target))
			return 0.0;
		return Utility::Max(p.Distance(target), PointOnLine().Distance(target));
	}
	const Vec2 normalV = v.GetNormalized();
	const double tXMin = (target.Left() - p.x) / normalV.x;
	const double tXMax = (target.Right() - p.x) / normalV.x;
	const double tYMin = (target.Top() - p.y) / normalV.y;
	const double tYMax = (target.Bottom() - p.y) / normalV.y;
	if (Utility::Min(tXMax, tYMax) - Utility::Max(tXMin, tYMin) >= 0)
		return Utility::Min(p.Distance(target), PointOnLine().Distance(target));
	return Utility::Min(Utility::Min(Distance(target.LeftTop()), Distance(target.LeftBottom())), Utility::Min(Distance(target.RightTop()), Distance(target.RightBottom())));
}

bool Segment2D::IsCollided(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return IsCollided(*p);
	if (c != nullptr)
		return IsCollided(*c);
	if (s != nullptr)
		return IsCollided(*s);
	if (C != nullptr)
		return IsCollided(*C);
	if (P != nullptr)
		return IsCollided(*P);
	return 0.0;
}

bool Segment2D::IsCollided(const Point2D& p)const
{
	return p.IsCollided(*this);
}

bool Segment2D::IsCollided(const Circle2D& c)const
{
	return c.IsCollided(*this);
}

bool Segment2D::IsCollided(const Segment2D& s)const
{
	const Vec2 v1v2 = s.p - p;
	const double cross = v.Cross(s.v);
	const double t1 = v1v2.Cross(s.v);
	const double t2 = v1v2.Cross(this->v);
	if (t1 < 0 || t1 > 1 || t2 < 0 || t2 > 1)
		return false;
	return 
		0.0 <= t1 && t1 <= 1.0 &&
		0.0 <= t2 && t2 <= 1.0;
}
bool Segment2D::IsCollided(const Cupsule2D& C)const
{
	return Distance(C) <= C.r;
}
bool Segment2D::IsCollided(const Polygon2D& P)const
{
	for (int i = 0; i < P.verts.size(); i++) {
		if (IsCollided(P.Edge(i)))
			return true;
	}
	return false;
}

bool Segment2D::IsCollided(const AABB2D& target) const
{
	if (p.IsCollided(target) || PointOnLine().IsCollided(target))
		return true;
	if (v.SqLength() == 0.0)
		return false;
	if (v.x == 0.0)
		return target.IsCollidedToVerticalLine(p.x, p.y, PointOnLine().y);
	if (v.y == 0.0)
		return target.IsCollidedToHorizontalLine(p.y, p.x, PointOnLine().x);
	const AABB2D sAABB = GetAABB2D();
	if (!sAABB.IsCollided(target))
		return false;
	const AABB2D colliderToLine(Utility::Max(sAABB.Left(), target.Left()), Utility::Max(sAABB.Top(), target.Top()), Utility::Min(sAABB.Right(), target.Right()), Utility::Min(sAABB.Bottom(), target.Bottom()));
	const Vec2 normalV = v.GetNormalized();
	double tXMin, tXMax, tYMin, tYMax;
	if (v.x > 0.0) {
		tXMin = (target.Left() - p.x) / v.x;
		tXMax = (target.Right() - p.x) / v.x;
	}
	else {
		tXMin = (target.Right() - p.x) / v.x;
		tXMax = (target.Left() - p.x) / v.x;
	}
	if (v.y > 0.0) {
		tYMin = (target.Top() - p.y) / v.y;
		tYMax = (target.Bottom() - p.y) / v.y;
	}
	else {
		tYMin = (target.Bottom() - p.y) / v.y;
		tYMax = (target.Top() - p.y) / v.y;
	}
	return Utility::Min(tXMax, tYMax) - Utility::Max(tXMin, tYMin) >= 0.0;
}

Cupsule2D Cupsule2D::Rotate(const Point2D& pivot, const Vec2& angle)
{
	return *this = GetRotated(pivot, angle);
}

Cupsule2D Cupsule2D::Scale(const Point2D& pivot, const double& scale)
{
	return *this = GetScaled(pivot, scale);
}

Cupsule2D Cupsule2D::GetRotated(const Point2D& pivot, const Vec2& angle) const
{
	return Cupsule2D(s.GetRotated(pivot, angle), r);
}

Cupsule2D Cupsule2D::GetScaled(const Point2D& pivot, const double& scale) const
{
	return Cupsule2D(s.GetScaled(pivot, scale), r * scale);
}

Primitive2D* const Cupsule2D::PrimRotate(const Point2D& pivot, const Vec2& angle)
{
	return &(Rotate(pivot, angle));
}

Primitive2D* const Cupsule2D::PrimScale(const Point2D& pivot, const double& scale)
{
	return &(Scale(pivot, scale));
}

AABB2D Cupsule2D::GetAABB2D() const
{
	AABB2D buf = s.GetAABB2D();
	buf.LeftTop(buf.LeftTop() - r, true);
	buf.RightBottom(buf.RightBottom() + r, true);
	return buf;
}

double Cupsule2D::Distance(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return Distance(*p);
	if (c != nullptr)
		return Distance(*c);
	if (s != nullptr)
		return Distance(*s);
	if (C != nullptr)
		return Distance(*C);
	if (P != nullptr)
		return Distance(*P);
	return 0.0;
}

double Cupsule2D::Distance(const Point2D& p)const
{
	return p.Distance(*this);
}
double Cupsule2D::Distance(const Circle2D& c)const
{
	return c.Distance(*this);
}
double Cupsule2D::Distance(const Segment2D& s)const
{
	return s.Distance(*this);
}
double Cupsule2D::Distance(const Cupsule2D& C)const
{
	if (!IsCollided(C))
		return Distance(C.s) - r;
	if (r < C.r) {
		if (s.Distance(C) > r - C.r)
			return 0.0;
		return s.Distance(C) - (r - C.r);
	}
	if (C.s.Distance(*this) > C.r - r)
		return 0.0;
	return C.s.Distance(*this) - (C.r - r);
}
double Cupsule2D::Distance(const Polygon2D& P)const
{
	if (!IsCollided(P))
		return s.Distance(P) - r;
	for (int i = 0; i < P.verts.size(); i++)
		if (Distance(P.Edge(i)) == 0.0)
			return 0.0;
	if (IsCollided(P.Vert(0))) {
		double dis = Distance(P.Vert(0));
		for (int i = 1; i < P.verts.size(); i++) {
			const double tmpDis = Distance(P.Vert(i));
			if (tmpDis > dis)
				dis = tmpDis;
		}
		return dis;
	}
	return s.Distance(P) + r;
}

double Cupsule2D::Distance(const AABB2D& target) const
{
	const double segDis = s.Distance(target);
	if (segDis > r)
		return segDis - r;
	if (segDis < -r)
		return segDis + r;
	return 0.0;
}

bool Cupsule2D::IsCollided(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return IsCollided(*p);
	if (c != nullptr)
		return IsCollided(*c);
	if (s != nullptr)
		return IsCollided(*s);
	if (C != nullptr)
		return IsCollided(*C);
	if (P != nullptr)
		return IsCollided(*P);
	return 0.0;
}

bool Cupsule2D::IsCollided(const Point2D& p)const
{
	return p.IsCollided(*this);
}
bool Cupsule2D::IsCollided(const Circle2D& c)const
{
	return c.IsCollided(*this);
}
bool Cupsule2D::IsCollided(const Segment2D& s)const
{
	return s.IsCollided(*this);
}
bool Cupsule2D::IsCollided(const Cupsule2D& C)const
{
	return s.Distance(C) <= r;
}
bool Cupsule2D::IsCollided(const Polygon2D& P)const
{
	for (int i = 0; i < P.verts.size(); i++)
		if (IsCollided(P.Edge(i)))
			return true;
	return false;
}

bool Cupsule2D::IsCollided(const AABB2D& target) const
{
	return s.Distance(target) <= r;
}

void Polygon2D::AddAngle(const Vec2& v)
{
	if (!v)
		return;
	for (int i = 0; i < verts.size(); i++) {
		verts[i].AddAngle(v);
	}
}

void Polygon2D::Extend(const double v)
{
	if (v == 1.0)
		return;
	for (int i = 0; i < verts.size(); i++) {
		verts[i] *= v;
	}
}

Point2D Polygon2D::Vert(const int n)const
{
	assert(0 <= n && n < verts.size());
	return Point2D(p + verts[n]);
}

Segment2D Polygon2D::Edge(const int n)const
{
	assert(0 <= n && n < verts.size());
	return Segment2D(p + verts[n], Vec2(verts[n + 1 == verts.size() ? 0 : n + 1] - verts[n]));
}

Point2D Polygon2D::Center(void) const
{
	Vec2 sum;
	for (Vec2 v : verts)
		sum += v;
	return sum / verts.size() + p;
}

Polygon2D Polygon2D::Rotate(const Point2D& pivot, const Vec2& angle)
{
	return *this = GetRotated(pivot, angle);
}

Polygon2D Polygon2D::Scale(const Point2D& pivot, const double& scale)
{
	return *this = GetScaled(pivot, scale);
}

Polygon2D Polygon2D::GetRotated(const Point2D& pivot, const Vec2& angle) const
{
	Polygon2D buf = *this;
	for (int i = 0; i < verts.size(); i++)
		buf.verts[i].AddAngle(angle);
	buf.p.Rotate(pivot, angle);
	return buf;
}

Polygon2D Polygon2D::GetScaled(const Point2D& pivot, const double& scale) const
{
	Polygon2D buf = *this;
	buf.p.Scale(pivot, scale);
	for (auto& it : buf.verts)
		it *= scale;
	return buf;
}

Primitive2D* const Polygon2D::PrimRotate(const Point2D& pivot, const Vec2& angle)
{
	return &(Rotate(pivot, angle));
}

Primitive2D* const Polygon2D::PrimScale(const Point2D& pivot, const double& scale)
{
	return &(Scale(pivot, scale));
}

AABB2D Polygon2D::GetAABB2D() const
{
	Point2D lt(1, 1);
	Point2D rb(-1, -1);
	for (auto vert : verts) {
		lt.x = min(lt.x, vert.x);
		lt.y = min(lt.y, vert.y);
		rb.x = max(rb.x, vert.x);
		rb.y = max(rb.y, vert.y);
	}
	return AABB2D(lt + p, rb + p);
}

double Polygon2D::Distance(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return Distance(*p);
	if (c != nullptr)
		return Distance(*c);
	if (s != nullptr)
		return Distance(*s);
	if (C != nullptr)
		return Distance(*C);
	if (P != nullptr)
		return Distance(*P);
	return 0.0;
}

double Polygon2D::Distance(const Point2D& p)const
{
	return p.Distance(*this);
}

double Polygon2D::Distance(const Circle2D& c)const
{
	return c.Distance(*this);
}

double Polygon2D::Distance(const Segment2D& s)const
{
	return s.Distance(*this);
}

double Polygon2D::Distance(const Cupsule2D& C)const
{
	return C.Distance(*this);
}

double Polygon2D::Distance(const Polygon2D& P)const
{
	if (!IsCollided(P)) {
		double dis = Edge(0).Distance(P);
		for (int i = 1; i < verts.size(); i++) {
			const double tmpDis = Edge(i).IsCollided(P);
			if (tmpDis < dis)
				dis = tmpDis;
		}
		return dis;
	}
	for (int i = 0; i < verts.size(); i++)
		if (Edge(i).IsCollided(P))
			return 0.0;
	if (Vert(0).IsCollided(P)) {
		double dis = Vert(0).Distance(P);
		for (int i = 1; i < verts.size(); i++) {
			const double tmpDis = Vert(i).Distance(P);
			if (tmpDis > dis)
				dis = tmpDis;
		}
		return dis;
	}
	double dis = P.Vert(0).Distance(*this);
	for (int i = 1; i < P.verts.size(); i++) {
		const double tmpDis = P.Vert(i).Distance(*this);
		if (tmpDis > dis)
			dis = tmpDis;
	}
	return dis;
}

bool Polygon2D::IsCollided(Primitive2D* const target) const
{
	const Point2D* p = dynamic_cast<Point2D*>(target);
	const Circle2D* c = dynamic_cast<Circle2D*>(target);
	const Segment2D* s = dynamic_cast<Segment2D*>(target);
	const Cupsule2D* C = dynamic_cast<Cupsule2D*>(target);
	const Polygon2D* P = dynamic_cast<Polygon2D*>(target);

	if (p != nullptr)
		return IsCollided(*p);
	if (c != nullptr)
		return IsCollided(*c);
	if (s != nullptr)
		return IsCollided(*s);
	if (C != nullptr)
		return IsCollided(*C);
	if (P != nullptr)
		return IsCollided(*P);
	return 0.0;
}

bool Polygon2D::IsCollided(const Point2D& p)const
{
	return p.IsCollided(*this);
}

bool Polygon2D::IsCollided(const Circle2D& c)const
{
	return c.IsCollided(*this);
}

bool Polygon2D::IsCollided(const Segment2D& s)const
{
	return s.IsCollided(*this);
}

bool Polygon2D::IsCollided(const Cupsule2D& C)const
{
	return C.IsCollided(*this);
}

bool Polygon2D::IsCollided(const Polygon2D& P)const
{
	for (int i = 0; i < verts.size(); i++)
		if (Edge(i).IsCollided(P))
			return true;
	return false;
}

void Rect2D::SetSize(const Double2& size)
{
	const Vec2 angle = Edge(2).v.GetNormalized();
	const Double2 halfSize = size / 2;
	verts[0] = Vec2(halfSize.x, halfSize.y);
	verts[1] = Vec2(-halfSize.x, halfSize.y);
	verts[2] = Vec2(-halfSize.x, -halfSize.y);
	verts[3] = Vec2(halfSize.x, -halfSize.y);
	AddAngle(angle);
};

void Point2D::Draw(const unsigned int color, const bool fillFlag, const int lineThickness)const
{
	DrawCircle(x, y, lineThickness, color);
}

Point2D& Point2D::GetP()
{
	return *this;
}

void Circle2D::Draw(const unsigned int color, const bool fillFlag, const int lineThickness)const
{
	DrawCircle(p.x, p.y, r, color, fillFlag, lineThickness);
}

Point2D& Circle2D::GetP()
{
	return this->p;
}

void Segment2D::Draw(const unsigned int color, const bool fillFlag, const int lineThickness)const
{
	DrawLine(p.x, p.y, PointOnLine().x, PointOnLine().y, color, lineThickness);
}

Point2D& Segment2D::GetP()
{
	return p;
}

void Cupsule2D::Draw(const unsigned int color, const bool fillFlag, const int lineThickness)const
{
	DrawCircle(s.p.x, s.p.y, r, color, fillFlag, lineThickness);
	Point2D ep = s.PointOnLine();
	DrawCircle(ep.x, ep.y, r, color, fillFlag, lineThickness);
	if (fillFlag) {
		s.Draw(color, r * 2);
	}
	else {
		s.Draw(color, lineThickness);
		Vec2 normV = s.v.GetNormalized() * r;
		normV.AddAngle(Define::Pi / 2);
		Point2D sp1 = s.p + normV;
		Point2D sp2 = s.p - normV;
		Segment2D(sp1, s.v).Draw(color, lineThickness);
		Segment2D(sp2, s.v).Draw(color, lineThickness);
	}
}

Point2D& Cupsule2D::GetP()
{
	return s.p;
}

void Polygon2D::Draw(const unsigned int color, const bool fillFlag, const int lineThickness)const
{
	if (fillFlag) {
		const Point2D vert0 = Vert(0);
		for (int i = 0; i < verts.size() - 2; i++) {
			const Point2D vert1 = Vert(i + 1), vert2 = Vert(i + 2);
			DrawTriangle(vert0.x, vert0.y, vert1.x, vert1.y, vert2.x, vert2.y, color, true);
		}
	}
	else
	{
		for (int i = 0; i < verts.size(); i++) {
			Edge(i).Draw(color, lineThickness);
		}
	}
}

Point2D& Polygon2D::GetP()
{
	return p;
}

AABB2D::AABB2D()
	:lt(Point2D::Zero), rb(Point2D::Zero)
{
}

AABB2D::AABB2D(const AABB2D& obj)
	: lt(obj.lt), rb(obj.rb)
{
}

Point2D AABB2D::Center() const
{
	return lt + (rb - lt) / 2;
}

Double2 AABB2D::Size() const
{
	return Double2(rb - lt);
}

Point2D AABB2D::LeftTop() const
{
	return lt;
}

Point2D AABB2D::RightBottom() const
{
	return rb;
}

Point2D AABB2D::LeftBottom() const
{
	return Point2D(lt.x, rb.y);
}

Point2D AABB2D::RightTop() const
{
	return Point2D(rb.x, lt.y);
}

Point2D AABB2D::LeftTop(const Point2D& p, const bool transform)
{
	if (transform) {
		lt = p;
		LTRBNormalize();
	}
	else {
		rb += p - lt;
		lt = p;
	}
	return lt;
}

Point2D AABB2D::RightBottom(const Point2D& p, const bool transform)
{
	if (transform) {
		rb = p;
		LTRBNormalize();
	}
	else {
		lt += p - rb;
		rb = p;
	}
	return rb;
}

Point2D AABB2D::LeftBottom(const Point2D& p, const bool transform)
{
	if (transform) {
		lt.x = p.x;
		rb.y = p.y;
		LTRBNormalize();
	}
	else {
		const Vec2 offset = p - LeftBottom();
		lt += offset;
		rb += offset;
	}
	return LeftBottom();
}

Point2D AABB2D::RightTop(const Point2D& p, const bool transform)
{
	if (transform) {
		rb.x = p.x;
		lt.y = p.y;
		LTRBNormalize();
	}
	else {
		const Vec2 offset = p - RightTop();
		lt += offset;
		rb += offset;
	}
	return RightTop();
}

Point2D AABB2D::Center(const Point2D& p)
{
	const Double2 Size = AABB2D::Size();
	lt = p - Size / 2;
	rb = p + Size / 2;
	return Center();
}

double AABB2D::Top() const
{
	return lt.y;
}

double AABB2D::Bottom() const
{
	return rb.y;
}

double AABB2D::Left() const
{
	return lt.x;
}

double AABB2D::Right() const
{
	return rb.x;
}

double AABB2D::Top(const double y, const bool transform)
{
	if (transform) {
		lt.y = y;
		LTRBNormalize();
	}
	else {
		rb.y += y - lt.y;
		lt.y = y;
	}
	return Top();
}

double AABB2D::Bottom(const double y, const bool transform)
{
	if (transform) {
		rb.y = y;
		LTRBNormalize();
	}
	else {
		lt.y += y - rb.y;
		rb.y = y;
	}
	return rb.y;
}

double AABB2D::Left(const double x, const bool transform)
{
	if (transform) {
		lt.x = x;
		LTRBNormalize();
	}
	else {
		rb.x += x - lt.x;
		lt.x = x;
	}
	return Left();
}

double AABB2D::Right(const double x, const bool transform)
{
	if (transform) {
		rb.x = x;
		LTRBNormalize();
	}
	else {
		lt.x += x - rb.x;
		rb.x = x;
	}
	return Right();
}

double AABB2D::Height() const
{
	return rb.y - lt.y;
}

double AABB2D::Width() const
{
	return rb.x - lt.x;
}

bool AABB2D::IsCollided(const AABB2D& target) const
{
	return
		lt.x < target.rb.x&&
		rb.x > target.lt.x &&
		lt.y < target.rb.y&&
		rb.y > target.lt.y;
}

bool AABB2D::IsCollided(const Circle2D& target) const
{
	return target.IsCollided(*this);
}

bool AABB2D::IsCollidedToVerticalLine(const double x, const double y1, const double y2) const
{
	if (x <= lt.x || rb.x <= x)
		return false;
	const double top = min(y1, y2);
	const double bottom = max(y1, y2);
	return top < rb.y&& bottom > lt.y;
}

bool AABB2D::IsCollidedToHorizontalLine(const double y, const double x1, const double x2) const
{
	if (y <= lt.y || rb.y <= y)
		return false;
	const double left = min(x1, x2);
	const double right = max(x1, x2);
	return left < rb.x && right > lt.x;
}

double AABB2D::Distance(const Point2D& target) const
{
	return target.Distance(*this);
}

double AABB2D::Distance(const Circle2D& target) const
{
	return target.Distance(*this);
}

double AABB2D::Distance(const Segment2D& target) const
{
	return target.Distance(*this);
}

double AABB2D::Distance(const Cupsule2D& target) const
{
	return target.Distance(*this);
}

bool AABB2D::IsCollided(const Point2D& target) const
{
	return target.IsCollided(*this);
}

bool AABB2D::IsCollided(const Segment2D& target) const
{
	return target.IsCollided(*this);
}

bool AABB2D::IsCollided(const Cupsule2D& target) const
{
	return target.IsCollided(*this);
}

void AABB2D::Draw(const unsigned int color, const bool fillFlag, const int lineThickness) const
{
	DrawBox(lt.x, lt.y, rb.x, rb.y, color, fillFlag);
}

void AABB2D::LTRBNormalize()
{
	if (lt.x <= rb.x && lt.y <= rb.y)
		return;
	std::swap(lt, rb);
}

AABB2D::AABB2D(const Point2D& _lt, const Point2D& _rb)
	: lt(_lt), rb(_rb)
{
	LTRBNormalize();
}

AABB2D::AABB2D(const Double2& size) :
	lt(), rb(size)
{
	LTRBNormalize();
}

AABB2D::AABB2D(const double left, const double top, const double right, const double bottom):
	lt(left, top), rb(right, bottom)
{
	LTRBNormalize();
}

Point2D* const Primitive2D::GetAsPoint2D() 
{
	return dynamic_cast<Point2D*>(this);
}

Circle2D* const Primitive2D::GetAsCircle2D()
{
	return dynamic_cast<Circle2D*>(this);
}

Segment2D* const Primitive2D::GetAsSegment2D()
{
	return dynamic_cast<Segment2D*>(this);
}

Cupsule2D* const Primitive2D::GetAsCupsule2D()
{
	return dynamic_cast<Cupsule2D*>(this);
}

Polygon2D* const Primitive2D::GetAsPolygon2D()
{
	return dynamic_cast<Polygon2D*>(this);
}
