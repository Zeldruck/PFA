#ifndef _SEGMENT_HPP_
#define _SEGMENT_HPP_
#include "Vec3.h"

class Segment
{
public :
  inline Segment( Vec3, Vec3, float );
  inline ~Segment();
  Vec3 position, orientation , start, end;
  float length;
};

inline Segment::Segment( Vec3 _position, Vec3 _orientation, float _length )
: length {_length}
{
  position =  _position;
  orientation = _orientation;

  orientation.Normalize();

  if (_length == 0)
  {
    start = position;
    end   = position;
  }
  
  else
  {
    start = ( position - ( orientation * ( length / 2 ) ) );
    end = ( position + ( orientation * ( length / 2 ) ) );
  }
}

inline float DistanceFromPointToSegment( Vec3 point, Segment segment )
{
  Vec3 AB = segment.end - segment.start,
       AC = point - segment.start,
       BC = point - segment.end;
  float e = DotProduct( AC, AB ); //projecting our point on the segment

// cases where the point is projecte outside of the segment
  if ( e <= 0.f )
    return DotProduct( AC, AC );

  float sqNorm = DotProduct( AB, AB );
  if( e >= sqNorm)
    return DotProduct( BC, BC );

// case where the point is projected on the Segment
  return sqrtf( DotProduct(AC, AC) - e * e / sqNorm );
}

inline Segment::~Segment()
{}

#endif
