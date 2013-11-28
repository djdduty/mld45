#include <Level/Block.h>
#include <Level/Level.h>

namespace MLD {
Block::Block()
{
    m_Type = Level::BLOCK_TYPE_INACTIVE;
}

Block::~Block()
{

}

bool Block::IsActive()
{
    return m_Type != Level::BLOCK_TYPE_INACTIVE;
}
}
