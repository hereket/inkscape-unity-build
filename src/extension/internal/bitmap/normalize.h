// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Authors:
 *   Christopher Brown <audiere@gmail.com>
 *   Ted Gould <ted@gould.cx>
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#ifndef __EXTENSION_INTERNAL_BITMAP_NORMALIZE_H__
#define __EXTENSION_INTERNAL_BITMAP_NORMALIZE_H__
#include "imagemagick.h"

namespace Inkscape {
namespace Extension {
namespace Internal {
namespace Bitmap {

class Normalize : public ImageMagick
{
public:
  void applyEffect(Magick::Image *image) override;
  void refreshParameters(Inkscape::Extension::Effect *module) override;
  static void init();
};

}; /* namespace Bitmap */
}; /* namespace Internal */
}; /* namespace Extension */
}; /* namespace Inkscape */

#endif
