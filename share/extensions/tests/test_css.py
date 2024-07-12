# coding=utf-8
"""
Test CSS Selectors Implementation

This unit test is a heavily modified version, adapted to SVG, originating from
CSSSelect2 (BSD).
"""

import pytest
from lxml import etree
from inkex.elements._parser import load_svg
from inkex.styles import ConditionalStyle

document = load_svg("tests/data/svg/ids.svg").getroot()


ALL_IDS = [el.get("id") for el in document.iter() if not isinstance(el, etree._Comment)]


@pytest.mark.parametrize(
    "selector, result",
    (
        ("*", ALL_IDS),
        ("g", ["layer", "outer-g", "tspan-g", "foobar-g"]),
        ("g g", ["outer-g", "tspan-g", "foobar-g"]),
        ("g, g g", ["layer", "outer-g", "tspan-g", "foobar-g"]),
        ("g , g g", ["layer", "outer-g", "tspan-g", "foobar-g"]),
        ("rect[width]", ["rect1"]),
        ('rect[width="5"]', ["rect1"]),
        ('rect[style*="black"]', ["rect1"]),
        ('rect[style*=""]', []),
        ('rect[style^="fill"]', ["rect1", "rect2"]),
        ('rect[style^=""]', []),
        ('rect[style$=";"]', ["rect1", "rect2"]),
        ('rect[style$=""]', []),
        ('g[foobar~="bc"]', ["foobar-g"]),
        ('g[foobar~="cde"]', ["foobar-g"]),
        ('[foobar~="ab bc"]', []),
        ('[foobar~=""]', []),
        ('[foobar~=" \t"]', []),
        ('g[foobar~="cd"]', []),
        ('rect[style="fill:BlAck;"]', []),
        ('rect[style="fill:BlAck;" s]', []),
        ('rect[style="fill:BlAck;" i]', ["rect1"]),
        ('rect[style*="BlAck"]', []),
        ('rect[style*="BlAck" s]', []),
        ('rect[style*="BlAck" i]', ["rect1"]),
        ('rect[style^="fILl"]', []),
        ('rect[style^="fiLl" s]', []),
        ('rect[style^="fiLl" i]', ["rect1", "rect2"]),
        ('rect[style$="Black;"]', []),
        ('rect[style$="Black;" S]', []),
        ('rect[style$="Black;" I]', ["rect1"]),
        ('g[foobar~="BC"]', []),
        ('g[foobar~="BC" s]', []),
        ('g[foobar~="BC" i]', ["foobar-g"]),
        # Attribute values are case sensitive…
        ('*[lang|="En"]', ["second-tspan"]),
        ('[lang|="En-us"]', ["second-tspan"]),
        ('*[lang|="en"]', []),
        ('[lang|="en-US"]', []),
        ('*[lang|="e"]', []),
        # … but :lang() is not.
        (":lang(EN)", ["second-tspan", "tspan-g"]),
        ("*:lang(en-US)", ["second-tspan", "tspan-g"]),
        (":lang(En)", ["second-tspan", "tspan-g"]),
        (":lang(e)", []),
        (':lang("en-US")', ["second-tspan", "tspan-g"]),
        # pytest.param(
        #    ':lang("*-US")', ['second-tspan', 'tspan-g'], marks=pytest.mark.xfail),
        # pytest.param(
        #    ':lang(\\*-US)', ['second-tspan', 'tspan-g'], marks=pytest.mark.xfail),
        (":lang(en /* English */, fr /* French */)", ["second-tspan", "tspan-g"]),
        ("tspan:nth-child(3)", ["third-tspan"]),
        ("tspan:nth-child(10)", []),
        ("tspan:nth-child(2n)", ["second-tspan", "fourth-tspan", "sixth-tspan"]),
        ("tspan:nth-child(even)", ["second-tspan", "fourth-tspan", "sixth-tspan"]),
        ("tspan:nth-child(+2n+0)", ["second-tspan", "fourth-tspan", "sixth-tspan"]),
        (
            "tspan:nth-child(2n+1)",
            ["first-tspan", "third-tspan", "fifth-tspan", "seventh-tspan"],
        ),
        (
            "tspan:nth-child(odd)",
            ["first-tspan", "third-tspan", "fifth-tspan", "seventh-tspan"],
        ),
        ("tspan:nth-child(2n+4)", ["fourth-tspan", "sixth-tspan"]),
        ("tspan:nth-child(3n+1)", ["first-tspan", "fourth-tspan", "seventh-tspan"]),
        (
            "text > tspan:nth-child(2n of text tspan[my-attr=test])",
            ["third-tspan", "fifth-tspan"],
        ),
        ("tspan:nth-last-child(1)", ["seventh-tspan"]),
        ("tspan:nth-last-child(0)", []),
        ("tspan:nth-last-child(2n+2)", ["second-tspan", "fourth-tspan", "sixth-tspan"]),
        ("tspan:nth-last-child(even)", ["second-tspan", "fourth-tspan", "sixth-tspan"]),
        ("tspan:nth-last-child(2n+4)", ["second-tspan", "fourth-tspan"]),
        (":nth-last-child(1 of [my-attr=test])", ["fifth-tspan"]),
        ("text:first-of-type", ["first-text"]),
        ("text:nth-child(1)", []),
        ("text:nth-of-type(2)", ["second-text"]),
        (":nth-of-type(1 of .e)", ["first-text"]),
        ("text:nth-last-of-type(2)", ["first-text"]),
        (":nth-last-of-type(1 of .e)", ["second-text"]),
        ("mask:only-child", ["foobar-mask"]),
        ("g:only-child", ["tspan-g"]),
        ("g *:only-child", ["tspan-g", "link-element", "foobar-mask"]),
        (
            "pattern *:only-of-type",
            ["pattern-textPath", "link-element", "radialGradient"],
        ),
        ("pattern:only-of-type", ["paragraph"]),
        (
            "tspan:empty",
            [
                "third-tspan",
                "fourth-tspan",
                "fifth-tspan",
                "sixth-tspan",
                "seventh-tspan",
            ],
        ),
        (
            "tspan:EMpty",
            [
                "third-tspan",
                "fourth-tspan",
                "fifth-tspan",
                "sixth-tspan",
                "seventh-tspan",
            ],
        ),
        (":root", ["svg"]),
        ("svg:root", ["svg"]),
        ("tspan:root", []),
        ("* :root", []),
        (".a", ["first-text"]),
        (".b", ["first-text"]),
        ("*.a", ["first-text"]),
        ("text.a", ["first-text"]),
        (".c", ["first-text", "third-tspan", "fourth-tspan"]),
        ("*.c", ["first-text", "third-tspan", "fourth-tspan"]),
        ("text *.c", ["third-tspan", "fourth-tspan"]),
        ("text tspan.c", ["third-tspan", "fourth-tspan"]),
        ("tspan ~ tspan.c", ["third-tspan", "fourth-tspan"]),
        ("text > tspan.c", ["third-tspan", "fourth-tspan"]),
        ("#first-tspan", ["first-tspan"]),
        ("tspan#first-tspan", ["first-tspan"]),
        ("*#first-tspan", ["first-tspan"]),
        ("tspan g", ["tspan-g"]),
        ("tspan > g", ["tspan-g"]),
        ("g > g", ["outer-g", "foobar-g"]),
        ("g>.c", ["first-text"]),
        ("g > .c", ["first-text"]),
        ("g + g", ["foobar-g"]),
        ("stop ~ stop", ["stop2-radialGradient"]),
        ('circle[shape="circle"] ~ circle', ["circle-nohref"]),
        ("text#first-text tspan:last-child", ["seventh-tspan"]),
        ("text#first-text *:last-child", ["tspan-g", "seventh-tspan"]),
        ("#outer-g:first-child", ["outer-g"]),
        (
            "#outer-g :first-child",
            [
                "rect1",
                "first-tspan",
                "tspan-g",
                "pattern-p",
                "link-element",
                "stop-radialGradient",
                "circle-href",
            ],
        ),
        (":not(*)", []),
        ("linearGradient:not([href])", ["linearGradient-nohref"]),
        (
            "text :Not([class])",
            [
                "first-tspan",
                "second-tspan",
                "tspan-g",
                "fifth-tspan",
                "sixth-tspan",
                "seventh-tspan",
            ],
        ),
        ("tspan:not(:nth-child(odd), #second-tspan)", ["fourth-tspan", "sixth-tspan"]),
        ("tspan:not(tspan)", []),
        (":is(*)", ALL_IDS),
        (":is(g)", ["layer", "outer-g", "tspan-g", "foobar-g"]),
        (
            ":is(g, radialGradient)",
            ["layer", "outer-g", "tspan-g", "radialGradient", "foobar-g"],
        ),
        (":is(:::wrong)", []),
        (
            ":is(g, :::wrong, radialGradient)",
            ["layer", "outer-g", "tspan-g", "radialGradient", "foobar-g"],
        ),
        ("g :is(g, g)", ["outer-g", "tspan-g", "foobar-g"]),
        ("tspan:is(.c)", ["third-tspan", "fourth-tspan"]),
        ('stop:is([offset="1"])', ["stop2-radialGradient"]),
        ("g:is(:not(#outer-g))", ["layer", "tspan-g", "foobar-g"]),
        ("g:is(g::before)", []),
        (":where(*)", ALL_IDS),
        (":where(g)", ["layer", "outer-g", "tspan-g", "foobar-g"]),
        (
            ":where(g, radialGradient)",
            ["layer", "outer-g", "tspan-g", "radialGradient", "foobar-g"],
        ),
        (":where(:::wrong)", []),
        (
            ":where(g, :::wrong, radialGradient)",
            ["layer", "outer-g", "tspan-g", "radialGradient", "foobar-g"],
        ),
        ("g :where(g, g)", ["outer-g", "tspan-g", "foobar-g"]),
        ("tspan:where(.c)", ["third-tspan", "fourth-tspan"]),
        ('stop:where([offset="1"])', ["stop2-radialGradient"]),
        ("g:where(:not(#outer-g))", ["layer", "tspan-g", "foobar-g"]),
        ("g:where(g::before)", []),
        ("pattern:has(stop)", ["paragraph"]),
        ("pattern:has(radialGradient stop)", ["paragraph"]),
        ("pattern:has(> radialGradient)", ["paragraph"]),
        ("text:has(> g)", []),
        ("text:has(stop, tspan)", ["first-text"]),
        ("text:has(stop, radialGradient)", []),
        ("text:has(+ pattern)", ["first-text"]),
        ("text:has(~ text)", ["first-text"]),
        ("text:has(>a, ~ text)", ["first-text"]),
        ("text:has(a,text,  tspan  )", ["first-text"]),
        ("text:has(*)", ["first-text"]),
        ("text:has(:not(tspan))", ["first-text"]),
        ("text:has( > :not( tspan ))", []),
        ("text:has(:not(tspan, g))", []),
        # Invalid characters in XPath element names, should not crash
        (r"di\a0 v", []),
        (r"g\[", []),
        (r"[h\a0 ref]", []),
        (r"[h\]ref]", []),
        (":link", ["link", "link-element"]),
        (":any-link", ["link", "link-element"]),
        (":local-link", ["link", "link-element"]),
        (":visited", []),
        (":hover", []),
        (":active", []),
        (":focus", []),
        (":target", []),
        (":enabled", []),
        (":disabled", []),
        (":checked", []),
        # Check that comments inside the selector are not a problem
        ("a:not([href]), g g", ["outer-g", "tspan-g", "nolink", "foobar-g"]),
        ("a:not([href]) /* test */, g g", ["outer-g", "tspan-g", "nolink", "foobar-g"]),
        ("a:not([href]), /* test */ g g", ["outer-g", "tspan-g", "nolink", "foobar-g"]),
        ("/* test */a:not([href]),g g", ["outer-g", "tspan-g", "nolink", "foobar-g"]),
        ("a:not([href]) , g g/* test */", ["outer-g", "tspan-g", "nolink", "foobar-g"]),
        (
            "/* test */a:not([href]), /* test */ g g",
            ["outer-g", "tspan-g", "nolink", "foobar-g"],
        ),
        (
            "/* test */a:not([href])/* test */,g  g",
            ["outer-g", "tspan-g", "nolink", "foobar-g"],
        ),
        (
            "/* test */ a:not([href]), g/* test */ g",
            ["outer-g", "tspan-g", "nolink", "foobar-g"],
        ),
        (
            "a:not([href]) /* test */,/* test */g  g",
            ["outer-g", "tspan-g", "nolink", "foobar-g"],
        ),
        (":is() p", []),
        ("*~rect", ["rect2", "rect3"]),
        ("radialGradient *", ["stop-radialGradient", "stop2-radialGradient"]),
        ("radialGradient > :is()", []),
        ("pattern:has(stop, :is())", ["paragraph"]),
        ("svg|pattern:has(stop, :is())", ["paragraph"]),
        ('g[inkscape|groupmode="layer"][svg|id="layer"]', ["layer"]),
        ('g[inkscape|groupmode="layer"][id="layer"]', ["layer"]),
        ('g[groupmode="layer"][id="layer"]', []),
        (
            "#paragraph :last-of-type",
            [
                "pattern-textPath",
                "pattern-p2",
                "link-element",
                "nolink",
                "radialGradient",
                "stop2-radialGradient",
            ],
        ),
    ),
)
def test_select(selector, result):
    """Main selectors test"""
    style = ConditionalStyle(selector)
    found = [el.get("id", "nil") for el in style.all_matches(document)]

    assert found == result, found