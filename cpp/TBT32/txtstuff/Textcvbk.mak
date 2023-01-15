# Conversion make file

.SUFFIXES: .AST .AST

XT=$(DST)\as16text.AST $(DST)\as17text.AST
XT2=$(DST)\as18text.AST $(DST)\as19text.AST
#if XTXT=YES
XTXTNM=$(XT)
XTXTNM2=$(XT2)
#else
XTXTNM=
XTXTNM2=
#endif

all: $(DST)\as1text.AST $(DST)\as10text.AST $(DST)\as12text.AST \
	$(DST)\as11text.AST $(DST)\as2text.AST $(DST)\as3atext.AST \
	$(DST)\as3ctext.AST $(DST)\as3btext.AST $(DST)\as5text.AST \
	$(DST)\as6text.AST $(DST)\as13text.AST $(DST)\as7text.AST \
	$(DST)\as9text.AST $(DST)\as8text.AST $(DST)\as14text.AST \
	$(DST)\as15text.AST $(XTXTNM) $(XTXTNM2)

#.AST.AST:
#    $(FMT)TOAST $*$(EXT) $@

$(DST)\as1text.AST: $(SRC)\as1text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as10text.AST: $(SRC)\as10text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as12text.AST: $(SRC)\as12text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as11text.AST: $(SRC)\as11text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as2text.AST: $(SRC)\as2text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as3atext.AST: $(SRC)\as3atext$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as3ctext.AST: $(SRC)\as3ctext$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as3btext.AST: $(SRC)\as3btext$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as5text.AST: $(SRC)\as5text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as6text.AST: $(SRC)\as6text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as13text.AST: $(SRC)\as13text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as7text.AST: $(SRC)\as7text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as9text.AST: $(SRC)\as9text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as8text.AST: $(SRC)\as8text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as14text.AST: $(SRC)\as14text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as15text.AST: $(SRC)\as15text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

#if XTXT=YES

$(DST)\as16text.AST: $(SRC)\as16text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as17text.AST: $(SRC)\as17text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as18text.AST: $(SRC)\as18text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

$(DST)\as19text.AST: $(SRC)\as19text$(EXT)
    $(FMT)TOAST $*$(EXT) $@

#endif
