/**
 * \file vccert_builder_add_short_uint32.c
 *
 * Add a uint32_t field to a certificate.
 *
 * \copyright 2017 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <string.h>
#include <vpr/parameters.h>

#include "builder_internal.h"

/**
 * Add a uint32_t field to the certificate with a short field ID.
 *
 * Note that this value will be written as a Big Endian integer value.
 *
 * \param context           The builder context to use for this operation.
 * \param field             The short field ID to add.
 * \param value             The uint32_t value to encode as this field.
 *
 * \returns 0 on success and non-zero on failure.
 */
int vccert_builder_add_short_uint32(
    vccert_builder_context_t* context, uint16_t field, uint32_t value)
{
    size_t field_size = FIELD_TYPE_SIZE + FIELD_SIZE_SIZE + sizeof(value);

    MODEL_ASSERT(context != NULL);
    MODEL_ASSERT(context->buffer.data != NULL);
    MODEL_ASSERT(context->offset + field_size <= context->buffer.size);

    if (context == NULL || context->buffer.data == NULL || context->buffer.size < context->offset + field_size)
    {
        return VCCERT_ERROR_BUILDER_ADD_INVALID_ARG;
    }

    //write field header
    vccert_builder_write_fieldheader(context, field, sizeof(value));

    //write the value to the buffer
    uint8_t* out = ((uint8_t*)context->buffer.data) + context->offset;
    out[0] = (uint8_t)((value & 0xFF000000) >> 24);
    out[1] = (uint8_t)((value & 0x00FF0000) >> 16);
    out[2] = (uint8_t)((value & 0x0000FF00) >> 8);
    out[3] = (uint8_t)((value & 0x000000FF));

    //increment the offset
    context->offset += sizeof(value);

    return VCCERT_STATUS_SUCCESS;
}
