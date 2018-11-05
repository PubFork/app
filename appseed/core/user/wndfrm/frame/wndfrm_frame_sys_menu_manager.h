#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         class CLASS_DECL_CORE SysMenuManager :
            virtual public object
         {
         public:


            friend class WorkSet;

            enum States
            {
               state_initial = 0,
               StateMBDown = 1 // MOUSE BUtton down
            };

            WorkSet *      m_pworkset;
            States         m_enumState;


            SysMenuManager(WorkSet * pwf);
            virtual ~SysMenuManager();

            bool OnLButtonDblClk(UINT nFlags, point point);
            void relay_event(::message::message * pobj);

            bool update(WorkSet * pset);

            void message_handler(::user::interaction * pui, ::message::base * pbase);


         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user










