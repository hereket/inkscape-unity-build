// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Authors:
 *   Christopher Brown <audiere@gmail.com>
 *   Ted Gould <ted@gould.cx>
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#ifndef __EXTENSION_INTERNAL_BITMAP_ADDNOISE_H__
#define __EXTENSION_INTERNAL_BITMAP_ADDNOISE_H__
#ifndef __EXTENSIONS_INTERNAL_BITMAP_ADDNOISE__
#define __EXTENSIONS_INTERNAL_BITMAP_ADDNOISE__

#include "imagemagick.h"

namespace Inkscape {
namespace Extension {
namespace Internal {
namespace Bitmap {

class AddNoise : public ImageMagick
{
private:
	const gchar* _noiseTypeName;
public:
    void applyEffect(Magick::Image *image) override;
	void refreshParameters(Inkscape::Extension::Effect *module) override;
    static void init ();
};

}; /* namespace Bitmap */
}; /* namespace Internal */
}; /* namespace Extension */
}; /* namespace Inkscape */


#endif

#endif
