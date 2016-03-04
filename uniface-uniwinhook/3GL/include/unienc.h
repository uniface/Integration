/* CONT_ID %fv: unienc.h-10:incl:1 % %dc: Tue Sep  9 10:00:27 2014 % */

/*******************************************************************************
Copyright © 2014 Uniface B.V. All rights reserved.
U.S. GOVERNMENT RIGHTS-Use, duplication, or disclosure by the U.S. Government
is subject to restrictions as set forth inapplicable license agreement with
Uniface B.V. and/or its predecessor in interest and as provided in DFARS
227.7202-1(a) and 227.7202-3(a) (1995), DFARS 252.227-7013(c)(1)(ii)(OCT 1988),
FAR 12.212(a)(1995), FAR 52.227-19, or FAR 52.227-14(ALTIII), as applicable.
Uniface B.V.

You have a royalty-free right to use, modify, reproduce and distribute
this sample code (and/or any modified version) in any way you find useful,
provided that you agree that Uniface B.V. has no warranty obligations or
liability for any sample code which has been modified.
*******************************************************************************/
/*******************************************************************************
date   refnum    version who description
080218 c26405    9.3.01  ete Initial creation
090722 c27497    940101  jya Integrate Crypto++
090730 c27531    940101  jya support IV length.
090923 c27637    940101  jya Encode/decode : support UNIX/Linux platforms.
090924 c27639    940101  jya Encode/decode : support Windows Mobile platform.
100114 c28058    940101  ete Unibas needed by URL encode/decode for usprintf.
date   refnum    version who description
*******************************************************************************/

#ifndef UNIENC_H
#define UNIENC_H

#include "ustdlib.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
Encode a null terminated string in Base64 format.
@param In        [IN]  Pointer to the UTF8 string that is to be encoded.
@param Out       [OUT] Pointer to the area where the Base64 encoded result is to be stored.
@param OutMaxLen [IN]  Size of the area Out points to, i.e. the maximum amount of bytes that
                       can be written into Out.
@return:   < 0         Not all characters have been encoded; (-1 * <return value>) have been encoded.
          == 0         Failed to encode in base64.
           > 0         All characters have been encoded.
*/
extern long UBase64Enc(const unsigned char *In, unsigned char *Out, long OutMaxLen);

/**
Decode a null terminated Base64 encoded string to string.
@param In        [IN]  Pointer to the Base64 encoded string that is to be decoded.
@param Out       [OUT] Pointer to the area where the decoded result string is to be stored.
@param OutMaxLen [IN]  Size of the area Out points to, i.e. the maximum amount of bytes that
                       can be written into Out.
@return:   < 0         Not all characters have been decoded; (-1 * <return value>) have been decoded.
          == 0         Failed to decode from base64.
           > 0         All characters have been decoded.
*/
extern long UBase64Dec(const unsigned char *In, unsigned char *Out, long OutMaxLen);

/**
Encode raw data in Base64 format.
@param In        [IN]  Pointer to the data that is to be encoded.
@param InLen     [IN]  length of the data that is to be encoded.
@param Out       [OUT] Pointer to the area where the Base64 encoded result is to be stored.
@param OutMaxLen [IN]  Size of the area Out points to, i.e. the maximum amount of bytes that
                       can be written into Out.
@return:   < 0         Not all characters have been encoded; (-1 * <return value>) have been encoded.
          == 0         Failed to encode in base64.
           > 0         All characters have been encoded.
*/
extern long URawToB64(const unsigned char *In, long Inlen, unsigned char *Out, long OutMaxLen);

/**
Decode a null terminated Base64 encoded string to raw data.
@param In        [IN]  Pointer to the Base64 encoded string that is to be decoded.
@param Out       [OUT] Pointer to the area where the decoded result raw data is to be stored.
@param OutMaxLen [IN]  Size of the area Out points to, i.e. the maximum amount of bytes that
                       can be written into Out.
@return:   < 0         Not all characters have been decoded; (-1 * <return value>) have been decoded.
          == 0         Failed to decode from base64.
           > 0         All characters have been decoded.
*/
extern long UB64ToRaw(const unsigned char *In, unsigned char *Out, long OutMaxLen);

/**
Encode 8 bytes of data in DES format.
@param value     [IN]  Pointer to the 8 bytes of data that is to be encoded.
@param DESkey    [IN]  Pointer to the 8 byte DES key that is to be used to encode 'value'.
@param encrypted [OUT] Pointer to the area where the DES encoded result is to be stored, also 8 bytes in length.
*/
extern void DESencrypt (unsigned char *value, unsigned char *DESkey, unsigned char *encrypted);

/**
Decode 8 bytes of data in DES format.
@param value     [IN]  Pointer to the 8 bytes of encrypted data that is to be decoded.
@param DESkey    [IN]  Pointer to the 8 byte DES key that is to be used to decode 'value'.
@param decrypted [OUT] Pointer to the area where the decrypted result is to be stored, also 8 bytes in length.
*/
extern void DESdecrypt (unsigned char *value, unsigned char *DESkey, unsigned char *decrypted);

/**
Turn a string of 7 bytes into a DES key by adding an odd-parity bit for every 7 bits.
The result is 8 bytes long; in each byte the bit with the lowest significance is the parity bit.
*/
extern void create_DESkey (unsigned char *string, unsigned char *DESkey);

/**
Produce a HMAC digest for the purpose of Message Authentification using MD5 as hashing function
@param text      [IN]   Pointer to data stream.
@param text_len  [IN]   Length of the data stream.
@param key       [IN]   Pointer to authentication key.
@param key_len   [IN]   Length of the authentication key.
@param digest    [OUT]  Resulting 16 byte digest
*/
extern void HMAC_MD5digest(unsigned char*  text, int text_len, unsigned char* key, int key_len, unsigned char digest[16]);

/**
Produce an MD4 message digest.
@param value     [IN]   Pointer to data stream for which the digest is to be produced.
@param length    [IN]   Length of the data stream.
@param digest    [OUT]  Resulting 16 byte digest
*/
extern void MD4digest (unsigned char *value, unsigned int length, unsigned char *digest);

/**
Produce an MD5 message digest.
@param value     [IN]   Pointer to data stream for which the digest is to be produced.
@param length    [IN]   Length of the data stream.
@param digest    [OUT]  Resulting 16 byte digest
*/
extern void MD5digest (unsigned char *value, unsigned int length, unsigned char *digest);

/**
Encode/encrypt data

@param Type      [IN]  Encode/encrypt type.
@param Mode      [IN]  Mode for the block cipher encryption.
@param In        [IN]  Source data.
@param InSize    [IN]  Size of the source data in bytes.
@param Key       [IN]  Encryption key.
@param KeySize   [IN]  Size of the key in bytes.
@param IV        [IN]  Initialization vector for the block cipher modes.
@param IVSize    [IN]  Size of IV in bytes.
@param Out       [OUT] Output buffer. Memory is allocated by this function.
                       You should free it by yourself by calling UEncFree().

@return:   < 0         Error
           = 0         Success
           > 0         Number of bytes in the output buffer.
*/
extern long UEncode(UNIBAS         unibas,
                    const USTRING *Type,
                    const USTRING *Mode,
                    const USTRING *In,
                    const long     InSize,
                    const USTRING *Key,
                    const long     KeySize,
                    const USTRING *IV,
                    const long     IVSize,
                    USTRING      **Out);

/**
Decode/decrypt data

@param Type      [IN]  Decode/decrypt type.
@param Mode      [IN]  Mode for the block cipher encryption.
@param In        [IN]  Source (encoded/encrypted) data.
@param InSize    [IN]  Size of the source data in bytes.
@param Key       [IN]  Decryption key.
@param KeySize   [IN]  Size of the key in bytes.
@param IV        [IN]  Initialization vector for the block cipher modes.
@param IVSize    [IN]  Size of IV in bytes.
@param Out       [OUT] Output buffer. Memory is allocated by this function.
                       You should free it by yourself by calling UEncFree().

@return:   < 0         Error
           = 0         Success
           > 0         Number of bytes in the output buffer.
*/
extern long UDecode(UNIBAS         unibas,
                    const USTRING *Type,
                    const USTRING *Mode,
                    const USTRING *In,
                    const long     InSize,
                    const USTRING *Key,
                    const long     KeySize,
                    const USTRING *IV,
                    const long     IVSize,
                    USTRING      **Out);

/**
To free the allocated memory during UEncode() and UDecode().

@param Text      [IN]  Pointer to the allocated memory.

@return:   < 0         Error
           = 0         Success
*/
extern long UEncFree(USTRING *Text);


#ifdef __cplusplus
}
#endif

#endif /* UNIENC_H */
