#define _GNU_SOURCE

#include <dlfcn.h>
#include <link.h>
#include <linux/limits.h>
#include <stdio.h>

// TODO: can we avoid clobbering dlerror?

static inline const char *nullable(const char *s) { return s ? s : "<NULL>"; }

static void display_info(const char *filename, void *handle) {
    union {
        char path[PATH_MAX + 1];
        struct link_map *lmap;
    } info;
    // TODO: When (!filename && handle), RTLD_DI_ORIGIN segfaults internally...
    if (dlinfo(handle, RTLD_DI_LINKMAP, &info.lmap) == 0) {
        fprintf(stderr, "[DLTRACER] %s -> %s\n", nullable(filename),
                nullable(info.lmap->l_name));
    } else if (dlinfo(handle, RTLD_DI_ORIGIN, info.path) == 0) {
        fprintf(stderr, "[DLTRACER] %s -> %s\n", nullable(filename), info.path);
    } else {
        fprintf(stderr, "[DLTRACER] dlinfo(): %s\n", nullable(dlerror()));
    }
}

void *dlopen(const char *filename, int flags) {
    fprintf(stderr, "[DLTRACER] Calling dlopen on %s\n", nullable(filename));

    void *(*original_dlopen)(const char *, int) = dlsym(RTLD_NEXT, "dlopen");
    if (!original_dlopen) {
        fprintf(stderr, "[DLTRACER] Could not resolve dlopen\n");
        return NULL;
    }

    void *handle = original_dlopen(filename, flags);
    if (handle) {
        display_info(filename, handle);
    }

    return handle;
}

void *dlmopen(Lmid_t lmid, const char *filename, int flags) {
    fprintf(stderr, "[DLTRACER] Calling dlmopen on %s\n", nullable(filename));

    void *(*original_dlmopen)(Lmid_t, const char *, int) =
        dlsym(RTLD_NEXT, "dlmopen");
    if (!original_dlmopen) {
        fprintf(stderr, "[DLTRACER] Could not resolve dlmopen\n");
        return NULL;
    }

    void *handle = original_dlmopen(lmid, filename, flags);
    if (handle) {
        display_info(filename, handle);
    }

    return handle;
}
