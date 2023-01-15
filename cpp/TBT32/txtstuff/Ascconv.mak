.SUFFIXES: $(EXT) .ASC

all:    $(DST)\as1text$(EXT) $(DST)\as10text$(EXT) $(DST)\as12text$(EXT) \
	$(DST)\as11text$(EXT) $(DST)\as2text$(EXT) $(DST)\as3atext$(EXT) \
	$(DST)\as3ctext$(EXT) $(DST)\as3btext$(EXT) $(DST)\as5text$(EXT) \
	$(DST)\as6text$(EXT) $(DST)\as13text$(EXT) $(DST)\as7text$(EXT) \
	$(DST)\as9text$(EXT) $(DST)\as8text$(EXT) $(DST)\as14text$(EXT) \
	$(DST)\as15text$(EXT)

  #.ASC$(EXT):
  #    ASCTOAST $(SRC)\$*.ASC $$temp$$.TMP
  #    AST2$(FMT) $$temp$$.TMP $@
  #    +del $$temp$$.TMP

$(DST)\as1text$(EXT): $(SRC)\as1text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as10text$(EXT): $(SRC)\as10text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as11text$(EXT): $(SRC)\as11text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as12text$(EXT): $(SRC)\as12text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as13text$(EXT): $(SRC)\as13text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as14text$(EXT): $(SRC)\as14text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as15text$(EXT): $(SRC)\as15text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as2text$(EXT): $(SRC)\as2text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as3atext$(EXT): $(SRC)\as3atext.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as3ctext$(EXT): $(SRC)\as3ctext.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as3btext$(EXT): $(SRC)\as3btext.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as5text$(EXT): $(SRC)\as5text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as6text$(EXT): $(SRC)\as6text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as7text$(EXT): $(SRC)\as7text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as8text$(EXT): $(SRC)\as8text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

$(DST)\as9text$(EXT): $(SRC)\as9text.ASC
    ASCTOASTI $*.ASC $$temp$$.TMP
    AST2$(FMT) $$temp$$.TMP $@
    +del $$temp$$.TMP

