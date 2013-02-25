
#pragma once

#define LL_FLAG_POOL (1 << 0)
#define LL_FLAG_RES1 (1 << 1)
#define LL_FLAG_RES2 (1 << 2)
#define LL_FLAG_RES3 (1 << 3)
#define LL_FLAG_RES4 (1 << 4)
#define LL_FLAG_RES5 (1 << 5)
#define LL_FLAG_RES6 (1 << 6)
#define LL_FLAG_RES7 (1 << 7)

typedef struct link_s 
{
    struct link_s   *prev; 
    struct link_s   *next; 
    uint8_t 	     flags;
    void            *data; 
    size_t           size; 
} link_t; 

typedef struct linked_list_s 
{
    link_t      *head;
    link_t      *tail; 
    link_t      *pool[]; 
    size_t       poolSize; 
} linked_list_t; 


enum 
{
    EL_ERR_NONE     =  0,
    EL_ERR_FAILED   = -1, 
    EL_ERR_MEM      = -2, 
    EL_ERR_PARAM    = -3, 
};




