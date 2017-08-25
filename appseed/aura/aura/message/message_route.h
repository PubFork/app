#pragma once


// with tbs in <3!! (Thomas Boregaard Soerensen)


namespace message
{

   class route
   {
   public:

      receiver *        m_preceiver;

      virtual void route_message(message * pmessage) = 0;

   };

   template < typename PRED >
   class pred_route :
      public route
   {
   public:

      PRED m_pred;

      pred_route(receiver * preceiver, PRED pred) :
         m_pred(pred)
      {

         m_preceiver = preceiver;

      }

      virtual void route_message(message * pmessage)
      {

         m_pred(pmessage);

      }

   };

   
   template < typename PRED >
   route * create_pred_route(receiver * preceiver, PRED pred)
   {

      return new pred_route < PRED >(preceiver, pred);

   }

   using route_array = ::ptr_array < route >;

   using id_route = ::map < id, const id &, route_array >;


} // namespace message 