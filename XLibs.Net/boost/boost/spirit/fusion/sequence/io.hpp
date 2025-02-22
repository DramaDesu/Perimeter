/*=============================================================================
    Copyright (c) 1999-2003 Jaakko J�rvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2003 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_IO_HPP)
#define BOOST_IO_HPP

#include <iostream>
#include <boost/spirit/fusion/sequence/detail/io.hpp>
#include <boost/spirit/fusion/sequence/detail/sequence_base.hpp>

namespace boost { namespace fusion
{
    ///////////////////////////////////////////////////////////////////////////
    //
    //  Sequence I/O (<< and >> operators)
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename OStream, typename Sequence>
    inline OStream&
    operator<<(OStream& os, sequence_base<Sequence> const& seq)
    {
        detail::print_sequence(os, seq.cast());
        return os;
    }

    template <typename IStream, typename Sequence>
    inline IStream&
    operator>>(IStream& is, sequence_base<Sequence>& seq)
    {
        detail::read_sequence(is, seq.cast());
        return is;
    }
}}

#endif
