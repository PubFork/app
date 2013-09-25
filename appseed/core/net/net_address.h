#pragma once


namespace net
{


   class address
   {
   public:


      union
      {


         struct
         {


            uint16_t m_family;
            uint16_t m_port;


         };


         struct sockaddr_in      m_addr;
         struct sockaddr_in6     m_addr6;
         struct sockaddr         m_sa;


      };


#ifdef METROWIN

      ::Windows::Networking::HostName ^      m_hostname;
      ::Platform::String ^                   m_strService;

#endif



      address();
      address(int32_t family, port_t port = 0);
      address(const string & strAddress, port_t port = 0);
      address(const string & strAddress, const string & strServiceName);
      address(const in_addr & a, port_t port = 0);
      address(const in6_addr & a, port_t port = 0);
      address(const sockaddr_in & a);
      address(const sockaddr_in6 & a);
      address(const sockaddr & sa);
      address(const address & address);



      address & operator = (const address & address);
      bool operator == (const address & address) const;


      inline void copy(const address & address);

      string get_display_number() const;

      inline port_t get_service_number() const;
      inline void set_service_number(port_t iPort);


      bool is_in_same_net(const address & addr, const address & addrMask) const;
      bool is_equal(const address & addr) const;


      inline bool is_ipv4() const;
      inline bool is_ipv6() const;


      inline bool is_valid() const;


      inline int32_t get_family() const;
      

      inline const sockaddr * sa() const;
      inline int32_t sa_len() const;


      bool set_address(const string & strAddress);

      //string reverse() const;


      inline void SetFlowinfo(uint32_t x);
      inline uint32_t GetFlowinfo();


#ifndef WINDOWS
      inline void SetScopeId(uint32_t x);
      inline uint32_t GetScopeId();
#endif

      inline void sync_os_address();
      inline void sync_os_service();

   };


   inline int32_t address::get_family() const
   {
      
      return m_family;

   }

   inline port_t address::get_service_number() const
   {

      return ntohs(m_port);

   }


   inline void address::set_service_number(port_t port)
   {

      m_port = htons(port);

   }


   inline void address::copy(const address & address)
   {

      memcpy(this, &address, sizeof(m_sa));

      sync_os_address();
      sync_os_service();

   }


   inline bool address::is_ipv4() const
   {

      return m_family == AF_INET;

   }


   inline bool address::is_ipv6() const
   {

      return m_family == AF_INET6;

   }


   inline bool address::is_valid() const
   {

      return is_ipv6() || is_ipv4();

   }


   inline const sockaddr * address::sa() const
   {

      return &m_sa;

   }


   inline int32_t address::sa_len() const
   {

      return family_len(m_family);

   }

   inline void address::SetFlowinfo(uint32_t x)
   {
      ASSERT(is_ipv6());
      m_addr6.sin6_flowinfo = x;
   }


   inline uint32_t address::GetFlowinfo()
   {
      ASSERT(is_ipv6());
      return m_addr6.sin6_flowinfo;
   }


#ifndef WINDOWS

   inline void address::SetScopeId(uint32_t x)
   {
      ASSERT(is_ipv6());
      m_addr6.sin6_scope_id = x;
   }


   inline uint32_t address::GetScopeId()
   {
      ASSERT(is_ipv6());
      return m_addr6.sin6_scope_id;
   }

#endif

   inline void address::sync_os_address()
   {
#ifdef METROWIN
      m_hostname  = ref new ::Windows::Networking::HostName(get_display_number());
#endif
   }
   
   inline void address::sync_os_service()
   {
#ifdef METROWIN
#endif
   }


} // namespace sockets





