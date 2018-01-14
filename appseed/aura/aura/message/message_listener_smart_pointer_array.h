#pragma once


namespace message
{


   template < class RECEIVER >
   class listener_smart_pointer_array :
      virtual public sender,
      virtual protected spa(RECEIVER)
   {
   public:

      
      inline void add(RECEIVER * preceiver)
      {
         
         install_handlers(preceiver);
         
         spa(RECEIVER)::add(preceiver);

      }


      inline void remove(RECEIVER * preceiver)
      {
         
         spa(RECEIVER)::remove(preceiver);

         remove_receiver(preceiver);

      }

      //inline ::message::receiver * element_at(index i) { return spa(::message::receiver)::element_at(i); }
      //inline ::count get_size() { return spa(::message::receiver)::get_size(); }
      //inline ::count get_count() { return spa(::message::receiver)::get_count(); }
      //inline ::count size() { return spa(::message::receiver)::size(); }
      //inline ::count count() { return spa(::message::receiver)::count(); }

      virtual void install_handlers(RECEIVER *)
      {
      
      }

      using spa(RECEIVER)::element_at;
      using spa(RECEIVER)::get_size;
      using spa(RECEIVER)::get_count;
      using spa(RECEIVER)::size;
      using spa(RECEIVER)::count;

   };



} // namespace message



#define message_listener_spa(receiver) ::message::listener_smart_pointer_array < receiver >