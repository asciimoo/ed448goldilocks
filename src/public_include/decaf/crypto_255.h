/**
 * @file decaf/crypto_255.h
 * @copyright
 *   Copyright (c) 2015 Cryptography Research, Inc.  \n
 *   Released under the MIT License.  See LICENSE.txt for license information.
 * @author Mike Hamburg
 * @brief Example Decaf cyrpto routines.
 * @warning These are merely examples, though they ought to be secure.  But real
 * protocols will decide differently on magic numbers, formats, which items to
 * hash, etc.
 * @warning Experimental!  The names, parameter orders etc are likely to change.
 */

#ifndef __DECAF_CRYPTO_255_H__
#define __DECAF_CRYPTO_255_H__ 1

#include <decaf/decaf_255.h>
#include <decaf/shake.h>

/** Number of bytes for a symmetric key (expanded to full key) */
#define DECAF_255_SYMMETRIC_KEY_BYTES 32

/** A symmetric key, the compressed point of a private key. */
typedef unsigned char decaf_255_symmetric_key_t[DECAF_255_SYMMETRIC_KEY_BYTES];

/** An encoded public key. */
typedef unsigned char decaf_255_public_key_t[DECAF_255_SER_BYTES];

/** A signature. */
typedef unsigned char decaf_255_signature_t[DECAF_255_SER_BYTES + DECAF_255_SCALAR_BYTES];

typedef struct {
    /** @cond intetrnal */
    /** The symmetric key from which everything is expanded */
    decaf_255_symmetric_key_t sym;
    
    /** The scalar x */
    decaf_255_scalar_t secret_scalar;
    
    /** x*Base */
    decaf_255_public_key_t pub;
    /** @endcond */
} /** Private key structure for pointers. */
  decaf_255_private_key_s,
  /** A private key (gmp array[1] style). */
  decaf_255_private_key_t[1];

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * @brief Derive a key from its compressed form.
 * @param [out] priv The derived private key.
 * @param [in] proto The compressed or proto-key, which must be 32 random bytes.
 */
void decaf_255_derive_private_key (
    decaf_255_private_key_t priv,
    const decaf_255_symmetric_key_t proto
) NONNULL2 API_VIS;

/**
 * @brief Destroy a private key.
 */
void decaf_255_destroy_private_key (
    decaf_255_private_key_t priv
) NONNULL1 API_VIS;

/**
 * @brief Convert a private key to a public one.
 * @param [out] pub The extracted private key.
 * @param [in] priv The private key.
 */
void decaf_255_private_to_public (
    decaf_255_public_key_t pub,
    const decaf_255_private_key_t priv
) NONNULL2 API_VIS;
    
/**
 * @brief Compute a Diffie-Hellman shared secret.
 *
 * This is an example routine; real protocols would use something
 * protocol-specific.
 *
 * @param [out] shared A buffer to store the shared secret.
 * @param [in] shared_bytes The size of the buffer.
 * @param [in] my_privkey My private key.
 * @param [in] your_pubkey Your public key.
 * @param [in] me_first Direction flag to break symmetry.
 *
 * @retval DECAF_SUCCESS Key exchange was successful.
 * @retval DECAF_FAILURE Key exchange failed.
 */
decaf_error_t
decaf_255_shared_secret (
    uint8_t *shared,
    size_t shared_bytes,
    const decaf_255_private_key_t my_privkey,
    const decaf_255_public_key_t your_pubkey,
    int me_first
) NONNULL134 WARN_UNUSED API_VIS;
   
/**
 * @brief Sign a message from a STROBE context.
 *
 * @param [out] sig The signature.
 * @param [in] priv Your private key.
 * @param [in] strobe A STROBE context with the message.
 */ 
void
decaf_255_sign_strobe (
    keccak_strobe_t strobe,
    decaf_255_signature_t sig,
    const decaf_255_private_key_t priv
) NONNULL3 API_VIS;

/**
 * @brief Sign a message.
 *
 * @param [out] sig The signature.
 * @param [in] priv Your private key.
 * @param [in] message The message.
 * @param [in] message_len The message's length.
 */ 
void
decaf_255_sign (
    decaf_255_signature_t sig,
    const decaf_255_private_key_t priv,
    const unsigned char *message,
    size_t message_len
) NONNULL3 API_VIS;

/**
 * @brief Verify a signed message from its STROBE context.
 *
 * @param [in] sig The signature.
 * @param [in] pub The public key.
 * @param [in] strobe A STROBE context with the message.
 *
 * @return DECAF_SUCCESS The signature verified successfully.
 * @return DECAF_FAILURE The signature did not verify successfully.
 */    
decaf_error_t
decaf_255_verify_strobe (
    keccak_strobe_t strobe,
    const decaf_255_signature_t sig,
    const decaf_255_public_key_t pub
) NONNULL3 API_VIS WARN_UNUSED;

/**
 * @brief Verify a signed message.
 *
 * @param [in] sig The signature.
 * @param [in] pub The public key.
 * @param [in] message The message.
 * @param [in] message_len The message's length.
 *
 * @return DECAF_SUCCESS The signature verified successfully.
 * @return DECAF_FAILURE The signature did not verify successfully.
 */    
decaf_error_t
decaf_255_verify (
    const decaf_255_signature_t sig,
    const decaf_255_public_key_t pub,
    const unsigned char *message,
    size_t message_len
) NONNULL3 API_VIS WARN_UNUSED;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __DECAF_CRYPTO_255_H__ */


