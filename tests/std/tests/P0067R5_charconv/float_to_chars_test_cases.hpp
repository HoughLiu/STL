// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception


// Copyright 2018 Ulf Adams
// Copyright (c) Microsoft Corporation. All rights reserved.

// Boost Software License - Version 1.0 - August 17th, 2003

// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:

// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.


// This file contains test cases derived from:
// https://github.com/ulfjack/ryu
// See xcharconv_ryu.h for the exact commit.
// (Keep the cgmanifest.json commitHash in sync.)


#pragma once

#include "test.hpp"
#include <charconv>
using namespace std;

inline constexpr FloatToCharsTestCase float_to_chars_test_cases[] = {
    // Test special cases (zero, inf, nan) and an ordinary case. Also test negative signs.
    {0.0f, chars_format::scientific, "0e+00"},
    {-0.0f, chars_format::scientific, "-0e+00"},
    {float_inf, chars_format::scientific, "inf"},
    {-float_inf, chars_format::scientific, "-inf"},
    {float_nan, chars_format::scientific, "nan"},
    {-float_nan, chars_format::scientific, "-nan(ind)"},
    {float_nan_payload, chars_format::scientific, "nan"},
    {-float_nan_payload, chars_format::scientific, "-nan"},
    {2.018f, chars_format::scientific, "2.018e+00"},
    {-2.018f, chars_format::scientific, "-2.018e+00"},

    // Ditto for fixed, which doesn't emit exponents.
    {0.0f, chars_format::fixed, "0"},
    {-0.0f, chars_format::fixed, "-0"},
    {float_inf, chars_format::fixed, "inf"},
    {-float_inf, chars_format::fixed, "-inf"},
    {float_nan, chars_format::fixed, "nan"},
    {-float_nan, chars_format::fixed, "-nan(ind)"},
    {float_nan_payload, chars_format::fixed, "nan"},
    {-float_nan_payload, chars_format::fixed, "-nan"},
    {2.018f, chars_format::fixed, "2.018"},
    {-2.018f, chars_format::fixed, "-2.018"},

    // Ditto for general, which selects fixed for the scientific exponent 0.
    {0.0f, chars_format::general, "0"},
    {-0.0f, chars_format::general, "-0"},
    {float_inf, chars_format::general, "inf"},
    {-float_inf, chars_format::general, "-inf"},
    {float_nan, chars_format::general, "nan"},
    {-float_nan, chars_format::general, "-nan(ind)"},
    {float_nan_payload, chars_format::general, "nan"},
    {-float_nan_payload, chars_format::general, "-nan"},
    {2.018f, chars_format::general, "2.018"},
    {-2.018f, chars_format::general, "-2.018"},

    // Ditto for plain, which selects fixed because it's shorter for these values.
    {0.0f, chars_format{}, "0"},
    {-0.0f, chars_format{}, "-0"},
    {float_inf, chars_format{}, "inf"},
    {-float_inf, chars_format{}, "-inf"},
    {float_nan, chars_format{}, "nan"},
    {-float_nan, chars_format{}, "-nan(ind)"},
    {float_nan_payload, chars_format{}, "nan"},
    {-float_nan_payload, chars_format{}, "-nan"},
    {2.018f, chars_format{}, "2.018"},
    {-2.018f, chars_format{}, "-2.018"},

    // Ditto for hex.
    {0.0f, chars_format::hex, "0p+0"},
    {-0.0f, chars_format::hex, "-0p+0"},
    {float_inf, chars_format::hex, "inf"},
    {-float_inf, chars_format::hex, "-inf"},
    {float_nan, chars_format::hex, "nan"},
    {-float_nan, chars_format::hex, "-nan(ind)"},
    {float_nan_payload, chars_format::hex, "nan"},
    {-float_nan_payload, chars_format::hex, "-nan"},
    {0x1.729p+0f, chars_format::hex, "1.729p+0"},
    {-0x1.729p+0f, chars_format::hex, "-1.729p+0"},

    // Ryu f2s_test.cc SwitchToSubnormal
    {1.1754944e-38f, chars_format::scientific, "1.1754944e-38"},

    // Ryu f2s_test.cc MinAndMax
    {0x1.fffffep+127f, chars_format::scientific, "3.4028235e+38"},
    {0x1.000000p-149f, chars_format::scientific, "1e-45"},

    // Ryu f2s_test.cc BoundaryRoundEven
    {3.355445e7f, chars_format::scientific, "3.355445e+07"},
    {8.999999e9f, chars_format::scientific, "9e+09"},
    {3.4366717e10f, chars_format::scientific, "3.436672e+10"},

    // Ryu f2s_test.cc ExactValueRoundEven
    {3.0540412e5f, chars_format::scientific, "3.0540412e+05"},
    {8.0990312e3f, chars_format::scientific, "8.0990312e+03"},

    // Ryu f2s_test.cc LotsOfTrailingZeros
    {2.4414062e-4f, chars_format::scientific, "2.4414062e-04"},
    {2.4414062e-3f, chars_format::scientific, "2.4414062e-03"},
    {4.3945312e-3f, chars_format::scientific, "4.3945312e-03"},
    {6.3476562e-3f, chars_format::scientific, "6.3476562e-03"},

    // Ryu f2s_test.cc Regression
    {4.7223665e21f, chars_format::scientific, "4.7223665e+21"},
    {8388608.0f, chars_format::scientific, "8.388608e+06"},
    {1.6777216e7f, chars_format::scientific, "1.6777216e+07"},
    {3.3554436e7f, chars_format::scientific, "3.3554436e+07"},
    {6.7131496e7f, chars_format::scientific, "6.7131496e+07"},
    {1.9310392e-38f, chars_format::scientific, "1.9310392e-38"},
    {-2.47e-43f, chars_format::scientific, "-2.47e-43"},
    {1.993244e-38f, chars_format::scientific, "1.993244e-38"},
    {4103.9003f, chars_format::scientific, "4.1039004e+03"},
    {5.3399997e9f, chars_format::scientific, "5.3399997e+09"},
    {6.0898e-39f, chars_format::scientific, "6.0898e-39"},
    {0.0010310042f, chars_format::scientific, "1.0310042e-03"},
    {2.8823261e17f, chars_format::scientific, "2.882326e+17"},
    {0x1.5c87fap-84f, chars_format::scientific, "7.038531e-26"}, // TRANSITION, VSO-629490, should be 7.038531e-26f
    {9.2234038e17f, chars_format::scientific, "9.223404e+17"},
    {6.7108872e7f, chars_format::scientific, "6.710887e+07"},
    {1.0e-44f, chars_format::scientific, "1e-44"},
    {2.816025e14f, chars_format::scientific, "2.816025e+14"},
    {9.223372e18f, chars_format::scientific, "9.223372e+18"},
    {1.5846085e29f, chars_format::scientific, "1.5846086e+29"},
    {1.1811161e19f, chars_format::scientific, "1.1811161e+19"},
    {5.368709e18f, chars_format::scientific, "5.368709e+18"},
    {4.6143165e18f, chars_format::scientific, "4.6143166e+18"},
    {0.007812537f, chars_format::scientific, "7.812537e-03"},
    {1.4e-45f, chars_format::scientific, "1e-45"},
    {1.18697724e20f, chars_format::scientific, "1.18697725e+20"},
    {1.00014165e-36f, chars_format::scientific, "1.00014165e-36"},
    {200.0f, chars_format::scientific, "2e+02"},
    {3.3554432e7f, chars_format::scientific, "3.3554432e+07"},

    // Ryu f2s_test.cc LooksLikePow5
    {0x1.2a05f2p+59f, chars_format::scientific, "6.7108864e+17"},
    {0x1.2a05f2p+60f, chars_format::scientific, "1.3421773e+18"},
    {0x1.2a05f2p+61f, chars_format::scientific, "2.6843546e+18"},

    // Ryu f2s_test.cc OutputLength
    {1.0f, chars_format::scientific, "1e+00"},
    {1.2f, chars_format::scientific, "1.2e+00"},
    {1.23f, chars_format::scientific, "1.23e+00"},
    {1.234f, chars_format::scientific, "1.234e+00"},
    {1.2345f, chars_format::scientific, "1.2345e+00"},
    {1.23456f, chars_format::scientific, "1.23456e+00"},
    {1.234567f, chars_format::scientific, "1.234567e+00"},
    {1.2345678f, chars_format::scientific, "1.2345678e+00"},
    {1.23456735e-36f, chars_format::scientific, "1.23456735e-36"},

    // Test all exponents.
    {1.729e-45f, chars_format::scientific, "1e-45"},
    {1.729e-44f, chars_format::scientific, "1.7e-44"},
    {1.729e-43f, chars_format::scientific, "1.72e-43"},
    {1.729e-42f, chars_format::scientific, "1.729e-42"},
    {1.729e-41f, chars_format::scientific, "1.729e-41"},
    {1.729e-40f, chars_format::scientific, "1.729e-40"},
    {1.729e-39f, chars_format::scientific, "1.729e-39"},
    {1.729e-38f, chars_format::scientific, "1.729e-38"},
    {1.729e-37f, chars_format::scientific, "1.729e-37"},
    {1.729e-36f, chars_format::scientific, "1.729e-36"},
    {1.729e-35f, chars_format::scientific, "1.729e-35"},
    {1.729e-34f, chars_format::scientific, "1.729e-34"},
    {1.729e-33f, chars_format::scientific, "1.729e-33"},
    {1.729e-32f, chars_format::scientific, "1.729e-32"},
    {1.729e-31f, chars_format::scientific, "1.729e-31"},
    {1.729e-30f, chars_format::scientific, "1.729e-30"},
    {1.729e-29f, chars_format::scientific, "1.729e-29"},
    {1.729e-28f, chars_format::scientific, "1.729e-28"},
    {1.729e-27f, chars_format::scientific, "1.729e-27"},
    {1.729e-26f, chars_format::scientific, "1.729e-26"},
    {1.729e-25f, chars_format::scientific, "1.729e-25"},
    {1.729e-24f, chars_format::scientific, "1.729e-24"},
    {1.729e-23f, chars_format::scientific, "1.729e-23"},
    {1.729e-22f, chars_format::scientific, "1.729e-22"},
    {1.729e-21f, chars_format::scientific, "1.729e-21"},
    {1.729e-20f, chars_format::scientific, "1.729e-20"},
    {1.729e-19f, chars_format::scientific, "1.729e-19"},
    {1.729e-18f, chars_format::scientific, "1.729e-18"},
    {1.729e-17f, chars_format::scientific, "1.729e-17"},
    {1.729e-16f, chars_format::scientific, "1.729e-16"},
    {1.729e-15f, chars_format::scientific, "1.729e-15"},
    {1.729e-14f, chars_format::scientific, "1.729e-14"},
    {1.729e-13f, chars_format::scientific, "1.729e-13"},
    {1.729e-12f, chars_format::scientific, "1.729e-12"},
    {1.729e-11f, chars_format::scientific, "1.729e-11"},
    {1.729e-10f, chars_format::scientific, "1.729e-10"},
    {1.729e-9f, chars_format::scientific, "1.729e-09"},
    {1.729e-8f, chars_format::scientific, "1.729e-08"},
    {1.729e-7f, chars_format::scientific, "1.729e-07"},
    {1.729e-6f, chars_format::scientific, "1.729e-06"},
    {1.729e-5f, chars_format::scientific, "1.729e-05"},
    {1.729e-4f, chars_format::scientific, "1.729e-04"},
    {1.729e-3f, chars_format::scientific, "1.729e-03"},
    {1.729e-2f, chars_format::scientific, "1.729e-02"},
    {1.729e-1f, chars_format::scientific, "1.729e-01"},
    {1.729e0f, chars_format::scientific, "1.729e+00"},
    {1.729e1f, chars_format::scientific, "1.729e+01"},
    {1.729e2f, chars_format::scientific, "1.729e+02"},
    {1.729e3f, chars_format::scientific, "1.729e+03"},
    {1.729e4f, chars_format::scientific, "1.729e+04"},
    {1.729e5f, chars_format::scientific, "1.729e+05"},
    {1.729e6f, chars_format::scientific, "1.729e+06"},
    {1.729e7f, chars_format::scientific, "1.729e+07"},
    {1.729e8f, chars_format::scientific, "1.729e+08"},
    {1.729e9f, chars_format::scientific, "1.729e+09"},
    {1.729e10f, chars_format::scientific, "1.729e+10"},
    {1.729e11f, chars_format::scientific, "1.729e+11"},
    {1.729e12f, chars_format::scientific, "1.729e+12"},
    {1.729e13f, chars_format::scientific, "1.729e+13"},
    {1.729e14f, chars_format::scientific, "1.729e+14"},
    {1.729e15f, chars_format::scientific, "1.729e+15"},
    {1.729e16f, chars_format::scientific, "1.729e+16"},
    {1.729e17f, chars_format::scientific, "1.729e+17"},
    {1.729e18f, chars_format::scientific, "1.729e+18"},
    {1.729e19f, chars_format::scientific, "1.729e+19"},
    {1.729e20f, chars_format::scientific, "1.729e+20"},
    {1.729e21f, chars_format::scientific, "1.729e+21"},
    {1.729e22f, chars_format::scientific, "1.729e+22"},
    {1.729e23f, chars_format::scientific, "1.729e+23"},
    {1.729e24f, chars_format::scientific, "1.729e+24"},
    {1.729e25f, chars_format::scientific, "1.729e+25"},
    {1.729e26f, chars_format::scientific, "1.729e+26"},
    {1.729e27f, chars_format::scientific, "1.729e+27"},
    {1.729e28f, chars_format::scientific, "1.729e+28"},
    {1.729e29f, chars_format::scientific, "1.729e+29"},
    {1.729e30f, chars_format::scientific, "1.729e+30"},
    {1.729e31f, chars_format::scientific, "1.729e+31"},
    {1.729e32f, chars_format::scientific, "1.729e+32"},
    {1.729e33f, chars_format::scientific, "1.729e+33"},
    {1.729e34f, chars_format::scientific, "1.729e+34"},
    {1.729e35f, chars_format::scientific, "1.729e+35"},
    {1.729e36f, chars_format::scientific, "1.729e+36"},
    {1.729e37f, chars_format::scientific, "1.729e+37"},
    {1.729e38f, chars_format::scientific, "1.729e+38"},

    // Test all of the cases for fixed notation, including the non-Ryu fallback for large integers.
    {1.729e-4f, chars_format::fixed, "0.0001729"},
    {1.729e-3f, chars_format::fixed, "0.001729"},
    {1.729e-2f, chars_format::fixed, "0.01729"},
    {1.729e-1f, chars_format::fixed, "0.1729"},
    {1.729e0f, chars_format::fixed, "1.729"},
    {1.729e1f, chars_format::fixed, "17.29"},
    {1.729e2f, chars_format::fixed, "172.9"},
    {1.729e3f, chars_format::fixed, "1729"},
    {1.729e4f, chars_format::fixed, "17290"},
    {1.729e5f, chars_format::fixed, "172900"},
    {1.729e6f, chars_format::fixed, "1729000"},
    {1.729e7f, chars_format::fixed, "17290000"},
    {1.729e8f, chars_format::fixed, "172900000"},
    {1.729e9f, chars_format::fixed, "1728999936"},
    {1.729e10f, chars_format::fixed, "17290000384"},
    {1.729e11f, chars_format::fixed, "172900007936"},
    {1.729e12f, chars_format::fixed, "1728999981056"},
    {1.729e13f, chars_format::fixed, "17290000072704"},
    {1.729e14f, chars_format::fixed, "172899998629888"},
    {1.729e15f, chars_format::fixed, "1729000019853312"},
    {1.729e16f, chars_format::fixed, "17289999661662208"},
    {1.729e17f, chars_format::fixed, "172900007354040320"},
    {1.729e18f, chars_format::fixed, "1729000039180664832"},
    {1.729e19f, chars_format::fixed, "17289999567172927488"},
    {1.729e20f, chars_format::fixed, "172899997870752530432"},
    {1.729e21f, chars_format::fixed, "1729000013891897393152"},
    {1.729e22f, chars_format::fixed, "17290000138918973931520"},
    {1.729e23f, chars_format::fixed, "172899999137389925629952"},
    {1.729e24f, chars_format::fixed, "1729000063431493294227456"},
    {1.729e25f, chars_format::fixed, "17289999481393428335427584"},
    {1.729e26f, chars_format::fixed, "172900004037306320209051648"},
    {1.729e27f, chars_format::fixed, "1729000040373063202090516480"},
    {1.729e28f, chars_format::fixed, "17290000403730632020905164800"},
    {1.729e29f, chars_format::fixed, "172900004037306320209051648000"},
    {1.729e30f, chars_format::fixed, "1728999964815199476176193060864"},
    {1.729e31f, chars_format::fixed, "17290000252614904569076517961728"},
    {1.729e32f, chars_format::fixed, "172899990436890849544473432555520"},
    {1.729e33f, chars_format::fixed, "1729000059111413406117268687945728"},
    {1.729e34f, chars_format::fixed, "17290000281629124239827618154676224"},
    {1.729e35f, chars_format::fixed, "172899995388651006685994532152016896"},
    {1.729e36f, chars_format::fixed, "1728999993500591323992114118292144128"},
    {1.729e37f, chars_format::fixed, "17289999935005913239921141182921441280"},
    {1.729e38f, chars_format::fixed, "172899996814757931942752608835808002048"},

    // Also test one-digit cases, where the decimal point can't appear between digits like "17.29".
    {7e-3f, chars_format::fixed, "0.007"},
    {7e-2f, chars_format::fixed, "0.07"},
    {7e-1f, chars_format::fixed, "0.7"},
    {7e0f, chars_format::fixed, "7"},
    {7e1f, chars_format::fixed, "70"},
    {7e2f, chars_format::fixed, "700"},
    {7e3f, chars_format::fixed, "7000"},

    // Test the maximum value in fixed notation.
    {0x1.fffffep+127f, chars_format::fixed, "340282346638528859811704183484516925440"},

    // Test highly-trimmed powers of 2.
    {0x1p118f, chars_format::fixed, "332306998946228968225951765070086144"},
    {0x1p118f, chars_format::scientific, "3.32307e+35"},
    {0x1p119f, chars_format::fixed, "664613997892457936451903530140172288"},
    {0x1p119f, chars_format::scientific, "6.64614e+35"},

    // Test powers of 10 that are exactly representable.
    {1e0f, chars_format::fixed, "1"},
    {1e1f, chars_format::fixed, "10"},
    {1e2f, chars_format::fixed, "100"},
    {1e3f, chars_format::fixed, "1000"},
    {1e4f, chars_format::fixed, "10000"},
    {1e5f, chars_format::fixed, "100000"},
    {1e6f, chars_format::fixed, "1000000"},
    {1e7f, chars_format::fixed, "10000000"},
    {1e8f, chars_format::fixed, "100000000"},
    {1e9f, chars_format::fixed, "1000000000"},
    {1e10f, chars_format::fixed, "10000000000"},

    // Test powers of 10 that aren't exactly representable.
    // This exercises the "adjustment" code.
    {1e11f, chars_format::fixed, "99999997952"},
    {1e12f, chars_format::fixed, "999999995904"},
    {1e13f, chars_format::fixed, "9999999827968"},
    {1e14f, chars_format::fixed, "100000000376832"},
    {1e15f, chars_format::fixed, "999999986991104"},
    {1e16f, chars_format::fixed, "10000000272564224"},
    {1e17f, chars_format::fixed, "99999998430674944"},
    {1e18f, chars_format::fixed, "999999984306749440"},
    {1e19f, chars_format::fixed, "9999999980506447872"},
    {1e20f, chars_format::fixed, "100000002004087734272"},
    {1e21f, chars_format::fixed, "1000000020040877342720"},
    {1e22f, chars_format::fixed, "9999999778196308361216"},
    {1e23f, chars_format::fixed, "99999997781963083612160"},
    {1e24f, chars_format::fixed, "1000000013848427855085568"},
    {1e25f, chars_format::fixed, "9999999562023526247432192"},
    {1e26f, chars_format::fixed, "100000002537764290115403776"},
    {1e27f, chars_format::fixed, "999999988484154753734934528"},
    {1e28f, chars_format::fixed, "9999999442119689768320106496"},
    {1e29f, chars_format::fixed, "100000001504746621987668885504"},
    {1e30f, chars_format::fixed, "1000000015047466219876688855040"},
    {1e31f, chars_format::fixed, "9999999848243207295109594873856"},
    {1e32f, chars_format::fixed, "100000003318135351409612647563264"},
    {1e33f, chars_format::fixed, "999999994495727286427992885035008"},
    {1e34f, chars_format::fixed, "9999999790214767953607394487959552"},
    {1e35f, chars_format::fixed, "100000004091847875962975319375216640"},
    {1e36f, chars_format::fixed, "999999961690316245365415600208216064"},
    {1e37f, chars_format::fixed, "9999999933815812510711506376257961984"},
    {1e38f, chars_format::fixed, "99999996802856924650656260769173209088"},

    // These numbers have odd mantissas (unaffected by shifting)
    // that are barely within the "max shifted mantissa" limit.
    // They're exactly-representable multiples of powers of 10, and can use Ryu with zero-filling.
    {3355443e1f, chars_format::fixed, "33554430"},
    {671087e2f, chars_format::fixed, "67108700"},
    {134217e3f, chars_format::fixed, "134217000"},
    {26843e4f, chars_format::fixed, "268430000"},
    {5367e5f, chars_format::fixed, "536700000"},
    {1073e6f, chars_format::fixed, "1073000000"},
    {213e7f, chars_format::fixed, "2130000000"},
    {41e8f, chars_format::fixed, "4100000000"},
    {7e9f, chars_format::fixed, "7000000000"},
    {1e10f, chars_format::fixed, "10000000000"},

    // These numbers have odd mantissas (unaffected by shifting)
    // that are barely above the "max shifted mantissa" limit.
    // This activates the non-Ryu fallback for large integers.
    {3355445e1f, chars_format::fixed, "33554448"},
    {671089e2f, chars_format::fixed, "67108896"},
    {134219e3f, chars_format::fixed, "134219008"},
    {26845e4f, chars_format::fixed, "268449984"},
    {5369e5f, chars_format::fixed, "536899968"},
    {1075e6f, chars_format::fixed, "1075000064"},
    {215e7f, chars_format::fixed, "2150000128"},
    {43e8f, chars_format::fixed, "4300000256"},
    {9e9f, chars_format::fixed, "8999999488"},
    {3e10f, chars_format::fixed, "30000001024"},

    // Test the mantissa shifting logic.
    {5495808e5f, chars_format::fixed, "549580800000"}, // 5367 * 2^10
    {5497856e5f, chars_format::fixed, "549785567232"}, // 5369 * 2^10

    // Inspect all of those numbers in scientific notation.
    // For the within-limit numbers, this verifies that Ryu is actually being used with zero-filling above.
    // For the above-limit numbers, this tests Ryu's trimming.
    {3355443e1f, chars_format::scientific, "3.355443e+07"},
    {671087e2f, chars_format::scientific, "6.71087e+07"},
    {134217e3f, chars_format::scientific, "1.34217e+08"},
    {26843e4f, chars_format::scientific, "2.6843e+08"},
    {5367e5f, chars_format::scientific, "5.367e+08"},
    {1073e6f, chars_format::scientific, "1.073e+09"},
    {213e7f, chars_format::scientific, "2.13e+09"},
    {41e8f, chars_format::scientific, "4.1e+09"},
    {7e9f, chars_format::scientific, "7e+09"},
    {1e10f, chars_format::scientific, "1e+10"},
    {3355445e1f, chars_format::scientific, "3.355445e+07"},
    {671089e2f, chars_format::scientific, "6.71089e+07"},
    {134219e3f, chars_format::scientific, "1.34219e+08"},
    {26845e4f, chars_format::scientific, "2.6845e+08"},
    {5369e5f, chars_format::scientific, "5.369e+08"},
    {1075e6f, chars_format::scientific, "1.075e+09"},
    {215e7f, chars_format::scientific, "2.15e+09"},
    {43e8f, chars_format::scientific, "4.3e+09"},
    {9e9f, chars_format::scientific, "9e+09"},
    {3e10f, chars_format::scientific, "3e+10"},
    {5495808e5f, chars_format::scientific, "5.495808e+11"},
    {5497856e5f, chars_format::scientific, "5.497856e+11"},

    // Test the switching logic of chars_format::general.
    // C11 7.21.6.1 "The fprintf function"/8:
    // "Let P equal [...] 6 if the precision is omitted [...].
    // Then, if a conversion with style E would have an exponent of X:
    // - if P > X >= -4, the conversion is with style f [...].
    // - otherwise, the conversion is with style e [...]."
    {1e-6f, chars_format::general, "1e-06"},
    {1e-5f, chars_format::general, "1e-05"},
    {1e-4f, chars_format::general, "0.0001"},
    {1e-3f, chars_format::general, "0.001"},
    {1e-2f, chars_format::general, "0.01"},
    {1e-1f, chars_format::general, "0.1"},
    {1e0f, chars_format::general, "1"},
    {1e1f, chars_format::general, "10"},
    {1e2f, chars_format::general, "100"},
    {1e3f, chars_format::general, "1000"},
    {1e4f, chars_format::general, "10000"},
    {1e5f, chars_format::general, "100000"},
    {1e6f, chars_format::general, "1e+06"},
    {1e7f, chars_format::general, "1e+07"},
    {1.234e-6f, chars_format::general, "1.234e-06"},
    {1.234e-5f, chars_format::general, "1.234e-05"},
    {1.234e-4f, chars_format::general, "0.0001234"},
    {1.234e-3f, chars_format::general, "0.001234"},
    {1.234e-2f, chars_format::general, "0.01234"},
    {1.234e-1f, chars_format::general, "0.1234"},
    {1.234e0f, chars_format::general, "1.234"},
    {1.234e1f, chars_format::general, "12.34"},
    {1.234e2f, chars_format::general, "123.4"},
    {1.234e3f, chars_format::general, "1234"},
    {1.234e4f, chars_format::general, "12340"},
    {1.234e5f, chars_format::general, "123400"},
    {1.234e6f, chars_format::general, "1.234e+06"},
    {1.234e7f, chars_format::general, "1.234e+07"},
    {1.234e8f, chars_format::general, "1.234e+08"},
    {1.234e9f, chars_format::general, "1.234e+09"},
    {1.234e10f, chars_format::general, "1.234e+10"},

    // Test the switching logic of the plain overload.
    // N4762 19.19.2 [charconv.to.chars]/8:
    // "The conversion specifier is f or e, chosen according to the requirement
    // for a shortest representation (see above); a tie is resolved in favor of f."
    {1e-6f, chars_format{}, "1e-06"},
    {1e-5f, chars_format{}, "1e-05"},
    {1e-4f, chars_format{}, "1e-04"},
    {1e-3f, chars_format{}, "0.001"},
    {1e-2f, chars_format{}, "0.01"},
    {1e-1f, chars_format{}, "0.1"},
    {1e0f, chars_format{}, "1"},
    {1e1f, chars_format{}, "10"},
    {1e2f, chars_format{}, "100"},
    {1e3f, chars_format{}, "1000"},
    {1e4f, chars_format{}, "10000"},
    {1e5f, chars_format{}, "1e+05"},
    {1e6f, chars_format{}, "1e+06"},
    {1e7f, chars_format{}, "1e+07"},
    {1.234e-6f, chars_format{}, "1.234e-06"},
    {1.234e-5f, chars_format{}, "1.234e-05"},
    {1.234e-4f, chars_format{}, "0.0001234"},
    {1.234e-3f, chars_format{}, "0.001234"},
    {1.234e-2f, chars_format{}, "0.01234"},
    {1.234e-1f, chars_format{}, "0.1234"},
    {1.234e0f, chars_format{}, "1.234"},
    {1.234e1f, chars_format{}, "12.34"},
    {1.234e2f, chars_format{}, "123.4"},
    {1.234e3f, chars_format{}, "1234"},
    {1.234e4f, chars_format{}, "12340"},
    {1.234e5f, chars_format{}, "123400"},
    {1.234e6f, chars_format{}, "1234000"},
    {1.234e7f, chars_format{}, "12340000"},
    {1.234e8f, chars_format{}, "123400000"},
    {1.234e9f, chars_format{}, "1.234e+09"},
    {1.234e10f, chars_format{}, "1.234e+10"},

    // Test hexfloat corner cases.
    {0x1.728p+0f, chars_format::hex, "1.728p+0"}, // instead of "2.e5p-1"
    {0x0.000002p-126f, chars_format::hex, "0.000002p-126"}, // instead of "1p-149", min subnormal
    {0x0.fffffep-126f, chars_format::hex, "0.fffffep-126"}, // max subnormal
    {0x1p-126f, chars_format::hex, "1p-126"}, // min normal
    {0x1.fffffep+127f, chars_format::hex, "1.fffffep+127"}, // max normal

    // Test hexfloat exponents.
    {0x1p-109f, chars_format::hex, "1p-109"},
    {0x1p-99f, chars_format::hex, "1p-99"},
    {0x1p-9f, chars_format::hex, "1p-9"},
    {0x1p+0f, chars_format::hex, "1p+0"},
    {0x1p+9f, chars_format::hex, "1p+9"},
    {0x1p+99f, chars_format::hex, "1p+99"},
    {0x1p+109f, chars_format::hex, "1p+109"},

    // Test hexfloat hexits.
    {0x1.0123p+0f, chars_format::hex, "1.0123p+0"},
    {0x1.4567p+0f, chars_format::hex, "1.4567p+0"},
    {0x1.89abp+0f, chars_format::hex, "1.89abp+0"},
    {0x1.cdefp+0f, chars_format::hex, "1.cdefp+0"},

    // Test hexfloat trimming.
    {0x1.00000ap+0f, chars_format::hex, "1.00000ap+0"},
    {0x1.0000ap+0f, chars_format::hex, "1.0000ap+0"},
    {0x1.000ap+0f, chars_format::hex, "1.000ap+0"},
    {0x1.00ap+0f, chars_format::hex, "1.00ap+0"},
    {0x1.0ap+0f, chars_format::hex, "1.0ap+0"},
    {0x1.ap+0f, chars_format::hex, "1.ap+0"},
    {0x1p+0f, chars_format::hex, "1p+0"},

    // https://www.exploringbinary.com/the-shortest-decimal-string-that-round-trips-may-not-be-the-nearest/
    // This is an exhaustive list of anomalous values.
    // (See double_to_chars_test_cases.hpp for more details.)
    {0x1p90f, chars_format::scientific, "1.2379401e+27"},
    {0x1p87f, chars_format::scientific, "1.5474251e+26"},
    {0x1p-96f, chars_format::scientific, "1.2621775e-29"},
};