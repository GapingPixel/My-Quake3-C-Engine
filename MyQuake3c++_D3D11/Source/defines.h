#ifndef __DEFINES_H
#define __DEFINES_H

#include <string>

#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

#define PATH_ITEMS			".\\Data\\Models\\Items\\"
#define PATH_ITEMS_PLAYER	".\\Data\\Models\\ItemsPlayer\\"
#define PATH_WORLD			".\\Data\\Models\\World\\"
#define PATH_TEXTURES		".\\Data\\Models\\Textures\\"

#define MESH_GEOMETRIA					0x0001
#define MESH_GEOMETRIA_INDEXADA			0x0002
#define MESH_TEXTURAS					0x0004
#define	MESH_TEXTURAS_INDEXADAS			0x0008
#define MESH_COLOR						0x0010
#define MESH_CAJA_CONTENEDORA			0x0020
#define MESH_ESFERA_CONTENEDORA			0x0040

#define CHECKED_DELETE(x) if(x!=NULL) {delete x; x=NULL;}
#define CHECKED_RELEASE(x) if(x!=NULL) {x->Release(); x=NULL;}

#define LENGTH(a,b) sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z))

typedef enum TCameraControllerType
{ 
	FPS_CAMERA_CONTROLLER=0,
	SPHERICAL_CAMERA_CONTROLLER
};

void GetFilename(const char *path, std::string *filename);

#define DEG2RAD(x) x*XM_PI/180.0f
#define RAD2DEG(x) x*180.0f/XM_PI

float DistanceSqrXZ(const XMFLOAT3 &PosA, const XMFLOAT3 &PosB);
float CalculateYAW(const XMFLOAT3 &VDir);
float DistanceSqr(const XMFLOAT3 &Pos1, const XMFLOAT3 &Pos2);

#endif
