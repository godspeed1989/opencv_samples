#include "_cvcommon.h"

#include <cstring>
#include <ctime>

#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h>
#endif /* _WIN32 */


CV_IMPLEMENT_QSORT( icvSort_32f, float, less_than )

CV_IMPLEMENT_QSORT( icvSort_32s, int, less_than )

int icvMkDir( const char* filename )
{
    char path[PATH_MAX];
    char* p;
    int pos;

#ifdef _WIN32
    struct _stat st;
#else /* _WIN32 */
    struct stat st;
    mode_t mode;

    mode = 0755;
#endif /* _WIN32 */

    strcpy( path, filename );

    p = path;
    for( ; ; )
    {
        pos = (int)strcspn( p, "/\\" );

        if( pos == (int) strlen( p ) ) break;
        if( pos != 0 )
        {
            p[pos] = '\0';

#ifdef _WIN32
            if( p[pos-1] != ':' )
            {
                if( _stat( path, &st ) != 0 )
                {
                    if( _mkdir( path ) != 0 ) return 0;
                }
            }
#else /* _WIN32 */
            if( stat( path, &st ) != 0 )
            {
                if( mkdir( path, mode ) != 0 ) return 0;
            }
#endif /* _WIN32 */
        }

        p[pos] = '/';

        p += pos + 1;
    }

    return 1;
}

#if 0
/* debug functions */
void icvSave( const CvArr* ptr, const char* filename, int line )
{
    CvFileStorage* fs;
    char buf[PATH_MAX];
    const char* name;

    name = strrchr( filename, '\\' );
    if( !name ) name = strrchr( filename, '/' );
    if( !name ) name = filename;
    else name++; /* skip '/' or '\\' */

    sprintf( buf, "%s-%d-%d", name, line, time( NULL ) );
    fs = cvOpenFileStorage( buf, NULL, CV_STORAGE_WRITE_TEXT );
    if( !fs ) return;
    cvWrite( fs, "debug", ptr );
    cvReleaseFileStorage( &fs );
}
#endif // #if 0

/* End of file. */
