#ifndef BLOCK_H
#define BLOCK_H

namespace MLD {
class Block
{
private:
    friend class Level;
    char m_Type;//pointless to have anything more, we won't have many block types...

public:
    Block();
    ~Block();
    void SetType(char Type) {m_Type = Type;}
    char GetType() {return m_Type;}
    bool IsActive();
};
}

#endif
