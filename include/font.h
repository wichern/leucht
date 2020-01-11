/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Paul Wichern
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __LEUCHT_FONT_H__
#define __LEUCHT_FONT_H__

//==============================================================================

//==============================================================================

namespace font {

struct Char {
  bool bitmask[5][5];
  int width;
};

namespace simple {

Char S_21 = { {
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { false, false, false, false, false },
    { true, false, false, false, false }
}, 1 };

Char S_22 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false }
}, 3 };

Char S_23 = { {
    { true, false, true, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_24 = { {
    { true, true, true, false, false },
    { true, true, false, false, false },
    { true, true, true, false, false },
    { false, true, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_25 = { {
    { true, false, false, false, false },
    { false, false, true, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false },
    { false, false, true, false, false }
}, 3 };

Char S_26 = { {
    { false, true, false, false, false },
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_27 = { {
    { true, false, false, false, false },
    { true, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false }
}, 1 };

Char S_28 = { {
    { false, true, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { false, true, false, false, false }
}, 2 };

Char S_29 = { {
    { true, false, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false }
}, 2 };

Char S_2A = { {
    { false, true, false, false, false },
    { true, false, true, false, false },
    { false, true, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false }
}, 3};

Char S_2B = { {
    { false, false, false, false, false },
    { false, true, false, false, false },
    { true, true, true, false, false },
    { false, true, false , false, false},
    { false, false, false, false, false }
}, 3 };

Char S_2C = { {
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, true, false, false, false },
    { true, true, false, false, false }
}, 2 };

Char S_2D = { {
    { false, false, false, false, false },
    { false, false, false, false, false },
    { true, true, true, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false }
}, 3 };

Char S_2E = { {
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { true, false, false, false, false }
}, 1 };

Char S_2F = { {
    { false, false, true, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false }
}, 3 };

Char S_30 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_31 = { {
    { true, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_32 = { {
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_33 = { {
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_34 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { false, false, true, false, false }
}, 3 };

Char S_35 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_36 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_37 = { {
    { true, true, true, false, false },
    { false, false, true, false, false },
    { false, false, true, false, false },
    { false, false, true, false, false },
    { false, false, true, false, false }
}, 3 };

Char S_38 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_39 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_3A = { {
    { false, false, false, false, false },
    { true, false, false, false, false },
    { false, false, false, false, false },
    { true, false, false, false, false },
    { false, false, false, false, false }
}, 1 };

Char S_3B = { {
    { false, false, false, false, false },
    { false, true, false, false, false },
    { false, false, false, false, false },
    { false, true, false, false, false },
    { true, true, false, false, false }
}, 2 };

Char S_3C = { {
    { false, false, true, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false },
    { false, true, false, false, false },
    { false, false, true, false, false }
}, 3 };

Char S_3D = { {
    { false, false, false, false, false },
    { true, true, true, false, false },
    { false, false, false, false, false },
    { true, true, true, false, false },
    { false, false, false, false, false }
}, 3 };

Char S_3E = { {
    { true, false, false, false, false },
    { false, true, false, false, false },
    { false, false, true, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false }
}, 3 };

Char S_3F = { {
    { true, true, true, false, false },
    { false, false, true, false, false },
    { false, true, true, false, false },
    { false, false, false, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_40 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_41 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_42 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_43 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_44 = { {
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false }
}, 3 };

Char S_45 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_46 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false }
}, 3 };

Char S_47 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_48 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_49 = { {
    { true, true, true, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_4A = { {
    { false, false, true, false, false },
    { false, false, true, false, false },
    { false, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_4B = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_4C = { {
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_4D = { {
    { true, true, true, true, true },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, false, true, false, true }
}, 5 };

Char S_4E = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_4F = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_50 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false }
}, 3 };

Char S_51 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_52 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_53 = { {
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_54 = { {
    { true, true, true, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_55 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_56 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_57 = { {
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, true, true, true, true }
}, 5 };

Char S_58 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_59 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_5A = { {
    { true, true, true, false, false },
    { false, false, true, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_5B = { {
    { true, true, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, true, false, false, false }
}, 2 };

Char S_5C = { {
    { true, false, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, false, true, false, false }
}, 3 };

Char S_5D = { {
    { true, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { true, true, false, false, false }
}, 2 };

Char S_5E = { {
    { false, true, false, false, false },
    { true, false, true, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false }
}, 3 };

Char S_5F = { {
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_60 = { {
    { true, false, false, false, false },
    { false, true, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false },
    { false, false, false, false, false }
}, 2 };

Char S_61 = { {
    { false, false, false, false, false },
    { false, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, true, true, false, false }
}, 3 };

Char S_62 = { {
    { true, false, false, false, false },
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false }
}, 3 };

Char S_63 = { {
    { false, false, false, false, false },
    { true, true, true, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_64 = { {
    { false, false, true, false, false },
    { false, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, true, true, false, false }
}, 3 };

Char S_65 = { {
    { false, false, false, false, false },
    { false, true, false, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false },
    { false, true, true, false, false }
}, 3 };

Char S_66 = { {
    { false, true, true, false, false },
    { false, true, false, false, false },
    { true, true, true, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_67 = { {
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, false, false, false }
}, 3 };

Char S_68 = { {
    { true, false, false, false, false },
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_69 = { {
    { true, false, false, false, false },
    { false, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false }
}, 1 };

Char S_6A = { {
    { false, true, false, false, false },
    { false, false, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { true, false, false, false, false }
}, 2 };

Char S_6B = { {
    { true, false, false, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_6C = { {
    { true, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false }
}, 2 };

Char S_6D = { {
    { false, false, false, false, false },
    { true, true, true, true, true },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, false, true, false, true }
}, 5 };

Char S_6E = { {
    { false, false, false, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_6F = { {
    { false, false, false, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_70 = { {
    { true, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, false, false, false },
    { true, false, false, false, false }
}, 3 };

Char S_71 = { {
    { false, true, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, true, true, false, false },
    { false, false, true, false, false }
}, 3 };

Char S_72 = { {
    { false, false, false, false, false },
    { true, true, true, false, false },
    { true, false, true, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false }
}, 3 };

Char S_73 = { {
    { false, false, false, false, false },
    { false, true, true, false, false },
    { true, false, false, false, false },
    { false, false, true, false, false },
    { true, true, false, false, false }
}, 3 };

Char S_74 = { {
    { false, true, false, false, false },
    { true, true, true, false, false },
    { false, true, false, false, false },
    { false, true, false, false, false },
    { false, true, true, false, false }
}, 3 };

Char S_75 = { {
    { false, false, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false }
}, 3 };

Char S_76 = { {
    { false, false, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false },
    { false, true, false, false, false }
}, 3 };

Char S_77 = { {
    { false, false, false, false, false },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, false, true, false, true },
    { true, true, true, true, true }
}, 5 };

Char S_78 = { {
    { false, false, false, false, false },
    { true, false, true, false, false },
    { false, true, false, false, false },
    { true, false, true, false, false },
    { true, false, true, false, false }
}, 3 };

Char S_79 = { {
    { true, false, true, false, false },
    { true, false, true, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, true, false, false, false }
}, 3 };

Char S_7A = { {
    { false, false, false, false, false },
    { true, true, true, false, false },
    { false, false, true, false, false },
    { true, false, false, false, false },
    { false, true, true, false, false }
}, 3 };

Char S_7B = { {
    { false, true, true, false, false },
    { false, true, false, false, false },
    { true, true, false, false, false },
    { false, true, false, false, false },
    { false, true, true, false, false }
}, 3 };

Char S_7C = { {
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false },
    { true, false, false, false, false }
}, 1 };

Char S_7D = { {
    { true, true, false, false, false },
    { false, true, false, false, false },
    { false, true, true, false, false },
    { false, true, false, false, false },
    { true, true, false, false, false }
}, 3 };

//==============================================================================

Char S_ascii_table[93] = {
    S_21,
    S_22,
    S_23,
    S_24,
    S_25,
    S_26,
    S_27,
    S_28,
    S_29,
    S_2A,
    S_2B,
    S_2C,
    S_2D,
    S_2E,
    S_2F,
    S_30,
    S_31,
    S_32,
    S_33,
    S_34,
    S_35,
    S_36,
    S_37,
    S_38,
    S_39,
    S_3A,
    S_3B,
    S_3C,
    S_3D,
    S_3E,
    S_3F,
    S_40,
    S_41,
    S_42,
    S_43,
    S_44,
    S_45,
    S_46,
    S_47,
    S_48,
    S_49,
    S_4A,
    S_4B,
    S_4C,
    S_4D,
    S_4E,
    S_4F,
    S_50,
    S_51,
    S_52,
    S_53,
    S_54,
    S_55,
    S_56,
    S_57,
    S_58,
    S_59,
    S_5A,
    S_5B,
    S_5C,
    S_5D,
    S_5E,
    S_5F,
    S_60,
    S_61,
    S_62,
    S_63,
    S_64,
    S_65,
    S_66,
    S_67,
    S_68,
    S_69,
    S_6A,
    S_6B,
    S_6C,
    S_6D,
    S_6E,
    S_6F,
    S_70,
    S_71,
    S_72,
    S_73,
    S_74,
    S_75,
    S_76,
    S_77,
    S_78,
    S_79,
    S_7A,
    S_7B,
    S_7C,
    S_7D
};

}  // namespace simple
}  // namespace font

//==============================================================================

#endif // LFONT_H_
