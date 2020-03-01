#pragma once
#include <cstddef>

  /**
  * @brief : keep track of a index and increments or decrements
  *          as need be.
  * @bug :no known bugs
  */
class cIndexer
{
public:
  cIndexer();
  cIndexer(const cIndexer & other) = default;
  cIndexer(cIndexer && other) = default;
  ~cIndexer() = default;
public: 
  /**
  * @brief : increments the index by some amount.
  * @return : the index after the increment.
  * @bug : no known bugs.
  */
 size_t 
 operator+=(size_t Num);

  /**
  * @brief : decrement the index by some amount.
  * @return : the index after the decrement .
  * @bug : no known bugs.
  */
 size_t 
 operator-=(size_t Num);

  /**
  * @brief : increments the index by one
  * @returns : the value of the index AFTER the increment.
  * @bug : no known bugs.
  */
 size_t 
 operator++();

  /**
  * @brief : increments the index by one
  * @returns : the value of the index AFTER the increment.
  * @bug : no known bugs.
  */
 size_t 
 operator--();

  /**
  * @brief : set the value of the index
  * @returns : the value of the new index.
  * @bug : no known bugs.
  */
 size_t 
 operator=(size_t newIndex);

public:

  /**
  * @brief : reset the index to some value when and if the index 
  *         reaches some maximum value.
  * @param[in] maxValue : the value which when the index reaches-it
  *  the index will reset to some other value (more than likely zero)
  * 
  * @param[in] resetValue : the value which the index will reset to.
  *          
  * @returns : true if the index was reset.
  * @bug : no known bugs.
  */
  bool
  resetIfIndexEqualsMax(const size_t maxValue,
                        const size_t resetValue = 0u);
  /**
  * @brief : increments the index 
  * @bug :
  */
  size_t
  incrementIndex(size_t amount = 1u);


  size_t 
  incrementByIncrementAmount();

  /**
  * @returns : the current index.
  */
  size_t
  getIndex()const;

  /**
  * @brief : set the current index.
  */
 void
 setIndex(size_t newIndex);

 void 
 setIncrementAmount(int incrementAmount);

 size_t m_index = 0u;
 int m_IncrementAmount = 1;
};

