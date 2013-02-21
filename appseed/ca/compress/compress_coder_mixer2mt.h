// CoderMixer2MT.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace libcompress
{
   namespace coder_mixer
   {
      struct CCoder2: public CCoderInfo2, public ::gen::thread
      {
         HRESULT Result;
         base_array < sp(::gen::reader) > InStreams;
         base_array < sp(::gen::writer) > OutStreams;
         base_array < ::gen::reader * > InStreamPointers;
         base_array < ::gen::writer * > OutStreamPointers;

         CCoder2(::ca::application * papp, uint32_t numInStreams, uint32_t numOutStreams);
         void SetCoderInfo(const file_size **inSizes, const file_size **outSizes);
         virtual int32_t run();
         void Code(progress_info_interface *progress);
      };


      /*
      SetBindInfo()
      for each coder
      AddCoder[2]()
      SetProgressIndex(uint32_t coderIndex);

      for each file
      {
      ReInit()
      for each coder
      SetCoderInfo
      Code
      }
      */

      class CCoderMixer2MT:
         virtual public ::libcompress::coder2_interface,
         virtual public CCoderMixer2
      {
         CBindInfo _bindInfo;
         array_app_alloc < ::gen::stream_binder > _streamBinders;
         int32_t _progressCoderIndex;

         void AddCoderCommon();
         HRESULT Init(::gen::reader **inStreams, ::gen::writer **outStreams);
         HRESULT ReturnIfError(HRESULT code);
      public:
         array_app_alloc<CCoder2> _coders;


         CCoderMixer2MT(::ca::application * papp);

         gen::HRes Code(::gen::reader **inStreams,
            const file_size **inSizes,
            uint32_t numInStreams,
            ::gen::writer **outStreams,
            const file_size **outSizes,
            uint32_t numOutStreams,
            progress_info_interface *progress);

         gen::HRes SetBindInfo(const CBindInfo &bindInfo);
         void AddCoder(::libcompress::coder_interface *coder);
         void AddCoder2(::libcompress::coder2_interface *coder);
         void SetProgressCoderIndex(int32_t coderIndex) {  _progressCoderIndex = coderIndex; }

         void ReInit();
         void SetCoderInfo(uint32_t coderIndex, const file_size **inSizes, const file_size **outSizes)
         {  _coders[coderIndex].SetCoderInfo(inSizes, outSizes); }
         uint64_t GetWriteProcessedSize(uint32_t binderIndex) const
         {  return _streamBinders[binderIndex].ProcessedSize; }
      };

   } // namespace coder_mixer

} // namespace libcompress


