/**
 * \file test_vccert_parser_find_short.cpp
 *
 * Test vccert_parser_find_short.
 *
 * \copyright 2017 Velo-Payments, Inc.  All rights reserved.
 */

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <vccert/parser.h>
#include <vccrypt/suite.h>
#include <vpr/allocator/malloc_allocator.h>

//forward declarations for dummy certificate delegate methods
static bool dummy_txn_resolver(
    void*, void*, const uint8_t*, const uint8_t*,
    vccrypt_buffer_t*, bool*);
static int32_t dummy_artifact_state_resolver(
    void*, void*, const uint8_t*, vccrypt_buffer_t*);
static bool dummy_entity_key_resolver(
    void*, void*, uint64_t, const uint8_t*, vccrypt_buffer_t*,
    vccrypt_buffer_t*);
static int dummy_contract_resolver(
    void*, void*, const uint8_t*, const uint8_t*,
    vccert_contract_closure_t* closure);

static const uint8_t* TEST_CERT = (const uint8_t*)
    //field 0x0001 is 0x01020304
    "\x00\x01\x00\x04\x01\x02\x03\x04"
    //field 0x1002 is "Testing 1 2 3"
    "\x10\x02\x00\x0dTesting 1 2 3"
    //field 0x1735 is 0x01
    "\x17\x35\x00\x01\x01";
static const size_t TEST_CERT_SIZE = 30;

class vccert_parser_find_short_test : public ::testing::Test {
protected:
    void SetUp() override
    {
        vccrypt_suite_register_velo_v1();

        malloc_allocator_options_init(&alloc_opts);

        suite_init_result =
            vccrypt_suite_options_init(&crypto_suite, &alloc_opts,
                VCCRYPT_SUITE_VELO_V1);

        options_init_result =
            vccert_parser_options_init(
                &options, &alloc_opts, &crypto_suite, &dummy_txn_resolver,
                &dummy_artifact_state_resolver, &dummy_contract_resolver,
                &dummy_entity_key_resolver, &dummy_context);

        parser_init_result =
            vccert_parser_init(&options, &parser, TEST_CERT, TEST_CERT_SIZE);
    }

    void TearDown() override
    {
        if (options_init_result == 0)
        {
            dispose((disposable_t*)&options);
        }

        if (suite_init_result == 0)
        {
            dispose((disposable_t*)&crypto_suite);
        }

        if (parser_init_result == 0)
        {
            dispose((disposable_t*)&parser);
        }

        dispose((disposable_t*)&alloc_opts);
    }

    int suite_init_result, options_init_result, parser_init_result;
    int dummy_context;
    allocator_options_t alloc_opts;
    vccrypt_suite_options_t crypto_suite;
    vccert_parser_options_t options;
    vccert_parser_context_t parser;
};

/**
 * Sanity test of external dependencies.
 */
TEST_F(vccert_parser_find_short_test, external_dependencies)
{
    ASSERT_EQ(0, options_init_result);
    ASSERT_EQ(0, suite_init_result);
    ASSERT_EQ(0, parser_init_result);
}

/**
 * Test that an exhaustive search returns a non-zero result.
 */
TEST_F(vccert_parser_find_short_test, field_not_found)
{
    const uint8_t* value;
    size_t size;

    EXPECT_NE(0, vccert_parser_find_short(&parser, 0x1234, &value, &size));
}

/**
 * Test that each field can be found, and the values and sizes are correct.
 */
TEST_F(vccert_parser_find_short_test, field_search)
{
    const uint8_t* value;
    size_t size;

    uint32_t field1_val;

    //find field 0x0001
    ASSERT_EQ(0, vccert_parser_find_short(&parser, 0x0001, &value, &size));
    ASSERT_EQ(4U, size);
    ASSERT_NE((const uint8_t*)NULL, value);
    memcpy(&field1_val, value, sizeof(uint32_t));
    EXPECT_EQ(0x01020304UL, htonl(field1_val));

    //find field 0x1002
    ASSERT_EQ(0, vccert_parser_find_short(&parser, 0x1002, &value, &size));
    ASSERT_EQ(13U, size);
    ASSERT_NE((const uint8_t*)NULL, value);
    EXPECT_EQ(0, memcmp(value, "Testing 1 2 3", size));

    //find field 0x1735
    ASSERT_EQ(0, vccert_parser_find_short(&parser, 0x1735, &value, &size));
    ASSERT_EQ(1U, size);
    ASSERT_NE((const uint8_t*)NULL, value);
    EXPECT_EQ(0x01, *value);
}

/**
 * Dummy transaction resolver.
 */
static bool dummy_txn_resolver(
    void*, void*, const uint8_t*, const uint8_t*,
    vccrypt_buffer_t*, bool*)
{
    return false;
}

/**
 * Dummy artifact state resolver.
 */
static int32_t dummy_artifact_state_resolver(
    void*, void*, const uint8_t*, vccrypt_buffer_t*)
{
    return -1;
}

/**
 * Dummy entity key resolver.
 */
static bool dummy_entity_key_resolver(
    void*, void*, uint64_t, const uint8_t*, vccrypt_buffer_t*,
    vccrypt_buffer_t*)
{
    return false;
}

/**
 * Dummy contract resolver.
 */
static int dummy_contract_resolver(
    void*, void*, const uint8_t*, const uint8_t*,
    vccert_contract_closure_t*)
{
    return VCCERT_ERROR_PARSER_ATTEST_MISSING_CONTRACT;
}
