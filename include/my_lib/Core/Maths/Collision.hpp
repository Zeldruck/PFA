#if !defined(COLLISION_HPP)
#define COLLISION_HPP

#include "OrientedBox.hpp"
#include "Plane.hpp"
#include "Quad.hpp"
#include "Cylinder.hpp"
#include "Ray.hpp"
#include "AABB.hpp"
#include "Capsule.hpp"

class Hit
{
public:
	Vec3 point, normal;
	inline Hit();
	inline ~Hit();
};

inline Hit::Hit()
{
	point 	= Vec3(0,0,0);
	normal 	= Vec3(0,0,0);
}

inline Hit::~Hit()
{}

//Here all the functions i do in Collision.cpp with the line they start.

bool IsSphereCollidingWithOrientedBox						(const Sphere& A, const OrientedBox& B); //Line 3;

bool IsOrientedBoxCollidingWithOrientedBox					(const OrientedBox& A, const OrientedBox& B); //Line 20;

bool IsSegmentIntersectingPlane								(const Segment& seg, const Plane& plane, Hit& hit); //Line 64;

bool IsSegmentIntersectingQuad								(const Segment& seg, const Quad& quad, Hit& hit); //Line 83;

bool IsSegmentIntersectingSphere							(const Segment& seg, const Sphere& sphere, Hit& hit); //Line 106;

bool IsSegmentIntersectingInfiniteCylinder					(const Segment& seg, const InfiniteCylinder& cyl, Hit& hit); //Line 140;

bool IsSegmentIntersectingFiniteCylinder					(const Segment& seg, const FiniteCylinder& cyl, Hit& hit); //Line 227;

bool IsSegmentIntersectingCapsule							(const Segment& seg, const Capsule& caps, Hit& hit); //Line 358;

bool IsSegmentIntersectingAABB								(const Segment& seg, const AABB& A, Hit& hit);

bool IsSegmentIntersectingOrientedBox						(const Segment& seg, const OrientedBox& A, Hit& hit);

bool GetFirstCollisionPointBetweenMovingSphereAndStaticBox	(const OrientedBox& A, const Sphere& B, const Vec3& tempMovement, const float& deltatime, Hit& hit);

#endif // COLLISION_HPP