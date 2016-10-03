#pragma once


namespace ftp
{


   class itransfer_notification :
      virtual public iinterface
   {
   public:
      virtual ~itransfer_notification() {}
      virtual string GetLocalStreamName() const = 0;
      virtual UINT GetLocalStreamSize() const = 0;
      virtual void SetLocalStreamOffset(DWORD dwOffsetFromBeginOfStream) = 0;
      virtual void OnBytesReceived(const memory& /*vBuffer*/, long /*lReceivedBytes*/) {}
      virtual void OnPreBytesSend(byte* /*pszBuffer*/, size_t /*bufferSize*/, size_t& /*bytesToSend*/) {}
   };


} // namespace ftp





