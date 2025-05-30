//
// stream_handle.cpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include "asio/windows/stream_handle.hpp"

#include "asio/io_context.hpp"
#include "../archetypes/async_result.hpp"
#include "../unit_test.hpp"

//------------------------------------------------------------------------------

// windows_stream_handle_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// windows::stream_handle compile and link correctly. Runtime failures are
// ignored.

namespace windows_stream_handle_compile {

void write_some_handler(const asio::error_code&, std::size_t)
{
}

void read_some_handler(const asio::error_code&, std::size_t)
{
}

void test()
{
#if defined(ASIO_HAS_WINDOWS_STREAM_HANDLE)
  using namespace asio;
  namespace win = asio::windows;

  try
  {
    io_context ioc;
    const io_context::executor_type ioc_ex = ioc.get_executor();
    char mutable_char_buffer[128] = "";
    const char const_char_buffer[128] = "";
    archetypes::lazy_handler lazy;
    asio::error_code ec;

    // basic_stream_handle constructors.

    win::stream_handle handle1(ioc);
    HANDLE native_handle1 = INVALID_HANDLE_VALUE;
#if defined(ASIO_MSVC) && (_MSC_VER < 1910)
    // Skip this on older MSVC due to mysterious ambiguous overload errors.
#else
    win::stream_handle handle2(ioc, native_handle1);
#endif

    win::stream_handle handle3(ioc_ex);
    HANDLE native_handle2 = INVALID_HANDLE_VALUE;
    win::stream_handle handle4(ioc_ex, native_handle2);

    win::stream_handle handle5(std::move(handle4));

    win::basic_stream_handle<io_context::executor_type> handle6(ioc);
    win::stream_handle handle7(std::move(handle6));

    // basic_stream_handle operators.

    handle1 = win::stream_handle(ioc);
    handle1 = std::move(handle4);
    handle1 = std::move(handle6);

    // I/O object functions.

    windows::stream_handle::executor_type ex = handle1.get_executor();
    (void)ex;

    // basic_overlapped_handle functions.

    win::stream_handle::lowest_layer_type& lowest_layer
      = handle1.lowest_layer();
    (void)lowest_layer;

    const win::stream_handle& handle8 = handle1;
    const win::stream_handle::lowest_layer_type& lowest_layer2
      = handle8.lowest_layer();
    (void)lowest_layer2;

    HANDLE native_handle3 = INVALID_HANDLE_VALUE;
    handle1.assign(native_handle3);

    bool is_open = handle1.is_open();
    (void)is_open;

    handle1.close();
    handle1.close(ec);

    win::stream_handle::native_handle_type native_handle4
      = handle1.release();
    (void)native_handle4;
    win::stream_handle::native_handle_type native_handle5
      = handle1.release(ec);
    (void)native_handle5;

    win::stream_handle::native_handle_type native_handle6
      = handle1.native_handle();
    (void)native_handle6;

    handle1.cancel();
    handle1.cancel(ec);

    // basic_stream_handle functions.

    handle1.write_some(buffer(mutable_char_buffer));
    handle1.write_some(buffer(const_char_buffer));
    handle1.write_some(buffer(mutable_char_buffer), ec);
    handle1.write_some(buffer(const_char_buffer), ec);

    handle1.async_write_some(buffer(mutable_char_buffer), &write_some_handler);
    handle1.async_write_some(buffer(const_char_buffer), &write_some_handler);
    int i1 = handle1.async_write_some(buffer(mutable_char_buffer), lazy);
    (void)i1;
    int i2 = handle1.async_write_some(buffer(const_char_buffer), lazy);
    (void)i2;

    handle1.read_some(buffer(mutable_char_buffer));
    handle1.read_some(buffer(mutable_char_buffer), ec);

    handle1.async_read_some(buffer(mutable_char_buffer), &read_some_handler);
    int i3 = handle1.async_read_some(buffer(mutable_char_buffer), lazy);
    (void)i3;
  }
  catch (std::exception&)
  {
  }
#endif // defined(ASIO_HAS_WINDOWS_STREAM_HANDLE)
}

} // namespace windows_stream_handle_compile

//------------------------------------------------------------------------------

ASIO_TEST_SUITE
(
  "windows/stream_handle",
  ASIO_COMPILE_TEST_CASE(windows_stream_handle_compile::test)
)
