#pragma once


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _WAVEOUT
{

   void * waveoutcontext;

   int(*waveout_start)(void * waveoutcontext);

   int(*waveout_write)(void * waveoutcontext, const void * pdata, unsigned int s);

   int(*waveout_stop)(void * waveoutcontext);

   int(*waveout_close)(void * waveoutcontext);

} WAVEOUT, *LPWAVEOUT;



typedef struct _AUDIOFORMAT
{

   int   m_iChannels;
   int   m_iSamplePerSec;
   int   m_iBitsPerSample;

} AUDIOFORMAT, * LPAUDIOFORMAT;


#define WAVEOUT_MESSAGE_PACKET


typedef void WAVEOUT_CALLBACK(LPWAVEOUT pwaveout, unsigned int uiMessage, void * pdata, unsigned int s);

typedef WAVEOUT_CALLBACK * LPWAVEOUT_CALLBACK;



typedef LPWAVEOUT( * LPWAVEOUT_OPEN )(int iChanel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


LPWAVEOUT waveout_open(int iChanel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);

int waveout_start(LPWAVEOUT pwaveout);

int waveout_write(LPWAVEOUT pwaveout, const void * pdata, unsigned int s);

int waveout_stop(LPWAVEOUT pwaveout);

int waveout_close(LPWAVEOUT pwaveout);



#ifdef __cplusplus
} // extern "C"
#endif
