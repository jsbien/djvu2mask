#include <cstdarg>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <fcntl.h>
#include <errno.h>

#ifdef UNIX
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
#endif

#include "libdjvu/ddjvuapi.h"

#if HAVE_PUTC_UNLOCKED
# undef putc
# define putc putc_unlocked
#endif

#ifndef i18n
# define i18n(x) (x)
#endif

ddjvu_context_t *ctx;
ddjvu_document_t *doc;
const char *programname = 0;
const char *inputfilename = 0;
const char *outputfilename = 0;
FILE *fout = 0;

unsigned long ticks(void) {
#ifdef UNIX
    struct timeval tv;
    if (gettimeofday(&tv, NULL) >= 0)
        return (unsigned long)(((tv.tv_sec & 0xfffff) * 1000) + (tv.tv_usec / 1000));
#endif
    return 0;
}

void die(const char *message_fmt, ...) {
    va_list args;
    fprintf(stderr, "djvu2mask: ");
    va_start(args, message_fmt);
    vfprintf(stderr, message_fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(10);
}

void render(ddjvu_page_t *render_page, int pageno) {
    ddjvu_rect_t prect;
    ddjvu_rect_t rrect;
    ddjvu_format_t *format;
    int iw = ddjvu_page_get_width(render_page);
    int ih = ddjvu_page_get_height(render_page);
    char *image = 0;
    char white = (char)0xFF;
    int rowsize;

    // Debug: Output page dimensions
    fprintf(stderr, "Rendering page %d: width=%d, height=%d\n", pageno, iw, ih);

    prect.x = 0;
    prect.y = 0;
    prect.w = iw;
    prect.h = ih;

    rrect = prect;

    format = ddjvu_format_create(DDJVU_FORMAT_MSBTOLSB, 0, 0);
    if (!format) die("Failed to create format for rendering.");
    ddjvu_format_set_row_order(format, 1);

    rowsize = (rrect.w + 7) / 8;
    image = (char*)malloc(rowsize * rrect.h);
    if (!image) die("Cannot allocate image buffer for page %d", pageno);

    if (!ddjvu_page_render(render_page, DDJVU_RENDER_MASKONLY, &prect, &rrect, format, rowsize, image)) {
        memset(image, white, rowsize * rrect.h);
        fprintf(stderr, "Warning: Page %d rendered as empty mask.\n", pageno);
    }

    fprintf(fout, "P4\n%d %d\n", rrect.w, rrect.h);
    for (int i = 0; i < (int)rrect.h; i++, image += rowsize)
        if (fwrite(image, 1, rowsize, fout) < (size_t)rowsize)
            die("writing mask file: %s", strerror(errno));

    ddjvu_format_release(format);
    free(image);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: djvu2mask <djvufile> [<outputfile>]\n");
        exit(1);
    }

    inputfilename = argv[1];
    outputfilename = (argc > 2) ? argv[2] : "-";

    programname = argv[0];
    ctx = ddjvu_context_create(programname);
    if (!ctx) die("Cannot create djvu context. Error code: %d", errno);

    doc = ddjvu_document_create_by_filename(ctx, inputfilename, TRUE);
    if (!doc) die("Cannot open djvu document '%s'. Error code: %d", inputfilename, errno);

    fprintf(stderr, "Document loaded: %s\n", inputfilename);
    while (!ddjvu_document_decoding_done(doc)) {
        fprintf(stderr, "Decoding in progress...\n");
    }

    ddjvu_page_t *page = ddjvu_page_create_by_pageno(doc, 0);
    if (!page) die("Failed to load page 0.");

    fprintf(stderr, "Page 0 loaded, starting render...\n");

    fout = (strcmp(outputfilename, "-") == 0) ? stdout : fopen(outputfilename, "wb");
    if (!fout) die("Cannot open output file '%s'.", outputfilename);

    render(page, 1);

    fclose(fout);
    ddjvu_page_release(page);
    ddjvu_document_release(doc);
    ddjvu_context_release(ctx);

    return 0;
}

