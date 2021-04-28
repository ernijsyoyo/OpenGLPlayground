#include <Mesh.h>
class PrimitiveFactory
{
private:
  /* data */
public:
  enum PrimitiveType() {
    Cube,
    Sphere,
    Plane,
    Cylinder
  }

  static Mesh* instantiate(PrimitiveType type)
  PrimitiveFactory(/* args */);
  ~PrimitiveFactory();
};

