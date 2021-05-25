#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED


struct entity
{
    struct entity* cordSystem;
    float x,y,z;
    float xAlfa, yAlfa, zAlfa;
    unsigned char type;
    void (*drawFunc);
    void (*updateFunc);
    void (*heap);
};

#endif // ENTITY_H_INCLUDED
