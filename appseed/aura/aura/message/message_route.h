#pragma once


// with tbs in <3!! (Thomas Boregaard Soerensen)


namespace message
{

   class route
   {
   public:


      receiver *        m_preceiver;
      void *            m_pvoidReceiver;
      sp(type)          m_ptypeReceiver;


      route(receiver * preceiver, void * pvoidReceiver, ::type * ptypeReceiver) :
         m_preceiver(preceiver),
         m_pvoidReceiver(pvoidReceiver),
         m_ptypeReceiver(ptypeReceiver)
      {


      }

      virtual ~route()
      {


      }

      virtual void route_message(message * pmessage)
      {

         _throw(interface_only_exception(NULL));
         // has been the pred_route implementation deleted?

      }

   };

   template < typename PRED >
   class pred_route :
      public route
   {
   public:

      PRED m_pred;

      pred_route(receiver * preceiver, void * pvoidReceiver, PRED pred, type * ptype) :
         route(preceiver, pvoidReceiver, ptype),
         m_pred(pred)
      {

      }

      virtual ~pred_route()
      {


      }

      virtual void route_message(message * pmessage)
      {

         m_pred(pmessage);

      }

   };


   template < typename PRED >
   route * create_pred_route(receiver * preceiver, void * pvoidReceiver, PRED pred, ::type * ptype)
   {

      return new pred_route < PRED >(preceiver, pvoidReceiver, pred, ptype);

   }

   using route_array = ::auto_pointer_array < route >;

   using id_route = ::map < ::message::id, const ::message::id &, route_array >;

   using type_id_route = ::map < e_type, e_type, id_route >;


} // namespace message
