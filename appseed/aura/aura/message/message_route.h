#pragma once


// with tbs in <3!! (Thomas Boregaard Soerensen)


namespace message
{


   class route :
      virtual public simple_object
   {
   public:


      receiver *        m_preceiver;
      object *          m_pobjectReceiver;
      sp(type)          m_ptypeReceiver;


      route(receiver * preceiver, ::object * pobjectReceiver, ::type * ptypeReceiver) :
         m_preceiver(preceiver),
         m_pobjectReceiver(pobjectReceiver),
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

      pred_route(receiver * preceiver, ::object * pobjectReceiver, PRED pred, type * ptype) :
         route(preceiver, pobjectReceiver, ptype),
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
   route * create_pred_route(receiver * preceiver, ::object * pobjectReceiver, PRED pred, ::type * ptype)
   {

      return canew(pred_route < PRED >(preceiver, pobjectReceiver, pred, ptype));

   }

   using route_array = spa(route);

   using id_route = ::map < ::message::id, const ::message::id &, sp(route_array) >;

   using type_id_route = ::map < e_type, e_type, id_route >;


} // namespace message
