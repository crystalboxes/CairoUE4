// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "CairoFunctionLibrary.generated.h"

/**
 *
 */

class CairoContext;

UENUM(BlueprintType)
enum class EFontSlant : uint8 {
  FONT_SLANT_NORMAL UMETA(DisplayName = "Normal"),
  FONT_SLANT_ITALIC UMETA(DisplayName = "Italic"),
  FONT_SLANT_OBLIQUE UMETA(DisplayName = "Oblique")
};

UENUM(BlueprintType)
enum class EFontWeight : uint8 {
  FONT_FONT_WEIGHT_NORMAL UMETA(DisplayName = "Normal"),
  FONT_FONT_WEIGHT_BOLD UMETA(DisplayName = "Bold"),
};

USTRUCT(BlueprintType)
struct FCairoMatrix {
  GENERATED_BODY()

  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float xx = 0;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float yx = 0;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float xy = 0;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float yy = 0;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float x0 = 0;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float y0 = 0;
};

UENUM(BlueprintType)
enum class ECairoOperator : uint8 {
  CLEAR UMETA(DisplayName = "Clear"),

  SOURCE UMETA(DisplayName = "Source"),
  OVER UMETA(DisplayName = "Over"),
  OP_IN UMETA(DisplayName = "In"),
  OP_OUT UMETA(DisplayName = "Out"),
  ATOP UMETA(DisplayName = "Atop"),

  DEST UMETA(DisplayName = "Dest"),
  DEST_OVER UMETA(DisplayName = "Dest Over"),
  DEST_IN UMETA(DisplayName = "Dest In"),
  DEST_OUT UMETA(DisplayName = "Dest Out"),
  DEST_ATOP UMETA(DisplayName = "Dest Atop"),

  XOR UMETA(DisplayName = "Xor"),
  ADD UMETA(DisplayName = "Add"),
  SATURATE UMETA(DisplayName = "Saturate"),

  MULTIPLY UMETA(DisplayName = "Multiply"),
  SCREEN UMETA(DisplayName = "Screen"),
  OVERLAY UMETA(DisplayName = "Overlay"),
  DARKEN UMETA(DisplayName = "Darken"),
  LIGHTEN UMETA(DisplayName = "Lighten"),
  COLOR_DODGE UMETA(DisplayName = "Color Dodge"),
  COLOR_BURN UMETA(DisplayName = "Color Burn"),
  HARD_LIGHT UMETA(DisplayName = "Hard Light"),
  SOFT_LIGHT UMETA(DisplayName = "Soft Light"),
  DIFFERENCE UMETA(DisplayName = "Difference"),
  EXCLUSION UMETA(DisplayName = "Exclusion"),
  HSL_HUE UMETA(DisplayName = "HSL Hue"),
  HSL_SATURATION UMETA(DisplayName = "HSL Saturation"),
  HSL_COLOR UMETA(DisplayName = "HSL Color"),
  HSL_LUMINOSITY UMETA(DisplayName = "HSL Luminocity"),
};

UENUM(BlueprintType)
enum class ECairoAntialias : uint8 {
  ANTIALIAS_DEFAULT UMETA(DisplayName = "Default"),

  /* method */
  ANTIALIAS_NONE UMETA(DisplayName = "None"),
  ANTIALIAS_GRAY UMETA(DisplayName = "Gray"),
  ANTIALIAS_SUBPIXEL UMETA(DisplayName = "Subpixel"),

  /* hints */
  ANTIALIAS_FAST UMETA(DisplayName = "Fast"),
  ANTIALIAS_GOOD UMETA(DisplayName = "Good"),
  ANTIALIAS_BEST UMETA(DisplayName = "Best"),
};

UENUM(BlueprintType)
enum class EFillRule : uint8 {
  FILL_RULE_WINDING UMETA(DisplayName = "Fill Rule Winding"),
  FILL_RULE_EVEN_ODD UMETA(DisplayName = "Fill Rule Even Odd"),
};

UENUM(BlueprintType)
enum class ELineCap : uint8 {
  LINE_CAP_BUTT UMETA(DisplayName = "Butt"),
  LINE_CAP_ROUND UMETA(DisplayName = "Round"),
  LINE_CAP_SQUARE UMETA(DisplayName = "Square"),
};

UENUM(BlueprintType)
enum class ELineJoin : uint8 {
  LINE_JOIN_MITER UMETA(DisplayName = "Miter"),
  LINE_JOIN_ROUND UMETA(DisplayName = "Round"),
  LINE_JOIN_BEVEL UMETA(DisplayName = "Bevel"),
};

UENUM(BlueprintType)
enum class ECairoContent : uint8 {
  CONTENT_COLOR UMETA(DisplayName = "Color"),
  CONTENT_ALPHA UMETA(DisplayName = "Alpha"),
  CONTENT_COLOR_ALPHA UMETA(DisplayName = "Color + Alpha")
};

USTRUCT(BlueprintType)
struct FCairoPattern {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoScaledFont {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoSurface {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoRectangle {
  GENERATED_BODY()
  float X;
  float Y;
  float Width;
  float Height;
};

UENUM(BlueprintType)
enum class ECairoStatus : uint8 {
  CAIRO_STATUS_SUCCESS,
  CAIRO_STATUS_NO_MEMORY,
  CAIRO_STATUS_INVALID_RESTORE,
  CAIRO_STATUS_INVALID_POP_GROUP,
  CAIRO_STATUS_NO_CURRENT_POINT,
  CAIRO_STATUS_INVALID_MATRIX,
  CAIRO_STATUS_INVALID_STATUS,
  CAIRO_STATUS_NULL_POINTER,
  CAIRO_STATUS_INVALID_STRING,
  CAIRO_STATUS_INVALID_PATH_DATA,
  CAIRO_STATUS_READ_ERROR,
  CAIRO_STATUS_WRITE_ERROR,
  CAIRO_STATUS_SURFACE_FINISHED,
  CAIRO_STATUS_SURFACE_TYPE_MISMATCH,
  CAIRO_STATUS_PATTERN_TYPE_MISMATCH,
  CAIRO_STATUS_INVALID_CONTENT,
  CAIRO_STATUS_INVALID_FORMAT,
  CAIRO_STATUS_INVALID_VISUAL,
  CAIRO_STATUS_FILE_NOT_FOUND,
  CAIRO_STATUS_INVALID_DASH,
  CAIRO_STATUS_INVALID_DSC_COMMENT,
  CAIRO_STATUS_INVALID_INDEX,
  CAIRO_STATUS_CLIP_NOT_REPRESENTABLE,
  CAIRO_STATUS_TEMP_FILE_ERROR,
  CAIRO_STATUS_INVALID_STRIDE,
  CAIRO_STATUS_FONT_TYPE_MISMATCH,
  CAIRO_STATUS_USER_FONT_IMMUTABLE,
  CAIRO_STATUS_USER_FONT_ERROR,
  CAIRO_STATUS_NEGATIVE_COUNT,
  CAIRO_STATUS_INVALID_CLUSTERS,
  CAIRO_STATUS_INVALID_SLANT,
  CAIRO_STATUS_INVALID_WEIGHT,
  CAIRO_STATUS_INVALID_SIZE,
  CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED,
  CAIRO_STATUS_DEVICE_TYPE_MISMATCH,
  CAIRO_STATUS_DEVICE_ERROR,
  CAIRO_STATUS_INVALID_MESH_CONSTRUCTION,
  CAIRO_STATUS_DEVICE_FINISHED,
  CAIRO_STATUS_JBIG2_GLOBAL_MISSING,
  CAIRO_STATUS_PNG_ERROR,
  CAIRO_STATUS_FREETYPE_ERROR,
  CAIRO_STATUS_WIN32_GDI_ERROR,
  CAIRO_STATUS_TAG_ERROR,

  CAIRO_STATUS_LAST_STATUS
};

UENUM(BlueprintType)
enum class ECairoSubpixelOrder : uint8 {
  CAIRO_SUBPIXEL_ORDER_DEFAULT,
  CAIRO_SUBPIXEL_ORDER_RGB,
  CAIRO_SUBPIXEL_ORDER_BGR,
  CAIRO_SUBPIXEL_ORDER_VRGB,
  CAIRO_SUBPIXEL_ORDER_VBGR
};

UENUM(BlueprintType)
enum class ECairoHintStyle : uint8 {
  CAIRO_HINT_STYLE_DEFAULT,
  CAIRO_HINT_STYLE_NONE,
  CAIRO_HINT_STYLE_SLIGHT,
  CAIRO_HINT_STYLE_MEDIUM,
  CAIRO_HINT_STYLE_FULL
};

UENUM(BlueprintType)
enum class ECairoHintMetrics : uint8 { CAIRO_HINT_METRICS_DEFAULT, CAIRO_HINT_METRICS_OFF, CAIRO_HINT_METRICS_ON };

UENUM(BlueprintType)
enum class ECairoClusterFlags : uint8 { CAIRO_TEXT_CLUSTER_FLAG_BACKWARD = 1 };

USTRUCT(BlueprintType)
struct FCairoRectangleList {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoGlyph {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoTextCluster {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoFontFace {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoFontOptions {
  GENERATED_BODY()
  void *Inner = nullptr;
};

USTRUCT(BlueprintType)
struct FCairoTextExtents {
  GENERATED_BODY()
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float XBearing;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float YBearing;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float Width;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float Height;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float XAdvance;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float YAdvance;
};

USTRUCT(BlueprintType)
struct FCairoFontExtents {
  GENERATED_BODY()
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float Ascent;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float Descent;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float Height;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float MaxXAdvance;
  UPROPERTY(BlueprintReadWrite, Category = Cairo)
  float MaxYAdvance;
};

UCLASS()
class CAIROUE4_API UCairoFunctionLibrary : public UBlueprintFunctionLibrary {
  GENERATED_BODY()

  UFUNCTION(BlueprintCallable, Category = "Cairo", meta = (WorldContext = "WorldContextObject"))
  static UCairoContext *Create(UObject *WorldContextObject, int Width, int Height);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Destroy(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Save(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Restore(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void PushGroup(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void PushGroupWithContent(UCairoContext *Context, ECairoContent Content);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoPattern PopGroup(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void PopGroupToSource(UCairoContext *Context);

  /* Modify state */

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetOperator(UCairoContext *Context, ECairoOperator Operator);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetSource(UCairoContext *Context, const FCairoPattern &Source);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetSourceRGB(UCairoContext *Context, float Red, float Green, float Blue);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetSourceRGBA(UCairoContext *Context, const FLinearColor &RGBA);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetSourceSurface(UCairoContext *Context, const FCairoSurface &Surface, const FVector2D &Pos);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetTolerance(UCairoContext *Context, float Tolerance);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetAntialias(UCairoContext *Context, ECairoAntialias Antialias);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetFillRule(UCairoContext *Context, EFillRule FillRule);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetLineWidth(UCairoContext *Context, float Width);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetLineCap(UCairoContext *Context, ELineCap LineCap);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetLineJoin(UCairoContext *Context, ELineJoin LineJoin);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetDash(UCairoContext *Context, const TArray<float> &Dashes, int NumDashes, float Offset);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetMiterLimit(UCairoContext *Context, float Limit);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Translate(UCairoContext *Context, const FVector2D &Translation);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Scale(UCairoContext *Context, const FVector2D &Scale);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Rotate(UCairoContext *Context, float Angle);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Transform(UCairoContext *Context, const FCairoMatrix &Matrix);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetMatrix(UCairoContext *Context, const FCairoMatrix &Matrix);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void IdentityMatrix(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FVector2D UserToDevice(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FVector2D UserToDeviceDistance(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FVector2D DeviceToUser(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FVector2D DeviceToUserDistance(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void NewPath(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void MoveTo(UCairoContext *Context, const FVector2D &Position);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void NewSubPath(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void LineTo(UCairoContext *Context, const FVector2D &Position);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void CurveTo(UCairoContext *Context, const FVector2D &P1, const FVector2D &P2, const FVector2D &P3);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Arc(UCairoContext *Context, const FVector2D &Center, float Radius, float Angle1, float Angle2);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ArcNegative(UCairoContext *Context, const FVector2D &Center, float Radius, float Angle1, float Angle2);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void RelMoveTo(UCairoContext *Context, const FVector2D &Position);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void RelLineTo(UCairoContext *Context, const FVector2D &Position);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void RelCurveTo(UCairoContext *Context, const FVector2D &P1, const FVector2D &P2, const FVector2D &P3);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Rectangle(UCairoContext *Context, const FVector2D &XY, const FVector2D &Size);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ClosePath(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void PathExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Paint(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void PaintWithAlpha(UCairoContext *Context, float Alpha);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Mask(UCairoContext *Context, const FCairoPattern &Pattern);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void MaskSurface(UCairoContext *Context, const FCairoSurface &Surface, const FVector2D &Dimensions);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Stroke(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void StrokePreserve(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Fill(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FillPreserve(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void CopyPage(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ShowPage(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void InStroke(UCairoContext *Context, const FVector2D &XY);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void InFill(UCairoContext *Context, const FVector2D &XY);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void InClip(UCairoContext *Context, const FVector2D &XY);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void StrokeExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FillExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ResetClip(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void Clip(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ClipPreserve(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ClipExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2);

  // cairo_rectangle_t
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static TArray<FCairoRectangle> RectanglesFromList(UPARAM(ref) FCairoRectangleList &List) {
    check(false);
    return {};
  }

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoRectangleList CopyClipRectangleList(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void RectangleListDestroy(const FCairoRectangleList &RectangleList);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void TagBegin(UCairoContext *Context, const FString &TagName, const FString &Attributes);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void TagEnd(UCairoContext *Context, const FString &TagName);

  // cairo_glyph_t
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FVector2D GetGlyphPosition(const FCairoGlyph &Glyph);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static int GetGlyphIndex(const FCairoGlyph &Glyph);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoGlyph GlyphAllocate(int NumGlyphs);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void GlyphFree(UPARAM(ref) FCairoGlyph &Glyphs);

  // cairo_text_cluster_t
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static int GetClusterNumBytes(const FCairoTextCluster &Cl);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static int GetClusterNumGlyphs(const FCairoTextCluster &Cl);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoTextCluster TextClusterAllocate(int NumClusters);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void TextClusterFree(UPARAM(ref) FCairoTextCluster &Clusters);

  // cairo_font_options_t

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoFontOptions FontOptionsCreate();

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoFontOptions FontOptionsCopy(const FCairoFontOptions &Original);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsDestroy(UPARAM(ref) FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static ECairoStatus FontOptionsStatus(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsMerge(const FCairoFontOptions &Options, const FCairoFontOptions &Other);
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static bool FontOptionsEqual(const FCairoFontOptions &Options, const FCairoFontOptions &Other);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static int FontOptionsHash(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsSetAntialias(UPARAM(ref) FCairoFontOptions &options, ECairoAntialias Antialias);
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static ECairoAntialias FontOptionsGetAntialias(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsSetSubpixelOrder(UPARAM(ref) FCairoFontOptions &Options, ECairoSubpixelOrder SubpixelOrder);
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static ECairoSubpixelOrder FontOptionsGetSubpixelOrder(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsSetHintStyle(UPARAM(ref) FCairoFontOptions &options, ECairoHintStyle HintStyle);
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static ECairoHintStyle FontOptionsGetHintStyle(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsSetHintMetrics(UPARAM(ref) FCairoFontOptions &Options, ECairoHintMetrics Hint_metrics);
  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static ECairoHintMetrics FontOptionsGetHintMetrics(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FString FontOptionsGetVariations(const FCairoFontOptions &Options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontOptionsSetVariations(UPARAM(ref) FCairoFontOptions &Options, const FString &Variations);

  //

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SelectFontFace(UCairoContext *Context, const FString &Family, EFontSlant Slant, EFontWeight Weight);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetFontSize(UCairoContext *Context, float Size);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetFontMatrix(UCairoContext *Context, const FCairoMatrix &Matrix);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoMatrix GetFontMatrix(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetFontOptions(UCairoContext *Context, const FCairoFontOptions &options);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoFontOptions GetFontOptions(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetFontFace(UCairoContext *Context, const FCairoFontFace &FontFace);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoFontFace GetFontFace(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void SetScaledFont(UCairoContext *Context, const FCairoScaledFont &scaled_font);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoScaledFont GetScaledFont(UCairoContext *Context);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ShowGlyphs(UCairoContext *C, const FCairoGlyph &Glyphs, int NumGlyphs);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ShowTextGlyphs(UCairoContext *C, const FString &Text, const FCairoGlyph &Glyphs, int NumGlyphs,
                             const TArray<FCairoTextCluster> &Clusters, ECairoClusterFlags ClusterFlags);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void TextPath(UCairoContext *Context, const FString &Text);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void GlyphPath(UCairoContext *C, const FCairoGlyph &Glyphs, int NumGlyphs);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void GlyphExtents(UCairoContext *C, const FCairoGlyph &Glyphs, int NumGlyphs,
                           UPARAM(ref) FCairoTextExtents &extents);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontExtents(UCairoContext *Context, UPARAM(ref) FCairoTextExtents &extents);

  /* Generic identifier for a font style */

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FCairoFontFace FontFaceReference(const FCairoFontFace &FontFace);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void FontFaceDestroy(UPARAM(ref) FCairoFontFace &FontFace);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static int FontFaceGetReferenceCount(const FCairoFontFace &FontFace);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static ECairoStatus FontFaceStatus(const FCairoFontFace &FontFace);

  // 1534 font_type_t

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void ShowText(UCairoContext *Context, const FString &Text);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static FVector2D TextExtents(UCairoContext *Context, const FString &Text);

  UFUNCTION(BlueprintCallable, Category = "Cairo")
  static void RefreshContextTexture(UCairoContext *Context);
};
