#include "defines.h"

void GetFilename(const char *path, std::string *filename)
{
	char *pnt=NULL;
	for(int b=(int)strlen(path);b>0;--b)
	{
		if(path[b]=='\\')
		{
			pnt=(char*)&(path[b+1]);
			b=-1;
		}
	}
	if(pnt==NULL)
		pnt=(char*)&(path[0]);
	*filename=pnt;
}

float DistanceSqrXZ(const XMFLOAT3 &PosA, const XMFLOAT3 &PosB)
{
	return (PosA.x-PosB.x)*(PosA.x-PosB.x)+
		(PosA.z-PosB.z)*(PosA.z-PosB.z);
}

float CalculateYAW(const XMFLOAT3 &VDir)
{	
	return atan2f(VDir.x,VDir.z);
}

float DistanceSqr(const XMFLOAT3 &Pos1, const XMFLOAT3 &Pos2)
{
	return (Pos1.x-Pos2.x)*(Pos1.x-Pos2.x)+
		(Pos1.y-Pos2.y)*(Pos1.y-Pos2.y)+
		(Pos1.z-Pos2.z)*(Pos1.z-Pos2.z);
}
