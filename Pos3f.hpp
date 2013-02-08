////////////////////////////////////////////////////////////////////////////////
/// Declaration de la structure Vector3f
////////////////////////////////////////////////////////////////////////////////

#ifndef __POS3F__
#define __POS3F__

class Pos3f
{
public:
  float x;
  float y;
  float z;
  
  Pos3f(void);
  Pos3f(float x, float y, float z);
  ~Pos3f(void);
  void		setPos(const float x, const float y, const float z);
  float		getX() const;
  float		getY() const;
  float		getZ() const;
  void setX(const float x);
  void setY(const float y);
  void setZ(const float z);
};

#endif
