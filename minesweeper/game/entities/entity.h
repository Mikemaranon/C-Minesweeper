#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    ENTITY_EMPTY,
    ENTITY_BOMB,
    ENTITY_FLAG
} EntityType;

typedef struct {
    EntityType type;
    int focused;        // 0 = not focused, 1 = focused
    int revealed;       // 0 = hidden, 1 = revealed
    int adjacentBombs;  // Number of adjacent bombs
} Entity;

#endif
