#pragma once

#include "Define.h"
#include "Color.h"

#include <math.h>
#include <vector>
#include <assert.h>

//x,y��2�̗v�f������ϐ��͂��̌^���g��
class Double2 {
public:
	double x;
	double y;

	Double2() :x(0.0), y(0.0) {}
	Double2(const double _x, const double _y, const bool normalize = false) :x(_x), y(_y) { if (normalize)this->Normalize(); }

	Double2 operator +() const { return *this; }
	Double2 operator -() const { return Double2(-x, -y); }
	Double2 operator +(const Double2& v) const { return Double2(x + v.x, y + v.y); }
	Double2 operator -(const Double2& v) const { return Double2(x - v.x, y - v.y); }
	Double2 operator *(const Double2& v) const { return Double2(x * v.x, y * v.y); }
	Double2 operator /(const Double2& v) const { return Double2(x / v.x, y / v.y); }
	Double2 operator +(const double v) const { return Double2(x + v, y + v); }
	Double2 operator -(const double v) const { return Double2(x - v, y - v); }
	Double2 operator *(const double v) const { return Double2(x * v, y * v); }
	Double2 operator /(const double v) const { return Double2(x / v, y / v); }
	Double2 operator +=(const Double2& v) { x += v.x; y += v.y; return *this; }
	Double2 operator -=(const Double2& v) { x -= v.x; y -= v.y; return *this; }
	Double2 operator *=(const Double2& v) { x *= v.x; y *= v.y; return *this; }
	Double2 operator /=(const Double2& v) { x /= v.x; y /= v.y; return *this; }
	Double2 operator =(const Double2& v) { x = v.x; y = v.y; return *this; }
	Double2 operator +=(const double v) { x += v; y += v; return *this; }
	Double2 operator -=(const double v) { x -= v; y -= v; return *this; }
	Double2 operator *=(const double v) { x *= v; y *= v; return *this; }
	Double2 operator /=(const double v) { x /= v; y /= v; return *this; }
	Double2 operator =(const double v) { x = v; y = v; return *this; }
	bool operator ==(const Double2& v) const { return x >= v.x - Define::Epsilon && x <= v.x + Define::Epsilon && y >= v.y - Define::Epsilon && y <= v.y + Define::Epsilon; }
	bool operator !=(const Double2& v) const { return !(*this == v); }
	//x == 0.0 && y == 0.0�Ȃ�(false)����ȊO�Ȃ�(true) 
	explicit operator bool() const { return *this != Zero; }

	//������2����擾
	double SqLength()const;
	//�������擾�i��r�Ɏg�������Ȃ�SqLength()�̕����y���j
	double Length()const;
	//�p�x���ʓx�Ŏ擾(-PI �` PI)
	double RadAngle()const;
	//���K���x�N�g�����擾�i�����͕ۑ��j
	Double2 GetNormalized()const;
	//����
	double Dot(const Double2& v)const;
	//�O�ρi���g���E���Ȃ琳�j
	double Cross(const Double2& v)const;
	//���K��
	Double2 Normalize();

	const static Double2 Zero;
};

//�x�N�g��
class Vec2 : public Double2 {
public:
	Vec2() :Double2() {}
	Vec2(const double _x, const double _y, const bool normalize = false) :Double2(_x, _y, normalize) {}
	Vec2(const Double2& v) :Double2(v) {}
	Vec2(const double angle) :Double2(cos(angle), sin(angle)) {}
	Vec2(const Vec2& angle, const double length) :Double2(angle.GetNormalized().x * length, angle.GetNormalized().y * length) {}

	Vec2 SetLength  (const double v);
	Vec2 AddLength  (const double v);
	Vec2 SetAngle   (const Vec2& v);
	Vec2 AddAngle   (const Vec2& v);
	Vec2 InvertAngle(void);

	Vec2 GetSetLength    (const double v) const;
	Vec2 GetAddedLength  (const double v) const;
	Vec2 GetSetAngle     (const Vec2& v) const;
	Vec2 GetAddedAngle   (const Vec2& v) const;
	Vec2 GetInvertedAngle(void) const;
	
	//�����֌W�ɂ��邩�H
	bool IsVertical(const Vec2& v) const;
	//���s�֌W�ɂ��邩�H
	bool IsParallel(const Vec2& v) const;
	//�s�p�֌W�ɂ��邩�H
	bool IsSharpAngle(const Vec2& v) const;
};

class Point2D;
class Circle2D;
class Segment2D;
class Cupsule2D;
class Polygon2D;
class Rect2D;
class AABB2D;

class Primitive2D {
public:
	virtual Primitive2D* const PrimRotate(const Point2D& pivot, const Vec2& angle) = 0;
	virtual Primitive2D* const PrimScale(const Point2D& pivot, const double& scale) = 0;
	virtual AABB2D GetAABB2D() const = 0;
	virtual double Distance(Primitive2D* const target) const = 0;
	virtual bool IsCollided(Primitive2D* const target) const = 0;
	virtual void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1) const = 0;
	Point2D* const GetAsPoint2D();
	Circle2D* const GetAsCircle2D();
	Segment2D* const GetAsSegment2D();
	Cupsule2D* const GetAsCupsule2D();
	Polygon2D* const GetAsPolygon2D();
	virtual Point2D& GetP() = 0;
};

//�_
class Point2D : public Double2, public Primitive2D {
public:
	Point2D() :Double2() {}
	Point2D(const double _x, const double _y) :Double2(_x, _y) {}
	Point2D(const Double2& d) :Double2(d) {}

	//���g����������܂ޒ����ɉ��낵�������̑��𓾂�
	//tOut : �����̑��𓾂邽�߂�target��v�ɂ�����W���i�o�́j
	Point2D Leg(const Segment2D& target, double* const tOut = NULL) const;

	Point2D Rotate(const Point2D& pivot, const Vec2&   angle);
	Point2D Scale (const Point2D& pivot, const double& scale);

	Point2D GetRotated(const Point2D& pivot, const Vec2&   angle) const;
	Point2D GetScaled (const Point2D& pivot, const double& scale) const;

	Primitive2D* const PrimRotate(const Point2D& pivot, const Vec2& angle) override;
	Primitive2D* const PrimScale(const Point2D& pivot, const double& scale) override;

	AABB2D GetAABB2D() const override;

	double Distance(Primitive2D* const target) const override;
	double Distance(const AABB2D&      target) const;
	double Distance(const Point2D&     target) const;
	double Distance(const Circle2D&    target) const;
	double Distance(const Segment2D&   target) const;
	double Distance(const Cupsule2D&   target) const;
	double Distance(const Polygon2D&   target) const;
											 
	bool IsCollided(Primitive2D* const target) const override;
	bool IsCollided(const AABB2D&      target) const;
	bool IsCollided(const Point2D&     target) const;
	bool IsCollided(const Circle2D&    target) const;
	bool IsCollided(const Segment2D&   target) const;
	bool IsCollided(const Cupsule2D&   target) const;
	bool IsCollided(const Polygon2D&   target) const;

	void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1) const;

	Point2D& GetP() override;
};

//�~
class Circle2D : public Primitive2D{
public:
	Point2D p;	// ���S
	double r;	// ���a
	Circle2D() :p(), r(1.0) {}
	Circle2D(const Point2D& _p, const double _r) :p(_p), r(_r) {}

	Circle2D Rotate(const Point2D& pivot, const Vec2&  angle);
	Circle2D Scale(const Point2D& pivot, const double& scale);

	Circle2D GetRotated(const Point2D& pivot, const Vec2&  angle) const;
	Circle2D GetScaled(const Point2D& pivot, const double& scale) const;

	Primitive2D* const PrimRotate(const Point2D& pivot, const Vec2& angle) override;
	Primitive2D* const PrimScale(const Point2D& pivot, const double& scale) override;

	AABB2D GetAABB2D() const override;

	double Distance(Primitive2D* const target) const override;
	double Distance(const Point2D&     target) const;
	double Distance(const Circle2D&    target) const;
	double Distance(const Segment2D&   target) const;
	double Distance(const Cupsule2D&   target) const;
	double Distance(const Polygon2D&   target) const;
	double Distance(const AABB2D&      target) const;

	bool IsCollided(Primitive2D* const target) const override;
	bool IsCollided(const Point2D&     target) const;
	bool IsCollided(const Circle2D&    target) const;
	bool IsCollided(const Segment2D&   target) const;
	bool IsCollided(const Cupsule2D&   target) const;
	bool IsCollided(const Polygon2D&   target) const;
	bool IsCollided(const AABB2D&      target) const;

	void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1)const;

	Point2D& GetP() override;
};

//����
class Segment2D : public Primitive2D{
public:
	Point2D p;	//�n�_
	Vec2 v;		//�n�_����I�_�܂ł̃x�N�g��

	Segment2D() :p(), v() {}
	Segment2D(const Point2D& _p, const Vec2& _v) : p(_p), v(_v) {}
	//�n�_�ƏI�_���w��
	Segment2D(const Point2D& p1, const Point2D& p2) :p(p1), v(p2 - p1) {}

	//������̓_�̍��W���擾����
	//t : �x�N�g���ɂ�����W���i�f�t�H���g��1.0�A�I�_���擾����j
	Point2D PointOnLine(const double t = 1.0) const;

	//target���玩�g�ɉ��낵�������̑��𓾂�
	//tOut : �����̑��𓾂邽�߂Ɏ��g��v�ɂ�����W���i�o�́j
	Point2D Leg(const Point2D& target, double* const tOut = NULL)const;

	Segment2D Rotate(const Point2D& pivot, const Vec2&   angle);
	Segment2D Scale (const Point2D& pivot, const double& scale);

	Segment2D& SetEndPoint(const Point2D& newEndPoint);

	Segment2D GetRotated(const Point2D& pivot, const Vec2&   angle) const;
	Segment2D GetScaled (const Point2D& pivot, const double& scale) const;

	Primitive2D* const PrimRotate(const Point2D& pivot, const Vec2& angle) override;
	Primitive2D* const PrimScale(const Point2D& pivot, const double& scale) override;

	AABB2D GetAABB2D() const override;

	double Distance(Primitive2D* const target) const override;
	double Distance(const Point2D&     target) const;
	double Distance(const Circle2D&    target) const;
	double Distance(const Segment2D&   target) const;
	double Distance(const Cupsule2D&   target) const;
	double Distance(const Polygon2D&   target) const;
	double Distance(const AABB2D&      target) const;

	bool IsCollided(Primitive2D* const target) const override;
	bool IsCollided(const Point2D&     target) const;
	bool IsCollided(const Circle2D&    target) const;
	bool IsCollided(const Segment2D&   target) const;
	bool IsCollided(const Cupsule2D&   target) const;
	bool IsCollided(const Polygon2D&   target) const;
	bool IsCollided(const AABB2D& target) const;

	void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1)const;

	Point2D& GetP() override;
};

//�J�v�Z��
class Cupsule2D : public Primitive2D {
public:
	Segment2D s;	//�c�ƂȂ����
	double r;		//���a
	Cupsule2D() :s(), r(1.0) {}
	Cupsule2D(const Segment2D& _s, const double _r) :s(_s), r(_r) {}
	Cupsule2D(const Point2D& _p, const Vec2& _v, const double _r) :s(_p, _v), r(_r) {}
	Cupsule2D(const Point2D& p1, const Point2D& p2, const double r) :s(p1, p2), r(r) {}

	Cupsule2D Rotate(const Point2D& pivot, const Vec2&   angle);
	Cupsule2D Scale (const Point2D& pivot, const double& scale);
	
	Cupsule2D GetRotated(const Point2D& pivot, const Vec2&   angle) const;
	Cupsule2D GetScaled (const Point2D& pivot, const double& scale) const;

	Primitive2D* const PrimRotate(const Point2D& pivot, const Vec2& angle) override;
	Primitive2D* const PrimScale(const Point2D& pivot, const double& scale) override;

	AABB2D GetAABB2D() const override;

	double Distance(Primitive2D* const target) const override;
	double Distance(const Point2D&     target) const;
	double Distance(const Circle2D&    target) const;
	double Distance(const Segment2D&   target) const;
	double Distance(const Cupsule2D&   target) const;
	double Distance(const Polygon2D&   target) const;
	double Distance(const AABB2D&      target) const;

	bool IsCollided(Primitive2D* const target) const override;
	bool IsCollided(const Point2D&     target) const;
	bool IsCollided(const Circle2D&    target) const;
	bool IsCollided(const Segment2D&   target) const;
	bool IsCollided(const Cupsule2D&   target) const;
	bool IsCollided(const Polygon2D&   target) const;
	bool IsCollided(const AABB2D&      target) const;

	void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1)const;

	Point2D& GetP() override;
};


//���p�`
class Polygon2D : public Primitive2D{
public:
	Point2D p;					//��_
	std::vector<Vec2> verts;	//��_����e���_�ւ̃x�N�g���i���v���j
	Polygon2D() = default;
	//��_���w�肷��
	//absolutePosFlag : �e���_���Έʒu�Ŏw�肷�邩�̃t���O
	Polygon2D(
		const Point2D& _p,
		const std::initializer_list<Vec2>& _verts,
		const bool absolutePosFlag = false,
		const Vec2& angle = Vec2(0.0),
		const double scale = 1.0) 
		:p(_p), verts(_verts)
	{
		assert(verts.size() >= 3);
		if (absolutePosFlag) {
			for (int i = 0; i < _verts.size(); i++) {
				verts[i].x -= _p.x;
				verts[i].y -= _p.y;
			}
		}
		for (int i = 0; i < verts.size(); i++)
			assert(Edge(i).v.Cross(Edge((i + 1 == verts.size()) ? 0 : i + 1).v) > 0.0);
		AddAngle(angle); Extend(scale);
	}
	//��_���w�肵�Ȃ��i��_�͏d�S�ɂȂ�j
	Polygon2D(const std::initializer_list<Vec2> absoluteVertsPos, const Vec2& angle = Vec2(0.0), const double scale = 1.0) :verts(absoluteVertsPos)
	{
		assert(verts.size() >= 3);
		Vec2 sumVerts;
		for (Vec2 v : verts)
			sumVerts += v;
		p = sumVerts / verts.size();
		for (int i = 0; i < verts.size(); i++)
			verts[i] -= p;
		for (int i = 0; i < verts.size(); i++)
			assert(Edge(i).v.Cross(Edge((i + 1 == verts.size()) ? 0 : i + 1).v) > 0.0);
		AddAngle(angle); Extend(scale);
	}

	Polygon2D(const std::vector<Point2D> absoluteVertsPos)
	{
		assert(absoluteVertsPos.size() >= 3);
		Vec2 sumVerts;
		for (const Vec2& v : absoluteVertsPos)
			sumVerts += v;
		p = sumVerts / absoluteVertsPos.size();
		for (int i = 0; i < absoluteVertsPos.size(); i++)
			verts.push_back(absoluteVertsPos.at(i) - p);
		for (int i = 0; i < verts.size(); i++)
			assert(Edge(i).v.Cross(Edge((i + 1 == verts.size()) ? 0 : i + 1).v) > 0.0);
	}
	//��_�𒆐S�ɉ�]������
	void AddAngle(const Vec2& angle);
	//��_�𒆐S�Ɋg�傷��
	//v��1.0�Ȃ炻�̂܂�
	void Extend(const double v);
	//n�Ԗڂ̒��_�̓_���𓾂�
	Point2D Vert(const int n) const;
	//n�Ԗڂ̕ӂ̐������𓾂�
	Segment2D Edge(const int n)const;
	//�d�S�̈ʒu�𓾂�
	Point2D Center(void)const;

	Polygon2D Rotate(const Point2D& pivot, const Vec2&   angle);
	Polygon2D Scale (const Point2D& pivot, const double& scale);

	Polygon2D GetRotated(const Point2D& pivot, const Vec2&   angle) const;
	Polygon2D GetScaled (const Point2D& pivot, const double& scale) const;

	Primitive2D* const PrimRotate(const Point2D& pivot, const Vec2& angle) override;
	Primitive2D* const PrimScale(const Point2D& pivot, const double& scale) override;

	AABB2D GetAABB2D() const override;

	double Distance(Primitive2D* const target) const override;
	double Distance(const Point2D&     target) const;
	double Distance(const Circle2D&    target) const;
	double Distance(const Segment2D&   target) const;
	double Distance(const Cupsule2D&   target) const;
	double Distance(const Polygon2D&   target) const;
											 
	bool IsCollided(Primitive2D* const target) const override;
	bool IsCollided(const Point2D&     target) const;
	bool IsCollided(const Circle2D&    target) const;
	bool IsCollided(const Segment2D&   target) const;
	bool IsCollided(const Cupsule2D&   target) const;
	bool IsCollided(const Polygon2D&   target) const;

	void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1)const;

	Point2D& GetP() override;
};

//��`�i��]�\�j
class Rect2D : Polygon2D {
public:
	Rect2D(const Point2D& p, const Double2& size, const Vec2& angle = Vec2(0.0), const double scale = 1.0)
		:Polygon2D(p, { Vec2(size.x / 2, size.y / 2), Vec2(-size.x / 2, size.y / 2), Vec2(-size.x / 2, -size.y / 2), Vec2(size.x / 2, -size.y / 2) }, false, angle, scale) {}
	Rect2D(void) :Rect2D(Point2D::Zero, Double2(1.0, 1.0)) {}
	//���ƍ�����ݒ肷��
	void SetSize(const Double2& size);
};

//�����s���E�{�b�N�X
class AABB2D {
public:
	AABB2D();
	AABB2D(const AABB2D& obj);
	AABB2D(const Point2D& _lt, const Point2D& _rb);
	AABB2D(const Double2& size);
	AABB2D(const double left, const double top, const double right, const double bottom);
	~AABB2D() = default;
	AABB2D operator +(const Double2& v) const { return AABB2D(lt + v, rb + v); }
	AABB2D& operator +=(const Double2& v) { lt += v; rb += v; return *this; }
	AABB2D operator -(const Double2& v) const { return AABB2D(lt - v, rb - v); }
	AABB2D& operator -=(const Double2& v) { lt -= v; rb -= v; return *this; }
	//lt�����̒l�ɂȂ�悤�Ɉړ�����
	AABB2D& operator =(const Point2D& v) { rb += v - lt; lt = v; return *this; }
	Double2 Size() const;
	Point2D LeftTop() const;
	Point2D RightBottom() const;
	Point2D LeftBottom() const;
	Point2D RightTop() const;
	Point2D Center() const;
	Point2D LeftTop(const Point2D& p, const bool transform);
	Point2D RightBottom(const Point2D& p, const bool transform);
	Point2D LeftBottom(const Point2D& p, const bool transform);
	Point2D RightTop(const Point2D& p, const bool transform);
	Point2D Center(const Point2D& p);
	double Top() const;
	double Bottom() const;
	double Left() const;
	double Right() const;
	double Top(const double y, const bool transform);
	double Bottom(const double y, const bool transform);
	double Left(const double x, const bool transform);
	double Right(const double x, const bool transform);
	double Height() const;
	double Width() const;

	bool IsCollidedToVerticalLine(const double x, const double y1, const double y2) const;
	bool IsCollidedToHorizontalLine(const double y, const double x1, const double x2) const;

	double Distance(const Point2D& target) const;
	double Distance(const Circle2D& target) const;
	double Distance(const Segment2D& target) const;
	double Distance(const Cupsule2D& target) const;

	bool IsCollided(const Circle2D& target) const;
	bool IsCollided(const Point2D& target) const;
	bool IsCollided(const Segment2D& target) const;
	bool IsCollided(const Cupsule2D& target) const;
	bool IsCollided(const AABB2D& target) const;

	void Draw(const unsigned int color = Color::Get(ColorID::White), const bool fillFlag = false, const int lineThickness = 1)const;


private:
	void LTRBNormalize();
	Point2D lt, rb;
};