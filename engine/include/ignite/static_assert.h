#ifndef IGNITE_STATIC_ASSERT_H_
#define IGNITE_STATIC_ASSERT_H_

#if defined (__clang__) || defined(__gcc__)
#define IGNITE_STATIC_ASSERT _Static_assert
#else
#define IGNITE_STATIC_ASSERT static_assert
#endif

#endif // IGNITE_STATIC_ASSERT_H_
