#include "my_lib/Core/DataStructure/Graph.h"

Graph::Graph() 
{}

Graph::Graph(const Vec3& _position, const Vec3& _rotation, const Vec3& _scale)
{
  position        = _position;
  rotation        = DegreesToRadians(_rotation);
  scale           = _scale;

  worldRef        = Mat4::Identity();
  localRef        = Mat4::CreateTransformMatrix(position,rotation,scale);

  Vec4 V4Forward  = localRef * Vec4(0,0,1,0);
  Vec4 V4Right    = localRef * Vec4(1,0,0,0);
  Vec4 V4Up       = localRef * Vec4(0,1,0,0);

  forward         = Vec3(V4Forward.x, V4Forward.y, V4Forward.z);
  right           = Vec3(V4Right.x  , V4Right.y  , V4Right.z  );
  up              = Vec3(V4Up.x     , V4Up.y     , V4Up.z     );

  forward.Normalize();
  right.Normalize();
  up.Normalize();
}

Graph::~Graph()
{}