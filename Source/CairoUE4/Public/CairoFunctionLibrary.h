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
enum class EFontSlant : uint8
{
	FONT_SLANT_NORMAL UMETA(DisplayName = "Normal"),
	FONT_SLANT_ITALIC UMETA(DisplayName = "Italic"),
	FONT_SLANT_OBLIQUE UMETA(DisplayName = "Oblique")
};

UENUM(BlueprintType)
enum class EFontWeight : uint8
{
	FONT_FONT_WEIGHT_NORMAL UMETA(DisplayName = "Normal"),
	FONT_FONT_WEIGHT_BOLD UMETA(DisplayName = "Bold"),
};

USTRUCT(BlueprintType)
struct FCairoMatrix
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	float xx = 0;
	UPROPERTY(BlueprintReadWrite)
	float yx = 0;
	UPROPERTY(BlueprintReadWrite)
	float xy = 0;
	UPROPERTY(BlueprintReadWrite)
	float yy = 0;
	UPROPERTY(BlueprintReadWrite)
	float x0 = 0;
	UPROPERTY(BlueprintReadWrite)
	float y0 = 0;
};

UENUM(BlueprintType)
enum class ECairoOperator : uint8
{
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
enum class ECairoAntialias : uint8
{
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
enum class EFillRule : uint8
{
	FILL_RULE_WINDING UMETA(DisplayName = "Fill Rule Winding"),
	FILL_RULE_EVEN_ODD UMETA(DisplayName = "Fill Rule Even Odd"),
};

UENUM(BlueprintType)
enum class ELineCap : uint8
{
	LINE_CAP_BUTT UMETA(DisplayName = "Butt"),
	LINE_CAP_ROUND UMETA(DisplayName = "Round"),
	LINE_CAP_SQUARE UMETA(DisplayName = "Square"),
};

UENUM(BlueprintType)
enum class ELineJoin : uint8
{
	LINE_JOIN_MITER UMETA(DisplayName = "Miter"),
	LINE_JOIN_ROUND UMETA(DisplayName = "Round"),
	LINE_JOIN_BEVEL UMETA(DisplayName = "Bevel"),
};

UCLASS()
class CAIROUE4_API UCairoFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Cairo", meta = (WorldContext = "WorldContextObject"))
	static UCairoContext *InitCairoSurface(UObject *WorldContextObject, int Width, int Height);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void DestroyContext(UCairoContext *Context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetSourceRGBA(UCairoContext *Context, const FLinearColor &RGBA);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetSourceRGB(UCairoContext *Context, float Red, float Green, float Blue);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetOperator(UCairoContext *Context, ECairoOperator Operator);

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

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SelectFontFace(UCairoContext *Context, const FString &Family, EFontSlant Slant, EFontWeight Weight);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetFontSize(UCairoContext *Context, float Size);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void ShowText(UCairoContext *Context, const FString &Text);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static FVector2D TextExtents(UCairoContext *Context, const FString &Text);

	//cairo_public cairo_operator_t cairo_get_operator(cairo_t *cr);

	//cairo_public cairo_pattern_t *cairo_get_source(cairo_t *cr);

	//cairo_public double cairo_get_tolerance(cairo_t *cr);

	//cairo_public cairo_antialias_t cairo_get_antialias(cairo_t *cr);

	//cairo_public cairo_bool_t cairo_has_current_point(cairo_t *cr);

	//cairo_public void cairo_get_current_point(cairo_t *cr, double *x, double *y);

	//cairo_public cairo_fill_rule_t cairo_get_fill_rule(cairo_t *cr);

	//cairo_public double cairo_get_line_width(cairo_t *cr);

	//cairo_public cairo_line_cap_t cairo_get_line_cap(cairo_t *cr);

	//cairo_public cairo_line_join_t cairo_get_line_join(cairo_t *cr);

	//cairo_public double cairo_get_miter_limit(cairo_t *cr);

	//cairo_public int cairo_get_dash_count(cairo_t *cr);

	//cairo_public void cairo_get_dash(cairo_t *cr, double *dashes, double *offset);

	//cairo_public void cairo_get_matrix(cairo_t *cr, cairo_matrix_t *matrix);

	//cairo_public cairo_surface_t *cairo_get_target(cairo_t *cr);

	//cairo_public cairo_surface_t *cairo_get_group_target(cairo_t *cr);


	// TODO
	// Rectangle List (cairo_rectangle_list_t)
	// Tags Logical structure tagging functions
	// Glypth allocate
	// cairo_font_type_t
	// FUNCTIONs
	// cairo_set_font_matrix
	// cairo_get_font_matrix
	// cairo_set_font_options
	// cairo_get_font_options
	// cairo_set_font_face
	// cairo_get_font_face
	// cairo_set_scaled_font
	// cairo_get_scaled_font
	// cairo_show_glyphs
	// cairo_show_text_glyphs
	// cairo_text_path
	// cairo_glyph_path
	// cairo_glyph_extents
	// cairo_font_extents
	// cairo_font_face_reference
	// cairo_font_face_destroy
	// cairo_font_face_get_reference_count
	// cairo_font_face_status
	// Cairo status
	// cairo path
	// device type
	// cairo_surface_observer_mode_t
	// cairo_pattern_type_t
	// cairo_filter_t
	// cairo_region_overlap_t

	// cairo_public void
	// cairo_mask (cairo_t         *cr,
	// 	    cairo_pattern_t *pattern);

	// cairo_public void
	// cairo_mask_surface (cairo_t         *cr,
	// 		    cairo_surface_t *surface,
	// 		    double           surface_x,
	// 		    double           surface_y);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void RefreshContextTexture(UCairoContext *Context);
};
