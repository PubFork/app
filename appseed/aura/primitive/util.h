#pragma once


/// Base class for implementing the notification stuff.
/// @remarks Inherit public (instead of private) because it wouldn't compile under Dev-C++
template < typename T, typename T2 > class observer :
   virtual public ref_array < T >
{
public:


   typedef ref_array < T > base_type;

   T2 *   m_pt2This;

   virtual ~observer()
   {

      for (auto p : *this)
      {

         try
         {

            p->detach_observer(m_pt2This);

         }
         catch (...)
         {


         }

      }

   }

   bool attach_observer(T * p)
   {
      if (this->contains(p))
         return false;
      this->add(p);
      m_pt2This = dynamic_cast <T2 *>(this);
      p->attach_observer(m_pt2This);
      return true;
   }
   bool detach_observer(T * p)
   {
      if (!this->contains(p))
         return false;
      this->remove(p);
      p->detach_observer(m_pt2This);
      return true;
   }
};


/// @brief Calculates elapsed CPU time.
/// Is useful for calculating transfer rates.
class CTimer
{
public:
   CTimer() : m_dfStart(get_tick_count()) {}

   /// Restarts the timer.
   void Restart() { m_dfStart = get_tick_count(); }

   /// Get the elapsed time in seconds.
   double GetElapsedTime() const
   {
      return (static_cast<double>(get_tick_count()) - m_dfStart) / 1000;
   }

private:
   double m_dfStart; ///< elapsed CPU time for process (start of measurement)
};



