#include <fixpt.h>
#define TRACE_LEVEL TRACE_LVL_DBG
#include <trace.h>

#define COS_N 128

const int32_t costab[] = {
	Q31_SAT(Q31( 1.000000000)), /*   0 - θ =  0.000000*π */
	Q31_SAT(Q31( 0.999698819)), /*   1 - θ =  0.007813*π */
	Q31_SAT(Q31( 0.998795456)), /*   2 - θ =  0.015625*π */
	Q31_SAT(Q31( 0.997290457)), /*   3 - θ =  0.023438*π */
	Q31_SAT(Q31( 0.995184727)), /*   4 - θ =  0.031250*π */
	Q31_SAT(Q31( 0.992479535)), /*   5 - θ =  0.039063*π */
	Q31_SAT(Q31( 0.989176510)), /*   6 - θ =  0.046875*π */
	Q31_SAT(Q31( 0.985277642)), /*   7 - θ =  0.054688*π */
	Q31_SAT(Q31( 0.980785280)), /*   8 - θ =  0.062500*π */
	Q31_SAT(Q31( 0.975702130)), /*   9 - θ =  0.070313*π */
	Q31_SAT(Q31( 0.970031253)), /*  10 - θ =  0.078125*π */
	Q31_SAT(Q31( 0.963776066)), /*  11 - θ =  0.085938*π */
	Q31_SAT(Q31( 0.956940336)), /*  12 - θ =  0.093750*π */
	Q31_SAT(Q31( 0.949528181)), /*  13 - θ =  0.101563*π */
	Q31_SAT(Q31( 0.941544065)), /*  14 - θ =  0.109375*π */
	Q31_SAT(Q31( 0.932992799)), /*  15 - θ =  0.117188*π */
	Q31_SAT(Q31( 0.923879533)), /*  16 - θ =  0.125000*π */
	Q31_SAT(Q31( 0.914209756)), /*  17 - θ =  0.132813*π */
	Q31_SAT(Q31( 0.903989293)), /*  18 - θ =  0.140625*π */
	Q31_SAT(Q31( 0.893224301)), /*  19 - θ =  0.148438*π */
	Q31_SAT(Q31( 0.881921264)), /*  20 - θ =  0.156250*π */
	Q31_SAT(Q31( 0.870086991)), /*  21 - θ =  0.164063*π */
	Q31_SAT(Q31( 0.857728610)), /*  22 - θ =  0.171875*π */
	Q31_SAT(Q31( 0.844853565)), /*  23 - θ =  0.179688*π */
	Q31_SAT(Q31( 0.831469612)), /*  24 - θ =  0.187500*π */
	Q31_SAT(Q31( 0.817584813)), /*  25 - θ =  0.195313*π */
	Q31_SAT(Q31( 0.803207531)), /*  26 - θ =  0.203125*π */
	Q31_SAT(Q31( 0.788346428)), /*  27 - θ =  0.210938*π */
	Q31_SAT(Q31( 0.773010453)), /*  28 - θ =  0.218750*π */
	Q31_SAT(Q31( 0.757208847)), /*  29 - θ =  0.226563*π */
	Q31_SAT(Q31( 0.740951125)), /*  30 - θ =  0.234375*π */
	Q31_SAT(Q31( 0.724247083)), /*  31 - θ =  0.242188*π */
	Q31_SAT(Q31( 0.707106781)), /*  32 - θ =  0.250000*π */
	Q31_SAT(Q31( 0.689540545)), /*  33 - θ =  0.257813*π */
	Q31_SAT(Q31( 0.671558955)), /*  34 - θ =  0.265625*π */
	Q31_SAT(Q31( 0.653172843)), /*  35 - θ =  0.273438*π */
	Q31_SAT(Q31( 0.634393284)), /*  36 - θ =  0.281250*π */
	Q31_SAT(Q31( 0.615231591)), /*  37 - θ =  0.289063*π */
	Q31_SAT(Q31( 0.595699304)), /*  38 - θ =  0.296875*π */
	Q31_SAT(Q31( 0.575808191)), /*  39 - θ =  0.304688*π */
	Q31_SAT(Q31( 0.555570233)), /*  40 - θ =  0.312500*π */
	Q31_SAT(Q31( 0.534997620)), /*  41 - θ =  0.320313*π */
	Q31_SAT(Q31( 0.514102744)), /*  42 - θ =  0.328125*π */
	Q31_SAT(Q31( 0.492898192)), /*  43 - θ =  0.335938*π */
	Q31_SAT(Q31( 0.471396737)), /*  44 - θ =  0.343750*π */
	Q31_SAT(Q31( 0.449611330)), /*  45 - θ =  0.351563*π */
	Q31_SAT(Q31( 0.427555093)), /*  46 - θ =  0.359375*π */
	Q31_SAT(Q31( 0.405241314)), /*  47 - θ =  0.367188*π */
	Q31_SAT(Q31( 0.382683432)), /*  48 - θ =  0.375000*π */
	Q31_SAT(Q31( 0.359895037)), /*  49 - θ =  0.382813*π */
	Q31_SAT(Q31( 0.336889853)), /*  50 - θ =  0.390625*π */
	Q31_SAT(Q31( 0.313681740)), /*  51 - θ =  0.398438*π */
	Q31_SAT(Q31( 0.290284677)), /*  52 - θ =  0.406250*π */
	Q31_SAT(Q31( 0.266712757)), /*  53 - θ =  0.414063*π */
	Q31_SAT(Q31( 0.242980180)), /*  54 - θ =  0.421875*π */
	Q31_SAT(Q31( 0.219101240)), /*  55 - θ =  0.429688*π */
	Q31_SAT(Q31( 0.195090322)), /*  56 - θ =  0.437500*π */
	Q31_SAT(Q31( 0.170961889)), /*  57 - θ =  0.445313*π */
	Q31_SAT(Q31( 0.146730474)), /*  58 - θ =  0.453125*π */
	Q31_SAT(Q31( 0.122410675)), /*  59 - θ =  0.460938*π */
	Q31_SAT(Q31( 0.098017140)), /*  60 - θ =  0.468750*π */
	Q31_SAT(Q31( 0.073564564)), /*  61 - θ =  0.476563*π */
	Q31_SAT(Q31( 0.049067674)), /*  62 - θ =  0.484375*π */
	Q31_SAT(Q31( 0.024541229)), /*  63 - θ =  0.492188*π */
	Q31_SAT(Q31( 0.000000000)), /*  64 - θ =  0.500000*π */
	Q31_SAT(Q31(-0.024541229)), /*  65 - θ =  0.507813*π */
	Q31_SAT(Q31(-0.049067674)), /*  66 - θ =  0.515625*π */
	Q31_SAT(Q31(-0.073564564)), /*  67 - θ =  0.523438*π */
	Q31_SAT(Q31(-0.098017140)), /*  68 - θ =  0.531250*π */
	Q31_SAT(Q31(-0.122410675)), /*  69 - θ =  0.539063*π */
	Q31_SAT(Q31(-0.146730474)), /*  70 - θ =  0.546875*π */
	Q31_SAT(Q31(-0.170961889)), /*  71 - θ =  0.554688*π */
	Q31_SAT(Q31(-0.195090322)), /*  72 - θ =  0.562500*π */
	Q31_SAT(Q31(-0.219101240)), /*  73 - θ =  0.570313*π */
	Q31_SAT(Q31(-0.242980180)), /*  74 - θ =  0.578125*π */
	Q31_SAT(Q31(-0.266712757)), /*  75 - θ =  0.585938*π */
	Q31_SAT(Q31(-0.290284677)), /*  76 - θ =  0.593750*π */
	Q31_SAT(Q31(-0.313681740)), /*  77 - θ =  0.601563*π */
	Q31_SAT(Q31(-0.336889853)), /*  78 - θ =  0.609375*π */
	Q31_SAT(Q31(-0.359895037)), /*  79 - θ =  0.617188*π */
	Q31_SAT(Q31(-0.382683432)), /*  80 - θ =  0.625000*π */
	Q31_SAT(Q31(-0.405241314)), /*  81 - θ =  0.632813*π */
	Q31_SAT(Q31(-0.427555093)), /*  82 - θ =  0.640625*π */
	Q31_SAT(Q31(-0.449611330)), /*  83 - θ =  0.648438*π */
	Q31_SAT(Q31(-0.471396737)), /*  84 - θ =  0.656250*π */
	Q31_SAT(Q31(-0.492898192)), /*  85 - θ =  0.664063*π */
	Q31_SAT(Q31(-0.514102744)), /*  86 - θ =  0.671875*π */
	Q31_SAT(Q31(-0.534997620)), /*  87 - θ =  0.679688*π */
	Q31_SAT(Q31(-0.555570233)), /*  88 - θ =  0.687500*π */
	Q31_SAT(Q31(-0.575808191)), /*  89 - θ =  0.695313*π */
	Q31_SAT(Q31(-0.595699304)), /*  90 - θ =  0.703125*π */
	Q31_SAT(Q31(-0.615231591)), /*  91 - θ =  0.710938*π */
	Q31_SAT(Q31(-0.634393284)), /*  92 - θ =  0.718750*π */
	Q31_SAT(Q31(-0.653172843)), /*  93 - θ =  0.726563*π */
	Q31_SAT(Q31(-0.671558955)), /*  94 - θ =  0.734375*π */
	Q31_SAT(Q31(-0.689540545)), /*  95 - θ =  0.742188*π */
	Q31_SAT(Q31(-0.707106781)), /*  96 - θ =  0.750000*π */
	Q31_SAT(Q31(-0.724247083)), /*  97 - θ =  0.757813*π */
	Q31_SAT(Q31(-0.740951125)), /*  98 - θ =  0.765625*π */
	Q31_SAT(Q31(-0.757208847)), /*  99 - θ =  0.773438*π */
	Q31_SAT(Q31(-0.773010453)), /* 100 - θ =  0.781250*π */
	Q31_SAT(Q31(-0.788346428)), /* 101 - θ =  0.789063*π */
	Q31_SAT(Q31(-0.803207531)), /* 102 - θ =  0.796875*π */
	Q31_SAT(Q31(-0.817584813)), /* 103 - θ =  0.804688*π */
	Q31_SAT(Q31(-0.831469612)), /* 104 - θ =  0.812500*π */
	Q31_SAT(Q31(-0.844853565)), /* 105 - θ =  0.820313*π */
	Q31_SAT(Q31(-0.857728610)), /* 106 - θ =  0.828125*π */
	Q31_SAT(Q31(-0.870086991)), /* 107 - θ =  0.835938*π */
	Q31_SAT(Q31(-0.881921264)), /* 108 - θ =  0.843750*π */
	Q31_SAT(Q31(-0.893224301)), /* 109 - θ =  0.851563*π */
	Q31_SAT(Q31(-0.903989293)), /* 110 - θ =  0.859375*π */
	Q31_SAT(Q31(-0.914209756)), /* 111 - θ =  0.867188*π */
	Q31_SAT(Q31(-0.923879533)), /* 112 - θ =  0.875000*π */
	Q31_SAT(Q31(-0.932992799)), /* 113 - θ =  0.882813*π */
	Q31_SAT(Q31(-0.941544065)), /* 114 - θ =  0.890625*π */
	Q31_SAT(Q31(-0.949528181)), /* 115 - θ =  0.898438*π */
	Q31_SAT(Q31(-0.956940336)), /* 116 - θ =  0.906250*π */
	Q31_SAT(Q31(-0.963776066)), /* 117 - θ =  0.914063*π */
	Q31_SAT(Q31(-0.970031253)), /* 118 - θ =  0.921875*π */
	Q31_SAT(Q31(-0.975702130)), /* 119 - θ =  0.929688*π */
	Q31_SAT(Q31(-0.980785280)), /* 120 - θ =  0.937500*π */
	Q31_SAT(Q31(-0.985277642)), /* 121 - θ =  0.945313*π */
	Q31_SAT(Q31(-0.989176510)), /* 122 - θ =  0.953125*π */
	Q31_SAT(Q31(-0.992479535)), /* 123 - θ =  0.960938*π */
	Q31_SAT(Q31(-0.995184727)), /* 124 - θ =  0.968750*π */
	Q31_SAT(Q31(-0.997290457)), /* 125 - θ =  0.976563*π */
	Q31_SAT(Q31(-0.998795456)), /* 126 - θ =  0.984375*π */
	Q31_SAT(Q31(-0.999698819)), /* 127 - θ =  0.992188*π */
	Q31_SAT(Q31(-1.000000000)), /* 128 - θ =  1.000000*π */
	Q31_SAT(Q31(-0.999698819)), /* 129 - θ =  1.007813*π */
};

int32_t q31cos(int32_t x)
{
	int32_t y321;
	int32_t y32;
	int32_t y21;
	int32_t y3;
	int32_t y2;
	int32_t y1;
	int32_t y;
	int32_t x1;
	int32_t dx1;
	int32_t dx2;
	int32_t i;

	i = ((int64_t)x * COS_N) >> 31;
	y1 = costab[i];
	y2 = costab[i + 1];
	y3 = costab[i + 2];
	y21 = (y2 - y1) * 2;
	y32 = (y3 - y2) * 2;
	y321 = y32 - y21;
	x1 = ((int64_t)i << 31) / COS_N;
	dx1 = (x - x1) * (COS_N / 2);
	dx2 = dx1 + Q31(-1.0);
	y = y1 + Q31_MUL(y21, dx1) + Q31_MUL(y321, Q31_MUL(dx1, dx2));

	return y;
}

