#pragma once
#include <iostream>

/*!
\class enVector2 "enVector2.h"
\brief This class will be used for 2d vector math
NOTE : all operator with '=' alter the current vector, examples include : += -= *=

*/

class enVector2
{
public:// constructors 
  enVector2();
  enVector2(float x, float y);

  enVector2(const enVector2& other) = default;
  enVector2(enVector2&& other) = default;

  ~enVector2() = default;
public:// functions

  //! multiplying two 2D vectors give a scalar.
  float
  DotProduct(const enVector2& OtherVector);

  //! multiplying two 2D vectors give a scalar.
  float
  DotProduct(const enVector2& OtherVector) const;

  //! return the theoretical component Z axis 
  float
  CrossProduct(enVector2& OtherVector);

/**
* @brief : does the operation of adding 2 vector
* @return : A vector that the sum this vector plus the other vector
* @bug : no know bugs
*/
  enVector2
  Add(enVector2& OtherVector);

  /*! creates a new vector and can be used the tell distance*/
  enVector2
  Subtract(const enVector2& OtherVector) const;

  /*! crates a new vector */
  enVector2
  ScalarMultiplation(float Scalar);


  /**
  * @returns : a normalized version of the vector
  */
  enVector2
  NormalizeReturn() const;

  /**
  *  @brief : normalizes the vector
  */
  void 
  NormalizeSelf();

  /**
  *  @returns : how long the vector is 
  */
  float 
  Magnitude() const;

  /**
  *  @returns : how long vector is squared
  */
  float 
  SquaredMagnitude() const;
  /**
  *  @returns : 1/magnitude of the current vector
  */

  float
  InverseSquaredRoot() const;
  /**
  *  @returns : the smallest value in the vector
  */
  float
  Min()const;
  /**
  *  @returns : the biggest value in the vector
  */
  float
  Max()const;

  /**
  *  @returns : a vector after the original values
  *             had the ceiling operation performed on them (aka rounding up).
  */
  enVector2
  CeilReturn() const;
  /**
  *  @brief : performs the ceiling operation on the current
  *           vector values.
  */
  void
  CeilSelf();

  /**
  *  @returns : a vector after the original values
  *             had the flooring operation performed on them (aka rounding down).
  */
  enVector2
  FloorReturn() const;

  /**
  *  @brief : performs the flooring operation on the current
              vector values.
  */
  void
  FloorSelf();
/**
* @brief :
* @bug :
*/
  enVector2
  RoundReturn() const;
/**
* @brief :
* @bugs :
*/
  void
  RoundSelf();
/**
* @brief :
* @bugs :
*/
  float
  Distance(const enVector2& other) const;
/**
* @brief :
* @bugs :
*/
  float
  DistanceSquared(const enVector2& other) const;

  /**
  * @brief :
  */
  enVector2
  Projection(const enVector2& other) const;

  /*! used to get the angle of the current vector */
  float
  Angle();
  /**
  * @brief : calculates the angle in-between two vectors
  * 
  *https://www.softschools.com/math/pre_calculus/angle_between_two_vectors/
  */
  float
  AngleBetweenTwoVectors(enVector2& OtherVector);

  /**
  *  @returns : a rotated version of the vector
  *  @param degrees [in] the amount of degrees to rotate the vector.
  */
  enVector2
  RotateReturnDeg(float degrees) const;
  /**
  *  @brief : rotate's the current vector by x degrees
  *  @param degrees [in] the amount of degrees which the vector rotates
  */
  void
  RotateSlefDeg(float degrees);
  /**
  *  @returns : a rotated version of the vector
  */
  enVector2
  RotateReturnRad(float radians)const;

  /**
  *  @brief : rotate's the current vector by x radians
  *  @param radians [in] the amount of radians which the vector rotates
  */
  void
  RotateSelfRad(float radians); 

    /**
    * @brief : set the values associated with the vector
    * @param x : the new value for 'x' in the vector
    * @param y : the new value for 'y' in the vector
    */
  void 
  setValues(float x, float y);

  /**
  * @brief : all this does is multiply the 'y' value of the vector by -1
  */
  enVector2//parallel
  ReturnFakeParallelVector()const;

public:

  enVector2
  operator+(const enVector2& OtherVector) const;

  enVector2	
  operator-(const enVector2& OtherVector) const;
  // !the same as DotProduct

  enVector2 
  operator%(const enVector2& OtherVector);

  //! multiples the values of the current vector 
  enVector2
  operator*(float Scalar) const;

  /* alters the vector */
  enVector2&
  operator+= (const enVector2& OtherVector);

  /*!Return the Current ofter operation vector */
  enVector2&
  operator-= (const enVector2& OtherVector);

  /*!alters this vector and returns the result of multiplication */
  enVector2&
  operator%= (const enVector2& OtherVector);
  /*! multiples the current vector by a scalar*/
  enVector2&
  operator*= (float Scalar);


  enVector2&
  operator=(const enVector2& OtherVector);

  bool
  operator==(const enVector2& OtherVector);

public: // static const vars

  static const enVector2 zeroVector;

  static const enVector2 maxVector;

  static const enVector2 minVector;

public://variables 
  union
  {
    struct
    {
      float X;
      float Y;
    };
    float Array[2];
  };
};

static std::ostream&
operator<<(std::ostream& Stream, const enVector2& other)
{
  return Stream << '<' << other.X << ',' << other.Y << '>';
}

