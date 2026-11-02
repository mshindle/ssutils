#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "cgic.h"

// build vars getting a default if not set
#ifndef ASSETDIR
#define ASSETDIR "/tmp"
#endif
#ifndef CACHEDIR
#define CACHEDIR "/tmp"
#endif
#ifndef TMPDIR
#define TMPDIR "/tmp"
#endif

// Production Values
#define CRLF "\r\n"
#define BUFFER_SIZE 512
#define CMD_BUFFER (BUFFER_SIZE * 2)
#define SERVER_NAME     "yph"
#define TYPE_YPH        0
#define TYPE_SIG        1

typedef struct {
    char *baseName;
    char *bgColor;
} yph_type;

typedef struct {
    char *fname;
    int width;
    int height;
    int type;
} yph_asset;

// all of our assets
yph_asset assets[] = {
    {"yph0.gif", 50, 50, TYPE_YPH},
    {"yph1.gif", 75, 74, TYPE_YPH},
    {"yph2.gif", 98, 99, TYPE_YPH},
    {"yph3.gif", 140, 141, TYPE_YPH},
    {"yph4.gif", 197, 92, TYPE_YPH},
    {"yph5.gif", 230, 81, TYPE_YPH},
    {"sig0.png", 200, 100, TYPE_SIG}
};

// base file name
yph_type types[] = {
    {.baseName = "yph", .bgColor = "#a6a8ab"},
    {.baseName = "sig", .bgColor = "#ffffff"}
};
//char *baseName[] = {"yph", "sig"};

// does our file exist?
int file_exist(char *fname) {
    FILE *f;

    if ((f = fopen(fname, "r"))) {
        fclose(f);
        return 1;
    }
    return 0;
}

// how close does the file meet what we need?
int score(int w0, int h0, int w1, int h1) {
    int s;

    if (w1 < w0 || h1 < h0) return -1000;
    s = h1 - h0 + w1 - w0;
    return 1000 - s;
}

// find the best one...
int
find_best_yph(int width, int height, int type) {
    int i, s;
    int best = 0;
    int bscore = INT_MIN;
    int num = sizeof(assets) / sizeof(yph_asset);

    i = 0;
    while (i < num) {
        if (assets[i].type == type) {
            s = score(assets[i].width, assets[i].height, width, height);
            if (s > bscore) {
                best = i;
                bscore = s;
            }
        }
        i++;
    }
    return best;
}

int
determineTypeRequest() {
    int type;

    const cgiFormResultType rt = cgiFormIntegerBounded("type", &type,TYPE_YPH,TYPE_SIG,TYPE_YPH);
    switch (rt) {
        case cgiFormSuccess:
            return type;
        default:
            return TYPE_YPH;
    }
}

int
cgiMain() {
    char cacheName[BUFFER_SIZE];
    char cmd[CMD_BUFFER];
    char buf[BUFFER_SIZE];
    int width, height;

    if (cgiFormInteger("width", &width, 0) == cgiFormSuccess &&
        cgiFormInteger("height", &height, 0) == cgiFormSuccess) {
        FILE *f;
        // based on the type
        const int type = determineTypeRequest();

        // determine the width and height for the asset we need
        if (width < 0) width = 0;
        if (height < 0) height = 0;
        if (width > 1000) width = 1000;
        if (height > 1000) height = 1000;
        const int assetIndex = find_best_yph(width, height, type);

        // see if we have the file already...
        sprintf(cacheName, "%s/%s_%dx%d.png", CACHEDIR, types[type].baseName, width, height);
        if (!file_exist(cacheName)) {
            const __pid_t pid = getpid();
            sprintf(cmd,
                    "convert xc:%s -resize %dx%d! -gravity center %s/%s -compose over -composite %s/yph.%d.png",
                    types[type].bgColor, width, height, ASSETDIR, assets[assetIndex].fname,
                    TMPDIR, pid);
            system(cmd);
            sprintf(cmd, "mv -f %s/yph.%d.png %s", TMPDIR, pid, cacheName);
            system(cmd);
        }

        // send whatever we have out...
        if ((f = fopen(cacheName, "r"))) {
            fseek(f, 0, SEEK_END);
            const long int fsize = ftell(f);
            fseek(f, 0, SEEK_SET);
            // print out our header
            fprintf(cgiOut, "Content-length: %ld" CRLF "Content-type: image/png" CRLF CRLF, fsize);
            // print out our file
            while (!feof(f)) {
                const size_t num = fread(buf, 1, 512, f);
                fwrite(buf, 1, num, stdout);
            }
            fclose(f);
        }
    }
    return 0;
}
