#ifndef LIBGTE_H
#define LIBGTE_H

#include "TYPES.H"

typedef struct {
	short	m[3][3];	/* 3x3 rotation matrix */
	long    t[3];		/* transfer vector */
} MATRIX;

typedef struct {		/* long word type 3D vector */
	long	vx, vy;
	long	vz, pad;
} VECTOR;

struct SVECTOR {		/* short word type 3D vector */
	short	vx, vy;
	short	vz, pad;
};

struct CVECTOR {		/* color type vector */
	unsigned char	r, g, b, cd;
};

typedef struct {		/* 2D short vector */
	short vx, vy;
} DVECTOR;

extern void InitGeom();
extern void SetGeomOffset(int ofx, int ofy);
extern void SetGeomScreen(int h);

typedef union
{
	struct { unsigned char l, h, h2, h3; } b;
	struct { unsigned short l, h; } w;
	struct { char l, h, h2, h3; } sb;
	struct { short l, h; } sw;

	unsigned int d;
	int sd;
} PAIR;

typedef struct {
	unsigned char r, g, b, c;
} CBGR;

typedef struct {
	short x, y, z, pad;
} SVector3D;

typedef struct {
	short x, y;
} SVector2D;

typedef struct {
	short z, pad;
} SVector2Dz;

typedef struct {
	short m11, m12, m13, m21, m22, m23, m31, m32, m33, pad;
} SMatrix3D;

typedef union
{
	struct
	{
		SVector3D    v0, v1, v2;
		CBGR         rgb;
		int          otz;
		int          ir0, ir1, ir2, ir3;
		SVector2D    sxy0, sxy1, sxy2, sxyp;
		SVector2Dz   sz0, sz1, sz2, sz3;
		CBGR         rgb0, rgb1, rgb2;
		int          reserved;
		int          mac0, mac1, mac2, mac3;
		unsigned int irgb, orgb;
		int          lzcs, lzcr;
	} n;

	unsigned int r[32];
	PAIR p[32];

} psxCP2Data;

typedef union
{
	struct {
		SMatrix3D rMatrix;
		int      trX, trY, trZ;
		SMatrix3D lMatrix;
		int      rbk, gbk, bbk;
		SMatrix3D cMatrix;
		int      rfc, gfc, bfc;
		int      ofx, ofy;
		int      h;
		int      dqa, dqb;
		int      zsf3, zsf4;
		int      flag;
	} n;
	unsigned int r[32];
	PAIR p[32];
} psxCP2Ctrl;

typedef union {
	struct {
		unsigned int	Index, Random, EntryLo0, BPC,
			Context, BDA, PIDMask, DCIC,
			BadVAddr, BDAM, EntryHi, BPCM,
			Status, Cause, EPC, PRid,
			Config, LLAddr, WatchLO, WatchHI,
			XContext, Reserved1, Reserved2, Reserved3,
			Reserved4, Reserved5, ECC, CacheErr,
			TagLo, TagHi, ErrorEPC, Reserved6;
	} n;
	unsigned int r[32];
} psxCP0Regs;

typedef struct
{
	psxCP0Regs CP0;  /* Coprocessor0 Registers */
	psxCP2Data CP2D; /* Cop2 data registers */
	psxCP2Ctrl CP2C; /* Cop2 control registers */
} GTERegisters;

extern GTERegisters gteRegs;
extern unsigned int gte_leadingzerocount(unsigned int lzcs);

extern void SetRotMatrix(MATRIX* m);
extern void SetLightMatrix(MATRIX* m);
extern void SetColorMatrix(MATRIX* m);
extern void SetTransMatrix(MATRIX* m);
extern void PushMatrix();
extern void PopMatrix();
extern long RotTransPers(struct SVECTOR* v0, long* sxy, long* p, long* flag);
extern void RotTrans(struct SVECTOR* v0, VECTOR* v1, long* flag);
extern void NormalColorDpq(struct SVECTOR* v0, struct CVECTOR* v1, long p, struct CVECTOR* v2);
extern void NormalColorCol(struct SVECTOR* v0, struct CVECTOR* v1, struct CVECTOR* v2);
extern long RotAverageNclip4(struct SVECTOR* v0, struct SVECTOR* v1, struct SVECTOR* v2, struct SVECTOR* v3, long* sxy0/*arg_10*/, long* sxy1/*arg_14*/, long* sxy2/*arg_18*/, long* sxy3/*arg_1C*/, long* p/*arg_20*/, long* otz/*arg_24*/, long* flag/*arg_28*/);
extern MATRIX* MulMatrix0(MATRIX* m0, MATRIX* m1, MATRIX* m2);
extern MATRIX* MulMatrix(MATRIX* m0, MATRIX* m1);
extern MATRIX* MulMatrix2(MATRIX* m0, MATRIX* m1);
extern void SetBackColor(long rbk, long gbk, long bbk);
extern void SetFarColor(long rfc, long gfc, long bfc);
extern MATRIX* RotMatrix(struct SVECTOR* r, MATRIX* m);
extern MATRIX* TransMatrix(MATRIX* m, VECTOR* v);
extern MATRIX* ScaleMatrix(MATRIX* m, VECTOR* v);
extern void SetDQA(int iDQA);
extern void SetDQB(int iDQB);
extern void SetFogNear(long a, long h);
extern int rsin(int a);

#if defined(PGXP)
#define MAX_NUM_VERTICES 32768

struct PGXPVertex
{
	unsigned int originalSXY2;
	float x;
	float y;
	float z;
};

extern struct PGXPVertex pgxp_vertex_buffer[MAX_NUM_VERTICES];
extern int pgxp_vertex_index;
extern int pgxp_vertex_count;
#endif

#endif