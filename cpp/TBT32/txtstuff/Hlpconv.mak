.SUFFIXES: $(EXT) .SRC

all:    $(DST)\COMPATAB$(EXT) $(DST)\PLANETS$(EXT) $(DST)\RISING$(EXT) \
	$(DST)\ASPECTS$(EXT) $(DST)\FAMOUS$(EXT) $(DST)\PLASIGNI$(EXT) \
	$(DST)\HOUSES$(EXT) $(DST)\TRANSITS$(EXT) $(DST)\SCOUTPL$(EXT) \
	$(DST)\RETROGRD$(EXT)

#.SRC$(EXT):
#    ASCTOAST $*.SRC $$temp$$.TMP
#    ASTTO$(FMT) $$temp$$.TMP $@
#    +del $$temp$$.TMP

$(DST)\COMPATAB$(EXT): $(SRC)\COMPATAB.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\PLANETS$(EXT): $(SRC)\PLANETS.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\RISING$(EXT): $(SRC)\RISING.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\ASPECTS$(EXT): $(SRC)\ASPECTS.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\FAMOUS$(EXT): $(SRC)\FAMOUS.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\PLASIGNI$(EXT): $(SRC)\PLASIGNI.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\HOUSES$(EXT): $(SRC)\HOUSES.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\TRANSITS$(EXT): $(SRC)\TRANSITS.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\SCOUTPL$(EXT): $(SRC)\SCOUTPL.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\RETROGRD$(EXT): $(SRC)\RETROGRD.SRC
    ASCTOASTI $*.SRC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

