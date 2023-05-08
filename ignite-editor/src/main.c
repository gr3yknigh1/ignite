#include <stdio.h>
#include <time.h>

#include <ignite/container_type.h>
#include <ignite/dynamic_array.h>
#include <ignite/ignite.h>
#include <ignite/logging.h>
#include <ignite/random.h>
#include <ignite/types.h>

struct human {
    c_str name;
    u16 age;

    struct human *father;
    struct human *mother;
};

IGNITE_IMPL_CONTAINER_TYPE(HUMAN_CONT_TYPE, sizeof(struct human), true,
                           ignite_memory_copy, ignite_memory_free);

#define PRINT_ARR(__ptr, __len, __type, __fmt)                                 \
    do {                                                                       \
        for (unsigned long i = 0; i < (__len); ++i) {                          \
            printf(__fmt " ", *((__type *)(__ptr) + i));                       \
        }                                                                      \
        printf("\n");                                                          \
    } while (0)

int main() {
    ignite_random_init((u32)time(NULL));
    IGNITE_LOG_TRACE("Hi hi there!");

    struct human misha = {0};
    struct human inna = {0};
    struct human ilya = {
        .name = "Ilya",
        .age = 20,
        .father = &misha,
        .mother = &inna,
    };

    struct ignite_dynamic_array array;
    ignite_dynamic_array_init_empty(&array, &HUMAN_CONT_TYPE);
    IGNITE_LOG_INFO("%li", array.capacity);
    ignite_dynamic_array_push_back(&array, &ilya);
    IGNITE_LOG_INFO("%li", array.capacity);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    ignite_dynamic_array_push_back(&array, &ilya);
    IGNITE_LOG_INFO("%li", array.capacity);

    for (u64 i = 0; i < array.length; ++i) {
        struct human *h = NULL;
        enum ignite_status ret = ignite_dynamic_array_get(&array, i, (void **)&h);
        if (ret != IGNITE_OK) {
            IGNITE_LOG_ERROR("ignite status code: '%i'", ret);
            return EXIT_FAILURE;
        }
        IGNITE_LOG_INFO("%s", h->name);
    }
    return EXIT_SUCCESS;
}
