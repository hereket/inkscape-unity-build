#include "../__generated/inkscape-version.cpp"

#include "async/async.cpp"
#include "colors/cms/profile.cpp"
#include "colors/cms/system.cpp"
#include "colors/cms/transform.cpp"
#include "colors/color.cpp"
#include "colors/document-cms.cpp"
#include "colors/dragndrop.cpp"
#include "colors/manager.cpp"
#include "colors/parser.cpp"
#include "colors/printer.cpp"
#include "colors/color-set.cpp"
#include "colors/spaces/base.cpp"
#include "colors/spaces/cms.cpp"
#include "colors/spaces/cmyk.cpp"
#include "colors/spaces/components.cpp"
#include "colors/spaces/gray.cpp"
#include "colors/spaces/hsl.cpp"
#include "colors/spaces/hsluv.cpp"
#include "colors/spaces/hsv.cpp"
#include "colors/spaces/lab.cpp"
#include "colors/spaces/lch.cpp"
#include "colors/spaces/linear-rgb.cpp"
#include "colors/spaces/luv.cpp"
#include "colors/spaces/okhsl.cpp"
#include "colors/spaces/oklab.cpp"
#include "colors/spaces/oklch.cpp"
#include "colors/spaces/named.cpp"
#include "colors/spaces/rgb.cpp"
#include "colors/spaces/xyz.cpp"
#include "colors/utils.cpp"
#include "colors/xml-color.cpp"
#include "debug/demangle.cpp"
#include "debug/heap.cpp"
#include "debug/logger.cpp"
#include "debug/sysv-heap.cpp"
#include "debug/timestamp.cpp"
#include "display/cairo-utils.cpp"
#include "display/curve.cpp"
#include "display/drawing-context.cpp"
#include "display/drawing-group.cpp"
#include "display/drawing-image.cpp"
#include "display/drawing-item.cpp"
#include "display/drawing-paintserver.cpp"
#include "display/drawing-pattern.cpp"
#include "display/drawing-shape.cpp"
#include "display/drawing-surface.cpp"
#include "display/drawing-text.cpp"
#include "display/drawing.cpp"
#include "display/nr-3dutils.cpp"
#include "display/nr-filter-blend.cpp"
#include "display/nr-filter-colormatrix.cpp"
#include "display/nr-filter-component-transfer.cpp"
#include "display/nr-filter-composite.cpp"
#include "display/nr-filter-convolve-matrix.cpp"
#include "display/nr-filter-diffuselighting.cpp"
#include "display/nr-filter-displacement-map.cpp"
#include "display/nr-filter-flood.cpp"
#include "display/nr-filter-gaussian.cpp"
#include "display/nr-filter-image.cpp"
#include "display/nr-filter-merge.cpp"
#include "display/nr-filter-morphology.cpp"
#include "display/nr-filter-offset.cpp"
#include "display/nr-filter-primitive.cpp"
#include "display/nr-filter-slot.cpp"
#include "display/nr-filter-specularlighting.cpp"
#include "display/nr-filter-tile.cpp"
#include "display/nr-filter-turbulence.cpp"
#include "display/nr-filter-units.cpp"
#include "display/nr-filter.cpp"
#include "display/nr-light.cpp"
#include "display/nr-style.cpp"
#include "display/nr-svgfonts.cpp"
#include "display/translucency-group.cpp"
#include "display/control/canvas-temporary-item-list.cpp"
#include "display/control/canvas-temporary-item.cpp"
#include "display/control/ctrl-handle-manager.cpp"
#include "display/control/ctrl-handle-rendering.cpp"
#include "display/control/ctrl-handle-styling.cpp"
#include "display/control/snap-indicator.cpp"
#include "display/control/canvas-item.cpp"
#include "display/control/canvas-item-bpath.cpp"
#include "display/control/canvas-item-catchall.cpp"
#include "display/control/canvas-item-context.cpp"
#include "display/control/canvas-item-ctrl.cpp"
#include "display/control/canvas-item-curve.cpp"
#include "display/control/canvas-item-drawing.cpp"
#include "display/control/canvas-item-grid.cpp"
#include "display/control/canvas-item-group.cpp"
#include "display/control/canvas-item-guideline.cpp"
#include "display/control/canvas-item-quad.cpp"
#include "display/control/canvas-item-rect.cpp"
#include "display/control/canvas-item-text.cpp"
#include "display/control/canvas-page.cpp"
#include "extension/db.cpp"
#include "extension/dependency.cpp"
#include "extension/processing-action.cpp"
#include "extension/effect.cpp"
#include "extension/execution-env.cpp"
#include "extension/extension.cpp"
#include "extension/input.cpp"
#include "extension/output.cpp"
#include "extension/patheffect.cpp"
#include "extension/print.cpp"
#include "extension/system.cpp"
#include "extension/template.cpp"
#include "extension/timer.cpp"
#include "extension/loader.cpp"
#include "extension/implementation/implementation.cpp"
#include "extension/implementation/xslt.cpp"
#include "extension/implementation/script.cpp"
#include "extension/internal/bluredge.cpp"
#include "extension/internal/cairo-ps-out.cpp"
#include "extension/internal/cairo-render-context.cpp"
#include "extension/internal/cairo-renderer.cpp"
#include "extension/internal/cairo-renderer-pdf-out.cpp"
#include "extension/internal/emf-inout.cpp"
#include "extension/internal/emf-print.cpp"
#include "extension/internal/gdkpixbuf-input.cpp"
#include "extension/internal/gimpgrad.cpp"
#include "extension/internal/grid.cpp"
#include "extension/internal/image-resolution.cpp"
#include "extension/internal/latex-pstricks.cpp"
#include "extension/internal/latex-pstricks-out.cpp"
#include "extension/internal/metafile-inout.cpp"
#include "extension/internal/metafile-print.cpp"
#include "extension/internal/odf.cpp"
#include "extension/internal/latex-text-renderer.cpp"
#include "extension/internal/png-output.cpp"
#include "extension/internal/pov-out.cpp"
#include "extension/internal/svg.cpp"
#include "extension/internal/svgz.cpp"
#include "extension/internal/template-base.cpp"
#include "extension/internal/template-from-file.cpp"
#include "extension/internal/template-other.cpp"
#include "extension/internal/template-paper.cpp"
#include "extension/internal/template-screen.cpp"
#include "extension/internal/template-social.cpp"
#include "extension/internal/template-video.cpp"
#include "extension/internal/text_reassemble.c"
#include "extension/internal/wmf-inout.cpp"
#include "extension/internal/wmf-print.cpp"
#include "extension/internal/filter/filter-all.cpp"
#include "extension/internal/filter/filter-file.cpp"
#include "extension/internal/filter/filter.cpp"
#include "extension/prefdialog/prefdialog.cpp"
#include "extension/prefdialog/parameter.cpp"
#include "extension/prefdialog/parameter-bool.cpp"
#include "extension/prefdialog/parameter-color.cpp"
#include "extension/prefdialog/parameter-float.cpp"
#include "extension/prefdialog/parameter-int.cpp"
#include "extension/prefdialog/parameter-notebook.cpp"
#include "extension/prefdialog/parameter-optiongroup.cpp"
#include "extension/prefdialog/parameter-path.cpp"
#include "extension/prefdialog/parameter-string.cpp"
#include "extension/prefdialog/widget.cpp"
#include "extension/prefdialog/widget-box.cpp"
#include "extension/prefdialog/widget-image.cpp"
#include "extension/prefdialog/widget-label.cpp"
#include "extension/prefdialog/widget-separator.cpp"
#include "extension/prefdialog/widget-spacer.cpp"
#include "extension/internal/pdfinput/poppler-utils.cpp"
#include "extension/internal/pdfinput/poppler-cairo-font-engine.cpp"
#include "extension/internal/pdfinput/pdf-utils.cpp"
#include "extension/internal/pdfinput/pdf-input.cpp"
#include "extension/internal/pdfinput/pdf-parser.cpp"
#include "extension/internal/pdfinput/svg-builder.cpp"
#include "extension/internal/cdr-input.cpp"
#include "extension/internal/vsd-input.cpp"
#include "extension/internal/wpg-input.cpp"
#include "extension/internal/rvng-import-dialog.cpp"
#include "extension/internal/bitmap/adaptiveThreshold.cpp"
#include "extension/internal/bitmap/addNoise.cpp"
#include "extension/internal/bitmap/blur.cpp"
#include "extension/internal/bitmap/channel.cpp"
#include "extension/internal/bitmap/charcoal.cpp"
#include "extension/internal/bitmap/colorize.cpp"
#include "extension/internal/bitmap/contrast.cpp"
#include "extension/internal/bitmap/crop.cpp"
#include "extension/internal/bitmap/cycleColormap.cpp"
#include "extension/internal/bitmap/despeckle.cpp"
#include "extension/internal/bitmap/edge.cpp"
#include "extension/internal/bitmap/emboss.cpp"
#include "extension/internal/bitmap/enhance.cpp"
#include "extension/internal/bitmap/equalize.cpp"
#include "extension/internal/bitmap/gaussianBlur.cpp"
#include "extension/internal/bitmap/imagemagick.cpp"
#include "extension/internal/bitmap/implode.cpp"
#include "extension/internal/bitmap/level.cpp"
#include "extension/internal/bitmap/levelChannel.cpp"
#include "extension/internal/bitmap/medianFilter.cpp"
#include "extension/internal/bitmap/modulate.cpp"
#include "extension/internal/bitmap/negate.cpp"
#include "extension/internal/bitmap/normalize.cpp"
#include "extension/internal/bitmap/oilPaint.cpp"
#include "extension/internal/bitmap/opacity.cpp"
#include "extension/internal/bitmap/raise.cpp"
#include "extension/internal/bitmap/reduceNoise.cpp"
#include "extension/internal/bitmap/sample.cpp"
#include "extension/internal/bitmap/shade.cpp"
#include "extension/internal/bitmap/sharpen.cpp"
#include "extension/internal/bitmap/solarize.cpp"
#include "extension/internal/bitmap/spread.cpp"
#include "extension/internal/bitmap/swirl.cpp"
#include "extension/internal/bitmap/threshold.cpp"
#include "extension/internal/bitmap/unsharpmask.cpp"
#include "extension/internal/bitmap/wave.cpp"
#include "extension/init.cpp"
#include "helper/choose-file.cpp"
#include "helper/geom.cpp"
#include "helper/geom-nodetype.cpp"
#include "helper/geom-pathstroke.cpp"
#include "helper/geom-pathvector_nodesatellites.cpp"
#include "helper/geom-nodesatellite.cpp"
#include "helper/gettext.cpp"
#include "helper/pixbuf-ops.cpp"
#include "helper/png-write.cpp"
#include "helper/save-image.cpp"
#include "helper/stock-items.cpp"
#include "io/dir-util.cpp"
#include "io/file.cpp"
#include "io/file-export-cmd.cpp"
#include "io/resource.cpp"
#include "io/fix-broken-links.cpp"
#include "io/stream/bufferstream.cpp"
#include "io/stream/gzipstream.cpp"
#include "io/stream/inkscapestream.cpp"
#include "io/stream/stringstream.cpp"
#include "io/stream/uristream.cpp"
#include "io/stream/xsltstream.cpp"
#include "io/sys.cpp"
#include "live_effects/effect.cpp"
#include "live_effects/fill-conversion.cpp"
#include "live_effects/lpe-angle_bisector.cpp"
#include "live_effects/lpe-attach-path.cpp"
#include "live_effects/lpe-bendpath.cpp"
#include "live_effects/lpe-bool.cpp"
#include "live_effects/lpe-bounding-box.cpp"
#include "live_effects/lpe-bspline.cpp"
#include "live_effects/lpe-circle_3pts.cpp"
#include "live_effects/lpe-circle_with_radius.cpp"
#include "live_effects/lpe-clone-original.cpp"
#include "live_effects/lpe-constructgrid.cpp"
#include "live_effects/lpe-copy_rotate.cpp"
#include "live_effects/lpe-curvestitch.cpp"
#include "live_effects/lpe-dashed-stroke.cpp"
#include "live_effects/lpe-dynastroke.cpp"
#include "live_effects/lpe-ellipse_5pts.cpp"
#include "live_effects/lpe-embrodery-stitch.cpp"
#include "live_effects/lpe-embrodery-stitch-ordering.cpp"
#include "live_effects/lpe-envelope.cpp"
#include "live_effects/lpe-extrude.cpp"
#include "live_effects/lpe-fill-between-many.cpp"
#include "live_effects/lpe-fill-between-strokes.cpp"
#include "live_effects/lpe-fillet-chamfer.cpp"
#include "live_effects/lpe-gears.cpp"
#include "live_effects/lpe-interpolate.cpp"
#include "live_effects/lpe-interpolate_points.cpp"
#include "live_effects/lpe-jointype.cpp"
#include "live_effects/lpe-knot.cpp"
#include "live_effects/lpe-lattice.cpp"
#include "live_effects/lpe-lattice2.cpp"
#include "live_effects/lpe-line_segment.cpp"
#include "live_effects/lpe-measure-segments.cpp"
#include "live_effects/lpe-mirror_symmetry.cpp"
#include "live_effects/lpe-offset.cpp"
#include "live_effects/lpe-parallel.cpp"
#include "live_effects/lpe-path_length.cpp"
#include "live_effects/lpe-patternalongpath.cpp"
#include "live_effects/lpe-perp_bisector.cpp"
#include "live_effects/lpe-perspective-envelope.cpp"
#include "live_effects/lpe-powerclip.cpp"
#include "live_effects/lpe-powermask.cpp"
#include "live_effects/lpe-powerstroke.cpp"
#include "live_effects/lpe-pts2ellipse.cpp"
#include "live_effects/lpe-recursiveskeleton.cpp"
#include "live_effects/lpe-rough-hatches.cpp"
#include "live_effects/lpe-roughen.cpp"
#include "live_effects/lpe-ruler.cpp"
#include "live_effects/lpe-show_handles.cpp"
#include "live_effects/lpe-simplify.cpp"
#include "live_effects/lpe-skeleton.cpp"
#include "live_effects/lpe-sketch.cpp"
#include "live_effects/lpe-slice.cpp"
#include "live_effects/lpe-spiro.cpp"
#include "live_effects/lpe-tangent_to_curve.cpp"
#include "live_effects/lpe-taperstroke.cpp"
#include "live_effects/lpe-test-doEffect-stack.cpp"
#include "live_effects/lpe-text_label.cpp"
#include "live_effects/lpe-tiling.cpp"
#include "live_effects/lpe-transform_2pts.cpp"
#include "live_effects/lpegroupbbox.cpp"
#include "live_effects/lpeobject-reference.cpp"
#include "live_effects/lpe-vonkoch.cpp"
#include "live_effects/lpeobject.cpp"
#include "live_effects/spiro-converters.cpp"
#include "live_effects/spiro.cpp"
#include "live_effects/parameter/array.cpp"
#include "live_effects/parameter/bool.cpp"
#include "live_effects/parameter/colorpicker.cpp"
#include "live_effects/parameter/hidden.cpp"
#include "live_effects/parameter/satellite.cpp"
#include "live_effects/parameter/satellitearray.cpp"
#include "live_effects/parameter/satellite-reference.cpp"
#include "live_effects/parameter/message.cpp"
#include "live_effects/parameter/originalsatellite.cpp"
#include "live_effects/parameter/originalpath.cpp"
#include "live_effects/parameter/patharray.cpp"
#include "live_effects/parameter/parameter.cpp"
#include "live_effects/parameter/path-reference.cpp"
#include "live_effects/parameter/path.cpp"
#include "live_effects/parameter/point.cpp"
#include "live_effects/parameter/powerstrokepointarray.cpp"
#include "live_effects/parameter/random.cpp"
#include "live_effects/parameter/scalararray.cpp"
#include "live_effects/parameter/nodesatellitesarray.cpp"
#include "live_effects/parameter/text.cpp"
#include "live_effects/parameter/fontbutton.cpp"
#include "live_effects/parameter/togglebutton.cpp"
#include "live_effects/parameter/transformedpoint.cpp"
#include "live_effects/parameter/unit.cpp"
#include "live_effects/parameter/vector.cpp"
#include "object/box3d-side.cpp"
#include "object/box3d.cpp"
#include "object/color-profile.cpp"
#include "object/object-set.cpp"
#include "object/persp3d-reference.cpp"
#include "object/persp3d.cpp"
#include "object/sp-anchor.cpp"
#include "object/sp-clippath.cpp"
#include "object/sp-conn-end-pair.cpp"
#include "object/sp-conn-end.cpp"
#include "object/sp-defs.cpp"
#include "object/sp-desc.cpp"
#include "object/sp-dimensions.cpp"
#include "object/sp-ellipse.cpp"
#include "object/sp-factory.cpp"
#include "object/sp-filter-reference.cpp"
#include "object/sp-filter.cpp"
#include "object/sp-flowdiv.cpp"
#include "object/sp-flowregion.cpp"
#include "object/sp-flowtext.cpp"
#include "object/sp-font-face.cpp"
#include "object/sp-font.cpp"
#include "object/sp-glyph-kerning.cpp"
#include "object/sp-glyph.cpp"
#include "object/sp-gradient-reference.cpp"
#include "object/sp-gradient.cpp"
#include "object/sp-grid.cpp"
#include "object/sp-guide.cpp"
#include "object/sp-hatch-path.cpp"
#include "object/sp-hatch.cpp"
#include "object/sp-image.cpp"
#include "object/sp-item-group.cpp"
#include "object/sp-item-transform.cpp"
#include "object/sp-item.cpp"
#include "object/sp-line.cpp"
#include "object/sp-linear-gradient.cpp"
#include "object/sp-lpe-item.cpp"
#include "object/sp-marker.cpp"
#include "object/sp-mask.cpp"
#include "object/sp-mesh-array.cpp"
#include "object/sp-mesh-gradient.cpp"
#include "object/sp-mesh-patch.cpp"
#include "object/sp-mesh-row.cpp"
#include "object/sp-metadata.cpp"
#include "object/sp-missing-glyph.cpp"
#include "object/sp-namedview.cpp"
#include "object/sp-object-group.cpp"
#include "object/sp-object.cpp"
#include "object/sp-offset.cpp"
#include "object/sp-paint-server.cpp"
#include "object/sp-page.cpp"
#include "object/sp-path.cpp"
#include "object/sp-pattern.cpp"
#include "object/sp-polygon.cpp"
#include "object/sp-polyline.cpp"
#include "object/sp-radial-gradient.cpp"
#include "object/sp-rect.cpp"
#include "object/sp-root.cpp"
#include "object/sp-script.cpp"
#include "object/sp-shape.cpp"
#include "object/sp-shape-reference.cpp"
#include "object/sp-solid-color.cpp"
#include "object/sp-spiral.cpp"
#include "object/sp-star.cpp"
#include "object/sp-stop.cpp"
#include "object/sp-string.cpp"
#include "object/sp-style-elem.cpp"
#include "object/sp-switch.cpp"
#include "object/sp-symbol.cpp"
#include "object/sp-tag-use-reference.cpp"
#include "object/sp-tag-use.cpp"
#include "object/sp-tag.cpp"
#include "object/sp-text.cpp"
#include "object/sp-title.cpp"
#include "object/sp-tref-reference.cpp"
#include "object/sp-tref.cpp"
#include "object/sp-tspan.cpp"
#include "object/sp-use-reference.cpp"
#include "object/sp-use.cpp"
#include "object/uri-references.cpp"
#include "object/uri.cpp"
#include "object/viewbox.cpp"
#include "object/filters/sp-filter-primitive.cpp"
#include "object/filters/blend.cpp"
#include "object/filters/colormatrix.cpp"
#include "object/filters/componenttransfer-funcnode.cpp"
#include "object/filters/componenttransfer.cpp"
#include "object/filters/composite.cpp"
#include "object/filters/convolvematrix.cpp"
#include "object/filters/diffuselighting.cpp"
#include "object/filters/displacementmap.cpp"
#include "object/filters/distantlight.cpp"
#include "object/filters/flood.cpp"
#include "object/filters/gaussian-blur.cpp"
#include "object/filters/image.cpp"
#include "object/filters/merge.cpp"
#include "object/filters/mergenode.cpp"
#include "object/filters/morphology.cpp"
#include "object/filters/offset.cpp"
#include "object/filters/pointlight.cpp"
#include "object/filters/specularlighting.cpp"
#include "object/filters/spotlight.cpp"
#include "object/filters/slot-resolver.cpp"
#include "object/filters/tile.cpp"
#include "object/filters/turbulence.cpp"
#include "object/algorithms/graphlayout.cpp"
#include "object/algorithms/removeoverlap.cpp"
#include "object/algorithms/unclump.cpp"
#include "path/path-boolop.cpp"
#include "path/path-object-set.cpp"
#include "path/path-offset.cpp"
#include "path/path-outline.cpp"
#include "path/path-simplify.cpp"
#include "path/path-util.cpp"
#include "path/splinefit/bezier-fit.cpp"
#include "path/splinefit/splinefit.c"
#include "path/splinefit/splinefont.c"
#include "path/splinefit/splinerefigure.c"
#include "svg/css-ostringstream.cpp"
#include "svg/path-string.cpp"
#include "svg/stringstream.cpp"
#include "svg/strip-trailing-zeros.cpp"
#include "svg/svg-affine.cpp"
#include "svg/svg-affine-parser.cpp"
#include "svg/svg-box.cpp"
#include "svg/svg-angle.cpp"
#include "svg/svg-length.cpp"
#include "svg/svg-bool.cpp"
#include "svg/svg-path.cpp"
#include "trace/cielab.cpp"
#include "trace/filterset.cpp"
#include "trace/imagemap.cpp"
#include "trace/imagemap-gdk.cpp"
#include "trace/quantize.cpp"
#include "trace/siox.cpp"
#include "trace/trace.cpp"
#include "trace/potrace/inkscape-potrace.cpp"
#include "trace/autotrace/inkscape-autotrace.cpp"
#include "trace/depixelize/inkscape-depixelize.cpp"
#include "ui/builder-utils.cpp"
#include "ui/clipboard.cpp"
#include "ui/contextmenu.cpp"
#include "ui/controller.cpp"
#include "ui/cursor-utils.cpp"
#include "ui/dialog-events.cpp"
#include "ui/dialog-run.cpp"
#include "ui/draw-anchor.cpp"
#include "ui/drag-and-drop.cpp"
#include "ui/icon-loader.cpp"
#include "ui/interface.cpp"
#include "ui/monitor.cpp"
#include "ui/pack.cpp"
#include "ui/popup-menu.cpp"
#include "ui/shape-editor.cpp"
#include "ui/shape-editor-knotholders.cpp"
#include "ui/simple-pref-pusher.cpp"
#include "ui/shortcuts.cpp"
#include "ui/svg-renderer.cpp"
#include "ui/syntax.cpp"
#include "ui/themes.cpp"
#include "ui/tool-factory.cpp"
#include "ui/util.cpp"
#include "ui/modifiers.cpp"
#include "ui/cache/svg_preview_cache.cpp"
#include "ui/desktop/document-check.cpp"
#include "ui/desktop/menubar.cpp"
#include "ui/desktop/menu-set-tooltips-shift-icons.cpp"
#include "ui/knot/knot.cpp"
#include "ui/knot/knot-holder.cpp"
#include "ui/knot/knot-holder-entity.cpp"
#include "ui/knot/knot-ptr.cpp"
#include "ui/tool/control-point-selection.cpp"
#include "ui/tool/control-point.cpp"
#include "ui/tool/curve-drag-point.cpp"
#include "ui/tool/modifier-tracker.cpp"
#include "ui/tool/multi-path-manipulator.cpp"
#include "ui/tool/node.cpp"
#include "ui/tool/path-manipulator.cpp"
#include "ui/tool/selectable-control-point.cpp"
#include "ui/tool/transform-handle-set.cpp"
#include "ui/toolbar/arc-toolbar.cpp"
#include "ui/toolbar/box3d-toolbar.cpp"
#include "ui/toolbar/calligraphy-toolbar.cpp"
#include "ui/toolbar/connector-toolbar.cpp"
#include "ui/toolbar/dropper-toolbar.cpp"
#include "ui/toolbar/marker-toolbar.cpp"
#include "ui/toolbar/eraser-toolbar.cpp"
#include "ui/toolbar/gradient-toolbar.cpp"
#include "ui/toolbar/lpe-toolbar.cpp"
#include "ui/toolbar/measure-toolbar.cpp"
#include "ui/toolbar/mesh-toolbar.cpp"
#include "ui/toolbar/node-toolbar.cpp"
#include "ui/toolbar/page-toolbar.cpp"
#include "ui/toolbar/paintbucket-toolbar.cpp"
#include "ui/toolbar/pencil-toolbar.cpp"
#include "ui/toolbar/rect-toolbar.cpp"
#include "ui/toolbar/select-toolbar.cpp"
#include "ui/toolbar/booleans-toolbar.cpp"
#include "ui/toolbar/spiral-toolbar.cpp"
#include "ui/toolbar/spray-toolbar.cpp"
#include "ui/toolbar/star-toolbar.cpp"
#include "ui/toolbar/text-toolbar.cpp"
#include "ui/toolbar/toolbar.cpp"
#include "ui/toolbar/tweak-toolbar.cpp"
#include "ui/toolbar/zoom-toolbar.cpp"
#include "ui/toolbar/command-toolbar.cpp"
#include "ui/toolbar/tool-toolbar.cpp"
#include "ui/toolbar/snap-toolbar.cpp"
#include "ui/toolbar/toolbars.cpp"
#include "ui/tools/arc-tool.cpp"
#include "ui/tools/box3d-tool.cpp"
#include "ui/tools/calligraphic-tool.cpp"
#include "ui/tools/connector-tool.cpp"
#include "ui/tools/dropper-tool.cpp"
#include "ui/tools/dynamic-base.cpp"
#include "ui/tools/eraser-tool.cpp"
#include "ui/tools/flood-tool.cpp"
#include "ui/tools/freehand-base.cpp"
#include "ui/tools/gradient-tool.cpp"
#include "ui/tools/lpe-tool.cpp"
#include "ui/tools/measure-tool.cpp"
#include "ui/tools/mesh-tool.cpp"
#include "ui/tools/node-tool.cpp"
#include "ui/tools/object-picker-tool.cpp"
#include "ui/tools/pages-tool.cpp"
#include "ui/tools/pencil-tool.cpp"
#include "ui/tools/pen-tool.cpp"
#include "ui/tools/rect-tool.cpp"
#include "ui/tools/marker-tool.cpp"
#include "ui/tools/select-tool.cpp"
#include "ui/tools/booleans-builder.cpp"
#include "ui/tools/booleans-tool.cpp"
#include "ui/tools/booleans-subitems.cpp"
#include "ui/tools/shortcuts.cpp"
#include "ui/tools/spiral-tool.cpp"
#include "ui/tools/spray-tool.cpp"
#include "ui/tools/star-tool.cpp"
#include "ui/tools/text-tool.cpp"
#include "ui/tools/tool-base.cpp"
#include "ui/tools/tweak-tool.cpp"
#include "ui/tools/zoom-tool.cpp"
#include "ui/dialog/about.cpp"
#include "ui/dialog/align-and-distribute.cpp"
#include "ui/dialog/calligraphic-profile-rename.cpp"
#include "ui/dialog/clonetiler.cpp"
#include "ui/dialog/color-item.cpp"
#include "ui/dialog/command-palette.cpp"
#include "ui/dialog/attrdialog.cpp"
#include "ui/dialog/dialog-base.cpp"
#include "ui/dialog/dialog-container.cpp"
#include "ui/dialog/dialog-data.cpp"
#include "ui/dialog/dialog-manager.cpp"
#include "ui/dialog/dialog-multipaned.cpp"
#include "ui/dialog/dialog-notebook.cpp"
#include "ui/dialog/dialog-window.cpp"
#include "ui/dialog/document-properties.cpp"
#include "ui/dialog/document-resources.cpp"
#include "ui/dialog/export.cpp"
#include "ui/dialog/export-batch.cpp"
#include "ui/dialog/export-single.cpp"
#include "ui/dialog/extensions-gallery.cpp"
#include "ui/dialog/filedialog.cpp"
#include "ui/dialog/filedialogimpl-gtkmm.cpp"
#include "ui/dialog/fill-and-stroke.cpp"
#include "ui/dialog/filter-effects-dialog.cpp"
#include "ui/dialog/find.cpp"
#include "ui/dialog/font-collections-manager.cpp"
#include "ui/dialog/font-substitution.cpp"
#include "ui/dialog/global-palettes.cpp"
#include "ui/dialog/glyphs.cpp"
#include "ui/dialog/grid-arrange-tab.cpp"
#include "ui/dialog/guides.cpp"
#include "ui/dialog/icon-preview.cpp"
#include "ui/dialog/inkscape-preferences.cpp"
#include "ui/dialog/knot-properties.cpp"
#include "ui/dialog/layer-properties.cpp"
#include "ui/dialog/livepatheffect-editor.cpp"
#include "ui/dialog/lpe-fillet-chamfer-properties.cpp"
#include "ui/dialog/lpe-powerstroke-properties.cpp"
#include "ui/dialog/memory.cpp"
#include "ui/dialog/messages.cpp"
#include "ui/dialog/new-from-template.cpp"
#include "ui/dialog/object-attributes.cpp"
#include "ui/dialog/object-properties.cpp"
#include "ui/dialog/objects.cpp"
#include "ui/dialog/polar-arrange-tab.cpp"
#include "ui/dialog/print.cpp"
#include "ui/dialog/prototype.cpp"
#include "ui/dialog/selectorsdialog.cpp"
#include "ui/dialog/startup.cpp"
#include "ui/dialog/styledialog.cpp"
#include "ui/dialog/svg-fonts-dialog.cpp"
#include "ui/dialog/swatches.cpp"
#include "ui/dialog/symbols.cpp"
#include "ui/dialog/paint-servers.cpp"
#include "ui/dialog/text-edit.cpp"
#include "ui/dialog/tile.cpp"
#include "ui/dialog/tracedialog.cpp"
#include "ui/dialog/transformation.cpp"
#include "ui/dialog/undo-history.cpp"
#include "ui/dialog/xml-tree.cpp"
#include "ui/dialog/save-template-dialog.cpp"
#include "ui/widget/iconrenderer.cpp"
#include "ui/widget/alignment-selector.cpp"
#include "ui/widget/anchor-selector.cpp"
#include "ui/widget/bin.cpp"
#include "ui/widget/completion-popup.cpp"
#include "ui/widget/canvas.cpp"
#include "ui/widget/canvas/stores.cpp"
#include "ui/widget/canvas/synchronizer.cpp"
#include "ui/widget/canvas/util.cpp"
#include "ui/widget/canvas/texture.cpp"
#include "ui/widget/canvas/texturecache.cpp"
#include "ui/widget/canvas/pixelstreamer.cpp"
#include "ui/widget/canvas/updaters.cpp"
#include "ui/widget/canvas/framecheck.cpp"
#include "ui/widget/canvas/glgraphics.cpp"
#include "ui/widget/canvas/cairographics.cpp"
#include "ui/widget/canvas/graphics.cpp"
#include "ui/widget/canvas-grid.cpp"
#include "ui/widget/canvas-notice.cpp"
#include "ui/widget/color-entry.cpp"
#include "ui/widget/color-notebook.cpp"
#include "ui/widget/color-palette.cpp"
#include "ui/widget/color-palette-preview.cpp"
#include "ui/widget/color-picker.cpp"
#include "ui/widget/color-preview.cpp"
#include "ui/widget/color-scales.cpp"
#include "ui/widget/color-slider.cpp"
#include "ui/widget/combo-box-entry-tool-item.cpp"
#include "ui/widget/combo-tool-item.cpp"
#include "ui/widget/css-name-class-init.cpp"
#include "ui/widget/custom-tooltip.cpp"
#include "ui/widget/dash-selector.cpp"
#include "ui/widget/desktop-widget.cpp"
#include "ui/widget/entity-entry.cpp"
#include "ui/widget/entry.cpp"
#include "ui/widget/export-lists.cpp"
#include "ui/widget/export-preview.cpp"
#include "ui/widget/filter-effect-chooser.cpp"
#include "ui/widget/fill-style.cpp"
#include "ui/widget/font-button.cpp"
#include "ui/widget/font-collection-selector.cpp"
#include "ui/widget/font-list.cpp"
#include "ui/widget/font-selector.cpp"
#include "ui/widget/font-variants.cpp"
#include "ui/widget/font-variations.cpp"
#include "ui/widget/frame.cpp"
#include "ui/widget/gradient-image.cpp"
#include "ui/widget/gradient-editor.cpp"
#include "ui/widget/gradient-selector.cpp"
#include "ui/widget/gradient-vector-selector.cpp"
#include "ui/widget/gradient-with-stops.cpp"
#include "ui/widget/icon-combobox.cpp"
#include "ui/widget/handle-preview.cpp"
#include "ui/widget/image-properties.cpp"
#include "ui/widget/imagetoggler.cpp"
#include "ui/widget/ink-color-wheel.cpp"
#include "ui/widget/ink-ruler.cpp"
#include "ui/widget/ink-spinscale.cpp"
#include "ui/widget/labelled.cpp"
#include "ui/widget/layer-selector.cpp"
#include "ui/widget/licensor.cpp"
#include "ui/widget/marker-combo-box.cpp"
#include "ui/widget/notebook-page.cpp"
#include "ui/widget/object-composite-settings.cpp"
#include "ui/widget/objects-dialog-cells.cpp"
#include "ui/widget/oklab-color-wheel.cpp"
#include "ui/widget/optglarea.cpp"
#include "ui/widget/page-properties.cpp"
#include "ui/widget/page-size-preview.cpp"
#include "ui/widget/page-selector.cpp"
#include "ui/widget/paint-selector.cpp"
#include "ui/widget/pattern-editor.cpp"
#include "ui/widget/point.cpp"
#include "ui/widget/popover-bin.cpp"
#include "ui/widget/popover-menu.cpp"
#include "ui/widget/popover-menu-item.cpp"
#include "ui/widget/preferences-widget.cpp"
#include "ui/widget/random.cpp"
#include "ui/widget/registered-widget.cpp"
#include "ui/widget/registry.cpp"
#include "ui/widget/rendering-options.cpp"
#include "ui/widget/rotateable.cpp"
#include "ui/widget/scalar-unit.cpp"
#include "ui/widget/scalar.cpp"
#include "ui/widget/scroll-utils.cpp"
#include "ui/widget/selected-style.cpp"
#include "ui/widget/shapeicon.cpp"
#include "ui/widget/spin-scale.cpp"
#include "ui/widget/spinbutton.cpp"
#include "ui/widget/status-bar.cpp"
#include "ui/widget/stroke-style.cpp"
#include "ui/widget/style-subject.cpp"
#include "ui/widget/style-swatch.cpp"
#include "ui/widget/swatch-selector.cpp"
#include "ui/widget/template-list.cpp"
#include "ui/widget/text.cpp"
#include "ui/widget/unit-menu.cpp"
#include "ui/widget/unit-tracker.cpp"
#include "ui/widget/widget-vfuncs-class-init.cpp"
#include "ui/widget/xml-treeview.cpp"
#include "ui/view/svg-view-widget.cpp"
#include "widgets/sp-attribute-widget.cpp"
#include "widgets/spw-utilities.cpp"
#include "xml/composite-node-observer.cpp"
#include "xml/croco-node-iface.cpp"
#include "xml/event.cpp"
#include "xml/log-builder.cpp"
#include "xml/node-fns.cpp"
#include "xml/node.cpp"
#include "xml/node-iterators.cpp"
#include "xml/quote.cpp"
#include "xml/repr.cpp"
#include "xml/repr-css.cpp"
#include "xml/repr-io.cpp"
#include "xml/repr-sorting.cpp"
#include "xml/repr-util.cpp"
#include "xml/simple-document.cpp"
#include "xml/simple-node.cpp"
#include "xml/subtree.cpp"
#include "xml/helper-observer.cpp"
#include "xml/rebase-hrefs.cpp"
#include "xml/href-attribute-helper.cpp"
#include "libnrtype/font-factory.cpp"
#include "libnrtype/font-instance.cpp"
#include "libnrtype/font-lister.cpp"
#include "libnrtype/Layout-TNG.cpp"
#include "libnrtype/Layout-TNG-Compute.cpp"
#include "libnrtype/Layout-TNG-Input.cpp"
#include "libnrtype/Layout-TNG-OutIter.cpp"
#include "libnrtype/Layout-TNG-Output.cpp"
#include "libnrtype/Layout-TNG-Scanline-Makers.cpp"
#include "libnrtype/OpenTypeUtil.cpp"
#include "libnrtype/style-attachments.cpp"
#include "alignment-snapper.cpp"
#include "attribute-rel-css.cpp"
#include "attribute-rel-svg.cpp"
#include "attribute-rel-util.cpp"
#include "attribute-sort-util.cpp"
#include "attributes.cpp"
#include "auto-save.cpp"
#include "axis-manip.cpp"
#include "composite-undo-stack-observer.cpp"
#include "conditions.cpp"
#include "conn-avoid-ref.cpp"
#include "console-output-undo-observer.cpp"
#include "context-fns.cpp"
#include "desktop-events.cpp"
#include "desktop-style.cpp"
#include "desktop.cpp"
#include "distribution-snapper.cpp"
#include "document-subset.cpp"
#include "document-undo.cpp"
#include "document.cpp"
#include "event-log.cpp"
#include "extract-uri.cpp"
#include "file.cpp"
#include "file-update.cpp"
#include "filter-chemistry.cpp"
#include "filter-enums.cpp"
#include "gc-anchored.cpp"
#include "gc-finalized.cpp"
#include "gradient-chemistry.cpp"
#include "gradient-drag.cpp"
#include "guide-snapper.cpp"
#include "grid-snapper.cpp"
#include "id-clash.cpp"
#include "inkscape.cpp"
#include "inkscape-version-info.cpp"
#include "layer-manager.cpp"
#include "line-geometry.cpp"
#include "line-snapper.cpp"
#include "media.cpp"
#include "message-context.cpp"
#include "message-stack.cpp"
#include "mod360.cpp"
#include "object-hierarchy.cpp"
#include "object-snapper.cpp"
#include "page-manager.cpp"
#include "path-chemistry.cpp"
#include "path-prefix.cpp"
#include "perspective-line.cpp"
#include "preferences.cpp"
#include "print.cpp"
#include "proj_pt.cpp"
#include "pure-transform.cpp"
#include "rdf.cpp"
#include "rubberband.cpp"
#include "selcue.cpp"
#include "selection-chemistry.cpp"
#include "selection-describer.cpp"
#include "selection.cpp"
#include "seltrans-handles.cpp"
#include "seltrans.cpp"
#include "snap-preferences.cpp"
#include "snap.cpp"
#include "snapped-curve.cpp"
#include "snapped-line.cpp"
#include "snapped-point.cpp"
#include "snapper.cpp"
#include "style-internal.cpp"
#include "style.cpp"
#include "text-chemistry.cpp"
#include "text-editing.cpp"
#include "transf_mat_3x4.cpp"
#include "unicoderange.cpp"
#include "vanishing-point.cpp"
#include "version.cpp"
#include "pattern-manager.cpp"
#include "pattern-manipulation.cpp"
#include "inkscape-window.cpp"
#include "inkscape-application.cpp"
#include "actions/actions-effect-data.cpp"
#include "actions/actions-extra-data.cpp"
#include "actions/actions-hint-data.cpp"
#include "actions/actions-base.cpp"
#include "actions/actions-canvas-mode.cpp"
#include "actions/actions-canvas-snapping.cpp"
#include "actions/actions-canvas-transform.cpp"
#include "actions/actions-dialogs.cpp"
#include "actions/actions-edit-document.cpp"
#include "actions/actions-edit-window.cpp"
#include "actions/actions-edit.cpp"
#include "actions/actions-effect.cpp"
#include "actions/actions-element-a.cpp"
#include "actions/actions-element-image.cpp"
#include "actions/actions-file-window.cpp"
#include "actions/actions-file.cpp"
#include "actions/actions-helper.cpp"
#include "actions/actions-helper-gui.cpp"
#include "actions/actions-help-url.cpp"
#include "actions/actions-hide-lock.cpp"
#include "actions/actions-layer.cpp"
#include "actions/actions-node-align.cpp"
#include "actions/actions-object.cpp"
#include "actions/actions-object-align.cpp"
#include "actions/actions-output.cpp"
#include "actions/actions-paths.cpp"
#include "actions/actions-selection-object.cpp"
#include "actions/actions-selection-window.cpp"
#include "actions/actions-selection.cpp"
#include "actions/actions-text.cpp"
#include "actions/actions-tools.cpp"
#include "actions/actions-tutorial.cpp"
#include "actions/actions-transform.cpp"
#include "actions/actions-undo-document.cpp"
#include "actions/actions-view-mode.cpp"
#include "actions/actions-view-window.cpp"
#include "actions/actions-window.cpp"
#include "actions/actions-pages.cpp"
#include "actions/actions-svg-processing.cpp"
#include "inkview-application.cpp"
#include "inkview-window.cpp"
#include "manipulation/copy-resource.cpp"
#include "inkscape-main.cpp"