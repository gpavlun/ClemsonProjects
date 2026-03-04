#ifndef LINKED
#define LINKED

#define LLnode struct LinkedListNode
#define LLheader struct LinkedListHeader

LLnode{
    LLnode *next;
    LLnode *prev;
    void *data;
};
LLheader{
    LLnode *start;
    LLnode *end;
    int entrycount;
};

LLheader *LLconstruct(void);
void LLdestruct(LLheader *Header);
void LLappend(LLheader *Header, void *data);
char LLinsert(LLheader *Header, void *data, int index);
void *LLremove(LLheader *Header, int index);
int LLfind(LLheader *Header, void *data);
void LLprint(LLheader *Header);

#endif