#include "enPathNode.H"

enPathNode::enPathNode()
:m_position(enVector2::zeroVector),
m_radius(100.0f),
is_visited(false)
{}

enPathNode::enPathNode(const enVector2 & position, float radius)
:m_position(position),
m_radius(radius),
is_visited(false)
{}
