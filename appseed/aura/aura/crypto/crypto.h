#pragma once


#if defined(HAVE_OPENSSL)

typedef struct rsa_st RSA;

#define AXIS_RSA_KEY RSA *

#else

#error "AXIS_RSA_KEY could not be defined, is RSA implementation missing?"

#endif

#include "crypto_crypto.h"

int32_t crypto_encrypt(memory & storageEncrypt, const memory & storageDecrypt, memory & key);

int32_t crypto_decrypt(memory & storageDecrypt, const memory & storageEncrypt, memory & key);



