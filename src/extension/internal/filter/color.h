// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef SEEN_INKSCAPE_EXTENSION_INTERNAL_FILTER_COLOR_H__
#define SEEN_INKSCAPE_EXTENSION_INTERNAL_FILTER_COLOR_H__
/* Change the 'COLOR' above to be your file name */

/*
 * Copyright (C) 2013-2015 Authors:
 *   Ivan Louette (filters)
 *   Nicolas Dufour (UI) <nicoduf@yahoo.fr>
 *
 * Color filters
 *   Brilliance
 *   Channel painting
 *   Color blindness
 *   Color shift
 *   Colorize
 *   Component transfer
 *   Duochrome
 *   Extract channel
 *   Fade to black or white
 *   Greyscale
 *   Invert
 *   Lighting
 *   Lightness-contrast
 *   Nudge RGB
 *   Nudge CMY
 *   Quadritone
 *   Simple blend
 *   Solarize
 *   Tritone
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information.
 */
/* ^^^ Change the copyright to be you and your e-mail address ^^^ */

#include "filter.h"

#include "extension/internal/clear-n_.h"
#include "extension/system.h"
#include "extension/extension.h"

namespace Inkscape {
namespace Extension {
namespace Internal {
namespace Filter {

/**
    \brief    Custom predefined Brilliance filter.
    
    Brilliance filter.

    Filter's parameters:
    * Brilliance (1.->10., default 2.) -> colorMatrix (RVB entries)
    * Over-saturation (0.->10., default 0.5) -> colorMatrix (6 other entries)
    * Lightness (-10.->10., default 0.) -> colorMatrix (last column)
    * Inverted (boolean, default false) -> colorMatrix
    
    Matrix:
      St Vi Vi 0  Li
      Vi St Vi 0  Li
      Vi Vi St 0  Li
      0  0  0  1  0
*/
class Brilliance : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Brilliance ( ) : Filter() { };
    ~Brilliance ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Brilliance") "</name>\n"
              "<id>org.inkscape.effect.filter.Brilliance</id>\n"
              "<param name=\"brightness\" gui-text=\"" N_("Brightness") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"1\" max=\"10.00\">2</param>\n"
              "<param name=\"sat\" gui-text=\"" N_("Over-saturation") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0.0\" max=\"10.00\">0.5</param>\n"
              "<param name=\"lightness\" gui-text=\"" N_("Lightness") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.00\" max=\"10.00\">0</param>\n"
              "<param name=\"invert\" gui-text=\"" N_("Inverted") "\" type=\"bool\">false</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Brightness filter") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Brilliance>());
        // clang-format on
    };
};

gchar const *
Brilliance::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream brightness;
    std::ostringstream sat;
    std::ostringstream lightness;

    if (ext->get_param_bool("invert")) {
        brightness << -ext->get_param_float("brightness");
        sat << 1 + ext->get_param_float("sat");
        lightness << -ext->get_param_float("lightness");
    } else {
        brightness << ext->get_param_float("brightness");
        sat << -ext->get_param_float("sat");
        lightness << ext->get_param_float("lightness");
    }

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Brilliance\">\n"
          "<feColorMatrix values=\"%s %s %s 0 %s %s %s %s 0 %s %s %s %s 0 %s 0 0 0 1 0 \" />\n"
        "</filter>\n", brightness.str().c_str(), sat.str().c_str(), sat.str().c_str(),
                       lightness.str().c_str(), sat.str().c_str(), brightness.str().c_str(),
                       sat.str().c_str(), lightness.str().c_str(), sat.str().c_str(),
                       sat.str().c_str(), brightness.str().c_str(), lightness.str().c_str() );
    // clang-format on

    return _filter;
}; /* Brilliance filter */

/**
    \brief    Custom predefined Channel Painting filter.
    
    Channel Painting filter.

    Filter's parameters:
    * Saturation (0.->1., default 1.) -> colormatrix1 (values)
    * Red (-10.->10., default -1.) -> colormatrix2 (values)
    * Green (-10.->10., default 0.5) -> colormatrix2 (values)
    * Blue (-10.->10., default 0.5) -> colormatrix2 (values)
    * Alpha (-10.->10., default 1.) -> colormatrix2 (values)
    * Flood colors (guint, default 16777215) -> flood (flood-opacity, flood-color)
    * Inverted (boolean, default false) -> composite1 (operator, true='in', false='out')
    
    Matrix:
      1  0  0  0  0
      0  1  0  0  0
      0  0  1  0  0
      R  G  B  A  0
*/
class ChannelPaint : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    ChannelPaint ( ) : Filter() { };
    ~ChannelPaint ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }
    
    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Channel Painting") "</name>\n"
              "<id>org.inkscape.effect.filter.ChannelPaint</id>\n"
                "<param name=\"tab\" type=\"notebook\">\n"
                  "<page name=\"optionstab\" gui-text=\"Options\">\n"
                    "<param name=\"saturation\" gui-text=\"" N_("Saturation") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0.\" max=\"1.\">1</param>\n"
                    "<param name=\"red\" gui-text=\"" N_("Red") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.\" max=\"10.\">-1</param>\n"
                    "<param name=\"green\" gui-text=\"" N_("Green") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.\" max=\"10.\">0.5</param>\n"
                    "<param name=\"blue\" gui-text=\"" N_("Blue") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.\" max=\"10.\">0.5</param>\n"
                    "<param name=\"alpha\" gui-text=\"" N_("Alpha") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.\" max=\"10.\">1</param>\n"
                    "<param name=\"invert\" gui-text=\"" N_("Inverted") "\" type=\"bool\">false</param>\n"
                  "</page>\n"
                  "<page name=\"colortab\" gui-text=\"Color\">\n"
                    "<param name=\"color\" gui-text=\"" N_("Color") "\" type=\"color\">16777215</param>\n"
                  "</page>\n"
                "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Replace RGB by any color") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<ChannelPaint>());
        // clang-format on
    };
};

gchar const *
ChannelPaint::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream saturation;
    std::ostringstream red;
    std::ostringstream green;
    std::ostringstream blue;
    std::ostringstream alpha;
    std::ostringstream invert;

    saturation << ext->get_param_float("saturation");
    red << ext->get_param_float("red");
    green << ext->get_param_float("green");
    blue << ext->get_param_float("blue");
    alpha << ext->get_param_float("alpha");

    auto flood = ext->get_param_color("color");

    if (ext->get_param_bool("invert")) {
        invert << "in";
    } else {
        invert << "out";
    }
    
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Channel Painting\">\n"
          "<feColorMatrix values=\"%s\" type=\"saturate\" result=\"colormatrix1\" />\n"
          "<feColorMatrix values=\"1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 %s %s %s %s 0 \" in=\"SourceGraphic\" result=\"colormatrix2\" />\n"
          "<feFlood flood-color=\"%s\" flood-opacity=\"%f\" result=\"flood\" />\n"
          "<feComposite in2=\"colormatrix2\" operator=\"%s\" result=\"composite1\" />\n"
          "<feMerge result=\"merge\">\n"
            "<feMergeNode in=\"colormatrix1\" />\n"
            "<feMergeNode in=\"composite1\" />\n"
          "</feMerge>\n"
          "<feComposite in=\"merge\" in2=\"SourceGraphic\" operator=\"in\" result=\"composite2\" />\n"
        "</filter>\n", saturation.str().c_str(), red.str().c_str(), green.str().c_str(),
                       blue.str().c_str(), alpha.str().c_str(),
                       flood.toString(false).c_str(), flood.getOpacity(),
                       invert.str().c_str() );
    // clang-format on

    return _filter;
}; /* Channel Painting filter */

/**
    \brief    Custom predefined Color Blindness filter.

    Color Blindness filter.
    Based on https://openclipart.org/detail/22299/Color%20Blindness%20filters
    
    Filter's parameters:
    * Blindness type (enum, default Achromatomaly) -> colormatrix
*/
class ColorBlindness : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    ColorBlindness ( ) : Filter() { };
    ~ColorBlindness ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }
    
    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Color Blindness") "</name>\n"
              "<id>org.inkscape.effect.filter.ColorBlindness</id>\n"
              "<param name=\"tab\" type=\"notebook\">\n"
                "<page name=\"optionstab\" gui-text=\"Options\">\n"
                  "<param name=\"type\" gui-text=\"" N_("Blindness type:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                    "<option value=\"0.618 0.32 0.062 0 0 0.163 0.775 0.062 0 0 0.163 0.32 0.516 0 0 0 0 0 1 0 \">" N_("Rod monochromacy (atypical achromatopsia)") "</option>\n"
                    "<option value=\"0.299 0.587 0.114 0 0 0.299 0.587 0.114 0 0 0.299 0.587 0.114 0 0 0 0 0 1 0 \">" N_("Cone monochromacy (typical achromatopsia)") "</option>\n"
                    "<option value=\"0.8 0.2 0 0 0 0.2583 0.74167 0 0 0 0 0.14167 0.85833 0 0 0 0 0 1 0 \">" N_("Green weak (deuteranomaly)") "</option>\n"
                    "<option value=\"0.625 0.375 0 0 0 0.7 0.3 0 0 0 0 0.3 0.7 0 0 0 0 0 1 0 \">" N_("Green blind (deuteranopia)") "</option>\n"
                    "<option value=\"0.8166 0.1833 0 0 0 0.333 0.666 0 0 0 0 0.125 0.875 0 0 0 0 0 1 0 \">" N_("Red weak (protanomaly)") "</option>\n"
                    "<option value=\"0.566 0.43333 0 0 0 0.55833 0.4416 0 0 0 0 0.24167 0.75833 0 0 0 0 0 1 0 \">" N_("Red blind (protanopia)") "</option>\n"
                    "<option value=\"0.966 0.033 0 0 0 0 0.733 0.266 0 0 0 0.1833 0.816 0 0 0 0 0 1 0 \">" N_("Blue weak (tritanomaly)") "</option>\n"
                    "<option value=\"0.95 0.05 0 0 0 0.2583 0.4333 0.5667 0 0 0 0.475 0.525 0 0 0 0 0 1 0 \">" N_("Blue blind (tritanopia)") "</option>\n"
                  "</param>\n"
                "</page>\n"
                "<page name=\"helptab\" gui-text=\"Help\">\n"
                  "<label xml:space=\"preserve\">\n"
"Filters based on https://openclipart.org/detail/22299/Color%20Blindness%20filters\n"
"\n"
"These filters don't correctly reflect actual color blindness for two main reasons:\n"
"  * Everyone is different, and is not affected exactly the same way.\n"
"  * The filters are in the RGB color space, and ignore confusion lines.\n"
                  "</label>\n"
                "</page>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Simulate color blindness") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<ColorBlindness>());
        // clang-format on
    };
};

gchar const *
ColorBlindness::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream type;
    type << ext->get_param_optiongroup("type");

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" height=\"1\" width=\"1\" y=\"0\" x=\"0\" inkscape:label=\"Color Blindness\">\n"
          "<feColorMatrix values=\"%s\" type=\"matrix\" result=\"colormatrix1\" />\n"
        "</filter>\n", type.str().c_str());
    // clang-format on

    return _filter;
}; /* Color Blindness filter */

/**
    \brief    Custom predefined Color shift filter.
    
    Rotate and desaturate hue

    Filter's parameters:
    * Shift (0->360, default 330) -> color1 (values)
    * Saturation (0.->1., default 0.6) -> color2 (values)
*/

class ColorShift : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    ColorShift ( ) : Filter() { };
    ~ColorShift ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Color Shift") "</name>\n"
              "<id>org.inkscape.effect.filter.ColorShift</id>\n"
              "<param name=\"shift\" gui-text=\"" N_("Shift (°)") "\" type=\"int\" appearance=\"full\" min=\"0\" max=\"360\">330</param>\n"
              "<param name=\"sat\" gui-text=\"" N_("Saturation") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0.\" max=\"1\">0.6</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Rotate and desaturate hue") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<ColorShift>());
        // clang-format on
    };

};

gchar const *
ColorShift::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream shift;
    std::ostringstream sat;

    shift << ext->get_param_int("shift");
    sat << ext->get_param_float("sat");

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Color Shift\">\n"
          "<feColorMatrix type=\"hueRotate\" values=\"%s\" result=\"color1\" />\n"
          "<feColorMatrix type=\"saturate\" values=\"%s\" result=\"color2\" />\n"
        "</filter>\n", shift.str().c_str(), sat.str().c_str() );
    // clang-format on

    return _filter;
}; /* ColorShift filter */

/**
    \brief    Custom predefined Colorize filter.
    
    Blend image or object with a flood color.

    Filter's parameters:
    * Harsh light (0.->10., default 0) -> composite1 (k1)
    * Normal light (0.->10., default 1) -> composite2 (k2)
    * Duotone (boolean, default false) -> colormatrix1 (values="0")
    * Filtered greys (boolean, default false) -> colormatrix2 (values="0")
    * Blend mode 1 (enum, default Multiply) -> blend1 (mode)
    * Blend mode 2 (enum, default Screen) -> blend2 (mode)
*/

class Colorize : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Colorize ( ) : Filter() { };
    ~Colorize ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
                "<name>" N_("Colorize") "</name>\n"
                "<id>org.inkscape.effect.filter.Colorize</id>\n"
                "<param name=\"tab\" type=\"notebook\">\n"
                  "<page name=\"optionstab\" gui-text=\"Options\">\n"
                    "<param name=\"hlight\" gui-text=\"" N_("Harsh light") "\" type=\"float\" appearance=\"full\" min=\"0\" max=\"10\">0</param>\n"
                    "<param name=\"nlight\" gui-text=\"" N_("Normal light") "\" type=\"float\" appearance=\"full\" min=\"0\" max=\"10\">1</param>\n"
                    "<param name=\"duotone\" gui-text=\"" N_("Duotone") "\" type=\"bool\" >false</param>\n"
                    "<param name=\"blend1\" gui-text=\"" N_("Blend 1:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                      "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                      "<option value=\"normal\">" N_("Normal") "</option>\n"
                      "<option value=\"screen\">" N_("Screen") "</option>\n"
                      "<option value=\"lighten\">" N_("Lighten") "</option>\n"
                      "<option value=\"darken\">" N_("Darken") "</option>\n"
                    "</param>\n"
                    "<param name=\"blend2\" gui-text=\"" N_("Blend 2:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                      "<option value=\"screen\">" N_("Screen") "</option>\n"
                      "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                      "<option value=\"normal\">" N_("Normal") "</option>\n"
                      "<option value=\"lighten\">" N_("Lighten") "</option>\n"
                      "<option value=\"darken\">" N_("Darken") "</option>\n"
                    "</param>\n"
                  "</page>\n"
                  "<page name=\"colortab\" gui-text=\"Color\">\n"
                    "<param name=\"color\" gui-text=\"" N_("Color") "\" type=\"color\">-1639776001</param>\n"
                  "</page>\n"
                "</param>\n"
                "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                  "</effects-menu>\n"
                "<menu-tip>" N_("Blend image or object with a flood color") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Colorize>());
        // clang-format on
    };

};

gchar const *
Colorize::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream hlight;
    std::ostringstream nlight;
    std::ostringstream duotone;
    std::ostringstream blend1;
    std::ostringstream blend2;

    auto color = ext->get_param_color("color");
    hlight << ext->get_param_float("hlight");
    nlight << ext->get_param_float("nlight");
    blend1 << ext->get_param_optiongroup("blend1");
    blend2 << ext->get_param_optiongroup("blend2");
    if (ext->get_param_bool("duotone")) {
        duotone << "0";
    } else {
        duotone << "1";
    }
    
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Colorize\">\n"
          "<feComposite in2=\"SourceGraphic\" operator=\"arithmetic\" k1=\"%s\" k2=\"%s\" result=\"composite1\" />\n"
          "<feColorMatrix in=\"composite1\" values=\"%s\" type=\"saturate\" result=\"colormatrix1\" />\n"
          "<feFlood flood-opacity=\"%f\" flood-color=\"%s\" result=\"flood1\" />\n"
          "<feBlend in=\"flood1\" in2=\"colormatrix1\" mode=\"%s\" result=\"blend1\" />\n"
          "<feBlend in2=\"blend1\" mode=\"%s\" result=\"blend2\" />\n"
          "<feColorMatrix in=\"blend2\" values=\"1\" type=\"saturate\" result=\"colormatrix2\" />\n"
          "<feComposite in=\"colormatrix2\" in2=\"SourceGraphic\" operator=\"in\" k2=\"1\" result=\"composite2\" />\n"
        "</filter>\n", hlight.str().c_str(), nlight.str().c_str(), duotone.str().c_str(),
                       color.getOpacity(), color.toString(false).c_str(),
                       blend1.str().c_str(), blend2.str().c_str() );
    // clang-format on

    return _filter;
}; /* Colorize filter */

/**
    \brief    Custom predefined ComponentTransfer filter.
    
    Basic component transfer structure.

    Filter's parameters:
    * Type (enum, default identity) -> component function

*/
class ComponentTransfer : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    ComponentTransfer ( ) : Filter() { };
    ~ComponentTransfer ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Component Transfer") "</name>\n"
              "<id>org.inkscape.effect.filter.ComponentTransfer</id>\n"
              "<param name=\"type\" gui-text=\"" N_("Type:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"identity\">" N_("Identity") "</option>\n"
                "<option value=\"table\">" N_("Table") "</option>\n"
                "<option value=\"discrete\">" N_("Discrete") "</option>\n"
                "<option value=\"linear\">" N_("Linear") "</option>\n"
                "<option value=\"gamma\">" N_("Gamma") "</option>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Basic component transfer structure") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<ComponentTransfer>());
        // clang-format on
    };
};

gchar const *
ComponentTransfer::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream CTfunction;
    const gchar *type = ext->get_param_optiongroup("type");

    if ((g_ascii_strcasecmp("identity", type) == 0)) {
        CTfunction << "<feFuncR type=\"identity\" tableValues=\"1 0\" />\n"
                 << "<feFuncG type=\"identity\" tableValues=\"1 0\" />\n"
                 << "<feFuncB type=\"identity\" tableValues=\"1 0\" />\n"
                 << "<feFuncA type=\"identity\" tableValues=\"0 1\" />\n";
    } else if ((g_ascii_strcasecmp("table", type) == 0)) {
        CTfunction << "<feFuncR type=\"table\" tableValues=\"0 1 0\" />\n"
                 << "<feFuncG type=\"table\" tableValues=\"0 1 0\" />\n"
                 << "<feFuncB type=\"table\" tableValues=\"0 1 0\" />\n";
    } else if ((g_ascii_strcasecmp("discrete", type) == 0)) {
        CTfunction << "<feFuncR tableValues=\"0 0.2 0.4 0.6 0.8 1 1\" type=\"discrete\" />\n"
                 << "<feFuncG tableValues=\"0 0.2 0.4 0.6 0.8 1 1\" type=\"discrete\" />\n"
                 << "<feFuncB tableValues=\"0 0.2 0.4 0.6 0.8 1 1\" type=\"discrete\" />\n";
    } else if ((g_ascii_strcasecmp("linear", type) == 0)) {
        CTfunction << "<feFuncR type=\"linear\" slope=\".5\" intercept=\".10\" />\n"
                 << "<feFuncG type=\"linear\" slope=\".5\" intercept=\".10\" />\n"
                 << "<feFuncB type=\"linear\" slope=\".5\" intercept=\".10\" />\n";
    } else { //Gamma
        CTfunction << "<feFuncR type=\"gamma\" amplitude=\"3\" exponent=\"3\" offset=\"0.1\" />\n"
                 << "<feFuncG type=\"gamma\" amplitude=\"3\" exponent=\"3\" offset=\"0.1\" />\n"
                 << "<feFuncB type=\"gamma\" amplitude=\"3\" exponent=\"3\" offset=\"0.1\" />\n";
    }
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Component Transfer\">\n"
        "<feComponentTransfer>\n"
        "%s\n"
        "</feComponentTransfer>\n"
        "</filter>\n", CTfunction.str().c_str());
    // clang-format on

    return _filter;
}; /* ComponentTransfer filter */

/**
    \brief    Custom predefined Duochrome filter.
    
    Convert luminance values to a duochrome palette.

    Filter's parameters:
    * Fluorescence level (0.->2., default 0) -> composite4 (k2)
    * Swap (enum, default "No swap") -> composite1, composite2 (operator)
    * Color 1 (guint, default 1364325887) -> flood1 (flood-opacity, flood-color)
    * Color 2 (guint, default -65281) -> flood2 (flood-opacity, flood-color)
*/

class Duochrome : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Duochrome ( ) : Filter() { };
    ~Duochrome ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Duochrome") "</name>\n"
              "<id>org.inkscape.effect.filter.Duochrome</id>\n"
              "<param name=\"tab\" type=\"notebook\">\n"
                "<page name=\"optionstab\" gui-text=\"Options\">\n"
                  "<param name=\"fluo\" gui-text=\"" N_("Fluorescence level") "\" type=\"float\" appearance=\"full\" min=\"0\" max=\"2\">0</param>\n"
                  "<param name=\"swap\" gui-text=\"" N_("Swap:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                    "<option value=\"none\">" N_("No swap") "</option>\n"
                    "<option value=\"full\">" N_("Color and alpha") "</option>\n"
                    "<option value=\"color\">" N_("Color only") "</option>\n"
                    "<option value=\"alpha\">" N_("Alpha only") "</option>\n"
                  "</param>\n"
                "</page>\n"
                "<page name=\"co11tab\" gui-text=\"Color 1\">\n"
                  "<param name=\"color1\" gui-text=\"" N_("Color 1") "\" type=\"color\">1364325887</param>\n"
                "</page>\n"
                "<page name=\"co12tab\" gui-text=\"Color 2\">\n"
                  "<param name=\"color2\" gui-text=\"" N_("Color 2") "\" type=\"color\">-65281</param>\n"
                "</page>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Convert luminance values to a duochrome palette") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Duochrome>());
        // clang-format on
    };

};

gchar const *
Duochrome::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    bool swapa = false;
    std::ostringstream fluo;
    std::ostringstream swap1;
    std::ostringstream swap2;
    auto color1 = ext->get_param_color("color1");
    auto color2 = ext->get_param_color("color2");
    double fluorescence = ext->get_param_float("fluo");
    const gchar *swaptype = ext->get_param_optiongroup("swap");

    fluo << fluorescence;

    if ((g_ascii_strcasecmp("full", swaptype) == 0)) {
        swap1 << "in";
        swap2 << "out";
    } else if ((g_ascii_strcasecmp("color", swaptype) == 0)) {
        swap1 << "in";
        swap2 << "out";
        swapa = true;
    } else if ((g_ascii_strcasecmp("alpha", swaptype) == 0)) {
        swap1 << "out";
        swap2 << "in";
        swapa = true;
    } else {
        swap1 << "out";
        swap2 << "in";
    }

    double a1 = swapa ? color2.getOpacity() : color1.getOpacity();
    double a2 = swapa ? color1.getOpacity() : color2.getOpacity();

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Duochrome\">\n"
          "<feColorMatrix type=\"luminanceToAlpha\" result=\"colormatrix1\" />\n"
          "<feFlood flood-opacity=\"%f\" flood-color=\"%s\" result=\"flood1\" />\n"
          "<feComposite in2=\"colormatrix1\" operator=\"%s\" result=\"composite1\" />\n"
          "<feFlood flood-opacity=\"%f\" flood-color=\"%s\" result=\"flood2\" />\n"
          "<feComposite in2=\"colormatrix1\" result=\"composite2\" operator=\"%s\" />\n"
          "<feComposite in=\"composite2\" in2=\"composite1\" k2=\"1\"  k3=\"1\" operator=\"arithmetic\" result=\"composite3\" />\n"
          "<feColorMatrix in=\"composite3\" type=\"matrix\" values=\"2 -1 0 0 0 0 2 -1 0 0 -1 0 2 0 0 0 0 0 1 0 \" result=\"colormatrix2\" />\n"
          "<feComposite in=\"colormatrix2\" in2=\"composite3\" operator=\"arithmetic\" k2=\"%s\" result=\"composite4\" />\n"
          "<feBlend in=\"composite4\" in2=\"composite3\" mode=\"normal\" result=\"blend\" />\n"
          "<feComposite in2=\"SourceGraphic\" operator=\"in\" />\n"
        "</filter>\n", a1, color1.toString(false).c_str(), swap1.str().c_str(),
                       a2, color2.toString(false).c_str(), swap2.str().c_str(),
                       fluo.str().c_str() );
    // clang-format on

    return _filter;
}; /* Duochrome filter */

/**
    \brief    Custom predefined Extract Channel filter.
    
    Extract color channel as a transparent image.

    Filter's parameters:
    * Channel (enum, all colors, default Red) -> colormatrix (values)
    * Background blend (enum, Normal, Multiply, Screen, default Normal) -> blend (mode)
    * Channel to alpha (boolean, default false) -> colormatrix (values)

*/
class ExtractChannel : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    ExtractChannel ( ) : Filter() { };
    ~ExtractChannel ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Extract Channel") "</name>\n"
              "<id>org.inkscape.effect.filter.ExtractChannel</id>\n"
              "<param name=\"source\" gui-text=\"" N_("Channel:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"r\">" N_("Red") "</option>\n"
                "<option value=\"g\">" N_("Green") "</option>\n"
                "<option value=\"b\">" N_("Blue") "</option>\n"
                "<option value=\"c\">" N_("Cyan") "</option>\n"
                "<option value=\"m\">" N_("Magenta") "</option>\n"
                "<option value=\"y\">" N_("Yellow") "</option>\n"
              "</param>\n"
              "<param name=\"blend\" gui-text=\"" N_("Background blend mode:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                "<option value=\"normal\">" N_("Normal") "</option>\n"
                "<option value=\"screen\">" N_("Screen") "</option>\n"
              "</param>\n"
              "<param name=\"alpha\" gui-text=\"" N_("Channel to alpha") "\" type=\"bool\">false</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Extract color channel as a transparent image") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<ExtractChannel>());
        // clang-format on
    };
};

gchar const *
ExtractChannel::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream blend;
    std::ostringstream colors;

    blend << ext->get_param_optiongroup("blend");

    const gchar *channel = ext->get_param_optiongroup("source");
    if (ext->get_param_bool("alpha")) {
        if ((g_ascii_strcasecmp("r", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0";
        } else if ((g_ascii_strcasecmp("g", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0";
        } else if ((g_ascii_strcasecmp("b", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0";
        } else if ((g_ascii_strcasecmp("c", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 0 0 1 0";
        } else if ((g_ascii_strcasecmp("m", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 0 1 0";
        } else {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 1 0";
        }
    } else {
        if ((g_ascii_strcasecmp("r", channel) == 0)) {
            colors << "0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0";
        } else if ((g_ascii_strcasecmp("g", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0";
        } else if ((g_ascii_strcasecmp("b", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0";
        } else if ((g_ascii_strcasecmp("c", channel) == 0)) {
            colors << "0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 -1 0 0 1 0";
        } else if ((g_ascii_strcasecmp("m", channel) == 0)) {
            colors << "0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 -1 0 1 0";
        } else {
            colors << "0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 -1 1 0";
        }
    }

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Extract Channel\">\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"%s 0 \" result=\"colormatrix\" />\n"
          "<feBlend in2=\"BackgroundImage\" mode=\"%s\" result=\"blend\" />\n"
        "</filter>\n", colors.str().c_str(), blend.str().c_str() );
    // clang-format on

    return _filter;
}; /* ExtractChannel filter */

/**
    \brief    Custom predefined Fade to Black or White filter.
    
    Fade to black or white.

    Filter's parameters:
    * Level (0.->1., default 1.) -> colorMatrix (RVB entries)
    * Fade to (enum [black|white], default black) -> colorMatrix (RVB entries)
    
    Matrix
     black           white
    Lv 0  0  0 0    Lv 0  0  1-lv 0
    0  Lv 0  0 0    0  Lv 0  1-lv 0
    0  0  Lv 0 0    0  0  Lv 1-lv 0
    0  0  0  1 0    0  0  0  1    0
*/
class FadeToBW : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    FadeToBW ( ) : Filter() { };
    ~FadeToBW ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Fade to Black or White") "</name>\n"
              "<id>org.inkscape.effect.filter.FadeToBW</id>\n"
              "<param name=\"level\" gui-text=\"" N_("Level") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0\" max=\"1\">1</param>\n"
              "<param name=\"fadeto\" gui-text=\"" N_("Fade to:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"black\">" N_("Black") "</option>\n"
                "<option value=\"white\">" N_("White") "</option>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Fade to black or white") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<FadeToBW>());
        // clang-format on
    };
};

gchar const *
FadeToBW::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream level;
    std::ostringstream wlevel;

    level << ext->get_param_float("level");

    const gchar *fadeto = ext->get_param_optiongroup("fadeto");
    if ((g_ascii_strcasecmp("white", fadeto) == 0)) {
    // White
        wlevel << (1 - ext->get_param_float("level"));
    } else {
    // Black
        wlevel << "0";
    }

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Fade to Black or White\">\n"
          "<feColorMatrix values=\"%s 0 0 0 %s 0 %s 0 0 %s 0 0 %s 0 %s 0 0 0 1 0\" />\n"
        "</filter>\n", level.str().c_str(), wlevel.str().c_str(),
                       level.str().c_str(), wlevel.str().c_str(),
                       level.str().c_str(), wlevel.str().c_str() );
    // clang-format on

    return _filter;
}; /* Fade to black or white filter */

/**
    \brief    Custom predefined Greyscale filter.
    
    Customize greyscale components.

    Filter's parameters:
    * Red (-10.->10., default .21) -> colorMatrix (values)
    * Green (-10.->10., default .72) -> colorMatrix (values)
    * Blue (-10.->10., default .072) -> colorMatrix (values)
    * Lightness (-10.->10., default 0.) -> colorMatrix (values)
    * Transparent (boolean, default false) -> matrix structure
    
    Matrix:
     normal       transparency
    R G B St 0    0 0 0 0    0
    R G B St 0    0 0 0 0    0
    R G B St 0    0 0 0 0    0  
    0 0 0 1  0    R G B 1-St 0
*/
class Greyscale : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Greyscale ( ) : Filter() { };
    ~Greyscale ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Greyscale") "</name>\n"
              "<id>org.inkscape.effect.filter.Greyscale</id>\n"
              "<param name=\"red\" gui-text=\"" N_("Red") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.00\" max=\"10.00\">0.21</param>\n"
              "<param name=\"green\" gui-text=\"" N_("Green") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.00\" max=\"10.00\">0.72</param>\n"
              "<param name=\"blue\" gui-text=\"" N_("Blue") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.00\" max=\"10.00\">0.072</param>\n"
              "<param name=\"strength\" gui-text=\"" N_("Lightness") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-10.00\" max=\"10.00\">0</param>\n"
              "<param name=\"transparent\" gui-text=\"" N_("Transparent") "\" type=\"bool\" >false</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Customize greyscale components") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Greyscale>());
        // clang-format on
    };
};

gchar const *
Greyscale::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream red;
    std::ostringstream green;
    std::ostringstream blue;
    std::ostringstream strength;
    std::ostringstream redt;
    std::ostringstream greent;
    std::ostringstream bluet;
    std::ostringstream strengtht;
    std::ostringstream transparency;
    std::ostringstream line;
    
    red << ext->get_param_float("red");
    green << ext->get_param_float("green");
    blue << ext->get_param_float("blue");
    strength << ext->get_param_float("strength");
    
    redt << - ext->get_param_float("red");
    greent << - ext->get_param_float("green");
    bluet << - ext->get_param_float("blue");
    strengtht << 1 - ext->get_param_float("strength");

    if (ext->get_param_bool("transparent")) {
        line << "0 0 0 0";
        transparency << redt.str().c_str() << " " <<  greent.str().c_str() << " " <<  bluet.str().c_str() << " " << strengtht.str().c_str();
    } else {
        line << red.str().c_str() << " " <<  green.str().c_str() << " " <<  blue.str().c_str() << " " << strength.str().c_str();
        transparency << "0 0 0 1";
    }
    
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Greyscale\">\n"
          "<feColorMatrix values=\"%s 0 %s 0 %s 0 %s 0 \" />\n"
        "</filter>\n", line.str().c_str(), line.str().c_str(), line.str().c_str(), transparency.str().c_str() );
    // clang-format on

    return _filter;
}; /* Greyscale filter */

/**
    \brief    Custom predefined Invert filter.
    
    Manage hue, lightness and transparency inversions

    Filter's parameters:
    * Invert hue (boolean, default false) -> color1 (values, true: 180, false: 0)
    * Invert lightness (boolean, default false) -> color1 (values, true: 180, false: 0; XOR with Invert hue),
                                                   color2 (values: from a00 to a22, if 1, set -1 and set 1 in ax4, if -1, set 1 and set 0 in ax4)
    * Invert transparency (boolean, default false) -> color2 (values: negate a30, a31 and a32, substract 1 from a33)
    * Invert channels (enum, default Red and blue) -> color2 (values -for R&B: swap ax0 and ax2 in the first 3 lines)
    * Light transparency (0.->1., default 0.) -> color2 (values: a33=a33-x)
*/

class Invert : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Invert ( ) : Filter() { };
    ~Invert ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Invert") "</name>\n"
              "<id>org.inkscape.effect.filter.Invert</id>\n"
              "<param name=\"channels\" gui-text=\"" N_("Invert channels:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"0\">" N_("No inversion") "</option>\n"
                "<option value=\"1\">" N_("Red and blue") "</option>\n"
                "<option value=\"2\">" N_("Red and green") "</option>\n"
                "<option value=\"3\">" N_("Green and blue") "</option>\n"
              "</param>\n"
              "<param name=\"opacify\" gui-text=\"" N_("Light transparency") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0.\" max=\"1\">0</param>\n"
              "<param name=\"hue\" gui-text=\"" N_("Invert hue") "\" type=\"bool\" >false</param>\n"
              "<param name=\"lightness\" gui-text=\"" N_("Invert lightness") "\" type=\"bool\" >false</param>\n"
              "<param name=\"transparency\" gui-text=\"" N_("Invert transparency") "\" type=\"bool\" >false</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Manage hue, lightness and transparency inversions") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Invert>());
        // clang-format on
    };

};

gchar const *
Invert::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream line1;
    std::ostringstream line2;
    std::ostringstream line3;

    std::ostringstream col5;
    std::ostringstream transparency;
    std::ostringstream hue;

    if (ext->get_param_bool("hue") ^ ext->get_param_bool("lightness")) {
        hue << "<feColorMatrix type=\"hueRotate\" values=\"180\" result=\"color1\" />\n";
    } else {
        hue << "";
    }
         
    if (ext->get_param_bool("transparency")) {
        transparency << "0.21 0.72 0.07 " << 1 - ext->get_param_float("opacify");
    } else {
        transparency << "-0.21 -0.72 -0.07 " << 2 - ext->get_param_float("opacify");  
    }
    
    if (ext->get_param_bool("lightness")) {
        switch (atoi(ext->get_param_optiongroup("channels"))) {
            case 1:
                line1 << "0 0 -1";
                line2 << "0 -1 0";
                line3 << "-1 0 0";
                break;
            case 2:
                line1 << "0 -1 0";
                line2 << "-1 0 0";
                line3 << "0 0 -1";
                break;
            case 3:
                line1 << "-1 0 0";
                line2 << "0 0 -1";
                line3 << "0 -1 0";
                break;
            default:
                line1 << "-1 0 0";
                line2 << "0 -1 0";
                line3 << "0 0 -1";
                break;
        }
        col5 << "1";
    } else {
        switch (atoi(ext->get_param_optiongroup("channels"))) {
            case 1:
                line1 << "0 0 1";
                line2 << "0 1 0";
                line3 << "1 0 0";
                break;
            case 2:
                line1 << "0 1 0";
                line2 << "1 0 0";
                line3 << "0 0 1";
                break;
            case 3:
                line1 << "1 0 0";
                line2 << "0 0 1";
                line3 << "0 1 0";
                break;
            default:
                line1 << "1 0 0";
                line2 << "0 1 0";
                line3 << "0 0 1";
                break;
        }
        col5 << "0";
    }

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Invert\">\n"
          "%s"
          "<feColorMatrix values=\"%s 0 %s %s 0 %s %s 0 %s %s 0 \" result=\"color2\" />\n"
        "</filter>\n", hue.str().c_str(),
                       line1.str().c_str(), col5.str().c_str(),
                       line2.str().c_str(), col5.str().c_str(),
                       line3.str().c_str(), col5.str().c_str(),
                       transparency.str().c_str() );
    // clang-format on

    return _filter;
}; /* Invert filter */

/**
    \brief    Custom predefined Lighting filter.
    
    Modify lights and shadows separately.

    Filter's parameters:
    * Lightness (0.->20., default 1.) -> component (amplitude)
    * Shadow (0.->20., default 1.) -> component (exponent)
    * Offset (-1.->1., default 0.) -> component (offset)
*/
class Lighting : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Lighting ( ) : Filter() { };
    ~Lighting ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Lighting") "</name>\n"
              "<id>org.inkscape.effect.filter.Lighting</id>\n"
              "<param name=\"amplitude\" gui-text=\"" N_("Lights") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0.00\" max=\"20.00\">1</param>\n"
              "<param name=\"exponent\" gui-text=\"" N_("Shadows") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"0.00\" max=\"20.00\">1</param>\n"
              "<param name=\"offset\" gui-text=\"" N_("Offset") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-1.00\" max=\"1.00\">0</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Modify lights and shadows separately") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Lighting>());
        // clang-format on
    };
};

gchar const *
Lighting::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream amplitude;
    std::ostringstream exponent;
    std::ostringstream offset;

    amplitude << ext->get_param_float("amplitude");
    exponent << ext->get_param_float("exponent");
    offset << ext->get_param_float("offset");

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Lighting\">\n"
          "<feComponentTransfer in=\"blur\" result=\"component\" >\n"
          "<feFuncR type=\"gamma\" amplitude=\"%s\" exponent=\"%s\" offset=\"%s\" />\n"
          "<feFuncG type=\"gamma\" amplitude=\"%s\" exponent=\"%s\" offset=\"%s\" />\n"
          "<feFuncB type=\"gamma\" amplitude=\"%s\" exponent=\"%s\" offset=\"%s\" />\n"
          "</feComponentTransfer>\n"
        "</filter>\n", amplitude.str().c_str(), exponent.str().c_str(), offset.str().c_str(),
                       amplitude.str().c_str(), exponent.str().c_str(), offset.str().c_str(),
                       amplitude.str().c_str(), exponent.str().c_str(), offset.str().c_str() );
    // clang-format on

    return _filter;
}; /* Lighting filter */

/**
    \brief    Custom predefined Lightness-Contrast filter.
    
    Modify lightness and contrast separately.

    Filter's parameters:
    * Lightness (0.->100., default 0.) -> colorMatrix
    * Contrast (0.->100., default 0.) -> colorMatrix
    
    Matrix:
      Co/10 0     0     1+(Co-1)*Li/2000  -(Co-1)/20
      0     Co/10 0     1+(Co-1)*Li/2000  -(Co-1)/20
      0     0     Co/10 1+(Co-1)*Li/2000  -(Co-1)/20
      0     0     0     1                 0
*/
class LightnessContrast : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    LightnessContrast ( ) : Filter() { };
    ~LightnessContrast ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Lightness-Contrast") "</name>\n"
              "<id>org.inkscape.effect.filter.LightnessContrast</id>\n"
              "<param name=\"lightness\" gui-text=\"" N_("Lightness") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-100\" max=\"100\">0</param>\n"
              "<param name=\"contrast\" gui-text=\"" N_("Contrast") "\" type=\"float\" appearance=\"full\" precision=\"2\" min=\"-100\" max=\"100\">0</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Modify lightness and contrast separately") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<LightnessContrast>());
        // clang-format on
    };
};

gchar const *
LightnessContrast::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream lightness;
    std::ostringstream contrast;
    std::ostringstream contrast5;

    double c5;
    if (ext->get_param_float("contrast") > 0) {
        contrast << (1 + ext->get_param_float("contrast") / 10);
        c5 = (- ext->get_param_float("contrast") / 20);
    } else {
        contrast << (1 + ext->get_param_float("contrast") / 100);
        c5 =(- ext->get_param_float("contrast") / 200);
    } 

    contrast5 << c5;
    lightness << ((1 - c5) * ext->get_param_float("lightness") / 100);

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Lightness-Contrast\">\n"
          "<feColorMatrix values=\"%s 0 0 %s %s 0 %s 0 %s %s 0 0 %s %s %s 0 0 0 1 0\" />\n"
        "</filter>\n", contrast.str().c_str(), lightness.str().c_str(), contrast5.str().c_str(),
                       contrast.str().c_str(), lightness.str().c_str(), contrast5.str().c_str(),
                       contrast.str().c_str(), lightness.str().c_str(), contrast5.str().c_str() );
    // clang-format on

    return _filter;
}; /* Lightness-Contrast filter */

/**
    \brief    Custom predefined Nudge RGB filter.
    
    Nudge RGB channels separately and blend them to different types of backgrounds

    Filter's parameters:
    Offsets
      * Red
        * x (-100.->100., default -6) -> offset1 (dx)
        * y (-100.->100., default -6) -> offset1 (dy)
      * Green
        * x (-100.->100., default 6) -> offset2 (dx)
        * y (-100.->100., default 7) -> offset2 (dy)
      * Blue
        * x (-100.->100., default 1) -> offset3 (dx)
        * y (-100.->100., default -16) -> offset3 (dy)
    Color
      * Background color (guint, default 255)-> flood (flood-color, flood-opacity)

*/
class NudgeRGB : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    NudgeRGB ( ) : Filter() { };
    ~NudgeRGB ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Nudge RGB") "</name>\n"
              "<id>org.inkscape.effect.filter.NudgeRGB</id>\n"
              "<param name=\"tab\" type=\"notebook\">\n"
                "<page name=\"offsettab\" gui-text=\"Offset\">\n"
                  "<label appearance=\"header\">" N_("Red offset") "</label>\n"
                    "<param name=\"rx\" gui-text=\"" N_("X") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">-6</param>\n"
                    "<param name=\"ry\" gui-text=\"" N_("Y") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">-6</param>\n"
                  "<label appearance=\"header\">" N_("Green offset") "</label>\n"
                    "<param name=\"gx\" gui-text=\"" N_("X") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">6</param>\n"
                    "<param name=\"gy\" gui-text=\"" N_("Y") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">7</param>\n"
                  "<label appearance=\"header\">" N_("Blue offset") "</label>\n"
                    "<param name=\"bx\" gui-text=\"" N_("X") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">1</param>\n"
                    "<param name=\"by\" gui-text=\"" N_("Y") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">-16</param>\n"
                "</page>\n"
                "<page name=\"coltab\" gui-text=\"Color\">\n"
                  "<param name=\"color\" gui-text=\"" N_("Background color") "\" type=\"color\">255</param>\n"
                "</page>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Nudge RGB channels separately and blend them to different types of backgrounds") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<NudgeRGB>());
        // clang-format on
    };
};

gchar const *
NudgeRGB::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream rx;
    std::ostringstream ry;
    std::ostringstream gx;
    std::ostringstream gy;
    std::ostringstream bx;
    std::ostringstream by;

    rx << ext->get_param_float("rx");
    ry << ext->get_param_float("ry");
    gx << ext->get_param_float("gx");
    gy << ext->get_param_float("gy");
    bx << ext->get_param_float("bx");
    by << ext->get_param_float("by");

    auto color = ext->get_param_color("color");
    
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Nudge RGB\">\n"
          "<feFlood flood-opacity=\"%f\" flood-color=\"%s\" result=\"flood\" />\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 \" result=\"colormatrix1\" />\n"
          "<feOffset dy=\"%s\" dx=\"%s\" result=\"offset1\" />\n"
          "<feBlend in2=\"flood\" mode=\"screen\" result=\"blend1\" />\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 1 0 0 0 \" result=\"colormatrix2\" />\n"
          "<feOffset dy=\"%s\" dx=\"%s\" result=\"offset2\" />\n"
          "<feBlend in2=\"blend1\" mode=\"screen\" result=\"blend2\" />\n"
          "<feOffset dy=\"%s\" dx=\"%s\" result=\"offset3\" />\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 1 0 0 \" result=\"colormatrix3\" />\n"
          "<feBlend in2=\"offset3\" mode=\"screen\" result=\"blend3\" />\n"
        "</filter>\n", color.getOpacity(), color.toString(false).c_str(),
                       rx.str().c_str(), ry.str().c_str(),
                       gx.str().c_str(), gy.str().c_str(),
                       bx.str().c_str(), by.str().c_str() );
    // clang-format on

    return _filter;

}; /* Nudge RGB filter */

/**
    \brief    Custom predefined Nudge CMY filter.
    
    Nudge CMY channels separately and blend them to different types of backgrounds

    Filter's parameters:
    Offsets
      * Cyan
        * x (-100.->100., default -6) -> offset1 (dx)
        * y (-100.->100., default -6) -> offset1 (dy)
      * Magenta
        * x (-100.->100., default 6) -> offset2 (dx)
        * y (-100.->100., default 7) -> offset2 (dy)
      * Yellow
        * x (-100.->100., default 1) -> offset3 (dx)
        * y (-100.->100., default -16) -> offset3 (dy)
    Color
      * Background color (guint, default -1)-> flood (flood-color, flood-opacity)
*/
class NudgeCMY : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    NudgeCMY ( ) : Filter() { };
    ~NudgeCMY ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Nudge CMY") "</name>\n"
              "<id>org.inkscape.effect.filter.NudgeCMY</id>\n"
              "<param name=\"tab\" type=\"notebook\">\n"
                "<page name=\"offsettab\" gui-text=\"Offset\">\n"
                  "<label appearance=\"header\">" N_("Cyan offset") "</label>\n"
                    "<param name=\"cx\" gui-text=\"" N_("X") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">-6</param>\n"
                    "<param name=\"cy\" gui-text=\"" N_("Y") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">-6</param>\n"
                  "<label appearance=\"header\">" N_("Magenta offset") "</label>\n"
                    "<param name=\"mx\" gui-text=\"" N_("X") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">6</param>\n"
                    "<param name=\"my\" gui-text=\"" N_("Y") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">7</param>\n"
                  "<label appearance=\"header\">" N_("Yellow offset") "</label>\n"
                    "<param name=\"yx\" gui-text=\"" N_("X") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">1</param>\n"
                    "<param name=\"yy\" gui-text=\"" N_("Y") "\" type=\"float\" indent=\"1\" appearance=\"full\" precision=\"2\" min=\"-100.\" max=\"100.\">-16</param>\n"
                "</page>\n"
                "<page name=\"coltab\" gui-text=\"Color\">\n"
                  "<param name=\"color\" gui-text=\"" N_("Background color") "\" type=\"color\">-1</param>\n"
                "</page>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Nudge CMY channels separately and blend them to different types of backgrounds") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<NudgeCMY>());
        // clang-format on
    };
};

gchar const *
NudgeCMY::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream cx;
    std::ostringstream cy;
    std::ostringstream mx;
    std::ostringstream my;
    std::ostringstream yx;
    std::ostringstream yy;

    cx << ext->get_param_float("cx");
    cy << ext->get_param_float("cy");
    mx << ext->get_param_float("mx");
    my << ext->get_param_float("my");
    yx << ext->get_param_float("yx");
    yy << ext->get_param_float("yy");

    auto color = ext->get_param_color("color");
    
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Nudge CMY\">\n"
          "<feFlood flood-opacity=\"%f\" flood-color=\"%s\" result=\"flood\" />\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"0 0 0 0 0 0 0 0 0 1 0 0 0 0 1 -1 0 0 1 0 \" result=\"colormatrix1\" />\n"
          "<feOffset dy=\"%s\" dx=\"%s\" result=\"offset1\" />\n"
          "<feBlend in2=\"flood\" mode=\"multiply\" result=\"blend1\" />\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 -1 0 1 0 \" result=\"colormatrix2\" />\n"
          "<feOffset dy=\"%s\" dx=\"%s\" result=\"offset2\" />\n"
          "<feBlend in2=\"blend1\" mode=\"multiply\" result=\"blend2\" />\n"
          "<feOffset dy=\"%s\" dx=\"%s\" result=\"offset3\" />\n"
          "<feColorMatrix in=\"SourceGraphic\" values=\"0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 -1 1 0 \" result=\"colormatrix3\" />\n"
          "<feBlend in2=\"offset3\" mode=\"multiply\" result=\"blend3\" />\n"
        "</filter>\n", color.getOpacity(), color.toString(false).c_str(),
                       cx.str().c_str(), cy.str().c_str(),
                       mx.str().c_str(), my.str().c_str(),
                       yx.str().c_str(), yy.str().c_str() );
    // clang-format on

    return _filter;

}; /* Nudge CMY filter */

/**
    \brief    Custom predefined Quadritone filter.
    
    Replace hue by two colors.

    Filter's parameters:
    * Hue distribution (0->360, default 280) -> colormatrix1 (values)
    * Colors (0->360, default 100) -> colormatrix3 (values)
    * Blend mode 1 (enum, default Normal) -> blend1 (mode)
    * Over-saturation (0.->1., default 0) -> composite1 (k2)
    * Blend mode 2 (enum, default Normal) -> blend2 (mode)
*/

class Quadritone : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Quadritone ( ) : Filter() { };
    ~Quadritone ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Quadritone Fantasy") "</name>\n"
              "<id>org.inkscape.effect.filter.Quadritone</id>\n"
                "<param name=\"dist\" gui-text=\"" N_("Hue distribution (°)") "\" type=\"int\" appearance=\"full\" min=\"0\" max=\"360\">280</param>\n"
                "<param name=\"colors\" gui-text=\"" N_("Colors") "\" type=\"int\" appearance=\"full\" min=\"0\" max=\"360\">100</param>\n"
                "<param name=\"blend1\" gui-text=\"" N_("Blend 1:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                  "<option value=\"normal\">" N_("Normal") "</option>\n"
                  "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                  "<option value=\"screen\">" N_("Screen") "</option>\n"
                "</param>\n"
                "<param name=\"sat\" gui-text=\"" N_("Over-saturation") "\" type=\"float\" appearance=\"full\" precision=\"2\"  min=\"0.00\" max=\"1.00\">0</param>\n"
                "<param name=\"blend2\" gui-text=\"" N_("Blend 2:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                  "<option value=\"normal\">" N_("Normal") "</option>\n"
                  "<option value=\"screen\">" N_("Screen") "</option>\n"
                  "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                  "<option value=\"lighten\">" N_("Lighten") "</option>\n"
                  "<option value=\"darken\">" N_("Darken") "</option>\n"
                "</param>\n"
                "<effect>\n"
                  "<object-type>all</object-type>\n"
                  "<effects-menu>\n"
                    "<submenu name=\"" N_("Filters") "\">\n"
                      "<submenu name=\"" N_("Color") "\"/>\n"
                    "</submenu>\n"
                  "</effects-menu>\n"
                "<menu-tip>" N_("Replace hue by two colors") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Quadritone>());
        // clang-format on
    };

};

gchar const *
Quadritone::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream dist;
    std::ostringstream colors;
    std::ostringstream blend1;
    std::ostringstream sat;
    std::ostringstream blend2;

    dist << ext->get_param_int("dist");
    colors << ext->get_param_int("colors");
    blend1 << ext->get_param_optiongroup("blend1");
    sat << ext->get_param_float("sat");
    blend2 << ext->get_param_optiongroup("blend2");

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Quadritone fantasy\">\n"
          "<feColorMatrix in=\"SourceGraphic\" type=\"hueRotate\" values=\"%s\" result=\"colormatrix1\" />\n"
          "<feColorMatrix type=\"matrix\" values=\"0.5 0 0.5 0 0 0 1 0 0 0 0.5 0 0.5 0 0 0 0 0 1 0 \" result=\"colormatrix2\" />\n"
          "<feColorMatrix type=\"hueRotate\" values=\"%s\" result=\"colormatrix3\" />\n"
          "<feBlend in2=\"colormatrix3\" mode=\"%s\" result=\"blend1\" />\n"
          "<feColorMatrix type=\"matrix\" values=\"2.5 -0.75 -0.75 0 0 -0.75 2.5 -0.75 0 0 -0.75 -0.75 2.5 0 0 0 0 0 1 0 \" result=\"colormatrix4\" />\n"
          "<feComposite in=\"colormatrix4\" in2=\"blend1\" operator=\"arithmetic\" k2=\"%s\" result=\"composite1\" />\n"
          "<feBlend in2=\"blend1\" mode=\"%s\" result=\"blend2\" />\n"
        "</filter>\n", dist.str().c_str(), colors.str().c_str(), blend1.str().c_str(), sat.str().c_str(), blend2.str().c_str() );
    // clang-format on

    return _filter;
}; /* Quadritone filter */


/**
    \brief    Custom predefined Simple blend filter.
    
    Simple blend filter.

    Filter's parameters:
    * Color (guint, default 16777215) -> flood1 (flood-opacity, flood-color)
    * Blend mode (enum, default Hue) -> blend1 (mode)
*/
class SimpleBlend : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    SimpleBlend ( ) : Filter() { };
    ~SimpleBlend ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }
    
    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Simple blend") "</name>\n"
              "<id>org.inkscape.effect.filter.SimpleBlend</id>\n"
              "<param name=\"color\" gui-text=\"" N_("Color") "\" type=\"color\">16777215</param>\n"
              "<param name=\"blendmode\" gui-text=\"" N_("Blend mode:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"normal\">" N_("Normal") "</option>\n"          
                "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                "<option value=\"screen\">" N_("Screen") "</option>\n"
                "<option value=\"saturation\">" N_("Saturation") "</option>\n"
                "<option value=\"darken\">" N_("Darken") "</option>\n"
                "<option value=\"difference\">" N_("Difference") "</option>\n"          
                "<option value=\"lighten\">" N_("Lighten") "</option>\n"
                "<option value=\"luminosity\">" N_("Luminosity") "</option>\n"
                "<option value=\"overlay\">" N_("Overlay") "</option>\n"
                "<option value=\"color-dodge\">" N_("Color Dodge") "</option>\n"
                "<option value=\"color-burn\">" N_("Color Burn") "</option>\n"          
                "<option value=\"color\">" N_("Color") "</option>\n"
                "<option value=\"hard-light\">" N_("Hard Light") "</option>\n"
                "<option value=\"hue\">" N_("Hue") "</option>\n"
                "<option value=\"exclusion\">" N_("Exclusion") "</option>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Simple blend filter") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<SimpleBlend>());
        // clang-format on
    };
};

gchar const *
SimpleBlend::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream blend;

    auto color = ext->get_param_color("color");
    blend << ext->get_param_optiongroup("blendmode");

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Simple blend\">\n"
          "<feFlood result=\"flood1\" flood-color=\"%s\" flood-opacity=\"%f\" />\n"
          "<feBlend result=\"blend1\" in=\"flood1\" in2=\"SourceGraphic\" mode=\"%s\" />\n"
          "<feComposite operator=\"in\" in=\"blend1\" in2=\"SourceGraphic\" />\n"
        "</filter>\n", color.toString(false).c_str(),
                       color.getOpacity(), blend.str().c_str());
    // clang-format on

    return _filter;
}; /* SimpleBlend filter */

/**
    \brief    Custom predefined Solarize filter.
    
    Classic photographic solarization effect.

    Filter's parameters:
    * Type (enum, default "Solarize") ->
        Solarize = blend1 (mode="darken"), blend2 (mode="screen")
        Moonarize = blend1 (mode="lighten"), blend2 (mode="multiply") [No other access to the blend modes]
    * Hue rotation (0->360, default 0) -> colormatrix1 (values)
*/


class Solarize : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Solarize ( ) : Filter() { };
    ~Solarize ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Solarize") "</name>\n"
              "<id>org.inkscape.effect.filter.Solarize</id>\n"
              "<param name=\"rotate\" gui-text=\"" N_("Hue rotation (°)") "\" type=\"int\" appearance=\"full\" min=\"0\" max=\"360\">0</param>\n"
              "<param name=\"type\" gui-text=\"" N_("Type:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                "<option value=\"solarize\">" N_("Solarize") "</option>\n"
                "<option value=\"moonarize\">" N_("Moonarize") "</option>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Classic photographic solarization effect") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Solarize>());
        // clang-format on
    };

};

gchar const *
Solarize::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);

    std::ostringstream rotate;
    std::ostringstream blend1;
    std::ostringstream blend2;

    rotate << ext->get_param_int("rotate");
    const gchar *type = ext->get_param_optiongroup("type");
    if ((g_ascii_strcasecmp("solarize", type) == 0)) {
    // Solarize
        blend1 << "darken";
        blend2 << "screen";
    } else {
    // Moonarize
        blend1 << "lighten";
        blend2 << "multiply";
    }

    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Solarize\">\n"
          "<feColorMatrix values=\"1 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1 1 \" />\n"
          "<feColorMatrix type=\"hueRotate\" values=\"%s\" result=\"colormatrix2\" />\n"
          "<feColorMatrix in=\"colormatrix2\" values=\"-1 0 0 0 1 0 -1 0 0 1 0 0 -1 0 1 0 0 0 1 0 \" result=\"colormatrix3\" />\n"
          "<feBlend in=\"colormatrix3\" in2=\"colormatrix2\" mode=\"%s\" result=\"blend1\" />\n"
          "<feBlend in2=\"blend1\" mode=\"%s\" result=\"blend2\" />\n"
          "<feComposite in2=\"SourceGraphic\" operator=\"in\" />\n"
        "</filter>\n", rotate.str().c_str(), blend1.str().c_str(), blend2.str().c_str() );
    // clang-format on

    return _filter;
}; /* Solarize filter */

/**
    \brief    Custom predefined Tritone filter.
    
    Create a custom tritone palette with additional glow, blend modes and hue moving.

    Filter's parameters:
    * Option (enum, default Normal) ->
        Normal = composite1 (in2="flood"), composite2 (in="p", in2="blend6"), blend6 (in2="composite1")
        Enhance hue = Normal + composite2 (in="SourceGraphic")
        Phosphorescence = Normal + blend6 (in2="SourceGraphic") composite2 (in="blend6", in2="composite1")
        PhosphorescenceB = Normal + blend6 (in2="flood") composite1 (in2="SourceGraphic")
        Hue to background = Normal + composite1 (in2="BackgroundImage") [a template with an activated background is needed, or colors become black]
    * Hue distribution (0->360, default 0) -> colormatrix1 (values)
    * Colors (guint, default -73203457) -> flood (flood-opacity, flood-color)
    * Global blend (enum, default Lighten) -> blend5 (mode) [Multiply, Screen, Darken, Lighten only!]
    * Glow (0.01->10., default 0.01) -> blur (stdDeviation)
    * Glow & blend (enum, default Normal) -> blend6 (mode) [Normal, Multiply and Darken only!]
    * Local light (0.->10., default 0) -> composite2 (k1)
    * Global light (0.->10., default 1) -> composite2 (k3) [k2 must be fixed to 1].
*/

class Tritone : public Inkscape::Extension::Internal::Filter::Filter {
protected:
    gchar const * get_filter_text (Inkscape::Extension::Extension * ext) override;

public:
    Tritone ( ) : Filter() { };
    ~Tritone ( ) override { if (_filter != nullptr) g_free((void *)_filter); return; }

    static void init () {
        // clang-format off
        Inkscape::Extension::build_from_mem(
            "<inkscape-extension xmlns=\"" INKSCAPE_EXTENSION_URI "\">\n"
              "<name>" N_("Tritone") "</name>\n"
              "<id>org.inkscape.effect.filter.Tritone</id>\n"
              "<param name=\"tab\" type=\"notebook\">\n"
                "<page name=\"optionstab\" gui-text=\"Options\">\n"
                  "<param name=\"type\" gui-text=\"" N_("Type:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                    "<option value=\"normal\">" N_("Normal") "</option>\n"
                    "<option value=\"enhue\">" N_("Enhance hue") "</option>\n"
                    "<option value=\"phospho\">" N_("Phosphorescence") "</option>\n"
                    "<option value=\"phosphoB\">" N_("Colored nights") "</option>\n"
                    "<option value=\"htb\">" N_("Hue to background") "</option>\n"
                  "</param>\n"
                  "<param name=\"globalblend\" gui-text=\"" N_("Global blend:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                    "<option value=\"lighten\">" N_("Lighten") "</option>\n"
                    "<option value=\"screen\">" N_("Screen") "</option>\n"
                    "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                    "<option value=\"darken\">" N_("Darken") "</option>\n"
                  "</param>\n"
                  "<param name=\"glow\" gui-text=\"" N_("Glow") "\" type=\"float\" appearance=\"full\" min=\"0.01\" max=\"10\">0.01</param>\n"
                  "<param name=\"glowblend\" gui-text=\"" N_("Glow blend:") "\" type=\"optiongroup\" appearance=\"combo\">\n"
                    "<option value=\"normal\">" N_("Normal") "</option>\n"
                    "<option value=\"multiply\">" N_("Multiply") "</option>\n"
                    "<option value=\"darken\">" N_("Darken") "</option>\n"
                  "</param>\n"
                  "<param name=\"llight\" gui-text=\"" N_("Local light") "\" type=\"float\" appearance=\"full\" min=\"0\" max=\"10\">0</param>\n"
                  "<param name=\"glight\" gui-text=\"" N_("Global light") "\" type=\"float\" appearance=\"full\" min=\"0\" max=\"10\">1</param>\n"
                "</page>\n"
                "<page name=\"co1tab\" gui-text=\"Color\">\n"
                  "<param name=\"dist\" gui-text=\"" N_("Hue distribution (°):") "\" type=\"int\" appearance=\"full\" min=\"0\" max=\"360\">0</param>\n"
                  "<param name=\"color\" gui-text=\"" N_("Color") "\" type=\"color\">-73203457</param>\n"
                "</page>\n"
              "</param>\n"
              "<effect>\n"
                "<object-type>all</object-type>\n"
                "<effects-menu>\n"
                  "<submenu name=\"" N_("Filters") "\">\n"
                    "<submenu name=\"" N_("Color") "\"/>\n"
                  "</submenu>\n"
                "</effects-menu>\n"
                "<menu-tip>" N_("Create a custom tritone palette with additional glow, blend modes and hue moving") "</menu-tip>\n"
              "</effect>\n"
            "</inkscape-extension>\n", std::make_unique<Tritone>());
        // clang-format on
    };

};

gchar const *
Tritone::get_filter_text (Inkscape::Extension::Extension * ext)
{
    if (_filter != nullptr) g_free((void *)_filter);
    
    std::ostringstream dist;
    std::ostringstream globalblend;
    std::ostringstream glow;
    std::ostringstream glowblend;
    std::ostringstream llight;
    std::ostringstream glight;
    std::ostringstream c1in2;
    std::ostringstream c2in;
    std::ostringstream c2in2;
    std::ostringstream b6in2;
    
    auto color = ext->get_param_color("color");
    globalblend << ext->get_param_optiongroup("globalblend");
    dist << ext->get_param_int("dist");
    glow << ext->get_param_float("glow");
    glowblend << ext->get_param_optiongroup("glowblend");
    llight << ext->get_param_float("llight");
    glight << ext->get_param_float("glight");
    
    const gchar *type = ext->get_param_optiongroup("type");
    if ((g_ascii_strcasecmp("enhue", type) == 0)) {
    // Enhance hue
        c1in2 << "flood";
        c2in << "SourceGraphic";
        c2in2 << "blend6";
        b6in2 << "composite1";
    } else if ((g_ascii_strcasecmp("phospho", type) == 0)) {
    // Phosphorescence
        c1in2 << "flood";
        c2in << "blend6";
        c2in2 << "composite1";
        b6in2 << "SourceGraphic";
    } else if ((g_ascii_strcasecmp("phosphoB", type) == 0)) {
    // Phosphorescence B
        c1in2 << "SourceGraphic";
        c2in << "blend6";
        c2in2 << "composite1";
        b6in2 << "flood";
    } else if ((g_ascii_strcasecmp("htb", type) == 0)) {
    // Hue to background
        c1in2 << "BackgroundImage";
        c2in << "blend2";
        c2in2 << "blend6";
        b6in2 << "composite1";
    } else {
    // Normal
        c1in2 << "flood";
        c2in << "blend2";
        c2in2 << "blend6";
        b6in2 << "composite";
    }
    
    // clang-format off
    _filter = g_strdup_printf(
        "<filter xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\" style=\"color-interpolation-filters:sRGB;\" inkscape:label=\"Tritone\">\n"
          "<feColorMatrix type=\"hueRotate\" values=\"%s\" result=\"colormatrix1\" />\n"
          "<feColorMatrix in=\"colormatrix1\" type=\"matrix\" values=\"1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 0 1 \" result=\"colormatrix2\" />\n"
          "<feColorMatrix in=\"colormatrix1\" type=\"matrix\" values=\"0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 0 1 \" result=\"colormatrix3\" />\n"
          "<feColorMatrix in=\"colormatrix1\" type=\"matrix\" values=\"0 0 1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 0 0 1 \" result=\"colormatrix4\" />\n"
          "<feBlend in=\"colormatrix2\" in2=\"colormatrix3\" mode=\"darken\" result=\"blend1\" />\n"
          "<feBlend in=\"blend1\" in2=\"colormatrix4\" mode=\"darken\"  result=\"blend2\" />\n"
          "<feBlend in=\"colormatrix2\" in2=\"colormatrix3\" mode=\"lighten\" result=\"blend3\" />\n"
          "<feBlend in=\"blend3\" in2=\"colormatrix4\" mode=\"lighten\" result=\"blend4\" />\n"
          "<feComponentTransfer in=\"blend4\" result=\"componentTransfer\">\n"
            "<feFuncR type=\"linear\" slope=\"0\" />\n"
          "</feComponentTransfer>\n"
          "<feBlend in=\"blend2\" in2=\"componentTransfer\" mode=\"%s\" result=\"blend5\" />\n"
          "<feColorMatrix in=\"blend5\" type=\"matrix\" values=\"-1 1 0 0 0 -1 1 0 0 0 -1 1 0 0 0 0 0 0 0 1 \" result=\"colormatrix5\" />\n"
          "<feFlood flood-opacity=\"%f\" flood-color=\"%s\" result=\"flood\" />\n"
          "<feComposite in=\"colormatrix5\" in2=\"%s\" operator=\"arithmetic\" k1=\"1\" result=\"composite1\" />\n"
          "<feGaussianBlur stdDeviation=\"%s\" result=\"blur\" />\n"
          "<feBlend in2=\"%s\" mode=\"%s\" result=\"blend6\" />\n"
          "<feComposite in=\"%s\" in2=\"%s\" operator=\"arithmetic\" k1=\"%s\" k2=\"1\" k3=\"%s\" k4=\"0\" result=\"composite2\" />\n"
          "<feComposite in2=\"SourceGraphic\" operator=\"in\" result=\"composite3\" />\n"
        "</filter>\n", dist.str().c_str(), globalblend.str().c_str(),
                       color.getOpacity(), color.toString(false).c_str(),
                       c1in2.str().c_str(), glow.str().c_str(), b6in2.str().c_str(), glowblend.str().c_str(),
                       c2in.str().c_str(), c2in2.str().c_str(), llight.str().c_str(), glight.str().c_str() );
    // clang-format on

    return _filter;
}; /* Tritone filter */

}; /* namespace Filter */
}; /* namespace Internal */
}; /* namespace Extension */
}; /* namespace Inkscape */

/* Change the 'COLOR' below to be your file name */
#endif /* SEEN_INKSCAPE_EXTENSION_INTERNAL_FILTER_COLOR_H__ */
