/**
 * \file config-mini-tls1_1.h
 *
 * \brief Minimal configuration for TLS 1.1 (RFC 4346)
 */
/*
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
/*
 * Modified for TLS1.2 and GCP IoT Core
 */

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

/* System support */
#define MBEDTLS_HAVE_ASM
//#define MBEDTLS_HAVE_TIME

/* mbed TLS feature support */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_SSL_PROTO_TLS1_2

/* mbed TLS modules */
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C

#define MBEDTLS_ECP_C

//#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
//#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
//#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
//#define MBEDTLS_ECP_DP_BP256R1_ENABLED
//#define MBEDTLS_ECP_DP_BP384R1_ENABLED
//#define MBEDTLS_ECP_DP_BP512R1_ENABLED
//#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
//#define MBEDTLS_ECP_DP_CURVE448_ENABLED

#define MBEDTLS_AES_C
#define MBEDTLS_GCM_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CTR_DRBG_C
//#define MBEDTLS_DES_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_MD_C
//#define MBEDTLS_MD5_C
//#define MBEDTLS_NET_C
#define MBEDTLS_OID_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_RSA_C
//#define MBEDTLS_SHA1_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SSL_CLI_C
//#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_X509_USE_C
#define MBEDTLS_SSL_SERVER_NAME_INDICATION

#define MBEDTLS_ECP_NIST_OPTIM
#define ECP_FIXED_POINT_OPTIM 1

//Memory Consumption stat.
//#define MBEDTLS_PLATFORM_MEMORY
//#define MBEDTLS_PLATFORM_C
//#define MBEDTLS_MEMORY_BUFFER_ALLOC_C
//#define MBEDTLS_MEMORY_DEBUG
//#define MBEDTLS_PLATFORM_FPRINTF_ALT
//#define MBEDTLS_PLATFORM_EXIT_ALT

//#define MBEDTLS_SSL_IN_CONTENT_LEN	(8*1024)
//#define MBEDTLS_SSL_OUT_CONTENT_LEN	    (2*1024)
//#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH

//#define MBEDTLS_MPI_MAX_SIZE 512
//#define MBEDTLS_MPI_WINDOW_SIZE 1 
#define MBEDTLS_AES_ROM_TABLES

/* For test certificates */
#define MBEDTLS_BASE64_C
#define MBEDTLS_CERTS_C


#define MBEDTLS_DEBUG_C

/* For testing with compat.sh */
//#define MBEDTLS_FS_IO

#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */
