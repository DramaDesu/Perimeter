// Copyright David Abrahams 2002. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/has_back_reference.hpp>
#include <boost/python/back_reference.hpp>
#include <boost/ref.hpp>
#include <boost/utility.hpp>
#include <memory>
#include <cassert>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/mpl/bool.hpp>

// This test shows that a class can be wrapped "as itself" but also
// acquire a back-reference iff has_back_reference<> is appropriately
// specialized.
using namespace boost::python;

struct X
{
    explicit X(int x) : x(x), magic(7654321) { ++counter; }
    X(X const& rhs) : x(rhs.x), magic(7654321) { ++counter; }
    virtual ~X() { assert(magic == 7654321); magic = 6666666; x = 9999; --counter; }

    void set(int x) { assert(magic == 7654321); this->x = x; }
    int value() const { assert(magic == 7654321); return x; }
    static int count() { return counter; }
 private:
    void operator=(X const&);
 private:
    int x;
    long magic;
    static int counter;
};

int X::counter;

struct Y : X
{
    Y(PyObject* self, int x) : X(x) {};
    Y(PyObject* self, Y const& rhs) : X(rhs), self(self) {};
 private:
    Y(Y const&);
    PyObject* self;
};

struct Z : X
{
    Z(PyObject* self, int x) : X(x) {};
    Z(PyObject* self, Z const& rhs) : X(rhs), self(self) {};
 private:
    Z(Z const&);
    PyObject* self;
};

Y const& copy_Y(Y const& y) { return y; }
Z const& copy_Z(Z const& z) { return z; }

namespace boost { namespace python
{
  template <>
  struct has_back_reference<Y>
      : mpl::true_
  {
  };

  template <>
  struct has_back_reference<Z>
      : mpl::true_
  {
  };
}}

// prove that back_references get initialized with the right PyObject*
object y_identity(back_reference<Y const&> y)
{
    return y.source();
}

// prove that back_references contain the right value
bool y_equality(back_reference<Y const&> y1, Y const& y2)
{
    return &y1.get() == &y2;
}

BOOST_PYTHON_MODULE(back_reference_ext)
{
    def("copy_Y", copy_Y, return_value_policy<copy_const_reference>());
    def("copy_Z", copy_Z, return_value_policy<copy_const_reference>());
    def("x_instances", &X::count);
    
    class_<Y>("Y", init<int>())
        .def("value", &Y::value)
        .def("set", &Y::set)
        ;

    class_<Z,std::auto_ptr<Z> >("Z", init<int>())
        .def("value", &Z::value)
        .def("set", &Z::set)
        ;

    def("y_identity", y_identity);
    def("y_equality", y_equality);

}

#include "module_tail.cpp"
