#include "CairoUE4.h"
#include "Modules/ModuleManager.h"
IMPLEMENT_MODULE(FDefaultGameModuleImpl, CairoUE4)

#include <cairo/cairo.h>

#include "CairoFunctionLibrary.h"
#include "CairoContext.h"

void UCairoFunctionLibrary::Save(UCairoContext *C) {
  cairo_save(C->ctx);
}
void UCairoFunctionLibrary::Restore(UCairoContext *C) {
  cairo_restore(C->ctx);
}
void UCairoFunctionLibrary::PushGroup(UCairoContext *C) {
  cairo_push_group(C->ctx);
}
void UCairoFunctionLibrary::PushGroupWithContent(UCairoContext *C, ECairoContent Content) {
  cairo_push_group_with_content(C->ctx, (cairo_content_t)Content);
}
FCairoPattern UCairoFunctionLibrary::PopGroup(UCairoContext *C) {
  return {cairo_pop_group(C->ctx)};
}
void UCairoFunctionLibrary::PopGroupToSource(UCairoContext *C) {
  cairo_pop_group_to_source(C->ctx);
}
void UCairoFunctionLibrary::SetSource(UCairoContext *C, const FCairoPattern &Source) {
  cairo_set_source(C->ctx, (cairo_pattern_t *)Source.Inner);
}
void UCairoFunctionLibrary::SetSourceSurface(UCairoContext *C, const FCairoSurface &Surface, const FVector2D &Pos) {
  cairo_set_source_surface(C->ctx, (cairo_surface_t *)Surface.Inner, Pos.X, Pos.Y);
}
void UCairoFunctionLibrary::Mask(UCairoContext *C, const FCairoPattern &Pattern) {
  cairo_mask(C->ctx, (cairo_pattern_t *)Pattern.Inner);
}
void UCairoFunctionLibrary::MaskSurface(UCairoContext *C, const FCairoSurface &Surface, const FVector2D &Dimensions) {
  cairo_mask_surface(C->ctx, (cairo_surface_t *)Surface.Inner, Dimensions.X, Dimensions.Y);
}
FCairoRectangleList UCairoFunctionLibrary::CopyClipRectangleList(UCairoContext *C) {
  return {cairo_copy_clip_rectangle_list(C->ctx)};
}
void UCairoFunctionLibrary::RectangleListDestroy(const FCairoRectangleList &RectangleList) {
  cairo_rectangle_list_destroy((cairo_rectangle_list_t *)RectangleList.Inner);
}
void UCairoFunctionLibrary::TagBegin(UCairoContext *C, const FString &TagName, const FString &Attributes) {
  cairo_tag_begin(C->ctx, TCHAR_TO_ANSI(*TagName), TCHAR_TO_ANSI(*Attributes));
}
void UCairoFunctionLibrary::TagEnd(UCairoContext *C, const FString &TagName) {
  cairo_tag_end(C->ctx, TCHAR_TO_ANSI(*TagName));
}
FVector2D UCairoFunctionLibrary::GetGlyphPosition(const FCairoGlyph &Glyph) {
  const cairo_glyph_t &g = *(cairo_glyph_t *)Glyph.Inner;
  return {(float)g.x, (float)g.y};
}
int UCairoFunctionLibrary::GetGlyphIndex(const FCairoGlyph &Glyph) {
  const cairo_glyph_t &g = *(cairo_glyph_t *)Glyph.Inner;
  return g.index;
}

void UCairoFunctionLibrary::ShowGlyphs(UCairoContext *C, const FCairoGlyph &Glyphs, int NumGlyphs) {
  cairo_show_glyphs(C->ctx, (cairo_glyph_t *)Glyphs.Inner, NumGlyphs);
}

FCairoGlyph UCairoFunctionLibrary::GlyphAllocate(int NumGlyphs) {
  return {cairo_glyph_allocate(NumGlyphs)};
}
void UCairoFunctionLibrary::GlyphFree(FCairoGlyph &Glyphs) {
  cairo_glyph_free((cairo_glyph_t *)Glyphs.Inner);
}
int UCairoFunctionLibrary::GetClusterNumBytes(const FCairoTextCluster &Cl) {
  const cairo_text_cluster_t &cl = *(cairo_text_cluster_t *)Cl.Inner;
  return cl.num_bytes;
}
int UCairoFunctionLibrary::GetClusterNumGlyphs(const FCairoTextCluster &Cl) {
  const cairo_text_cluster_t &cl = *(cairo_text_cluster_t *)Cl.Inner;
  return cl.num_glyphs;
}
FCairoTextCluster UCairoFunctionLibrary::TextClusterAllocate(int NumClusters) {
  return {cairo_text_cluster_allocate(NumClusters)};
}
void UCairoFunctionLibrary::TextClusterFree(FCairoTextCluster &Clusters) {
  cairo_text_cluster_free((cairo_text_cluster_t *)Clusters.Inner);
}
FCairoFontOptions UCairoFunctionLibrary::FontOptionsCreate() {
  return {cairo_font_options_create()};
}
FCairoFontOptions UCairoFunctionLibrary::FontOptionsCopy(const FCairoFontOptions &Original) {
  return {cairo_font_options_copy((cairo_font_options_t *)Original.Inner)};
}
void UCairoFunctionLibrary::FontOptionsDestroy(FCairoFontOptions &Options) {
  cairo_font_options_destroy((cairo_font_options_t *)Options.Inner);
}
ECairoStatus UCairoFunctionLibrary::FontOptionsStatus(const FCairoFontOptions &Options) {
  return (ECairoStatus)cairo_font_options_status((cairo_font_options_t *)Options.Inner);
}
void UCairoFunctionLibrary::FontOptionsMerge(const FCairoFontOptions &Options, const FCairoFontOptions &Other) {
  cairo_font_options_merge((cairo_font_options_t *)Options.Inner, (cairo_font_options_t *)Other.Inner);
}
bool UCairoFunctionLibrary::FontOptionsEqual(const FCairoFontOptions &Options, const FCairoFontOptions &Other) {
  return cairo_font_options_equal((cairo_font_options_t *)Options.Inner, (cairo_font_options_t *)Other.Inner);
}
int UCairoFunctionLibrary::FontOptionsHash(const FCairoFontOptions &Options) {
  return cairo_font_options_hash((cairo_font_options_t *)Options.Inner);
}
void UCairoFunctionLibrary::FontOptionsSetAntialias(FCairoFontOptions &Options, ECairoAntialias Antialias) {
  cairo_font_options_set_antialias((cairo_font_options_t *)Options.Inner, (cairo_antialias_t)Antialias);
}
ECairoAntialias UCairoFunctionLibrary::FontOptionsGetAntialias(const FCairoFontOptions &Options) {
  return (ECairoAntialias)cairo_font_options_get_antialias((cairo_font_options_t *)Options.Inner);
}
void UCairoFunctionLibrary::FontOptionsSetSubpixelOrder(FCairoFontOptions &Options, ECairoSubpixelOrder SubpixelOrder) {
  check(false && "Not Implemented");
}
ECairoSubpixelOrder UCairoFunctionLibrary::FontOptionsGetSubpixelOrder(const FCairoFontOptions &Options) {
  return (ECairoSubpixelOrder)cairo_font_options_get_subpixel_order((cairo_font_options_t *)Options.Inner);
}
void UCairoFunctionLibrary::FontOptionsSetHintStyle(FCairoFontOptions &options, ECairoHintStyle HintStyle) {
  check(false && "Not Implemented");
}
ECairoHintStyle UCairoFunctionLibrary::FontOptionsGetHintStyle(const FCairoFontOptions &Options) {
  return (ECairoHintStyle)cairo_font_options_get_hint_style((cairo_font_options_t *)Options.Inner);
}
void UCairoFunctionLibrary::FontOptionsSetHintMetrics(FCairoFontOptions &Options, ECairoHintMetrics Hint_metrics) {
  check(false && "Not Implemented");
}
ECairoHintMetrics UCairoFunctionLibrary::FontOptionsGetHintMetrics(const FCairoFontOptions &Options) {
  return (ECairoHintMetrics)cairo_font_options_get_hint_metrics((cairo_font_options_t *)Options.Inner);
}
FString UCairoFunctionLibrary::FontOptionsGetVariations(const FCairoFontOptions &Options) {
  return cairo_font_options_get_variations((cairo_font_options_t *)Options.Inner);
}
void UCairoFunctionLibrary::FontOptionsSetVariations(FCairoFontOptions &Options, const FString &Variations) {
  check(false && "Not Implemented");
}
void UCairoFunctionLibrary::SetFontMatrix(UCairoContext *C, const FCairoMatrix &Matrix) {
  cairo_matrix_t matrix = {Matrix.xx, Matrix.yx, Matrix.xy, Matrix.yy, Matrix.x0, Matrix.y0};
  cairo_set_font_matrix(C->ctx, &matrix);
}
FCairoMatrix UCairoFunctionLibrary::GetFontMatrix(UCairoContext *C) {
  cairo_matrix_t matrix;
  cairo_get_font_matrix(C->ctx, &matrix);
  return {(float)matrix.xx, (float)matrix.yx, (float)matrix.xy, (float)matrix.yy, (float)matrix.x0, (float)matrix.y0};
}
void UCairoFunctionLibrary::SetFontOptions(UCairoContext *C, const FCairoFontOptions &options) {
  check(false && "Not Implemented");
}
FCairoFontOptions UCairoFunctionLibrary::GetFontOptions(UCairoContext *C) {
  check(false && "Not Implemented");
  return {nullptr};
}
void UCairoFunctionLibrary::SetFontFace(UCairoContext *C, const FCairoFontFace &FontFace) {
  check(false && "Not Implemented");
}
FCairoFontFace UCairoFunctionLibrary::GetFontFace(UCairoContext *C) {
  return {cairo_get_font_face(C->ctx)};
}
void UCairoFunctionLibrary::SetScaledFont(UCairoContext *C, const FCairoScaledFont &scaled_font) {
  check(false && "Not Implemented");
}
FCairoScaledFont UCairoFunctionLibrary::GetScaledFont(UCairoContext *C) {
  return {cairo_get_scaled_font(C->ctx)};
}
void UCairoFunctionLibrary::ShowTextGlyphs(UCairoContext *C, const FString &Text, const FCairoGlyph &Glyphs,
                                                int NumGlyphs,
                         const TArray<FCairoTextCluster> &Clusters, ECairoClusterFlags ClusterFlags) {
  check(false && "Not Implemented");
}
void UCairoFunctionLibrary::TextPath(UCairoContext *C, const FString &Text) {
  check(false && "Not Implemented");
}
void UCairoFunctionLibrary::GlyphPath(UCairoContext *C, const FCairoGlyph &Glyphs, int NumGlyphs) {
  check(false && "Not Implemented");
}
void UCairoFunctionLibrary::GlyphExtents(UCairoContext *C, const FCairoGlyph &Glyphs, int NumGlyphs,
                                              FCairoTextExtents &extents) {
  check(false && "Not Implemented");
}
void UCairoFunctionLibrary::FontExtents(UCairoContext *C, FCairoTextExtents &extents) {
  check(false && "Not Implemented");
}
FCairoFontFace UCairoFunctionLibrary::FontFaceReference(const FCairoFontFace &FontFace) {
  return {cairo_font_face_reference((cairo_font_face_t *)FontFace.Inner)};
}
void UCairoFunctionLibrary::FontFaceDestroy(FCairoFontFace &FontFace) {
  check(false && "Not Implemented");
}
int UCairoFunctionLibrary::FontFaceGetReferenceCount(const FCairoFontFace &FontFace) {
  return cairo_font_face_get_reference_count((cairo_font_face_t *)FontFace.Inner);
}
ECairoStatus UCairoFunctionLibrary::FontFaceStatus(const FCairoFontFace &FontFace) {
  return (ECairoStatus)cairo_font_face_status((cairo_font_face_t *)FontFace.Inner);
}
