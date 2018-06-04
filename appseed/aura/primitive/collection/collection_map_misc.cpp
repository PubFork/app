#include "framework.h"

map_ptr_to_ptr::map_ptr_to_ptr(::aura::application * papp) :
   object(papp),
   map < void *, void *, void *, void *> (papp)
{
}

map_ptr_to_word::map_ptr_to_word(::aura::application * papp) :
   object(papp),
   map < void *, void *, WORD, WORD > (papp)
{
}


map_string_to_ob::map_string_to_ob(::aura::application * papp) :
   object(papp),
   map < string, const string &, object *, object * > (papp)
{
}

map_string_to_ptr::map_string_to_ptr(::aura::application * papp) :
   object(papp),
   map < string, const string &, void *, void * > (papp)
{
}

map_word_to_ob::map_word_to_ob(::aura::application * papp) :
   object(papp),
   map < WORD, WORD, object *, object * > (papp)
{
}

map_word_to_ptr::map_word_to_ptr(::aura::application * papp) :
   object(papp),
   map < WORD, WORD, void *, void * > (papp)
{
}

