#include "enVector2D.h"
#include <cmath>
#include <algorithm>

enVector2::enVector2()
  :X(0.0f), Y(0.0f)
{}

enVector2::enVector2(float x, float y)
  : X(x), Y(y)
{}


float
enVector2::DotProduct(const enVector2& OtherVector)
{
  return  (this->X * OtherVector.X) + (this->Y * OtherVector.Y);
}

float
enVector2::DotProduct(const enVector2& OtherVector) const
{
  return  (this->X * OtherVector.X) + (this->Y * OtherVector.Y);
}

float
enVector2::CrossProduct(enVector2& OtherVector)
{

  return (this->X * OtherVector.Y) - (this->Y * OtherVector.X);
}

enVector2
enVector2::Add(enVector2& OtherVector)
{
  return enVector2(this->X + OtherVector.X, this->Y + OtherVector.Y);
}

enVector2
enVector2::Subtract(const enVector2& OtherVector) const
{
  return enVector2(this->X - OtherVector.X, this->Y - OtherVector.Y);
}

enVector2
enVector2::ScalarMultiplation(float Scalar)
{
  return enVector2(this->X * Scalar, this->Y * Scalar);
}

enVector2
enVector2::NormalizeReturn() const
{
  //get current magnitude
  const float magnitude = this->Magnitude();
  enVector2 UnitVector(enVector2::zeroVector);
  if (this->X > 0 || this->X < 0)
  {
    UnitVector.X = (this->X / magnitude);
  }

  if (this->Y > 0.0f || this->Y < 0.0f)
  {
    UnitVector.Y = (this->Y / magnitude);
  }

  return UnitVector;
}


void
enVector2::NormalizeSelf()
{
  const float magnitude = this->Magnitude();
  if (this->X > 0.0f || this->X < 0.0f)
  {
    this->X = (this->X / magnitude);
  }

  if (this->Y > 0.0f || this->Y < 0.0f)
  {
    this->Y = (this->Y / magnitude);
  }

}

float
enVector2::Magnitude() const
{
  float SquaredMagnitude = (this->X * this->X) + (this->Y * this->Y);

  return sqrtf(SquaredMagnitude);
}

float
enVector2::SquaredMagnitude() const
{
  return (this->X * this->X) + (this->Y * this->Y);
}

float
enVector2::InverseSquaredRoot() const
{
  return 1.0f / SquaredMagnitude();
}

float
enVector2::Min() const
{
  return  std::min(this->X, this->Y);
}

float
enVector2::Max() const
{
  return  std::max(this->Y, this->X);
}

enVector2
enVector2::CeilReturn() const
{
  return enVector2(std::ceilf(this->X), std::ceilf(this->Y));
}

void
enVector2::CeilSelf()
{
  this->X = std::ceilf(this->X);
  this->Y = std::ceilf(this->Y);
}

enVector2 enVector2::FloorReturn() const
{
  return enVector2(std::floorf(this->X), std::floorf(this->Y));
}

void
enVector2::FloorSelf()
{
  this->X = std::floorf(this->X);
  this->Y = std::floorf(this->Y);
}

enVector2
enVector2::RoundReturn() const
{
  return enVector2(std::roundf(this->X), std::roundf(this->Y));
}

void
enVector2::RoundSelf()
{
  this->X = std::roundf(this->X);
  this->Y = std::roundf(this->Y);
}

float
enVector2::Distance(const enVector2& other) const
{
  return this->Subtract(other).Magnitude();
}

float
enVector2::DistanceSquared(const enVector2& other) const
{
  return this->Subtract(other).SquaredMagnitude();
}

enVector2
enVector2::Projection(const enVector2& other) const
{
  return other * (this->DotProduct(other) / other.SquaredMagnitude());
}

float
enVector2::Angle()
{
  return std::atan2(Y, X);
}

float
enVector2::AngleBetweenTwoVectors(enVector2& OtherVector)
{
  float Product = this->DotProduct(OtherVector);
  float ThisVectorsMagnitude = this->Magnitude();
  float OtherVectorMagnitude = OtherVector.Magnitude();

  return std::acosf(Product / (ThisVectorsMagnitude * OtherVectorMagnitude));
}

enVector2
enVector2::RotateReturnDeg(float degrees) const
{
  //converting degrees to radians 
  degrees = degrees * (3.14159f / 180.0f);

  const float TempX = std::cosf(this->X * degrees) - std::sinf(this->Y * degrees);
  const float TempY = std::sinf(this->X * degrees) + std::cosf(this->Y * degrees);

  return enVector2(TempX, TempY);
}

void
enVector2::RotateSlefDeg(float degrees)
{
  degrees = degrees * (3.14159f / 180.0f);

  float TempX = std::cosf(this->X * degrees) - std::sinf(this->Y * degrees);
  float TempY = std::sinf(this->X * degrees) + std::cosf(this->Y * degrees);

  this->X = TempX;
  this->Y = TempY;
}

enVector2
enVector2::RotateReturnRad(float radians) const
{

  float TempX = std::cosf(this->X * radians) - std::sinf(this->Y * radians);
  float TempY = std::sinf(this->X * radians) + std::cosf(this->Y * radians);

  return enVector2(TempX, TempY);
}

void
enVector2::RotateSelfRad(float radians)
{
  float TempX = std::cosf(this->X * radians) - std::sinf(this->Y * radians);
  float TempY = std::sinf(this->X * radians) + std::cosf(this->Y * radians);

  this->X = TempX;
  this->Y = TempY;
}

void
enVector2::setValues(float x, float y)
{
  this->X = x;
  this->Y = y;
}


enVector2 
enVector2::ReturnFakeParallelVector() const
{
  return enVector2(this->X,this->Y * -1);
}

enVector2
enVector2::operator+(const enVector2& OtherVector) const
{
  return enVector2(this->X + OtherVector.X, this->Y + OtherVector.Y);;
}

enVector2
enVector2::operator-(const enVector2& OtherVector) const
{
  return enVector2(this->X - OtherVector.X, this->Y - OtherVector.Y);
}

enVector2
enVector2::operator%(const enVector2& OtherVector)
{
  return enVector2(this->X * OtherVector.X, this->Y * OtherVector.Y);
}

enVector2
enVector2::operator*(float Scalar) const
{
  return enVector2((this->X * Scalar), (this->Y * Scalar));
}

enVector2&
enVector2::operator=(const enVector2& OtherVector)
{
  this->X = OtherVector.X;
  this->Y = OtherVector.Y;
  return *this;
}

bool
enVector2::operator==(const enVector2& OtherVector)
{
  if (this->X > OtherVector.X || this->X < OtherVector.X)
    return false;
  if (this->Y > OtherVector.Y || this->Y < OtherVector.Y)
    return false;

  return true;
}


enVector2&
enVector2::operator+=(const enVector2& OtherVector)
{
  this->X = this->X + OtherVector.X;
  this->Y = this->Y + OtherVector.Y;

  return *this;
}

enVector2&
enVector2::operator-=(const enVector2& OtherVector)
{
  this->X = this->X - OtherVector.X;
  this->Y = this->Y - OtherVector.Y;

  return *this;
}

enVector2&
enVector2::operator%=(const enVector2& OtherVector)
{
  this->X = this->X * OtherVector.X;
  this->Y = this->Y * OtherVector.Y;

  return *this;
}

enVector2&
enVector2::operator*=(float Scalar)
{
  this->X = this->X * Scalar;
  this->Y = this->Y * Scalar;

  return *this;
}

const enVector2 enVector2::zeroVector(0.0f, 0.0f);

const enVector2 enVector2::maxVector(FLT_MAX, FLT_MAX);

const enVector2 enVector2::minVector(FLT_MIN, FLT_MIN);

