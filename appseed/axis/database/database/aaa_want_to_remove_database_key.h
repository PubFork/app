#pragma once


//
//
//namespace database
//{
//
//   class client;
//
//
//   class CLASS_DECL_AXIS key
//   {
//   public:
//
//
//      client *          m_pclient; // client may intefere in default key calculation
//      id                m_id;
//
//
//
//      key()
//      {
//         m_pclient = NULL;
//      }
//
//      key(const key & key)
//      {
//         operator = (key);
//      }
//
//
//      key(client * pclient,::database::key id)
//      {
//
//         m_pclient      = pclient;
//         m_id           = id;
//
//      }
//
//
//
//      key & operator = (const key & key)
//      {
//         if(&key != this)
//         {
//            m_pclient      = key.m_pclient;
//            m_id           = key.m_id;
//         }
//         return *this;
//      }
//
//
//   };
//
//
//} // namespace database
//
//
//
//
//
//
