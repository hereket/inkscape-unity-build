// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Manages external resources such as image and css files.
 *
 * Copyright 2011  Jon A. Cruz  <jon@joncruz.org>
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */

#ifndef __IO_FIX_BROKEN_LINKS_H__
#define __IO_FIX_BROKEN_LINKS_H__

#include <string>

class SPDocument;

namespace Inkscape {

std::string optimizePath(std::string const &path, std::string const &base, unsigned int parents = 2);
bool fixBrokenLinks(SPDocument *doc);

}

#endif

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
