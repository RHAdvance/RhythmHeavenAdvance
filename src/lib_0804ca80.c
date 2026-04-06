#include "lib_0804ca80.h"

asm(".include \"include/gba.inc\"");//Temporary

static u8 D_03004428;
static void *(*sSpriteMemAlloc)(u32);
static void  (*sSpriteMemDealloc)(void *);
static void *(*sSpriteMemAllocId)(u32, u32);

// Set Functions for Memory Allocation & Deallocation
void sprite_lib_set_mem_alloc(void *memAllocFunc, void *memDeallocFunc) {
    sSpriteMemAlloc = memAllocFunc;
    sSpriteMemDealloc = memDeallocFunc;
}


// Set Function for Memory Allocation by ID
void sprite_lib_set_mem_alloc_id(void *memAllocIdFunc) {
    sSpriteMemAllocId = memAllocIdFunc;
}


// Create Sprite Handler
struct SpriteHandler *sprite_handler_create(u16 objAmount, void *objBuffer, u16 spriteAmount, u32 memID) {
    struct SpriteHandler *handler;
    struct Sprite *sprites;
    u32 spritesSize;
    u32 i;
    u32 *buf;

    if (memID != 0) {
        handler = sSpriteMemAllocId(memID, sizeof(struct SpriteHandler));
    } else {
        handler = sSpriteMemAlloc(sizeof(struct SpriteHandler));
    }

    handler->objAmount = objAmount;
    handler->oamBuffer = objBuffer;

    buf = objBuffer;
    for (i = 0; i < (objAmount / 8); i++) {
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = 0x22222222;
        buf += 8;
    }
    for (i = 0; i < (objAmount % 8); i++) { // Fill the remainder
        buf[i] = 0x22222222;
    }

    handler->spriteAmount = spriteAmount;
    spritesSize = spriteAmount * sizeof(struct Sprite);

    if (memID != 0) {
        sprites = sSpriteMemAllocId(memID, spritesSize);
    } else {
        sprites = sSpriteMemAlloc(spritesSize);
    }

    handler->sprites = sprites;
    sprite_handler_reset(handler);
    return handler;
}


// Delete Sprite Handler
void sprite_handler_delete(struct SpriteHandler *handler) {
    sSpriteMemDealloc(handler->sprites);
    sSpriteMemDealloc(handler);
}


// Set OAM Buffer
void sprite_handler_set_obj_buffer(struct SpriteHandler *handler, u16 bufferSize, u32 *buffer) {
    handler->objAmount = bufferSize;
    handler->oamBuffer = buffer;
}


// Render Sprite Cel
u32 func_0804cb88(struct struct_0804cb88 *drawData) {
    u32 (*drawFunc)(struct struct_0804cb88 *);
    u32 i;

    drawData->objTotal = drawData->src[0];
    if (drawData->objTotal == 0) {
       return 0;
    }

    drawData->src++;
    drawData->objCount = 0;
    if (drawData->srcInc < 0) {
        drawData->src += ((drawData->objTotal - 1) * 3);
    }

    drawFunc = func_0804e418;
    return drawFunc(drawData);
}


// Reset Sprite Handler
void sprite_handler_reset(struct SpriteHandler *handler) {
    struct Sprite *sprites;
    u32 spriteAmount;
    u32 i;

    spriteAmount = handler->spriteAmount;
    sprites = handler->sprites;

    for (i = 0; i < spriteAmount; i++) {
        sprites[i].visible = FALSE;
        sprites[i].allocated = FALSE;
    }
    handler->zLinkEnd = -1;
    handler->zLinkStart = -1;

    sprites[0].zLinkPrev = -1;
    sprites[0].zLinkNext = 1;
    for (i = 1; i < spriteAmount - 1; i++) {
        sprites[i].zLinkPrev = i - 1;
        sprites[i].zLinkNext = i + 1;
    }
    sprites[i].zLinkPrev = i - 1;
    sprites[i].zLinkNext = -1;

    handler->nextAllocID = 0;
    handler->lastAllocID = i;
    handler->paused = FALSE;
    handler->xPos = 0;
    handler->yPos = 0;
    handler->totalCycles = 0;
    handler->memID = 0;
    handler->unk1E = 255;
    handler->unk22_b0 = 0;
}


// Return TRUE if Sprite is Invalid
u32 sprite_is_invalid(struct SpriteHandler *handler, s16 id) {
    // Standard invalid index.
    if (id == -1) {
        return TRUE;
    }

    // Other invalid index.
    if (id < 0) {
        if (handler->unk22_b0 == 0) {
            handler->unk22_b0 = 1;
            handler->unk24 = handler->memID;
            handler->unk26 = D_03004428;
        }
        return TRUE;
    }

    // Index exceeds the maximum.
    if (id >= handler->spriteAmount) {
        if (handler->unk22_b0 == 0) {
            handler->unk22_b0 = 1;
            handler->unk24 = handler->memID;
            handler->unk26 = D_03004428;
        }
        return TRUE;
    }

    // Sprite doesn't exist.
    if (!handler->sprites[id].allocated) {
        if (handler->unk22_b0 == 0) {
            handler->unk22_b0 = 2;
            handler->unk24 = handler->memID;
            handler->unk26 = D_03004428;
        }
        return TRUE;
    }

    // Sprite is valid.
    return FALSE;
}


// Set Current Animation Cel (Internal)
void sprite_update_anim_cel(struct SpriteHandler *handler, s16 id, s8 nextCel, u32 resetDuration) {
    struct Sprite *sprite;
    u32 celIsOutOfBounds, updateCel;
    s8 cel, celTotal, loopCel;

    cel = nextCel;
    D_03004428 = SPRITE_OPERATION_SET_ANIM_CEL;

    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    if (resetDuration) {
        sprite->currentCelTime = 0;
    }

    celTotal = sprite->celTotal;
    loopCel = sprite->loopCel;
    if (loopCel >= celTotal) {
        loopCel = celTotal - 1;
    }
    if (loopCel < 0) {
        loopCel = 0;
    }

    celIsOutOfBounds = (cel < 0 || cel >= celTotal);
    if (celIsOutOfBounds) {
        switch (sprite->playbackType) {
            // Jump to the loop start position.
            case SPRITE_PLAYBACK_NORMAL_LOOP:
                cel = loopCel;
                updateCel = TRUE;
                break;

            // Jump to the loop start position and hide the sprite.
            case SPRITE_PLAYBACK_NORMAL_HIDE:
                cel = loopCel;
                updateCel = TRUE;
                sprite->visible = FALSE;
                break;

            // Jump to the loop start position OR run the callback function if present.
            case SPRITE_PLAYBACK_NORMAL_CALLBACK:
                cel = loopCel;
                if (sprite->callbackFunc) {
                    updateCel = FALSE;
                    sprite->currentCelTime += INT_TO_FIXED(sprite->animation[cel].duration);
                    sprite->currentCel = cel;
                    sprite->callbackFunc(handler, id, sprite->callbackArg);
                } else {
                    updateCel = TRUE;
                }
                break;

            // Seemingly alternates between playing forwards and backwards.
            case SPRITE_PLAYBACK_ALTERNATING_LOOP:
                if (cel < 1) {              // If the cel is at or before the first,
                    cel = -cel;             // invert it
                    if (cel >= celTotal) {  // and clamp.
                        cel = celTotal - 1;
                    }
                } else {            // Else ???
                    cel = (celTotal - 3) - (cel - celTotal);
                    if (cel < 0) {  // and clamp.
                        cel = 0;
                    }
                }
                sprite->celInc = -sprite->celInc;
                updateCel = TRUE;
                break;

            // Delete the sprite.
            case SPRITE_PLAYBACK_NORMAL_DELETE:
                updateCel = FALSE;
                sprite_delete(handler, id);
                break;
        }
    } else {
        updateCel = TRUE;
    }

    if (updateCel) {
        sprite->currentCelTime += INT_TO_FIXED(sprite->animation[cel].duration);
        sprite->currentCel = cel;
        if (sprite->callbackFunc) {
            if (cel == sprite->callbackCel) {
                sprite->callbackFunc(handler, id, sprite->callbackArg);
            }
            if (sprite->callbackCel == -2) {
                sprite->callbackFunc(handler, id, sprite->callbackArg, cel);
            }
        }
    }
}


// Set Current Animation Cel
void sprite_set_anim_cel(struct SpriteHandler *handler, s16 id, s8 cel) {
    sprite_update_anim_cel(handler, id, cel, TRUE);
}


// Set Current Animation Cel by Position Relative to Duration
    // 'progress' is a Q0.8 fixed-point value denoting the position within
    // the animation as a proportion of the combined duration of all cels.
void sprite_set_anim_progress(struct SpriteHandler *handler, s16 id, u8 progress) {
    struct Sprite *sprite;
    struct Animation *anim;
    u24_8 targetTime, totalTime;
    s8 cel;

    D_03004428 = SPRITE_OPERATION_SET_ANIM_PROGRESS;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    targetTime = FIXED_POINT_MUL(sprite->totalDuration, progress);
    anim = sprite->animation;
    cel = 0;
    totalTime = 0;

    do {
        totalTime += anim->duration;
        if (targetTime < totalTime) {
            sprite_set_anim_cel(handler, id, cel);
            return;
        }

        anim++;
        cel++;
    } while (anim->cel != NULL);
}


// Update Z Depth
void sprite_update_z_link(struct SpriteHandler *handler, s16 id) {
    struct Sprite *sprites = handler->sprites;
    s16 start = handler->zLinkStart;
    s16 end = handler->zLinkEnd;
    u16 zDepth = sprites[id].zDepth;
    s16 prev = handler->zLinkEnd;
    s16 next;

    while ((prev != -1) && (zDepth < sprites[prev].zDepth)) {
        prev = sprites[prev].zLinkPrev;
    }

    if (prev >= 0) {
        next = sprites[prev].zLinkNext;
        sprites[prev].zLinkNext = id;
        sprites[id].zLinkPrev = prev;
        sprites[id].zLinkNext = next;
        if (next >= 0) {
            sprites[next].zLinkPrev = id;
        }
    } else {
        prev = start;
        if (prev >= 0) {
            sprites[prev].zLinkPrev = id;
            sprites[id].zLinkNext = prev;
        } else {
            sprites[id].zLinkNext = -1;
        }
        sprites[id].zLinkPrev = -1;
    }

    if (sprites[id].zLinkPrev == -1) {
        do { start = id; } while (0);
    }
    if (sprites[id].zLinkNext == -1) {
        end = id;
    }

    handler->zLinkStart = start;
    handler->zLinkEnd = end;
}


// Unlink Sprite
void sprite_remove_z_link(struct SpriteHandler *handler, s16 id) {
    struct Sprite *sprites = handler->sprites;
    s16 next = sprites[id].zLinkNext;
    s16 prev = sprites[id].zLinkPrev;

    if (prev >= 0) {
        sprites[prev].zLinkNext = next;
    } else {
        handler->zLinkStart = next;
    }

    if (next >= 0) {
        sprites[next].zLinkPrev = prev;
    } else {
        handler->zLinkEnd = prev;
    }
}


// Allocate Next Free ID
s16 sprite_handler_alloc_id(struct SpriteHandler *handler) {
    s16 id = handler->nextAllocID;

    if (id >= 0) {
        handler->nextAllocID = handler->sprites[id].zLinkNext;
        if (handler->nextAllocID < 0) {
            handler->lastAllocID = -1;
        }
    }

    return id;
}


// Deallocate Sprite ID
void sprite_handler_dealloc_id(struct SpriteHandler *handler, s16 id) {
    if (id >= 0) {
        if (handler->lastAllocID >= 0) {
            handler->sprites[handler->lastAllocID].zLinkNext = id;
        } else {
            handler->nextAllocID = id;
        }

        handler->sprites[id].zLinkNext = -1;
        handler->lastAllocID = id;
    }
}


// Get Total Animation Cels
u8 sprite_anim_get_cel_total(struct Animation *anim) {
    u8 n = 0;

    while (anim[n].cel != NULL) {
        n++;
    }

    return n;
}


// Get Total Duration of Animation (in Frames)
u16 sprite_get_anim_duration(struct Animation *anim) {
    u16 len = 0;

    while (anim->cel != NULL) {
        len += anim->duration;
        anim++;
    }

    return len;
}


// Create New Sprite
s16 sprite_create(struct SpriteHandler *handler, struct Animation *anim, s8 startCel, s16 x, s16 y, u16 z,
                                            s8 animDirection, s8 loopCel, u16 loopType) {
    struct Sprite *sprite;
    s16 id = sprite_handler_alloc_id(handler);

    if (id < 0) {
        return -1;
    }

    sprite = &handler->sprites[id];
    sprite->allocated = TRUE;
    sprite->animation = anim;
    sprite->celInc = animDirection;
    sprite->loopCel = loopCel;
    sprite->xPos = x;
    sprite->yPos = y;
    sprite->zDepth = z;
    sprite->celTotal = sprite_anim_get_cel_total(anim);
    sprite->playbackType = loopType & 0xFF;
    sprite->oamAttributes = 0;
    sprite->baseTile = 0;
    sprite->basePalette = 0;
    sprite->callbackCel = -1;
    sprite->update = FALSE;
    sprite->paused = FALSE;
    sprite->callbackFunc = NULL;
    sprite->totalDuration = sprite_get_anim_duration(anim);
    sprite->yOrigin = &D_08bd0cac;
    sprite->xOrigin = &D_08bd0cac;
    sprite->memID = handler->memID;
    sprite->animationSpeed = INT_TO_FIXED(1.0);
    sprite_update_z_link(handler, id);
    sprite_set_anim_cel(handler, id, startCel);
    sprite->visible = ((loopType & 0x8000) == 0);

    return id;
}


// Create New Sprite (w/ Attributes)
s16 sprite_create_w_attr(struct SpriteHandler *handler, struct Animation *anim, s8 startCel, s16 x, s16 y, u16 z,
                                                s8 animDirection, s8 loopCel, u16 loopType, u32 attrs) {
    struct Sprite *sprite;
    s16 id = sprite_handler_alloc_id(handler);

    if (id < 0) {
        return -1;
    }

    sprite = &handler->sprites[id];
    sprite->allocated = TRUE;
    sprite->animation = anim;
    sprite->celInc = animDirection;
    sprite->loopCel = loopCel;
    sprite->xPos = x;
    sprite->yPos = y;
    sprite->zDepth = z;
    sprite->celTotal = sprite_anim_get_cel_total(anim);
    sprite->playbackType = loopType & 0xFF;
    sprite->oamAttributes = attrs;
    sprite->baseTile = 0;
    sprite->basePalette = 0;
    sprite->callbackCel = -1;
    sprite->update = FALSE;
    sprite->paused = FALSE;
    sprite->callbackFunc = NULL;
    sprite->totalDuration = sprite_get_anim_duration(anim);
    sprite->yOrigin = &D_08bd0cac;
    sprite->xOrigin = &D_08bd0cac;
    sprite->memID = handler->memID;
    sprite->animationSpeed = INT_TO_FIXED(1.0);
    sprite_update_z_link(handler, id);
    sprite_set_anim_cel(handler, id, startCel);
    sprite->visible = ((loopType & 0x8000) == 0);

    return id;
}


// Duplicate Sprite
s16 sprite_clone(struct SpriteHandler *handler, s16 id) {
    struct Sprite *srcSprite, *destSprite;
    s16 destID;

    D_03004428 = SPRITE_OPERATION_CLONE;
    if (sprite_is_invalid(handler, id)) {
        return -1;
    }

    destID = sprite_handler_alloc_id(handler);
    if (destID < 0) {
        return -1;
    }

    destSprite = &handler->sprites[destID];
    srcSprite = &handler->sprites[id];
    DmaCopy32(3, srcSprite, destSprite, sizeof(struct Sprite));
    destSprite->memID = handler->memID;
    destSprite->zLinkPrev = id;
    destSprite->zLinkNext = srcSprite->zLinkNext;
    srcSprite->zLinkNext = destID;

    if (destSprite->zLinkNext == -1) {
        handler->zLinkEnd = destID;
    } else {
        handler->sprites[destSprite->zLinkNext].zLinkPrev = destID;
    }

    return destID;
}


// Copy Data to Sprite
void sprite_copy(struct SpriteHandler *handler, s16 id, s16 srcID) {
    u8 *src, *dest;
    u16 memID;
    s16 i;

    D_03004428 = SPRITE_OPERATION_COPY;
    if (sprite_is_invalid(handler, id) || sprite_is_invalid(handler, srcID)) {
        return;
    }

    memID = handler->sprites[id].memID;
    sprite_remove_z_link(handler, id);

    dest = (u8 *)&handler->sprites[id];
    src = (u8 *)&handler->sprites[srcID];
    for (i = 0; i < sizeof(struct Sprite); i++) {
        *dest++ = *src++;
    }

    sprite_update_z_link(handler, id);
    handler->sprites[id].memID = memID;
}


// Stop and Deallocate Sprite
void sprite_delete(struct SpriteHandler *handler, s16 id) {
    D_03004428 = SPRITE_OPERATION_DELETE;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].visible = FALSE;
    handler->sprites[id].allocated = FALSE;
    sprite_remove_z_link(handler, id);
    sprite_handler_dealloc_id(handler, id);
}


// Set X,Y Position and Z-Depth (Layer)
void sprite_set_x_y_z(struct SpriteHandler *handler, s16 id, s16 x, s16 y, u16 z) {
    D_03004428 = SPRITE_OPERATION_SET_XYZ;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].xPos = x;
    handler->sprites[id].yPos = y;
    if (handler->sprites[id].zDepth != z) {
        sprite_remove_z_link(handler, id);
        handler->sprites[id].zDepth = z;
        sprite_update_z_link(handler, id);
    }
}


// Set X,Y Position
void sprite_set_x_y(struct SpriteHandler *handler, s16 id, s16 x, s16 y) {
    D_03004428 = SPRITE_OPERATION_SET_XY;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].xPos = x;
    handler->sprites[id].yPos = y;
}


// Set X Position
void sprite_set_x(struct SpriteHandler *handler, s16 id, s16 x) {
    D_03004428 = SPRITE_OPERATION_SET_X;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].xPos = x;
}


// Set Y Position
void sprite_set_y(struct SpriteHandler *handler, s16 id, s16 y) {
    D_03004428 = SPRITE_OPERATION_SET_Y;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].yPos = y;
}


// Set Z-Depth (Layer)
void sprite_set_z(struct SpriteHandler *handler, s16 id, u16 z) {
    D_03004428 = SPRITE_OPERATION_SET_Z;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    if (handler->sprites[id].zDepth != z) {
        sprite_remove_z_link(handler, id);
        handler->sprites[id].zDepth = z;
        sprite_update_z_link(handler, id);
    }
}


// Get Current Animation Cel
s8 sprite_get_anim_cel(struct SpriteHandler *handler, s16 id) {
    D_03004428 = SPRITE_OPERATION_GET_ANIM_CEL;
    if (sprite_is_invalid(handler, id)) {
        return -1;
    }

    return handler->sprites[id].currentCel;
}


// Get Animation Progress
    // Returns a Q0.8 fixed-point value denoting the position within
    // the animation as a proportion of the combined duration of all cels.
u8 sprite_get_anim_progress(struct SpriteHandler *handler, s16 id) {
    struct Sprite *sprite;
    struct Animation *anim;
    u32 totalTime;
    u32 i;

    D_03004428 = SPRITE_OPERATION_GET_ANIM_PROGRESS;
    if (sprite_is_invalid(handler, id)) {
        return 0;
    }

    sprite = &handler->sprites[id];
    anim = sprite->animation;
    totalTime = 0;
    for (i = 0; i < sprite->currentCel; i++) {
        totalTime += anim->duration;
        anim++;
    }

    // Include the time that has passed for the current cel.
    totalTime += (anim->duration - (s8)FIXED_TO_INT(sprite->currentCelTime));
    // Express as a proportion of the total animation duration.
    return (u32)INT_TO_FIXED(totalTime) / sprite->totalDuration;
}


// Set Sprite Visibility
void sprite_set_visible(struct SpriteHandler *handler, s16 id, u16 isVisible) {
    D_03004428 = SPRITE_OPERATION_SET_VISIBLE;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].visible = isVisible;
}


// Set Attributes
void sprite_attr_set(struct SpriteHandler *handler, s16 id, u32 attr) {
    D_03004428 = SPRITE_OPERATION_SET_ATTR;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].oamAttributes = attr;
}


// OR Attributes
void sprite_attr_orr(struct SpriteHandler *handler, s16 id, u32 attr) {
    D_03004428 = SPRITE_OPERATION_ORR_ATTR;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].oamAttributes |= attr;
}


// AND Attributes
void sprite_attr_and(struct SpriteHandler *handler, s16 id, u32 attr) {
    D_03004428 = SPRITE_OPERATION_AND_ATTR;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].oamAttributes &= attr;
}


// Bit-Clear Attributes
void sprite_attr_bic(struct SpriteHandler *handler, s16 id, u32 attr) {
    D_03004428 = SPRITE_OPERATION_BIC_ATTR;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].oamAttributes &= ~attr;
}


// Set Base Tile Offset
void sprite_set_base_tile(struct SpriteHandler *handler, s16 id, s16 baseTile) {
    D_03004428 = SPRITE_OPERATION_SET_BASE_TILE;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].baseTile = baseTile;
}


// Set Base Palette Offset
void sprite_set_base_palette(struct SpriteHandler *handler, s16 id, s8 basePalette) {
    D_03004428 = SPRITE_OPERATION_SET_BASE_PALETTE;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].basePalette = basePalette;
}


// Set Animation
void sprite_set_anim(struct SpriteHandler *handler, s16 id, struct Animation *anim,
                                s8 startCel, s8 direction, s8 loopCel, u16 playbackType) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_ANIM;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    sprite->celTotal = sprite_anim_get_cel_total(anim);
    sprite->animation = anim;
    sprite->totalDuration = sprite_get_anim_duration(anim);

    if (startCel >= 0) {
        sprite->celInc = direction;
        sprite->loopCel = loopCel;
        sprite->playbackType = playbackType;
        sprite_set_anim_cel(handler, id, startCel);
    }
}


// Set Animation from Struct
void sprite_set_anim_data(struct SpriteHandler *handler, s16 id, struct SpritePlaybackData *data) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_ANIM;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    sprite->celTotal = sprite_anim_get_cel_total(data->anim);
    sprite->animation = data->anim;
    sprite->totalDuration = sprite_get_anim_duration(data->anim);

    if (data->startCel >= 0) {
        sprite->celInc = data->direction;
        sprite->loopCel = data->loopCel;
        sprite_set_anim_cel(handler, id, data->startCel);
    }
}


// Set Update Flag
void sprite_set_enable_updates(struct SpriteHandler *handler, s16 id, u16 canUpdate) {
    D_03004428 = SPRITE_OPERATION_SET_ENABLE_UPDATES;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].update = canUpdate;
}


// Set Pause Flag
void sprite_set_paused(struct SpriteHandler *handler, s16 id, u16 isPaused) {
    D_03004428 = SPRITE_OPERATION_SET_PAUSED;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].paused = isPaused;
}


// Set Callback
void sprite_set_callback(struct SpriteHandler *handler, s16 id, void *func, u32 arg) {
    D_03004428 = SPRITE_OPERATION_SET_CALLBACK;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    handler->sprites[id].callbackFunc = func;
    handler->sprites[id].callbackArg = arg;
}


// Set Playback Data
void sprite_set_playback(struct SpriteHandler *handler, s16 id, s8 direction, s8 loopCel, u16 playbackType) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_PLAYBACK;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    sprite->celInc = direction;
    sprite->loopCel = loopCel;
    sprite->playbackType = playbackType & 0xFF;
}


// Set World Origin X,Y Position
void sprite_set_origin_x_y(struct SpriteHandler *handler, s16 id, s16 *xOrigin, s16 *yOrigin) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_ORIGIN;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    sprite->xOrigin = (xOrigin != NULL) ? xOrigin : &D_08bd0cac;
    sprite->yOrigin = (yOrigin != NULL) ? yOrigin : &D_08bd0cac;
}


// Set World Origin X Position
void sprite_set_origin_x(struct SpriteHandler *handler, s16 id, s16 *xOrigin) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_ORIGIN;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    sprite->xOrigin = (xOrigin != NULL) ? xOrigin : &D_08bd0cac;
}


// Set World Origin Y Position
void sprite_set_origin_y(struct SpriteHandler *handler, s16 id, s16 *yOrigin) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_ORIGIN;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    sprite->yOrigin = (yOrigin != NULL) ? yOrigin : &D_08bd0cac;
}


// Set Affine
void sprite_set_affine_params(struct SpriteHandler *handler, s16 id, s32 affineIndex, s16 *affineParams) {
    struct Sprite *sprite;

    D_03004428 = SPRITE_OPERATION_SET_AFFINE;
    if (sprite_is_invalid(handler, id)) {
        return;
    }

    sprite = &handler->sprites[id];
    if (affineIndex >= 0) {
        sprite->affineParams = affineParams;
        sprite->oamAttributes &= ~0x02000000; // Clear affine flag.
        sprite->oamAttributes &= ~0x00003E00; // Clear affine param index.
        sprite->oamAttributes &= ~(2 | 1);
        sprite->oamAttributes |= 0x2000000; // Affine flag.
        sprite->oamAttributes |= affineIndex << 9; // Affine param index.
        sprite->oamAttributes |= (2 | 1); // Affine | Double-Size flag.
    } else {
        sprite->oamAttributes &= ~0x02000000;
        sprite->oamAttributes &= ~0x00003E00;
        sprite->oamAttributes &= ~(2 | 1);
    }
}


// Set Affine & Double Size Flags
void func_0804dc8c(struct SpriteHandler *handler, s16 id, u32 args) {
    struct Sprite *sprite;

    if (id >= 0) {
        sprite = &handler->sprites[id];
        sprite->oamAttributes &= ~(2 | 1);
        sprite->oamAttributes |= args;
    }
}


// Set Animation Speed
void sprite_set_anim_speed(struct SpriteHandler *handler, s16 id, u8_8 speed) {
    struct Sprite *sprite;

    if (id >= 0) {
        sprite = &handler->sprites[id];
        sprite->animationSpeed = speed;
    }
}


#define AS_OAM(data) ((struct OAM *)data)

// Get Sprite Dimensions (!TODO - see if there's any way to write this better)
u32 sprite_get_cel_dimensions(u16 *cel, u32 requestedDataType) {
    s32 zero;
    s32 bottomEdge, topEdge, rightEdge, leftEdge;
    s32 total, i;
    u8 *objSizes;
    struct OamDimensions *dimensions;
    s32 x, y;

    zero = 0;
    bottomEdge = 0;
    topEdge = 0;
    rightEdge = 0;
    leftEdge = 0;
    total = *cel++;

    if (zero < total) {
        objSizes = (u8 *)&D_08bd0cae;
        i = total;
        do {
            // Get the X and Y, clamp them
            x = AS_OAM(cel)->xPos;
            if (x > 255) {
                x -= 512;
            }
            y = AS_OAM(cel)->yPos;
            if (y > 127) {
                y -= 256;
            }
            // Get the dimensions
            // D_08bd0cae[AS_OAM(cel)->shape][AS_OAM(cel)->size];
            dimensions = (struct OamDimensions *)&objSizes[(AS_OAM(cel)->objShape * 8) + (AS_OAM(cel)->objSize * 2)];
            
            // Calculate edges
            if (x < leftEdge) {
                leftEdge = x;
            }
            if (x + dimensions->width > rightEdge) { 
                rightEdge = x + dimensions->width;
            }
            if (y < topEdge) {
                topEdge = y;
            }
            (s32)dimensions = y + dimensions->height; // ???????????
            if ((s32)dimensions > bottomEdge) {
                bottomEdge = (s32)dimensions;
            }
        
            cel += 3;
            i--;
        } while (i != 0);
    }

    switch (requestedDataType) {
        case SPRITE_DIMENSION_LEFT:
            return leftEdge;
        case SPRITE_DIMENSION_RIGHT:
            return rightEdge;
        case SPRITE_DIMENSION_TOP:
            return topEdge;
        case SPRITE_DIMENSION_BOTTOM:
            return bottomEdge;
        case SPRITE_DIMENSION_WIDTH:
            return rightEdge - leftEdge;
        case SPRITE_DIMENSION_HEIGHT:
            return bottomEdge - topEdge;
        default:
            return 0;
    }
}

#undef AS_OAM


// Get Sprite Data
s32 sprite_get_data(struct SpriteHandler *handler, s16 id, u32 requestedDataType) {
    struct Sprite *sprite;
    s32 output;

    D_03004428 = SPRITE_OPERATION_GET_DATA;
    if (sprite_is_invalid(handler, id)) {
        return 0;
    }

    sprite = &handler->sprites[id];
    switch (requestedDataType) {
        case SPRITE_DATA_VISIBLE:
            output = sprite->visible;
            break;
        case SPRITE_DATA_PLAYBACK_TYPE:
            output = sprite->playbackType;
            break;
        case SPRITE_DATA_TOTAL_CELS:
            output = sprite->celTotal;
            break;
        case SPRITE_DATA_UPDATE_FLAG:
            output = sprite->update;
            break;
        case SPRITE_DATA_X_POS:
            output = sprite->xPos;
            break;
        case SPRITE_DATA_Y_POS:
            output = sprite->yPos;
            break;
        case SPRITE_DATA_Z_DEPTH:
            output = sprite->zDepth;
            break;
        case SPRITE_DATA_ANIMATION:
            output = (u32)sprite->animation;
            break;
        case SPRITE_DATA_CURRENT_CEL_TIME_LEFT:
            output = (s8)FIXED_TO_INT(sprite->currentCelTime);
            break;
        case SPRITE_DATA_CURRENT_CEL:
            output = sprite->currentCel;
            break;
        case SPRITE_DATA_CEL_INC:
            output = sprite->celInc;
            break;
        case SPRITE_DATA_LOOP_CEL:
            output = sprite->loopCel;
            break;
        case SPRITE_DATA_ATTRS10:
            output = sprite->oamAttributes;
            break;
        case SPRITE_DATA_BASE_TILE:
            output = sprite->baseTile;
            break;
        case SPRITE_DATA_CALLBACK_FUNC:
            output = (u32)sprite->callbackFunc;
            break;
        case SPRITE_DATA_CALLBACK_ARG:
            output = sprite->callbackArg;
            break;
        case SPRITE_DATA_MEM_ID:
            output = sprite->memID;
            break;
        case SPRITE_DATA_ORIGIN_X:
            output = (u32)sprite->xOrigin;
            break;
        case SPRITE_DATA_ORIGIN_Y:
            output = (u32)sprite->yOrigin;
            break;
        case SPRITE_DATA_ANIM_SPEED:
            output = sprite->animationSpeed;
            break;
        case SPRITE_DATA_DIMENSION_LEFT:
            output = sprite_get_cel_dimensions((u16 *)sprite->animation[sprite->currentCel].cel, SPRITE_DIMENSION_LEFT);
            break;
        case SPRITE_DATA_DIMENSION_RIGHT:
            output = sprite_get_cel_dimensions((u16 *)sprite->animation[sprite->currentCel].cel, SPRITE_DIMENSION_RIGHT);
            break;
        case SPRITE_DATA_DIMENSION_TOP:
            output = sprite_get_cel_dimensions((u16 *)sprite->animation[sprite->currentCel].cel, SPRITE_DIMENSION_TOP);
            break;
        case SPRITE_DATA_DIMENSION_BOTTOM:
            output = sprite_get_cel_dimensions((u16 *)sprite->animation[sprite->currentCel].cel, SPRITE_DIMENSION_BOTTOM);
            break;
        case SPRITE_DATA_DIMENSION_WIDTH:
            output = sprite_get_cel_dimensions((u16 *)sprite->animation[sprite->currentCel].cel, SPRITE_DIMENSION_WIDTH);
            break;
        case SPRITE_DATA_DIMENSION_HEIGHT:
            output = sprite_get_cel_dimensions((u16 *)sprite->animation[sprite->currentCel].cel, SPRITE_DIMENSION_HEIGHT);
            break;
        default:
            output = 0;
            break;
    }

    return output;
}


// Set Callback Animation Cel
void sprite_set_callback_cel(struct SpriteHandler *handler, s16 id, s8 cel) {
    struct Sprite *sprite;

    if (id >= 0) {
        sprite = &handler->sprites[id];
        sprite->callbackCel = cel;
    }
}


// Set Callback to Trigger Every Time the Current Cel Changes
void sprite_run_callback_every_cel(struct SpriteHandler *handler, s16 id) {
    sprite_set_callback_cel(handler, id, -2);
}


// Set Values by Mem. ID
void sprite_id_set_data(struct SpriteHandler *handler, u16 memID, u32 targetDataType, u32 arg) {
    s16 spriteID = handler->zLinkStart;

    while (spriteID >= 0) {
        s16 nextID = handler->sprites[spriteID].zLinkNext;

        if (handler->sprites[spriteID].memID == memID) {
            switch (targetDataType) {
                case SPRITE_ACT_DELETE:
                    sprite_delete(handler, spriteID);
                    break;
                case SPRITE_ACT_SET_VISIBLE:
                    sprite_set_visible(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_SET_UPDATE:
                    sprite_set_enable_updates(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_SET_ATTR:
                    sprite_attr_set(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_ORR_ATTR:
                    sprite_attr_orr(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_AND_ATTR:
                    sprite_attr_and(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_BIC_ATTR:
                    sprite_attr_bic(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_SET_BASE_TILE:
                    sprite_set_base_tile(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_SET_BASE_PALETTE:
                    sprite_set_base_palette(handler, spriteID, arg);
                    break;
                case SPRITE_ACT_SET_ORIGIN_XY:
                    sprite_set_origin_x_y(handler, spriteID, *(s16 **)arg, *(s16 **)((u32 *)arg + 1));
                    break;
                case SPRITE_ACT_SET_ANIM_SPEED:
                    sprite_set_anim_speed(handler, spriteID, arg);
                    break;
            }
        }

        spriteID = nextID;
    }
}


// Increment Unknown Counter in Sprite Handler
u16 func_0804e0a0(struct SpriteHandler *handler) {
    if (++handler->unk1E == 0) {
        handler->unk1E = 256;
    }

    return handler->unk1E;
}


// Set Current Mem. ID
void sprite_handler_set_mem_id(struct SpriteHandler *handler, u16 memID) {
    handler->memID = memID;
}


// Get Current Mem. ID
u16 sprite_handler_get_mem_id(struct SpriteHandler *handler) {
    return handler->memID;
}


// Delete Sprites by Mem. ID
void sprite_id_delete(struct SpriteHandler *handler, u16 memID) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_DELETE, 0);
}


// Set Visibility by Mem. ID
void sprite_id_set_visible(struct SpriteHandler *handler, u16 memID, u16 isVisible) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_VISIBLE, isVisible);
}


// Set Update Flag by Mem. ID
void sprite_id_set_enable_updates(struct SpriteHandler *handler, u16 memID, u16 canUpdate) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_UPDATE, canUpdate);
}


// Set Attributes by Mem. ID
void sprite_id_set_attr(struct SpriteHandler *handler, u16 memID, u32 attr) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_ATTR, attr);
}


// OR Attributes by Mem. ID
void sprite_id_orr_attr(struct SpriteHandler *handler, u16 memID, u32 attr) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_ORR_ATTR, attr);
}


// AND Attributes by Mem. ID
void sprite_id_and_attr(struct SpriteHandler *handler, u16 memID, u32 attr) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_AND_ATTR, attr);
}


// Bit-Clear Attributes by Mem. ID
void sprite_id_bic_attr(struct SpriteHandler *handler, u16 memID, u32 attr) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_BIC_ATTR, attr);
}


// Set Base Tile Offset by Mem. ID
void sprite_id_set_base_tile(struct SpriteHandler *handler, u16 memID, s16 baseTile) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_BASE_TILE, baseTile);
}


// Set Base Palette Offset by Mem. ID
void sprite_id_set_base_palette(struct SpriteHandler *handler, u16 memID, s8 basePalette) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_BASE_PALETTE, basePalette);
}


// Set World Origin X,Y Position by Mem. ID
void sprite_id_set_origin_x_y(struct SpriteHandler *handler, u16 memID, s16 *xOrigin, s16 *yOrigin) {
    s16 *origin[2] = { xOrigin, yOrigin };

    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_ORIGIN_XY, (uintptr_t)&origin);
}


// Set Animation Speed by Mem. ID
void sprite_id_set_anim_speed(struct SpriteHandler *handler, u16 memID, u8_8 speed) {
    sprite_id_set_data(handler, memID, SPRITE_ACT_SET_ANIM_SPEED, speed);
}


// Set Pause Sprite Flag
void sprite_handler_set_global_pause(struct SpriteHandler *handler, u16 isPaused) {
    handler->paused = isPaused;
}


// Set Global X,Y Offset
void sprite_handler_set_global_x_y(struct SpriteHandler *handler, u16 x, u16 y) {
    handler->xPos = x;
    handler->yPos = y;
}


// Update Sprite Library (https://decomp.me/scratch/THxdI)
#include "asm/lib_0804ca80/asm_0804e1c8.s"


// Get Total Active Sprites
s32 sprite_handler_get_total_active(struct SpriteHandler *handler) {
    struct Sprite *sprites;
    s32 total = 0;
    s32 id;

    sprites = handler->sprites;
    for (id = handler->zLinkStart; id != -1; id = sprites[id].zLinkNext) {
        total++;
    }

    return total;
}


// Get Total Active Sprites by Mem. ID
s32 sprite_handler_get_total_active_id(struct SpriteHandler *handler, u16 memID) {
    struct Sprite *sprites;
    s32 total = 0;
    s32 id;

    sprites = handler->sprites;
    for (id = handler->zLinkStart; id != -1; id = sprites[id].zLinkNext) {
        if (sprites[id].memID == memID) {
            total++;
        }
    }

    return total;
}
