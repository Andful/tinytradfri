#include <check.h>

#include "Gateway.h"
#include "Command.h"

START_TEST(test_gateway_constructor) {
    char* ip = "255.255.255.255";
    char* key = "1234567890123456";
    char* identity = "test_identity";
    Gateway gateway = newGateway(ip, key, identity);

    ck_assert_str_eq(ip, gateway.ip);
    ck_assert_str_eq(key, gateway.key);
    ck_assert_str_eq(identity, gateway.identity);
} END_TEST

Suite* gateway_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Gateway");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_gateway_constructor);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, char const *argv[]) {
    Suite* s = gateway_suite();
    SRunner* sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}