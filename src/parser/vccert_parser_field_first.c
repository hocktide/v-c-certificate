/**
 * \file vccert_parser_field_first.c
 *
 * Return the first field in a certificate.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <vpr/parameters.h>

#include "parser_internal.h"

/**
 * Return the first field in the certificate.  If the certificate has not been
 * attested, then this performs an UNSAFE SEARCH of the RAW CERTIFICATE.  Run
 * vccert_parser_attest() first if you want trusted information.  Additional
 * fields can be found by calling vccert_parser_field_next().
 *
 * \param context           The parser context structure for this certificate.
 * \param field_id          The pointer to receive the short-hand field
 *                          identifier.
 * \param value             The pointer to receive a pointer to the field value.
 * \param size              The pointer to receive the size of this field.
 *
 * \returns 0 on success and non-zero if no fields exist in this certificate.
 */
int vccert_parser_field_first(
    vccert_parser_context_t* context, uint16_t* field_id,
    const uint8_t** value, size_t* size)
{
    MODEL_ASSERT(context != NULL);
    MODEL_ASSERT(context->cert != NULL);
    MODEL_ASSERT(context->size > 0);
    MODEL_ASSERT(field_id != NULL);
    MODEL_ASSERT(value != NULL);
    MODEL_ASSERT(size != NULL);

    size_t next_offset;

    return vccert_parser_field(context->cert, context->size, 0, field_id, size,
        value, &next_offset);
}
