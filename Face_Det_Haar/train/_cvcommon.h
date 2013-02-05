#ifndef __CVCOMMON_H_
#define __CVCOMMON_H_

#include "opencv2/core/core.hpp"
#include "opencv2/core/internal.hpp"

#include "cxcore.h"
#include "cv.h"
#include "cxmisc.h"

#define __BEGIN__ __CV_BEGIN__
#define __END__  __CV_END__
#define EXIT __CV_EXIT__

#define CV_DECLARE_QSORT( func_name, T, less_than )                     \
void func_name( T* array, size_t length, int aux );

#define less_than( a, b ) ((a) < (b))

CV_DECLARE_QSORT( icvSort_32f, float, less_than )

CV_DECLARE_QSORT( icvSort_32s, int, less_than )

#ifndef PATH_MAX
#define PATH_MAX 512
#endif /* PATH_MAX */

int icvMkDir( const char* filename );

/* returns index at specified position from index matrix of any type.
   if matrix is NULL, then specified position is returned */
CV_INLINE
int icvGetIdxAt( CvMat* idx, int pos );

CV_INLINE
int icvGetIdxAt( CvMat* idx, int pos )
{
    if( idx == NULL )
    {
        return pos;
    }
    else
    {
        CvScalar sc;
        int type;

        type = CV_MAT_TYPE( idx->type );
        cvRawDataToScalar( idx->data.ptr + pos *
            ( (idx->rows == 1) ? CV_ELEM_SIZE( type ) : idx->step ), type, &sc );

        return (int) sc.val[0];
    }
}

/* debug functions */

#define CV_DEBUG_SAVE( ptr ) icvSave( ptr, __FILE__, __LINE__ );

void icvSave( const CvArr* ptr, const char* filename, int line );

#endif /* __CVCOMMON_H_ */

