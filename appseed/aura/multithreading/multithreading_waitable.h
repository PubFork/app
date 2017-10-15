/**
* \brief Session independent waitables
*/
#pragma once


class mutex;
class event;



///  \brief    pauses object for specified time
///  \param    duration sleeping time of object
CLASS_DECL_AURA void sleep(const duration & duration);


// forward declaration
class event_base;


/// This class represents a virtual interface for a callback method for WaitableItems in a
/// event_collection.


class CLASS_DECL_AURA waitable_callback
{
   public:
      virtual ~waitable_callback();

      /// called on signalization of a event_base
      /// \param signaling event_base
      virtual void callback(const event_base& waitItem) = 0;
};



namespace aura
{


   // platform abstraction layer
   namespace pal
   {


      typedef ::object WaitableItem;


   } // namespace pal - platform abstraction layer


} // namespace aura




