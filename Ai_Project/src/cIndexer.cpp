#include "..\include\cIndexer.h"

cIndexer::cIndexer()
  :m_index(0u)
{}

size_t
cIndexer::operator+=(size_t Num)
{
  return (m_index += Num);
}

size_t
cIndexer::operator-=(size_t Num)
{
  return  m_index -= Num;
}

size_t
cIndexer::operator++()
{
  return ++m_index;
}

size_t
cIndexer::operator--()
{
  return --m_index;
}

size_t
cIndexer::operator=(size_t newIndex)
{
  return m_index = newIndex;
}

bool 
cIndexer::resetIfIndexEqualsMax(const size_t maxValue, const size_t resetValue)
{
  if( m_index >= maxValue )
  {
    m_index = resetValue;
    return true;
  }

  return false;
}

size_t 
cIndexer::incrementIndex(size_t amount)
{
  return (m_index += amount);
}

size_t 
cIndexer::incrementByIncrementAmount()
{
  m_index += m_IncrementAmount;
  return m_index;
}

size_t 
cIndexer::getIndex() const
{
  return m_index;
}

void
cIndexer::setIndex(size_t newIndex)
{
  m_index = newIndex;
}

void 
cIndexer::setIncrementAmount(int newIncrementAmount)
{
  m_IncrementAmount = newIncrementAmount;
}
