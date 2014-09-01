#ifndef SRL_MERGER_H_
#define SRL_MERGER_H_

#include "EXTERN.h"
#include "perl.h"

/* General 'config' constants */
#ifdef MEMDEBUG
#   define INITIALIZATION_SIZE 1
#else
#   define INITIALIZATION_SIZE 64
#endif

#include "../Encoder/srl_buffer_types.h"

/* the merger main struct */
typedef struct {
    srl_buffer_t obuf;                  /* output buffer */
    unsigned char *ibuf_start;          /* ptr to "physical" start of input buffer */
    unsigned char *ibuf_end;            /* ptr to end of input buffer */
    unsigned char *ipos;                /* ptr to current position within input buffer */
    unsigned char *ibody_pos;           /* in Sereal V2, all offsets are relative to the body */

    AV *tracked_offsets;                /* list of tracked offsets */
    AV *tracked_offsets_with_duplicates;

    U32 protocol_version;             /* the version of the Sereal protocol to emit. */
    //HV *string_deduper_hv;            /* track strings we have seen before, by content */
} srl_merger_t;

srl_merger_t *srl_build_merger_struct(pTHX_ HV *opt);       /* constructor from options */
void srl_destroy_merger(pTHX_ srl_merger_t *mrg);           /* explicit destructor */
void srl_merger_append(pTHX_ srl_merger_t *mrg, SV *src);   /* class methods */
char * srl_merger_finish(pTHX_ srl_merger_t *mrg);

#endif

