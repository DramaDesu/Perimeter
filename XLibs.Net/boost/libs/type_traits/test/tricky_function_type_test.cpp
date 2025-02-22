
//  (C) Copyright John Maddock 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "test.hpp"
#include "check_integral_constant.hpp"
#ifdef TEST_STD
#  include <type_traits>
#else
#  include <boost/type_traits/is_function.hpp>
#  include <boost/type_traits/is_float.hpp>
#  include <boost/type_traits/is_enum.hpp>
#  include <boost/type_traits/is_class.hpp>
#  include <boost/type_traits/is_scalar.hpp>
#  include <boost/type_traits/is_pod.hpp>
#  include <boost/type_traits/has_trivial_constructor.hpp>
#  include <boost/type_traits/has_trivial_copy.hpp>
#  include <boost/type_traits/has_trivial_assign.hpp>
#  include <boost/type_traits/has_trivial_destructor.hpp>
#  include <boost/type_traits/is_compound.hpp>
#  include <boost/type_traits/is_base_and_derived.hpp>
#  include <boost/type_traits/is_convertible.hpp>
#endif

TT_TEST_BEGIN(tricky_function_type_test)

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_function<const int&>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_function<int (&)(int)>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo0_t>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pod<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo0_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_base_and_derived<foo0_t, foo0_t>::value), false);
BOOST_CHECK_INTEGRAL_CONSTANT((::tt::is_convertible<foo0_t, int>::value), false);


BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo1_t>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pod<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo1_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo1_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo2_t>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pod<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo2_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo2_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo3_t>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pod<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo3_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo3_t>::value, false);

BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_class<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_enum<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_scalar<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_compound<foo4_t>::value, true);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::is_pod<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_constructor<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_copy<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_assign<foo4_t>::value, false);
BOOST_CHECK_INTEGRAL_CONSTANT(::tt::has_trivial_destructor<foo4_t>::value, false);

TT_TEST_END








