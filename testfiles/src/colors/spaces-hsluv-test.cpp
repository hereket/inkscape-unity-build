// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Unit tests for the HSLuv color space
 *
 * Copyright (C) 2023 Authors
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#include "spaces-testbase.h"

namespace {

using Space::Type::HSLUV;
using Space::Type::RGB;
using Space::Type::LUV;

// clang-format off
// There is no CSS string for HSLuv colors
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(fromString);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(badColorString);
GTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(toString);

INSTANTIATE_TEST_SUITE_P(ColorsSpacesHSLuv, convertColorSpace, testing::Values(
    // No conversion
    _P(inb, HSLUV, {1.000, 0.400, 0.200}, HSLUV, {1.000, 0.400, 0.200}),
    // Generated by hsluv.org a sample of low and high saturation hues
    _P(inb, HSLUV, {0.946, 0.182, 0.500}, RGB,   {0.565, 0.431, 0.490}),
    _P(inb, HSLUV, {0.016, 0.723, 0.500}, RGB,   {0.835, 0.247, 0.349}),
    _P(inb, HSLUV, {0.760, 0.787, 0.500}, RGB,   {0.517, 0.372, 0.878}),
    _P(inb, HSLUV, {0.748, 0.768, 0.232}, RGB,   {0.207, 0.137, 0.549}),
    _P(inb, HSLUV, {0.018, 0.752, 0.232}, RGB,   {0.415, 0.094, 0.149}),
    _P(inb, HSLUV, {0.358, 0.454, 0.232}, RGB,   {0.149, 0.239, 0.152}),
    _P(inb, HSLUV, {0.344, 0.821, 0.848}, RGB,   {0.458, 0.933, 0.352}),
    _P(inb, HSLUV, {0.874, 0.526, 0.848}, RGB,   {0.921, 0.792, 0.901}),
    _P(inb, HSLUV, {0.205, 0.788, 0.848}, RGB,   {0.921, 0.831, 0.384})
));

INSTANTIATE_TEST_SUITE_P(ColorsSpacesHSLuv, normalize, testing::Values(
    _P(inb, HSLUV, { 0.5,   0.5,   0.5,   0.5  }, HSLUV, { 0.5,   0.5,   0.5,   0.5  }),
    _P(inb, HSLUV, { 1.2,   1.2,   1.2,   1.2  }, HSLUV, { 0.2,   1.0,   1.0,   1.0  }),
    _P(inb, HSLUV, {-0.2,  -0.2,  -0.2,  -0.2  }, HSLUV, { 0.8,   0.0,   0.0,   0.0  }),
    _P(inb, HSLUV, { 0.0,   0.0,   0.0,   0.0  }, HSLUV, { 0.0,   0.0,   0.0,   0.0  }),
    _P(inb, HSLUV, { 1.0,   1.0,   1.0,   1.0  }, HSLUV, { 1.0,   1.0,   1.0,   1.0  })
));
// clang-format on

TEST(ColorsSpacesHSLuv, randomConversion)
{
    EXPECT_TRUE(RandomPassthrough(HSLUV, RGB, 1000));
}

TEST(ColorsSpacesHSLuv, components)
{
    auto c = Manager::get().find(HSLUV)->getComponents();
    ASSERT_EQ(c.size(), 3);
    ASSERT_EQ(c[0].id, "h");
    ASSERT_EQ(c[1].id, "s");
    ASSERT_EQ(c[2].id, "l");
}

} // namespace

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
