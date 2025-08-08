#include "../../FsLibrary/FsGraphics.h"
#include "../../FsLibrary/Fs.h"
#include "../../FsLibrary/FsUtils.h"

//********************************************************
//�w�肵���͈͂𕽒R������Bpr�̒l�Ő��l�������ł���
//********************************************************
PF_Err CFsGraph::flat8(FsFlatParam *fp,FsPixelRand *pr)
{
	PF_Err err = PF_Err_NONE;
	if ( (fp->sizeX<0)||(fp->sizeY<0)) return err;
	if ( (fp->sizeX<=1)&&(fp->sizeY<=1)) return err;
	A_long x = fp->x;
	A_long y = fp->y;
	A_long sx = fp->sizeX;
	A_long sy = fp->sizeY;
	if ( x>=m_width) return err;
	if ( y>=m_height) return err;

	if (x<0) {
		sx += x;
		if ( sx<=0) return err;
		x =0;
	}
	if ( (x+sx)>m_width){
		sx = m_width -x;
		if ( sx<=0) return err;
	}
	if (y<0) {
		sy += y;
		if ( sy<=0) return err;
		y =0;
	}
	if ( (y+sy)>m_height){
		sy = m_height -y;
		if ( sy<=0) return err;
	}
	FsPixelRand pp;
	if ( pr == NULL){
		pp.a = pp.b = pp.g = pp.r =0;
	}else{
		pp = *pr;
	}

	A_long i,j;
	PF_Pixel * data;
	data = (PF_Pixel *)m_data; 
	A_long target;
	A_long targetBase = x + y * m_widthTrue;
	A_long	yr = 0,yg = 0,yb = 0,ya = 0;
	target =targetBase;
	for ( j=0; j<sy; j++){
		A_long xr=0,xg=0,xb=0,xa=0;
		target =targetBase + j * m_widthTrue;
		for ( i=0; i<sx; i++){
			xa += data[target].alpha;
			xr += data[target].red;
			xg += data[target].green;
			xb += data[target].blue;
			target++;
		}
		ya += (xa / sx);
		yr += (xr / sx);
		yg += (xg / sx);
		yb += (xb / sx);
	}
	PF_Pixel c;
	//�������̂Ƃ���̂݃����_����
	A_long a2 = RoundByteLong(ya/sy);
	if ( a2<(PF_MAX_CHAN8-26)) a2 += pp.a;
	c.alpha	= RoundByteLong(a2);
	c.blue	= RoundByteLong(yb/sy + pp.b);
	c.green = RoundByteLong(yg/sy + pp.g);
	c.red	= RoundByteLong(yr/sy + pp.r);

	for ( j=0; j<sy; j++){
		target =targetBase + j * m_widthTrue;
		for ( i=0; i<sx; i++){
			data[target] = c;
			target++;
		}
	}
	return err;
}
//********************************************************
//�w�肵���͈͂𕽒R������Bpr�̒l�Ő��l�������ł���
//********************************************************
PF_Err CFsGraph::flat16(FsFlatParam *fp,FsPixelRand *pr)
{
	PF_Err err = PF_Err_NONE;
	if ( (fp->sizeX<0)||(fp->sizeY<0)) return err;
	if ( (fp->sizeX<=1)&&(fp->sizeY<=1)) return err;
	A_long x = fp->x;
	A_long y = fp->y;
	A_long sx = fp->sizeX;
	A_long sy = fp->sizeY;
	if ( x>=m_width) return err;
	if ( y>=m_height) return err;

	if (x<0) {
		sx += x;
		if ( sx<=0) return err;
		x =0;
	}
	if ( (x+sx)>m_width){
		sx = m_width -x;
		if ( sx<=0) return err;
	}
	if (y<0) {
		sy += y;
		if ( sy<=0) return err;
		y =0;
	}
	if ( (y+sy)>m_height){
		sy = m_height -y;
		if ( sy<=0) return err;
	}
	FsPixelRand pp;
	if ( pr == NULL){
		pp.a = pp.b = pp.g = pp.r =0;
	}else{
		pp = *pr;
	}

	A_long i,j;
	PF_Pixel16 * data;
	data = (PF_Pixel16 *)m_data; 
	A_long target;
	A_long targetBase = x + y * m_widthTrue;
	A_long	yr = 0,yg = 0,yb = 0,ya = 0;
	target =targetBase;
	for ( j=0; j<sy; j++){
		A_long xr=0,xg=0,xb=0,xa=0;
		target =targetBase + j * m_widthTrue;
		for ( i=0; i<sx; i++){
			xa += data[target].alpha;
			xr += data[target].red;
			xg += data[target].green;
			xb += data[target].blue;
			target++;
		}
		ya += (xa / sx);
		yr += (xr / sx);
		yg += (xg / sx);
		yb += (xb / sx);
	}
	PF_Pixel16 c;
	//�������̂Ƃ���̂݃����_����
	A_long a2 = RoundShort(ya/sy);
	if (a2<(PF_MAX_CHAN16-65534)) a2 += pp.a;
	c.alpha	= RoundShort(a2);
	c.blue	= RoundShort(yb/sy + pp.b);
	c.green = RoundShort(yg/sy + pp.g);
	c.red	= RoundShort(yr/sy + pp.r);

	for ( j=0; j<sy; j++){
		target =targetBase + j * m_widthTrue;
		for ( i=0; i<sx; i++){
			data[target] = c;
			target++;
		}
	}
	return err;
}
//********************************************************
//�w�肵���͈͂𕽒R������Bpr�̒l�Ő��l�������ł���
//********************************************************
PF_Err CFsGraph::flat32(FsFlatParam *fp,FsPixelRandFloat *pr)
{
	PF_Err err = PF_Err_NONE;
	if ( (fp->sizeX<0)||(fp->sizeY<0)) return err;
	if ( (fp->sizeX<=1)&&(fp->sizeY<=1)) return err;
	A_long x = fp->x;
	A_long y = fp->y;
	A_long sx = fp->sizeX;
	A_long sy = fp->sizeY;
	if ( x>=m_width) return err;
	if ( y>=m_height) return err;

	if (x<0) {
		sx += x;
		if ( sx<=0) return err;
		x =0;
	}
	if ( (x+sx)>m_width){
		sx = m_width -x;
		if ( sx<=0) return err;
	}
	if (y<0) {
		sy += y;
		if ( sy<=0) return err;
		y =0;
	}
	if ( (y+sy)>m_height){
		sy = m_height -y;
		if ( sy<=0) return err;
	}
	FsPixelRandFloat pp;
	if ( pr == NULL){
		pp.a = pp.b = pp.g = pp.r =0;
	}else{
		pp = *pr;
	}

	A_long i,j;
	PF_PixelFloat * data;
	data = (PF_PixelFloat *)m_data; 
	A_long target;
	A_long targetBase = x + y * m_widthTrue;
	PF_FpLong	yr = 0,yg = 0,yb = 0,ya = 0;
	target =targetBase;
	for ( j=0; j<sy; j++){
		PF_FpLong xr=0,xg=0,xb=0,xa=0;
		target =targetBase + j * m_widthTrue;
		for ( i=0; i<sx; i++){
			xa += data[target].alpha;
			xr += data[target].red;
			xg += data[target].green;
			xb += data[target].blue;
			target++;
		}
		ya += (xa / sx);
		yr += (xr / sx);
		yg += (xg / sx);
		yb += (xb / sx);
	}
	PF_PixelFloat c;
	//�������̂Ƃ���̂݃����_����
	PF_FpLong a2 = RoundFpShortDouble(ya/sy);
	if ( a2<(1.0-0.1)) a2 += pp.a;
	c.alpha	= RoundFpShortDouble(a2);
	c.blue	= RoundFpShortDouble(yb/sy + pp.b);
	c.green = RoundFpShortDouble(yg/sy + pp.g);
	c.red	= RoundFpShortDouble(yr/sy + pp.r);

	for ( j=0; j<sy; j++){
		target =targetBase + j * m_widthTrue;
		for ( i=0; i<sx; i++){
			data[target] = c;
			target++;
		}
	}
	return err;
}
//********************************************************
//********************************************************
PF_Err CFsGraph::mosaic8(FsMosaicParam *mp)
{
	PF_Err err = PF_Err_NONE;
	//��_�ƃ��[�v��
	FsFlatParam fp;
	fp.sizeX	= mp->sizeX;
	fp.sizeY	= mp->sizeY;
	A_long posX = (mp->pos.x>>16) % mp->sizeX;
	if (posX>0) posX -= mp->sizeX;
	A_long cntX = (m_width - posX) / mp->sizeX;
	if (((m_width - posX) % mp->sizeX)>0)cntX++;
	A_long posY = (mp->pos.y>>16) % mp->sizeY;
	if (posY>0) posY -= mp->sizeY;
	A_long cntY = (m_height - posY) / mp->sizeY;
	if (((m_height - posY) % mp->sizeY)>0) cntY++;

	if (( (posX+fp.sizeX) + fp.sizeX)>=m_width){
		posX = 0;
		fp.sizeX = m_width;
		cntX = 1;
	}
	if (( (posY + fp.sizeY)  + fp.sizeY)>=m_height){
		posY = 0;
		fp.sizeY = m_height;
		cntY = 1;
	}
	
	//�����_���̏�����
	FsPixelRand pr;
	pr.a = pr.b = pr.g = pr.r = 0;
	A_long randValue;
	if (mp->rand >0){
		if (mp->isFrameRand == TRUE){
			init_xorShift(m_frame);
		}else{
			init_xorShift(0);
		}
		randValue = (A_long)(PF_MAX_CHAN8 * mp->rand);
	}
	A_long i,j;
	for ( j=0; j<cntY; j++){
		fp.y =  posY + j * fp.sizeY;
		for ( i=0; i<cntX; i++){
			fp.x =  posX + i * fp.sizeX;
			if ( mp->rand>0){
				if ( mp->isRandGray){
					pr.a = pr.b = pr.g = pr.r
						= F_RAND2(-randValue,randValue);
				}else{
					pr.a = F_RAND2(-randValue,randValue);
					pr.b = F_RAND2(-randValue,randValue);
					pr.g = F_RAND2(-randValue,randValue);
					pr.r = F_RAND2(-randValue,randValue);
				}
			}
			flat8(&fp, &pr);
		}
	}
	return err;
}
//********************************************************
//********************************************************
PF_Err CFsGraph::mosaic16(FsMosaicParam *mp)
{
	PF_Err err = PF_Err_NONE;
	//��_�ƃ��[�v��
	FsFlatParam fp;
	fp.sizeX	= mp->sizeX;
	fp.sizeY	= mp->sizeY;
	A_long posX = (mp->pos.x>>16) % mp->sizeX;
	if (posX>0) posX -= mp->sizeX;
	A_long cntX = (m_width - posX) / mp->sizeX;
	if (((m_width - posX) % mp->sizeX)>0)cntX++;
	A_long posY = (mp->pos.y>>16) % mp->sizeY;
	if (posY>0) posY -= mp->sizeY;
	A_long cntY = (m_height - posY) / mp->sizeY;
	if (((m_height - posY) % mp->sizeY)>0) cntY++;

	if (( (posX+fp.sizeX) + fp.sizeX)>=m_width){
		posX = 0;
		fp.sizeX = m_width;
		cntX = 1;
	}
	if (( (posY + fp.sizeY)  + fp.sizeY)>=m_height){
		posY = 0;
		fp.sizeY = m_height;
		cntY = 1;
	}
	
	//�����_���̏�����
	FsPixelRand pr;
	pr.a = pr.b = pr.g = pr.r = 0;
	A_long randValue;
	if (mp->rand >0){
		if (mp->isFrameRand == TRUE){
			init_xorShift(m_frame);
		}else{
			init_xorShift(0);
		}
		randValue = (A_long)(PF_MAX_CHAN16 * mp->rand);
	}
	A_long i,j;
	for ( j=0; j<cntY; j++){
		fp.y =  posY + j * fp.sizeY;
		for ( i=0; i<cntX; i++){
			fp.x =  posX + i * fp.sizeX;
			if ( mp->rand>0){
				if ( mp->isRandGray){
					pr.a = pr.b = pr.g = pr.r
						= F_RAND2(-randValue,randValue);
				}else{
					pr.a = F_RAND2(-randValue,randValue);
					pr.b = F_RAND2(-randValue,randValue);
					pr.g = F_RAND2(-randValue,randValue);
					pr.r = F_RAND2(-randValue,randValue);
				}
			}
			flat16(&fp, &pr);
		}
	}
	return err;
}
//********************************************************
//********************************************************
PF_Err CFsGraph::mosaic32(FsMosaicParam *mp)
{
	PF_Err err = PF_Err_NONE;
	//��_�ƃ��[�v��
	FsFlatParam fp;
	fp.sizeX	= mp->sizeX;
	fp.sizeY	= mp->sizeY;
	A_long posX = (mp->pos.x>>16) % mp->sizeX;
	if (posX>0) posX -= mp->sizeX;
	A_long cntX = (m_width - posX) / mp->sizeX;
	if (((m_width - posX) % mp->sizeX)>0)cntX++;
	A_long posY = (mp->pos.y>>16) % mp->sizeY;
	if (posY>0) posY -= mp->sizeY;
	A_long cntY = (m_height - posY) / mp->sizeY;
	if (((m_height - posY) % mp->sizeY)>0) cntY++;

	if (( (posX+fp.sizeX) + fp.sizeX)>=m_width){
		posX = 0;
		fp.sizeX = m_width;
		cntX = 1;
	}
	if (( (posY + fp.sizeY)  + fp.sizeY)>=m_height){
		posY = 0;
		fp.sizeY = m_height;
		cntY = 1;
	}
	
	//�����_���̏�����
	FsPixelRandFloat pr;
	pr.a = pr.b = pr.g = pr.r = 0;
	A_long randValue;
	if (mp->rand >0){
		if (mp->isFrameRand == TRUE){
			init_xorShift(m_frame);
		}else{
			init_xorShift(0);
		}
		randValue = (A_long)(PF_MAX_CHAN16 * mp->rand);
	}
	A_long i,j;
	for ( j=0; j<cntY; j++){
		fp.y =  posY + j * fp.sizeY;
		for ( i=0; i<cntX; i++){
			fp.x =  posX + i * fp.sizeX;
			if ( mp->rand>0){
				if ( mp->isRandGray){
					pr.a = pr.b = pr.g = pr.r
						= (PF_FpShort)((PF_FpShort)F_RAND2(-randValue,randValue) / PF_MAX_CHAN16);
				}else{
					pr.a = (PF_FpShort)((PF_FpShort)F_RAND2(-randValue,randValue)/ PF_MAX_CHAN16);
					pr.b = (PF_FpShort)((PF_FpShort)F_RAND2(-randValue,randValue)/ PF_MAX_CHAN16);
					pr.g = (PF_FpShort)((PF_FpShort)F_RAND2(-randValue,randValue)/ PF_MAX_CHAN16);
					pr.r = (PF_FpShort)((PF_FpShort)F_RAND2(-randValue,randValue)/ PF_MAX_CHAN16);
				}
			}
			flat32(&fp, &pr);
		}
	}
	return err;
}
//********************************************************
PF_Err CFsGraph::mosaic(FsMosaicParam *mp)
{
	PF_Err err = PF_Err_NONE;
	switch(m_format)
	{
	case PF_PixelFormat_ARGB128:
		mosaic32(mp);
		break;
	case PF_PixelFormat_ARGB64:
		mosaic16(mp);
		break;
	case PF_PixelFormat_ARGB32:
		mosaic8(mp);
		break;
	default:
		err = PF_Err_OUT_OF_MEMORY;
		break;
	}
	return err;
}
