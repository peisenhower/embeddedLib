
#pragma once

typedef struct link_s 
{
    struct link_s   *prev; 
    struct link_s   *next; 
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
