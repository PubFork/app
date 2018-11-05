#include "framework.h"


string_list::string_list()
{

}



string_list::~string_list()
{
}


POSITION string_list::find(string searchValue, POSITION startAfter) const
{
   ASSERT_VALID(this);

   node* pNode = (node*) startAfter;
   if (pNode == NULL)
   {
      pNode = m_phead;  // start at head
   }
   else
   {
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      pNode = pNode->m_pnext;  // start after the one specified
   }

   for (; pNode != NULL; pNode = pNode->m_pnext)
      if (pNode->m_value == searchValue)
         return (POSITION) pNode;
   return NULL;
}



void string_list::assert_valid() const
{
   object::assert_valid();

   if (m_count == 0)
   {
      // is_empty list
      ASSERT(m_phead == NULL);
      ASSERT(m_ptail == NULL);
   }
   else
   {
      // non-is_empty list
      ASSERT(__is_valid_address(m_phead, sizeof(node)));
      ASSERT(__is_valid_address(m_ptail, sizeof(node)));
   }
}


void string_list::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_count << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      POSITION pos = get_head_position();
      while (pos != NULL)
         dumpcontext << "\n\t" << get_next(pos);
   }

   dumpcontext << "\n";
}

