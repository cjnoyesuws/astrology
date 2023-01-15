# Conversion make file

.SUFFIXES: .AST $(EXT)

XT=$(DST)\as16text$(EXT) $(DST)\as17text$(EXT)
XT2=$(DST)\as18text$(EXT) $(DST)\as19text$(EXT)
#if XTXT=YES
XTXTNM=$(XT)
XTXTNM2=$(XT2)
#else
XTXTNM=
XTXTNM2=
#endif

all: $(DST)\as1text$(EXT) $(DST)\as10text$(EXT) $(DST)\as12text$(EXT) \
	$(DST)\as11text$(EXT) $(DST)\as2text$(EXT) $(DST)\as3atext$(EXT) \
	$(DST)\as3ctext$(EXT) $(DST)\as3btext$(EXT) $(DST)\as5text$(EXT) \
	$(DST)\as6text$(EXT) $(DST)\as13text$(EXT) $(DST)\as7text$(EXT) \
	$(DST)\as9text$(EXT) $(DST)\as8text$(EXT) $(DST)\as14text$(EXT) \
	$(DST)\as15text$(EXT) $(XTXTNM) $(XTXTNM2)

#.AST$(EXT):
#    AST2$(FMT) $*.AST $@

$(DST)\as1text$(EXT): $(SRC)\as1text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as10text$(EXT): $(SRC)\as10text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as12text$(EXT): $(SRC)\as12text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as11text$(EXT): $(SRC)\as11text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as2text$(EXT): $(SRC)\as2text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as3atext$(EXT): $(SRC)\as3atext.AST
    AST2$(FMT) $*.AST $@

$(DST)\as3ctext$(EXT): $(SRC)\as3ctext.AST
    AST2$(FMT) $*.AST $@

$(DST)\as3btext$(EXT): $(SRC)\as3btext.AST
    AST2$(FMT) $*.AST $@

$(DST)\as5text$(EXT): $(SRC)\as5text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as6text$(EXT): $(SRC)\as6text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as13text$(EXT): $(SRC)\as13text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as7text$(EXT): $(SRC)\as7text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as9text$(EXT): $(SRC)\as9text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as8text$(EXT): $(SRC)\as8text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as14text$(EXT): $(SRC)\as14text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as15text$(EXT): $(SRC)\as15text.AST
    AST2$(FMT) $*.AST $@

#if XTXT=YES

$(DST)\as16text$(EXT): $(SRC)\as16text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as17text$(EXT): $(SRC)\as17text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as18text$(EXT): $(SRC)\as18text.AST
    AST2$(FMT) $*.AST $@

$(DST)\as19text$(EXT): $(SRC)\as19text.AST
    AST2$(FMT) $*.AST $@

#endif
