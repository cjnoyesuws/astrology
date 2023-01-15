
# BUILD REPORTS

.SUFFIXES: $(EXT) .AST

all:  $(DST)\gender$(EXT) $(DST)\chhead$(EXT) $(DST)\RETURN$(EXT) \
      $(DST)\STRING$(EXT) $(DST)\monthstr$(EXT) $(DST)\ARABIC$(EXT) \
      $(DST)\helio$(EXT) $(DST)\PROBLEM$(EXT) $(DST)\FIXEDST$(EXT) \
      $(DST)\NUMERIC$(EXT) $(DST)\PROGRESS$(EXT) $(DST)\TRANSITR$(EXT) \
      $(DST)\TRANSAFT$(EXT) $(DST)\COMPOS$(EXT) $(DST)\COMPAT$(EXT) \
      $(DST)\COSUMMR$(EXT) $(DST)\NATAL$(EXT) $(DST)\SUMMARY$(EXT) \
      $(DST)\PROBRES$(EXT) $(DST)\ARABNAM$(EXT) $(DST)\FIXDNAMS$(EXT) \
      $(DST)\COTRANS$(EXT)

$(DST)\gender$(EXT) :  $(SRC)\gender.AST
  AST2$(FMT) $*.AST $@

$(DST)\chhead$(EXT) :  $(SRC)\chhead.AST
  AST2$(FMT) $*.AST $@

$(DST)\RETURN$(EXT) :  $(SRC)\RETURN.AST
  AST2$(FMT) $*.AST $@

$(DST)\STRING$(EXT) :  $(SRC)\STRING.AST
  AST2$(FMT) $*.AST $@

$(DST)\monthstr$(EXT) :  $(SRC)\monthstr.AST
  AST2$(FMT) $*.AST $@

$(DST)\ARABIC$(EXT) :  $(SRC)\ARABIC.AST
  AST2$(FMT) $*.AST $@

$(DST)\helio$(EXT) :  $(SRC)\helio.AST
  AST2$(FMT) $*.AST $@

$(DST)\PROBLEM$(EXT) : $(SRC)\PROBLEM.AST
  AST2$(FMT) $*.AST $@

$(DST)\PROBRES$(EXT) : $(SRC)\PROBRES.AST
  AST2$(FMT) $*.AST $@

$(DST)\FIXEDST$(EXT) : $(SRC)\FIXEDST.AST
  AST2$(FMT) $*.AST $@

$(DST)\NUMERIC$(EXT) : $(SRC)\NUMERIC.AST
  AST2$(FMT) $*.AST $@

$(DST)\PROGRESS$(EXT) : $(SRC)\PROGRESS.AST
  AST2$(FMT) $*.AST $@

$(DST)\TRANSITR$(EXT) : $(SRC)\TRANSITR.AST
  AST2$(FMT) $*.AST $@

$(DST)\TRANSAFT$(EXT) : $(SRC)\TRANSAFT.AST
  AST2$(FMT) $*.AST $@

$(DST)\COMPOS$(EXT) : $(SRC)\COMPOS.AST
  AST2$(FMT) $*.AST $@

$(DST)\COMPAT$(EXT) : $(SRC)\COMPAT.AST
  AST2$(FMT) $*.AST $@

$(DST)\COSUMMR$(EXT) : $(SRC)\COSUMMR.AST
  AST2$(FMT) $*.AST $@

$(DST)\NATAL$(EXT) : $(SRC)\NATAL.AST
  AST2$(FMT) $*.AST $@

$(DST)\SUMMARY$(EXT) : $(SRC)\SUMMARY.AST
  AST2$(FMT) $*.AST $@

$(DST)\ARABNAM$(EXT) : $(SRC)\ARABNAM.AST
  AST2$(FMT) $*.AST $@

$(DST)\FIXDNAMS$(EXT) : $(SRC)\FIXDNAMS.AST
  AST2$(FMT) $*.AST $@

$(DST)\COTRANS$(EXT) : $(DST)\COTRANS.AST
  AST2$(FMT) $*.AST $@
