/**
 * \file error_codes.h
 *
 * Error codes for vccert.
 *
 * \copyright 2018 Velo Payments, Inc.  All rights reserved.
 */

#ifndef VCCERT_ERROR_CODES_HEADER_GUARD
#define VCCERT_ERROR_CODES_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif  //__cplusplus

/**
 * \defgroup error codes for the Velo Crypto Library.
 *
 * @
 */
#define VCCERT_STATUS_SUCCESS 0x0000
#define VCCERT_ERROR_PARSER_OPTIONS_INIT_INVALID_ARG 0x3100
#define VCCERT_ERROR_PARSER_INIT_INVALID_ARG 0x3104
#define VCCERT_ERROR_PARSER_FIELD_NEXT_INVALID_FIELD_SIZE 0x3108
#define VCCERT_ERROR_PARSER_FIELD_NEXT_FIELD_NOT_FOUND 0x3109
#define VCCERT_ERROR_PARSER_FIELD_INVALID_ARG 0x310C
#define VCCERT_ERROR_PARSER_FIELD_INVALID_FIELD_SIZE 0x310D
#define VCCERT_ERROR_PARSER_ATTEST_MISSING_SIGNER_UUID 0x3110
#define VCCERT_ERROR_PARSER_ATTEST_MISSING_SIGNATURE 0x3111
#define VCCERT_ERROR_PARSER_ATTEST_MISSING_SIGNING_CERT 0x3112
#define VCCERT_ERROR_PARSER_ATTEST_CHAIN_ATTESTATION 0x3113
#define VCCERT_ERROR_PARSER_ATTEST_SIGNER_UUID_MISMATCH 0x3114
#define VCCERT_ERROR_PARSER_ATTEST_SIGNER_MISSING_SIGNING_KEY 0x3115
#define VCCERT_ERROR_PARSER_ATTEST_SIGNATURE_MISMATCH 0x3116
#define VCCERT_ERROR_PARSER_ATTEST_MISSING_CONTRACT 0x3117
#define VCCERT_ERROR_PARSER_ATTEST_CONTRACT_VERIFICATION 0x3118
#define VCCERT_ERROR_PARSER_ATTEST_MISSING_TRANSACTION_TYPE 0x3119
#define VCCERT_ERROR_PARSER_ATTEST_MISSING_ARTIFACT_ID 0x311A
#define VCCERT_ERROR_PARSER_ATTEST_GENERAL 0x3120
#define VCCERT_ERROR_PARSER_FIND_NEXT_INVALID_FIELD_SIZE 0x3124
#define VCCERT_ERROR_PARSER_FIND_NEXT_FIELD_NOT_FOUND 0x3125
#define VCCERT_ERROR_BUILDER_OPTIONS_INIT_INVALID_ARG 0x3129
#define VCCERT_ERROR_BUILDER_INIT_INVALID_ARG 0x312D
#define VCCERT_ERROR_BUILDER_SIGN_INVALID_ARG 0x3131
#define VCCERT_ERROR_BUILDER_SIGN_INVALID_FIELD_SIZE 0x3132
#define VCCERT_ERROR_BUILDER_ADD_INVALID_ARG 0x3134

/**
 * @}
 */

/* make this header C++ friendly. */
#ifdef __cplusplus
}
#endif  //__cplusplus

#endif  //VCCERT_ERROR_CODES_HEADER_GUARD
