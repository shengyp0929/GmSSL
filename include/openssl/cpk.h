/* ====================================================================
 * Copyright (c) 2007 - 2016 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 */

#ifndef HEADER_CPK_H
#define HEADER_CPK_H

#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/ossl_typ.h>
#include <openssl/ecies.h>

#ifdef  __cplusplus
extern "C" {
#endif

#define CPK_MAX_ID_LENGTH	64


typedef struct cpk_master_secret_st {
	long version;
	X509_NAME *id;
	X509_ALGOR *pkey_algor;
	X509_ALGOR *map_algor;
	ASN1_OCTET_STRING *secret_factors;
} CPK_MASTER_SECRET;
DECLARE_ASN1_FUNCTIONS(CPK_MASTER_SECRET)

typedef struct cpk_public_params_st {
	long version;
	X509_NAME *id;
	X509_ALGOR *pkey_algor;
	X509_ALGOR *map_algor;
	ASN1_OCTET_STRING *public_factors;
} CPK_PUBLIC_PARAMS;
DECLARE_ASN1_FUNCTIONS(CPK_PUBLIC_PARAMS)

X509_ALGOR *CPK_MAP_new_default(void);
int CPK_MAP_is_valid(const X509_ALGOR *algor);
int CPK_MAP_num_factors(const X509_ALGOR *algor);
int CPK_MAP_num_indexes(const X509_ALGOR *algor);
int CPK_MAP_str2index(const X509_ALGOR *algor, const char *str, int *index);
int CPK_MAP_print(BIO *out, X509_ALGOR *map, int indent, unsigned long flags);

CPK_MASTER_SECRET *CPK_MASTER_SECRET_create(const char *domain_id, EVP_PKEY *pkey, X509_ALGOR *map_algor);
CPK_PUBLIC_PARAMS *CPK_MASTER_SECRET_extract_public_params(CPK_MASTER_SECRET *master);
EVP_PKEY *CPK_MASTER_SECRET_extract_private_key(CPK_MASTER_SECRET *master, const char *id);
EVP_PKEY *CPK_PUBLIC_PARAMS_extract_public_key(CPK_PUBLIC_PARAMS *params, const char *id);


int CPK_PUBLIC_PARAMS_compute_share_key(CPK_PUBLIC_PARAMS *params,
	void *out, size_t outlen, const char *id, EVP_PKEY *priv_key,
	void *(*kdf)(const void *in, size_t inlen, void *out, size_t *outlen));

char *CPK_MASTER_SECRET_get_name(CPK_MASTER_SECRET *master, char *buf, int size);
char *CPK_PUBLIC_PARAMS_get_name(CPK_PUBLIC_PARAMS *params);
int CPK_MASTER_SECRET_digest(CPK_MASTER_SECRET *master, const EVP_MD *type, unsigned char *md, unsigned int *len);
int CPK_PUBLIC_PARAMS_digest(CPK_PUBLIC_PARAMS *params, const EVP_MD *type, unsigned char *md, unsigned int *len);
int CPK_MASTER_SECRET_print(BIO *out, CPK_MASTER_SECRET *master, int indent, unsigned long flags);
int CPK_PUBLIC_PARAMS_print(BIO *out, CPK_PUBLIC_PARAMS *params, int indent, unsigned long flags);
int CPK_MASTER_SECRET_validate_public_params(CPK_MASTER_SECRET *master, CPK_PUBLIC_PARAMS *params);
int CPK_PUBLIC_PARAMS_validate_private_key(CPK_PUBLIC_PARAMS *params, const char *id, const EVP_PKEY *pkey);
CPK_MASTER_SECRET *d2i_CPK_MASTER_SECRET_bio(BIO *bp, CPK_MASTER_SECRET **master);
int i2d_CPK_MASTER_SECRET_bio(BIO *bp, CPK_MASTER_SECRET *master);
CPK_PUBLIC_PARAMS *d2i_CPK_PUBLIC_PARAMS_bio(BIO *bp, CPK_PUBLIC_PARAMS **params);
int i2d_CPK_PUBLIC_PARAMS_bio(BIO *bp, CPK_PUBLIC_PARAMS *params);


/* BEGIN ERROR CODES */
