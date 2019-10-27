// Fill out your copyright notice in the Description page of Project Settings.

#include "CairoFunctionLibrary.h"
#include "CairoContext.h"
#include "Engine/Texture2D.h"

UCairoContext *UCairoFunctionLibrary::InitCairoSurface(UObject *WorldContextObject, int Width, int Height)
{
	UCairoContext &Context = *NewObject<UCairoContext>(WorldContextObject);
	Context.Width = Width;
	Context.Height = Height;

	int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, Context.Width);

	Context.Size = stride * Context.Height;
	Context.data = (unsigned char *)FMemory::Malloc(Context.Size);
	cairo_surface_t *surface =
	    cairo_image_surface_create_for_data(Context.data, CAIRO_FORMAT_ARGB32, Context.Width, Context.Height, stride);
	Context.ctx = cairo_create(surface);

	Context.bIsInitialized = true;
	Context.Texture = UTexture2D::CreateTransient(Context.Width, Context.Height);
	Context.Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Context.Texture->SRGB = 0;

	return &Context;
}

void UCairoFunctionLibrary::RefreshContextTexture(UCairoContext *Context)
{
	if (Context->Texture == nullptr)
	{
		return;
	}
	FTexture2DMipMap &Mip = Context->Texture->PlatformData->Mips[0];
	void *Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(Data, Context->data, Context->Size);
	Mip.BulkData.Unlock();
	Context->Texture->UpdateResource();
}

void UCairoFunctionLibrary::DestroyContext(UCairoContext *Context)
{
	Context->Cleanup();
}

void UCairoFunctionLibrary::SetSourceRGBA(UCairoContext *Context, const FLinearColor &RGBA)
{
	cairo_set_source_rgba(Context->ctx, RGBA.R, RGBA.G, RGBA.B, RGBA.A);
}

void UCairoFunctionLibrary::SetSourceRGB(UCairoContext *Context, float Red, float Green, float Blue)
{
	cairo_set_source_rgb(Context->ctx, Red, Green, Blue);
}

void UCairoFunctionLibrary::Paint(UCairoContext *Context)
{
	cairo_paint(Context->ctx);
}

void UCairoFunctionLibrary::SetFontSize(UCairoContext *Context, float Size)
{
	cairo_set_font_size(Context->ctx, Size);
}

void UCairoFunctionLibrary::MoveTo(UCairoContext *Context, const FVector2D &Position)
{
	cairo_move_to(Context->ctx, Position.X, Position.Y);
}

void UCairoFunctionLibrary::ShowText(UCairoContext *Context, const FString &Text)
{
	cairo_show_text(Context->ctx, TCHAR_TO_UTF8(*Text));
}

void UCairoFunctionLibrary::LineTo(UCairoContext *Context, const FVector2D &Position)
{
	cairo_line_to(Context->ctx, Position.X, Position.Y);
}

void UCairoFunctionLibrary::Rectangle(UCairoContext *Context, const FVector2D &XY, const FVector2D &Size)
{
	cairo_rectangle(Context->ctx, XY.X, XY.Y, Size.X, Size.Y);
}

void UCairoFunctionLibrary::Arc(UCairoContext *Context, const FVector2D &Center, float Radius, float Angle1,
                                float Angle2)
{
	cairo_arc(Context->ctx, Center.X, Center.Y, Radius, Angle1, Angle2);
}

void UCairoFunctionLibrary::ArcNegative(UCairoContext *Context, const FVector2D &Center, float Radius, float Angle1,
                                        float Angle2)
{
	cairo_arc_negative(Context->ctx, Center.X, Center.Y, Radius, Angle1, Angle2);
}

void UCairoFunctionLibrary::Fill(UCairoContext *Context)
{
	cairo_fill(Context->ctx);
}

void UCairoFunctionLibrary::Stroke(UCairoContext *Context)
{
	cairo_stroke(Context->ctx);
}

void UCairoFunctionLibrary::NewSubPath(UCairoContext *Context)
{
	cairo_new_sub_path(Context->ctx);
}

void UCairoFunctionLibrary::ClosePath(UCairoContext *Context)
{
	cairo_close_path(Context->ctx);
}

void UCairoFunctionLibrary::SelectFontFace(UCairoContext *Context, const FString &Family, EFontSlant Slant,
                                           EFontWeight Weight)
{
	cairo_font_slant_t CairoFontSlant;
	cairo_font_weight_t CairoFontWeight;
	switch (Slant)
	{
	case EFontSlant::FONT_SLANT_ITALIC:
		CairoFontSlant = CAIRO_FONT_SLANT_ITALIC;
		break;
	case EFontSlant::FONT_SLANT_OBLIQUE:
		CairoFontSlant = CAIRO_FONT_SLANT_OBLIQUE;
		break;
	case EFontSlant::FONT_SLANT_NORMAL:
	default:
		CairoFontSlant = CAIRO_FONT_SLANT_NORMAL;
		break;
	}

	switch (Weight)
	{
	case EFontWeight::FONT_FONT_WEIGHT_BOLD:
		CairoFontWeight = CAIRO_FONT_WEIGHT_BOLD;
		break;
	case EFontWeight::FONT_FONT_WEIGHT_NORMAL:
	default:
		CairoFontWeight = CAIRO_FONT_WEIGHT_NORMAL;
		break;
	}
	cairo_select_font_face(Context->ctx, TCHAR_TO_ANSI(*Family), CairoFontSlant, CairoFontWeight);
}

FVector2D UCairoFunctionLibrary::TextExtents(UCairoContext *Context, const FString &Text)
{
	cairo_text_extents_t CairoTextExtents;
	cairo_text_extents(Context->ctx, TCHAR_TO_UTF8(*Text), &CairoTextExtents);
	return FVector2D(CairoTextExtents.width, CairoTextExtents.height);
}

void UCairoFunctionLibrary::SetOperator(UCairoContext *Context, ECairoOperator Operator)
{
	cairo_operator_t op;
	switch (Operator)
	{
	case ECairoOperator::CLEAR:
	default:
		op = CAIRO_OPERATOR_CLEAR;
		break;

	case ECairoOperator::SOURCE:
		op = CAIRO_OPERATOR_SOURCE;
		break;
	case ECairoOperator::OVER:
		op = CAIRO_OPERATOR_OVER;
		break;
	case ECairoOperator::OP_IN:
		op = CAIRO_OPERATOR_IN;
		break;
	case ECairoOperator::OP_OUT:
		op = CAIRO_OPERATOR_OUT;
		break;
	case ECairoOperator::ATOP:
		op = CAIRO_OPERATOR_ATOP;
		break;

	case ECairoOperator::DEST:
		op = CAIRO_OPERATOR_DEST;
		break;
	case ECairoOperator::DEST_OVER:
		op = CAIRO_OPERATOR_DEST_OVER;
		break;
	case ECairoOperator::DEST_IN:
		op = CAIRO_OPERATOR_DEST_IN;
		break;
	case ECairoOperator::DEST_OUT:
		op = CAIRO_OPERATOR_DEST_OUT;
		break;
	case ECairoOperator::DEST_ATOP:
		op = CAIRO_OPERATOR_DEST_ATOP;
		break;

	case ECairoOperator::XOR:
		op = CAIRO_OPERATOR_XOR;
		break;
	case ECairoOperator::ADD:
		op = CAIRO_OPERATOR_ADD;
		break;
	case ECairoOperator::SATURATE:
		op = CAIRO_OPERATOR_SATURATE;
		break;

	case ECairoOperator::MULTIPLY:
		op = CAIRO_OPERATOR_MULTIPLY;
		break;
	case ECairoOperator::SCREEN:
		op = CAIRO_OPERATOR_SCREEN;
		break;
	case ECairoOperator::OVERLAY:
		op = CAIRO_OPERATOR_OVERLAY;
		break;
	case ECairoOperator::DARKEN:
		op = CAIRO_OPERATOR_DARKEN;
		break;
	case ECairoOperator::LIGHTEN:
		op = CAIRO_OPERATOR_LIGHTEN;
		break;
	case ECairoOperator::COLOR_DODGE:
		op = CAIRO_OPERATOR_COLOR_DODGE;
		break;
	case ECairoOperator::COLOR_BURN:
		op = CAIRO_OPERATOR_COLOR_BURN;
		break;
	case ECairoOperator::HARD_LIGHT:
		op = CAIRO_OPERATOR_HARD_LIGHT;
		break;
	case ECairoOperator::SOFT_LIGHT:
		op = CAIRO_OPERATOR_SOFT_LIGHT;
		break;
	case ECairoOperator::DIFFERENCE:
		op = CAIRO_OPERATOR_DIFFERENCE;
		break;
	case ECairoOperator::EXCLUSION:
		op = CAIRO_OPERATOR_EXCLUSION;
		break;
	case ECairoOperator::HSL_HUE:
		op = CAIRO_OPERATOR_HSL_HUE;
		break;
	case ECairoOperator::HSL_SATURATION:
		op = CAIRO_OPERATOR_HSL_SATURATION;
		break;
	case ECairoOperator::HSL_COLOR:
		op = CAIRO_OPERATOR_HSL_COLOR;
		break;
	case ECairoOperator::HSL_LUMINOSITY:
		op = CAIRO_OPERATOR_HSL_LUMINOSITY;
		break;
	};

	cairo_set_operator(Context->ctx, op);
}

void UCairoFunctionLibrary::SetTolerance(UCairoContext *Context, float Tolerance)
{
	cairo_set_tolerance(Context->ctx, Tolerance);
}

void UCairoFunctionLibrary::SetAntialias(UCairoContext *Context, ECairoAntialias Antialias)
{
	cairo_antialias_t aa;
	switch (Antialias)
	{
	case ECairoAntialias::ANTIALIAS_DEFAULT:
	default:
		aa = CAIRO_ANTIALIAS_DEFAULT;
		break;
	case ECairoAntialias::ANTIALIAS_NONE:
		aa = CAIRO_ANTIALIAS_NONE;
		break;
	case ECairoAntialias::ANTIALIAS_SUBPIXEL:
		aa = CAIRO_ANTIALIAS_SUBPIXEL;
		break;
	case ECairoAntialias::ANTIALIAS_FAST:
		aa = CAIRO_ANTIALIAS_FAST;
		break;
	case ECairoAntialias::ANTIALIAS_BEST:
		aa = CAIRO_ANTIALIAS_BEST;
		break;
	case ECairoAntialias::ANTIALIAS_GOOD:
		aa = CAIRO_ANTIALIAS_GOOD;
		break;
	};
	cairo_set_antialias(Context->ctx, aa);
}

void UCairoFunctionLibrary::SetFillRule(UCairoContext *Context, EFillRule FillRule)
{
	cairo_fill_rule_t rule;
	switch (FillRule)
	{
	case EFillRule::FILL_RULE_EVEN_ODD:
	default:
		rule = CAIRO_FILL_RULE_EVEN_ODD;
		break;
	case EFillRule::FILL_RULE_WINDING:
		rule = CAIRO_FILL_RULE_WINDING;
		break;
	}
	cairo_set_fill_rule(Context->ctx, rule);
}

void UCairoFunctionLibrary::SetLineWidth(UCairoContext *Context, float Width)
{
	cairo_set_line_width(Context->ctx, Width);
}

void UCairoFunctionLibrary::SetLineCap(UCairoContext *Context, ELineCap LineCap)
{
	cairo_line_cap_t cap;
	switch (LineCap)
	{
	case ELineCap::LINE_CAP_BUTT:
	default:
		cap = CAIRO_LINE_CAP_BUTT;
		break;
	case ELineCap::LINE_CAP_ROUND:
		cap = CAIRO_LINE_CAP_ROUND;
		break;
	case ELineCap::LINE_CAP_SQUARE:
		cap = CAIRO_LINE_CAP_SQUARE;
		break;
	}
	cairo_set_line_cap(Context->ctx, cap);
}

void UCairoFunctionLibrary::SetLineJoin(UCairoContext *Context, ELineJoin LineJoin)
{
	cairo_line_join_t join;
	switch (LineJoin)
	{
	case ELineJoin::LINE_JOIN_BEVEL:
		join = CAIRO_LINE_JOIN_BEVEL;
		break;
	case ELineJoin::LINE_JOIN_MITER:
		join = CAIRO_LINE_JOIN_MITER;
		break;
	case ELineJoin::LINE_JOIN_ROUND:
	default:
		join = CAIRO_LINE_JOIN_ROUND;
		break;
	}
	cairo_set_line_join(Context->ctx, join);
}

void UCairoFunctionLibrary::SetDash(UCairoContext *Context, const TArray<float> &Dashes, int NumDashes, float Offset)
{
	TArray<double> dashes;
	for (int x = 0; x < Dashes.Num(); x++)
	{
		dashes.Add(Dashes[x]);
	}
	cairo_set_dash(Context->ctx, dashes.GetData(), Dashes.Num(), Offset);
}

void UCairoFunctionLibrary::SetMiterLimit(UCairoContext *Context, float Limit)
{
	cairo_set_miter_limit(Context->ctx, Limit);
}

void UCairoFunctionLibrary::Translate(UCairoContext *Context, const FVector2D &Translation)
{
	cairo_translate(Context->ctx, Translation.X, Translation.Y);
}

void UCairoFunctionLibrary::Scale(UCairoContext *Context, const FVector2D &Scale)
{

	cairo_scale(Context->ctx, Scale.X, Scale.Y);
}

void UCairoFunctionLibrary::Rotate(UCairoContext *Context, float Angle)
{
	cairo_rotate(Context->ctx, Angle);
}

void UCairoFunctionLibrary::Transform(UCairoContext *Context, const FCairoMatrix &Matrix)
{
	cairo_matrix_t m;
	m.x0 = Matrix.x0;
	m.xx = Matrix.xx;
	m.xy = Matrix.xy;
	m.y0 = Matrix.y0;
	m.yx = Matrix.yx;
	m.yy = Matrix.yy;
	cairo_transform(Context->ctx, &m);
}

void UCairoFunctionLibrary::SetMatrix(UCairoContext *Context, const FCairoMatrix &Matrix)
{
	cairo_matrix_t m;
	m.x0 = Matrix.x0;
	m.xx = Matrix.xx;
	m.xy = Matrix.xy;
	m.y0 = Matrix.y0;
	m.yx = Matrix.yx;
	m.yy = Matrix.yy;
	cairo_set_matrix(Context->ctx, &m);
}

void UCairoFunctionLibrary::IdentityMatrix(UCairoContext *Context)
{
	cairo_identity_matrix(Context->ctx);
}

FVector2D UCairoFunctionLibrary::UserToDevice(UCairoContext *Context)
{
	double x, y;
	cairo_user_to_device(Context->ctx, &x,&y);
	return FVector2D(x, y);
}

FVector2D UCairoFunctionLibrary::UserToDeviceDistance(UCairoContext *Context)
{
	double x, y;
	cairo_user_to_device_distance(Context->ctx, &x, &y);
	return FVector2D(x, y);
}

FVector2D UCairoFunctionLibrary::DeviceToUser(UCairoContext *Context)
{
	double x, y;
	cairo_device_to_user(Context->ctx, &x, &y);
	return FVector2D(x, y);
}

FVector2D UCairoFunctionLibrary::DeviceToUserDistance(UCairoContext *Context)
{
	double x, y;
	cairo_device_to_user_distance(Context->ctx, &x, &y);
	return FVector2D(x, y);
}

void UCairoFunctionLibrary::NewPath(UCairoContext *Context)
{
	cairo_new_path(Context->ctx);
}

void UCairoFunctionLibrary::CurveTo(UCairoContext *Context, const FVector2D &P1, const FVector2D &P2,
                                    const FVector2D &P3)
{
	cairo_curve_to(Context->ctx, P1.X, P1.Y, P2.X, P2.Y, P3.X,P3.Y);
}

void UCairoFunctionLibrary::RelMoveTo(UCairoContext *Context, const FVector2D &Position)
{
	cairo_rel_move_to(Context->ctx, Position.X, Position.Y);
}

void UCairoFunctionLibrary::RelLineTo(UCairoContext *Context, const FVector2D &Position)
{
	cairo_rel_line_to(Context->ctx, Position.X, Position.Y);
}

void UCairoFunctionLibrary::RelCurveTo(UCairoContext *Context, const FVector2D &P1, const FVector2D &P2,
                                       const FVector2D &P3)
{
	cairo_rel_curve_to(Context->ctx, P1.X, P1.Y, P2.X, P2.Y, P3.X, P3.Y);
}

void UCairoFunctionLibrary::PathExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2)
{
	double a, b, c, d;
	cairo_path_extents(Context->ctx, &a, &b, &c, &d);
	P1.X = a;
	P1.Y = b;
	P2.X = c;
	P2.Y = d;
}

void UCairoFunctionLibrary::StrokeExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2)
{
	double a, b, c, d;
	cairo_stroke_extents(Context->ctx, &a, &b, &c, &d);
	P1.X = a;
	P1.Y = b;
	P2.X = c;
	P2.Y = d;
}

void UCairoFunctionLibrary::FillExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2)
{
	double a, b, c, d;
	cairo_fill_extents(Context->ctx, &a, &b, &c, &d);
	P1.X = a;
	P1.Y = b;
	P2.X = c;
	P2.Y = d;
}

void UCairoFunctionLibrary::ClipExtents(UCairoContext *Context, FVector2D &P1, FVector2D &P2)
{
	double a, b, c, d;
	cairo_clip_extents(Context->ctx, &a, &b, &c, &d);
	P1.X = a;
	P1.Y = b;
	P2.X = c;
	P2.Y = d;
}

void UCairoFunctionLibrary::PaintWithAlpha(UCairoContext *Context, float Alpha)
{
	cairo_paint_with_alpha(Context->ctx, Alpha);
}

void UCairoFunctionLibrary::StrokePreserve(UCairoContext *Context)
{
	cairo_stroke_preserve(Context->ctx);
}

void UCairoFunctionLibrary::FillPreserve(UCairoContext *Context)
{
	cairo_fill_preserve(Context->ctx);
}

void UCairoFunctionLibrary::CopyPage(UCairoContext *Context)
{
	cairo_copy_page(Context->ctx);
}

void UCairoFunctionLibrary::ShowPage(UCairoContext *Context)
{
	cairo_show_page(Context->ctx);
}

void UCairoFunctionLibrary::InStroke(UCairoContext *Context, const FVector2D &XY)
{
	cairo_in_stroke(Context->ctx, XY.X, XY.Y);
}

void UCairoFunctionLibrary::InFill(UCairoContext *Context, const FVector2D &XY)
{
	cairo_in_fill(Context->ctx, XY.X, XY.Y);
}

void UCairoFunctionLibrary::InClip(UCairoContext *Context, const FVector2D &XY)
{
	cairo_in_clip(Context->ctx, XY.X, XY.Y);
}

void UCairoFunctionLibrary::ResetClip(UCairoContext *Context)
{
	cairo_reset_clip(Context->ctx);
}

void UCairoFunctionLibrary::Clip(UCairoContext *Context)
{
	cairo_clip(Context->ctx);
}

void UCairoFunctionLibrary::ClipPreserve(UCairoContext *Context)
{
	cairo_clip_preserve(Context->ctx);
}
