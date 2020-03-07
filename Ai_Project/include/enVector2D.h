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
              vector.
  */
  void
  FloorSelf();
/**
* @return : a vector with all it'stateFlags values rounded
* @bugs : no known bugs
*/
  enVector2
  RoundReturn() const;
/**
* @brief : rounds the values of the current vector
* @bugs : no known bugs
*/
  void
  RoundSelf();
/**
* @brief : the distance between 2 vectors
* @bugs : no known bugs
*/
  float
  Distance(const enVector2& other) const;
/**
* @returns : the distance between 2 vectors squared
* @bugs : no known bugs
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
  getAngle();

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
  *  @brief : rotate'stateFlags the current vector by x degrees
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
  *  @brief : rotate'stateFlags the current vector by x radians
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

  /**
  *  @brief : this perform the operation on the current vector
  *  @return : the vector after the dot product operation
  *  @bug : no known bugs.
  */
  enVector2&
  operator%= (const enVector2& OtherVector);

  /*! multiples the current vector by a scalar*/
  enVector2&
  operator*= (float Scalar);

  /**
  * @brief : copy'stateFlags the values of the other vector
  * @return : the current vector ofter it copied the values of the other vector
  * @bug : no known bugs.
  */
  enVector2&
  operator=(const enVector2& OtherVector);


  /**
  *  @brief : compares the individual values of the vector to see if there the same.
  *  @bug : no known bugs.
  */
  bool
  operator==(const enVector2& OtherVector);

public: // static const vars

  /**
  *  @brief : a vector where all the values are zeros
  */
  static const enVector2 zeroVector;

  /**
  *  @brief : a vector where all the values are the maximum 
  *  permitted by the 'float' data type
  */
  static const enVector2 maxVector;

  /**
  *  @brief : a vector where all the values are the smallest positive values possible
  *  @bug : no known bugs.
  */
  static const enVector2 minVector;

  /**
  *  @brief : a vector with the most negative values possible
  *  @bug : no known bugs.
  */
  static const enVector2 lowestVector;

  /**
  *  @brief : a vector which serve as an absolute reference to where 'north' is
  *  @bug : no known bugs.
  */
  static const enVector2 northVector;

  /**
  *  @brief : a vector which serve as an absolute reference to where 'south' is
  *  @bug : no known bugs.
  */
  static const enVector2 southVector;
  
  /**
  *  @brief : a vector which serve as an absolute reference to where 'west' is
  *  @bug : no known bugs.
  */
  static const enVector2 westVector;

  /**
  *  @brief : a vector which serve as an absolute reference to where 'east' is
  *  @bug : no known bugs.
  */
  static const enVector2 eastVector;

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

  friend std::ostream& operator<<(std::ostream& Stream, const enVector2& other)
  {
    return Stream << '<' << other.X << ',' << other.Y << '>';
  }
};

//static std::ostream&
//operator<<(std::ostream& Stream, const enVector2& other)
//{
//  return Stream << '<' << other.X << ',' << other.Y << '>';
//}
//
