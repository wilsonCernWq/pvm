// (c) by Stefan Roettger, licensed under GPL 2+

#ifndef DDSBASE_H
#define DDSBASE_H

#include <pvm_export.h>

#include "codebase.h" // universal code base

PVM_EXPORT void
writeDDSfile(const char*    filename,
             unsigned char* data,
             unsigned int   bytes,
             unsigned int   skip   = 0,
             unsigned int   strip  = 0,
             BOOLINT        nofree = FALSE);
PVM_EXPORT unsigned char*
readDDSfile(const char* filename, unsigned int* bytes);

PVM_EXPORT void
writeRAWfile(const char*    filename,
             unsigned char* data,
             unsigned int   bytes,
             BOOLINT        nofree = FALSE);
PVM_EXPORT unsigned char*
readRAWfile(const char* filename, unsigned int* bytes);

PVM_EXPORT void
writePNMimage(const char*    filename,
              unsigned char* image,
              unsigned int   width,
              unsigned int   height,
              unsigned int   components,
              BOOLINT        dds = FALSE);
PVM_EXPORT unsigned char*
readPNMimage(const char*   filename,
             unsigned int* width,
             unsigned int* height,
             unsigned int* components);

PVM_EXPORT void
writePVMvolume(const char*    filename,
               unsigned char* volume,
               unsigned int   width,
               unsigned int   height,
               unsigned int   depth,
               unsigned int   components  = 1,
               float          scalex      = 1.0f,
               float          scaley      = 1.0f,
               float          scalez      = 1.0f,
               unsigned char* description = NULL,
               unsigned char* courtesy    = NULL,
               unsigned char* parameter   = NULL,
               unsigned char* comment     = NULL);

PVM_EXPORT unsigned char*
readPVMvolume(const char*     filename,
              unsigned int*   width,
              unsigned int*   height,
              unsigned int*   depth,
              unsigned int*   components  = NULL,
              float*          scalex      = NULL,
              float*          scaley      = NULL,
              float*          scalez      = NULL,
              unsigned char** description = NULL,
              unsigned char** courtesy    = NULL,
              unsigned char** parameter   = NULL,
              unsigned char** comment     = NULL);

PVM_EXPORT int
checkfile(const char* filename);
PVM_EXPORT unsigned int
checksum(unsigned char* data, unsigned int bytes);

PVM_EXPORT void
swapbytes(unsigned char* data, long long bytes);
PVM_EXPORT void
convbytes(unsigned char* data, long long bytes);
PVM_EXPORT void
convfloat(unsigned char** data, long long bytes);
PVM_EXPORT void
convrgb(unsigned char** data, long long bytes);

PVM_EXPORT unsigned char*
quantize(unsigned char* volume,
         long long      width,
         long long      height,
         long long      depth,
         BOOLINT        msb    = TRUE,
         BOOLINT        linear = FALSE,
         BOOLINT        nofree = FALSE);

PVM_EXPORT char*
processPVMvolume(const char* filename);

#endif
