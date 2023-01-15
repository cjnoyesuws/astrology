# make file for Astro-helper files

.SUFFIXES: $(EXT) .hlp .BSM .SYM

#.doc.hlp:
#  +del $@
#  buildtxt $*$(EXT) $& $(FMT) T
#  +del $&.ndx
#  +ren $&.txt $&

all: TEXT.BSM STRTABLE.BSM $(DST)\aspects.hlp $(DST)\compatab.hlp \
   $(DST)\famous.hlp $(DST)\rising.hlp $(DST)\plasigni.hlp \
   $(DST)\scoutpl.hlp $(DST)\retrogrd.hlp $(DST)\transits.hlp  \
   $(DST)\planets.hlp $(DST)\houses.hlp

TEXT.BSM : TEXT.SYM
    MKBSR TEXT.BSM TEXT.SYM

STRTABLE.BSM : STRING.TAB CHAR.TAB
    MKSTRB STRING.TAB CHAR.TAB

$(DST)\aspects.hlp:    $(SRC)\aspects$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\XXasXX $(FMT) T
   +del $(DST)\XXasXX.ndx
   +ren $(DST)\XXasXX.txt $&.hlp

$(DST)\compatab.hlp:   $(SRC)\compatab$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\$& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\famous.hlp:     $(SRC)\famous$(EXT)
   +del $@
   buildtxt $*$(EXT) $& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\planets.hlp:    $(SRC)\planets$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\XXPLXX $(FMT) T
   +del $(DST)\XXPLXX.ndx
   +ren $(DST)\XXPLXX.txt $&.hlp

$(DST)\rising.hlp:     $(SRC)\rising$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\$& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\plasigni.hlp:   $(SRC)\plasigni$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\$& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\transits.hlp:   $(SRC)\transits$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\$& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\scoutpl.hlp:    $(SRC)\scoutpl$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\$& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\retrogrd.hlp:   $(SRC)\retrogrd$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\$& $(FMT) T
   +del $(DST)\$&.ndx
   +ren $(DST)\$&.txt $&.hlp

$(DST)\houses.hlp:     $(SRC)\houses$(EXT)
   +del $@
   buildtxt $*$(EXT) $(DST)\XXHSXX $(FMT) T
   +del $(DST)\XXHSXX.ndx
   +ren $(DST)\XXHSXX.txt $&.hlp
