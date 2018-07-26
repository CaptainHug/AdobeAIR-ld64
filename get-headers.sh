#!/bin/bash

mkdir osxinclude

# ==============================================
#cp -rf /usr/include/mach osxinclude/
#cp -rf /usr/include/mach-o osxinclude/
#cp -rf /usr/include/machine osxinclude/
#cp -rf /usr/include/mach_debug osxinclude/
#cp -rf /usr/include/libkern osxinclude/
#cp -rf /usr/include/uuid osxinclude/
#cp -rf /usr/include/architecture osxinclude/
#cp -rf /usr/include/i386 osxinclude/
#cp -rf /usr/include/architecture osxinclude/

#cp -rf /usr/include/Availability*.h osxinclude/
#cp -rf /usr/include/execinfo.h osxinclude/
#cp -rf /usr/include/dlfcn.h osxinclude/
#cp -rf /usr/include/libunwind.h osxinclude/
#cp -rf /usr/include/libunwind.h osxinclude/

# ==============================================
touch osxinclude/AvailabilityMacros.h
touch osxinclude/dlfcn.h
touch osxinclude/pwd.h
touch osxinclude/libc.h

#cp -f /usr/include/fts.h osxinclude/
#cp -f /usr/include/ar.h osxinclude/
touch osxinclude/spawn.h

# ==============================================
mkdir -p osxinclude/CommonCrypto
#cp -rf /usr/include/CommonCrypto/CommonDigest.h osxinclude/CommonCrypto/CommonDigest.h
touch osxinclude/CommonCrypto/CommonDigest.h

# ==============================================
mkdir -p osxinclude/uuid
touch osxinclude/uuid/uuid.h

# ==============================================
mkdir -p osxinclude/sys/_types
touch osxinclude/sys/mount.h
touch osxinclude/sys/_types.h
touch osxinclude/sys/_types/_mach_port_t.h
touch osxinclude/sys/_types/_os_inline.h
touch osxinclude/sys/_types/_uuid_t.h
touch osxinclude/sys/appleapiopts.h
touch osxinclude/sys/errno.h
touch osxinclude/sys/mman.h
touch osxinclude/sys/sysctl.h
touch osxinclude/sys/wait.h
touch osxinclude/sys/_symbol_aliasing.h
touch osxinclude/sys/_posix_availability.h
#cp -f /usr/include/sys/_endian.h osxinclude/sys/
#cp -f /usr/include/sys/cdefs.h osxinclude/sys/
#cp -f /usr/include/sys/signal.h osxinclude/sys/

# ==============================================
#cp -f include/mach/machine.h osxinclude/mach/machine.h
