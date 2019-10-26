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
	static void Paint(UCairoContext *Context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void MoveTo(UCairoContext *Context, const FVector2D &Position);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void LineTo(UCairoContext *Context, const FVector2D &Position);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void Rectangle(UCairoContext *Context, const FVector2D &XY, const FVector2D &Size);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void Arc(UCairoContext *Context, const FVector2D &Center, float Radius, float Angle1, float Angle2);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void ArcNegative(UCairoContext *Context, const FVector2D &Center, float Radius, float Angle1, float Angle2);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void NewSubPath(UCairoContext *Context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void ClosePath(UCairoContext *Context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void Fill(UCairoContext *Context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void Stroke(UCairoContext *Context);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SelectFontFace(UCairoContext *Context, const FString &Family, EFontSlant Slant, EFontWeight Weight);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static FVector2D TextExtents(UCairoContext *Context, const FString &Text);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void SetFontSize(UCairoContext *Context, float Size);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void ShowText(UCairoContext *Context, const FString &Text);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void RefreshContextTexture(UCairoContext *Context);

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

	// TODO use fvector2d
	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void Scale(UCairoContext *Context, const FVector2D &Scale);

	UFUNCTION(BlueprintCallable, Category = "Cairo")
	static void Rotate(UCairoContext *Context, float Angle);

	// TODO

	// cairo_public void
	// cairo_transform (cairo_t	      *cr,
	// 		 const cairo_matrix_t *matrix);

	// cairo_public void
	// cairo_set_matrix (cairo_t	       *cr,
	// 		  const cairo_matrix_t *matrix);

	// cairo_public void
	// cairo_identity_matrix (cairo_t *cr);

	// cairo_public void
	// cairo_user_to_device (cairo_t *cr, double *x, double *y);

	// cairo_public void
	// cairo_user_to_device_distance (cairo_t *cr, double *dx, double *dy);

	// cairo_public void
	// cairo_device_to_user (cairo_t *cr, double *x, double *y);

	// cairo_public void
	// cairo_device_to_user_distance (cairo_t *cr, double *dx, double *dy);

	// /* Path creation functions */
	// cairo_public void
	// cairo_new_path (cairo_t *cr);

	// cairo_public void
	// cairo_move_to (cairo_t *cr, double x, double y);

	// cairo_public void
	// cairo_new_sub_path (cairo_t *cr);

	// cairo_public void
	// cairo_line_to (cairo_t *cr, double x, double y);

	// cairo_public void
	// cairo_curve_to (cairo_t *cr,
	// 		double x1, double y1,
	// 		double x2, double y2,
	// 		double x3, double y3);

	// cairo_public void
	// cairo_arc (cairo_t *cr,
	// 	   double xc, double yc,
	// 	   double radius,
	// 	   double angle1, double angle2);

	// cairo_public void
	// cairo_arc_negative (cairo_t *cr,
	// 		    double xc, double yc,
	// 		    double radius,
	// 		    double angle1, double angle2);

	// /* XXX: NYI
	// cairo_public void
	// cairo_arc_to (cairo_t *cr,
	// 	      double x1, double y1,
	// 	      double x2, double y2,
	// 	      double radius);
	// */

	// cairo_public void
	// cairo_rel_move_to (cairo_t *cr, double dx, double dy);

	// cairo_public void
	// cairo_rel_line_to (cairo_t *cr, double dx, double dy);

	// cairo_public void
	// cairo_rel_curve_to (cairo_t *cr,
	// 		    double dx1, double dy1,
	// 		    double dx2, double dy2,
	// 		    double dx3, double dy3);

	// cairo_public void
	// cairo_rectangle (cairo_t *cr,
	// 		 double x, double y,
	// 		 double width, double height);

	// /* XXX: NYI
	// cairo_public void
	// cairo_stroke_to_path (cairo_t *cr);
	// */

	// cairo_public void
	// cairo_close_path (cairo_t *cr);

	// cairo_public void
	// cairo_path_extents (cairo_t *cr,
	// 		    double *x1, double *y1,
	// 		    double *x2, double *y2);

	// /* Painting functions */
	// cairo_public void
	// cairo_paint (cairo_t *cr);

	// cairo_public void
	// cairo_paint_with_alpha (cairo_t *cr,
	// 			double   alpha);

	// cairo_public void
	// cairo_mask (cairo_t         *cr,
	// 	    cairo_pattern_t *pattern);

	// cairo_public void
	// cairo_mask_surface (cairo_t         *cr,
	// 		    cairo_surface_t *surface,
	// 		    double           surface_x,
	// 		    double           surface_y);

	// cairo_public void
	// cairo_stroke (cairo_t *cr);

	// cairo_public void
	// cairo_stroke_preserve (cairo_t *cr);

	// cairo_public void
	// cairo_fill (cairo_t *cr);

	// cairo_public void
	// cairo_fill_preserve (cairo_t *cr);

	// cairo_public void
	// cairo_copy_page (cairo_t *cr);

	// cairo_public void
	// cairo_show_page (cairo_t *cr);

	// /* Insideness testing */
	// cairo_public cairo_bool_t
	// cairo_in_stroke (cairo_t *cr, double x, double y);

	// cairo_public cairo_bool_t
	// cairo_in_fill (cairo_t *cr, double x, double y);

	// cairo_public cairo_bool_t
	// cairo_in_clip (cairo_t *cr, double x, double y);

	// /* Rectangular extents */
	// cairo_public void
	// cairo_stroke_extents (cairo_t *cr,
	// 		      double *x1, double *y1,
	// 		      double *x2, double *y2);

	// cairo_public void
	// cairo_fill_extents (cairo_t *cr,
	// 		    double *x1, double *y1,
	// 		    double *x2, double *y2);

	// /* Clipping */
	// cairo_public void
	// cairo_reset_clip (cairo_t *cr);

	// cairo_public void
	// cairo_clip (cairo_t *cr);

	// cairo_public void
	// cairo_clip_preserve (cairo_t *cr);

	// cairo_public void
	// cairo_clip_extents (cairo_t *cr,
	// 		    double *x1, double *y1,
	// 		    double *x2, double *y2);
};
