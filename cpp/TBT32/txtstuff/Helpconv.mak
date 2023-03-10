# Conversion make file

.SUFFIXES: .AST $(EXT)

all:    $(DST)\COMPATAB$(EXT) $(DST)\PLANETS$(EXT) $(DST)\RISING$(EXT) \
	$(DST)\ASPECTS$(EXT) $(DST)\FAMOUS$(EXT) $(DST)\PLASIGNI$(EXT)  \
	$(DST)\HOUSES$(EXT) $(DST)\TRANSITS$(EXT) $(DST)\SCOUTPL$(EXT) \
	$(DST)\RETROGRD$(EXT)

#.AST$(EXT):
#    AST2$(FMT) $*.AST $@

$(DST)\COMPATAB$(EXT): $(SRC)\COMPATAB.AST
    AST2$(FMT) $*.AST $@

$(DST)\PLANETS$(EXT): $(SRC)\PLANETS.AST
    AST2$(FMT) $*.AST $@

$(DST)\RISING$(EXT): $(SRC)\RISING.AST
    AST2$(FMT) $*.AST $@

$(DST)\ASPECTS$(EXT): $(SRC)\ASPECTS.AST
    AST2$(FMT) $*.AST $@

$(DST)\FAMOUS$(EXT): $(SRC)\FAMOUS.AST
    AST2$(FMT) $*.AST $@

$(DST)\PLASIGNI$(EXT): $(SRC)\PLASIGNI.AST
    AST2$(FMT) $*.AST $@

$(DST)\HOUSES$(EXT): $(SRC)\HOUSES.AST
    AST2$(FMT) $*.AST $@

$(DST)\TRANSITS$(EXT): $(SRC)\TRANSITS.AST
    AST2$(FMT) $*.AST $@

$(DST)\SCOUTPL$(EXT): $(SRC)\SCOUTPL.AST
    AST2$(FMT) $*.AST $@

$(DST)\RETROGRD$(EXT): $(SRC)\RETROGRD.AST
    AST2$(FMT) $*.AST $@

