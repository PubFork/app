#pragma once


// with tbs in <3!! (Thomas Boregaard Soerensen)


namespace message
{

   class route
   {
   public:

      receiver *        m_preceiver;
      void *            m_phandler;

      virtual void route_message(message * pmessage) = 0;

   };

   template < typename PRED >
   class pred_route
   {
   public:

      PRED m_pred;

      pred_route(receiver * preceiver, void * phandler, PRED pred) :
         m_preceiver(preceiver),
         m_phandler(phandler),
         m_pred(pred)
      {



      }

      virtual void route_message(message * pmessage)
      {

         m_pred(pmessage);

      }

   };

   
   template < typename PRED >
   route * create_pred_route(PRED pred)
   {

      return new pred_route < PRED >(pred);

   }

   using route_array = ::ptr_array < route >;

   using id_route = ::map < id, const id &, route_array >;


} // namespace message 