#include "my_lib/Core/Maths/Collision.hpp"
bool IsSphereCollidingWithOrientedBox(const Sphere& A, const OrientedBox& B)
{
    //Changing the postion of the sphere position to be in OBB local coordinates to get an AABB x Sphere collision detection.
    Vec3 localSpherePosition = worldToLocal(A.position, B.position, B.I , B.J, B.K);

    if (abs(localSpherePosition.x) > ( B.width / 2 ) + A.radius || abs(localSpherePosition.y) > ( B.height / 2 ) + A.radius || abs(localSpherePosition.z) > ( B.depth / 2 ) + A.radius)
    {
        return false;
    }
    

    //Finding the closest point of the AABB to the sphere.
    float x = __max(-(B.width/2),     __min(localSpherePosition.x, B.width/2));
    float y = __max(-(B.height/2),    __min(localSpherePosition.y, B.height/2));
    float z = __max(-(B.depth/2),     __min(localSpherePosition.z, B.depth/2));

    //Then get the distance between them.
    float distance = (x - localSpherePosition.x) * (x - localSpherePosition.x) +
                        (y - localSpherePosition.y) * (y - localSpherePosition.y) +
                        (z - localSpherePosition.z) * (z - localSpherePosition.z);

    //And compare if the distance is lower than the radius to see if their are a collision.
    return distance <  (A.radius * A.radius);
}

bool IsOrientedBoxCollidingWithOrientedBox(const OrientedBox& A, const OrientedBox& B)
{
    //Get all axis needed for the 3D SAT.
    Vec3 centerDistance = B.position - A.position;

    Vec3 AXaxis = A.I * (A.width/2);
    Vec3 AYaxis = A.J * (A.height/2);
    Vec3 AZaxis = A.K * (A.depth/2);
    Vec3 BXaxis = B.I * (B.width/2);
    Vec3 BYaxis = B.J * (B.height/2);
    Vec3 BZaxis = B.K * (B.depth/2);

    Vec3 TestedAxis;

    std::vector<Vec3> Aaxis;
    Aaxis.push_back(A.I);
    Aaxis.push_back(A.J);
    Aaxis.push_back(A.K);

    std::vector<Vec3> Baxis;
    Baxis.push_back(B.I);
    Baxis.push_back(B.J);
    Baxis.push_back(B.K);

    //Looping to find a separete axis and if you dont have one, you have a collision.
    for (unsigned int index1 = 0; index1 < NB_OF_OBB_AXIS; index1++)
    {
        //test 3 axis of the OBB A referencial
        TestedAxis = Aaxis[index1];

        if (abs(DotProduct(centerDistance, TestedAxis)) > ( abs( DotProduct( AXaxis, TestedAxis)) + abs( DotProduct( AYaxis, TestedAxis)) + abs( DotProduct( AZaxis, TestedAxis)) + abs( DotProduct( BXaxis, TestedAxis)) + abs( DotProduct( BYaxis, TestedAxis)) + abs( DotProduct( BZaxis, TestedAxis)) ) )
        {
            return false;
        }

        //test 3 axis of the OBB B referencial
        TestedAxis = Baxis[index1];

        if (abs(DotProduct(centerDistance, TestedAxis)) > ( abs( DotProduct( AXaxis, TestedAxis)) + abs( DotProduct( AYaxis, TestedAxis)) + abs( DotProduct( AZaxis, TestedAxis)) + abs( DotProduct( BXaxis, TestedAxis)) + abs( DotProduct( BYaxis, TestedAxis)) + abs( DotProduct( BZaxis, TestedAxis)) ) )
        {
            return false;
        }

        //test 3*3 axis of the OBB A and B referencial cross product (for exeample Xa cross Xb) (so testing all the normals)
        for (unsigned int index2 = 0; index2 < NB_OF_OBB_AXIS; index2++)
        {
            TestedAxis = CrossProduct(Aaxis[index2], Baxis[index1]);

            if (abs(DotProduct(centerDistance, TestedAxis)) > ( abs( DotProduct( AXaxis, TestedAxis)) + abs( DotProduct( AYaxis, TestedAxis)) + abs( DotProduct( AZaxis, TestedAxis)) + abs( DotProduct( BXaxis, TestedAxis)) + abs( DotProduct( BYaxis, TestedAxis)) + abs( DotProduct( BZaxis, TestedAxis)) ) )
            {
                return false;
            }
        }
    }

    return true;
}


bool IsSegmentIntersectingPlane( const Segment& seg, const Plane& plane, Hit& hit )
{
    //if the dotProduct is equal to 0 they are orthogonal so no unique intersection
    if( DotProduct( seg.orientation, plane.normal ) == 0 )
        return false;

    //Then we find t to find the intersection point if t is on the segment (between 0 and 1)
    float t = (plane.distance - DotProduct( plane.normal, seg.start )) /
                DotProduct( plane.normal, seg.orientation );

    if( t >= -10.f && t <= 10.f )
    {
        hit.point   = seg.start + t * seg.orientation;
        hit.normal  = plane.normal;
        return true;
    }
    return false;
}



bool IsSegmentIntersectingQuad(const Segment& seg, const Quad& quad, Hit& hit)
{
    //like plane but here we check the limit of the quad with OI and OJ because a quad is a finite plane so we check if the intersection is in the quad.

    if (IsSegmentIntersectingPlane(seg, Plane(quad.position,quad.K), hit))
    {
        Vec3 localPos = worldToLocal(hit.point, quad.position, quad.I, quad.J, quad.K);

        if (localPos.x >= -quad.Ix && localPos.x <= quad.Ix && localPos.y >= -quad.Iy && localPos.y <= quad.Iy)
        {
            return true;
        }

        return false;
        
    }

    return false;
}



bool IsSegmentIntersectingSphere(const Segment& seg, const Sphere& sphere, Hit& hit)
{
    Vec3 m = seg.start - sphere.position;

    float b = DotProduct(m, seg.orientation);
    float c = DotProduct(m, m) - sphere.radius * sphere.radius;

    //Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
    if (c > 0.0f && b > 0.0f)
    {
        return false;
    }

    float discr = b*b - c;

    //A negative discriminant corresponds to seg missing sphere
    if (discr < 0.0f)
    {
        return false;
    }

    //Seg now found to intersect sphere, compute smallest t value of intersection
    float t = -b - sqrtf(discr);

    if( t >= 0.f && t <= 1.f )
    {
        hit.point = seg.start + t * seg.orientation;
        return true;
    }

    return false;

}

bool IsSegmentIntersectingInfiniteCylinder(const Segment& seg, const InfiniteCylinder& cyl, Hit& hit)
{
    //Aling cylinder to the Z-axis to simplify the detection.
    Vec3 W = CrossProduct(cyl.orientation,Vec3(0,0,1));

    Vec3 localSegPos = seg.position;

    if (W.GetMagnitude() != 0)
    {
        Vec3 K = cyl.orientation;

        Plane plane = Plane(cyl.position, cyl.orientation);

        Vec3 J = plane.GetClosestPointOnPlane(seg.position) - cyl.position;

        Vec3 I = CrossProduct(K,J);

        localSegPos = Vec3( seg.position.x * I.x + seg.position.y * I.y + seg.position.z * I.z,
		                            seg.position.x * J.x + seg.position.y * J.y + seg.position.z * J.z,
                                    seg.position.x * K.x + seg.position.y * K.y + seg.position.z * K.z);
    }

    //Compute the discriminant.
    Vec3 zero = ( localSegPos - ( seg.orientation * ( seg.length /2 ) ) );
    Vec3 one = ( localSegPos + ( seg.orientation * ( seg.length /2 ) ) );

    Vec3 temp = one - zero;

    float u = temp.x;
    float v = temp.y;
    float w = temp.z;

    float A = ( u * u + v * v );
    float B =  2 * ( u * zero.x + v * zero.y );
    float C = zero.x * zero.x + zero.y * zero.y - cyl.radius * cyl.radius;

    float delta = B * B - 4 * (A * C);

    float t1 = -1;
    float t2 = -1;

    //If delta < seg missing cylinder.
    if (delta < 0)
    {
        return false;
    }

    if (delta > 0)
    {
        t1 = ( -B - sqrtf(delta) ) / (2 * A);
        t2 = ( -B + sqrtf(delta) ) / (2 * A);
    }

    //Find t1 and t2 then finding the hit point and normal
    if ( t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0)
    {
        if ( t1 <= t2 )
        {
            hit.point = Vec3(zero.x + t1 * u, zero.y + t1 * v, zero.z + t1 * w);
            hit.normal = -1 * seg.orientation;
        }

        else
        {
            hit.point = Vec3(zero.x + t2 * u, zero.y + t2 * v, zero.z + t2 * w);
            hit.normal = -1 * seg.orientation;
        }

        return true;
    }

    else if (t1 <= 1 && t1 >= 0)
    {
        hit.point = Vec3(zero.x + t1 * u, zero.y + t1 * v, zero.z + t1 * w);
        hit.normal = -1 * seg.orientation;
        return true;
    }

    else if (t2 <= 1 && t2 >= 0)
    {
        hit.point = Vec3(zero.x + t2 * u, zero.y + t2 * v, zero.z + t2 * w);
        hit.normal = -1 * seg.orientation;
        return true;
    }

    else
    {
        return false;
    }
}

bool IsSegmentIntersectingFiniteCylinder(const Segment& seg, const FiniteCylinder& cyl, Hit& hit)
{
    //Same as infinite cylinder just add exeption with the limit of the cylinder.
    Vec3 W = CrossProduct(cyl.orientation,Vec3(0,0,1));
    Vec3 localSegPos = seg.position;

    if (W.GetMagnitude() != 0)
    {
        Vec3 K = cyl.orientation;

        Plane plane = Plane(cyl.position, cyl.orientation);

        Vec3 J = plane.GetClosestPointOnPlane(seg.position) - cyl.position;

        Vec3 I = CrossProduct(K,J);

        localSegPos = Vec3( seg.position.x * I.x + seg.position.y * I.y + seg.position.z * I.z,
		                            seg.position.x * J.x + seg.position.y * J.y + seg.position.z * J.z,
                                    seg.position.x * K.x + seg.position.y * K.y + seg.position.z * K.z);
    }

    Vec3 zero = ( localSegPos - ( seg.orientation * ( seg.length /2 ) ) );
    Vec3 one = ( localSegPos + ( seg.orientation * ( seg.length /2 ) ) );

    Vec3 temp = one - zero;

    float u = temp.x;
    float v = temp.y;
    float w = temp.z;

    float A = ( u * u + v * v );
    float B =  2 * ( u * zero.x + v * zero.y );
    float C = zero.x * zero.x + zero.y * zero.y - cyl.radius * cyl.radius;

    float delta = B * B - 4 * (A * C);

    float t1 = -1;
    float t2 = -1;

    if (delta < 0)
    {
        return false;
    }

    if (delta > 0)
    {
        t1 = ( -B - sqrtf(delta) ) / (2 * A);
        t2 = ( -B + sqrtf(delta) ) / (2 * A);
    }

    Vec3 StartCyl = ( cyl.position - ( cyl.orientation * ( cyl.length  / 2 ) ) );
    Vec3 EndCyl = ( cyl.position + ( cyl.orientation * ( cyl.length  / 2 ) ) );

    if ( t1 <= 1 && t1 >= 0 && t2 <= 1 && t2 >= 0)
    {
        if ( t1 <= t2 )
        {
            hit.point = Vec3(zero.x + t1 * u, zero.y + t1 * v, zero.z + t1 * w);

            if (hit.point.z < StartCyl.z || hit.point.z > EndCyl.z)
            {
                hit.point = Vec3(0,0,0);
                return false;
            }

            else
            {
                hit.normal = -1 * seg.orientation;
            }
        }

        else
        {
            hit.point = Vec3(zero.x + t2 * u, zero.y + t2 * v, zero.z + t2 * w);

            if (hit.point.z < StartCyl.z || hit.point.z > EndCyl.z)
            {
                hit.point = Vec3(0,0,0);
                return false;
            }

            else
            {
                hit.normal = -1 * seg.orientation;
            }
        }

        return true;
    }

    else if (t1 <= 1 && t1 >= 0)
    {
        hit.point = Vec3(zero.x + t1 * u, zero.y + t1 * v, zero.z + t1 * w);

        if (hit.point.z < StartCyl.z || hit.point.z > EndCyl.z)
        {
            hit.point = Vec3(0,0,0);
            return false;
        }

        else
        {
            hit.normal = -1 * seg.orientation;
        }

        return true;
    }

    else if (t2 <= 1 && t2 >= 0)
    {
        hit.point = Vec3(zero.x + t2 * u, zero.y + t2 * v, zero.z + t2 * w);

        if (hit.point.z < StartCyl.z || hit.point.z > EndCyl.z)
        {
            hit.point = Vec3(0,0,0);
            return false;
        }

        else
        {
            hit.normal = -1 * seg.orientation;
        }

        return true;
    }

    else
    {
        return false;
    }
}

bool IsSegmentIntersectingCapsule(const Segment& seg, const Capsule& caps, Hit& hit)
{
    //First : check the cylinder collision.
    if (IsSegmentIntersectingFiniteCylinder(seg,caps.cyl,hit))
    {
        //Then verify if the hit point is on the top or bottom of the cylinder then check for the corresponding sphere for handling two exeption.
        Vec3 StartCyl = ( caps.cyl.position - ( caps.cyl.orientation * ( caps.cyl.length  / 2 ) ) );
        Vec3 EndCyl = ( caps.cyl.position + ( caps.cyl.orientation * ( caps.cyl.length  / 2 ) ) );

        if (hit.point.z == StartCyl.z)
        {
            if (IsSegmentIntersectingSphere(seg,caps.bottomSphere,hit))
            {
                return true;
            }
        }

        else if (hit.point.z == EndCyl.z)
        {
            if (IsSegmentIntersectingSphere(seg,caps.topSphere,hit))
            {
                return true;
            }
        }

        return true;
    }
    
    //Checking if an intersection appear on the two sphere.
    else if (IsSegmentIntersectingSphere(seg,caps.bottomSphere,hit))
    {
        return true;
    }

    else if (IsSegmentIntersectingSphere(seg,caps.topSphere,hit))
    {
        return true;
    }

    //If nothing collide so obviously no collision.
    return false;
}

bool IsSegmentIntersectingAABB(const Segment& seg, const AABB& A, Hit& hit)
{
    /*Pas encore corriger mais on n'est a pas besoin de suite*/
    Vec3 centerRight    = Vec3(A.position.x + A.width/2, A.position.y, A.position.z);
    Vec3 centerLeft     = Vec3(A.position.x - A.width/2, A.position.y, A.position.z);

    Vec3 centerTop      = Vec3(A.position.x , A.position.y + A.height/2, A.position.z);
    Vec3 centerBottom   = Vec3(A.position.x , A.position.y - A.height/2, A.position.z);

    Vec3 centerFront    = Vec3(A.position.x , A.position.y, A.position.z - A.depth/2);
    Vec3 centerBack     = Vec3(A.position.x , A.position.y, A.position.z + A.depth/2);

    std::vector<Quad> quadList;

    Quad right      = Quad(centerRight  , centerBack - A.position   , centerTop - A.position    , centerRight - A.position  );
    quadList.push_back(right);
    Quad left       = Quad(centerLeft   , centerFront - A.position  , centerTop - A.position    , centerLeft - A.position   );
    quadList.push_back(left);

    Quad top        = Quad(centerTop    , centerRight - A.position  , centerBack - A.position   , centerTop - A.position    );
    quadList.push_back(top);
    Quad bottom     = Quad(centerBottom , centerRight - A.position  , centerFront - A.position  , centerBottom - A.position );
    quadList.push_back(bottom);

    Quad front      = Quad(centerFront  , centerRight - A.position  , centerTop - A.position    , centerFront - A.position  );
    quadList.push_back(front);
    Quad back       = Quad(centerBack   , centerLeft - A.position   , centerTop - A.position    , centerBack - A.position   );
    quadList.push_back(back);

    for (unsigned int i = 0; i < NB_OF_AABB_FACE; i++)
    {
        if (IsSegmentIntersectingQuad(seg,quadList[i],hit))
        {
            return true;
        }
    }

    return false;
}

bool IsSegmentIntersectingOrientedBox(const Segment& seg, const OrientedBox& A, Hit& hit)
{
    if ((A.position - seg.position).x > A.width / 2 || (A.position - seg.position).z > A.depth / 2 || (A.position - seg.position).x < -A.width / 2 || (A.position - seg.position).z < -A.depth / 2)
    {
        return false;
    }
    
    Vec3 centerRight    = A.position + A.I * (A.width / 2);
    Vec3 centerLeft     = A.position - A.I * (A.width / 2);

    Vec3 centerTop      = A.position + A.J * (A.height / 2);
    Vec3 centerBottom   = A.position - A.J * (A.height / 2);

    Vec3 centerFront    = A.position + A.K * (A.depth / 2);
    Vec3 centerBack     = A.position - A.K * (A.depth / 2);

    std::vector<Quad> quadList;

    Quad right      = Quad(centerRight  , centerBack - A.position   , centerTop - A.position    , centerRight - A.position  );
    quadList.push_back(right);
    Quad left       = Quad(centerLeft   , centerFront - A.position  , centerTop - A.position    , centerLeft - A.position   );
    quadList.push_back(left);

    Quad top        = Quad(centerTop    , centerRight - A.position  , centerBack - A.position   , centerTop - A.position    );
    quadList.push_back(top);
    Quad bottom     = Quad(centerBottom , centerRight - A.position  , centerFront - A.position  , centerBottom - A.position );
    quadList.push_back(bottom);

    Quad front      = Quad(centerFront  , centerRight - A.position  , centerTop - A.position    , centerFront - A.position  );
    quadList.push_back(front);
    Quad back       = Quad(centerBack   , centerLeft - A.position   , centerTop - A.position    , centerBack - A.position   );
    quadList.push_back(back);

    for (unsigned int i = 0; i < NB_OF_AABB_FACE; i++)
    {
        if (IsSegmentIntersectingQuad(seg,quadList[i],hit))
        {
            return true;
        }
    }

    return false;
}

bool GetFirstCollisionPointBetweenMovingSphereAndStaticBox(const OrientedBox& A, const Sphere& B, const Vec3& tempMovement, const float& deltatime, Hit& hit)
{
    Sphere tempSphere    = Sphere(B.position + tempMovement, B.radius);

    if (IsSphereCollidingWithOrientedBox(tempSphere, A))
    {
        Vec3 distance    = tempSphere.position - B.position;
        Segment path     = Segment( B.position + (distance * 0.5), distance, distance.GetMagnitude());

        float localAxmax = A.width  / 2 ;
        float localAymax = A.height / 2 ;
        float localAzmax = A.depth  / 2 ;

        float localAxmin = -1 * ( A.width  / 2 );
        float localAymin = -1 * ( A.height / 2 );
        float localAzmin = -1 * ( A.depth  / 2 );
         
        OrientedBox minkowskiBox = OrientedBox(A.position, A.I * ( ( A.width / 2 ) + B.radius ), A.J * ( ( A.height / 2 ) + B.radius ), A.K * ( ( A.depth / 2 ) + B.radius ));

        if (IsSegmentIntersectingOrientedBox(path, minkowskiBox, hit))
        {
            Vec3 localHitPos = worldToLocal(hit.point, A.position, A.I, A.J, A.K);
            if ( ( localHitPos.x <= localAxmax && localHitPos.x >= localAxmin ) || ( localHitPos.y <= localAymax && localHitPos.y >= localAymin ) || ( localHitPos.z <= localAzmax && localHitPos.z >= localAzmin ) )
            {
                return true;
            }

            else
            {
                if (localHitPos.x < localAxmin)
                {
                    if (localHitPos.y < localAymin)
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x - ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y - ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.depth), hit);
                        
                        return true;
                    }

                    else if (localHitPos.y > localAymax)
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x - ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y + ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.depth), hit);
                        
                        return true;
                    }
                    
                    else if (localHitPos.z < localAzmin)
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x - ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y,
                                            minkowskiBox.position.z - ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.height), hit);
                        
                        return true;
                    }
                    
                    else
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x - ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y,
                                            minkowskiBox.position.z + ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.height), hit);
                        
                        return true;
                    }
                    
                }

                else if (localHitPos.x > localAxmax)
                {
                    if (localHitPos.y < localAymin)
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x + ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y - ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.depth), hit);
                        
                        return true;
                    }

                    else if (localHitPos.y > localAymax)
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x + ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y + ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.depth), hit);
                        
                        return true;
                    }
                    
                    else if (localHitPos.z < localAzmin)
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x + ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y,
                                            minkowskiBox.position.z - ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.height), hit);
                        
                        return true;
                    }
                    
                    else
                    {
                        Vec3 pos = Vec3( minkowskiBox.position.x + ( ( minkowskiBox.width / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.y,
                                            minkowskiBox.position.z + ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                        IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.height), hit);
                        
                        return true;
                    }
                    
                }

                else
                {
                    if (localHitPos.z < localAzmin)
                    {
                        if (localHitPos.y < localAymin)
                        {
                            Vec3 pos = Vec3( minkowskiBox.position.x,
                                            minkowskiBox.position.y - ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z - ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                            IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.width), hit);
                        
                            return true;
                        }

                        else
                        {
                            Vec3 pos = Vec3( minkowskiBox.position.x,
                                            minkowskiBox.position.y + ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z - ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                            IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.width), hit);
                        
                            return true;
                        }
                        
                        
                    }

                    else
                    {
                        if (localHitPos.y < localAymin)
                        {
                            Vec3 pos = Vec3( minkowskiBox.position.x,
                                            minkowskiBox.position.y - ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z + ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                            IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.width), hit);
                        
                            return true;
                        }
                        
                        else
                        {
                            Vec3 pos = Vec3( minkowskiBox.position.x,
                                            minkowskiBox.position.y + ( ( minkowskiBox.height / 2 ) - ( B.radius / 2 ) ),
                                            minkowskiBox.position.z + ( ( minkowskiBox.depth / 2 ) - ( B.radius / 2 ) ) );

                            IsSegmentIntersectingCapsule(path, Capsule(pos, B.radius/2, A.width), hit);
                        
                            return true;
                        }
                    }
                    
                    
                }
                 
            }
            
            
        }

        return false;
    }
    
    return false;
}