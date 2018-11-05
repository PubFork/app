#pragma once



namespace sockets
{
   /** List type containing file descriptors. */
   class CLASS_DECL_AURA socket_id_list :
      public ::comparable_list<SOCKET>
   {
   };

} // namespace sockets
