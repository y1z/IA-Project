#include "enNode.h"

enNode::enNode()
:m_position(enVector2::zeroVector),
m_radius(100.0f),
is_visited(false)
{}

enNode::enNode(const enVector2 & position, float radius)
:m_position(position),
m_radius(radius),
is_visited(false)
{}
