#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src/engines/drum_studio.h"

START_TEST(test_buffer_reads_never_exceed_declared_length)
{
    // Invariant: Buffer reads never exceed the declared length
    const char *payloads[] = {
        "normal",                    // Valid input
        "A",                         // Boundary: single char
        "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",  // 100 chars - exceeds typical buffer
        "EXPLOIT_PAYLOAD_OVERFLOW",  // Exact exploit case from finding
        ""                           // Empty string
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);
    
    for (int i = 0; i < num_payloads; i++) {
        // Test the actual production function that uses strcat/strncat
        char buffer[32] = {0};  // Small buffer to test overflow
        char safe_buffer[256] = {0};  // Large buffer for comparison
        
        // Call the actual function from drum_studio.c
        int result = process_drum_input(buffer, sizeof(buffer), payloads[i]);
        
        // Security invariant: buffer must not be corrupted
        ck_assert_msg(strlen(buffer) < sizeof(buffer), 
                     "Buffer overflow detected for payload: %s", payloads[i]);
        ck_assert_msg(buffer[sizeof(buffer)-1] == '\0',
                     "Buffer null-terminator corrupted for payload: %s", payloads[i]);
        
        // Additional check: compare with safe implementation
        strncpy(safe_buffer, payloads[i], sizeof(safe_buffer)-1);
        safe_buffer[sizeof(safe_buffer)-1] = '\0';
        
        // If result indicates success, verify content matches safe version
        if (result == 0) {
            ck_assert_msg(strcmp(buffer, safe_buffer) == 0 || 
                         strlen(buffer) == sizeof(buffer)-1,
                         "Buffer content mismatch for payload: %s", payloads[i]);
        }
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_buffer_reads_never_exceed_declared_length);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}